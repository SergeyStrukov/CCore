/* IXP465.INT.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_IXP465_INT_h
#define CCore_inc_dev_IXP465_INT_h

#include <CCore/inc/dev/IXP465.h>
#include <CCore/inc/dev/DevRW.h>

namespace IXP465 {
namespace INT {

/* IXP465.INT.desc -> IXP465.INT.gen.h */ 

#include <CCore/inc/dev/IXP465.INT.gen.h>

/* enum Int */ 

enum Int
 {
  // 0-31
 
  Int_NPE_A     =  0,
  Int_NPE_B     =  1,
  Int_NPE_C     =  2,
  
  Int_QMLO      =  3,
  Int_QMHI      =  4,
  
  Int_T0        =  5,
  
  Int_GPIO0     =  6,
  Int_GPIO1     =  7,
  
  Int_PCI       =  8,
  Int_PCI_DMA1  =  9,
  Int_PCI_DMA2  = 10,
  
  Int_T1        = 11,
  Int_USBDev    = 12,
  Int_UART1     = 13,
  Int_TS        = 14,
  Int_UART0     = 15,
  Int_WD        = 16,
  Int_APB_PMU   = 17,
  Int_CPU_PMU   = 18,
  
  Int_GPIO2     = 19,
  Int_GPIO3     = 20,
  Int_GPIO4     = 21,
  Int_GPIO5     = 22,
  Int_GPIO6     = 23,
  Int_GPIO7     = 24,
  Int_GPIO8     = 25,
  Int_GPIO9     = 26,
  Int_GPIO10    = 27,
  Int_GPIO11    = 28,
  Int_GPIO12    = 29,
  
  Int_SWI0      = 30,
  Int_SWI1      = 31,
  
  // 32-63
  
  Int_USBHost   = 32,
  Int_I2C       = 33,
  Int_SSP       = 34,
  Int_TSYNC     = 35,
  Int_EAU       = 36,
  Int_SHA       = 37,
  
   // 38-57 reserved
  
  Int_SWCP      = 58,
  
   // 59 reserved
   
  Int_QMERR     = 60,
  Int_MCU       = 61,
  Int_EXP       = 62
  
   // 63 reserved
 };
 
/* struct IntBit */ 

struct IntBit
 {
  uint32 bit;
  
  IntBit() : bit(0) {}
  
  explicit IntBit(Int nbit) { set(nbit); }
  
  bool set(Int nbit)
   {
    if( nbit>=32 )
      {
       bit = uint32(1)<<(nbit-32) ;
       
       return true;
      }
    else
      {
       bit = uint32(1)<<nbit ;
       
       return false;
      }  
   }
  
  operator Bits_Status() const { return Bits_Status(bit); }
  
  operator Bits_Status2() const { return Bits_Status2(bit); }
 };
 
/* struct Bar */ 

struct Bar : INTBar<CCore::Dev::RegRW>
 {
  Bar() : INTBar<CCore::Dev::RegRW>(0xC8003000) {}
 };
 
} // namespace INT
} // namespace IXP465
 
#endif

