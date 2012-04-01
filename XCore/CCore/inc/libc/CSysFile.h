/* CSysFile.h */ 
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

#ifndef CCore_inc_libc_CSysFile_h
#define CCore_inc_libc_CSysFile_h

#include <CCore/inc/libc/CStdFile.h>

namespace LibC_Internal {

/* classes */ 

//enum FileSystemResult;

struct FileSystem;

/* enum FileSystemResult */ 

enum FileSystemResult
 {
  FileSystemResult_Ok = 0,
  
  FileSystemResult_NoMemory,
  
  FileSystemResult_NoSuchFile,
  FileSystemResult_NoSuchPath,
  FileSystemResult_AccessDenied,
  
  FileSystemResult_NoFreeSpace,
  
  FileSystemResult_Fault
 };
 
/* struct FileSystem */ 

struct FileSystem
 {
  static FileSystemResult Remove(const char *file_name);
  
  static FileSystemResult Rename(const char *old_name,const char *new_name);
  
  static bool Exist(const char *file_name);
  
  static const char * TmpFileNamePattern(); // "???%u"

  static void AttachStdX();
  
  static RetFileOp<Size> ConRead(void *buf,Size buf_size);        // serialized 
  static RetFileOp<Size> ConWrite(const void *buf,Size buf_size); // serialized
   
  static void Stdin(IOFile &ret);
  static void Stdout(IOFile &ret);
  static void Stderr(IOFile &ret);
  
  static void DetachStdX();
  
  static FileSystemResult OpenTemp(IOFile &ret);
  static FileSystemResult Open(IOFile &ret,const char *file_name,unsigned access_flags);
 };
 
} // namespace LibC_Internal
 
#endif


