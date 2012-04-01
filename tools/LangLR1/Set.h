/* Set.h */ 
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

#ifndef LangLR1_Set_h
#define LangLR1_Set_h

#include "Tool.h"

namespace App {

/* classes */ 

template <class T> struct Joiner; 

template <class T> struct SimpleJoiner;

template <class T,template <class> class J> class JoinBuilder;

template <class T,template <class> class J> class Set;

template <class I,class T> struct IndexPair;

/* struct Joiner<T> */ 

template <class T>
struct Joiner
 {
  static T Join(const T &a,const T &b) { return a.join(b); }
  
  static CmpResult WeakCmp(const T &a,const T &b) { return a.weakCmp(b); }
 };

/* struct SimpleJoiner<T> */ 

template <class T>
struct SimpleJoiner
 {
  static T Join(const T &a,const T &) { return a; }
  
  static CmpResult WeakCmp(const T &a,const T &b) { return Cmp(a,b); }
 };
 
/* class JoinBuilder<T,J> */  

template <class T,template <class> class J>
class JoinBuilder
 {
   PtrLen<const T> ra;
   PtrLen<const T> rb;
   
  public:
  
   JoinBuilder(PtrLen<const T> ra_,PtrLen<const T> rb_) : ra(ra_),rb(rb_) {}
   
   ulen getLen() const { return LenAdd(ra.len,rb.len); }
   
   PtrLen<T> operator () (Place<void> place) const;
 };
 
template <class T,template <class> class J>
PtrLen<T> JoinBuilder<T,J>::operator () (Place<void> place) const
 {
  auto a=ra;
  auto b=rb;
  
  typename ArrayAlgo<T>::BuildGuard guard(place);
 
  for(; +a && +b ;++guard)
    switch( J<T>::WeakCmp(*a,*b) )
      {
       case CmpLess :
        {
         new(guard.at()) T(*a);
         
         ++a;
        }
       break;

       case CmpGreater :  
        {
         new(guard.at()) T(*b);
         
         ++b;
        }
       break; 
        
       default: // case CmpEqual 
        {
         new(guard.at()) T(J<T>::Join(*a,*b));
         
         ++a;
         ++b;
        }
      }
         
  for(; +a ;++a,++guard) new(guard.at()) T(*a);
  
  for(; +b ;++b,++guard) new(guard.at()) T(*b);
  
  return guard.disarm();
 }
 
/* class Set<T,J> */ 

template <class T,template <class> class J>
class Set : public CmpComparable<Set<T,J> >
 {
   RefArray<T> array;
   
  public:
   
   // constructors
  
   Set() {}
   
   explicit Set(const T &t) : array(DoFill(1),t) {}
   
   Set(const Set<T,J> &a,const Set<T,J> &b) : array(DoBuild,JoinBuilder<T,J>(a.read(),b.read())) {}
   
   explicit Set(PtrLen<const T> olist) : array(DoCopy(olist.len),olist.ptr) {}
   
   template <class Builder>
   Set(DoBuildType,Builder builder) : array(DoBuild,builder) {}
      
   ~Set() {}
   
   // methods
   
   bool isEmpty() const { return !array.getLen(); }
   
   bool nonEmpty() const { return array.getLen(); }
   
   ulen getLen() const { return array.getLen(); }
   
   PtrLen<const T> read() const { return Range_const(array); }
   
   PtrLen<T> write() { return array.modify(); }
   
   CmpResult objCmp(const Set<T,J> &obj) const { return RangeCmp(read(),obj.read()); }
   
   // operators
    
   friend Set<T,J> operator + (const Set<T,J> &a,const Set<T,J> &b)
    {  
     if( a.isEmpty() ) return b;
     if( b.isEmpty() ) return a;
  
     return Set<T,J>(a,b);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* struct IndexPair<I,T> */  
 
template <class I,class T> 
struct IndexPair : CmpComparable<IndexPair<I,T> >
 {
  I index;
  T object;
  
  // constuctors
  
  IndexPair() : index(),object() {}
       
  IndexPair(const I &index_,const T &object_) : index(index_),object(object_) {}
  
  // methods
       
  IndexPair<I,T> join(const IndexPair<I,T> &obj) const 
   { 
    return IndexPair<I,T>(index,object+obj.object); 
   }
       
  CmpResult weakCmp(const IndexPair<I,T> &obj) const 
   { 
    return Cmp(index,obj.index);
   }
         
  CmpResult objCmp(const IndexPair<I,T> &obj) const 
   { 
    return AlphaCmp(index,obj.index,object,obj.object);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = NoThrowFlags<I>::Default_no_throw && NoThrowFlags<T>::Default_no_throw ,
    Copy_no_throw = NoThrowFlags<I>::Copy_no_throw && NoThrowFlags<T>::Copy_no_throw
   };
 };

} // namespace App

#endif

