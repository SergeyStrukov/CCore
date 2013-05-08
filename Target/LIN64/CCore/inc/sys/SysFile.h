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
 
  // public
  
  Result open(StrLen file_name,FileOpenFlags oflags) noexcept;
 
  void close(FileMultiError &errout,bool preserve_file=false) noexcept;
  
  void close() noexcept; 
   
  Result write(FilePosType off,const uint8 *buf,ulen len) noexcept; 
  
  FileError read(FilePosType off,uint8 *buf,ulen len) noexcept; 
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
 
  // public
  
  Result open(StrLen file_name,FileOpenFlags oflags) noexcept;
  
  void close(FileMultiError &errout,bool preserve_file=false) noexcept; 
  
  void close() noexcept; 
  
  FileError testRead(FilePosType off,ulen len) noexcept;
  
  Result setWrite(FilePosType off,ulen len) noexcept;
  
  RWResult startRead(Async async,FilePosType off,uint8 *buf,ulen len) noexcept;
  
  FileError completeRead(Async async,ulen len) noexcept;
  
  RWResult startWrite(Async async,FilePosType off,const uint8 *buf,ulen len) noexcept;
  
  FileError completeWrite(Async async,ulen len) noexcept;
 };

/* struct AsyncFileWait */

struct AsyncFileWait
 {
  // public
  
  static const ulen MaxAsyncs = 50 ;
  
  FileError init(ulen async_count) noexcept;
  
  void exit() noexcept;
  
  AltAsyncFile::Async getAsync(ulen index) noexcept;
  
  bool addWait(ulen index) noexcept;
  
  bool delWait(ulen index) noexcept;
  
  WaitResult wait(MSec timeout) noexcept;
  
  WaitResult wait(TimeScope time_scope) noexcept;
  
  void interrupt() noexcept; // async , semaphore
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

