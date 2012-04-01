/* DataMap.h */
//----------------------------------------------------------------------------------------
//
//  Project: ParserGen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ParserGen_DataMap_h
#define ParserGen_DataMap_h

#include <CCore/inc/ddl/DDLTypeDesc.h>

#include <CCore/inc/PrintSet.h>

namespace App {

/* using */

using namespace CCore;

using DDL::DataPtr;
using DDL::ArrayPtr;

/* types */

typedef DDL::imp_uint NIndex;
typedef DDL::imp_uint TIndex;
typedef DDL::imp_uint RIndex;
typedef DDL::imp_uint NTIndex;
typedef DDL::imp_uint StateIndex;

/* classes */

struct Rule;

struct NonTerminal;

struct State;

class DataMap;

/* struct Rule */

struct Rule
 {
  RIndex rule;
  StrLen name;
  NIndex result;
  PtrLen<NTIndex> str;
  
  Rule() {}
  
  Rule(const DDL::TypeDesc_struct<4> &desc,DataPtr ptr) 
   {
    rule=*ptr.select(desc,0);
    name=*ptr.select(desc,1);
    result=*ptr.select(desc,2);
    str=*ptr.select(desc,3);
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"{#;,#;,#;,#;}",rule,name,result,PrintSet(str));
   }
 };

/* struct NonTerminal */

struct NonTerminal
 {
  NIndex nt;
  StrLen name;
  PtrLen<DataPtr> rules; // Rule *
  
  NonTerminal() {}
  
  NonTerminal(const DDL::TypeDesc_struct<3> &desc,DataPtr ptr) 
   {
    nt=*ptr.select(desc,0);
    name=*ptr.select(desc,1);
    rules=*ptr.select(desc,2);
   }
  
  template <class P,class Data>
  void print(P &out,const Data &data) const
   {
    Printf(out,"{#;,#;}",nt,name);
    
    for(DataPtr ptr : rules ) Printf(out,"\n  #;",data.getRule(ptr));
    
    Putch(out,'\n');
   }
 };

/* struct State */

struct State
 {
  StateIndex state;

  struct Transition 
   { 
    NTIndex ntt; 
    DataPtr state; // State *
    
    Transition() {}
    
    Transition(const DDL::TypeDesc_struct<2> &desc,DataPtr ptr) 
     {
      ntt=*ptr.select(desc,0);
      state=*ptr.select(desc,1);
     }
    
    template <class P,class Data>
    void print(P &out,const Data &data) const
     {
      Printf(out,"\n  {#;} -> #;",ntt,data.getState(state).state);
     }
   };
  
  ArrayPtr transitions;

  struct Final 
   { 
    TIndex t; 
    DataPtr rule; // Rule *
    
    Final() {}
    
    Final(const DDL::TypeDesc_struct<2> &desc,DataPtr ptr) 
     {
      t=*ptr.select(desc,0);
      rule=*ptr.select(desc,1);
     }
    
    template <class P,class Data>
    void print(P &out,const Data &data) const
     {
      Printf(out,"\n  {#;} => #;",t,data.getRule(rule).name);
     }
   };
  
  ArrayPtr finals;
  
  State() {}
  
  State(const DDL::TypeDesc_struct<3> &desc,DataPtr ptr)
   {
    state=*ptr.select(desc,0);
    
    transitions=*ptr.select(desc,1);
    finals=*ptr.select(desc,2);
   }
  
  template <class P,class Data>
  void print(P &out,const Data &data) const
   {
    Printf(out,"{#;}",state);

    for(ulen i=0; i<transitions.len ;i++) data.getTransition(transitions.ptr,i).print(out,data);
    
    for(ulen i=0; i<finals.len ;i++) data.getFinal(finals.ptr,i).print(out,data);
    
    Putch(out,'\n');
   }
 };

/* class DataMap */

class DataMap : NoCopy
 {
  private:
  
   DDL::TypeDesc_basic desc_NIndex;
   DDL::TypeDesc_basic desc_TIndex;
   DDL::TypeDesc_basic desc_RIndex;
   DDL::TypeDesc_basic desc_NTIndex;
   DDL::TypeDesc_basic desc_StateIndex;
   DDL::TypeDesc_basic desc_text;
   
   DDL::TypeDesc_ptr desc_State_ptr;
  
   DDL::TypeDesc_struct<2> desc_Transition;
   
   DDL::TypeDesc_ptr desc_Rule_ptr;
   
   DDL::TypeDesc_struct<2> desc_Final;
   
   DDL::TypeDesc_array desc_Transition_array;
   DDL::TypeDesc_array desc_Final_array;
   
   DDL::TypeDesc_struct<3> desc_State;
   
   DDL::TypeDesc_array desc_NTIndex_array;
   
   DDL::TypeDesc_struct<4> desc_Rule;
   
   DDL::TypeDesc_array desc_Rule_ptr_array;
   
   DDL::TypeDesc_struct<3> desc_NonTerminal;
   
   DDL::TypeDesc_array_getlen desc_StateTable;
   DDL::TypeDesc_array_getlen desc_NonTerminalTable;
   DDL::TypeDesc_array_getlen desc_RuleTable;
   DDL::TypeDesc_array_getlen desc_TNames;
  
  private:
  
   void *mem;
   
   DataPtr table_State;
   DataPtr table_NonTerminal;
   DataPtr table_Rule;
   DataPtr table_TNames;
 
  public:
  
   explicit DataMap(StrLen file_name);
   
   ~DataMap();
   
   // TNames
   
   PtrLen<StrLen> getTNames() const { return table_TNames.range(desc_TNames.len); }
   
   // Rules
   
   ulen getRuleCount() const { return desc_RuleTable.len; }
   
   Rule getRule(DataPtr ptr) const
    {
     return Rule(desc_Rule,ptr);
    }
   
   Rule getRule(ulen ind) const
    {
     return getRule(table_Rule.elem(desc_Rule,ind));
    }
   
   // NonTerminals
   
   ulen getNonTerminalCount() const { return desc_NonTerminalTable.len; }
   
   NonTerminal getNonTerminal(DataPtr ptr) const 
    {
     return NonTerminal(desc_NonTerminal,ptr);
    }
   
   NonTerminal getNonTerminal(ulen ind) const 
    { 
     return getNonTerminal(table_NonTerminal.elem(desc_NonTerminal,ind)); 
    }
   
   // State
   
   ulen getStateCount() const { return desc_StateTable.len; }
   
   State getState(DataPtr ptr) const
    {
     return State(desc_State,ptr);
    }
   
   State getState(ulen ind) const
    {
     return getState(table_State.elem(desc_State,ind));
    }
   
   // State::Final
   
   State::Final getFinal(DataPtr ptr) const
    {
     return State::Final(desc_Final,ptr);
    }
   
   State::Final getFinal(DataPtr base,ulen ind) const
    {
     return getFinal(base.elem(desc_Final,ind));
    }
   
   // State::Transition
   
   State::Transition getTransition(DataPtr ptr) const
    {
     return State::Transition(desc_Transition,ptr);
    }
   
   State::Transition getTransition(DataPtr base,ulen ind) const
    {
     return getTransition(base.elem(desc_Transition,ind));
    }
 };

} // namespace App

#endif

