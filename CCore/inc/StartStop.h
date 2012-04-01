/* StartStop.h */ 
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

#ifndef CCore_inc_StartStop_h
#define CCore_inc_StartStop_h

#include <CCore/inc/Task.h>
 
namespace CCore {

/* classes */ 

template <class T> class StartStopObject;

/* class StartStopObject<T> */ 

template <class T> 
class StartStopObject : NoCopy
 {
   T &obj;
   Sem stop_sem;
   
  public:
  
   template <class ... TT>
   StartStopObject(T &obj_,TT ... tt)
    : obj(obj_),
      stop_sem("StartStopObject")
    {
     obj_.prepareRun();
    
     RunFuncTask( [&] () { obj_.objRun(); } ,stop_sem.function_give(),tt...);
     
     obj_.completeRun(); // assume no throw
    }
   
   ~StartStopObject() 
    {
     obj.signalStop(); 
     
     stop_sem.take();
     
     obj.completeStop();
    }
 };
 
} // namespace CCore
 
#endif
 

