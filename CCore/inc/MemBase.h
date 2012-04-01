/* MemBase.h */ 
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

#ifndef CCore_inc_MemBase_h
#define CCore_inc_MemBase_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/PlanInit.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_MemBase();

/* words */ 

enum JustTryType { JustTry };
 
/* functions */ 

void GuardNoMem(ulen len);

/* Mem...() */  
 
void * TryMemAlloc(ulen len) noexcept;

void * MemAlloc(ulen len);

ulen MemLen(const void *mem);       // mem may == 0

bool MemExtend(void *mem,ulen len); // mem may == 0

bool MemShrink(void *mem,ulen len); // mem may == 0
 
void MemFree(void *mem);            // mem may == 0

void MemLim(ulen limit);

/* classes */ 

struct MemStatData;

struct MemStat;

struct MemPeak;

class MemScope;

struct MemBase;

/* struct MemStatData */ 

struct MemStatData
 {
  ulen block_count;
  ulen len_count;
  
  MemStatData()
   {
    block_count=0;
    len_count=0;
   }
  
  // count
  
  void add(ulen len) { block_count++; len_count+=len; }
  
  void del(ulen len) { block_count--; len_count-=len; }
  
  void extend(ulen delta) { len_count+=delta; }
  
  void shrink(ulen delta) { len_count-=delta; }
  
  // set
  
  void set(const MemStatData &obj) { *this=obj; }
  
  void setMax(const MemStatData &obj)
   {
    if( obj.len_count>len_count ) set(obj);
   }
  
  // compare
  
  bool operator == (const MemStatData &obj) const 
   { 
    return block_count==obj.block_count && len_count==obj.len_count ; 
   }
  
  bool operator != (const MemStatData &obj) const 
   { 
    return block_count!=obj.block_count || len_count!=obj.len_count ; 
   }
  
  // print object
   
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#; blocks, #; total length)",block_count,len_count);
   }
 };
 
/* struct MemStat */  

struct MemStat : MemStatData
 {
  MemStat();
 };
 
/* struct MemPeak */ 

struct MemPeak : MemStatData
 {
  MemPeak();
 };
 
/* class MemScope */ 

class MemScope : NoCopy
 {
   MemStat on_init;
   
  public: 
  
   MemScope() {}
   
   ~MemScope();
 };
 
/* struct MemBase */ 

struct MemBase
 {
  // placement new/delete
  
  void * operator new(std::size_t,Place<void> place) { return place; }
   
  void operator delete(void *,Place<void>) {}
  
  // new/delete
   
  void * operator new(std::size_t len) { return MemAlloc(len); }
  
  void * operator new(std::size_t len,JustTryType) noexcept { return TryMemAlloc(len); }
  
  void operator delete(void *mem) { MemFree(mem); }
  
  // extra space
  
  template <class T>
  static Place<void> ExtraSpace(T *obj) { return PlaceAt(obj)+Align(sizeof (T)); }
  
  void * operator new(std::size_t len,ulen extra,ulen size_of=1) { return MemAlloc(LenOf(extra,size_of,Align(len))); }
  
  void operator delete(void *mem,ulen,ulen) { MemFree(mem); }
 };

/* type MemBase_nocopy */

typedef NoCopyBase<MemBase> MemBase_nocopy;
 
} // namespace CCore
 
#endif
 

