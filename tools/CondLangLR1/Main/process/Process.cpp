/* Process.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Process.h"

#include "LangDiagram.h"
#include "LangEstimate.h"
#include "NonEmptyEstimate.h"
#include "GoodEstimate.h"
#include "LangStateMachine.h"

namespace App {

/* functions */

static bool RunGoodTest(const Lang &lang)
 {
  LangEstimate<GoodEstimate> estimate(lang,{});
  
  bool ret=true;

  lang.applyForSynts( [&] (Synt synt) 
                          {
                           auto est=estimate[synt];
                           
                           if( est.notGood() )
                             {
                              Printf(Con,"#; is #;\n",synt.getName(),est);
                             
                              ret=false;
                             }
                          } 
                    );
  
  return ret;
 }

static void ProcessNonEmpty(const Lang &lang)
 {
  LangStateMachine<NonEmptyEstimate> machine(lang,{});
  
  // TODO
 }

static void ProcessLR1(const ExtLang &lang)
 {
  // TODO
 }

void Process(StrLen file_name)
 {
  Printf(Con,"Load file #.q;\n",file_name);
  
  CondLang clang(file_name);
  
  Printf(Con,"Build bottom lang\n");
  
  BottomLang bottom(clang);
  
  Printf(Con,"Build top lang\n");
  
  TopLang top(clang);
  
  Printf(Con,"Build extended bottom lang\n");
  
  ExtLang ext(bottom);
  
  Printf(Con,"Run good test on top lang\n");
  
  if( !RunGoodTest(top) ) return;
  
  // TODO
  ProcessNonEmpty(top);
  ProcessLR1(ext);
  
  Printf(Con,"Finish\n");
 }

} // namespace App

