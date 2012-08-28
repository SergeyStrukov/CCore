/* testPrint.cpp */
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

#include <CCore/test/testPrint.h>

#include <CCore/inc/String.h>
#include <CCore/inc/Exception.h>

namespace App {

/* class PrintFile */

PrintFile::PrintFile()
 {
 }

PrintFile::PrintFile(StrLen file_name,FileOpenFlags oflags)
 {
  open(file_name,oflags);
 }

PrintFile::~PrintFile()
 {
 }

void PrintFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  String name=StringCat("host:",file_name);
  
  PrintAsyncFile::open(Range(name),oflags);
 }

/* class StreamFile */

 // constructors

StreamFile::StreamFile()
 {
 }
   
StreamFile::StreamFile(StrLen file_name,FileOpenFlags oflags) 
 {
  open(file_name,oflags);
 }
   
StreamFile::~StreamFile() 
 {
  flush();
 }
   
 // methods
   
void StreamFile::open(StrLen file_name,FileOpenFlags oflags) 
 {
  String name=StringCat("host:",file_name);
  
  FilePosType file_len=file.open(Range(name),oflags);  

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }
   
void StreamFile::soft_close(FileMultiError &errout) 
 {
  flush();
  
  file.soft_close(errout);
 }
   
void StreamFile::close() 
 {
  flush();
  
  file.close();
 }
   
 // put
   
void StreamFile::provide()
 {
  flush();
  
  auto result=file.getWritePacket();
  
  packet=result.packet;
 
  out=result.buf;
  buf_len=out.len;
 }

void StreamFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len); 
 
  while( +src )
    {
     if( !out ) provide();
    
     ulen delta=Min(src.len,out.len);
    
     (out+=delta).copy( (src+=delta).ptr );
    }
 }
   
PtrLen<uint8> StreamFile::do_putRange(ulen) 
 { 
  Printf(Exception,"StreamFile::do_putRange(...) : not supported");
  
  return Nothing;
 }
   
void StreamFile::flush() 
 {
  if( +packet )
    {
     ulen len=buf_len-out.len;
     
     out=Nothing;
    
     file.write(file_pos,len,Replace_null(packet));
  
     file_pos+=len;
    }
 }
   
} // namespace App

