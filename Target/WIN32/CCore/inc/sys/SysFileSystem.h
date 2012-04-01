/* SysFileSystem.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysFileSystem_h
#define CCore_inc_sys_SysFileSystem_h
 
#include <CCore/inc/GenFile.h>

namespace CCore {
namespace Sys {

/* classes */ 

struct FileSystem;

/* struct FileSystem */ 

struct FileSystem
 {
  // public
  
  struct TypeResult
   {
    FileType type;
    FileError error;
   };
  
  struct PathOfResult
   {
    StrLen path;
    FileError error;
   };
   
  struct DirCursor 
   {
    // private data
  
    typedef int Type;
  
    Type handle;
    bool is_first;
    bool is_closed;
  
    // public
   
    char file_name[MaxPathLen]; // file name only
    ulen len;
    FileType type;
    FileError error;
    
    void init(FileSystem *fs,StrLen dir_name) noexcept;
  
    void exit() noexcept;
    
    bool next() noexcept;
   };
 
  // public
  
  static FileError init() noexcept;
  
  static FileError exit() noexcept;
  
  static TypeResult getFileType(StrLen path) noexcept;
  
  static FileError createFile(StrLen file_name) noexcept;
  
  static FileError deleteFile(StrLen file_name) noexcept;
  
  static FileError createDir(StrLen dir_name) noexcept;
  
  static FileError deleteDir(StrLen dir_name,bool recursive) noexcept;
  
  static FileError rename(StrLen old_path,StrLen new_path,bool allow_overwrite) noexcept;
  
  static FileError remove(StrLen path) noexcept;
  
  static FileError exec(StrLen dir,StrLen program,StrLen arg) noexcept;
  
  static PathOfResult pathOf(StrLen path,char buf[MaxPathLen+1]) noexcept;
 };
 
} // namespace Sys
} // namespace CCore
 
#endif
 

