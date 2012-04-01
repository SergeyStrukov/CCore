/* testRun.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_testRun_h
#define CCore_test_testRun_h

#include <CCore/inc/Task.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

class RunTasks;

/* class RunTasks */

class RunTasks : NoCopy
 {
   AntiSem asem;
   Function<void (void)> stop_func;
   
  public:
  
   explicit RunTasks(Function<void (void)> stop_func_=Nothing) : asem("RunTasks"),stop_func(stop_func_) {}
   
   ~RunTasks() { stop_func(); asem.wait(); }
   
   template <class FuncInit,class ... TT>
   void operator () (FuncInit func_init,TT ... tt)
    {
     asem.inc();
        
     RunFuncTask(func_init,asem.function_dec(),tt...);
    }
   
   template <class FuncInit,class ... TT>
   void operator () (ulen count,FuncInit func_init,TT ... tt)
    {
     for(ulen cnt=count; cnt ;cnt--) (*this)(func_init,tt...);
    }
 };

} // namespace App

#endif

