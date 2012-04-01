/* CSysFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/libc/CSysFile.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/AsyncFile.h>

#include <stdlib.h>

namespace LibC_Internal {

/* struct FileSystem */ 

using namespace CCore;

FileSystemResult FileSystem::Remove(const char *file_name)
 {
  SilentReportException report;
  
  try
    {
     AsyncFileSystem::Remove(file_name);
     
     return FileSystemResult_Ok;
    }
  catch(CatchType) {}
    
  return FileSystemResult_Fault;
 }
   
FileSystemResult FileSystem::Rename(const char *old_name,const char *new_name)
 {
  SilentReportException report;
  
  try
    {
     AsyncFileSystem::Rename(old_name,new_name,false);
     
     return FileSystemResult_Ok;
    }
  catch(CatchType) {}
    
  return FileSystemResult_Fault;
 }
   
bool FileSystem::Exist(const char *file_name)
 {
  SilentReportException report;
  
  try
    {
     return AsyncFileSystem::GetFileType(file_name)==FileType_file;
    }
  catch(CatchType) {}
    
  return false;
 }
   
const char * FileSystem::TmpFileNamePattern()
 {
  return "host:/tmp/tmpfile%u";
 }
 
static RetFileOp<Size> ConRead_(IOFile::Handle,void *buf,Size buf_size)
 {
  return FileSystem::ConRead(buf,buf_size);
 }
 
static RetFileOp<Size> ConWrite_(IOFile::Handle,const void *buf,Size buf_size)
 {
  return FileSystem::ConWrite(buf,buf_size);
 }
 
void FileSystem::Stdin(IOFile &ret)
 {
  ret.initNoOp();
  
  ret.do_read=ConRead_;
  ret.access_flags=Access_Read;
 }
  
void FileSystem::Stdout(IOFile &ret)
 {
  ret.initNoOp();
  
  ret.do_write=ConWrite_;
  ret.access_flags=Access_Write;
 }
  
void FileSystem::Stderr(IOFile &ret)
 {
  ret.initNoOp();
  
  ret.do_write=ConWrite_;
  ret.access_flags=Access_Write;
 }
   
FileSystemResult FileSystem::OpenTemp(IOFile &)
 {
  return FileSystemResult_NoFreeSpace;
 }
 
/* FileSystem::Open() */  

namespace Private_CSysFile {

/* class RWFile */

class RWFile : public MemBase_nocopy , public Funchor
 {
   Sys::AsyncFile file;
   
   PacketFormat write_format;
   ulen max_read_len;
   
   PacketSet<uint8> pset;
   MSec timeout;
   
   Mutex mutex;
   
   FileError error;
   FilePosType file_len;
   
   FilePosType file_pos;
   
  private: 
  
   void complete_open(PacketHeader *packet);
   
   PacketFunction function_complete_open() { return FunctionOf(this,&RWFile::complete_open); }
   
   void complete_close(PacketHeader *packet);
   
   PacketFunction function_complete_close() { return FunctionOf(this,&RWFile::complete_close); }
   
   void complete_write(PacketHeader *packet);
   
   PacketFunction function_complete_write() { return FunctionOf(this,&RWFile::complete_write); }
   
   void complete_read(PacketHeader *packet);
   
   PacketFunction function_complete_read() { return FunctionOf(this,&RWFile::complete_read); }
   
  public:
  
   RWFile() : pset("RWFile.pset"),timeout(DefaultTimeout),mutex("RWFile") {}
   
   ~RWFile() {}
   
   FileError open(StrLen file_name,FileOpenFlags open_flags);
   
   FileError close();
   
   struct PosResult
    {
     FilePosType pos;
     FileError error;
    };
   
   PosResult getPos();
   
   PosResult getLen();
   
   FileError setPos(FilePosType pos);
   
   struct IOResult
    {
     ulen len;
     FileError error;
    };
   
   IOResult write(const uint8 *buf,ulen len);
   
   IOResult read(uint8 *buf,ulen len);
 };
 
void RWFile::complete_open(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::OpenExt> packet=packet_;
  
  Sys::AsyncFile::OpenExt *ext=packet.getExt();
  
  error=ext->error;
  
  if( !error )
    {
     write_format=ext->write_format;
     max_read_len=ext->max_read_len;
     
     file_len=ext->file_len;
     
     file_pos=0;
    }  
  
  packet.popExt().complete();
 }
  
void RWFile::complete_close(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::CloseExt> packet=packet_;
  
  Sys::AsyncFile::CloseExt *ext=packet.getExt();
  
  error=ext->error;
  
  packet.popExt().complete();
 }
 
void RWFile::complete_write(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::WriteExt> packet=packet_;
  
  Sys::AsyncFile::WriteExt *ext=packet.getExt();
  
  if( ext->error )
    {
     Mutex::Lock lock(mutex);
     
     if( !error ) error=ext->error;
    }
  else
    {
     Mutex::Lock lock(mutex);

     Replace_max(file_len,ext->file_len);
    }  
  
  packet.popExt().complete();
 }
 
void RWFile::complete_read(PacketHeader *packet_)
 {
  Packet<uint8,Sys::AsyncFile::ReadExt> packet=packet_;
  
  Sys::AsyncFile::ReadExt *ext=packet.getExt();
  
  if( ext->error )
    {
     Mutex::Lock lock(mutex);
     
     if( !error ) error=ext->error;
    }
  
  packet.popExt().complete();
 }
   
FileError RWFile::open(StrLen file_name,FileOpenFlags open_flags)
 {
  TimeScope time_scope(timeout);
    
  Packet<uint8> packet=pset.get(time_scope); 
  
  if( !packet )
    {
     return FileError_SysOverload;
    }
    
  Packet<uint8,Sys::AsyncFile::OpenExt> packet2=packet.pushExt<Sys::AsyncFile::OpenExt>();  
  
  packet2.pushCompleteFunction(function_complete_open());
    
  file.open(packet2,file_name,open_flags);  
  
  pset.wait(time_scope);
  
  if( error ) file.closeState();
  
  return error;  
 }
   
FileError RWFile::close()
 {
  TimeScope time_scope(timeout);
    
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     file.closeState();
    
     return FileError_SysOverload;
    }
    
  Packet<uint8,Sys::AsyncFile::CloseExt> packet2=packet.pushExt<Sys::AsyncFile::CloseExt>(); 
  
  packet2.pushCompleteFunction(function_complete_close());
  
  file.close(packet2);
  
  pset.wait(time_scope);
  
  file.closeState();
  
  return error;
 }
   
RWFile::PosResult RWFile::getPos()
 {
  PosResult ret;
  
  ret.pos=file_pos;
  ret.error=error;
  
  return ret;
 }
   
RWFile::PosResult RWFile::getLen()
 {
  PosResult ret;
  
  ret.pos=file_len;
  ret.error=error;
  
  return ret;
 }
   
FileError RWFile::setPos(FilePosType pos)
 {
  if( error ) return error;
  
  file_pos=pos;
  
  return FileError_Ok;
 }
   
RWFile::IOResult RWFile::write(const uint8 *buf,ulen len)
 {
  IOResult ret;
  
  if( error )
    {
     ret.len=0;
     ret.error=error;
     
     return ret;
    }
  
  for(auto r=Range(buf,len); +r ;)
    {
     Packet<uint8> packet=pset.get(timeout);
  
     if( !packet ) 
       {
        pset.cancel_and_wait();
        
        error=FileError_SysOverload;
        
        ret.len=0;
        ret.error=error;
     
        return ret;
       }
       
     ulen max_len=packet.getMaxDataLen(write_format).len;  
     
     if( !max_len )
       {
        pset.cancel_and_wait();
        
        error=FileError_WriteFault;
        
        ret.len=0;
        ret.error=error;
     
        return ret;
       }
       
     auto frame=r.takeup(max_len);
     
     packet.setDataLen(write_format,frame.len).copy(frame.ptr);
     
     Packet<uint8,Sys::AsyncFile::WriteExt> packet2=packet.pushExt<Sys::AsyncFile::WriteExt>();  
     
     packet2.pushCompleteFunction(function_complete_write());
     
     file.write(packet2,file_pos);
     
     file_pos+=frame.len;
    }
    
  pset.wait(timeout);  
  
  if( error )
    {
     ret.len=0;
     ret.error=error;
    }
  else
    {
     ret.len=len;
     ret.error=FileError_Ok;
    }
  
  return ret;
 }
   
RWFile::IOResult RWFile::read(uint8 *buf,ulen len)
 {
  IOResult ret;
  
  if( error )
    {
     ret.len=0;
     ret.error=error;
     
     return ret;
    }
  
  if( file_pos>=file_len )
    {
     ret.len=0;
     ret.error=FileError_Ok;
     
     return ret;
    }
    
  FilePosType avail=file_len-file_pos; 
  
  if( len>avail ) len=(ulen)avail;
  
  if( !max_read_len )  
    {
     error=FileError_ReadFault;
    
     ret.len=0;
     ret.error=error;
     
     return ret;
    }
    
  for(auto r=Range(buf,len); +r ;)
    {
     auto frame=r.takeup(max_read_len);
     
     Packet<uint8> packet=pset.get(timeout);
  
     if( !packet ) 
       {
        pset.cancel_and_wait();
        
        error=FileError_SysOverload;
        
        ret.len=0;
        ret.error=error;
     
        return ret;
       }
       
     Packet<uint8,Sys::AsyncFile::ReadExt> packet2=packet.pushExt<Sys::AsyncFile::ReadExt>(file_pos,frame);  
     
     packet2.pushCompleteFunction(function_complete_read());
     
     file.read(packet2);
     
     file_pos+=frame.len;
    }
    
  pset.wait(timeout);  
  
  if( error )
    {
     ret.len=0;
     ret.error=error;
    }
  else
    {
     ret.len=len;
     ret.error=FileError_Ok;
    }
  
  return ret;
 }
   
} // namespace Private_CSysFile
 
using namespace Private_CSysFile;
 
static RWFile * GetSys(IOFile::Handle hfile) { return static_cast<RWFile *>(hfile.ptr_handle); }
 
static FileResult FileClose(IOFile::Handle hfile) 
 {
  RWFile *file=GetSys(hfile);
  FileResult ret;
  
  if( file->close() ) 
    ret=FileResult_CloseFault;
  else
    ret=FileResult_Ok;  
    
  delete file;  
    
  return ret;  
 }
 
static RetFileOp<FilePos> FileSize(IOFile::Handle hfile)
 {
  RWFile::PosResult result=GetSys(hfile)->getLen();
  
  if( result.error || result.pos>FilePos(-1) ) return FileResult_SizeFault;
  
  return FilePos(result.pos);
 }
 
static RetFileOp<FilePos> FileTell(IOFile::Handle hfile)
 {
  RWFile::PosResult result=GetSys(hfile)->getPos();
  
  if( result.error || result.pos>FilePos(-1) ) return FileResult_TellFault;
  
  return FilePos(result.pos);
 }
 
static FileResult FileSeek(IOFile::Handle hfile,FilePos pos)
 {
  if( GetSys(hfile)->setPos(pos) ) return FileResult_SeekFault;
  
  return FileResult_Ok;
 }
 
static RetFileOp<Size> FileRead(IOFile::Handle hfile,void *buf,Size buf_size)
 {
  RWFile *file=GetSys(hfile);
  
  RWFile::IOResult result=file->read(static_cast<uint8 *>(buf),buf_size);

  if( result.error ) return FileResult_ReadFault;
  
  return Size(result.len);
 }
 
static RetFileOp<Size> FileWrite(IOFile::Handle hfile,const void *buf,Size buf_size)
 {
  RWFile *file=GetSys(hfile);
 
  RWFile::IOResult result=file->write(static_cast<const uint8 *>(buf),buf_size);

  if( result.error ) return FileResult_WriteFault;
  
  return Size(result.len);
 }  
 
static FileOpenFlags make_flags(unsigned access_flags)
 {
  FileOpenFlags ret=FileOpenFlags(0);
  
  if( access_flags&Access_Read   ) ret=ret|Open_Read;
  if( access_flags&Access_Write  ) ret=ret|Open_Write;
  
  if( access_flags&Access_Erase  ) ret=ret|Open_Erase;
  if( !(access_flags&Access_Exist) ) ret=ret|Open_Create;
  
  return ret;
 }
 
static FileSystemResult map_error(FileError error)
 {
  switch( error )
    {
     case FileError_SysOverload : return FileSystemResult_NoMemory;
     case FileError_NoFile      : return FileSystemResult_NoSuchFile;
     case FileError_NoPath      : return FileSystemResult_NoSuchPath;
     case FileError_NoAccess    : return FileSystemResult_AccessDenied;
     case FileError_DiskFull    : return FileSystemResult_NoFreeSpace;
     
     default: return FileSystemResult_Fault;
    }
 }
 
FileSystemResult FileSystem::Open(IOFile &ret,const char *file_name,unsigned access_flags)
 {
  RWFile *file=new(JustTry) RWFile();
  
  if( !file ) return FileSystemResult_NoMemory;
  
  if( FileError error=file->open(file_name,make_flags(access_flags)) )
    {
     delete file;
     
     return map_error(error);
    }
    
  ret.handle.ptr_handle=file;  
  ret.access_flags=(access_flags&(Access_Read|Access_Write|Access_Append))|Access_Pos;
  
  ret.do_close=FileClose;
  ret.do_size=FileSize;
  ret.do_tell=FileTell;
  ret.do_seek=FileSeek;
  ret.do_read=FileRead;
  ret.do_write=FileWrite;
  
  return FileSystemResult_Ok;
 }
 
} // namespace LibC_Internal
 


