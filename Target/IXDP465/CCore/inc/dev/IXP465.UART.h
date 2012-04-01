/* IXP465.UART.h */ 
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

#ifndef CCore_inc_dev_IXP465_UART_h
#define CCore_inc_dev_IXP465_UART_h

#include <CCore/inc/dev/IXP465.h>
#include <CCore/inc/dev/DevRW.h>

namespace IXP465 {
namespace UART {

/* IXP465.UART.desc -> IXP465.UART.gen.h */ 

#include <CCore/inc/dev/IXP465.UART.gen.h>

/* enum SpeedDiv */  

enum SpeedDiv : uint16 // Speed = 14.7456 MHz / (16*Div)
 {
  SpeedDiv_1200    = 0x0300,
  SpeedDiv_2400    = 0x0180,
  SpeedDiv_4800    = 0x00C0,
  SpeedDiv_9600    = 0x0060,
  
  SpeedDiv_14400   = 0x0040,
  SpeedDiv_19200   = 0x0030,
  SpeedDiv_28800   = 0x0020,
  SpeedDiv_57600   = 0x0010,
  
  SpeedDiv_115200  = 0x0008,
  SpeedDiv_230400  = 0x0004,
  SpeedDiv_460800  = 0x0002,
  SpeedDiv_921600  = 0x0001
 };
  
/* struct Bar */  

struct Bar : UARTBar<CCore::Dev::RegRW>
 {
  template <class T>
  explicit Bar(T select) // 0-1 
   : UARTBar<CCore::Dev::RegRW>(0xC8000000+0x1000*select) 
   {
   } 
 };
 
} // namespace UART
} // namespace IXP465
 
#endif


