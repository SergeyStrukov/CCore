/* Function.h */ 
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

#ifndef CCore_inc_gadget_Function_h
#define CCore_inc_gadget_Function_h

#include <CCore/inc/base/PlatformBase.h>

#include <CCore/inc/gadget/Handle.h>
#include <CCore/inc/gadget/Nothing.h>
#include <CCore/inc/gadget/NoCopy.h>
 
namespace CCore {

/* classes */ 

template <class R> struct DefaultFunction;

template <class FuncType> class Function;

struct Funchor; // Fu(nction) (A)nchor

/* struct DefaultFunction<R> */ 

template <class R> 
struct DefaultFunction
 {
  static R Func() { return R(); }
 };
 
template <> 
struct DefaultFunction<void>
 {
  static void Func() {}
 };

/* class Function<R,AA> */

template <class R,class ... AA>
class Function<R (AA...)>
 {
   Funchor *obj;

   struct CtxFunc 
    {
     Handle ctx;
     R (*func)(Handle ctx,AA...);
    };
   
   union 
    {
     CtxFunc ptr; 
     R (Funchor::*method)(AA...);
    };
   
  private: 

   static R EmptyFunction(AA ...) { return DefaultFunction<R>::Func(); }
   
   static R FuncProxy(Handle ctx,AA ... aa)
    {
     R (*func_ptr)(AA...);
     
     func_ptr=(R (*)(AA...))ctx.func_ptr;
     
     return func_ptr(aa...);
    }
   
   void init(R (*func)(AA...))
    {
     obj=0; 
     ptr.func=FuncProxy;
     ptr.ctx=(Handle::FuncPtr)func;
    }
   
  public: 
   
   // constructors

   Function()
    {
     init(EmptyFunction);
    }

   Function(NothingType)
    {
     init(EmptyFunction);
    }

   Function(R (*func)(AA...)) 
    {
     init(func);
    }
   
   Function(R (*func)(Handle ctx,AA...),Handle ctx) 
    { 
     obj=0;
     ptr.func=func;
     ptr.ctx=ctx;
    }

   template <class T>
   Function(T *obj_,R (T::*method_)(AA...))
    {
     obj=obj_;
     method=static_cast<R (Funchor::*)(AA...)>(method_);
    }
   
   // methods

   bool operator + () const { return obj!=0 || ptr.func!=FuncProxy || ptr.ctx.func_ptr!=(Handle::FuncPtr)EmptyFunction; }
 
   bool operator ! () const { return obj==0 && ptr.func==FuncProxy && ptr.ctx.func_ptr==(Handle::FuncPtr)EmptyFunction; }

   template <class ... TT>
   R operator () (TT && ... tt)
    {
     if( obj ) return (obj->*method)( std::forward<TT>(tt)... );

     return ptr.func(ptr.ctx, std::forward<TT>(tt)... );
    }
 };

/* struct Funchor */

struct Funchor
 {
  template <class T,class R,class ... AA>
  static Function<R (AA...)> FunctionOf(T *obj,R (T::*method)(AA...)) 
   {
    return Function<R (AA...)>(obj,method);
   }
 };

//
// class T : public Funchor
//  {
//   public:
//
//    void method();
//
//    Function<void (void)> function_method() { return FunctionOf(this,&T::method); }
//  };
//

/* type Funchor_nocopy */

typedef NoCopyBase<Funchor> Funchor_nocopy;

} // namespace CCore
 
#endif
 

