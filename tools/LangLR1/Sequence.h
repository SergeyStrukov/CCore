/* Sequence.h */ 
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

#ifndef LangLR1_Sequence_h
#define LangLR1_Sequence_h

#include "Tool.h"

namespace App {

/* classes */ 

template <class T> class ConcatenateBuilder;

template <class T> class Sequence;

/* class ConcatenateBuilder<T> */ 

template <class T>
class ConcatenateBuilder
 {
   PtrLen<const T> a;
   PtrLen<const T> b;
 
  public:
  
   ConcatenateBuilder(PtrLen<const T> a_,PtrLen<const T> b_) : a(a_),b(b_) {}
   
   ulen getLen() const { return LenAdd(a.len,b.len); }

   PtrLen<T> operator () (Place<void> place) const;
 };

template <class T>
PtrLen<T> ConcatenateBuilder<T>::operator () (Place<void> place) const
 {
  typename ArrayAlgo<T>::template CreateGuardNoThrow<NoThrowFlags<T>::Copy_no_throw> guard(place,a.len+b.len);
  
  for(auto p=a; +p ;++p,++guard) new(guard.at()) T(*p);
  
  for(auto p=b; +p ;++p,++guard) new(guard.at()) T(*p);
    
  return guard.disarm();
 }
 
/* class Sequence<T> */ 

template <class T>
class Sequence : public CmpComparable<Sequence<T> >
 {
   RefArray<T> array;
   
  public:
   
   // constructors
  
   Sequence() {}
   
   explicit Sequence(const T &t) : array(DoFill(1),t) {}
   
   Sequence(const Sequence<T> &a,const Sequence<T> &b) : array(DoBuild,ConcatenateBuilder<T>(a.read(),b.read())) {}
   
   Sequence(const Sequence<T> &a,const T &t) : array(a.array) { array.append_copy(t); }
   
   ~Sequence() {}
   
   // methods
   
   bool isNull() const { return !array.getLen(); }
   
   ulen nonNull() const { return array.getLen(); }
   
   ulen getLen() const { return array.getLen(); }
   
   PtrLen<const T> read() const { return Range_const(array); }
   
   CmpResult objCmp(const Sequence<T> &obj) const { return RangeCmp(read(),obj.read()); }
   
   // operators
    
   friend Sequence<T> operator + (const Sequence<T> &a,const Sequence<T> &b)
    {  
     if( a.isNull() ) return b;
     if( b.isNull() ) return a;
  
     return Sequence<T>(a,b);
    }
   
   friend Sequence<T> operator + (const Sequence<T> &a,const T &t)
    {  
     if( a.isNull() ) return Sequence<T>(t);
  
     return Sequence<T>(a,t);
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


