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

namespace App {

/* classes */

struct ExtLangOpt;

struct StateCompressBase;

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
    PtrLen<const Transition> transitions;
    
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
   
  private: 
   
   using Desc = typename LangStateMachine<Estimate>::StateDesc ; 
    
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
   
   template <class Machine,class ... TT>
   explicit StateCompress(const Machine &machine,const TT & ... tt);
   
   ~StateCompress() {}
   
   // description
   
   PtrLen<const StateDesc> getStateTable() const { return Range_const(state_table); }
   
   PtrLen<const EstProp> getProps() const { return Range_const(prop_buf); }
   
   ulen getAtomCount() const { return atom_count; }
   
   ulen getElementCount() const { return element_count; }
   
   // print object
   
   using PrintOptType = LangOpt ;
   
   template <class P>
   void print(P &out,LangOpt opt) const
    {
     Putobj(out,"-----\n");
     
     Printf(out,"atoms = #; elements = #;\n",getAtomCount(),getElementCount());
     
     opt.lang.applyForAtoms(getAtomCount(), [&] (Atom atom) { Printf(out,"#; ",atom.getName()); } );
     
     opt.lang.applyForSynts( [&] (Synt synt) { Printf(out,"#; ",synt.getName()); } );
     
     Putobj(out,"\n-----\n");
     
     for(auto &state : getStateTable() )
       {
        Putobj(out,BindOpt(ExtLangOpt(opt.lang,getAtomCount()),state),"-----\n");
       }
     
     ulen index=0;
     
     for(auto &prop : getProps() )
       {
        Printf(out,"#;) #;\n",index,prop);
        
        Putobj(out,"-----\n");
        
        index++;
       }
    }
 };

template <class Estimate,class EstProp> 
template <class Machine,class ... TT>
StateCompress<Estimate,EstProp>::StateCompress(const Machine &machine,const TT & ... tt)
 {
  atom_count=machine.getAtomCount();
  element_count=machine.getElementCount();
  
  auto table=machine.getStateTable();
  
  DynArray<EstProp> props(DoReserve,table.len);
  
  for(auto &t : table )
    {
     props.append_fill(t.est,tt...);
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
 }

} // namespace App

#endif
