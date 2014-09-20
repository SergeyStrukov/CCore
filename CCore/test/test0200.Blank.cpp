/* test0200.Blank.cpp */ 
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

#include <CCore/inc/Scanf.h>

namespace App {

namespace Private_0200 {

enum E
 {
  E0 = 0 
 };

class ESet
 {
   int val;
   
  public:
   
   ESet() {}
   
   void map(E &ret) const
    {
     ret=(E)val;
    }
   
   using ScanOptType = IntScanOpt ;
   
   template <class S>
   void scan(S &inp,ScanOptType opt)
    {
     Scanobj(inp,BindScanOpt(opt,val));
    }
 };

} // namespace Private_0200
 
using namespace Private_0200;

} // namespace App

namespace CCore {

template <>
struct ScanProxy<App::E> : ScanProxySet<App::E,App::ESet> {};

} // namespace CCore

namespace App {

/* Testit<200> */ 

template<>
const char *const Testit<200>::Name="Test200 Blank";

template<>
bool Testit<200>::Main() 
 {
  ScanString inp("12345");
  
  E e=E0;
  
  Scanf(inp,"#.8;",e);
  
  Printf(Con,"e = #.8;\n",e);
  
  return true;
 }
 
} // namespace App
 
