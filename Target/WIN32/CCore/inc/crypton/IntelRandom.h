/* IntelRandom.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_IntelRandom_h
#define CCore_inc_crypton_IntelRandom_h

#include <CCore/inc/Random.h>
 
namespace CCore {
namespace Crypton {

/* functions */

bool DetectIntelRDRAND();

void GuardIntelRDRANDNotAvailable();

inline void GuardIntelRDRAND()
 {
  if( !DetectIntelRDRAND() ) GuardIntelRDRANDNotAvailable();
 }

/* classes */

class IntelRandom;

/* class IntelRandom */ 

class IntelRandom : NoCopy
 {
  public:
  
   IntelRandom() { GuardIntelRDRAND(); }
   
   typedef uint32 UnitType;
   
   uint32 next();
   
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

} // namespace Crypton
} // namespace CCore
 
#endif
 

