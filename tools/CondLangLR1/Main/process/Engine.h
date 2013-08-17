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

struct PrintState;

/* struct PrintState */

struct PrintState
 {
  ulen index;
  Trace trace;
  
  // constructors
  
  PrintState(ulen index_,const DynArray<Trace> &trace_table) : index(index_),trace(trace_table[index_]) {}
  
  // print object
  
  using PrintOptType = ExtLangOpt ;
  
  template <class P>
  void print(P &out,ExtLangOpt opt) const
   {
    Printf(out,"( #; ; #; )",index,BindOpt(opt,trace));
   }
 };

/* PrintCompress() */

template <class P,class Compress>
void PrintCompress(P &out,const ExtLang &ext_lang,const Compress &compress,const StateTrace &trace)
 {
  ExtLangOpt opt(ext_lang,compress.getAtomCount());
  
  Printf(out,"#;\n",Title("States"));
  
  ulen state_count=compress.getStateCount();
  
  DynArray<Trace> trace_table(state_count);
  
  for(ulen i=0; i<state_count ;i++) trace_table[i]=trace[i];
  
  for(auto p=compress.getStateTable(); +p ;++p)
    {
     Printf(out,"\n#; = #;\n\n",BindOpt(opt,PrintState(p->index,trace_table)),p->prop_index);
     
     for(auto &t : p->transitions )
       {
        Printf(out,"  #; -> #;\n\n",opt[t.element],BindOpt(opt,PrintState(t.dst->index,trace_table)));
       }
    
     if( p.len>1 )
       Putobj(out,"-----\n");
     else
       Printf(out,"#;\n",Title("Estimates"));
    }
  
  // properties 
  
  ulen index=0;
  
  for(auto p=compress.getProps(); +p ;++p)
    {
     Printf(out,"\n#;) #.b;",index,*p);
     
     index++;
     
     if( p.len>1 )
       Putobj(out,"\n-----\n");
     else
       Printf(out,"\n#;\n",TextDivider());
    }
 }

} // namespace App

#endif
