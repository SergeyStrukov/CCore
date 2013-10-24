/* NewDelete.h */ 
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

#ifndef CCore_inc_NewDelete_h
#define CCore_inc_NewDelete_h

#include <CCore/inc/MemBase.h>

namespace CCore {

/* classes */

struct DefaultHeapAlloc;

template <class AllocInit> class CustomAllocGuard;

/* struct DefaultHeapAlloc */

struct DefaultHeapAlloc
 {
  DefaultHeapAlloc() {}
  
  using AllocType = DefaultHeapAlloc ;
  
  void * alloc(ulen len) { return MemAlloc(len); }
  
  void free(void *ptr,ulen) { MemFree(ptr); }
 };

/* class CustomAllocGuard<AllocInit> */

template <class AllocInit>
class CustomAllocGuard : NoCopy
 {
   typedef typename AllocInit::AllocType AllocType;
 
   AllocType alloc;
   ulen len;
   void *mem;
   
  public: 
   
   CustomAllocGuard(AllocInit init,ulen len_)
    : alloc(init)
    {
     len=len_;
     mem=alloc.alloc(len);
    }
   
   ~CustomAllocGuard()
    {
     if( mem ) alloc.free(mem,len);
    }
   
   Place<void> getPlace() { return PlaceAt(mem); }
   
   void disarm() { mem=0; }
 };

/* New() */

template <class T,class AllocInit,class ... SS>
T * New(AllocInit init,SS && ... ss)
 {
  CustomAllocGuard<AllocInit> alloc(init,sizeof (T));
  
  T *ret=new(alloc.getPlace()) T( std::forward<SS>(ss)... );
  
  alloc.disarm();
  
  return ret;
 }

/* Delete() */

template <class T,class AllocInit>
void Delete(AllocInit init,T *obj)
 {
  typedef typename AllocInit::AllocType AllocType;
  
  obj->~T();
  
  AllocType alloc(init);
  
  alloc.free(obj,sizeof (T));
 }

} // namespace CCore
 
#endif
 

