/* State.cpp */
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

#include "State.h"

namespace App {

/* class State */ 

bool State::wayout(State *base)
 {
  if( way_flag!=HasWay ) return false;
     
  bool ret=false;
    
  for(auto t=transitions.read(); +t ;++t)
    {
     State *dst=base+t->object;
        
     if( !dst->way_flag )
       {
        dst->way=way+t->index;
        dst->way_flag=HasWay;
        
        ret=true;
       }
    }
       
  way_flag=HasWayOut;  
       
  return ret;  
 }
    
void State::propagateGroupNumber(const State *base)
 {
  new_group_number=base[group_number].new_group_number; 
 }
 
void State::update(const State *base)
 {
  for(auto p=transitions.write(); +p ;++p)
    {
     ulen num=p->object;
     
     p->object=base[num].new_group_number;
    }
 
  number=new_group_number;
 }
 
CmpResult State::groupCmp(const State *base,const State &obj) const
 {
  if( CmpResult ret=Cmp(final_number,obj.final_number) ) return ret;
  
  auto a=transitions.read();
  auto b=obj.transitions.read();
  
  for(; +a && +b ;++a,++b)
    {
     if( CmpResult ret=Cmp(a->index,b->index) ) return ret;
     
     if( CmpResult ret=Cmp(base[a->object].group_number,base[b->object].group_number) ) return ret;
    }
    
  if( +b ) return CmpLess;
  if( +a ) return CmpGreater;
  
  return CmpEqual;
 }
 
bool State::nonLR1() const 
 {
  for(auto q=finals.read(); +q ;++q)
    if( q->object.getLen()>1 ) 
      return true;
       
  return false;  
 }
    
void State::fill(PtrLen<ulen> ifinals,PtrLen<ulen> itransitions) const
 {
  ifinals.set_null();
  itransitions.set_null();
  
  for(auto p=finals.read(); +p ;++p)
    {
     auto r=p->object.read();
         
     if( r.len!=1 )
       {
        Printf(Exception,"State::fill() : r.len!=1");
       }
        
     ifinals[p->index]=(*r)+1;
    } 
     
  for(auto p=transitions.read(); +p ;++p)
    {
     itransitions[p->index]=p->object+1;
    }
 }

} // namespace App

