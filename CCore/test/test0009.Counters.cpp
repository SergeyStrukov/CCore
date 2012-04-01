/* test0009.Counters.cpp */ 
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

#include <CCore/inc/Counters.h>

namespace App {

namespace Private_0009 {

/* enum E */

enum E
 {
  E1,
  E2,
  E3,
  
  ELim
 };
 
const char * GetTextDesc(E e) 
 {
  switch( e )
    {
     case E1 : return "E1";
     case E2 : return "E2";
     case E3 : return "E3";
     
     default: return "";
    }
 }
 
/* functions */

void Add(Counters<E,ELim> &cnt)
 {
  cnt.count(E1,5);
  cnt.count(E2);
  cnt.count(E3,15);
 }
 
void Show(Counters<E,ELim> &cur,Counters<E,ELim> next) 
 {
  Printf(Con,"count\n#;",next);
  
  cur.diff(next);
  
  Printf(Con,"diff\n#10;",next);
 }
  
} // namespace Private_0009
 
using namespace Private_0009; 
 
/* Testit<9> */ 

template<>
const char *const Testit<9>::Name="Test9 Counters";

template<>
bool Testit<9>::Main() 
 { 
  Counters<E,ELim> cnt;
  
  Counters<E,ELim> cur;
  
  Add(cnt);
  Show(cur,cnt);
  
  Add(cnt);
  Show(cur,cnt);
  
  Add(cnt);
  Show(cur,cnt);
  
  return true;
 }
 
} // namespace App
 
