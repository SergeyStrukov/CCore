/* SysFile.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-H
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
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
 
  // public
  
  FileError open(StrLen file_name,FileOpenFlags oflags) noexcept;
 
  void close(FileMultiError &errout,bool preserve_file=false) noexcept;
  
  void close() noexcept; 
   
  IOResult write(const uint8 *buf,ulen len) noexcept;
  
  IOResult read(uint8 *buf,ulen len) noexcept;
  
  PosResult getLen() noexcept;
  
  PosResult getPos() noexcept;
  
  FileError setPos(FilePosType pos) noexcept;
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
  
  static const ulen MaxRWLen = 1_MByte ;
  
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
 

