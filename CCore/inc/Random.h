/* Random.h */ 
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

#ifndef CCore_inc_Random_h
#define CCore_inc_Random_h

#include <CCore/inc/MersenneTwister.h>
#include <CCore/inc/UIntSplit.h>
 
namespace CCore {
 
/* classes */ 

template <class UInt> struct RandomFill_gen;

template <class UInt> struct RandomFill;

class Random;

/* struct RandomFill_gen<UInt> */ 

template <class UInt> 
struct RandomFill_gen
 {
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::RandomFill_gen<UInt> : UInt must be an unsigned integral type");
 
  template <unsigned DstBit,unsigned SrcBit> struct Extra_loop;
  
  template <unsigned DstBit,unsigned SrcBit> struct Extra_last;
  
  template <unsigned DstBit,unsigned SrcBit>
  using Extra = Meta::Select<( DstBit>SrcBit ), Extra_loop<DstBit,SrcBit> , Extra_last<DstBit,SrcBit> > ;
 
  template <class T>
  static UInt Do(T &random);
 };
 
template <class UInt> 
template <unsigned DstBit,unsigned SrcBit> 
struct RandomFill_gen<UInt>::Extra_loop
 {
  template <class T>
  static void Do(UInt &ret,T &random)
   {
    const unsigned Delta=Meta::UIntBits<typename T::UnitType>::Ret;
    
    ret=UInt( (ret<<Delta)^random.next() );
    
    Extra<DstBit,SrcBit+Delta>::Do(ret,random);
   }
 };
  
template <class UInt> 
template <unsigned DstBit,unsigned SrcBit> 
struct RandomFill_gen<UInt>::Extra_last
 {
  template <class T>
  static void Do(UInt &,T &) {}
 };
  
template <class UInt> 
template <class T>
UInt RandomFill_gen<UInt>::Do(T &random)
 {
  UInt ret=UInt(random.next());
  
  Extra<Meta::UIntBits<UInt>::Ret,Meta::UIntBits<typename T::UnitType>::Ret>::Do(ret,random);
    
  return ret;
 }
 
/* struct RandomFill<UInt> */  

template <class UInt> 
struct RandomFill : RandomFill_gen<UInt> {};
  
template <> 
struct RandomFill<uint8>
 {
  template <class T>
  static uint8 Do(T &random) { return random.next8(); }
 };
 
template <> 
struct RandomFill<uint16>
 {
  template <class T>
  static uint16 Do(T &random) { return random.next16(); }
 };
 
template <> 
struct RandomFill<uint32>
 {
  template <class T>
  static uint32 Do(T &random) { return random.next32(); }
 };
 
template <> 
struct RandomFill<uint64>
 {
  template <class T>
  static uint64 Do(T &random) { return random.next64(); }
 };
 
/* class Random */ 

class Random : public MersenneTwister::Gen<MersenneTwister::MT19937>
 {
  public:
  
   Random();
   
   uint8  next8()  { return uint8 (next()); }
   
   uint16 next16() { return uint16(next()); }
   
   uint32 next32() { return uint32(next()); }
   
   uint64 next64() 
    {
     UIntSplit<uint64,uint32> split;
     
     split[0]=next32();
     split[1]=next32();
     
     return split.get(); 
    }
    
   template <class UInt> 
   UInt next_uint() { return RandomFill<UInt>::Do(*this); }
   
   uint32 select(uint32 lim) { return lim?uint32( next64()%lim ):next32(); }
   
   uint32 select(uint32 a,uint32 b) { return a+select(b-a+1); }
   
   template <class UInt> 
   void fill(PtrLen<UInt> r) 
    { 
     for(; +r ;++r) *r=next_uint<UInt>(); 
    }
   
   template <class UInt> 
   void fill(UInt *ptr,ulen len) 
    { 
     fill(Range(ptr,len));
    } 
 };
 
} // namespace CCore
 
#endif
 

