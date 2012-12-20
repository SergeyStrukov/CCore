/* test0072.GCDConst.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/algon/GCDConst.h>

namespace App {

namespace Private_0072 {


} // namespace Private_0072
 
using namespace Private_0072; 
 
/* Testit<72> */ 

template<>
const char *const Testit<72>::Name="Test72 GCDConst";

template<>
bool Testit<72>::Main() 
 {
  Printf(Con,"#;\n",Algon::GCDConst<unsigned,100*19,100*12>::Result());
  Printf(Con,"#;\n",Algon::LCMConst<unsigned,100*19,100*12>::Result());
  
  return true;
 }
 
} // namespace App
 
