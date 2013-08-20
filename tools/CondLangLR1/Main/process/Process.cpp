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

#include "StateMap.h"

#include <CCore/inc/Path.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Exception.h>

namespace App {

/* RunGoodTest() */

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

/* PrintFibres() */

template <class P,class TopCompress>
void PrintFibre(P &out,const TopCompress &compress,PtrLen<const State> range)
 {
  ulen prop=range->getPropIndex();
  bool flag=false;
  
  for(State top : range ) 
    {
     ulen index=top.getPropIndex();
     
     Printf(out," #;:#;)",top.getIndex(),index);
     
     if( index!=prop ) flag=true;
    }

  if( flag )
    {
     for(State top : range )
       {
        Printf(out,"  #.b;\n  -----\n",compress.getProps()[top.getPropIndex()]);
       }
    }
  
  Putch(out,'\n');
 }

static bool HasMultipleProps(PtrLen<const State> range)
 {
  ulen prop=range->getPropIndex();
  
  for(State top : range ) 
    {
     if( top.getPropIndex()!=prop ) return true;
    }
  
  return false;
 }

template <class P,class TopCompress,class BottomCompress>
void PrintFibres(P &out,const TopCompress &compress,const BottomCompress &bottom,const StateMap &map)
 {
  Printf(out,"#;\n",Title("Fibres"));
  
  bottom.applyForStates( [&] (State state) 
                             { 
                              auto range=map.getFibre(state);
                             
                              Printf(out,"\n#;:#;) <-",state.getIndex(),state.getPropIndex());
                             
                              if( !range )
                                {
                                 Putobj(out," empty\n");
                                }
                              else
                                {
                                 PrintFibre(out,compress,range);
                                }
                             } 
                       );
  
  {
   auto range=map.getNullFibre();
   
   if( +range )
     {
      Printf(out,"\nNULL <-");
      
      PrintFibre(out,compress,range);
     }
  }
  
  Printf(out,"\n#;\n",TextDivider());
  
  ulen count=0;
  
  bottom.applyForStates( [&] (State state) 
                             { 
                              auto range=map.getFibre(state);
                              
                              if( range.len>1 && HasMultipleProps(range) )
                                {
                                 Printf(out,"\n#;) MP fibre size #;\n",state.getIndex(),range.len);
                                 
                                 count++;
                                }
                             } 
                       );
  
  {
   auto range=map.getNullFibre();
   
   if( range.len>1 && HasMultipleProps(range) )
     {
      Printf(out,"\nNULL MP fibre size #;\n",range.len);
      
      count++;
     }
  }
  
  Printf(out,"\nMP fibres = #;\n",count);
  
  Printf(out,"\n#;\n",TextDivider());
 }

/* Process() */

void Process(StrLen file_name)
 {
  SplitPath dev_name(file_name);
  SplitName path_name(dev_name.path);
  
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
  
  TrackStage("LR1) #;",PrintCompressCounts(compress));
  
  {
   ulen conflicts=0;
   
   for(auto &est : compress.getProps() ) conflicts+=est.hasConflict();
   
   if( conflicts )
     {
      String out_name=StringCat(dev_name.dev,path_name.path,"BadResult.txt");
      PrintFile out(Range(out_name));
      
      Putobj(out,BindOpt(ext_top,compress));
     
      Printf(Exception,"#; CONFLICTs detected. Not LR1 language.",conflicts);
     }
   else
     {
      TrackStage("No conflicts. LR1 language.");
     }
  }
  
  StateCompress<LR1Estimate,LR1PropNonEmpty> compress_ne(machine);
  
  TrackStage("NonEmpty) #;",PrintCompressCounts(compress_ne));

#if 0  
  
  StateCompress<LR1Estimate,LR1PropShiftSet> compress_shift(machine);
  
  TrackStage("Shift) #;",PrintCompressCounts(compress_shift));
  
  StateCompress<LR1Estimate,LR1PropValidSet> compress_valid(machine);
  
  TrackStage("Valid) #;",PrintCompressCounts(compress_valid));
  
  StateCompress<LR1Estimate,LR1PropRuleSet> compress_rules(machine);
  
  TrackStage("Rules) #;",PrintCompressCounts(compress_rules));
  
#endif  
  
  StateMap map(compress,compress_ne);
  
  String out_name=StringCat(dev_name.dev,path_name.path,"Result.txt");
  PrintFile out(Range(out_name));
  
  PrintFibres(out,compress,compress_ne,map);
  
  Putobj(out,BindOpt(ext_top,compress));
  Putobj(out,BindOpt(ext_top,compress_ne));

  TrackStage("Finish");
 }

} // namespace App

