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

/* class BinaryFile */

BinaryFile::BinaryFile()
 {
 }
   
BinaryFile::BinaryFile(StrLen file_name,FileOpenFlags oflags)
 {
  open(file_name,oflags);
 }
   
BinaryFile::~BinaryFile()
 {
 }
   
void BinaryFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  String name=StringCat("host:",file_name);
  
  AsyncBinaryFile::open(Range(name),oflags);
 }
   
} // namespace App

