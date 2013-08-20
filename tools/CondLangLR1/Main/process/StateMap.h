/* StateMap.h */
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

#ifndef CondLangLR1_process_StateMap_h
#define CondLangLR1_process_StateMap_h

#include "StateCompress.h"

namespace App {

/* functions */

void GuardNoTrace();

inline void GuardTrace(bool ok)
 {
  if( !ok ) GuardNoTrace();
 }

void GuardBrokenMap(ulen state,ulen element);

/* classes */

class StateMap;

/* class StateMap */

class StateMap : NoCopy
 {
   DynArray<State> map;
   
   DynArray<State> top_buf;
   DynArray<PtrLen<const State> > fibres;
   
  private:
   
   bool test(State top,State bottom) const
    {
     if( +top )
       {
        return (*this)[top]==bottom;
       }
     else
       {
        return !bottom;
       }
    }
   
   struct Rec : NoThrowFlagsBase
    {
     State top;
     State bottom;
     
     Rec(State top_,State bottom_) : top(top_),bottom(bottom_) {}
    };
   
  public:
  
   template <class FromCompress,class ToCompress>
   StateMap(const FromCompress &from,ToCompress &to);
   
   ~StateMap() {}
   
   State operator [] (State state) const { return map[state.getIndex()]; }
   
   PtrLen<const State> getFibre(State state) const { return fibres[state.getIndex()]; }
   
   PtrLen<const State> getNullFibre() const { return fibres[fibres.getLen()-1]; }
 };

template <class FromCompress,class ToCompress>
StateMap::StateMap(const FromCompress &from,ToCompress &to)
 : map(from.getStateCount())
 {
  // build
  
  from.applyForStates( [&] (State state) 
                           {
                            Trace trace=from.buildTrace(state);
    
                            GuardTrace(trace.ok);
    
                            State dst=to.getStart();
    
                            for(ulen element : trace.trace )
                              {
                               dst=dst.find(element);

                               if( !dst ) break;
                              }
    
                            map[state.getIndex()]=dst;  
                           } 
                     );
  
  // check

  from.applyForStates( [&] (State state) 
                           {
                            State dst=(*this)[state];
                            
                            if( +dst )
                              {
                               for(ulen element=0,len=from.getElementCount(); element<len ;element++)
                                 {
                                  State top=state.find(element);
                                  State bottom=dst.find(element);
                                  
                                  if( !test(top,bottom) ) GuardBrokenMap(state.getIndex(),element);
                                 }
                              }
                            else
                              {
                               for(auto &trans : state.getTransitions() )
                                 {
                                  State bottom=(*this)[trans.dst];
                                  
                                  if( +bottom ) GuardBrokenMap(state.getIndex(),trans.element);
                                 }
                              }
                           } 
                     );
  
  // fibres
  
  DynArray<Rec> buf(DoReserve,from.getStateCount());
   
  from.applyForStates( [&] (State state) { buf.append_fill(state,(*this)[state]); } );
  
  DynArray<State> top_buf(DoReserve,from.getStateCount());
  
  DynArray<PtrLen<const State> > fibres(LenAdd(to.getStateCount(),1));
  
  ulen null_index=to.getStateCount();
  
  Algon::IncrSortThenApplyUniqueRangeBy(Range(buf), [] (const Rec &rec) { return rec.bottom; } , 
                                                    [&] (PtrLen<Rec> range) 
                                                        {
                                                         for(auto &rec : range ) top_buf.append_copy(rec.top);
                                                         
                                                         ulen index=range->bottom.getExtIndex();
                                                         
                                                         if( index==MaxULen ) index=null_index;
                                                         
                                                         fibres[index].len=range.len;
                                                        } 
                                       );

  State *ptr=top_buf.getPtr();
  
  for(auto &p : fibres )
    {
     ulen len=p.len;
     
     p.ptr=ptr;
     
     Sort(ptr,len);
     
     ptr+=len;
    }
  
  Swap(top_buf,this->top_buf);
  Swap(fibres,this->fibres);
 }

} // namespace App

#endif
