/* __std_init.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <__std_init.h>

#include <stdio.h>

#include <CCore/inc/Print.h>
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
  
  __std_init_global(); // init CCore here
 }
 
extern int main(int argc,const char *argv[]);
 
void __std_main(void)
 {
  Task::Internal::Enable();
  
  const char *argv[]={"main",0};
  
  int ret=main(1,argv);
  
  fflush(stdout);
  
  Printf(Con,"\nmain() return #;\n\n",ret);
  
  Task::Internal::Disable();
 }
 
void __std_exit(void)
 {
  Exit_atexit(); // call atexit functions
  
  __std_exit_global();
  
  Exit_SpecialMem();
  Dev::Exit_CPU();
 }
 
