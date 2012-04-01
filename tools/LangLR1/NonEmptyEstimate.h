/* NonEmptyEstimate.h */ 
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

#ifndef LangLR1_NonEmptyEstimate_h
#define LangLR1_NonEmptyEstimate_h

#include "Tool.h"

namespace App {

/* classes */

struct NonEmptyEstimate;

/* struct NonEmptyEstimate */ 

struct NonEmptyEstimate 
 {
  enum Const
   {
    Empty,Null,Good
   };
 
  enum SetResult
   {
    NoChange,Change,ChangeToMax
   };
 
  class Type
   {
     int value;
     
    private: 
     
     explicit Type(int value_) : value(value_) {}
  
    public: 
  
     Type(Const c=Empty) : value(c) {}
     
     // methods
  
     bool isBad() const { return value!=Good; }
  
     const char * badDesc() const { return (value==Empty)?"empty":"only null string"; }
  
     SetResult set(Type t)
      {
       if( value==t.value ) return NoChange;
    
       value=t.value;
    
       return (value==Good)?ChangeToMax:Change;
      }
     
     // operators
      
     friend Type operator + (Type a,Type b) { return Type(Max(a.value,b.value)); }
     
     friend Type operator * (Type a,Type b) { return Type(Min(a.value*b.value,2)); }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
   };
 };

} // namespace App

#endif


