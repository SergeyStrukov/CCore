/* State.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_State_h
#define LangLR1_State_h

#include "Sequence.h"
#include "MatrixRec.h"

namespace App {

/* classes */

class State;

/* class State */ 

class State
 {
   ulen number;
   TransitionSet transitions;
   FinalSet finals;
   
   enum WayFlag
    {
     NoWay,
     HasWay,
     HasWayOut
    };
   
   WayFlag way_flag;
   Sequence<AlphaIndex> way;
   
   ulen final_number;
   ulen group_number;
   ulen new_group_number;
   
  public:
  
   State()
    : number(0),
      way_flag(NoWay),
      final_number(0),
      group_number(0),
      new_group_number(0) 
    {
    }
   
   State(ulen number_,const TransitionSet &transitions_,const FinalSet &finals_)
    : number(number_),
      transitions(transitions_),
      finals(finals_),
      way_flag(NoWay),
      final_number(0),
      group_number(0),
      new_group_number(0) 
    {
    }
   
   // props
    
   ulen getNumber() const { return number; }
   
   const TransitionSet & getTransitions() const { return transitions; }
    
   const FinalSet & getFinals() const { return finals; }
   
   // way 
    
   void setHasWay() { way_flag=HasWay; }
    
   bool wayout(State *base);
   
   // final number
   
   void setFinalNumber(ulen final_number_) { group_number=final_number=final_number_; }
   
   ulen getFinalNumber() const { return final_number; }
   
   // group number
   
   void setGroupNumber(ulen number) { new_group_number=number; }
   
   void updateGroupNumber() { group_number=new_group_number; }
   
   bool isSelected() const { return number==group_number; }
   
   void propagateGroupNumber(const State *base);
   
   void update(const State *base);
   
   // group cmp
   
   CmpResult groupCmp(const State *base,const State &obj) const;
    
   // LR1 
     
   bool nonLR1() const; 
    
   // parser
    
   void fill(PtrLen<ulen> ifinals,PtrLen<ulen> itransitions) const;
    
   // print 
   
   template <class P> 
   void print(const Punct &punct,P &out) const;
   
   class PrintRec
    {
      const Punct &punct;
      const State &state;
     
     public:
      
      PrintRec(const Punct &punct_,const State &state_) : punct(punct_),state(state_) {}
     
      template <class P> 
      void print(P &out) const 
       {
        state.print(punct,out);
       }
    };
   
   PrintRec getPrint(const Punct &punct) const { return PrintRec(punct,*this); }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

template <class P> 
void State::print(const Punct &punct,P &out) const
 {
  if( way_flag )
    Printf(out,"\nState #;\n : #;\n {\n",number,punct.printStr(way.read()));
  else
    Printf(out,"\nState #;\n {\n",number);
     
  for(auto p=transitions.read(); +p ;++p)
    Printf(out,"  #; -> State #;\n",punct.getTextDesc(p->index),p->object);

  Putobj(out,"  ---------------------\n");
  
  for(auto q=finals.read(); +q ;++q)
    Printf(out,"  #; -> #;\n",punct.getTextDesc(q->index),punct.printStr(q->object.read()));

  Putobj(out," }\n");
 }

} // namespace App

#endif 

