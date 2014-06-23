/* TypeSwitch.h */ 
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

#ifndef CCore_inc_TypeSwitch_h
#define CCore_inc_TypeSwitch_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Meta {

/* classes */

template <class SUInt,SUInt Val,class T> struct Case;

template <class ... CC> struct CaseList;

template <class ... CC> struct SplitCaseList0;

template <class ... CC> struct SplitCaseList1;

template <class ... CC> struct SplitCaseList2;

template <class ... CC> struct SplitCaseList3;

template <class ... CC> struct SplitCaseList4;

template <class ... CC> struct SplitCaseList5;

template <unsigned Off,class CaseList> struct SplitCaseOf;

template <class CaseList> struct CaseListExtend;

template <class CaseList1,class CaseList2> struct CaseListJoin;

template <unsigned Off,class ... CC> struct SplitCaseList;

template <class CaseList> struct TypeSwitch;

/* struct Case<SUInt,SUInt Val,class T> */

template <class SUInt,SUInt Val_,class T> 
struct Case
 {
  using SwType = SUInt ;
  
  static const SwType Val = Val_ ;
  
  using Type = T ;
 };

/* struct CaseList<CC> */

template <class ... CC> 
struct CaseList
 {
  static const unsigned Len = sizeof ... (CC) ;
  
  using Split = SplitCaseList<Len/2,CC...> ;
  
  using First = typename Split::First ;
  using Last  = typename Split::Last ;
  
  using SwType = typename CommonType<typename First::SwType,typename Last::SwType>::Ret ;
 };

template <> 
struct CaseList<>
 {
  static const unsigned Len = 0 ;
 };

template <class C1> 
struct CaseList<C1>
 {
  static const unsigned Len = 1 ;
  
  using SwType = typename C1::SwType ;
 };

template <class C1,class C2> 
struct CaseList<C1,C2>
 {
  static const unsigned Len = 2 ;
  
  using First = CaseList<C1> ;
  using Last  = CaseList<C2> ;
  
  using SwType = typename CommonType<typename First::SwType,typename Last::SwType>::Ret ;
 };

/* struct SplitCaseList0<CC> */

template <class ... CC> 
struct SplitCaseList0
 {
  using First = CaseList<> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseList1<CC> */

template <class C1,class ... CC> 
struct SplitCaseList1<C1,CC...>
 {
  using First = CaseList<C1> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseList2<CC> */

template <class C1,class C2,class ... CC> 
struct SplitCaseList2<C1,C2,CC...>
 {
  using First = CaseList<C1,C2> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseList3<CC> */

template <class C1,class C2,class C3,class ... CC> 
struct SplitCaseList3<C1,C2,C3,CC...>
 {
  using First = CaseList<C1,C2,C3> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseList4<CC> */

template <class C1,class C2,class C3,class C4,class ... CC> 
struct SplitCaseList4<C1,C2,C3,C4,CC...>
 {
  using First = CaseList<C1,C2,C3,C4> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseList5<CC> */

template <class C1,class C2,class C3,class C4,class C5,class ... CC> 
struct SplitCaseList5<C1,C2,C3,C4,C5,CC...>
 {
  using First = CaseList<C1,C2,C3,C4,C5> ;
  using Last = CaseList<CC...> ;
 };

/* struct SplitCaseOf<unsigned Off,CaseList> */

template <unsigned Off,class ... CC>
struct SplitCaseOf<Off,CaseList<CC...> > : SplitCaseList<Off,CC...> {};

/* struct CaseListExtend<CaseList> */

template <class ... CC>
struct CaseListExtend<CaseList<CC...> >
 {
  template <class ... TT>
  struct Extend
   {
    using Ret = CaseList<CC...,TT...> ;
   };
 };

/* struct CaseListJoin<CaseList1,CaseList2> */

template <class CaseList1,class ... CC>
struct CaseListJoin<CaseList1,CaseList<CC...> >
 {
  using Extend = typename CaseListExtend<CaseList1>::template Extend<CC...> ;
  using Ret = typename Extend::Ret ;
 };

/* struct SplitCaseList<unsigned Off,CC> */

template <unsigned Off,class ... CC> 
struct SplitCaseList
 {
  static const unsigned A = Off/2 ;
  static const unsigned B = Off-A ;
  
  using SplitA = SplitCaseList<A,CC...> ;
  
  using SplitB = SplitCaseOf<B,typename SplitA::Last> ;
  
  using First = typename CaseListJoin<typename SplitA::First,typename SplitB::First>::Ret ;
  using Last = typename SplitB::Last ;
 };

template <class ... CC> 
struct SplitCaseList<0,CC...> : SplitCaseList0<CC...> {};

template <class ... CC> 
struct SplitCaseList<1,CC...> : SplitCaseList1<CC...> {};

template <class ... CC> 
struct SplitCaseList<2,CC...> : SplitCaseList2<CC...> {};

template <class ... CC> 
struct SplitCaseList<3,CC...> : SplitCaseList3<CC...> {};

template <class ... CC> 
struct SplitCaseList<4,CC...> : SplitCaseList4<CC...> {};

template <class ... CC> 
struct SplitCaseList<5,CC...> : SplitCaseList5<CC...> {};

/* struct TypeSwitch<CaseList> */

template <class CaseList> 
struct TypeSwitch
 {
  using SwType = typename CaseList::SwType ;
  using First = typename CaseList::First ;
  using Last = typename CaseList::Last ;
  
  template <class Ctx,class RetType_>
  struct Tail
   {
    using RetType = RetType_ ;
    
    Ctx &ctx;
    
    explicit Tail(Ctx &ctx_) : ctx(ctx_) {}
    
    template <class T>
    RetType call() { return ctx.template call<T>(); }
    
    RetType defcall(SwType val)
     {
      return TypeSwitch<Last>::template Switch<Ctx &,RetType>(val,ctx);
     }
   };
  
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SwType val,Ctx ctx)
   {
    return TypeSwitch<First>::Switch(val,Tail<Ctx,RetType>(ctx));
   }
 };

template <>
struct TypeSwitch<CaseList<> >
 {
 };

template <class SUInt,SUInt Val1,class T1>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>();
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4,
                      SUInt Val5,class T5>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4>,
                           Case<SUInt,Val5,T5> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       case Val5 : return ctx.template call<T5>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4,
                      SUInt Val5,class T5,
                      SUInt Val6,class T6>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4>,
                           Case<SUInt,Val5,T5>,
                           Case<SUInt,Val6,T6> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       case Val5 : return ctx.template call<T5>(); 
       case Val6 : return ctx.template call<T6>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4,
                      SUInt Val5,class T5,
                      SUInt Val6,class T6,
                      SUInt Val7,class T7>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4>,
                           Case<SUInt,Val5,T5>,
                           Case<SUInt,Val6,T6>,
                           Case<SUInt,Val7,T7> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       case Val5 : return ctx.template call<T5>(); 
       case Val6 : return ctx.template call<T6>(); 
       case Val7 : return ctx.template call<T7>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4,
                      SUInt Val5,class T5,
                      SUInt Val6,class T6,
                      SUInt Val7,class T7,
                      SUInt Val8,class T8>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4>,
                           Case<SUInt,Val5,T5>,
                           Case<SUInt,Val6,T6>,
                           Case<SUInt,Val7,T7>,
                           Case<SUInt,Val8,T8> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       case Val5 : return ctx.template call<T5>(); 
       case Val6 : return ctx.template call<T6>(); 
       case Val7 : return ctx.template call<T7>(); 
       case Val8 : return ctx.template call<T8>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt Val1,class T1,
                      SUInt Val2,class T2,
                      SUInt Val3,class T3,
                      SUInt Val4,class T4,
                      SUInt Val5,class T5,
                      SUInt Val6,class T6,
                      SUInt Val7,class T7,
                      SUInt Val8,class T8,
                      SUInt Val9,class T9>
struct TypeSwitch<CaseList<Case<SUInt,Val1,T1>,
                           Case<SUInt,Val2,T2>,
                           Case<SUInt,Val3,T3>,
                           Case<SUInt,Val4,T4>,
                           Case<SUInt,Val5,T5>,
                           Case<SUInt,Val6,T6>,
                           Case<SUInt,Val7,T7>,
                           Case<SUInt,Val8,T8>,
                           Case<SUInt,Val9,T9> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case Val1 : return ctx.template call<T1>(); 
       case Val2 : return ctx.template call<T2>(); 
       case Val3 : return ctx.template call<T3>(); 
       case Val4 : return ctx.template call<T4>(); 
       case Val5 : return ctx.template call<T5>(); 
       case Val6 : return ctx.template call<T6>(); 
       case Val7 : return ctx.template call<T7>(); 
       case Val8 : return ctx.template call<T8>(); 
       case Val9 : return ctx.template call<T9>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

} // namespace Meta
} // namespace CCore
 
#endif
 

