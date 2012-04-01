/* PickRule.h */
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

#ifndef LangLR1_PickRule_h
#define LangLR1_PickRule_h

#include "Lang.h"

namespace App {

/* classes */ 

class PickRule;

/* class PickRule */ 

class PickRule
 {
   bool empty;
   RIndex rule;
   
  private:
   
   static void GuardShiftRule();
   
  public:
   
   // constructors
  
   PickRule() : empty(true),rule(RIndexShift) {}
   
   explicit PickRule(RIndex r) : empty(false),rule(r) {}
   
   explicit PickRule(TIndex) : empty(false),rule(RIndexShift) {}
   
   // methods
   
   RIndex getRule() const 
    {
     if( rule==RIndexShift ) GuardShiftRule();
     
     return rule; 
    }
   
   bool set(PickRule a) 
    { 
     if( empty && !a.empty ) 
       {
        *this=a;
        
        return true;
       }
       
     return false;
    }
   
   // operators
    
   friend PickRule operator + (PickRule a,PickRule b)
    {
     if( a.empty ) return b;
     
     return a;
    }
    
   friend PickRule operator * (PickRule a,PickRule b) 
    {
     if( !a.empty ) return b;
     
     return PickRule();
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

} // namespace App

#endif
