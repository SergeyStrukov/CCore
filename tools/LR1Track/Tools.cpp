/* Tools.cpp */
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

#include "Tools.h"

#include <CCore/inc/algon/SortUnique.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

/* struct Track */

void Track::buildStates(PtrLen<DynArray<TypeDef::State *> > state_transitions)
 {
  DynArray<TypeDef::State *> temp(DoReserve,100);
   
  for(auto *state : start->states )
    {
     for(auto *element : args )
       {
        state=state_transitions[state->state][element->element];
       }
      
     temp.append_copy(state);
    }

  states.reserve(100);
   
  Algon::IncrSortThenApplyUniqueBy(Range(temp), [] (TypeDef::State *state) { return state->state; } ,
                                                [&] (TypeDef::State *state) { states.append_copy(state); } );
   
  states.shrink_extra();
 }

void Track::buildFinals()
 {
  // finals
  {
   DynArray<TypeDef::Final *> temp(DoReserve,100);
   
   for(auto *state : states )
     {
      temp.append_copy(state->final);
     }
   
   finals.reserve(100);
   
   Algon::IncrSortThenApplyUniqueBy(Range(temp), [] (TypeDef::Final *final) { return final->final; } ,
                                                 [&] (TypeDef::Final *final) { finals.append_copy(final); } );
   
   finals.shrink_extra();
  }
  
  // rules
  {
   DynArray<TypeDef::Rule *> temp(DoReserve,100);
   
   for(auto *final : finals )
     {
      for(auto action : final->actions )
        {
         if( action.rule->rule )
           temp.append_copy(action.rule);
        }
     }
   
   rules.reserve(100);
   
   Algon::IncrSortThenApplyUniqueBy(Range(temp), [] (TypeDef::Rule *rule) { return rule->rule; } ,
                                                 [&] (TypeDef::Rule *rule) { rules.append_copy(rule); } );
   
   rules.shrink_extra();
  }
  
  buildCombinedFinal();
 }

void Track::buildCombinedFinal()
 {
  DynArray<TypeDef::Final::Action> temp(DoReserve,100);
  
  for(auto *final : finals )
    {
     for(auto action : final->actions )
       {
        temp.append_copy(action);
       }
    }
  
  combined_final.reserve(100);
  
  Algon::IncrSortThenApplyUniqueRangeBy(Range(temp), [] (TypeDef::Final::Action action) { return action.atom->element; } , 
                                                     [&] (PtrLen<TypeDef::Final::Action> r) { appendActions(r); } );
  
  combined_final.shrink_extra();
 }

void Track::appendActions(PtrLen<TypeDef::Final::Action> r)
 {
  auto rule=r->rule->rule;
  
  for(++r; +r ;++r)
    {
     if( rule!=r->rule->rule )
       {
        Printf(Exception,"Final conflict");
       }
    }
  
  combined_final.append_copy(*r);
 }

/* class TrackBuilder */

void TrackBuilder::buildTransitions()
 {
  auto table=transitions.extend_fill(shift_states.len,TypeDef::Element::Ext::ElementLim);
  
  for(auto shift_state : shift_states )
    {
     auto row=Range(table[shift_state.state]);
     
     for(auto transition : shift_state.transitions )
       {
        row[transition.element->element]=transition.state;
       }
    }
 }
   
void TrackBuilder::buildStateTransitions()
 {
  PtrLen<TypeDef::State> states=data->getStates();
  
  auto table=state_transitions.extend_fill(states.len,TypeDef::Element::Ext::ElementLim);
  
  for(auto state : states )
    {
     auto row=Range(table[state.state]);
     
     for(auto transition : state.transitions )
       {
        row[transition.element->element]=transition.state;
       }
    }
 }
   
void TrackBuilder::buildTracks()
 {
  for(auto &shift_state : shift_states )
    {
     for(auto &rule : rules )
       {
        RefArray<TypeDef::ShiftState *> path(DoReserve,100);
        
        TypeDef::ShiftState *ptr=&shift_state;
        
        if( transitions[ptr->state][rule.result->element] )
          {
           for(auto *element : rule.args )
             {
              ptr=transitions[ptr->state][element->element];
              
              if( !ptr ) break;
              
              path.append_copy(ptr);
             }
           
           if( ptr )
             {
              path.shrink_extra();
             
              Track *track=tracks.append_default();
              
              track->start=&shift_state;
              track->args=rule.args;
              track->finish=ptr;
              track->path=path;
             }
          }
       }
    }
  
  tracks.shrink_extra();
 }

void TrackBuilder::uniqueTracks()
 {
  DynArray<Track> temp(DoReserve,100);
  
  Algon::SortThenApplyUnique(Range(tracks), [&] (const Track &track) { temp.append_copy(track); } );
  
  temp.shrink_extra();
  
  Swap(tracks,temp);
 }

void TrackBuilder::completeTracks()
 {
  for(auto &track : tracks ) 
    {
     track.buildStates(Range(state_transitions));
     track.buildFinals();
    }
 }

TrackBuilder::TrackBuilder(DataMap *data_)
 : data(data_),
   tracks(DoReserve,100)
 {
  shift_states=data->getShiftStates();
  rules=data->getRules();
  
  ++rules;
  
  buildTransitions();
  buildStateTransitions();
  buildTracks();
  uniqueTracks();
  completeTracks();
 }
   
TrackBuilder::~TrackBuilder()
 {
 }

} // namespace App

