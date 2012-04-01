/* test0005.Quick.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/base/Quick.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0005 {

/* struct BitCur */ 

struct BitCur
 {
  Quick::ScanUInt value;
  unsigned bit;
  
  BitCur()
   {
    value=1;
    bit=0;
   }
   
  bool operator + () const { return value; } 
  
  void operator ++ ()
   {
    value<<=1;
    bit++;
   }
 };
 
/* class Engine */

class Engine : NoCopy
 {
   static const unsigned Rep = 1000000 ;
 
   Random random;
   
  private: 
   
   Quick::ScanUInt get() { return random.next_uint<Quick::ScanUInt>(); }
   
   template <class UInt>
   void test_swap(UInt val,UInt ret)
    {
     for(unsigned cnt=Meta::UIntBits<UInt>::Ret/8,shift=8*(cnt-1); cnt ;cnt--,ret>>=8,val<<=8)
       {
        if( (ret&0xFF)!=((val>>shift)&0xFF) )
          {
           Printf(Exception,"test_swap() failed");
          }
       }
    }
   
  public:
  
   Engine() {}
   
   void test1();
   void test2();
   void test3();
   void test4();
   void test5();
   void test6();
   void test7();
 };
 
void Engine::test1()
 {
  for(BitCur cur; +cur ;++cur)
    {
     unsigned msbit=Quick::ScanMSBit(cur.value);
     unsigned lsbit=Quick::ScanLSBit(cur.value);
     
     if( cur.bit!=msbit )
       {
        Printf(Exception,"Failed at value = #.h; msbit = #;",cur.value,msbit);
       }
    
     if( cur.bit!=lsbit )
       {
        Printf(Exception,"Failed at value = #.h; lsbit = #;",cur.value,lsbit);
       }
       
     Printf(Con,"ScanBit #; #; #;\n",cur.bit,msbit,lsbit);
    }
 }
 
void Engine::test2()
 {
  for(BitCur cur; +cur ;++cur)  
    {
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        Quick::ScanUInt val=(get()<<1)|1;
     
        val<<=cur.bit;
        
        unsigned lsbit=Quick::ScanLSBit(val);
     
        if( lsbit!=cur.bit ) 
          {
           Printf(Exception,"Failed at value = #.h; lsbit = #;\n",val,lsbit);
          }
       }
    }
 }
 
void Engine::test3()
 {
  for(BitCur cur; +cur ;++cur)  
    {
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        Quick::ScanUInt val=(get()>>1)^Quick::ScanUInt(-1);
     
        val>>=(Meta::UIntBits<Quick::ScanUInt>::Ret-1-cur.bit);
        
        unsigned msbit=Quick::ScanMSBit(val);
     
        if( msbit!=cur.bit ) 
          {
           Printf(Exception,"Failed at value = #.h; msbit = #;\n",val,msbit);
          }
       }
    }
 }
 
void Engine::test4()
 {
  {
   uint16 val=random.next16();
   uint16 ret=Quick::ByteSwap16(val);
   
   Printf(Con,"val = #5.hi; ret = #5.hi;\n",val,ret);
  }
  {
   uint32 val=random.next32();
   uint32 ret=Quick::ByteSwap32(val);
   
   Printf(Con,"val = #9.hi; ret = #9.hi;\n",val,ret);
  }
  {
   uint64 val=random.next64();
   uint64 ret=Quick::ByteSwap64(val);
   
   Printf(Con,"val = #17.hi; ret = #17.hi;\n",val,ret);
  }
 } 
 
void Engine::test5()
 {
  for(unsigned cnt=Rep; cnt ;cnt--)
    {
     uint16 val=random.next16();
     uint16 ret=Quick::ByteSwap16(val);
     
     test_swap(val,ret);
    }
 }
 
void Engine::test6()
 {
  for(unsigned cnt=Rep; cnt ;cnt--)
    {
     uint32 val=random.next32();
     uint32 ret=Quick::ByteSwap32(val);
     
     test_swap(val,ret);
    }
 }
 
void Engine::test7()
 {
  for(unsigned cnt=Rep; cnt ;cnt--)
    {
     uint64 val=random.next64();
     uint64 ret=Quick::ByteSwap64(val);
     
     test_swap(val,ret);
    }
 }
 
} // namespace Private_0005
 
using namespace Private_0005; 
 
/* Testit<5> */ 

template<>
const char *const Testit<5>::Name="Test5 Quick";

template<>
bool Testit<5>::Main() 
 { 
  Engine engine;
  
  engine.test1();
  engine.test2();
  engine.test3();
  engine.test4();
  engine.test5();
  engine.test6();
  engine.test7();
  
  return true;
 }
 
} // namespace App
 
