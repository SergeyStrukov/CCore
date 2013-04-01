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

namespace App {

/* classes */

struct Track;

class TrackBuilder;

/* struct Track */

struct Track : NoThrowFlagsBase
 {
  TypeDef::ShiftState *start;
  TypeDef::Rule *rule;
  TypeDef::ShiftState *finish;
  
  RefArray<TypeDef::ShiftState *> path;
  RefArray<TypeDef::State *> states;
  RefArray<TypeDef::Final *> finals;
  bool finals_ok;
  
  Track() : finals_ok(true) {}
  
  // methods
  
  void testActions(PtrLen<TypeDef::Final::Action> r);
  
  void testFinals();
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#;) #; #;)\n",start->state,rule->name,finish->state);

    for(auto *shift_state : path ) Printf(out," -> #;)",shift_state->state);
    
    Putobj(out,"\nStates:");
    
    for(auto *state : states ) Printf(out," #;)",state->state);
    
    Putobj(out,"\nFinals:");
    
    for(auto *final : finals ) Printf(out," #;)",final->final);
    
    if( !finals_ok ) Putobj(out," Bad finals");
    
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
   
  public: 
  
   explicit TrackBuilder(DataMap *data);
   
   ~TrackBuilder();
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     for(auto &t : tracks ) Printf(out,"#;\n",t);
    }
 };

} // namespace App

#endif

