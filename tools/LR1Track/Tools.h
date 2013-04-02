/* Tools.h */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Track 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LR1Track_Tools_h
#define LR1Track_Tools_h

#include "DataMap.h"

#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace App {

/* classes */

struct Track;

class TrackBuilder;

/* struct Track */

struct Track : CmpComparable<Track> , NoThrowFlagsBase
 {
  TypeDef::ShiftState *start;
  PtrLen<TypeDef::Element *> args;
  TypeDef::ShiftState *finish;
  
  RefArray<TypeDef::ShiftState *> path;
  RefArray<TypeDef::State *> states;
  
  RefArray<TypeDef::Final *> finals;
  RefArray<TypeDef::Rule *> rules;
  
  RefArray<TypeDef::Final::Action> combined_final; 
  
  // methods
  
  void buildStates(PtrLen<DynArray<TypeDef::State *> > state_transitions);
  
  void buildFinals();
  
  void buildCombinedFinal();
  
  void appendActions(PtrLen<TypeDef::Final::Action> r);
  
  // cmp objects
  
  CmpResult objCmp(const Track &obj) const
   {
    if( CmpResult ret=Cmp(start->state,obj.start->state) ) return ret;
    
    return RangeCmpBy(args,obj.args, [] (TypeDef::Element *element) { return element->element; } );
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;) #;)\n",start->state,finish->state);

    for(auto *shift_state : path ) Printf(out," -> #;)",shift_state->state);
    
    Putobj(out,"\nStates:");
    
    for(auto *state : states ) Printf(out," #;)",state->state);
    
    Putobj(out,"\nFinals:");
    
    for(auto *final : finals ) Printf(out," #;)",final->final);
    
    Putobj(out,"\nRules:");
    
    for(auto *rule : rules ) Printf(out," #;",rule->name);
    
    Putch(out,'\n');
   }
 };

/* class TrackBuilder */

class TrackBuilder : NoCopy
 {
   DataMap *data;
   
   PtrLen<TypeDef::ShiftState> shift_states;
   PtrLen<TypeDef::Rule> rules;
   
   DynArray<DynArray<TypeDef::ShiftState *> > transitions;
   DynArray<DynArray<TypeDef::State *> > state_transitions;
   
   DynArray<Track> tracks;
   
  private: 
  
   void buildTransitions();
   
   void buildStateTransitions();
   
   void buildTracks();
   
   void uniqueTracks();
   
   void completeTracks();
   
  public: 
  
   explicit TrackBuilder(DataMap *data);
   
   ~TrackBuilder();
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     for(auto &t : tracks ) if( t.finals.getLen()>1 ) Printf(out,"#;\n",t);
    }
 };

} // namespace App

#endif

