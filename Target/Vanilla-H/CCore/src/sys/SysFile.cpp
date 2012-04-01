/* SysFile.cpp */ 
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
 
#include <CCore/inc/sys/SysFile.h>

namespace CCore {
namespace Sys {

/* struct File */ 

FileError File::open(StrLen /*file_name*/,FileOpenFlags /*oflags*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
 
void File::close(FileMultiError & /*errout*/,bool /*preserve_file*/) noexcept
 {
  // TODO
 }
  
void File::close() noexcept
 {
  FileMultiError errout;

  close(errout);
 }
   
auto File::write(const uint8 * /*buf*/,ulen /*len*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }
  
auto File::read(uint8 * /*buf*/,ulen /*len*/) noexcept -> IOResult
 {
  // TODO

  return IOResult{};
 }
  
auto File::getLen() noexcept -> PosResult
 {
  // TODO

  return PosResult{};
 }
  
auto File::getPos() noexcept -> PosResult
 {
  // TODO

  return PosResult{};
 }
  
FileError File::setPos(FilePosType /*pos*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }

/* struct AltFile */ 

auto AltFile::open(StrLen /*file_name*/,FileOpenFlags /*oflags*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
 
void AltFile::close(FileMultiError & /*errout*/,bool /*preserve_file*/) noexcept
 {
  // TODO
 }
  
void AltFile::close() noexcept
 {
  FileMultiError errout;

  close(errout);
 }
   
auto AltFile::write(FilePosType /*off*/,const uint8 * /*buf*/,ulen /*len*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
  
FileError AltFile::read(FilePosType /*off*/,uint8 * /*buf*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }

/* struct AltAsyncFile */

auto AltAsyncFile::open(StrLen /*file_name*/,FileOpenFlags /*oflags*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
  
void AltAsyncFile::close(FileMultiError & /*errout*/,bool /*preserve_file*/) noexcept
 {
  // TODO
 }
  
void AltAsyncFile::close() noexcept
 {
  FileMultiError errout;

  close(errout);
 }
  
FileError AltAsyncFile::testRead(FilePosType /*off*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
auto AltAsyncFile::setWrite(FilePosType /*off*/,ulen /*len*/) noexcept -> Result
 {
  // TODO

  return Result{};
 }
  
auto AltAsyncFile::startRead(Async /*async*/,FilePosType /*off*/,uint8 * /*buf*/,ulen /*len*/) noexcept -> RWResult
 {
  // TODO

  return RWResult{};
 }
  
FileError AltAsyncFile::completeRead(Async /*async*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
auto AltAsyncFile::startWrite(Async /*async*/,FilePosType /*off*/,const uint8 * /*buf*/,ulen /*len*/) noexcept -> RWResult
 {
  // TODO

  return RWResult{};
 }
  
FileError AltAsyncFile::completeWrite(Async /*async*/,ulen /*len*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }

/* struct AsyncFileWait */

FileError AsyncFileWait::init(ulen /*async_count*/) noexcept
 {
  // TODO

  return FileError_Ok;
 }
  
void AsyncFileWait::exit() noexcept
 {
  // TODO
 }
  
AltAsyncFile::Async AsyncFileWait::getAsync(ulen /*index*/) noexcept
 {
  // TODO

  return 0;
 }
  
bool AsyncFileWait::addWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
bool AsyncFileWait::delWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
WaitResult AsyncFileWait::wait(MSec /*timeout*/) noexcept
 {
  // TODO

  return Wait_error; 
 }
  
WaitResult AsyncFileWait::wait(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return Wait_error; 
 }
  
void AsyncFileWait::interrupt() noexcept
 {
  // TODO
 }

} // namespace Sys
} // namespace CCore
 

