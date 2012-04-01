/* test1010.SysFile.cpp */ 
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

namespace App {

namespace Private_1010 {

/* class File */

class File : NoCopy
 {
   Sys::File file;
   bool ok;
 
  public:
  
   File() : ok(false) {}
  
   void open(StrLen file_name,FileOpenFlags oflags)
    {
     if( ok ) return;
    
     FileError fe=file.open(file_name,oflags);
     
     Printf(Con,"open(#.q;,#;) : #;\n",file_name,oflags,fe);
     
     ok=!fe;
    }
 
   void close(bool preserve_file=false)
    {
     if( !ok ) return;
     
     FileMultiError errout;
    
     file.close(errout,preserve_file);
     
     Printf(Con,"close(#;) : #;\n",preserve_file,errout);
     
     ok=false;
    }
  
   ulen write(const uint8 *buf,ulen len)
    {
     if( !ok ) return 0;
    
     auto result=file.write(buf,len);
     
     Printf(Con,"write(,#;) : #; #;\n",len,result.error,result.len);
     
     return result.len;
    }
  
   ulen read(uint8 *buf,ulen len)
    {
     if( !ok ) return 0;
    
     auto result=file.read(buf,len);
     
     Printf(Con,"read(,#;) : #; #;\n",len,result.error,result.len);
     
     return result.len;
    }
  
   FilePosType getLen()
    {
     if( !ok ) return 0;
    
     auto result=file.getLen();
     
     Printf(Con,"getLen() : #; #;\n",result.error,result.pos);
     
     return result.pos;
    }
  
   FilePosType getPos()
    {
     if( !ok ) return 0;
    
     auto result=file.getPos();
     
     Printf(Con,"getPos() : #; #;\n",result.error,result.pos);
     
     return result.pos;
    }
  
   void setPos(FilePosType pos)
    {
     if( !ok ) return;
    
     FileError fe=file.setPos(pos);
     
     Printf(Con,"setPos(#;) : #;\n",pos,fe);
    }
 };

/* test1() */

void test1()
 {
  File file;
  
  // 1
  
  file.open("not_exist.txt",Open_Read);
  
  file.open("z:not_exist.txt",Open_Read);
  
  file.open("no_write.txt",Open_Write);
  
  file.open("no_write.txt",Open_Read);
  
  file.close();
  
  // 2
  
  file.open("no_read.txt",Open_Read);
  
  file.open("no_read.txt",Open_Write);
  
  file.close();
  
  // 3
  
  file.open("temp.txt",Open_Write|Open_AutoDelete|Open_New);
  
  file.close();
  
  file.open("temp.txt",Open_Write|Open_AutoDelete);
  
  file.close();
  
  file.open("temp.txt",Open_Write|Open_AutoDelete|Open_Create|Open_Pos);
  
  file.getLen();
  
  file.close();
  
  file.open("temp.txt",Open_Write|Open_AutoDelete|Open_Erase);
  
  file.close();
  
  file.open("temp.txt",Open_Write|Open_AutoDelete|Open_Create|Open_Erase|Open_Pos);
  
  file.getLen();
  
  file.close();
  
  // 4
  
  const ulen Len = 100 ;
  
  uint8 buf[Len];
  
  Range(buf).set('1');
  
  // 5
  
  file.open("temp_saved.txt",Open_Write|Open_New);
  
  file.close();
  
  file.open("temp_saved.txt",Open_Write|Open_Pos);
  
  file.write(buf,Len);
  
  file.getLen();
  
  file.close();
  
  file.open("temp_saved.txt",Open_Write|Open_Create|Open_Pos);
  
  file.getLen();
  
  file.close();
  
  file.open("temp_saved.txt",Open_Write|Open_Erase|Open_Pos);
  
  file.getLen();
  
  file.write(buf,DimOf(buf));
  
  file.close();
  
  file.open("temp_saved.txt",Open_Write|Open_AutoDelete|Open_Create|Open_Erase|Open_Pos);
  
  file.getLen();
  
  file.close(true);
 }

/* test2() */

void test2()
 {
  const ulen WLen = 100 ;
  const ulen RLen = 200 ;
 
  uint8 wbuf[WLen];
  uint8 rbuf[RLen];
  
  Range(wbuf).set('1');
  
  // file
  
  File file;
  
  file.open("temp.txt",Open_AutoDelete);
  
  file.close();
  
  file.open("temp.txt",Open_Create|Open_Write);
  
  file.write(wbuf,WLen);
  file.read(rbuf,RLen);
  file.setPos(WLen/2);
  
  file.close();
  
  file.open("temp.txt",Open_Read);
  
  file.read(rbuf,RLen);
  
  if( !Range(wbuf).equal(Range(rbuf,WLen)) ) Printf(Con,"not equal\n");
  
  file.close();
 } 

/* test3() */

void test3()
 {
  const ulen WLen = 100 ;
  uint8 wbuf[WLen];
  
  Range(wbuf).set('1');
  
  // file
  
  File file;
  
  file.open("temp.txt",Open_ToWrite|Open_Pos|Open_AutoDelete);
  
  file.write(wbuf,WLen);
  
  file.getLen();
  
  file.setPos(WLen/2);
  file.getPos();
  
  file.setPos(WLen);
  file.getPos();
  
  file.setPos(0);
  file.getPos();
  
  file.close();
 } 
 
} // namespace Private_1010
 
using namespace Private_1010; 
 
/* Testit<1010> */ 

template<>
const char *const Testit<1010>::Name="Test1010 SysFile";

template<>
bool Testit<1010>::Main() 
 { 
  test1();
  test2();
  test3();
  
  return true;
 }
 
} // namespace App
 
