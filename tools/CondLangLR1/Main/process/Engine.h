/* Engine.h */
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

#ifndef CondLangLR1_process_Engine_h
#define CondLangLR1_process_Engine_h

#include "StateTrace.h"

namespace App {

/* classes */

template <class Estimate> class Engine;

/* class Engine<Estimate> */

template <class Estimate>
class Engine : NoCopy
 {
   ExtLang ext_lang;
   LangStateMachine<Estimate> machine;
   StateCompress<Estimate> compress;
   StateTrace trace;
   
  private:
   
   using Context = typename Estimate::Context ; 
   
   struct PrintState
    {
     ulen index;
     const DynArray<Trace> &trace_table;
     
     // constructors
     
     PrintState(ulen index_,const DynArray<Trace> &trace_table_) : index(index_),trace_table(trace_table_) {}
     
     // print object
     
     using PrintOptType = ExtLangOpt ;
     
     template <class P>
     void print(P &out,ExtLangOpt opt) const
      {
       Printf(out,"( #; ; #; )",index,BindOpt(opt,trace_table[index]));
      }
    };
   
  public:
 
   template <class ... TT>
   explicit Engine(const Lang &lang,TT && ... tt)
    : ext_lang(lang),
      machine(ext_lang,Context(ext_lang, std::forward<TT>(tt)... )),
      compress(machine),
      trace(compress)
    {
    }
   
   ~Engine() 
    {
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;\n",ext_lang);
     
     //Printf(out,"#;\n",BindOpt(LangOpt(ext_lang),machine));
     //Printf(out,"#;\n",BindOpt(LangOpt(ext_lang),compress));
     
     // state table
     
     ExtLangOpt opt(ext_lang,compress.getAtomCount());
     
     Printf(out,"#;\n",Title("States"));
     
     ulen state_count=compress.getStateTable().len;
     
     DynArray<Trace> trace_table(state_count);
     
     for(ulen i=0; i<state_count ;i++) trace_table[i]=trace[i];
     
     for(auto p=compress.getStateTable(); +p ;++p)
       {
        Printf(out,"\n#; = #;\n\n",BindOpt(opt,PrintState(p->index,trace_table)),p->estimate_index);
        
        for(auto &t : p->transitions )
          {
           Printf(out,"  #; -> #;\n\n",opt[t.element],BindOpt(opt,PrintState(t.dst->index,trace_table)));
          }
       
        if( p.len>1 )
          Putobj(out,"-----\n");
        else
          Printf(out,"#;\n",Title("Estimates"));
       }
     
     // estimates 
     
     ulen index=0;
     
     for(auto p=compress.getEstimates(); +p ;++p)
       {
        Printf(out,"\n#;) #.b;",index,*p);
        
        index++;
        
        if( p.len>1 )
          Putobj(out,"\n-----\n");
        else
          Printf(out,"\n#;\n",TextDivider());
       }
    }
 };

} // namespace App

#endif
