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

#include "PrintTools.h"

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

/* PrintBad() */

template <class P>
void PrintBad(P &out,const Lang &lang,const StateCompress<LR1Estimate> &compress)
 {
  ExtLangOpt extopt(lang,compress.getAtomCount());
  
  Printf(out,"#;\n",Title("Bad States"));
  
  ulen state_count=compress.getStateCount();
  
  DynArray<Trace> trace_table(state_count);
  
  for(ulen i=0; i<state_count ;i++) trace_table[i]=compress.buildTrace(i);
  
  for(auto p=compress.getStateTable(); +p ;++p)
    {
     ulen prop_index=p->prop_index;
     
     auto &prop=compress.getProps()[prop_index];
     
     if( prop.hasConflict() )
       {
        Printf(out,"\n#; = #;\n\n",BindOpt(extopt,PrintState(p->index,trace_table)),prop_index);
        
        Printf(out,"#;) #.b;",prop_index,prop);
       }
    }
  
  Printf(out,"\n#;\n",TextDivider());
 }

/* PrintRules() */

template <class P>
void PrintRules(P &out,const LangBase::SyntDesc &desc)
 {
  Putobj(out,"{ ");
  
  auto rules=desc.rules;
  
  for(ulen i=0; i<rules.len ;i++)
    {
     Printf(out,"lang.rules+#;",rules[i].index);
     
     if( i+1<rules.len ) Putobj(out," , ");
    }
  
  Putobj(out," }");
 }

/* PrintArgs() */

template <class P>
void PrintArgs(P &out,const LangBase::RuleDesc &desc)
 {
  Putobj(out,"{ ");
  
  auto args=desc.args;
  
  for(ulen i=0; i<args.len ;i++)
    {
     args[i].apply( [&] (Atom atom) { Printf(out,"lang.atoms+#;",atom.getIndex()); } , 
                    [&] (Synt synt) { Printf(out,"lang.synts+#;",synt.getIndex()); } );
     
     if( i+1<args.len ) Putobj(out," , ");
    }
  
  Putobj(out," }");
 }

/* Process() */

void Process(StrLen file_name)
 {
  SplitPath dev_name(file_name);
  SplitName path_name(dev_name.path);
  SplitExt no_ext(path_name.name);
  
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
      String out_name=StringCat(dev_name.dev,path_name.path,no_ext.name,".bad.txt");
      PrintFile out(Range(out_name)); 
    
      PrintBad(out,ext_top,compress);
      
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
  
  StateMap map(compress,compress_ne);
  
  String out_name=StringCat(dev_name.dev,path_name.path,"Result.txt");
  PrintFile out(Range(out_name));
  
  PrintFibres(out,compress,compress_ne,map);
  
  Putobj(out,BindOpt(ext_top,compress_ne));
  
#endif  

  {
   String out_name=StringCat(dev_name.dev,path_name.path,no_ext.name,".txt");
   PrintFile out(Range(out_name));
  
   Putobj(out,BindOpt(ext_top,compress));
  }
  
  {
   String out_name=StringCat(dev_name.dev,path_name.path,no_ext.name,".ddl");
   
   PosPrint<PrintFile> out(Range(out_name));
   
   Printf(out,"/* #;.ddl */\n\n",no_ext.name);
   
   Putobj(out,"include <../LangTypes.ddl>\n\n");
   
   Putobj(out,"Lang lang=\n");

   // lang
   {
    ListPrint<decltype(out)> lang_out(out);
    
    // atoms
    {
     ListPrint<decltype(lang_out)> atom_out(lang_out);
      
     for(auto &atom : clang.getAtoms() )
       Printf(atom_out,"{ #; , #; }#;",atom.index,StrLen(atom.name.inner(2,1)),EndItem());
     
     Putobj(atom_out,EndList());
    }
    
    Putobj(lang_out,EndItem());
    
    // synts
    {
     ListPrint<decltype(lang_out)> synt_out(lang_out);

     for(auto &synt : clang.getSynts() )
       {
        Printf(synt_out,"{ #; , #.q; ,",synt.index,synt.name);
        
        auto kinds=synt.kinds;
        
        if( !kinds )
          {
           Printf(synt_out," { { 0 , \"\" , lang.synts+#; } } ,#;",synt.index,AutoIndent());
          }
        else
          {
           Indent indent(synt_out.getCol());
         
           Putobj(synt_out,indent);
          
           ListPrint<decltype(synt_out)> kind_out(synt_out);
           
           for(auto &kind : kinds )
             Printf(kind_out,"{ #; , #.q; , lang.synts+#; }#;",kind.index,kind.name,synt.index,EndItem());
            
           Putobj(kind_out,EndList());
           
           Putobj(synt_out," ,",indent);
          }
        
        ListPrint<decltype(synt_out)> rule_out(synt_out);
         
        for(auto &rule : synt.rules )
          Printf(rule_out,"lang.rules+#;#;",rule.index,EndItem());
         
        Putobj(rule_out,EndList());
        
        Putobj(synt_out,"\n}",EndItem());
       }
     
     Putobj(synt_out,EndList());
    }
    
    Putobj(lang_out,EndItem());
    
    // elements
    {
     ListPrint<decltype(lang_out)> elem_out(lang_out);
     
     ulen element=0;
     
     for(auto &atom : clang.getAtoms() )
       Printf(elem_out,"{ #; , lang.atoms+#; , null }#;",element++,atom.index,EndItem());
     
     for(auto &synt : clang.getSynts() )
       {
        auto len=synt.kinds.len;
        
        if( !len ) len=1;
       
        for(ulen i=0; i<len ;i++)
          {
           Printf(elem_out,"{ #; , null , lang.synts[#;].kinds+#; }#;",element++,synt.index,i,EndItem());
          }
       }
     
     Putobj(elem_out,EndList());
    }
    
    Putobj(lang_out,EndItem());
    
    // rules
    {
     ListPrint<decltype(lang_out)> rule_out(lang_out);
     
     for(auto &rule : clang.getRules() )
       {
        ulen kindex=0;
        
        if( rule.kind ) kindex=rule.kind->index;
       
        Printf(rule_out,"{ #; , #.q; , lang.synts[#;].kinds+#; ,#;",rule.index,rule.name,rule.ret->index,kindex,AutoIndent());
        
        ListPrint<decltype(rule_out)> arg_out(rule_out);
         
        for(auto &element : rule.args )
          element.apply( [&] (const CondLangBase::AtomDesc *desc) 
                             {
                              Printf(arg_out,"{ lang.atoms+#; , null }#;",desc->index,EndItem()); 
                             } , 
                         [&] (const CondLangBase::SyntDesc *desc) 
                             {
                              Printf(arg_out,"{ null , lang.synts+#; }#;",desc->index,EndItem());
                             } 
                       );
         
        Putobj(arg_out,EndList());
        
        Putobj(rule_out,"\n}",EndItem());
       }
     
     Putobj(rule_out,EndList());
    }
    
    Putobj(lang_out,EndItem());
    
    // states
    {
     ListPrint<decltype(lang_out)> state_out(lang_out);
     
     for(auto &state : compress.getStateTable() )
       {
        Printf(state_out,"{ #; , lang.finals+#; ,#;",state.index,state.prop_index,AutoIndent());
        
        ListPrint<decltype(state_out)> trans_out(state_out);
         
        for(auto &trans : state.transitions )
          Printf(trans_out,"{ lang.elements+#; , lang.states+#; }#;",trans.element,trans.dst->index,EndItem());
         
        Putobj(trans_out,EndList());

        Putobj(state_out,"\n}",EndItem());
       }
     
     Putobj(state_out,EndList());
    }
    
    Putobj(lang_out,EndItem());
    
    // finals
    {
     ListPrint<decltype(lang_out)> final_out(lang_out);
     
     ulen index=0;
     
     for(auto &final : compress.getProps() )
       {
        Printf(final_out,"{ #; ,#;",index++,AutoIndent());
        
        ListPrint<decltype(final_out)> action_out(final_out);
        
        if( final.hasNull() )
          {
           Printf(action_out,"{ null , null }#;",EndItem());
          }
        else
          {
           auto &alpha=final.getAlpha();
           
           if( alpha.nonEmpty() )
             {
              Printf(action_out,"{ null , lang.rules+#; }#;",alpha.getPtr()->getIndex(),EndItem());
             }
          }
        
        for(auto &rec : Range(final.getBeta()) )
          {
           if( rec.object.shift )
             {
              Printf(action_out,"{ lang.atoms+#; , null }#;",rec.index.getIndex(),EndItem());
             }
           else
             {
              auto &rules=rec.object.rules;
              
              if( rules.nonEmpty() )
                {
                 Printf(action_out,"{ lang.atoms+#; , lang.rules+#; }#;",rec.index.getIndex(),rules.getPtr()->getIndex(),EndItem());
                }
             }
          }
        
        Putobj(action_out,EndList());
        
        Putobj(final_out,"\n}",EndItem());
       }
     
     Putobj(final_out,EndList());
    }
    
    Putobj(lang_out,EndItem(),EndList());
   }
   
   Putobj(out,";\n\n");
  }

  TrackStage("Finish");
 }

} // namespace App

