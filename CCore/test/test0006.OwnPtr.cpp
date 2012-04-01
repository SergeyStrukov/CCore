/* test0006.OwnPtr.cpp */ 
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

#include <CCore/inc/MemBase.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_0006 {

/* class Test */

class Test : public MemBase_nocopy
 {
   int value;
   
  public:
  
   explicit Test(int value_) : value(value_) { Printf(Con,"Test(#;)\n",value); }
   
   ~Test() { Printf(Con,"~Test(#;)\n",value); }
   
   void show() { Printf(Con,"Test(#;).show()\n",value); }
 };
 
} // namespace Private_0006
 
using namespace Private_0006; 
 
/* Testit<6> */ 

template<>
const char *const Testit<6>::Name="Test6 OwnPtr";

template<>
bool Testit<6>::Main() 
 { 
  OwnPtr<Test> obj1(new Test(1));
  OwnPtr<Test> obj2(new Test(2));
  
  Swap(obj1,obj2);
  
  obj1->show();
  obj2->show();

  InitExitObject<OwnPtr<Test> > init_obj;
  InitStorage<sizeof (OwnPtr<Test>)> mem1;
  InitStorage<sizeof (OwnPtr<Test>)> mem2;
  
  init_obj.clean();
  init_obj.init();
  
  OwnPtr<Test> *obj=init_obj.getPtr();
  
  Swap(obj1,*obj);
  
  (*obj)->show();
  
  obj=Move(obj,mem1.getPlace());
  
  (*obj)->show();
  
  obj=CtorMove(obj,mem2.getPlace());
  
  (*obj)->show();
  
  obj->~OwnPtr();
 
  return true;
 }
 
} // namespace App
 
