/* Run.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Run.h"

namespace App {

/* class PrintRule */

void PrintRule::GuardRuleList()
 {
  Printf(Exception,"PrintRule::PrintRule(PtrLen<const RIndex> list) : list.len!=1");
 }

/* class Run */

template <class T>
bool Run::sanity()
 {
  T test(lang);
  
  while( test.step() );
  
  PrintCon con(Con);
  
  if( !test.check(con) )
    {
     test.check(out);
     
     return false;
    }
    
  return true;  
 }

void Run::puncture(bool do_out)
 {
  // create MatrixTable
  
  MatrixTable<Estimate> table(punct);

  if( do_out )
    {
     Putobj(out,"/* NonTerminal estimates */ \n");
    
     for(auto p=lang.getNRange(); +p ;++p)
       Printf(out,"\n#; :\n#;\n",lang.getTextDesc(*p),PrintEstimate(punct,table.get(*p)));
    
     Putobj(out,"\n/* Matrix table */ \n");
    
     for(auto p=punct.getAlphaRange(); +p ;++p)
       Printf(out,"\n#; :#;",punct.getTextDesc(*p),PrintEMatrix(punct,table.getMatrix(*p)));
     
     Putch(out,'\n');
    }
  
  // evaluate F
  
  Putobj(Con," Evaluate F ...\n");

  EMatrix F(table.getMatrix(AlphaIndexNull)); 

  {
   while( SetCmp(F,F+F*F) );
  }
  
  if( do_out )
    {
     Putobj(out,"/* F */ \n");
    
     Printf(out,"\nF :#;\n",PrintEMatrix(punct,F));
    }
  
  Putobj(Con," finished\n\n");
  
  // evaluate B

  Putobj(Con," Evaluate B ...\n");

  EMatrix B(table.getMatrix(AlphaIndexBegin));
  
  {
   B=B+F*B;
  }
  
  if( do_out )
    {
     Putobj(out,"/* B */ \n");
    
     Printf(out,"\nB :#;\n",PrintEMatrix(punct,B));
    }
  
  Putobj(Con," finished\n\n");
  
  // evaluate T[]
  
  Putobj(Con," Evaluate T[] ...\n");

  DynArray<EMatrix> T(punct.getAlphaIndexLim());

  {
   for(auto p=punct.getAlphaRange(AlphaIndexFirst); +p ;++p)
     {
      AlphaIndex a=*p;
      
      auto &t=table.getMatrix(a);
    
      T[a]=t+F*t;
     }
  }
  
  if( do_out )
    {
     Putobj(out,"/* T[] */ \n");
     
     for(auto p=punct.getAlphaRange(AlphaIndexFirst); +p ;++p)
       {
        AlphaIndex a=*p;
       
        Printf(out,"\nT[#;] :#;",punct.getTextDesc(a),PrintEMatrix(punct,T[a]));
       }
     
     Putch(out,'\n');
    }
  
  Putobj(Con," finished\n\n");
  
  // generate states
  
  Putobj(Con," State generation process ...\n\n");
  
  {
   MatrixRecSet recset;
   DynArray<MatrixRec *> ptr_array;
   
   {
    MatrixRec &rec=recset.find_or_add(B);
    
    rec.setNumber(0);
    
    ptr_array.append_copy(&rec);
   }
   
   for(ulen I=0; I<ptr_array.getLen() ;I++)
     {
      if( I>=MaxStates ) 
        {
         Printf(Exception,"Run::puncture() : too many states");
        }
     
      MatrixRec *cur=ptr_array[I];
     
      DynArray<StateTransition> trans;
   
      for(auto p=punct.getAlphaRange(AlphaIndexFirst); +p ;++p)
        {
         AlphaIndex a=*p;
         
         EMatrix M=T[a]*cur->getMatrix();
         
         if( M.nonEmpty() )
           {
            MatrixRec &rec=recset.find_or_add(M);
         
            if( rec.setNumber(ptr_array.getLen()) ) ptr_array.append_copy(&rec);
           
            trans.append_fill(a,rec.getNumber());
           }
        }
        
      state_list.append_fill(I,TransitionSet(Range_const(trans)),cur->getFinals());
        
      Printf(Con," State #;\n",I);
     }
  }
  
  Putobj(Con,"\n finished\n\n");
 }
 
void Run::way(bool do_out)
 {
  Putobj(Con," State way process ...\n\n");
  
  // wayout
  {
   state_list[0].setHasWay();
  
   for(;;)
     {
      bool stop=true;
      
      for(auto p=Range(state_list); +p ;++p)
        if( p->wayout(state_list.getPtr()) )
          stop=false;
          
      if( stop ) break;   
     }
  }
  
  // print states
  
  if( do_out )
    {
     Putobj(out,"/* States */ \n");
    
     for(auto p=Range(state_list); +p ;++p) Putobj(out,p->getPrint(punct)); 

     Putch(out,'\n');
    }

  Putobj(Con,"\n finished\n\n");
 }
 
void Run::compression()
 {
  Putobj(Con," State compression process ...\n\n");
  
  // finals extraction
  {
   DynArray<State *> finsort;
   
   RecordPtrs(Range(state_list),finsort);
   
   IncrSort(Range(finsort), [] (State *a,State *b) -> bool { return a->getFinals() < b->getFinals() ; } );
   
   auto p=Range_const(finsort);
   
   if( +p )
     {
      FinalSet prev=(*p)->getFinals();
      ulen prev_number=0;

      {
       finals.append_copy(prev);
      
       (*p)->setFinalNumber(prev_number);
      }
      
      for(++p; +p ;++p)
        {
         const FinalSet &cur=(*p)->getFinals();
       
         if( cur!=prev )
           {
            prev=cur;
            prev_number++;
            
            finals.append_copy(prev);
           }
         
         (*p)->setFinalNumber(prev_number);
        }
     }
  }
  
  // print finals
  {
   Putobj(out,"/* Finals */ \n");
   
   for(ulen i=0,lim=finals.getLen(); i<lim ;i++) Putobj(out,PrintFinalSet(punct,finals[i],i)); 
   
   Putch(out,'\n');
  } 
  
  // compression
  {
   ulen prev_group_count=0;
  
   for(;;)
     {
      DynArray<State *> groupsort;
      
      RecordPtrs(Range(state_list),groupsort);
      
      State *base=state_list.getPtr();
      
      IncrSort(Range(groupsort), [=] (State *a,State *b) -> bool { return a->groupCmp(base,*b)<0 ; } );
      
      ulen group_count=0;
      
      auto p=Range_const(groupsort);
      
      if( +p )
        {
         State *prev=*p;
         
         group_count++;
           
         (*p)->setGroupNumber(prev->getNumber());
         
         for(++p; +p ;++p)
           {
            if( prev->groupCmp(base,**p) ) 
              {
               prev=*p;
               group_count++;
              }
              
            (*p)->setGroupNumber(prev->getNumber());
           }
        }
        
      for(auto p=Range(state_list); +p ;++p) p->updateGroupNumber();
      
      Printf(Con," group_count=#;\n",group_count);
      
      if( !SetCmp(prev_group_count,group_count) ) break; 
     }
     
   DynArray<State> new_list(DoReserve,prev_group_count); 
   
   for(auto p=Range(state_list); +p ;++p)
     if( p->isSelected() )
       {
        p->setGroupNumber(new_list.getLen());
        
        new_list.append_copy(*p);
       } 
       
   for(auto p=Range(state_list); +p ;++p)
     p->propagateGroupNumber(state_list.getPtr());
   
   for(auto p=Range(new_list); +p ;++p)
     p->update(state_list.getPtr());
     
   Swap(state_list,new_list);
  }  
  
  // print
  {
   Putobj(out,"/* Compressed States */ \n");
  
   for(auto p=Range_const(state_list); +p ;++p) Putobj(out,p->getPrint(punct)); 

   Putch(out,'\n');
  } 

  Putobj(Con,"\n finished\n\n");
 }

bool Run::nonLR1()
 {
  bool ret=false;
  
  for(auto p=Range(state_list); +p ;++p)
    if( p->nonLR1() )
      {
       if( !ret )
         {
          Putobj(out,"/* NonLR1 */ \n");
       
          ret=true;
         }

       Putobj(out,p->getPrint(punct));
      } 
    
  if( ret )
    Putobj(Con,"\n Non LR1 language\n\n");
  else
    Putobj(Con,"\n LR1 language\n\n");
       
  return ret;  
 }
 
void Run::stateDDL(bool nonLR1)
 {
  ulen RIndexLim=lang.getRIndexLim();
  ulen TIndexLim=lang.getTIndexLim();
  ulen NIndexLim=lang.getNIndexLim();
  ulen StateLim=state_list.getLen();
  ulen FinalLim=finals.getLen();
  
  PrintFile out("State.ddl");
  
  Putobj(out,"/* State.ddl */ \n\n");
  
  Printf(out,

          "type RIndex = uint ;\n"
          "type TIndex = uint ;\n"
          "type NIndex = uint ;\n"
          "type NTIndex = uint ;\n"
          "type StateIndex = uint ;\n"
          "type FinalIndex = uint ;\n\n"
    
          "RIndex RIndexLim = #; ;\n"
          "TIndex TIndexLim = #; ;\n"
          "NIndex NIndexLim = #; ;\n"
          "NTIndex NTIndexLim = #; ; // T , N\n"
          "StateIndex StateIndexLim = #; ;\n"
          "FinalIndex FinalIndexLim = #; ;\n\n"
    
          "struct Final\n"
          " {\n"
          "  FinalIndex final;\n\n"
    
          "  struct Action { TIndex t; #;; } [] actions;\n"
          " };\n\n"
    
          "struct State\n"
          " {\n"
          "  StateIndex state;\n\n"
    
          "  struct Transition { NTIndex ntt; State *state; } [] transitions;\n\n"
    
          "  Final *final;\n"
          " };\n\n"
    
          "struct Rule\n"
          " {\n"
          "  RIndex rule;\n"
          "  text name;\n"
          "  NIndex result;\n"
          "  NTIndex[] str;\n"
          " };\n\n"
    
          "struct NonTerminal\n"
          " {\n"
          "  NIndex nt;\n" 
          "  text name;\n"
          "  Rule * [] rules;\n"
          " };\n\n"
    
        ,RIndexLim
        ,TIndexLim
        ,NIndexLim
        ,TIndexLim+NIndexLim
        ,StateLim
        ,FinalLim
        ,(nonLR1?"Rule * [] rules":"Rule *rule")
        );
  
  Printf(out,
    
          "Final[#;] FinalTable=\n"
          " {\n"
    
        ,FinalLim);
  
  for(ulen i=0; i<FinalLim ;i++)
    {
     Printf(out,"  { #; ,\n",i);
     
     auto p=finals[i].read();
     
     Putobj(out,"   {\n");
     
     if( nonLR1 )
       {
        if( +p )
          {
           Printf(out,"    { #; , #; }",p->index,PrintRules(p->object.read()));
           
           for(++p; +p ;++p) Printf(out,",\n    { #; , #; }",p->index,PrintRules(p->object.read()));
           
           Putch(out,'\n');
          }
       }
     else
       {
        if( +p )
          {
           Printf(out,"    { #; , #; }",p->index,PrintRule(p->object.read()));
           
           for(++p; +p ;++p) Printf(out,",\n    { #; , #; }",p->index,PrintRule(p->object.read()));
           
           Putch(out,'\n');
          }
       }
     
     Putobj(out,"   }\n");
     
     Putobj(out,"  }");
     
     if( i+1<FinalLim ) Putobj(out,",\n"); else Putobj(out,"\n");
    }
  
  Putobj(out,
    
          " };\n\n"
    
        );
  
  Printf(out,
    
          "State[#;] StateTable=\n"
          " {\n"
    
        ,StateLim);

  for(ulen i=0; i<StateLim ;i++)
    {
     Printf(out,"  { #; ,\n",i);

     {
      auto p=state_list[i].getTransitions().read();
      
      Putobj(out,"   {\n");
      
      if( +p )
        {
         Printf(out,"    { #; , StateTable+#; }",p->index-1,p->object);
         
         for(++p; +p ;++p) Printf(out,",\n    { #; , StateTable+#; }",p->index-1,p->object);
         
         Putch(out,'\n');
        }
      
      Putobj(out,"   },\n");
     }

     Printf(out,"    FinalTable+#;\n",state_list[i].getFinalNumber());
     
     Putobj(out,"  }");
     
     if( i+1<StateLim ) Putobj(out,",\n"); else Putobj(out,"\n");
    }
  
  Putobj(out,
    
          " };\n\n"
    
        );
  
  Printf(out,
    
          "text[#;] TNames=\n"
          " {\n"
    
        ,TIndexLim);

  {
   auto p=lang.getTRange();
   
   if( +p )
     {
      Printf(out,"  \"#;\"",SlashQuote(lang,*p));
      
      for(++p; +p ;++p) Printf(out,",\n  \"#;\"",SlashQuote(lang,*p));
      
      Putch(out,'\n');
     }
  }
  
  Putobj(out,
    
          " };\n\n"
    
        );
  
  Printf(out,
    
          "Rule[#;] RuleTable=\n"
          " {\n"
          "  /* shift, special */ { 0 , \"<-\" }"
    
        ,RIndexLim);
  
  {
   for(auto p=lang.getRRange(RIndexFirst); +p ;++p)
     {
      auto rec=lang.getRule(*p);
      
      Printf(out,",\n  { #; , #.q; , #; , #; }",rec.rule,lang.getTextDesc(rec.rule),rec.result,PrintRuleStr(TIndexLim,rec.str));
     }
   
   Putch(out,'\n');
  }
  
  Putobj(out,
    
          " };\n\n"
    
        );
  
  Printf(out,
    
          "NonTerminal[#;] NonTerminalTable=\n"
          " {\n"
    
        ,NIndexLim);
  
  {
   auto p=lang.getNRange();
   
   if( +p )
     {
      Printf(out,"  { #; , #.q; , #; }",*p,lang.getTextDesc(*p),PrintRules_rec(lang.getRules(*p)));
      
      for(++p; +p ;++p) Printf(out,",\n  { #; , #.q; , #; }",*p,lang.getTextDesc(*p),PrintRules_rec(lang.getRules(*p)));
      
      Putch(out,'\n');
     }
  }
  
  Putobj(out,
    
          " };\n\n"
    
        );
 }

void Run::test(StrLen CCORE_Root)
 {
  FileSystem fs;

  try
    {
     SilentReportException report;
     
     fs.createDir("test");
     fs.createDir("test/obj");
    }
  catch(...)
    {
    }
  
  PrintFile out("test/Makefile");
  
  Printf(out, 
    
          "## Makefile\n\n"
         
          "CCORE_ROOT = #;\n\n"
         
          "CCORE_TARGET = WIN32\n\n"
         
          "SRC_PATH_LIST = . $(CCORE_ROOT)/tools/LangLR1-tools/test\n\n"
         
          "OBJ_PATH = obj\n\n"
         
          "TARGET = main.exe\n\n"
         
          "LANG = #;\n\n"
         
          "CCOPT_EXTRA = -D 'DEF_LANG=$(LANG)' -I .\n\n"
         
          "include $(CCORE_ROOT)/Target/Makefile.app\n\n"
         
          "run: $(TARGET)\n"
          "\t./$(TARGET)\n"
    
        ,CCORE_Root
        ,lang.getName());
 }

void Run::parser()
 {
  StrLen Name=lang.getName();
  ulen RIndexLim=lang.getRIndexLim();
  ulen TIndexLim=lang.getTIndexLim();
  ulen NIndexLim=lang.getNIndexLim();
  ulen AlphaIndexLim=punct.getAlphaIndexLim();
  
  ulen RLMax=0;
  
  for(auto p=lang.getRRange(RIndexFirst); +p ;++p) Replace_max(RLMax,lang.getRule(*p).str.len); 
   
  // h-file
 
  PrintFile outH("test/Parser.gen.h");
  
  Printf(outH,
  
          "/* Parser.gen.h */ \n\n"
  
          "##ifndef Parser_gen_h\n"
          "##define Parser_gen_h\n\n"
          
          "/* lang #; */ \n\n"
          
          "namespace #; {\n\n"
          
          "/* types */ \n\n"      
          
          "enum RIndex { RIndexShift=0, RIndexLim=#; };\n\n" 
          
          "const char * GetTextDesc(RIndex);\n\n"
          
          "enum RuleLength { RuleLengthZero=0, RuleLengthMax=#; };\n\n"
          
          "enum TIndex { TIndexEnd=0, TIndexLim=#; };\n\n"
          
          "const char * GetTextDesc(TIndex);\n\n"
          
          "enum NTIndex { NTIndexEnd=0, NTIndexLim=#; };\n\n"
    
          "const char * GetTextDesc(NTIndex);\n\n"
          
          "enum StateIndex { StateIndexBegin=0, StateIndexLim=#; };\n\n"
          
          "/* struct RuleProp */ \n\n"
          
          "struct RuleProp\n"
          " {\n"
          "  RIndex rule;\n"
          "  RuleLength length;\n"
          "  NTIndex result;\n"
          "  NTIndex args[RuleLengthMax];\n\n"
          
          "  static const RuleProp Table[RIndexLim-1];\n"
          "  static const RuleProp ShiftTable[TIndexLim];\n"
          " };\n\n"

          "/* struct State */ \n\n"
          
          "struct State\n"
          " {\n"
          "  RIndex finals[TIndexLim];\n"
          "  StateIndex transitions[NTIndexLim];\n\n"
          
          "  static const State * GetBegin() { return Table; }\n\n"
          
          "  const RuleProp * final(TIndex i) const\n"
          "   {\n"
          "    if( RIndex r=finals[i] )\n"
          "      {\n"
          "       if( r==1 )\n"
          "         return RuleProp::ShiftTable+i;\n"
          "       else\n"
          "         return RuleProp::Table+r-2;\n"
          "      }\n\n"
          
          "    return 0;\n"
          "   }\n\n"
          
          "  const State * transition(NTIndex i) const\n" 
          "   {\n"
          "    if( StateIndex t=transitions[i] ) return Table+t-1;\n\n" 
          
          "    return 0;\n"
          "   }\n\n"
          
          "  static const State Table[StateIndexLim];\n"
          " };\n\n"
          
          "} // namespace #;\n\n"      
  
          "##endif\n\n"
          
        ,Name
        ,Name
        ,RIndexLim
        ,RLMax
        ,TIndexLim
        ,TIndexLim+NIndexLim
        ,state_list.getLen()
        ,Name);
          
  // cpp-file        
          
  PrintFile outCpp("test/Parser.gen.cpp");
  
  Printf(outCpp,
    
          "/* Parser.gen.cpp */ \n\n"
  
          "##include \"Parser.gen.h\"\n\n"
            
          "/* lang #; */ \n\n"
          
          "namespace #; {\n\n"
            
          "/* types */ \n\n"
          
          "const char * GetTextDesc(RIndex i)\n"
          " {\n"
          "  static const char *const Table[]=\n"
          "   {\n" 
            
        ,Name
        ,Name);
            
  for(auto p=lang.getRRange(); +p ;++p)
    Printf(outCpp,"    \"#;\",\n",lang.getTextDesc(*p));
            
  Putobj(outCpp,
    
          "    \"...\"\n"
          "   };\n\n"
            
          "  return Table[i];\n"
          " }\n\n"
          
          "const char * GetTextDesc(TIndex i)\n"
          " {\n"
          "  static const char *const Table[]=\n"
          "   {\n"
    
        );
            
  for(auto p=lang.getTRange(); +p ;++p)
    Printf(outCpp,"    \"#;\",\n",SlashQuote(lang,*p));

  Putobj(outCpp,
    
          "    \"...\"\n"
          "   };\n\n"
            
          "  return Table[i];\n"
          " }\n\n"
    
          "const char * GetTextDesc(NTIndex i)\n"
          " {\n"
          "  static const char *const Table[]=\n"
          "   {\n"
    
        );
  
  for(auto p=lang.getTRange(); +p ;++p)
    Printf(outCpp,"    \"#;\",\n",SlashQuote(lang,*p));
  
  for(auto p=lang.getNRange(); +p ;++p)
    Printf(outCpp,"    \"#;\",\n",lang.getTextDesc(*p));
    
  Putobj(outCpp,
  
          "    \"...\"\n"
          "   };\n\n"
    
          "  return Table[i];\n"
          " }\n\n"
    
          "/* struct RuleProp */ \n\n"
            
          "const RuleProp RuleProp::Table[RIndexLim-1]=\n"
          " {\n" 
    
        );
     
  for(auto p=lang.getRRange(RIndexFirst); +p ;++p) 
    {
     RuleRecord rec=lang.getRule(*p);
     
     Printf(outCpp,"  {RIndex(#;),RuleLength(#;),NTIndex(#;),{",*p,rec.str.len,TIndexLim+rec.result);
     
     for(auto q=rec.str; +q ;++q)
       {
        if( q->isNIndex() )
          Printf(outCpp,"NTIndex(#;),",TIndexLim+q->getNIndex());
        else
          Printf(outCpp,"NTIndex(#;),",q->getTIndex());
       }
     
     Putobj(outCpp,"}},\n");
    }

  Putobj(outCpp,
    
          " };\n\n"
            
          "const RuleProp RuleProp::ShiftTable[TIndexLim]=\n"
          " {\n"
    
        );
          
  for(auto p=lang.getTRange(); +p ;++p)
    Printf(outCpp,"  {RIndexShift,RuleLengthZero,NTIndex(#;)},\n",*p);

  Putobj(outCpp,
    
          " };\n\n"
  
          "/* struct State */ \n\n"
            
          "const State State::Table[StateIndexLim]=\n"
          " {\n"
    
        );
  
  DynArray<ulen> finals(TIndexLim);
  DynArray<ulen> transitions(AlphaIndexLim);
          
  for(auto p=Range_const(state_list); +p ;++p) 
    {
     p->fill(Range(finals),Range(transitions));
     
     Putobj(outCpp,
       
             "  {\n"
             "   {\n"
       
           );
     
     for(auto q=Range_const(finals); +q ;++q) Printf(outCpp,"    RIndex(#;),\n",*q);
     
     Putobj(outCpp,
       
             "   },\n"
             "   {\n"
       
           );
     
     auto q=Range_const(transitions);

     Putobj(outCpp,
       
             "    StateIndex(0),\n"
       
           );
      
     ++q;
     ++q;
           
     for(; +q ;++q) Printf(outCpp,"    StateIndex(#;),\n",*q);
     
     Putobj(outCpp,
     
             "   }\n"
             "  },\n"
       
           );
    }
    
  Printf(outCpp,
    
          " };\n\n"
  
          "} // namespace #;\n\n"
            
        ,Name);     
 }
 
void Run::generator()
 {
  StrLen Name=lang.getName();
  ulen RIndexLim=lang.getRIndexLim();
  ulen TIndexLim=lang.getTIndexLim();
  ulen NIndexLim=lang.getNIndexLim();
  
  Estimator<PickRule> pick_rule(lang);
 
  // h-file
 
  PrintFile outH("test/Generator.gen.h");
  
  Printf(outH,
    
          "/* Generator.gen.h */ \n\n"
  
          "##ifndef Generator_gen_h\n"
          "##define Generator_gen_h\n\n"
    
          "##include <CCore/inc/Gadget.h>\n\n" 
          
          "##include \"Parser.gen.h\"\n\n"
          
          "/* lang #; */ \n\n"
          
          "namespace #; {\n\n"
          
          "/* using */ \n\n"
          
          "using CCore::ulen;\n\n"
          
          "/* types */ \n\n"      
          
          "enum RTIndex\n" 
          " {\n" 
          "  RTIndexEnd=0,\n" 
          "  RTIndexRule=TIndexLim,\n" 
          "  RTIndexLim=TIndexLim+RIndexLim\n" 
          " };\n\n"
 
          "inline bool isRule(RTIndex i) { return i>=RTIndexRule; }\n\n"

          "inline RTIndex toRTIndex(TIndex i) { return RTIndex(i); }\n\n"

          "inline RTIndex toRTIndex(RIndex i) { return RTIndex(TIndexLim+i); }\n\n"

          "inline RIndex toRIndex(RTIndex i) { return RIndex(i-RTIndexRule); }\n\n"

          "inline TIndex toTIndex(RTIndex i) { return TIndex(i); }\n\n"

          "inline const char * GetTextDesc(RTIndex i)\n"
          " {\n"
          "  if( isRule(i) ) return GetTextDesc( toRIndex(i) );\n\n"
  
          "  return GetTextDesc( toTIndex(i) );\n"
          " }\n\n"

          "enum NRTIndex\n" 
          " {\n" 
          "  NRTIndexEnd=0,\n" 
          "  NRTIndexRule=RTIndexRule,\n" 
          "  NRTIndexNonTerminal=RTIndexLim,\n" 
          "  NRTIndexLim=NTIndexLim+RIndexLim\n" 
          " };\n\n"

          "inline bool isNonTerminal(NRTIndex i) { return i>=NRTIndexNonTerminal; }\n\n"

          "inline RTIndex toRTIndex(NRTIndex i) { return RTIndex(i); }\n\n"
          
          "/* struct GeneratorProp */ \n\n"
          
          "struct GeneratorProp\n"
          " {\n"
          "  static const NRTIndex StartTable[#;];\n\n"
          
        ,Name
        ,Name
        ,lang.getResult().len);
          
  for(auto p=lang.getRRange(RIndexFirst); +p ;++p)  
    Printf(outH,"  static const NRTIndex Rule_#;[#;];\n",lang.getTextDesc(*p),lang.getRule(*p).str.len+2);

  Putch(outH,'\n');
          
  for(auto p=lang.getNRange(); +p ;++p)  
    Printf(outH,"  static const NRTIndex *const NT_#;[#;];\n",lang.getTextDesc(*p),lang.getRules(*p).len+1);

  Printf(outH,
    
          "\n  struct NTRec\n"  
          "   {\n"
          "    const NRTIndex *const *list;\n"
          "    ulen list_len;\n"
          "   };\n\n"
          
          "  static const NTRec NTable[#;];\n"
          " };\n\n"

          "} // namespace #;\n\n"      
  
          "##endif\n\n"
          
        ,NIndexLim
        ,Name);
          
  // cpp-file        
          
  PrintFile outCpp("test/Generator.gen.cpp");

  Printf(outCpp,
    
          "/* Generator.gen.cpp */ \n\n"
  
          "##include \"Generator.gen.h\"\n\n"
            
          "/* lang #; */ \n\n"
          
          "namespace #; {\n\n"
            
          "/* using */ \n\n"
            
          "using CCore::DimOf;\n\n"
            
          "/* struct GeneratorProp */ \n\n"
            
          "const NRTIndex GeneratorProp::StartTable[#;]=\n"
          " {\n"
            
        ,Name
        ,Name
        ,lang.getResult().len);
            
  for(auto p=lang.getResult(); +p ;++p)          
    Printf(outCpp,"  NRTIndex(NRTIndexNonTerminal+#;),\n",*p);

  Putobj(outCpp," };\n\n");
            
  for(auto p=lang.getRRange(RIndexFirst); +p ;++p)        
    {
     auto str=lang.getRule(*p).str;
     
     Printf(outCpp,
       
             "const NRTIndex GeneratorProp::Rule_#;[#;]=\n" 
             " {\n"
       
           ,lang.getTextDesc(*p),str.len+2);
     
               
     for(auto q=str; +q ;++q)
       if( q->isNIndex() )
         Printf(outCpp,"  NRTIndex(#;),\n",q->getNIndex()+TIndexLim+RIndexLim);
       else
         Printf(outCpp,"  NRTIndex(#;),\n",q->getTIndex());

     Printf(outCpp,
       
             "  NRTIndex(#;),\n"
             "  NRTIndexEnd\n"
             " };\n\n"
       
           ,*p+TIndexLim);
    }
    
  for(auto p=lang.getNRange(); +p ;++p)        
    {
     auto rules=lang.getRules(*p);
     
     Printf(outCpp,
       
             "const NRTIndex *const GeneratorProp::NT_#;[#;]=\n"
             " {\n" 
       
           ,lang.getTextDesc(*p),rules.len+1);
               
     Printf(outCpp,"  Rule_#;,\n",lang.getTextDesc(pick_rule.get(*p).getRule()));
     
     for(auto p=rules; +p ;++p)
       Printf(outCpp,"  Rule_#;,\n",lang.getTextDesc(p->rule));

     Putobj(outCpp," };\n\n");
    }
    
  Printf(outCpp,
    
          "const GeneratorProp::NTRec GeneratorProp::NTable[#;]=\n" 
          " {\n"
    
        ,NIndexLim);
  
  for(auto p=lang.getNRange(); +p ;++p)
    {
     auto desc=lang.getTextDesc(*p);
     
     Printf(outCpp,"  {NT_#;,DimOf(NT_#;)},\n",desc,desc);
    }
            
  Printf(outCpp,
    
          " };\n\n"
     
          "} // namespace #;\n\n"
    
        ,Name);
 } 

Run::Run(const Lang &lang_) 
 : lang(lang_),
   punct(lang),
   out("Result.txt")
 {
  Putobj(out,"/* Result.txt */ \n\n");
 }

Run::~Run()
 {
 }
   
int Run::run(StrLen CCORE_Root,bool ext_out)
 {
  Putobj(Con,"Start...\n\n");
 
  if( !sanity<IsolatedTest>() ) return 1;
  
  if( !sanity<NonEmptyTest>() ) return 1;
  
  puncture(ext_out);
  
  way(ext_out);
  
  compression();
  
  if( nonLR1() )
    {
     stateDDL(true);
     
     Putobj(Con,"\nfailure\n\n");
    
     return 1;
    }
    
  stateDDL(false);

  test(CCORE_Root);
  
  parser();  
  
  generator();
  
  Putobj(Con,"\nsuccess\n\n");

  return 0;
 }

} // namespace App

