/* NonEmptyEstimate.h */
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

#ifndef CondLangLR1_process_NonEmptyEstimate_h
#define CondLangLR1_process_NonEmptyEstimate_h

#include "lang/Lang.h"

namespace App {

/* classes */

class NonEmptyEstimate;

/* class NonEmptyEstimate */

class NonEmptyEstimate : public CmpComparable<NonEmptyEstimate> , public NoThrowFlagsBase 
 {
   bool value;
   
  private: 
   
   NonEmptyEstimate(bool value_) : value(value_) {}
   
  public:
  
   // constructors
   
   NonEmptyEstimate() : value(false) {}
   
   NonEmptyEstimate(ElementNullType) : value(false) {}
   
   NonEmptyEstimate(ElementOneType) : value(true) {}
   
   struct Context {};
   
   NonEmptyEstimate(Atom,Context) : value(true) {}
   
   // methods
   
   bool operator + () const { return value; }
   
   bool operator ! () const { return !value; }
   
   bool set(NonEmptyEstimate obj)
    {
     if( value!=obj.value )
       {
        value=obj.value;
       
        return true;
       }
     
     return false;
    }
   
   // cmp objects
   
   CmpResult objCmp(NonEmptyEstimate obj) const { return LessCmp(value,obj.value); }
   
   // operations
   
   friend NonEmptyEstimate operator + (NonEmptyEstimate a,NonEmptyEstimate b) { return a.value|b.value; }
   
   friend NonEmptyEstimate operator * (NonEmptyEstimate a,NonEmptyEstimate b) { return a.value&b.value; }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     if( value )
       Putobj(out,"non-empty");
     else
       Putobj(out,"empty");
    }
 };

} // namespace App

#endif
