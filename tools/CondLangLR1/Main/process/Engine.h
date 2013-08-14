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

template <class Estimate> struct MakeContext;

template <class Estimate> class Engine;

/* struct MakeContext<Estimate> */

template <class Estimate> 
struct MakeContext : Estimate::Context
 {
  explicit MakeContext(const ExtLang &) {}
 };

template <>
struct MakeContext<LR1Estimate> 
 {
  ulen atom_count;
  
  explicit MakeContext(const ExtLang &lang) : atom_count(lang.getOriginalAtomCount()) {}
  
  operator ulen() const { return atom_count; } 
 };

/* class Engine<Estimate> */

template <class Estimate>
class Engine : NoCopy
 {
   ExtLang ext_lang;
   LangStateMachine<Estimate> machine;
   StateCompress<Estimate> compress;
   StateTrace trace;
   
  private:
   
   template <class P>
   void printElement(P &out,ulen element) const
    {
     ulen atom_count=compress.getAtomCount();
  
     if( element<atom_count )
       Putobj(out,ext_lang.getAtoms()[element].name);
     else
       Putobj(out,ext_lang.getSynts()[element-atom_count].name);
    }
   
   template <class P>
   void printTrace(P &out,Trace trace) const
    {
     if( trace.ok )
       {
        for(ulen element : trace.trace )
          {
           Putch(out,' ');
           
           printElement(out,element);
          }
       }
     else
       {
        Putobj(out," NO-TRACE");
       }
    }
   
   template <class P,class T>
   void printState(P &out,ulen index,const T &trace_table) const
    {
     Printf(out,"( #; ,",index);
     
     printTrace(out,trace_table[index]);
     
     Putobj(out," )");
    }
   
  public:
 
   explicit Engine(const Lang &lang)
    : ext_lang(lang),
      machine(ext_lang,MakeContext<Estimate>(ext_lang)),
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
     
     // state table
     
     Printf(out,"#;\n",Title("States"));
     
     ulen state_count=compress.getStateTable().len;
     
     DynArray<Trace> trace_table(state_count);
     
     for(ulen i=0; i<state_count ;i++) trace_table[i]=trace[i];
     
     for(auto p=compress.getStateTable(); +p ;++p)
       {
        Putch(out,'\n');
        
        printState(out,p->index,trace_table);
        
        Printf(out," = #;\n\n",p->estimate_index);
        
        for(auto &t : p->transitions )
          {
           Putobj(out,"  ");
           
           printElement(out,t.element);
           
           Putobj(out," -> ");
           
           printState(out,t.dst->index,trace_table);
           
           Putobj(out,"\n\n");
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
        Putch(out,'\n');
       
        p->printBlock(out,index);
        
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
