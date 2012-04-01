/* SysAsyncFile.cpp */ 
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
 
#include <CCore/inc/sys/SysAsyncFile.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Path.h>
 
namespace CCore {
namespace Sys {

/* struct AsyncFile */ 

void AsyncFile::open(Packet<uint8,OpenExt> packet,StrLen file_name,FileOpenFlags oflags_)
 {
  file_state=0;
  oflags=oflags_;
  
  SplitDevName split(file_name);
  
  if( !split )
    {
     packet.getExt()->setError(FileError_BadName);
     
     packet.complete();
    
     return;
    }
  
  ObjHook hook(JustTry,split.dev_name);
  
  AsyncFileDevice *dev=hook.cast<AsyncFileDevice>();
     
  if( !dev )
    {
     packet.getExt()->setError(FileError_NoDevice);
    
     packet.complete();
     
     return;
    }
     
  file_state=dev->createState(hook);
  
  if( !file_state )
    {
     packet.getExt()->setError(FileError_SysOverload);
    
     packet.complete();
     
     return;
    }
  
  auto ext=packet.getExt();
     
  ext->write_format=file_state->getWriteFormat();
  ext->max_read_len=file_state->getMaxReadLen();
     
  file_state->open(packet,split.dev_path,oflags_);  
 }
 
void AsyncFile::close(Packet<uint8,CloseExt> packet,bool preserve_file)
 {
  file_state->close(packet,preserve_file);
 }
  
void AsyncFile::closeState()
 {
  delete Replace_null(file_state);
 }
  
void AsyncFile::write(Packet<uint8,WriteExt> packet,FilePosType off)
 {
  if( oflags&Open_Write )
    {
     file_state->write(packet,off);
    }
  else
    {
     packet.getExt()->setError(FileError_NoMethod);
     
     packet.complete();
    }
 }
 
void AsyncFile::read(Packet<uint8,ReadExt> packet)
 {
  if( oflags&Open_Read )
    {
     file_state->read(packet);
    }
  else
    {
     packet.getExt()->setError(FileError_NoMethod);
     
     packet.complete();
    }
 }
 
void AsyncFile::read(Packet<uint8,ReadBufExt> packet)
 {
  if( oflags&Open_Read )
    {
     file_state->read(packet);
    }
  else
    {
     packet.getExt()->setError(FileError_NoMethod);
     
     packet.complete();
    }
 }
 
} // namespace Sys
} // namespace CCore
 

