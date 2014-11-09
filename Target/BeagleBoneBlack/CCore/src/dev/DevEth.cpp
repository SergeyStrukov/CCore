/* DevEth.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/dev/DevEth.h>

#include <CCore/inc/dev/AM3359.ETH.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>
#include <CCore/inc/dev/AM3359.PRCM.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Dev {

/* class EthControl */

Net::MACAddress EthControl::MakeAddress(uint32 hi,uint32 lo)
 {
  return Net::MACAddress(uint8(lo),uint8(lo>>8),uint8(lo>>16),uint8(lo>>24),uint8(hi),uint8(hi>>8));
 }

void EthControl::connect()
 {
  Mutex::Lock lock(Dev::ControlMutex);
  
  using namespace AM3359::CONTROL;
  
  Bar bar;
  
  bar.get_GMIISelect()
     .set_Port1(GMIISelect_Port1_GMII)
     .set_Port2(GMIISelect_Port2_GMII)
     .setbit(GMIISelect_Port1RMIIClockInput|GMIISelect_Port2RMIIClockInput)
     .setTo(bar);
  
  bar.get_EthResetIsolation()
     .clearbit(EthResetIsolation_Enable)
     .setTo(bar);
  
  address1=MakeAddress(bar.get_MAC0Hi(),bar.get_MAC0Lo());
  address2=MakeAddress(bar.get_MAC1Hi(),bar.get_MAC1Lo());
  
  bar.null_PadMux()
     .set_MuxMode(0)
     .setbit(PadMux_NoPullUpDown)
     .set(bar.to_Conf_MII1_TX_EN())
     .set(bar.to_Conf_MII1_TXD3())
     .set(bar.to_Conf_MII1_TXD2())
     .set(bar.to_Conf_MII1_TXD1())
     .set(bar.to_Conf_MII1_TXD0());
  
#if 0
  
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD0());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD1());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD2());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD3());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TX_EN());    // 0
  
#endif  
  
  bar.null_PadMux()
     .set_MuxMode(0)
     .setbit(PadMux_RXEn)
     .set(bar.to_Conf_MII1_RXD0())
     .set(bar.to_Conf_MII1_RXD1())
     .set(bar.to_Conf_MII1_RXD2())
     .set(bar.to_Conf_MII1_RXD3())
     .set(bar.to_Conf_MII1_RX_ER())
     .set(bar.to_Conf_MII1_RX_DV())
     .set(bar.to_Conf_MII1_TX_CLK())
     .set(bar.to_Conf_MII1_RX_CLK())
     .set(bar.to_Conf_MII1_COL())
     .set(bar.to_Conf_MII1_CRS());
  
#if 0
     
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD0());     // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD1());     // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD2());     // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD3());     // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_ER());    // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_DV());    // Rx 0 PD
  
  Printf(Con,"#;\n",bar.get_Conf_MII1_TX_CLK());   // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_CLK());   // Rx 0 PD
  
  Printf(Con,"#;\n",bar.get_Conf_MII1_COL());      // Rx 0 PD
  Printf(Con,"#;\n",bar.get_Conf_MII1_CRS());      // Rx 0 PD
  
#endif  
  
  bar.null_PadMux()
     .set_MuxMode(0)
     .setbit(PadMux_RXEn|PadMux_PullUp)
     .set(bar.to_Conf_MDIO());
  
  bar.null_PadMux()
     .set_MuxMode(0)
     .setbit(PadMux_NoPullUpDown)
     .set(bar.to_Conf_MDC());
  
#if 0
  
  Printf(Con,"#;\n",bar.get_Conf_MDIO());          // Rx 0 PU
  Printf(Con,"#;\n",bar.get_Conf_MDC());           // 0
  
#endif  
  
  bar.null_PadMux()
     .set_MuxMode(7)
     .setbit(PadMux_RXEn)
     .set(bar.to_Conf_RMII1_REF_CLK());
  
#if 0
  
  Printf(Con,"#;\n",bar.get_Conf_RMII1_REF_CLK()); // Rx 7 PD
  
#endif  
 }
   
void EthControl::enable()
 {
  Mutex::Lock lock(Dev::ControlMutex);
  
  using namespace AM3359::PRCM;
  
#if 0
  
  {
   BarWKUP bar;
   
   Printf(Con,"IdleStatus = #;\n",bar.get_COREIdleStatus());   // Locked
   Printf(Con,"ClockSelect = #;\n",bar.get_COREClockSelect()); // Mul 1000 Div 23
   Printf(Con,"ClockMode = #;\n",bar.get_COREClockMode());     // Lock
   
   Printf(Con,"M4 = #;\n",bar.get_CORE_M4Div());               // Div 10
   Printf(Con,"M5 = #;\n",bar.get_CORE_M5Div());               // Div 8
   Printf(Con,"M6 = #;\n",bar.get_CORE_M6Div());               // Div 4
  }

  {
   BarDPLL bar;
   
   bar.get_CPTSClockSelect()
      .clearbit(CPTSClockSelect_M4)
      .setTo(bar);
   
   Printf(Con,"M4/M5 = #;\n",bar.get_CPTSClockSelect());       // M5
  }
  
#endif  
  
  {
   BarPER bar;
   
   bar.get_EthClockControl()
      .set_Control(EthClockControl_Control_ForceWakeup)
      .setTo(bar);
   
   bar.get_Eth()
      .set_Mode(ClockStandbyControl_Mode_Enable)
      .set(bar.to_Eth());
   
   while( bar.get_Eth().get_IdleStatus()!=ClockStandbyControl_IdleStatus_Running );

#if 0
   
   Printf(Con,"Clock = #;\n",bar.get_EthClockControl()); // ForceWakeup
   Printf(Con,"Module = #;\n",bar.get_Eth());            // Enable
   
#endif   
  }
 }
  
void EthControl::reset()
 {
  // TODO
 }

void EthControl::disable()
 {
  Mutex::Lock lock(Dev::ControlMutex);
  
  using namespace AM3359::PRCM;
  
  {
   BarPER bar;
   
   bar.get_Eth()
      .set_Mode(ClockStandbyControl_Mode_Disable)
      .set(bar.to_Eth());
   
   while( bar.get_Eth().get_IdleStatus()!=ClockStandbyControl_IdleStatus_Disabled );
  }
 }

EthControl::EthControl()
 : InstanceLock<EthControl>("Eth")
 {
  connect();
  enable();
  reset();
 }
   
EthControl::~EthControl()
 {
  reset();
  disable();
 }

} // namespace Dev
} // namespace CCore


