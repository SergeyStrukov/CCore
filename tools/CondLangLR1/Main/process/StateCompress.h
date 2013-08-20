/* StateCompress.h */
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

#ifndef CondLangLR1_process_StateCompress_h
#define CondLangLR1_process_StateCompress_h

#include "LangStateMachine.h"

#include <CCore/inc/algon/SortUnique.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* classes */

struct ExtLangOpt;

struct StateCompressBase;

struct State;

struct Trace;

class StateTrace;

struct PrintState;

struct PrintCompressCounts;

template <class Estimate,class EstProp=Estimate> class StateCompress;

/* struct ExtLangOpt */

struct ExtLangOpt
 {
  const Lang &lang;
  ulen atom_count;
  
  ExtLangOpt(const Lang &lang_,ulen atom_count_) : lang(lang_),atom_count(atom_count_) {}
  
  StrLen operator [] (ulen element) const
   {
    if( element<atom_count )
      return lang.getAtoms()[element].name;
    else
      return lang.getSynts()[element-atom_count].name;
   }
 };

/* struct StateCompressBase */

struct StateCompressBase : NoCopy
 {
  struct StateDesc;
  
  struct Transition : NoThrowFlagsBase
   {
    ulen element;
    const StateDesc *dst;
    
    Transition(ulen element_,const StateDesc *dst_) : element(element_),dst(dst_) {}
   };
  
  struct StateDesc : NoCopy , NoThrowFlagsBase
   {
    ulen index;
    ulen prop_index;
    PtrLen<const Transition> transitions; // strictly ordered by element
    
    const StateDesc * find(ulen element) const
     {
      auto r=transitions;
      
      Algon::BinarySearch_if(r, [=] (const Transition &t) { return t.element>=element; } );
      
      if( +r && r->element==element ) return r->dst;
      
      return 0;
     }
    
    // print object
    
    using PrintOptType = ExtLangOpt ;
    
    template <class P>
    void print(P &out,ExtLangOpt opt) const
     {
      Printf(out,"#;) #;\n",index,prop_index);
      
      for(auto &trans : transitions ) Printf(out,"  #3; -> #3;",opt[trans.element],trans.dst->index);
      
      Putch(out,'\n');
     }
   };
 };

/* struct State */

struct State : CmpComparable<State> , NoThrowFlagsBase
 {
  const StateCompressBase::StateDesc *desc;
  
  // constructors
  
  State() : desc(0) {}
  
  State(const StateCompressBase::StateDesc *desc_) : desc(desc_) {}
  
  // properties
  
  bool operator + () const { return desc!=0; }
  
  bool operator ! () const { return desc==0; }
  
  ulen getIndex() const { return desc->index; }
  
  ulen getPropIndex() const { return desc->prop_index; }
  
  PtrLen<const StateCompressBase::Transition> getTransitions() const { return desc->transitions; }
  
  State find(ulen element) const { return desc->find(element); }
  
  // cmp objects
  
  ulen getExtIndex() const { return desc?desc->index:MaxULen; }
  
  CmpResult objCmp(State obj) const { return LessCmp(getExtIndex(),obj.getExtIndex()); }
 };

/* struct Trace */

struct Trace : NoThrowFlagsBase 
 {
  bool ok;
  RefArray<ulen> trace;
  
  // constructors
  
  Trace() : ok(false) {}
  
  Trace(RefArray<ulen> trace_) : ok(true),trace(trace_) {}
  
  // print object
  
  using PrintOptType = ExtLangOpt ;
  
  template <class P>
  void print(P &out,ExtLangOpt opt) const
   {
    if( ok )
      {
       auto p=Range(trace);
       
       if( +p )
         {
          Putobj(out,opt[*p]);
          
          for(++p; +p ;++p)
            {
             Putch(out,' ');
             Putobj(out,opt[*p]);
            }
         }
       else
         {
          Putobj(out,"NULL");
         }
      }
    else
      {
       Putobj(out,"NO-TRACE");
      }
   }
 };

/* class StateTrace */

class StateTrace : NoCopy
 {
   using Desc = StateCompressBase::StateDesc ;
  
   struct BackTrace : NoCopy , NoThrowFlagsBase
    {
     bool ok;
     
     const BackTrace *from;
     ulen element;
     ulen len;
     
     BackTrace() : ok(false) {}
     
     void start()
      {
       ok=true;
       len=0;
      }
     
     bool setCmp(const BackTrace *from_,ulen element_)
      {
       if( ok ) return false;
       
       ok=true;
       from=from_;
       element=element_;
       len=LenAdd(from_->len,1);
       
       return true;
      }

     Trace build() const;
    };
   
  private: 
  
   DynArray<BackTrace> trace;
   
  public:

   StateTrace() {}
   
   ~StateTrace() {}
   
   // methods
   
   void create(PtrLen<const Desc> table);
   
   Trace build(ulen index) const { return trace[index].build(); }
 };

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

/* struct PrintCompressCounts */

struct PrintCompressCounts
 {
  ulen state_count;
  ulen prop_count;
  
  // constructors
  
  template <class Compress>
  PrintCompressCounts(const Compress &compress) 
   : state_count(compress.getStateCount()),prop_count(compress.getPropCount()) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"State count = #; Prop count = #;",state_count,prop_count);
   }
 };

/* class StateCompress<Estimate,EstProp> */

template <class Estimate,class EstProp> 
class StateCompress : public StateCompressBase
 {
  private:
   
   DynArray<StateDesc> state_table;
   DynArray<EstProp> prop_buf;
   DynArray<Transition> transition_buf;
   
   ulen atom_count;
   ulen element_count;
   
   StateTrace trace;
   
  private: 
   
   using Desc = StateMachineDesc<Estimate> ; 
    
   struct ToCmp : CmpComparable<ToCmp>
    {
     ulen num;
     PtrLen<const Desc *> transitions;
     const ulen *num_table;
     
     ToCmp(ulen index,const Desc &desc,const ulen *num_table_)
      : num(num_table_[index]),
        transitions(desc.transitions),
        num_table(num_table_)
      {
      }
     
     CmpResult objCmp(const ToCmp &obj) const
      {
       if( auto ret=Cmp(num,obj.num) ) return ret;
       
       ulen count=transitions.len;
       
       for(ulen i=0; i<count ;i++)
         {
          if( auto ret=Cmp(num_table[transitions[i]->index],num_table[obj.transitions[i]->index]) ) return ret;
         }
       
       return CmpEqual;
      }
    };
   
   static void SwapNum(ulen &x,ulen a,ulen b)
    {
     if( x==a ) x=b; else if( x==b ) x=a;
    }
   
   static void SkipError(ulen &x,ulen error)
    {
     if( x==error ) x=MaxULen; else if( x>error ) x--;
    }
   
  public: 
   
   template <class Machine,class ... SS>
   explicit StateCompress(const Machine &machine,const SS & ... ss);
   
   ~StateCompress() {}
   
   // description
   
   PtrLen<const StateDesc> getStateTable() const { return Range_const(state_table); }
   
   ulen getStateCount() const { return state_table.getLen(); }
   
   PtrLen<const EstProp> getProps() const { return Range_const(prop_buf); }
   
   ulen getPropCount() const { return prop_buf.getLen(); }
   
   ulen getAtomCount() const { return atom_count; }
   
   ulen getElementCount() const { return element_count; }
   
   State getStart() const { return State(state_table.getPtr()); } 
   
   // apply
   
   template <class FuncInit>
   void applyForStates(FuncInit func_init) const // func(State)
    {
     ApplyToDesc(getStateTable(),func_init);
    }
   
   // trace
   
   Trace buildTrace(ulen index) const { return trace.build(index); }
   
   Trace buildTrace(State state) const { return trace.build(state.getIndex()); }
   
   // print object
   
   using PrintOptType = LangOpt ;
   
   template <class P>
   void print(P &out,LangOpt opt) const
    {
     ExtLangOpt extopt(opt.lang,getAtomCount());
     
     Printf(out,"#;\n",Title("States"));
     
     ulen state_count=getStateCount();
     
     DynArray<Trace> trace_table(state_count);
     
     for(ulen i=0; i<state_count ;i++) trace_table[i]=buildTrace(i);
     
     for(auto p=getStateTable(); +p ;++p)
       {
        Printf(out,"\n#; = #;\n\n",BindOpt(extopt,PrintState(p->index,trace_table)),p->prop_index);
        
        for(auto &t : p->transitions )
          {
           Printf(out,"  #; -> #;\n\n",extopt[t.element],BindOpt(extopt,PrintState(t.dst->index,trace_table)));
          }
       
        if( p.len>1 )
          Putobj(out,"-----\n");
        else
          Printf(out,"#;\n",Title("Properties"));
       }
     
     // properties 
     
     ulen index=0;
     
     for(auto p=getProps(); +p ;++p)
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

template <class Estimate,class EstProp> 
template <class Machine,class ... SS>
StateCompress<Estimate,EstProp>::StateCompress(const Machine &machine,const SS & ... ss)
 {
  atom_count=machine.getAtomCount();
  element_count=machine.getElementCount();
  
  auto table=machine.getStateTable();
  
  DynArray<EstProp> props(DoReserve,table.len);
  
  for(auto &t : table )
    {
     props.append_fill(t.est, std::forward<SS>(ss)... );
    }
  
  DynArray<ulen> initial_num;
  
  DynArray<ulen> num_buf(table.len);
  DynArray<ulen> ind_buf(table.len);
  DynArray<ulen> temp(table.len);
  
  ulen num_count;
  
  //--------------------------------------------------------------------------
  
  TrackStage("Initial numbering");
  
  {
   auto ind=Range(ind_buf); 
    
   for(ulen i=0; i<table.len ;i++) ind[i]=i; 
   
   ulen *result=num_buf.getPtr();
   
   ulen count=0;
   
   prop_buf.reserve(table.len);
   
   Algon::IncrSortThenApplyUniqueRangeBy(ind, [&] (ulen i) { return props[i]; } , 
                                              [&] (PtrLen<ulen> r) 
                                                  {
                                                   prop_buf.append_copy(props[*r]);
                                                   
                                                   for(; +r ;++r) result[*r]=count;
                                                  
                                                   count++;
                                                  } 
                                        );
   
   num_buf.cloneTo(initial_num);
   
   num_count=count;
  }
  
  //--------------------------------------------------------------------------
  
  {
   for(ulen i=0; i<num_count ;i++)
     if( !prop_buf[i] )
       {
        ulen j=num_count-1;
        
        if( i!=j )
          {
           Swap(prop_buf[i],prop_buf[j]);
           
           for(ulen &x : initial_num ) SwapNum(x,i,j);
          }
       
        break;
       }
  }
  
  //--------------------------------------------------------------------------
  
  TrackStage("Refine numbering");
  
  {
   TrackStep track;
   
   ulen count;
   
   do
     {
      auto ind=Range(ind_buf); 
      
      for(ulen i=0; i<table.len ;i++) ind[i]=i;
      
      ulen *num_table=num_buf.getPtr();
      ulen *result=temp.getPtr();
      
      count=0;
      
      Algon::IncrSortThenApplyUniqueRangeBy(ind, [=] (ulen i) { return ToCmp(i,table[i],num_table); } , 
                                                 [&] (PtrLen<ulen> r) 
                                                     {
                                                      for(; +r ;++r) result[*r]=count;
                                                     
                                                      count++;
                                                     } 
                                           );

      Swap(temp,num_buf);
      
      track.step();
     }
   while( SetCmp(num_count,count) );
    
   track.finish();
  }
  
  //--------------------------------------------------------------------------
  
  {
   auto num=Range(num_buf); 
   
   if( ulen n=num[0] )
     {
      num[0]=0;
      
      for(++num; +num ;++num) SwapNum(*num,0,n);
     }
  }
  
  //--------------------------------------------------------------------------
  
  ulen error=MaxULen;
  
  {
   auto num=Range(num_buf);
   
   for(ulen i=0; i<table.len ;i++)
     {
      auto &desc=table[i];
      
      if( !props[i] )
        {
         ulen n=num[i];
         bool ok=true;
         
         for(auto *dst : desc.transitions ) 
           if( num[dst->index]!=n ) 
             {
              ok=false;
              
              break;
             }

         if( ok )
           {
            error=n;
           
            break;
           }
        }
     }
  }
  
  //--------------------------------------------------------------------------
  
  if( error!=MaxULen && error!=0 )
    {
     for(ulen &x : num_buf ) SkipError(x,error);
     
     num_count--;
    }
  
  //--------------------------------------------------------------------------

  DynArray<ulen> map(num_count);
  
  {
   auto num=Range(num_buf);
    
   for(ulen i=0; i<table.len ;i++)
     {
      ulen n=num[i];
       
      if( n<num_count ) map[n]=i;
     }
  }
  
  //--------------------------------------------------------------------------

  {
   DynArray<StateDesc> state_table(num_count);
   Collector<Transition> tbuf;
   
   ulen last_prop=prop_buf.getLen()-1;
   bool drop_null=true;
   
   for(ulen i=0; i<num_count ;i++)
     {
      ulen index=map[i];
      auto &desc=table[index];
      
      state_table[i].index=i;
      
      ulen prop_index=initial_num[index];
      
      if( prop_index==last_prop ) drop_null=false;
      
      state_table[i].prop_index=prop_index;
      
      ulen element=0;
      ulen len=0;
      
      for(auto *dst : desc.transitions )
        {
         ulen n=num_buf[dst->index];
         
         if( n<num_count )
           {
            tbuf.append_fill(element,state_table.getPtr()+n);
            
            len++;
           }
        
         element++;
        }
      
      state_table[i].transitions.len=len;
     }
   
   tbuf.extractTo(transition_buf);
   
   Transition *ptr=transition_buf.getPtr();
   
   for(ulen i=0; i<num_count ;i++)
     {
      ulen len=state_table[i].transitions.len;
     
      state_table[i].transitions.ptr=ptr;
      
      ptr+=len;
     }
   
   Swap(state_table,this->state_table);
   
   if( drop_null ) prop_buf.shrink_one();
  }
  
  prop_buf.shrink_extra();
  
  trace.create(getStateTable());
 }

} // namespace App

#endif
