/* HeapEngine.h */ 
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

#ifndef CCore_inc_HeapEngine_h
#define CCore_inc_HeapEngine_h

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Task.h>
 
namespace CCore {

/* classes */

template <class Heap> class HeapEngine;

/* class HeapEngine<Heap> */  

template <class Heap> 
class HeapEngine : NoCopy
 {
   Mutex mutex;
   
   Heap heap;
   MemStatData stat;
   MemStatData peak;
   ulen limit;
  
  private:
  
   bool overLim(ulen len) const
    {
     if( !limit ) return false;
    
     return stat.len_count>limit || len>(limit-stat.len_count) ;
    }
 
   void addStat(ulen len)
    {
     stat.add(len);
     peak.setMax(stat);
    }
 
   void delStat(ulen len)
    {
     stat.del(len);
    }
  
   void extendStat(ulen delta)
    {
     stat.extend(delta);
     peak.setMax(stat);
    }
 
   void shrinkStat(ulen delta)
    {
     stat.shrink(delta);
    }
  
  public:
  
   template <class ... SS>
   explicit HeapEngine(TextLabel name,SS && ... ss);
   
   ~HeapEngine();
   
   void * alloc(ulen len);
  
   ulen getLen(const void *mem);    // mem may == 0
  
   void free(void *mem);            // mem may == 0
  
   bool extend(void *mem,ulen len); // mem may == 0
  
   bool shrink(void *mem,ulen len); // mem may == 0
  
   void setLim(ulen limit);
  
   void getStat(MemStatData &ret);
  
   void getPeak(MemStatData &ret);
 };
 
template <class Heap> 
template <class ... SS>
HeapEngine<Heap>::HeapEngine(TextLabel name,SS && ... ss)
 : mutex(name),
   heap( std::forward<SS>(ss)... ),
   limit(0)
 {
 }
   
template <class Heap> 
HeapEngine<Heap>::~HeapEngine()
 {
 }
   
template <class Heap> 
void * HeapEngine<Heap>::alloc(ulen len)
 {
  Mutex::Lock lock(mutex);

  if( overLim(len) ) return 0;
 
  Space ret=heap.alloc(len);
  
  if( ret.len )
    {
     addStat(ret.len);

     return ret.mem;
    }
  
  return 0;
 }
  
template <class Heap> 
ulen HeapEngine<Heap>::getLen(const void *mem)
 {
  if( !mem ) return 0;
  
  Mutex::Lock lock(mutex);

  return heap.getLen(mem);
 }
  
template <class Heap> 
void HeapEngine<Heap>::free(void *mem)
 {
  if( !mem ) return;
  
  Mutex::Lock lock(mutex);
 
  ulen len=heap.free(mem);
  
  delStat(len);
 }
  
template <class Heap> 
bool HeapEngine<Heap>::extend(void *mem,ulen len)
 {
  if( !mem ) return false;
  
  Mutex::Lock lock(mutex);
  
  if( overLim(len) ) 
    {
     ulen memlen=heap.getLen(mem);
    
     if( len>=memlen && overLim(len-memlen) ) return false;
    }

  DeltaLen result=heap.extend(mem,len);

  extendStat(result.delta);

  return result.ok;
 }
  
template <class Heap> 
bool HeapEngine<Heap>::shrink(void *mem,ulen len)
 {
  if( !mem ) return false;
  
  Mutex::Lock lock(mutex);
  
  DeltaLen result=heap.shrink(mem,len);

  shrinkStat(result.delta);
  
  return result.ok;
 }
  
template <class Heap> 
void HeapEngine<Heap>::setLim(ulen limit_)
 {
  Mutex::Lock lock(mutex);
  
  limit=limit_;
 }
  
template <class Heap> 
void HeapEngine<Heap>::getStat(MemStatData &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat;
 }
  
template <class Heap> 
void HeapEngine<Heap>::getPeak(MemStatData &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=peak;
 }

} // namespace CCore
 
#endif
 

