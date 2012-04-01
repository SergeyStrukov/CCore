/* HFSProc.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "HFSProc.h"

#include <CCore/inc/Exception.h>

namespace App {

/* class BuildPath */ 

void BuildPath::add(StrLen str) 
 {
  if( str.len<=out.len ) 
    {
     str.copyTo(out.ptr);
        
     out+=str.len;
    }
  else
    {
     fe=FileError_TooLongPath;
    }  
 }
 
char BuildPath::Subst(char ch) 
 {
  if( ch==':' || ch=='.' ) return '-';
  
  return ch;
 }
 
void BuildPath::Subst(StrLen str,char *out)
 {
  for(; +str ;++str) *(out++)=Subst(*str);
 }
 
void BuildPath::addHome(StrLen str) 
 {
  if( str.len<=out.len ) 
    {
     Subst(str,out.ptr);
        
     out+=str.len;
    }
  else
    {
     fe=FileError_TooLongPath;
    }  
 }
    
void BuildPath::back()
 {
  if( level==0 ) 
    {
     fe=FileError_BadName;
     
     return;
    }
  
  char *ptr=out.ptr-1;
  
  for(; ptr[-1]!='/' ;ptr--);
  
  out.len+=Dist(ptr,out.ptr);
  
  out.ptr=ptr;
  
  level--;
 }
   
void BuildPath::start()
 {
  add("./");
 }
 
void BuildPath::next(StrLen name,StrLen point_name)
 {
  if( fe ) return;
 
  if( !name )
    {
     fe=FileError_BadName;
     
     return;
    }

  if( IsDot(name) )
    {
     return;
    }
    
  if( IsDotDot(name) )  
    {
     back();
     
     return;
    }
    
  if( level==0 && IsTilde(name) )  
    {
     addHome(point_name);
    }
  else
    {
     add(name);  
    }
  
  add(StrLen("/",1));
  
  level++;
 }
   
void BuildPath::stop(StrLen name,StrLen point_name)
 {
  if( fe ) return;
 
  if( !name )
    {
     fe=FileError_BadName;
     
     return;
    }
    
  if( IsDotDot(name) && level==0 )  
    {
     fe=FileError_BadName;
     
     return;
    }
 
  if( level==0 && IsTilde(name) )  
    {
     addHome(point_name);
    }      
  else
    {  
     add(name);
    } 
 }
 
BuildPath::BuildPath(StrLen path,StrLen point_name)
 : fe(FileError_Ok)
 {
  if( +path && IsSlash(*path) ) ++path;
  
  out=Range(buf);
  level=0;

  start();
  
  for(;;)
    {
     SplitDirName split(path);
     
     if( !split )
       {
        stop(path,point_name);
        
        break;
       }
     else
       {
        next(split.dir_name,point_name);
        
        path=split.path;
       }
    }
 }
 
/* struct FileNode */ 

ErrorIdType FileNode::open(StrLen file_name,StrLen point_name,FlagType oflags)
 {
  BuildPath path(file_name,point_name);
  
  if( FileError fe=!path ) return error(fe);
  
  auto result=sys_file.open(path.getStr(),FileOpenFlags(oflags));
 
  if( FileError fe=result.error ) return error(fe);
    
  file_len=result.file_len;
  
  return error(NoError); 
 }
 
FileReadResult FileNode::read(FileLenType off,PtrLen<uint8> buf)
 {
  if( error_state ) return error_state;
  
  if( off>=file_len ) return FileReadResult(NoError,0);
  
  FileLenType avail=file_len-off;
  
  ulen len=buf.len;
  
  if( len>avail ) len=(ulen)avail;
  
  if( FileError fe=sys_file.read(off,buf.ptr,len) ) return error(fe); 
 
  return FileReadResult(NoError,len);
 }
  
FileWriteResult FileNode::write(FileLenType off,PtrLen<const uint8> data)
 {
  if( error_state ) return error_state;
  
  if( data.len>MaxLen(off) ) return error(FileError_LenOverflow);
  
  auto result=sys_file.write(off,data.ptr,data.len);
  
  if( FileError fe=result.error ) return error(fe);
  
  file_len=result.file_len;
  
  return FileWriteResult(NoError,result.file_len);
 }
 
ErrorIdType FileNode::close(bool preserve_file)
 {
  FileMultiError errout;
     
  sys_file.close(errout,preserve_file);
  
  if( FileError fe=errout.getFirst() ) return error(fe);
  
  return NoError;
 }
 
/* struct MemNode */ 

FileReadResult MemNode::do_read(FileLenType off_,PtrLen<uint8> buf)
 {
  if( off_>=data.getLen() ) return FileReadResult(NoError,0);
  
  ulen off=ulen(off_);
  
  ulen avail=data.getLen()-off;
  
  Replace_min(buf.len,avail);
  
  buf.copy(data.getPtr()+off);
  
  return FileReadResult(NoError,buf.len);
 }
  
FileWriteResult MemNode::do_write(FileLenType off_,PtrLen<const uint8> src)
 {
  if( off_>MaxLen || src.len>MaxLen-(ulen)off_ ) return ToErrorId(FileError_LenOverflow);
  
  try
    {
     ulen off=ulen(off_);

     if( off<data.getLen() )
       {
        ulen avail=data.getLen()-off;
     
        src.takeup(avail).copyTo(data.getPtr()+off);

        if( +src ) data.extend_copy(src.len,src.ptr);
       }
     else
       {
        data.extend_default(off-data.getLen());
    
        if( +src ) data.extend_copy(src.len,src.ptr);
       }  
       
     return FileWriteResult(NoError,data.getLen());
    }
  catch(CatchType)  
    {
     return ToErrorId(FileError_DiskFull);
    }
 }
  
ErrorIdType MemNode::open(FlagType oflags_,MemNodeExt *ext_) 
 { 
  data.erase();
  
  oflags=oflags_;
  ext=ext_;
 
  return NoError; 
 }
  
FileReadResult MemNode::read(FileLenType off,PtrLen<uint8> buf)
 {
  if( !(oflags&Open_Read) ) return ToErrorId(FileError_NoMethod);
  
  return do_read(off,buf);
 }
  
FileWriteResult MemNode::write(FileLenType off,PtrLen<const uint8> data)
 {
  if( !(oflags&Open_Write) ) return ToErrorId(FileError_NoMethod);
  
  return do_write(off,data);
 }
  
ErrorIdType MemNode::close(bool preserve_file) 
 {
  ErrorIdType ret=NoError;
  
  if( ext )
    {
     ret=ext->atClose(this,preserve_file);
     
     delete ext;
     
     ext=0;
    }
  
  data.erase();
  
  return ret;
 }
 
/* class PrintMemNode */  

PtrLen<char> PrintMemNode::do_provide(ulen)
 {
  if( error_id ) return Nothing;
  
  return Range(buf);
 }
   
void PrintMemNode::do_flush(char *ptr,ulen len)
 {
  auto result=node->do_write(off,Mutate<const uint8>(Range(ptr,len)));
  
  off+=len;
  
  error_id=result.error_id;
 }
  
PrintMemNode::PrintMemNode(MemNode *node_)
 : node(node_),
   off(0),
   error_id(NoError)
 {
 }
   
PrintMemNode::~PrintMemNode()
 {
  flush();
 }
 
ErrorIdType PrintMemNode::complete()
 {
  flush();
  
  return error_id;
 }
 
/* class FileSet */ 

FileSet::FileSet(ulen max_files)
 : set(max_files)
 {
 }
   
FileSet::~FileSet()
 {
 }
   
FileResult FileSet::open(XPoint point,StrLen file_name,StrLen point_name,FlagType oflags)
 {
  auto result=set.allocNode(point);
 
  if( !result.node ) return Error_Exhausted;
  
  if( ErrorIdType error_id=result.node->open(file_name,point_name,oflags) )
    {
     set.freeNode(result.node);
    
     return error_id;
    }
    
  return FileResult(result.file_id,result.node);  
 }
   
ErrorIdType FileSet::close(FileNode *node,bool preserve_file)
 {
  ErrorIdType error_id=node->close(preserve_file);
  
  set.freeNode(node);
  
  return error_id;
 }
   
/* class MemSet */  
 
MemSet::MemSet(ulen max_mems)
 : set(max_mems)
 {
 }
   
MemSet::~MemSet()
 {
 }
   
MemResult MemSet::open(XPoint point,FlagType oflags,MemNodeExt *ext)
 {
  auto result=set.allocNode(point);
 
  if( !result.node ) 
    {
     delete ext;
     
     return Error_Exhausted;
    }
  
  if( ErrorIdType error_id=result.node->open(oflags,ext) )
    {
     delete ext;
    
     set.freeNode(result.node);
    
     return error_id;
    }
    
  return MemResult(result.file_id,result.node);  
 }
   
ErrorIdType MemSet::close(MemNode *node,bool preserve_file)
 {
  ErrorIdType error_id=node->close(preserve_file);
  
  set.freeNode(node);
  
  return error_id;
 }
   
/* class FileSystem */ 
 
FileSystem::FileSystem()
 {
  if( auto fe=fs.init() )
    {
     Printf(Exception,"App::FileSystem::FileSystem() : #;",fe);
    }
 }
   
FileSystem::~FileSystem()
 {
  if( auto fe=fs.exit() )
    {
     Printf(NoException,"App::FileSystem::~FileSystem() : #;",fe);
    }
 }
   
auto FileSystem::getFileType(StrLen path_,StrLen point_name) -> FileTypeResult
 {
  BuildPath path(path_,point_name);
  
  if( FileError fe=!path ) return FileTypeResult(fe);
  
  auto result=fs.getFileType(path.getStr());
  
  return FileTypeResult(result.error,result.type);
 }
 
ErrorIdType FileSystem::getFileList(StrLen dir_name_,StrLen point_name,MemNode *node)
 {
  BuildPath dir_name(dir_name_,point_name);
  
  if( FileError fe=!dir_name ) return ToErrorId(fe);

  PrintMemNode out(node);
  
  Sys::FileSystem::DirCursor cur;
  
  cur.init(&fs,dir_name.getStr());
  
  if( FileError fe=cur.error ) return ToErrorId(fe);  
  
  while( cur.next() )
    {
     Printf(out,"#; #.c;\n",StrLen(cur.file_name,cur.len),(cur.type==FileType_file)?'f':'d');
    }
    
  if( FileError fe=cur.error )  
    {
     cur.exit();
     
     return ToErrorId(fe);
    }
  else
    {  
     cur.exit();  
  
     return out.complete();
    } 
 }
 
ErrorIdType FileSystem::createFile(StrLen file_name,StrLen point_name)
 {
  BuildPath path(file_name,point_name);
  
  if( FileError fe=!path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.createFile(path.getStr()) );
 }
   
ErrorIdType FileSystem::deleteFile(StrLen file_name,StrLen point_name)
 {
  BuildPath path(file_name,point_name);
  
  if( FileError fe=!path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.deleteFile(path.getStr()) );
 }
   
ErrorIdType FileSystem::createDir(StrLen dir_name,StrLen point_name)
 {
  BuildPath path(dir_name,point_name);
  
  if( FileError fe=!path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.createDir(path.getStr()) );
 }
   
ErrorIdType FileSystem::deleteDir(StrLen dir_name,StrLen point_name,bool recursive)
 {
  BuildPath path(dir_name,point_name);
  
  if( FileError fe=!path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.deleteDir(path.getStr(),recursive) );
 }
   
ErrorIdType FileSystem::rename(StrLen old_path_,StrLen new_path_,StrLen point_name,bool allow_overwrite)
 {
  BuildPath old_path(old_path_,point_name);
  
  if( FileError fe=!old_path ) return ToErrorId(fe);
  
  BuildPath new_path(new_path_,point_name);
  
  if( FileError fe=!new_path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.rename(old_path.getStr(),new_path.getStr(),allow_overwrite) );
 }
 
ErrorIdType FileSystem::remove(StrLen path_,StrLen point_name)
 {
  BuildPath path(path_,point_name);
  
  if( FileError fe=!path ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.remove(path.getStr()) );
 }
   
ErrorIdType FileSystem::exec(StrLen dir_,StrLen program_,StrLen arg,StrLen point_name) 
 {
  BuildPath dir(dir_,point_name);
  
  if( FileError fe=!dir ) return ToErrorId(fe);
  
  BuildPath program(program_,point_name);
  
  if( FileError fe=!program ) return ToErrorId(fe);
  
  return ToErrorId_Ok( fs.exec(dir.getStr(),program.getStr(),arg) );
 }
 
/* class HFSProc */ 

void HFSProc::function_Open(Inbound &inbound)
 {
  Tailed<Net::HFS::OpenInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen file_name=Mutate<const char>(input.tail);
  
  FileResult result=file_set.open(inbound.point,file_name,desc.getStr(),input.base.open_flags);
  
  if( result.error_id )
    {
     log("HFSOpen(#;,#.q;,#;) error : #;",desc,file_name,FileOpenFlags(input.base.open_flags),GetErrorDesc(result.error_id));
    
     inbound.error_id=result.error_id;
     
     return inbound.send_error(ptp);
    }
    
  Net::HFS::OpenOutput output(result.file_id,result.node->getLen());
  
  log("HFSOpen(#;,#.q;,#;) at slot #;",desc,file_name,FileOpenFlags(input.base.open_flags),result.file_id.slot);  
  
  inbound.send_info(output,ptp);
 }
   
void HFSProc::function_Read(Inbound &inbound)
 {
  Net::HFS::ReadInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  if( TakeMemFlag(input.file_id) )
    {
     MemNode *node=mem_set.find(input.file_id);
     
     if( !node )
       {
        log("HFSRead(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
       
     PtrLen<uint8> buf=inbound.send_buf<Net::HFS::ReadOutput>(input.len);  
  
     FileReadResult ioresult=node->read(input.off,buf);  
    
     if( ioresult.error_id )  
       {
        log("HFSRead(...) error : #;",GetErrorDesc(ioresult.error_id));
    
        inbound.error_id=ioresult.error_id;
     
        return inbound.send_error(ptp);
       }
    
     Net::HFS::ReadOutput output(input.off,ioresult.len); 
  
     inbound.send_info_tailed(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.file_id);
  
     if( !node )
       {
        log("HFSRead(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
    
     PtrLen<uint8> buf=inbound.send_buf<Net::HFS::ReadOutput>(input.len);  
  
     FileReadResult ioresult=node->read(input.off,buf);  
    
     if( ioresult.error_id )  
       {
        log("HFSRead(...) error : #;",GetErrorDesc(ioresult.error_id));
    
        inbound.error_id=ioresult.error_id;
     
        return inbound.send_error(ptp);
       }
    
     Net::HFS::ReadOutput output(input.off,ioresult.len); 
  
     inbound.send_info_tailed(output,ptp);
    }
 }
   
void HFSProc::function_Write(Inbound &inbound)
 {
  Tailed<Net::HFS::WriteInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  if( TakeMemFlag(input.base.file_id) )
    {
     MemNode *node=mem_set.find(input.base.file_id);
     
     if( !node )
       {
        log("HFSWrite(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
       
     FileWriteResult ioresult=node->write(input.base.off,input.tail);  
  
     if( ioresult.error_id )
       {
        log("HFSWrite(...) error : #;",GetErrorDesc(ioresult.error_id));
    
        inbound.error_id=ioresult.error_id;
     
        return inbound.send_error(ptp);
       }
    
     Net::HFS::WriteOutput output(ioresult.file_len); 
  
     inbound.send_info(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.base.file_id);
  
     if( !node )
       {
        log("HFSWrite(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
    
     FileWriteResult ioresult=node->write(input.base.off,input.tail);  
  
     if( ioresult.error_id )
       {
        log("HFSWrite(...) error : #;",GetErrorDesc(ioresult.error_id));
    
        inbound.error_id=ioresult.error_id;
     
        return inbound.send_error(ptp);
       }
    
     Net::HFS::WriteOutput output(ioresult.file_len); 
  
     inbound.send_info(output,ptp);
    }
 }
   
void HFSProc::function_Close(Inbound &inbound)
 {
  Net::HFS::CloseInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  if( TakeMemFlag(input.file_id) )
    {
     MemNode *node=mem_set.find(input.file_id);
     
     if( !node )
       {
        log("HFSClose(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
     
     if( ErrorIdType error_id=mem_set.close(node,input.preserve_file) )
       {
        log("HFSClose(...) error : #;",GetErrorDesc(error_id));
    
        inbound.error_id=error_id;
     
        return inbound.send_error(ptp);
       }
     
     Net::HFS::CloseOutput output;
  
     log("HFSClose(...#;) at mem slot #;",(input.preserve_file?",preserve":""),input.file_id.slot);
  
     inbound.send_info(output,ptp);
    }
  else
    {
     FileNode *node=file_set.find(input.file_id);
  
     if( !node )
       {
        log("HFSClose(...) error : invalid file_id");
    
        inbound.error_id=ToErrorId(FileError_BadId);
     
        return inbound.send_error(ptp);
       }
    
     if( ErrorIdType error_id=file_set.close(node,input.preserve_file) )
       {
        log("HFSClose(...) error : #;",GetErrorDesc(error_id));
    
        inbound.error_id=error_id;
     
        return inbound.send_error(ptp);
       }
    
     Net::HFS::CloseOutput output;
  
     log("HFSClose(...#;) at slot #;",(input.preserve_file?",preserve":""),input.file_id.slot);
  
     inbound.send_info(output,ptp);
    }
 }
   
void HFSProc::function_GetFileType(Inbound &inbound)
 {
  Tailed<Net::HFS::GetFileTypeInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen path=Mutate<const char>(input.tail);
  
  auto result=filesys.getFileType(path,desc.getStr());
  
  if( result.error_id )
    {
     log("HFSGetFileType(#;,#.q;) error : #;",desc,path,GetErrorDesc(result.error_id));
    
     inbound.error_id=result.error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::GetFileTypeOutput output(result.type);
  
  log("HFSGetFileType(#;,#.q;) = #;",desc,path,result.type);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_GetFileList(Inbound &inbound)
 {
  Tailed<Net::HFS::GetFileListInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen dir_name=Mutate<const char>(input.tail);
  
  MemResult result=mem_set.open(inbound.point,Open_Read);
  
  if( result.error_id )
    {
     log("HFSGetFileList(#;,#.q;) error : #;",desc,dir_name,GetErrorDesc(result.error_id));
    
     inbound.error_id=result.error_id;
     
     return inbound.send_error(ptp);
    }
  
  if( ErrorIdType error_id=filesys.getFileList(dir_name,desc.getStr(),result.node) )
    {
     mem_set.close(result.node);
    
     log("HFSGetFileList(#;,#.q;) error : #;",desc,dir_name,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
    
  Net::HFS::GetFileListOutput output(result.file_id,result.node->getLen());
  
  log("HFSGetFileList(#;,#.q;) at mem slot #;",desc,dir_name,result.file_id.slot);
  
  SetMemFlag(output.file_id);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_CreateFile(Inbound &inbound)
 {
  Tailed<Net::HFS::CreateFileInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen file_name=Mutate<const char>(input.tail);
  
  if( ErrorIdType error_id=filesys.createFile(file_name,desc.getStr()) )
    {
     log("HFSCreateFile(#;,#.q;) error : #;",desc,file_name,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::CreateFileOutput output;
  
  log("HFSCreateFile(#;,#.q;)",desc,file_name);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_DeleteFile(Inbound &inbound)
 {
  Tailed<Net::HFS::DeleteFileInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen file_name=Mutate<const char>(input.tail);
  
  if( ErrorIdType error_id=filesys.deleteFile(file_name,desc.getStr()) )
    {
     log("HFSDeleteFile(#;,#.q;) error : #;",desc,file_name,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::DeleteFileOutput output;
  
  log("HFSDeleteFile(#;,#.q;)",desc,file_name);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_CreateDir(Inbound &inbound)
 {
  Tailed<Net::HFS::CreateDirInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen dir_name=Mutate<const char>(input.tail);
  
  if( ErrorIdType error_id=filesys.createDir(dir_name,desc.getStr()) )
    {
     log("HFSCreateDir(#;,#.q;) error : #;",desc,dir_name,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::CreateDirOutput output;
  
  log("HFSCreateDir(#;,#.q;)",desc,dir_name);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_DeleteDir(Inbound &inbound)
 {
  Tailed<Net::HFS::DeleteDirInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen dir_name=Mutate<const char>(input.tail);
  
  if( ErrorIdType error_id=filesys.deleteDir(dir_name,desc.getStr(),input.base.recursive) )
    {
     log("HFSDeleteDir(#;,#.q;#;) error : #;",desc,dir_name,(input.base.recursive?",recursive":""),GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::DeleteDirOutput output;
  
  log("HFSDeleteDir(#;,#.q;#;)",desc,dir_name,(input.base.recursive?",recursive":""));
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_Rename(Inbound &inbound)
 {
  Net::HFS::RenameInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen old_path=Mutate<const char>(input.old_path.path);
  StrLen new_path=Mutate<const char>(input.new_path.path);
  
  if( ErrorIdType error_id=filesys.rename(old_path,new_path,desc.getStr(),input.allow_overwrite) )
    {
     log("HFSRename(#;,#.q;,#.q;#;) error : #;",desc,old_path,new_path,(input.allow_overwrite?",overwrite":""),GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
    
  Net::HFS::RenameOutput output;  
  
  log("HFSRename(#;,#.q;,#.q;#;)",desc,old_path,new_path,(input.allow_overwrite?",overwrite":""));
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_Remove(Inbound &inbound)
 {
  Tailed<Net::HFS::RemoveInput> input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen path=Mutate<const char>(input.tail);
  
  if( ErrorIdType error_id=filesys.remove(path,desc.getStr()) )
    {
     log("HFSRemove(#;,#.q;) error : #;",desc,path,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::RemoveOutput output;
  
  log("HFSRemove(#;,#.q;)",desc,path);
  
  inbound.send_info(output,ptp);
 }
  
void HFSProc::function_Exec(Inbound &inbound)
 {
  Net::HFS::ExecInput input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen dir=Mutate<const char>(input.dir.path);
  StrLen program=Mutate<const char>(input.program.path);
  StrLen arg=Mutate<const char>(input.arg.path);
  
  if( ErrorIdType error_id=filesys.exec(dir,program,arg,desc.getStr()) )
    {
     log("HFSExec(#;,#.q;,#.q;,#.q;) error : #;",desc,dir,program,arg,GetErrorDesc(error_id));
    
     inbound.error_id=error_id;
     
     return inbound.send_error(ptp);
    }
    
  Net::HFS::ExecOutput output;
  
  log("HFSExec(#;,#.q;,#.q;,#.q;)",desc,dir,program,arg);
  
  inbound.send_info(output,ptp);
 }
 
ErrorIdType HFSProc::Exec2Ext::atClose(MemNode *node,bool preserve_file)
 {
  if( !preserve_file ) return NoError;
 
  StrLen arg(Mutate<const char>(node->getData()));
 
  return filesys.exec(Range(dir),Range(program),arg,Range(point_name));
 }
 
HFSProc::Exec2Ext::Exec2Ext(FileSystem &filesys_,StrLen dir_,StrLen program_,StrLen point_name_)
 : filesys(filesys_),
   dir(dir_),
   program(program_),
   point_name(point_name_)
 {
 }
      
HFSProc::Exec2Ext::~Exec2Ext() 
 {
 }
  
void HFSProc::function_Exec2(Inbound &inbound)
 {
  Net::HFS::Exec2Input input;
  
  if( !inbound.getInput(input) ) return inbound.send_error(ptp);
  
  Net::PointDesc desc(ptp->getMPDevice(),inbound.point);
  
  StrLen dir=Mutate<const char>(input.dir.path);
  StrLen program=Mutate<const char>(input.program.path);
  
  Exec2Ext *ext;
  
  try
    {
     ext=new Exec2Ext(filesys,dir,program,desc.getStr());
    }
  catch(CatchType)  
    {
     log("HFSExec2(#;,#.q;,#.q;) error : no memory",desc,dir,program);
    
     inbound.error_id=Error_Exhausted;
     
     return inbound.send_error(ptp);
    }
  
  MemResult result=mem_set.open(inbound.point,Open_Read|Open_Write,ext);
  
  if( result.error_id )
    {
     log("HFSExec2(#;,#.q;,#.q;) error : #;",desc,dir,program,GetErrorDesc(result.error_id));
    
     inbound.error_id=result.error_id;
     
     return inbound.send_error(ptp);
    }
  
  Net::HFS::Exec2Output output(result.file_id);
  
  log("HFSExec2(#;,#.q;,#.q;) at mem slot #;",desc,dir,program,result.file_id.slot);
  
  SetMemFlag(output.file_id);
  
  inbound.send_info(output,ptp);
 }
   
HFSProc::HFSProc(ServerProcBase *base,ulen max_files,ulen max_mems)
 : ProcBase(base),
   file_set(max_files),
   mem_set(max_mems)
 {
 }
   
HFSProc::~HFSProc()
 {
 }
   
void HFSProc::inbound(Inbound &inbound)
 {
  switch( inbound.serv_func.function_id )
    {
     case Net::HFS::FunctionId_Open :        function_Open(inbound); break;
    
     case Net::HFS::FunctionId_Read :        function_Read(inbound); break;
    
     case Net::HFS::FunctionId_Write :       function_Write(inbound); break;
    
     case Net::HFS::FunctionId_Close :       function_Close(inbound); break;
    
     case Net::HFS::FunctionId_GetFileType : function_GetFileType(inbound); break;
    
     case Net::HFS::FunctionId_GetFileList : function_GetFileList(inbound); break;
    
     case Net::HFS::FunctionId_CreateFile :  function_CreateFile(inbound); break;
    
     case Net::HFS::FunctionId_DeleteFile :  function_DeleteFile(inbound); break;
    
     case Net::HFS::FunctionId_CreateDir :   function_CreateDir(inbound); break;
    
     case Net::HFS::FunctionId_DeleteDir :   function_DeleteDir(inbound); break;
    
     case Net::HFS::FunctionId_Rename :      function_Rename(inbound); break;
    
     case Net::HFS::FunctionId_Remove :      function_Remove(inbound); break;
    
     case Net::HFS::FunctionId_Exec :        function_Exec(inbound); break;
    
     case Net::HFS::FunctionId_Exec2 :       function_Exec2(inbound); break;
    
     default:
      {
       inbound.error_id=Error_NoFunction;
       
       inbound.send_error(ptp);
      }
    }
 }
   
void HFSProc::tick()
 {
  // do nothing
 }
   
void HFSProc::session(XPoint point)
 {
  file_set.purge(point);
  mem_set.purge(point);
 }
   
bool HFSProc::exist(FunctionIdType function_id)
 {
  return function_id>=Net::HFS::FunctionId_Open && function_id<=Net::HFS::FunctionId_Exec2 ;
 }
 
} // namespace App
 
