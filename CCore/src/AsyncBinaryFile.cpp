/* AsyncBinaryFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/AsyncBinaryFile.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* class AsyncBinaryFile */

void AsyncBinaryFile::provide()
 {
  flush();
  
  auto result=file.getWritePacket();
  
  packet=result.packet;
 
  out=result.buf;
  buf_len=out.len;
 }

AsyncBinaryFile::AsyncBinaryFile()
 {
 }
   
AsyncBinaryFile::AsyncBinaryFile(StrLen file_name,FileOpenFlags oflags) 
 {
  open(file_name,oflags);
 }
   
AsyncBinaryFile::~AsyncBinaryFile() 
 {
  flush();
 }
   
void AsyncBinaryFile::open(StrLen file_name,FileOpenFlags oflags) 
 {
  FilePosType file_len=file.open(file_name,oflags);  

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }
   
void AsyncBinaryFile::soft_close(FileMultiError &errout) 
 {
  flush();
  
  file.soft_close(errout);
 }
   
void AsyncBinaryFile::close() 
 {
  flush();
  
  file.close();
 }

void AsyncBinaryFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len); 
 
  while( +src )
    {
     if( !out ) provide();
    
     ulen delta=Min(src.len,out.len);
    
     (out+=delta).copy( (src+=delta).ptr );
    }
 }
   
PtrLen<uint8> AsyncBinaryFile::do_putRange(ulen) 
 { 
  Printf(Exception,"AsyncBinaryFile::do_putRange(...) : not supported");
  
  return Nothing;
 }
   
void AsyncBinaryFile::flush() 
 {
  if( +packet )
    {
     ulen len=buf_len-out.len;
     
     out=Nothing;
    
     file.write(file_pos,len,Replace_null(packet));
  
     file_pos+=len;
    }
 }

} // namespace CCore
 

