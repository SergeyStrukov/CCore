/* test2013.ForcedTimeout.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/Task.h>

namespace App {

namespace Private_2013 {


} // namespace Private_2013
 
using namespace Private_2013; 
 
/* Testit<2013> */ 

template<>
const char *const Testit<2013>::Name="Test2013 ForcedTimeout";

template<>
bool Testit<2013>::Main() 
 { 
  ForcedTimeout fto;
  
  Ticker ticker(fto.function_abort_int());
  
  ticker.start(3_sec);
  
  Sem sem;
  
  sem.take(100_sec);
  //sem.take();
  
  Printf(Con,"done #;\n",fto.clear());
 
  return true;
 }
 
} // namespace App
 
