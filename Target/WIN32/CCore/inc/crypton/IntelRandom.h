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

class IntelRandom : public RandomBase<IntelRandom>
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
 };

} // namespace Crypton
} // namespace CCore
 
#endif
 

