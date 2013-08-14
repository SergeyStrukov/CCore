/* Quick.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/base/Quick.h>
 
namespace CCore {
namespace Quick {

/* functions */ 

#if 0
 
unsigned ScanLSBit(ScanUInt value) noexcept
 {
  unsigned ret=0;
 
  if( !(value&0xFFFFFFFF) ) ret+=32,value>>=32;
  if( !(value&0x0000FFFF) ) ret+=16,value>>=16;
  if( !(value&0x000000FF) ) ret+= 8,value>>= 8;
  
  static const unsigned Table[256]=
   {
    0,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    5,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    
    6,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    5,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    
    7,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    5,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    
    6,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    5,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0,
    4,0,1,0, 2,0,1,0, 3,0,1,0, 2,0,1,0
   };

  return ret+Table[value&0x00FF];
 }
 
#endif  

#if 0
 
unsigned ScanMSBit(ScanUInt value) noexcept
 {
  unsigned ret=0;
  
  if( value&0xFFFFFFFF00000000 ) ret+=32,value>>=32;
  if( value&0xFFFF0000         ) ret+=16,value>>=16;
  if( value&0xFF00             ) ret+= 8,value>>= 8;
  
  static const unsigned Table[256]=
   {
    0,0,1,1, 2,2,2,2, 3,3,3,3, 3,3,3,3,
    4,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,4,4,
    5,5,5,5, 5,5,5,5, 5,5,5,5, 5,5,5,5,
    5,5,5,5, 5,5,5,5, 5,5,5,5, 5,5,5,5,
    
    6,6,6,6, 6,6,6,6, 6,6,6,6, 6,6,6,6,
    6,6,6,6, 6,6,6,6, 6,6,6,6, 6,6,6,6,
    6,6,6,6, 6,6,6,6, 6,6,6,6, 6,6,6,6,
    6,6,6,6, 6,6,6,6, 6,6,6,6, 6,6,6,6,
    
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7,
    7,7,7,7, 7,7,7,7, 7,7,7,7, 7,7,7,7
   };
  
  return ret+Table[value&0x00FF];
 }
 
#endif  

#if 0

uint16 ByteSwap16(uint16 value) noexcept
 {
  return uint16( (value>>8)|(value<<8) );
 }
 
#endif  

#if 0

uint32 ByteSwap32(uint32 value) noexcept
 {
  return uint32( (value<<24)|(value>>24)|((value>>8)&0xFF00)|((value<<8)&0xFF0000) );
 }
 
#endif  

#if 0

uint64 ByteSwap64(uint64 value) noexcept
 {
  uint32 hi=uint32(value>>32);
  uint32 lo=uint32(value);
 
  return ByteSwap32(hi)|(uint64(ByteSwap32(lo))<<32);
 }
 
#endif  

} // namespace Quick
} // namespace CCore
 

