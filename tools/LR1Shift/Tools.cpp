/* Tools.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LR1Shift 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Tools.h"

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

/* functions */

RefArray<TypeDef::Final *> BuildFinals(PtrLen<TypeDef::State *const> states)
 {
  RefArray<TypeDef::Final *> finals;
  DynArray<TypeDef::Final *> temp;
  
  auto r=temp.extend_default(states.len);
  
  for(ulen i=0; i<states.len ;i++) r[i]=states[i]->final;
  
  SortThenProcessUniqueBy(r, [] (TypeDef::Final *a) { return a->final; } , [&] (TypeDef::Final *a) { finals.append_copy(a); } );
  
  return finals;
 }

/* struct StateGroup */

StateGroup::Track::Track(ulen start_,TypeDef::Rule *rule_,const RefArray<ulen> &path_,PtrLen<TypeDef::State *> r) 
 : start(start_),
   rule(rule_),
   path(path_) 
 {
  SortThenProcessUniqueBy(r, [] (TypeDef::State *a) { return a->state; } , [&] (TypeDef::State *a) { states.append_copy(a); } );
  
  finals=BuildFinals(Range(states));
 }

void StateGroup::setTransitions(PtrLen<Transition> transitions_)
 {
  transitions.extend_copy(transitions_.len,transitions_.ptr);
 }

void StateGroup::build()
 {
  finals=BuildFinals(Range(states));
 }

void StateGroup::mapTransitions(PtrLen<ulen> ret)
 {
  ret.set(NoGroup);
  
  for(auto transition : transitions ) ret[transition.element->element]=transition.group;
 }

/* class StateCompressor */

StateCompressor::Fin::Fin(const TypeDef::Final &final_)
 {
  final=final_.final;
  
  for(auto action : final_.actions ) 
    if( action.rule->rule==0 )
      {
       shift.aset.atoms.append_fill(action.atom);
      }
  
  Sort(shift.aset.atoms.modify());
 }

StateCompressor::Map::Map(const TypeDef::State &state)
 : transitions(TypeDef::Element::ElementLim)
 {
  for(auto transition : state.transitions ) transitions[transition.element->element]=transition.state; 
 }

ulen StateCompressor::initIndex(PtrLen<TypeDef::Final> finals)
 {
  shift_index.extend_default(finals.len);
  
  DynArray<Fin> temp(DoCast(finals.len),finals.ptr);
  
  auto r=Range(temp);
  
  Sort(r);
  
  if( +r )
    {
     ulen index=0;
     ShiftFinal shift=r->shift;
     shifts.append_copy(shift);
     
     shift_index[r->final]=index;
    
     for(++r; +r ;++r)
       {
        ShiftFinal next=r->shift;
        
        if( shift!=next )
          {
           index++;
           shift=next;
           shifts.append_copy(shift);
          }
        
        shift_index[r->final]=index;
       }
     
     return index+1;
    }
  
  return 0;
 }

void StateCompressor::setSplitFlags(ulen split)
 {
  for(ulen i=0,len=states.len; i<len ;i++)
    {
     maps[i].split_flag = ( maps[i].group == split ) ;
    }
 }

void StateCompressor::setFlags(ulen element)
 {
  for(ulen i=0,len=states.len; i<len ;i++)
    {
     TypeDef::State *state=maps[i].transitions[element];
    
     maps[i].flag = ( state && maps[state->state].split_flag ) ;
    }
 }

void StateCompressor::setCounts()
 {
  for(ulen i=0,count=group_count; i<count ;i++) groups[i].clean();
  
  for(ulen i=0,len=states.len; i<len ;i++) groups[maps[i].group].count[maps[i].flag]++;
 }

void StateCompressor::splitGroups(ulen split)
 {
  ulen count=group_count;
  
  for(ulen i=0; i<=split ;i++)
    {
     if( groups[i].needSplit() )
       {
        ulen g=group_count++;
        
        groups[i].setBigSmall(i,g);
       }
     else
       {
        groups[i].set(i,i);
       }
    }
  
  for(ulen i=split+1; i<count ;i++)
    {
     if( groups[i].needSplit() )
       {
        ulen g=group_count++;
       
        groups[i].set(i,g);
       }
     else
       {
        groups[i].set(i,i);
       }
    }
 }

void StateCompressor::mapGroups()
 {
  for(ulen i=0,len=states.len; i<len ;i++) 
    {
     ulen g=maps[i].group;
     
     maps[i].group=groups[g].next_group[maps[i].flag];
    }
 }

void StateCompressor::checkGroups()
 {
  for(ulen i=0,count=group_count; i<count ;i++)
    {
     if( groups[i].needSplit() )
       {
        Printf(Exception,"StateCompressor check failed");
       }
    }  
 }

void StateCompressor::setGroup0()
 {
  ulen g0=maps[0].group;
  
  if( g0==0 ) return;
  
  for(ulen i=0,len=states.len; i<len ;i++)
    {
     ulen g=maps[i].group;
     
     if( g==0 )
       {
        maps[i].group=g0;
       }
     else if( g==g0 )
       {
        maps[i].group=0;
       }
    }
 }

StateCompressor::StateCompressor(PtrLen<TypeDef::Final> finals,PtrLen<TypeDef::State> states_)
 : states(states_),
   maps(DoCast(states_.len),states_.ptr),
   groups(states_.len)
 {
  group_count=initIndex(finals);
  
  for(ulen i=0; i<states_.len ;i++)
    {
     maps[i].group=shift_index[states_[i].final->final];
    }
 }

void StateCompressor::run()
 {
  Printf(Con,"state count = #;\n",states.len);
  Printf(Con,"initial group count = #;\n",group_count);
  
  for(ulen split=0; split<group_count ;split++)
    {
     setSplitFlags(split);
    
     for(ulen element=0; element<TypeDef::Element::ElementLim ;element++)
       {
        setFlags(element);
        
        setCounts();
        
        splitGroups(split);
        
        mapGroups();
       }
    }
  
  Printf(Con,"group count = #;\n",group_count);
  
  setGroup0();
 }

void StateCompressor::check()
 {
  for(ulen split=0; split<group_count ;split++)
    {
     setSplitFlags(split);
   
     for(ulen element=0; element<TypeDef::Element::ElementLim ;element++)
       {
        setFlags(element);
        
        setCounts();
        
        checkGroups();
       }
    }
 }

auto StateCompressor::getResult(PtrLen<TypeDef::Rule> rules) const -> Result
 {
  Result ret;
  
  PtrLen<StateGroup> sg=ret.state_groups.extend_default(group_count);
  
  // 1
  
  for(ulen i=0,len=sg.len; i<len ;i++) sg[i].group=i;
  
  for(ulen i=0,len=states.len; i<len ;i++)
    {
     ulen g=maps[i].group;
     
     sg[g].states.append_copy(states.ptr+i);
    }
  
  for(ulen i=0,len=sg.len; i<len ;i++) 
    {
     DynArray<StateGroup::Transition> transitions;
    
     for(auto transition : sg[i].states[0]->transitions )
       {
        transitions.append_fill(transition.element,maps[transition.state->state].group);
       }
     
     sg[i].setTransitions(Range(transitions));
     
     sg[i].shift=shifts[shift_index[sg[i].states[0]->final->final]];
     
     sg[i].build();
    }

  // 2
  
  ++rules;
  
  DynArray<DynArray<ulen> > transitions(DoFill(sg.len),TypeDef::Element::ElementLim);
  
  for(ulen g=0; g<sg.len ;g++)
    {
     sg[g].mapTransitions(Range(transitions[g]));
    }
  
  for(ulen g=0; g<sg.len ;g++)
    {
     for(auto &rule : rules )
       {
        if( transitions[g][rule.result->element]!=NoGroup )
          {
           ulen dst=g;
           RefArray<ulen> path; 
           
           for(auto *element : rule.args )
             {
              dst=transitions[dst][element->element];
              
              if( dst==NoGroup ) break;
              
              path.append_copy(dst);
             } 
           
           if( dst!=NoGroup )
             {
              DynArray<TypeDef::State *> temp;
             
              for(auto *state : sg[g].states )
                {
                 auto *s=state;
                
                 for(auto *element : rule.args )
                   {
                    s=maps[s->state].transitions[element->element];
                   }
                 
                 temp.append_copy(s);
                }
             
              sg[dst].tracks.append_fill(g,&rule,path,Range(temp));
             }
          }
       }
    }
  
  return ret;
 }

} // namespace App

