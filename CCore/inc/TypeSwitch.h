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

template <class ... Case> struct CaseList;

template <class CaseList> struct TypeSwitch;

/* struct Case<SUInt,SUInt val,class T> */

template <class SUInt,SUInt val,class T> 
struct Case
 {
  static const SUInt Val = val ;
  
  using Type = T ;
 };

/* struct TypeSwitch<CaseList> */

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
 

