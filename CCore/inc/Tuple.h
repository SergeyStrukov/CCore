/* Tuple.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Tuple_h
#define CCore_inc_Tuple_h

#include <CCore/inc/FunctorType.h>
 
namespace CCore {

/* classes */ 

template <class ... TT> struct Tuple;

template <class ... TT> struct ForwardTuple;

/* struct Tuple<TT> */ 

template <> 
struct Tuple<>
 {
  Tuple() {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    func();
   }
 };
 
template <class T> 
struct Tuple<T>
 {
  T first;
 
  Tuple() : first() {}
  
  Tuple(const T &t) : first(t) {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    func(first);
   }
 };
 
template <class T,class S,class ... RR> 
struct Tuple<T,S,RR...>
 {
  T first;
  Tuple<S,RR...> rest;
  
  Tuple() {}
  
  Tuple(const T &t,const S &s,const RR & ... rr) : first(t),rest(s,rr...) {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    T &first_=first;
    
    rest.call( [&] (S &s,RR & ... rr) { func(first_,s,rr...); } );
   }
 };
 
/* struct ForwardTuple<TT> */ 

template <> 
struct ForwardTuple<>
 {
  ForwardTuple() {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    func();
   }
 };
 
template <class T> 
struct ForwardTuple<T>
 {
  T &&first;
 
  ForwardTuple(T &&t) : first( std::forward<T>(t) ) {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    func( std::forward<T>(first) );
   }
 };
 
template <class T,class S,class ... RR> 
struct ForwardTuple<T,S,RR...>
 {
  T &&first;
  ForwardTuple<S,RR...> rest;
  
  ForwardTuple(T &&t,S &&s,RR && ... rr) : first( std::forward<T>(t) ),rest( std::forward<S>(s) , std::forward<RR>(rr)... ) {}
  
  template <class FuncInit>
  void call(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);
    
    T &&first_=first;
    
    rest.call( [&] (S &&s,RR && ... rr) { func( std::forward<T>(first_) , std::forward<S>(s) , std::forward<RR>(rr)... ); } );
   }
 };

/* MakeTuple() */

template <class ... TT>
Tuple<TT...> MakeTuple(const TT & ... tt) { return Tuple<TT...>(tt...); }

} // namespace CCore
 
#endif
 

