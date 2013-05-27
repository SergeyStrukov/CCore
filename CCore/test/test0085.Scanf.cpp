/* test0085.Scanf.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scanf.h>

namespace App {

namespace Private_0085 {

/* test1() */

void test1()
 {
  ScanString scan("line1\rline2\nline3\r\nline4\n\r\n\r");
  
  for(; +scan ;++scan)
    Printf(Con,"#; #;\n",CharCode(*scan),scan.getTextPos());
 }

/* test2() */

void test2()
 {
  ScanString scan("12345 +12345 -12345 1001b ABCDh 0x12345");
  
  int x;
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #;\n",x);
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #;\n",x);
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #;\n",x);
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #.b;\n",x);
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #.h;\n",x);
  
  
  Scanf(scan," #;",x);
  
  Printf(Con,"x = #.x;\n",x);
  
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test2 failed");
    }
 }

/* test3() */

struct Test1
 {
  int x = 0 ;
  int y = 0 ;

  template <class S>
  void scan(S &inp)
   {
    Scanf(inp,"( #; , #; )",x,y);
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",x,y);
   }
 };

struct Test2
 {
  int x = 0 ;
  int y = 0 ;
  
  typedef IntScanOpt ScanOptType;

  template <class S>
  void scan(S &inp,const ScanOptType &opt)
   {
    Scanf(inp,"( #; , #; )",BindScanOpt(opt,x),BindScanOpt(opt,y));
   }
  
  typedef IntPrintOpt PrintOptType;
  
  template <class P>
  void print(P &out,const PrintOptType &opt) const
   {
    Printf(out,"(#;,#;)",BindOpt(opt,x),BindOpt(opt,y));
   }
 };

struct Test3
 {
  int val = 0 ;
  
  typedef int ScanProxyType;
  
  typedef int PrintProxyType;
  
  operator int & () { return val; }
  
  operator int() const { return val; }
 };

void test3()
 {
  ScanString scan("( 12345,6789 )  ( 12345h,6789h ) 12345  4444 5555");
  
  Test1 test1;
  

  Scanf(scan,"#;",test1);
  
  Printf(Con,"#;\n",test1);
  
  
  Test2 test2;
  
  
  Scanf(scan," #.h;",test2);
  
  Printf(Con,"#.h;\n",test2);
  
  Test3 test3;
  

  Scanf(scan," #;",test3);
  
  Printf(Con,"#;\n",test3);
  
  
  Tuple<int,int> test4;
  
  
  Scanf(scan," #; #;",test4);
  
  Printf(Con,"#; #;\n",test4.first,test4.rest.first);
  
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test3 failed");
    }
 }

/* test4() */

void test4()
 {
  ScanString scan(
                  "000000000000000000000000000000000000000011111111b 01111111b -10000000b"
                  " FFFFh 7fffH -0000000000000000000000000000000000000000000000000008000H"
                  " 0xFFFF 0x7FFF -0x0000000000000000000000000000000000000000000000000008000"
                  " 004294967295 +02147483647 -000000000000000000000002147483648"
                 );

  uint8 u8;
  sint8 s8;
  sint8 m8;
  
  Scanf(scan,"#; #; #;",u8,s8,m8);
  
  Printf(Con,"#.b; #.b; #.b;\n",u8,s8,m8);
  
  
  uint16 u16;
  sint16 s16;
  sint16 m16;
  
  Scanf(scan," #; #; #;",u16,s16,m16);
  
  Printf(Con,"#.h; #.h; #.h;\n",u16,s16,m16);
  
  Scanf(scan," #; #; #;",u16,s16,m16);
  
  Printf(Con,"#.h; #.h; #.h;\n",u16,s16,m16);
  
  
  uint32 u32;
  sint32 s32;
  sint32 m32;
  
  Scanf(scan," #; #; #;",u32,s32,m32);
  
  Printf(Con,"#; #; #;\n",u32,s32,m32);
  
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test4 failed");
    }
 }

/* test5() */

void test5()
 {
  ScanString scan(
                  "+0x01 -0x01 +0x00001"
                  " 0 +0 -0"
                  " -01 +002 -0003"
                  " -01h +002h -0003h"
                  " -01b +001b -0001b"
                  " 0b 00b 000b"
                  " 0h 00h 000h"
                  " 0 00 000"
                  " 0x0 0x00 0x000"
                  " 0x01 0x002 0x0003"
                 );
  
  int x,y,z;
  
  Scanf(scan,"#; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #; #; #;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test5 failed");
    }
 }

/* test6() */

void test6()
 {
  ScanString scan("string1, string2 string3= string4=== string5 string6 \"name1\" \"name2\"");
  
  String x,y,z;
  
  Scanf(scan,"#; , #; #; =",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #.s; #.s; #.s;",x,y,z);
  
  Printf(Con,"#; #; #;\n",x,y,z);
  
  Scanf(scan," #.q; #.q;",x,y);
  
  Printf(Con,"#; #;\n",x,y);
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test6 failed");
    }
 }

/* test7() */

void test7()
 {
  ScanString scan("set setX go help select");
  
  StringSetScan x{"set","setX","go","help","select"};
  
  Scanf(scan,"#;",x);
  
  Printf(Con,"#;\n",x);
  
  Scanf(scan," #;",x);
  
  Printf(Con,"#;\n",x);
  
  Scanf(scan," #;",x);
  
  Printf(Con,"#;\n",x);
  
  Scanf(scan," #;",x);
  
  Printf(Con,"#;\n",x);
  
  Scanf(scan," #;",x);
  
  Printf(Con,"#;\n",x);
  
  if( scan.isFailed() )
    {
     Printf(Exception,"test7 failed");
    }
 }

} // namespace Private_0085
 
using namespace Private_0085; 
 
/* Testit<85> */ 

template<>
const char *const Testit<85>::Name="Test85 Scanf";

template<>
bool Testit<85>::Main() 
 {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  
  return true;
 }
 
} // namespace App
 
