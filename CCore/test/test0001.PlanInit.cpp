/* test0001.PlanInit.cpp */ 
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

#include <CCore/inc/PlanInit.h>

namespace App {

#if 0

namespace Private_0001 {

ShowInitExit show_main("main.cpp");

/* struct Test1 */

struct Test1 : ShowInitExit 
 { 
  Test1() : ShowInitExit("Test1") {} 
  
  static const char * GetTag() { return "Test1"; }
 };

/* struct Test2 */

struct Test2 : ShowInitExit 
 { 
  Test2() : ShowInitExit("Test2") {} 
  
  static const char * GetTag() { return "Test2"; }
 };

/* pio */
 
PlanInitNode * Get1();
PlanInitNode * Get2();
 
PlanInitObject<Test1,PlanInitReq<GetPlanInitNode_CCore>/*,PlanInitReq<Get2>*/ > pio1 CCORE_INITPRI_1 ;

PlanInitNode * Get1() { return &pio1; }
 
PlanInitObject<Test2,PlanInitReq<Get1> > pio2 CCORE_INITPRI_1 ;

PlanInitNode * Get2() { return &pio2; }
 
} // namespace Private_0001
 
using namespace Private_0001; 
 
#endif
 
/* Testit<1> */ 

template<>
const char *const Testit<1>::Name="Test1 PlanInit";

template<>
bool Testit<1>::Main() 
 { 
  return true;
 }
 
} // namespace App
 
