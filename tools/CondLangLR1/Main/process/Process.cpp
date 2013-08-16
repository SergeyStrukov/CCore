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

#include "NonEmptyEstimate.h"
#include "GoodEstimate.h"
#include "LR1Estimate.h"

#include "Engine.h"

#include <CCore/inc/Exception.h>

namespace App {

/* functions */

static bool RunGoodTest(const Lang &lang)
 {
  LangEstimate<GoodEstimate> estimate(lang);
  
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
  
  TrackStage("Process bottom lang");

  Engine<LR1Estimate,LR1Context> engine_bottom(bottom);
  
  for(auto range=engine_bottom.getProps(); +range ;++range)
    if( range->hasConflict() )
      {
       TrackStage("CONFLICT");
        
       break;
      }
  
  {
   LR1Estimate::RuleSet::Accumulator acc;
   
   for(auto range=engine_bottom.getProps(); +range ;++range) acc+=range->getConflictSet();
   
   LR1Estimate::RuleSet result=acc;
   
   TrackStage("Conflict set: #;",result);
  }
  
  TrackStage("Process top lang");
  
  Engine<LR1Estimate,LR1Context> engine_top(top);
  
  PrintFile out("Result.txt");
  
  Putobj(out,engine_bottom,engine_top);

  TrackStage("Finish");
 }

} // namespace App

