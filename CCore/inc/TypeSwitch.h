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

template <class SUInt,SUInt val,class T> struct Case;

template <class ... CC> struct SwTypeOf;

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

/* struct Case<SUInt,SUInt val,class T> */

template <class SUInt,SUInt val,class T> 
struct Case
 {
  using SwType = SUInt ;
  
  static const SUInt Val = val ;
  
  using Type = T ;
 };

/* struct SwTypeOf<CC> */

template <class C,class ... CC>
struct SwTypeOf<C,CC...>
 {
  using Ret = typename C::SwType ;
 };

/* struct CaseList<CC> */

template <class ... CC> 
struct CaseList
 {
  using SwType = typename SwTypeOf<CC...>::Ret ;
  
  static const unsigned Len = sizeof ... (CC) ;
  
  using Split = SplitCaseList<Len/2,CC...> ;
  
  using First = typename Split::First ;
  using Last  = typename Split::Last ;
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
  struct ContCtx
   {
    using RetType = RetType_ ;
    
    Ctx &ctx;
    
    explicit ContCtx(Ctx &ctx_) : ctx(ctx_) {}
    
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
    return TypeSwitch<First>::Switch(val,ContCtx<Ctx,RetType>(ctx));
   }
 };

template <class SUInt,SUInt val1,class T1>
struct TypeSwitch<CaseList<Case<SUInt,val1,T1> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case val1 : return ctx.template call<T1>();
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt val1,class T1,
                      SUInt val2,class T2>
struct TypeSwitch<CaseList<Case<SUInt,val1,T1>,
                           Case<SUInt,val2,T2> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case val1 : return ctx.template call<T1>(); 
       case val2 : return ctx.template call<T2>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt val1,class T1,
                      SUInt val2,class T2,
                      SUInt val3,class T3>
struct TypeSwitch<CaseList<Case<SUInt,val1,T1>,
                           Case<SUInt,val2,T2>,
                           Case<SUInt,val3,T3> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case val1 : return ctx.template call<T1>(); 
       case val2 : return ctx.template call<T2>(); 
       case val3 : return ctx.template call<T3>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt val1,class T1,
                      SUInt val2,class T2,
                      SUInt val3,class T3,
                      SUInt val4,class T4>
struct TypeSwitch<CaseList<Case<SUInt,val1,T1>,
                           Case<SUInt,val2,T2>,
                           Case<SUInt,val3,T3>,
                           Case<SUInt,val4,T4> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case val1 : return ctx.template call<T1>(); 
       case val2 : return ctx.template call<T2>(); 
       case val3 : return ctx.template call<T3>(); 
       case val4 : return ctx.template call<T4>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

template <class SUInt,SUInt val1,class T1,
                      SUInt val2,class T2,
                      SUInt val3,class T3,
                      SUInt val4,class T4,
                      SUInt val5,class T5>
struct TypeSwitch<CaseList<Case<SUInt,val1,T1>,
                           Case<SUInt,val2,T2>,
                           Case<SUInt,val3,T3>,
                           Case<SUInt,val4,T4>,
                           Case<SUInt,val5,T5> > >
 {
  template <class Ctx,class RetType=typename Ctx::RetType>
  static RetType Switch(SUInt val,Ctx ctx)
   {
    switch( val )
      {
       case val1 : return ctx.template call<T1>(); 
       case val2 : return ctx.template call<T2>(); 
       case val3 : return ctx.template call<T3>(); 
       case val4 : return ctx.template call<T4>(); 
       case val5 : return ctx.template call<T5>(); 
       
       default: return ctx.defcall(val);
      }
   }
 };

} // namespace Meta
} // namespace CCore
 
#endif
 

