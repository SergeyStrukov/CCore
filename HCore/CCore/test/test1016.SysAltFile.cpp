/* test1016.SysAltFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/sys/SysFile.h>

#include <CCore/inc/Array.h>

namespace App {

namespace Private_1016 {

/* class File */

class File : NoCopy
 {
   Sys::AltFile file;
   
  public:
   
   File(StrLen file_name,FileOpenFlags oflags)
    {
     auto result=file.open(file_name,oflags);
     
     if( result.error )
       {
        Printf(Exception,"open() : #;",result.error);
       }
     
     Printf(Con,"file_len = #;\n",result.file_len);
    }
   
   ~File()
    {
     FileMultiError errout;
     
     file.close(errout);
     
     if( +errout )
       {
        Printf(NoException,"close() : #;",errout);
       }
    }
   
   void testRead(FilePosType off,ulen len)
    {
     SimpleArray<uint8> buf(len);
     
     FileError fe=file.read(off,buf.getPtr(),buf.getLen());
     
     Printf(Con,"read(#;,#;) : #;\n",off,len,fe);
    }
   
   void testWrite(FilePosType off,ulen len,uint8 fill)
    {
     SimpleArray<uint8> buf(len);
     
     Range(buf).set(fill);
     
     auto result=file.write(off,buf.getPtr(),buf.getLen());
     
     Printf(Con,"write(#;,#;) : #; #;\n",off,len,result.error,result.file_len);
    }
 };

} // namespace Private_1016
 
using namespace Private_1016; 
 
/* Testit<1016> */ 

template<>
const char *const Testit<1016>::Name="Test1016 SysAltFile";

template<>
bool Testit<1016>::Main() 
 { 
  // 1
  {
   File file("../../../HCore/files/NameList.txt",Open_Read);
   
   file.testRead(0,100);
   
   file.testRead(0,1_MByte);
   
   file.testRead(0,4_MByte);
   
   file.testRead(0,20_MByte);
   
   file.testRead(0,40_MByte);
   
   file.testRead(40_MByte,100);
  }
  
  // 2
  {
   File file("temp.txt",Open_ToWrite);
 
   file.testWrite(100,20_MByte,'1');
   
   file.testWrite(0,100,'2');
  }
  
  // 3
  {
   File file("temp1.txt",Open_ToWrite);
 
   file.testWrite(100,100,'1');
   
   file.testWrite(0,100,'2');
   
   file.testWrite(150,100,'3');
  }
  
  return true;
 }
 
} // namespace App
 
