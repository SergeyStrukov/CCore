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
#include "LR1Estimate.h"
#include "GoodEstimate.h"
#include "LangStateMachine.h"

#include <CCore/inc/Exception.h>

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
                              Printf(NoException,"#; is #;\n",synt.getName(),est);
                             
                              ret=false;
                             }
                          } 
                    );
  
  return ret;
 }

static void ProcessNonEmpty(const ExtLang &lang)
 {
  LangStateMachine<NonEmptyEstimate> machine(lang,{});

  Putobj(Con,lang);
  Putobj(Con,machine);
  // TODO
 }

static void ProcessLR1(const ExtLang &lang)
 {
  LangStateMachine<LR1Estimate> machine(lang,lang.getOriginalAtomCount());

  Putobj(Con,lang);
  Putobj(Con,machine);
  // TODO
 }

void Process(StrLen file_name)
 {
  TrackStage("Load file #.q;",file_name);
  
  CondLang clang(file_name);
  
  TrackStage("Build top lang");
  
  TopLang top(clang);
  
  TrackStage("Run good test on top lang");
  
  if( !RunGoodTest(top) ) return;
  
  TrackStage("Build bottom lang");
  
  BottomLang bottom(clang);
  
  TrackStage("Build extended top lang");
  
  ExtLang ext_top(top);
  
  TrackStage("Build extended bottom lang");
  
  ExtLang ext_bottom(bottom);
  
  // TODO
  ProcessNonEmpty(ext_top);
  ProcessLR1(ext_bottom);
  
  TrackStage("Finish");
 }

} // namespace App

