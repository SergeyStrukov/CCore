/* SysFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
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
  
  typedef int Type;
  
  Type handle;
  FileOpenFlags oflags;
  char *to_unlink;
  
  // private
  
  struct OpenType
   {
    Type handle;
    char *to_unlink;
    FileError error;
   };
 
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;

  static void Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept;
  
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
    to_unlink=result.to_unlink;
    oflags=oflags_;
    
    return result.error;
   }
 
  void close(FileMultiError &errout,bool preserve_file=false)
   { 
    Close(errout,handle,oflags,to_unlink,preserve_file); 
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
  
  typedef int Type;
  
  Type handle;
  FilePosType file_len;
  FileOpenFlags oflags;
  char *to_unlink;
  
  // private
  
  struct OpenType
   {
    Type handle;
    FilePosType file_len;
    char *to_unlink;
    FileError error;
   };
  
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;
  
  static void Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept;
  
  static FileError Write(Type handle,FileOpenFlags oflags,FilePosType off,const uint8 *buf,ulen len) noexcept;
  
  static FileError Read(Type handle,FileOpenFlags oflags,FilePosType off,uint8 *buf,ulen len) noexcept;
 
  // public
  
  Result open(StrLen file_name,FileOpenFlags oflags_)
   {
    OpenType result=Open(file_name,oflags_);
   
    handle=result.handle;
    file_len=result.file_len;
    to_unlink=result.to_unlink;
    oflags=oflags_;
   
    return {result.file_len,result.error};
   }
 
  void close(FileMultiError &errout,bool preserve_file=false)
   { 
    Close(errout,handle,oflags,to_unlink,preserve_file); 
   }
  
  void close()
   { 
    FileMultiError errout;
   
    close(errout);
   }
   
  Result write(FilePosType off,const uint8 *buf,ulen len) 
   { 
    if( len>FilePosType(-1)-off ) return {0,FileError_BadPosition};
    
    FileError fe=Write(handle,oflags,off,buf,len);
    
    if( fe )
      {
       return {0,fe};
      }
    else
      {
       Replace_max(file_len,off+len);
      
       return {file_len,fe};
      }
   } 
  
  FileError read(FilePosType off,uint8 *buf,ulen len) 
   {
    if( off>file_len || len>file_len-off ) return FileError_BadPosition;
    
    return Read(handle,oflags,off,buf,len); 
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
  
  typedef int Type;
  
  Type handle;
  FilePosType file_len;
  FileOpenFlags oflags;
  char *to_unlink;
  
  // private
  
  struct OpenType
   {
    Type handle;
    FilePosType file_len;
    char *to_unlink;
    FileError error;
   };
  
  static OpenType Open(StrLen file_name,FileOpenFlags oflags) noexcept;
  
  static void Close(FileMultiError &errout,Type handle,FileOpenFlags oflags,char *to_unlink,bool preserve_file) noexcept;
  
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
    to_unlink=result.to_unlink;
    oflags=oflags_;
  
    return {result.file_len,result.error};
   }
  
  void close(FileMultiError &errout,bool preserve_file=false)
   {
    Close(errout,handle,oflags,to_unlink,preserve_file);
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
    if( !(oflags&Open_Write) ) return {0,FileError_NoMethod}; 
    
    if( len>FilePosType(-1)-off ) return {0,FileError_BadPosition}; 
    
    Replace_max(file_len,off+len);
    
    return {file_len,FileError_Ok};
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
 

