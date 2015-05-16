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

#include <CCore/inc/video/UserAction.h>

namespace App {

namespace Private_0200 {


} // namespace Private_0200
 
using namespace Private_0200;

/* Testit<200> */ 

template<>
const char *const Testit<200>::Name="Test200 Blank";

template<>
bool Testit<200>::Main() 
 {
  using namespace Video;
  
  UserAction action=UserAction::Create_RepeatKey(VKey_F1,KeyMod_Null,5);

  struct SomeType
   {
    void key(VKey,KeyMod) { Printf(Con,"key()\n"); }
    
    //void key(VKey,KeyMod,unsigned) { Printf(Con,"key-repeat()\n"); }
   };
  
  SomeType obj;
  
  action.dispatch(obj, [] (UserAction) { Printf(Con,"default\n"); } );
  
  return true;
 }
 
} // namespace App
 
