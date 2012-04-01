/* SysAsyncFileSystem.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysAsyncFileSystem.h>
 
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Sys {

/* struct AsyncFileSystem */ 

FileError AsyncFileSystem::init(StrLen dev_name)
 {
  state=new(storage.getPlace()) State(dev_name);
  
  dev=*state;
  
  if( !dev ) 
    {
     Replace_null(state)->~State();
     
     return FileError_NoDevice;
    }
  
  return FileError_Ok;
 }
  
void AsyncFileSystem::exit()
 {
  dev=0;
  
  Replace_null(state)->~State();
 }
  
void AsyncFileSystem::getFileType(Packet<uint8,FileTypeExt> packet,StrLen path)
 {
  dev->getFileType(packet,path);
 }
  
void AsyncFileSystem::getFileList(Packet<uint8,FileExt> packet,StrLen dir_name)
 {
  dev->getFileList(state->hook,packet,dir_name);
 }
  
void AsyncFileSystem::createFile(Packet<uint8,ErrorExt> packet,StrLen file_name)
 {
  dev->createFile(packet,file_name);
 }
  
void AsyncFileSystem::deleteFile(Packet<uint8,ErrorExt> packet,StrLen file_name)
 {
  dev->deleteFile(packet,file_name);
 }
  
void AsyncFileSystem::createDir(Packet<uint8,ErrorExt> packet,StrLen dir_name)
 {
  dev->createDir(packet,dir_name);
 }
  
void AsyncFileSystem::deleteDir(Packet<uint8,ErrorExt> packet,StrLen dir_name,bool recursive)
 {
  dev->deleteDir(packet,dir_name,recursive);
 }
  
void AsyncFileSystem::rename(Packet<uint8,ErrorExt> packet,StrLen old_path,StrLen new_path,bool allow_overwrite)
 {
  dev->rename(packet,old_path,new_path,allow_overwrite);
 }
  
void AsyncFileSystem::remove(Packet<uint8,ErrorExt> packet,StrLen path)
 {
  dev->remove(packet,path);
 }
  
void AsyncFileSystem::exec(Packet<uint8,ErrorExt> packet,StrLen dir,StrLen program,StrLen arg)
 {
  dev->exec(packet,dir,program,arg);
 }
  
void AsyncFileSystem::exec2(Packet<uint8,FileExt> packet,StrLen dir,StrLen program)
 {
  dev->exec2(state->hook,packet,dir,program);
 }
 
} // namespace Sys
} // namespace CCore
 

