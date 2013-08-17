/* test3001.Atomic.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

namespace App {

namespace Private_3001 {


} // namespace Private_3001
 
using namespace Private_3001; 
 
/* Testit<3001> */ 

template<>
const char *const Testit<3001>::Name="Test3001 Atomic";

template<>
bool Testit<3001>::Main() 
 {
  Atomic atomic;

  atomic=0xFFFFFFFFFFFF;

  Printf(Con,"#.h;\n",atomic);

  auto old=(atomic=0x111122223333);

  Printf(Con,"#.h; #.h;\n",old,atomic);

  old=(atomic+=0x333322221111);

  Printf(Con,"#.h; #.h;\n",old,atomic);

  old=atomic.trySet(0,1);

  Printf(Con,"#.h; #.h;\n",old,atomic);

  old=atomic.trySet(0x444444444444,1);

  Printf(Con,"#.h; #.h;\n",old,atomic);
  
  return true;
 }
 
} // namespace App
 
