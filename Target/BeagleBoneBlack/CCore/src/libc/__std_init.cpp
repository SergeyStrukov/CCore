/* __std_init.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <__std_init.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/SpecialMemBase.h>
#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/libc/atexit.h>

using namespace CCore;

/* init/exit */

void __std_init(void)
 {
  Dev::Init_CPU();
  
  Init_SpecialMem();
  
  // constructors are called here
  
  __std_init_t *ptr=__std_get_init_base();
  __std_init_t *lim=__std_get_init_lim();
  
  for(; ptr<lim ;ptr++) 
    {
     if( __std_init_t func=*ptr ) func();
    }
 }
 
extern void before_main();
 
void __std_main(void)
 {
  Task::Internal::Enable();

  try
    {
     before_main();
    }
  catch(...)
    {
     Abort("Fatal error : exception from before_main()");
    }
  
  Task::Internal::Disable();
 }
 
void __std_exit(void)
 {
  Exit_atexit(); // call atexit functions, destructors are called here
  
  Exit_SpecialMem();
  
  Dev::Exit_CPU();
 }
 
