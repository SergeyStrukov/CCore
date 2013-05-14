/* SysFileSystem.cpp */ 
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
 
#include <CCore/inc/sys/SysFileSystem.h>
 
#include <CCore/inc/sys/SysInternal.h>

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

namespace CCore {
namespace Sys {

/* struct FileSystem::DirCursor */ 

void FileSystem::DirCursor::init(FileSystem * /*fs*/,StrLen /*dir_name*/) noexcept
 {
  // TODO
 }
  
void FileSystem::DirCursor::exit() noexcept
 {
  // TODO
 }
    
bool FileSystem::DirCursor::next() noexcept
 {
  // TODO

  return false;
 }
 
/* struct FileSystem */ 

FileError FileSystem::init() noexcept
 {
  return FileError_Ok;
 }
  
FileError FileSystem::exit() noexcept
 {
  return FileError_Ok;
 }
  
auto FileSystem::getFileType(StrLen path) noexcept -> TypeResult
 {
  FileName file_name;
  
  if( !file_name.set(path) ) return {FileType_none,FileError_TooLongPath};

  struct stat result;
  
  if( stat(file_name,&result)==-1 ) 
    {
     int error=errno;
     
     if( error==ENOENT || error==ENOTDIR ) return {FileType_none,FileError_Ok};
    
     return {FileType_none,MakeError(FileError_OpFault,error)};
    }

  return {(S_ISDIR(result.st_mode))?FileType_dir:FileType_file,FileError_Ok};
 }
  
FileError FileSystem::createFile(StrLen file_name_) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(file_name_) ) return FileError_TooLongPath;
  
  int flags=O_RDWR|O_CREAT|O_EXCL;
  int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
  
  int handle=open(file_name,flags,mode);
  
  if( handle==-1 ) return MakeError(FileError_OpenFault);
  
  close(handle);

  return FileError_Ok;
 }
  
FileError FileSystem::deleteFile(StrLen file_name_) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(file_name_) ) return FileError_TooLongPath;
  
  if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::createDir(StrLen dir_name) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(dir_name) ) return FileError_TooLongPath;
  
  int mode=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
  
  if( mkdir(file_name,mode)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::deleteDir(StrLen dir_name,bool recursive) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(dir_name) ) return FileError_TooLongPath;
  
  if( recursive ) return FileError_NoMethod; // TODO

  if( rmdir(file_name)==-1 ) return MakeError(FileError_OpFault);

  return FileError_Ok;
 }
  
FileError FileSystem::rename(StrLen /*old_path*/,StrLen /*new_path*/,bool /*allow_overwrite*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::remove(StrLen path) noexcept
 {
  FileName file_name;
  
  if( !file_name.set(path) ) return FileError_TooLongPath;

  struct stat result;
  
  if( stat(file_name,&result)==-1 ) 
    {
     int error=errno;
     
     if( error==ENOENT || error==ENOTDIR ) return FileError_NoPath;
    
     return MakeError(FileError_OpFault,error);
    }

  if( S_ISDIR(result.st_mode) )
    {
     if( rmdir(file_name)==-1 ) return MakeError(FileError_OpFault);
     
     return FileError_Ok;
    }
  else
    {
     if( unlink(file_name)==-1 ) return MakeError(FileError_OpFault);
     
     return FileError_Ok;
    }
 }
 
FileError FileSystem::exec(StrLen /*dir*/,StrLen /*program*/,StrLen /*arg*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
 
auto FileSystem::pathOf(StrLen /*path*/,char /*buf*/[MaxPathLen+1]) noexcept -> PathOfResult
 {
  // TODO

  return PathOfResult{};
 }

} // namespace Sys
} // namespace CCore
 

