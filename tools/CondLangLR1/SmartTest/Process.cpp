/* Process.cpp */
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

#include "Process.h"

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

/* functions */

void Process(StrLen file_name)
 {
  Printf(Con,"Load file #.q;\n\n",file_name);
  
  DataMap data(file_name);
  
  data.sanity();
  
  Printf(Con,"Sanity is OK\n\n");
  
  TopTest test(data);
  
  test.run();
  
  Printf(Con,"Top test is OK\n\n");
 }

/* class TopTest */

void TopTest::test(TypeDef::State *state,TypeDef::Kind *kind)
 {
  if( flag(state,kind) ) return;
  
  for(auto *rule : kind->rules )
    {
     TypeDef::State *st=state;
     
     for(auto arg : rule->args )
       {
        st=test(st,arg);
       }
     
     
    }
 }

TopTest::TopTest(const DataMap &data)
 : lang(data.getLang().lang),
   start_state(data.getLang().states.ptr)
 {
  // TODO : init table 
 }
   
TopTest::~TopTest()
 {
 }
   
void TopTest::run()
 {
 }
   
} // namespace App
