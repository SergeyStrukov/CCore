/* test0007.RefPtr.cpp */ 
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
#include <CCore/inc/RefPtr.h>

namespace App {

namespace Private_0007 {

/* class Test */

class Test : public MemBase_nocopy
 {
   unsigned refs;
   int value;
   
  public:
  
   explicit Test(int value_) : refs(1),value(value_) { Printf(Con,"Test(#;)\n",value); }
   
   ~Test() { Printf(Con,"~Test(#;)\n",value); }
   
   void show() { Printf(Con,"Test(#;).show()\n",value); }
   
   void incRef() { refs++; }
   
   bool decRef() { return !--refs; }
   
   void destroy() { delete this; }
 };
 
} // namespace Private_0007
 
using namespace Private_0007; 
 
/* Testit<7> */ 

template<>
const char *const Testit<7>::Name="Test7 RefPtr";

template<>
bool Testit<7>::Main() 
 { 
  RefPtr<Test> obj1(new Test(1));
  RefPtr<Test> obj2(new Test(2));
  
  Swap(obj1,obj2);
  
  obj1->show();
  obj2->show();
 
  InitExitObject<RefPtr<Test> > init_obj;
  InitStorage<sizeof (RefPtr<Test>)> mem1;
  InitStorage<sizeof (RefPtr<Test>)> mem2;
  
  init_obj.clean();
  init_obj.init(new Test(3));
  
  RefPtr<Test> *obj=init_obj.getPtr();
  
  Swap(obj1,*obj);
  
  (*obj)->show();
  
  obj=Move(obj,mem1.getPlace());
  
  (*obj)->show();
  
  obj=CtorMove(obj,mem2.getPlace());
  
  (*obj)->show();
  
  obj->~RefPtr();
  
  return true;
 }
 
} // namespace App
 
