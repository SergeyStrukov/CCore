/* Process.h */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-SmartTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef SmartTest_Process_h
#define SmartTest_Process_h

#include "DataMap.h"

#include <CCore/inc/Array.h>

namespace App {

/* functions */

void Process(StrLen file_name);

/* classes */

class TopTest;

/* class TopTest */

class TopTest : NoCopy
 {
   PtrLen<TypeDef::Synt *> lang;
   TypeDef::State *start_state;
   
   DynArray<DynArray<DynArray<bool> > > table;
   
  private:
   
   bool flag(TypeDef::State *state,TypeDef::Kind *kind);
  
   void test(TypeDef::State *state,TypeDef::Kind *kind); 
   
  public:
  
   explicit TopTest(const DataMap &data);
   
   ~TopTest();
   
   void run();
 };

} // namespace App

#endif

