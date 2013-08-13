/* Set.h */
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

#ifndef CondLangLR1_Set_h
#define CondLangLR1_Set_h

#include "Tools.h"

namespace App {

/* JoinSort() */

template <class T,template <class> class J>
T * JoinSorted(T *out,PtrLen<T> a,PtrLen<T> b)
 {
  while( +a && +b )
    switch( J<T>::WeakCmp(*a,*b) )
      {
       case CmpLess : 
        {
         *(out++)=*a; 
         
         ++a; 
        }
       break;
       
       case CmpGreater :
        {
         *(out++)=*b; 
         
         ++b;
        }
       break; 
        
       default: // case CmpEqual 
        {
         *(out++)=J<T>::Join(*a,*b); 
         
         ++a; 
         ++b;
        }
      }
      
  for(; +a ;++a) *(out++)=*a; 

  if( b.ptr!=out )  
    for(; +b ;++b) *(out++)=*b; 
  else
    out=b.ptr+b.len;
    
  return out;  
 }

template <class T,template <class> class J>
PtrLen<T> JoinSort(T *buf,T *spare,ulen len)
 {
  if( len<2 ) return Range(buf,len);
    
  ulen len2=len/2;
  ulen len1=len-len2;  
  
  PtrLen<T> ret1=JoinSort<T,J>(buf,spare,len1);
  PtrLen<T> ret2=JoinSort<T,J>(buf+len1,spare+len1,len2);
  
  T *out=(ret1.ptr==buf)?spare:buf;
  T *lim=JoinSorted<T,J>(out,ret1,ret2);
  
  return Range(out,lim);
 }

/* classes */ 

template <class T> struct Joiner; 

template <class T> struct SimpleJoiner;

template <class T,template <class> class J> class JoinBuilder;

template <class T,template <class> class J> class Set;

template <class ... TT> struct NoThrowFlagsBaseFor;

template <class I,class T> struct IndexPair;

/* struct Joiner<T> */ 

template <class T>
struct Joiner
 {
  static T Join(const T &a,const T &b) { return a.join(b); } // a weak equals b, result weak equals a
  
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
class Set : public CmpComparable<Set<T,J> > , public NoThrowFlagsBase
 {
   RefArray<T> array;
   
  public:
   
   // constructors
  
   Set() {}
   
   explicit Set(const T &t) : array(DoFill(1),t) {} // single element set
   
   Set(const Set<T,J> &a,const Set<T,J> &b) : array(DoBuild,JoinBuilder<T,J>(a.read(),b.read())) {}
   
   ~Set() {}
   
   // unsafe constructors
   
   explicit Set(PtrLen<const T> olist) : array(DoCopy(olist.len),olist.ptr) {} // strictly weak ordered input
   
   template <class Builder>
   Set(DoBuildType,Builder builder) : array(DoBuild,builder) {} // builder is responsible for the ordering
      
   // methods
   
   bool isEmpty() const { return !array.getLen(); }
   
   bool nonEmpty() const { return array.getLen(); }
   
   ulen getLen() const { return array.getLen(); }
   
   PtrLen<const T> read() const { return Range_const(array); }
   
   // cmp objects
   
   CmpResult objCmp(const Set<T,J> &obj) const { return RangeCmp(read(),obj.read()); }
   
   // operators
    
   friend Set<T,J> operator + (const Set<T,J> &a,const Set<T,J> &b)
    {  
     if( a.isEmpty() ) return b;
     if( b.isEmpty() ) return a;
  
     return Set<T,J>(a,b);
    }

   struct Accumulator;
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     auto p=read();
     
     if( +p )
       {
        Putobj(out,*p);
        
        for(++p; +p ;++p) Printf(out," #;",*p);
       }
    }
 };

template <class T,template <class> class J>
struct Set<T,J>::Accumulator : NoCopy
 {
   Set<T,J> first;
   ulen count = 0 ;
   Collector<T> collector;
   
  private:
   
   void add(const Set<T,J> &obj)
    {
     PtrLen<const T> range=obj.read();
     
     collector.extend_copy(range.len,range.ptr);
    }
   
   Set<T,J> build()
    {
     PtrLen<T> range=collector.flat();
     
     DynArray<T> temp(range.len);
     
     return Set<T,J>(Range_const(JoinSort<T,J>(range.ptr,temp.getPtr(),range.len)));
    }
   
  public:
  
   Accumulator() {}
  
   void operator += (const Set<T,J> &obj) 
    {
     if( count )
       {
        if( count==1 ) add(Replace_null(first));
         
        add(obj);
       }
     else
       {
        first=obj;
       }
     
     count++;
    }
  
   operator Set<T,J>()
    {
     switch( count )
       {
        case 0 : return Set<T,J>();
        case 1 : return first; 
        default: return build();
       }
    }
 };

/* struct NoThrowFlagsBaseFor<TT> */

template <>
struct NoThrowFlagsBaseFor<>
 {
  enum NoThrowFlagType
   {
    Default_no_throw = true ,
    Copy_no_throw = true
   };
 };

template <class T,class ... TT> 
struct NoThrowFlagsBaseFor<T,TT...>
 {
  enum NoThrowFlagType
   {
    Default_no_throw = NoThrowFlags<T>::Default_no_throw && NoThrowFlagsBaseFor<TT...>::Default_no_throw ,
    Copy_no_throw = NoThrowFlags<T>::Copy_no_throw && NoThrowFlagsBaseFor<TT...>::Copy_no_throw
   };
 };

/* struct IndexPair<I,T> */  
 
template <class I,class T> 
struct IndexPair : CmpComparable<IndexPair<I,T> > , NoThrowFlagsBaseFor<I,T>
 {
  I index;
  T object;
  
  // constuctors
  
  IndexPair() : index(),object() {}
       
  IndexPair(I index_,const T &object_) : index(index_),object(object_) {}
  
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
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; : #;",index,object);
   }
 };

} // namespace App

#endif


