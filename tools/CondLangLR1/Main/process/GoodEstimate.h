/* GoodEstimate.h */
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

#ifndef CondLangLR1_process_GoodEstimate_h
#define CondLangLR1_process_GoodEstimate_h

#include "lang/Lang.h"

namespace App {

/* classes */

class GoodEstimate;

/* class GoodEstimate */ 

class GoodEstimate : public CmpComparable<GoodEstimate> , public NoThrowFlagsBase 
 {
   enum Type
    {
     Empty,Null,Good
    };
   
   Type value;
   
  private: 
   
   GoodEstimate(Type value_) : value(value_) {}
   
  public:
   
   // constructors
   
   GoodEstimate() : value(Empty) {}
   
   GoodEstimate(ElementNullType) : value(Empty) {}
   
   GoodEstimate(ElementOneType) : value(Null) {}
   
   struct Context {};
   
   GoodEstimate(Atom,Context) : value(Good) {}
   
   // methods
   
   bool operator + () const { return value!=Empty; }
   
   bool operator ! () const { return value==Empty; }
   
   bool setCmp(GoodEstimate obj)
    {
     if( value!=obj.value )
       {
        value=obj.value;
       
        return true;
       }
     
     return false;
    }
   
   // properties
   
   bool notGood() const { return value!=Good; }
   
   // cmp objects
   
   CmpResult objCmp(GoodEstimate obj) const { return LessCmp(value,obj.value); }
   
   // operations
   
   friend GoodEstimate operator + (GoodEstimate a,GoodEstimate b) { return Max(a.value,b.value); }
   
   friend GoodEstimate operator * (GoodEstimate a,GoodEstimate b) { return Type(Min<int>(a.value*b.value,2)); }
   
   using Accumulator = GoodEstimate ;
   
   void operator += (GoodEstimate obj) { (*this)=(*this)+obj; }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     switch( value )
       {
        case Empty : Putobj(out,"empty"); break;
        case Null  : Putobj(out,"null"); break;
        case Good  : Putobj(out,"good"); break;
       }
    }
   
   template <class P>
   void printBlock(P &out,ulen index) const
    {
     Printf(out,"#;) #;\n",index,*this);
    }
 };

} // namespace App

#endif


