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

#include "LR1Prop.h"

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
  
  TrackStage("Extend bottom lang");

  ExtLang ext_bottom(bottom);
  
  TrackStage("Process top lang");
  
  ExtLang ext_top(top);
  LangDiagram diagram(ext_top);
  LangStateMachine<LR1Estimate,LR1MapContext> machine(ext_top,diagram,ext_bottom);
  StateCompress<LR1Estimate> compress(machine);
  StateTrace trace(compress);
  
  TrackStage("LR1) State count = #; Estimate count = #;",compress.getStateCount(),compress.getPropCount());
  
  {
   ulen conflicts=0;
   
   for(auto &est : compress.getProps() ) conflicts+=est.hasConflict();
   
   if( conflicts )
     {
      TrackStage("#; CONFLICTs detected. Not LR1 language.",conflicts);
     }
   else
     {
      TrackStage("No conflicts. LR1 language.");
     }
  }
  
  StateCompress<LR1Estimate,LR1PropNonEmpty> compress_ne(machine);
  StateTrace trace_ne(compress_ne);
  
  TrackStage("NonEmpty) State count = #; Estimate count = #;",compress_ne.getStateCount(),compress_ne.getPropCount());
  
  PrintFile out("Result.txt");
  
  PrintCompress(out,ext_top,compress,trace);
  PrintCompress(out,ext_top,compress_ne,trace_ne);

  TrackStage("Finish");
 }

} // namespace App

