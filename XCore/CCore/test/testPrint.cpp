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

StreamFile::StreamFile() {}
   
StreamFile::StreamFile(StrLen,FileOpenFlags) {}
   
StreamFile::~StreamFile() {}
   
 // methods
   
bool StreamFile::isOpened() const { return false; }
   
void StreamFile::open(StrLen,FileOpenFlags) {}
   
void StreamFile::disableExceptions() {} 
   
void StreamFile::soft_close(FileMultiError &) {}
   
void StreamFile::close() {}
   
void StreamFile::preserveFile() {}
   
 // put
   
void StreamFile::do_put(uint8) {}
   
void StreamFile::do_put(const uint8 *,ulen) {}
   
PtrLen<uint8> StreamFile::do_putRange(ulen) { return Nothing; }
   
void StreamFile::flush() {}
   
} // namespace App

