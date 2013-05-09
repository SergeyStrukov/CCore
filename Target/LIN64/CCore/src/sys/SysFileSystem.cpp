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
  
auto FileSystem::getFileType(StrLen /*path*/) noexcept -> TypeResult
 {
  // TODO

  return TypeResult{};
 }
  
FileError FileSystem::createFile(StrLen /*file_name*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::deleteFile(StrLen /*file_name*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::createDir(StrLen /*dir_name*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::deleteDir(StrLen /*dir_name*/,bool /*recursive*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::rename(StrLen /*old_path*/,StrLen /*new_path*/,bool /*allow_overwrite*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
FileError FileSystem::remove(StrLen /*path*/) noexcept
 {
  // TODO

  return FileError_Ok;
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
 

