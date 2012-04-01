/* test0010.TextLabel.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/TextLabel.h>

namespace App {

namespace Private_0010 {

/* enum E */

enum E
 {
  E1,
  E2,
  E3
 };

const char * GetTextDesc(E e)
 {
  switch( e )
    {
     case E1: return "E1";
     case E2: return "E2";
     case E3: return "E3";
     
     default: return "???";
    }
 }

/* struct Test */

struct Test
 {
  static unsigned Next;
  
  static const char * GetText() { return "Test"; }
  
  static unsigned GetNumber() { return GetTextLabelNumber(Next); }
 };
 
unsigned Test::Next = 0 ;

} // namespace Private_0010
 
using namespace Private_0010; 
 
/* Testit<10> */ 

template<>
const char *const Testit<10>::Name="Test10 TextLabel";

template<>
bool Testit<10>::Main() 
 { 
  NumTextLabel<Test> t1,t2,t3;
  
  Printf(Con,"#;\n#;\n#;\n",t1,t2,t3);
  
  TextLabel e1(E1),e2(E2),e3(E3);
  
  Printf(Con,"#;\n#;\n#;\n",e1,e2,e3);
  
  return true;
 }
 
} // namespace App
 
