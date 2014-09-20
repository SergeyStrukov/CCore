/* TypeNumber.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TypeNumber_h
#define CCore_inc_TypeNumber_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */

class TypeNumber;

template <class T> class TypeNumberOf;

/* class TypeNumber */

class TypeNumber
 {
   unsigned number;

   static bool OneOf(TypeNumber) { return false; }
   
   static bool OneOf(TypeNumber tn,TypeNumber tn1) { return tn==tn1; }
  
   static bool OneOf(TypeNumber tn,TypeNumber tn1,TypeNumber tn2) { return tn==tn1 || tn==tn2 ; }
   
   static bool OneOf(TypeNumber tn,TypeNumber tn1,TypeNumber tn2,TypeNumber tn3) { return tn==tn1 || tn==tn2 || tn==tn3 ; }
   
   template <class ... TT,class T>
   static bool OneOf(TypeNumber tn,TT ... tt,T t) { return OneOf(tn,tt...) || tn==t ; }
   
  protected: 
   
   class Anchor
    {
      unsigned number;
      
      static unsigned NextNumber;
      
     public:
      
      Anchor() : number(NextNumber++) {}
      
      operator unsigned() const { return number; }
    };
   
   explicit TypeNumber(unsigned number_) : number(number_) {}
   
  public:
   
   unsigned get() const { return number; }
   
   bool operator == (TypeNumber obj) const { return number==obj.number; }
   
   bool operator != (TypeNumber obj) const { return number!=obj.number; }
   
   template <class ... TT>
   bool oneOf() const { return OneOf(*this,TypeNumberOf<TT>()...); }
 };

/* class TypeNumberOf<T> */

template <class T> 
class TypeNumberOf : public TypeNumber
 {
   static Anchor TypeAnchor;
   
  public:
  
   TypeNumberOf() : TypeNumber(TypeAnchor) {}
 };

template <class T> 
TypeNumber::Anchor TypeNumberOf<T>::TypeAnchor CCORE_INITPRI_0 ;

} // namespace CCore
 
#endif
 

