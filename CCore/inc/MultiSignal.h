/* MultiSignal.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_MultiSignal_h
#define CCore_inc_MultiSignal_h

#include <CCore/inc/Signal.h>
#include <CCore/inc/Optional.h>
#include <CCore/inc/DeferCall.h>
 
namespace CCore {

/* classes */

class MultiSignal;

class DeferMultiSignal;

/* class MultiSignal */

class MultiSignal : NoCopy
 {
   Optional optional;
   
  public:
  
   explicit MultiSignal(ulen max_slot) : optional(max_slot) {}
   
   ~MultiSignal() {}
   
   template <unsigned slot,class ... TT>
   void assert(TT... tt)
    {
     if( auto *s=optional.try_take<slot,Signal<TT...> >() ) s->assert(tt...);
    }
   
   template <unsigned slot,class ... TT>
   Signal<TT...> & take()
    {
     return *optional.take<slot,Signal<TT...> >();
    }
 };

/* class DeferMultiSignal */

class DeferMultiSignal : public MultiSignal
 {
   DeferInput<MultiSignal> input;
   
  public:
  
   explicit DeferMultiSignal(unsigned max_slot) : MultiSignal(max_slot),input(this) {}
   
   ~DeferMultiSignal() {}
   
   template <unsigned slot,class ... TT>
   void post(const TT & ... tt)
    {
     input.post<TT...>(&MultiSignal::assert<slot,TT...>,tt...);
    }
   
   template <unsigned slot,class ... TT>
   void post_first(const TT & ... tt)
    {
     input.post_first<TT...>(&MultiSignal::assert<slot,TT...>,tt...);
    }
 };

} // namespace CCore
 
#endif
 

