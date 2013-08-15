/* SysFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysFile_h
#define CCore_inc_sys_SysFile_h

#include <CCore/inc/sys/SysWait.h>
 
#include <CCore/inc/PlanInit.h>
#include <CCore/inc/TimeScope.h>
#include <CCore/inc/GenFile.h>

namespace CCore {
namespace Sys {

/* classes */ 

struct File;

struct AltFile;

struct AltAsyncFile;

struct AsyncFileWait;

/* struct File */ 

struct File
 {
  // public
  
  struct IOResult
   {
    ulen len;
    FileError error;
   };
 
  struct PosResult
   {
    FilePosType pos;
    FileError error;
   };
 
  // private data
  
  typedef long Type;
  
  Type handle;
  FileOpenFlags oflags;
  
  // private
  
  struct OpenType
   {
    Type handle;
    FileError error;
   };
 
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;

  static void Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,bool preserve_file) noexcept;
  
  static IOResult Write(Type handle,FileOpenFlags oflags,const uint8 *buf,ulen len) noexcept;
  
  static IOResult Read(Type handle,FileOpenFlags oflags,uint8 *buf,ulen len) noexcept;
  
  static PosResult GetLen(Type handle,FileOpenFlags oflags) noexcept;
  
  static PosResult GetPos(Type handle,FileOpenFlags oflags) noexcept;
  
  static FileError SetPos(Type handle,FileOpenFlags oflags,FilePosType pos) noexcept;
  
  // public
  
  FileError open(StrLen file_name,FileOpenFlags oflags_)
   {
    OpenType result=Open(file_name,oflags_);
    
    handle=result.handle;
    oflags=oflags_;
    
    return result.error;
   }
 
  void close(FileMultiError &errout,bool preserve_file=false) 
   { 
    Close(errout,handle,oflags,preserve_file); 
   }
  
  void close() 
   { 
    FileMultiError errout;
   
    close(errout);
   }
   
  IOResult write(const uint8 *buf,ulen len) { return Write(handle,oflags,buf,len); }
  
  IOResult read(uint8 *buf,ulen len) { return Read(handle,oflags,buf,len); }
  
  PosResult getLen() { return GetLen(handle,oflags); }
  
  PosResult getPos() { return GetPos(handle,oflags); }
  
  FileError setPos(FilePosType pos) { return SetPos(handle,oflags,pos); }
 };
 
/* struct AltFile */ 

struct AltFile
 {
  // public
  
  struct Result
   {
    FilePosType file_len;
    FileError error;
   };
 
  // private data
  
  typedef long Type;
  typedef long EventType;
  
  Type handle;
  EventType h_event;
  FilePosType file_len;
  FileOpenFlags oflags;
  
  // private
  
  struct OpenType
   {
    Type handle;
    EventType h_event;
    FilePosType file_len;
    FileError error;
   };
 
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;

  static void Close(FileMultiError &errout,Type handle,EventType h_event,FileOpenFlags oflags,bool preserve_file) noexcept;
  
  static FileError ShortWrite(Type handle,EventType h_event,FilePosType off,const uint8 *buf,unsigned len) noexcept;
  
  static FileError ShortRead(Type handle,EventType h_event,FilePosType off,uint8 *buf,unsigned len) noexcept;
  
  static FileError Write(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,const uint8 *buf,ulen len) noexcept;
  
  static FileError Read(Type handle,EventType h_event,FileOpenFlags oflags,FilePosType off,uint8 *buf,ulen len) noexcept;
  
  // public
  
  Result open(StrLen file_name,FileOpenFlags oflags_)
   {
    OpenType result=Open(file_name,oflags_);
    
    handle=result.handle;
    h_event=result.h_event;
    file_len=result.file_len;
    oflags=oflags_;
    
    Result ret;
    
    ret.file_len=result.file_len;
    ret.error=result.error;
    
    return ret;
   }
 
  void close(FileMultiError &errout,bool preserve_file=false) 
   { 
    Close(errout,handle,h_event,oflags,preserve_file); 
   }
  
  void close() 
   { 
    FileMultiError errout;
   
    close(errout);
   }
   
  Result write(FilePosType off,const uint8 *buf,ulen len) 
   { 
    FileError fe=Write(handle,h_event,oflags,off,buf,len);
    
    Result ret;
    
    ret.error=fe;
    
    if( fe )
      {
       ret.file_len=0;
      }
    else
      {
       Replace_max(file_len,off+len);
       
       ret.file_len=file_len;
      }
    
    return ret; 
   }
  
  FileError read(FilePosType off,uint8 *buf,ulen len) 
   { 
    return Read(handle,h_event,oflags,off,buf,len); 
   }
 };

/* struct AltAsyncFile */

struct AltAsyncFile
 {
  // public
  
  struct AsyncState;
  
  typedef AsyncState * Async;
  
  struct Result
   {
    FilePosType file_len;
    FileError error;
   };
  
  struct RWResult
   {
    bool pending;
    FileError error;
   };
 
  // private data
  
  typedef long Type;
  
  Type handle;
  FilePosType file_len;
  FileOpenFlags oflags;
  
  // private
  
  struct OpenType
   {
    Type handle;
    FilePosType file_len;
    FileError error;
   };
 
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;

  static void Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,bool preserve_file) noexcept;
  
  static RWResult StartRead(Type handle,Async async,FilePosType off,uint8 *buf,ulen len) noexcept;
  
  static FileError CompleteRead(Type handle,Async async,ulen len) noexcept;
  
  static RWResult StartWrite(Type handle,Async async,FilePosType off,const uint8 *buf,ulen len) noexcept;
  
  static FileError CompleteWrite(Type handle,Async async,ulen len) noexcept;
  
  // public
  
  static const ulen MaxRWLen = 1_MByte ;
  
  Result open(StrLen file_name,FileOpenFlags oflags_)
   {
    OpenType result=Open(file_name,oflags_);
    
    handle=result.handle;
    file_len=result.file_len;
    oflags=oflags_;
    
    Result ret;
    
    ret.file_len=result.file_len;
    ret.error=result.error;
    
    return ret;
   }
  
  void close(FileMultiError &errout,bool preserve_file=false) 
   { 
    Close(errout,handle,oflags,preserve_file); 
   }
  
  void close() 
   { 
    FileMultiError errout;
   
    close(errout);
   }
  
  FileError testRead(FilePosType off,ulen len)
   {
    if( !(oflags&Open_Read) ) return FileError_NoMethod;
    
    if( off>file_len || len>file_len-off ) return FileError_BadPosition;
    
    return FileError_Ok;
   }
  
  Result setWrite(FilePosType off,ulen len)
   {
    Result ret;
    
    if( !(oflags&Open_Write) ) 
      {
       ret.file_len=0;
       ret.error=FileError_NoMethod;
       
       return ret;
      }
    
    if( len>FilePosType(-1)-off ) 
      {
       ret.file_len=0;
       ret.error=FileError_BadPosition;
       
       return ret;
      }
    
    Replace_max(file_len,off+len);
    
    ret.file_len=file_len;
    ret.error=FileError_Ok;
    
    return ret;
   }
  
  RWResult startRead(Async async,FilePosType off,uint8 *buf,ulen len)
   {
    return StartRead(handle,async,off,buf,len);
   }
  
  FileError completeRead(Async async,ulen len)
   {
    return CompleteRead(handle,async,len);
   }
  
  RWResult startWrite(Async async,FilePosType off,const uint8 *buf,ulen len)
   {
    return StartWrite(handle,async,off,buf,len); 
   }
  
  FileError completeWrite(Async async,ulen len)
   {
    return CompleteWrite(handle,async,len);
   }
 };

/* struct AsyncFileWait */

struct AsyncFileWait
 {
  // private
  
  class Engine;
  
  Engine *obj;
  AltAsyncFile::Async *asyncs;
  
  // public
  
  static const ulen MaxAsyncs = 50 ;
  
  FileError init(ulen async_count) noexcept;
  
  void exit() noexcept;
  
  AltAsyncFile::Async getAsync(ulen index) { return asyncs[index]; }
  
  bool addWait(ulen index) noexcept;
  
  bool delWait(ulen index) noexcept;
  
  WaitResult wait(MSec timeout) noexcept;
  
  WaitResult wait(TimeScope time_scope)
   {
    auto timeout=time_scope.get();
    
    if( !timeout ) return Wait_timeout;
    
    return wait(timeout);
   }
  
  void interrupt() noexcept; // async , semaphore
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

