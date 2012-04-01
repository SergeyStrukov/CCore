/* AsyncFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/AsyncFile.h>
 
#include <CCore/inc/Exception.h>
#include <CCore/inc/Path.h>

namespace CCore {

/* class AsyncFile */ 

void AsyncFile::setLarge()
 {
  ulen len=write_format.getMaxTotalLen();
  
  if( len>=MinLargeLen )
    large_write_len=Min(len,MaxLargeLen);
  else
    large_write_len=0;
 }
 
void AsyncFile::setError(FileError fe)
 {
  if( fe )
    {
     Mutex::Lock lock(mutex);
     
     if( !error ) error=fe;
    }
 }

FileError AsyncFile::getError()
 {
  Mutex::Lock lock(mutex);
     
  return error;
 }

void AsyncFile::guard()
 {
  if( !is_opened )
    {
     Printf(Exception,"CCore::AsyncFile::guard() : file is not opened");
    }
    
  if( FileError fe=getError() )
    {
     Printf(Exception,"CCore::AsyncFile::guard() : #;",fe);
    }
 }
 
void AsyncFile::complete_open(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::OpenExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  if( !error )
    {
     is_opened=true;
     preserve_file=false;
     
     write_format=ext->write_format;
     max_read_len=ext->max_read_len;
     file_len=ext->file_len;
     
     setLarge();
    }  
  
  packet.popExt().complete();
 }
 
void AsyncFile::complete_close(PacketHeader *packet_) 
 {
  Packet<uint8,Sys::AsyncFile::CloseExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  packet.popExt().complete();
 }
 
void AsyncFile::complete_write(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  setError(ext->error);
  
  packet.popExt().complete();
 }
 
void AsyncFile::complete_read(PacketHeader *packet_) 
 {
  Packet<uint8,Sys::AsyncFile::ReadExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  setError(ext->error);
  
  packet.popExt().complete();
 }
 
void AsyncFile::open(Sys::AsyncFileState *file_state,FileOpenFlags oflags,FilePosType file_len_)
 {
  file.open(file_state,oflags);
 
  error=FileError_Ok;
 
  is_opened=true;
  preserve_file=false;
     
  write_format=file_state->getWriteFormat();
  max_read_len=file_state->getMaxReadLen();
  file_len=file_len_;
  
  setLarge();
 }
 
AsyncFile::AsyncFile(MSec timeout_,ulen max_packets)
 : is_opened(false),
   pset("AsyncFile.pset",max_packets),
   timeout(timeout_),
   final_timeout(3*timeout_),
   mutex("AsyncFile")
 {
 }
   
AsyncFile::AsyncFile(StrLen file_name,FileOpenFlags oflags,MSec timeout_,ulen max_packets)
 : is_opened(false),
   pset("AsyncFile.pset",max_packets),
   timeout(timeout_),
   final_timeout(3*timeout_),
   mutex("AsyncFile")
 {
  open(file_name,oflags);
 }
   
AsyncFile::~AsyncFile()
 {
  if( is_opened )
    {
     FileMultiError errout;
  
     soft_close(errout);
 
     if( +errout )
       {
        Printf(NoException,"CCore::AsyncFile::~AsyncFile() : #;",errout);
       }
    }
 }
   
FilePosType AsyncFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  if( is_opened )
    {
     Printf(Exception,"CCore::AsyncFile::open(...) : already opened");
    }

  TimeScope time_scope(timeout);
    
  Packet<uint8> packet=pset.get(time_scope); 
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFile::open(...) : no packet");
    }
    
  Packet<uint8,Sys::AsyncFile::OpenExt> packet2=packet.pushExt<Sys::AsyncFile::OpenExt>();  
  
  packet2.pushCompleteFunction(function_complete_open());
    
  file.open(packet2,file_name,oflags);  
  
  pset.wait(time_scope);
  
  if( !is_opened )
    {
     file.closeState();
     
     Printf(Exception,"CCore::AsyncFile::open(#.q;,#;) : #;",file_name,oflags,error);
    }  
    
  return file_len;  
 }
   
void AsyncFile::soft_close(FileMultiError &errout)
 {
  if( !is_opened ) 
    {
     errout.add(FileError_NoMethod);
     
     return;
    }
  
  is_opened=false;
    
  pset.wait(final_timeout);
  
  errout.add(error);
  
  Packet<uint8> packet=pset.get(timeout);
  
  if( !packet )
    {
     errout.add(FileError_SysOverload);
     
     file.closeState();
    
     return;
    }
    
  Packet<uint8,Sys::AsyncFile::CloseExt> packet2=packet.pushExt<Sys::AsyncFile::CloseExt>(); 
  
  packet2.pushCompleteFunction(function_complete_close());
  
  file.close(packet2,preserve_file);
  
  pset.wait(timeout);
  
  file.closeState();
  
  errout.add(error);
 }
   
void AsyncFile::close()
 {
  FileMultiError errout;
  
  soft_close(errout);
 
  if( +errout )
    {
     Printf(Exception,"CCore::AsyncFile::close() : #;",errout);
    }
 }

void AsyncFile::setLargeWriteLen(ulen large_write_len_)
 {
  guard();
  
  if( large_write_len_ )
    large_write_len=Max(Min(large_write_len_,write_format.getMaxTotalLen()),MinLargeLen);
  else 
    large_write_len=0;
 }
 
AsyncFile::WritePacket AsyncFile::getWritePacket()
 {
  guard();
 
  Packet<uint8> packet=pset.get(timeout);  
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFile::getWritePacket() : timeout");
    }
  
  if( large_write_len ) packet.provide(large_write_len);
    
  PtrLen<uint8> buf=packet.getMaxRange(write_format).range;  
  
  if( !buf )
    {
     packet.complete();
     
     Printf(Exception,"CCore::AsyncFile::getWritePacket() : no room");
    }
  
  return WritePacket(packet,buf);
 }
 
void AsyncFile::write(FilePosType off,ulen len,Packet<uint8> packet) noexcept(EnableNoExcept)
 {
  if( !is_opened )
    {
     packet.complete();
     
     return;
    }
    
  Packet<uint8,Sys::AsyncFile::WriteExt> packet2=packet.pushExt<Sys::AsyncFile::WriteExt>();
  
  packet2.setDataLen(write_format,len);
  
  packet2.pushCompleteFunction(function_complete_write());
  
  file.write(packet2,off);
 }
 
void AsyncFile::read_all(FilePosType off,uint8 *buf,ulen len)
 {
  pset.wait(final_timeout);
  
  guard();
  
  if( !max_read_len )  
    {
     Printf(Exception,"CCore::AsyncFile::read_all(...) : no room");
    }
    
  for(auto range=Range(buf,len); +range ;)
    {
     auto frame=range.takeup(max_read_len);
     
     Packet<uint8> packet=pset.get(timeout);
  
     if( !packet ) 
       {
        pset.cancel_and_wait();
        
        Printf(Exception,"CCore::AsyncFile::read_all(...) : timeout");
       
        return;
       }
       
     Packet<uint8,Sys::AsyncFile::ReadExt> packet2=packet.pushExt<Sys::AsyncFile::ReadExt>(off,frame);  
     
     packet2.pushCompleteFunction(function_complete_read());
     
     file.read(packet2);
     
     off+=frame.len;
    }
    
  pset.wait(final_timeout);  
  
  if( error ) 
    {
     Printf(Exception,"CCore::AsyncFile::read_all(...) : #;",error);
    }
 }
 
void AsyncFile::read(FilePosType off,ulen len,PacketFunction complete_function)
 {
  TimeScope time_scope(timeout);  
  
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFile::read(...) : timeout");
    }

  Packet<uint8,Sys::AsyncFile::ReadBufExt> packet2=packet.pushExt<Sys::AsyncFile::ReadBufExt>(off,len);  
  
  packet2.pushCompleteFunction(complete_function);

  file.read(packet2);
 }
 
/* class AsyncFileSystem */ 

 // guard

void AsyncFileSystem::guard(const char *name,StrLen path)
 {
  if( error )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(#.q;) : #;",name,path,error);
    }
 }

void AsyncFileSystem::guard(const char *name,StrLen path1,StrLen path2)
 {
  if( error )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(#.q;,#.q;) : #;",name,path1,path2,error);
    }
 }

void AsyncFileSystem::guard(const char *name,StrLen path1,StrLen path2,StrLen path3)
 {
  if( error )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(#.q;,#.q;,#.q;) : #;",name,path1,path2,path3,error);
    }
 }

 // getPacket

void AsyncFileSystem::complete_error(PacketHeader *packet_) 
 {
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  packet.popExt().complete();
 }

Packet<uint8,Sys::AsyncFileSystem::ErrorExt> AsyncFileSystem::getPacket(const char *name,TimeScope time_scope) 
 {
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(...) : no packet",name);
    }
    
  Packet<uint8,Sys::AsyncFileSystem::ErrorExt> packet2=packet.pushExt<Sys::AsyncFileSystem::ErrorExt>();  
  
  packet2.pushCompleteFunction(function_complete_error());
  
  return packet2;
 }

 // getPacket_type

void AsyncFileSystem::complete_type(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFileSystem::FileTypeExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  if( !error ) file_type=ext->file_type;
  
  packet.popExt().complete();
 }
 
Packet<uint8,Sys::AsyncFileSystem::FileTypeExt> AsyncFileSystem::getPacket_type(const char *name,TimeScope time_scope)
 {
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(...) : no packet",name);
    }
    
  Packet<uint8,Sys::AsyncFileSystem::FileTypeExt> packet2=packet.pushExt<Sys::AsyncFileSystem::FileTypeExt>();  
  
  packet2.pushCompleteFunction(function_complete_type());
  
  return packet2;
 }

 // getPacket_file

void AsyncFileSystem::setFile(const char *name,AsyncFile &file_,FileOpenFlags oflags_)
 {
  if( file_.isOpened() )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(...) : file is already opened",name);
    }
 
  file=&file_;
  oflags=oflags_;
 }
 
void AsyncFileSystem::complete_file(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFileSystem::FileExt> packet=packet_;
  
  auto ext=packet.getExt();
  
  error=ext->error;
  
  if( !error )
    {
     file->open(ext->file_state,oflags,ext->file_len);
    }
  
  packet.popExt().complete();
 }
  
Packet<uint8,Sys::AsyncFileSystem::FileExt> AsyncFileSystem::getPacket_file(const char *name,TimeScope time_scope)
 {
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     Printf(Exception,"CCore::AsyncFileSystem::#;(...) : no packet",name);
    }
    
  Packet<uint8,Sys::AsyncFileSystem::FileExt> packet2=packet.pushExt<Sys::AsyncFileSystem::FileExt>();  
  
  packet2.pushCompleteFunction(function_complete_file());
  
  return packet2;
 }
   
 // public

AsyncFileSystem::AsyncFileSystem(StrLen dev_name,MSec timeout_,ulen max_packets)
 : pset(max_packets),
   timeout(timeout_)
 {
  if( FileError fe=fs.init(dev_name) )
    {
     Printf(Exception,"CCore::AsyncFileSystem::AsyncFileSystem(#.q;,...) : #;",dev_name,fe);
    }
 }
   
AsyncFileSystem::~AsyncFileSystem()
 {
  pset.cancel_and_wait();
 
  fs.exit();
 }
 
 // operations

FileType AsyncFileSystem::getFileType(StrLen path)
 {
  TimeScope time_scope(timeout);
  
  fs.getFileType(getPacket_type("getFileType",time_scope),path);
  
  pset.wait(time_scope);
  
  guard("getFileType",path);
  
  return file_type;  
 }
 
FilePosType AsyncFileSystem::getFileList(StrLen dir_name,AsyncFile &file)
 {
  setFile("getFileList",file,Open_Read);
  
  TimeScope time_scope(timeout);
  
  fs.getFileList(getPacket_file("getFileList",time_scope),dir_name);
  
  pset.wait(time_scope);
  
  guard("getFileList",dir_name);
  
  return file.file_len;
 }
  
void AsyncFileSystem::createFile(StrLen file_name)
 {
  TimeScope time_scope(timeout);
  
  fs.createFile(getPacket("createFile",time_scope),file_name);
  
  pset.wait(time_scope);
  
  guard("createFile",file_name);
 }
  
void AsyncFileSystem::deleteFile(StrLen file_name)
 {
  TimeScope time_scope(timeout);
  
  fs.deleteFile(getPacket("deleteFile",time_scope),file_name);
  
  pset.wait(time_scope);
  
  guard("deleteFile",file_name);
 }
  
void AsyncFileSystem::createDir(StrLen dir_name)
 {                                                
  TimeScope time_scope(timeout);
  
  fs.createDir(getPacket("createDir",time_scope),dir_name);
  
  pset.wait(time_scope);
  
  guard("createDir",dir_name);
 }
  
void AsyncFileSystem::deleteDir(StrLen dir_name,bool recursive)
 {
  TimeScope time_scope(timeout);
  
  fs.deleteDir(getPacket("deleteDir",time_scope),dir_name,recursive);
  
  pset.wait(time_scope);
  
  if( error )
    {
     Printf(Exception,"CCore::AsyncFileSystem::deleteDir(#.q;#;) : #;",dir_name,(recursive?",recursive":""),error);
    }
 }
  
void AsyncFileSystem::rename(StrLen old_path,StrLen new_path,bool allow_overwrite)
 {
  TimeScope time_scope(timeout);
  
  fs.rename(getPacket("rename",time_scope),old_path,new_path,allow_overwrite);
  
  pset.wait(time_scope);
  
  if( error )
    {
     Printf(Exception,"CCore::AsyncFileSystem::rename(#.q;,#.q;#;) : #;",old_path,new_path,(allow_overwrite?",overwrite":""),error);
    }
 }
  
void AsyncFileSystem::remove(StrLen path)
 {
  TimeScope time_scope(timeout);
  
  fs.remove(getPacket("remove",time_scope),path);
  
  pset.wait(time_scope);
  
  guard("remove",path);
 }
  
void AsyncFileSystem::exec(StrLen dir,StrLen program,StrLen arg)
 {
  TimeScope time_scope(timeout);
  
  fs.exec(getPacket("exec",time_scope),dir,program,arg);
  
  pset.wait(time_scope);
  
  guard("exec",dir,program,arg);
 }
  
void AsyncFileSystem::exec2(StrLen dir,StrLen program,AsyncFile &file)
 {
  setFile("exec2",file,Open_Write|Open_Read);
  
  TimeScope time_scope(timeout);
  
  fs.exec2(getPacket_file("exec2",time_scope),dir,program);
  
  pset.wait(time_scope);
  
  guard("exec2",dir,program);
 }
   
 // static

FileType AsyncFileSystem::GetFileType(StrLen path,MSec timeout)
 {
  SplitDevName split(path);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::GetFileType(#.q;,...) : bad name",path);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  return dev.getFileType(split.dev_path);
 }
  
void AsyncFileSystem::CreateFile(StrLen file_name,MSec timeout)
 {
  SplitDevName split(file_name);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::CreateFile(#.q;,...) : bad name",file_name);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  dev.createFile(split.dev_path);
 }
  
void AsyncFileSystem::DeleteFile(StrLen file_name,MSec timeout)
 {
  SplitDevName split(file_name);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::DeleteFile(#.q;,...) : bad name",file_name);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  dev.deleteFile(split.dev_path);
 }
  
void AsyncFileSystem::CreateDir(StrLen dir_name,MSec timeout)
 {
  SplitDevName split(dir_name);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::CreateDir(#.q;,...) : bad name",dir_name);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  dev.createDir(split.dev_path);
 }
  
void AsyncFileSystem::DeleteDir(StrLen dir_name,bool recursive,MSec timeout)
 {
  SplitDevName split(dir_name);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::DeleteDir(#.q;,...) : bad name",dir_name);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  dev.deleteDir(split.dev_path,recursive);
 }
  
void AsyncFileSystem::Rename(StrLen old_path,StrLen new_path,bool allow_overwrite,MSec timeout)
 {
  SplitDevName split_old(old_path);
  
  if( !split_old )
    {
     Printf(Exception,"CCore::AsyncFileSystem::Rename(#.q;,...) : bad name",old_path);
    }
    
  SplitDevName split_new(new_path);
  
  if( !split_new )
    {
     Printf(Exception,"CCore::AsyncFileSystem::Rename(,#.q;,...) : bad name",new_path);
    }
    
  if( !split_old.dev_name.equal(split_new.dev_name) )  
    {
     Printf(Exception,"CCore::AsyncFileSystem::Rename(#.q;,#.q;,...) : different devices",old_path,new_path);
    }
    
  AsyncFileSystem dev(split_old.dev_name,timeout); 
  
  dev.rename(split_old.dev_path,split_new.dev_path,allow_overwrite);
 }
  
void AsyncFileSystem::Remove(StrLen path,MSec timeout)
 {
  SplitDevName split(path);
  
  if( !split )
    {
     Printf(Exception,"CCore::AsyncFileSystem::Remove(#.q;,...) : bad name",path);
    }
    
  AsyncFileSystem dev(split.dev_name,timeout); 
  
  dev.remove(split.dev_path);
 }
  
void AsyncFileSystem::Exec(StrLen dir,StrLen program,StrLen arg,MSec timeout)
 {
  SplitDevName split_dir(dir);
  
  if( !split_dir )
    {
     Printf(Exception,"CCore::AsyncFileSystem::Exec(#.q;,...) : bad name",dir);
    }
    
  SplitDevName split_program(program);
  
  if( !split_program )
    {
     Printf(Exception,"CCore::AsyncFileSystem::Exec(,#.q;,...) : bad name",program);
    }
    
  if( !split_dir.dev_name.equal(split_program.dev_name) )  
    {
     Printf(Exception,"CCore::AsyncFileSystem::Exec(#.q;,#.q;,...) : different devices",dir,program);
    }
    
  AsyncFileSystem dev(split_dir.dev_name,timeout); 
  
  dev.exec(split_dir.dev_path,split_program.dev_path,arg);
 }
   
} // namespace CCore
 

