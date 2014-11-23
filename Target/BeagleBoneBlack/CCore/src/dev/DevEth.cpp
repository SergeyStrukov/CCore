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
  using namespace AM3359::ETH;
  
  {
   BarWR bar;
   
   bar.null_WRSoftReset()
      .setbit(WRSoftReset_Reset)
      .setTo(bar);
   
   while( bar.get_WRSoftReset().maskbit(WRSoftReset_Reset)!=0 );
  }
  
  {
   BarSwitch bar;
   
   bar.null_SwitchSoftReset()
      .setbit(SwitchSoftReset_Reset)
      .setTo(bar);
   
   while( bar.get_SwitchSoftReset().maskbit(SwitchSoftReset_Reset)!=0 );
  }
  
  {
   BarSliver1 bar;
   
   bar.null_SliverSoftReset()
      .setbit(SliverSoftReset_Reset)
      .setTo(bar);
   
   while( bar.get_SliverSoftReset().maskbit(SliverSoftReset_Reset)!=0 );
  }
  
  {
   BarSliver2 bar;
   
   bar.null_SliverSoftReset()
      .setbit(SliverSoftReset_Reset)
      .setTo(bar);
   
   while( bar.get_SliverSoftReset().maskbit(SliverSoftReset_Reset)!=0 );
  }
  
  {
   BarDMA bar;
   
   bar.null_DMASoftReset()
      .setbit(DMASoftReset_Reset)
      .setTo(bar);
   
   while( bar.get_DMASoftReset().maskbit(DMASoftReset_Reset)!=0 );
  }

  {
   BarDesc bar;
   
   for(uint32 ind=0; ind<8 ;ind++) bar.set_HeadTx_null(ind);
   
   for(uint32 ind=0; ind<8 ;ind++) bar.set_HeadRx_null(ind);
   
   for(uint32 ind=0; ind<8 ;ind++) bar.set_CompleteTx_null(ind);
   
   for(uint32 ind=0; ind<8 ;ind++) bar.set_CompleteRx_null(ind);
  }
 }

void EthControl::prepare()
 {
  using namespace AM3359::ETH;
  
  {
   BarWR bar;
   
   bar.null_WRControl()
      .set_IdleMode(WRControl_IdleMode_NoIdle)
      .set_StandbyMode(WRControl_StandbyMode_NoStandby)
      .setTo(bar);
   
   bar.null_WRIntControl()
      .setbit(WRIntControl_C0RxPace|WRIntControl_C0TxPace)
      .setTo(bar);
   
   bar.set_WRC0RxThreshEnable(0xFF);
   bar.set_WRC0RxEnable(0xFF);
   bar.set_WRC0TxEnable(0xFF);
   bar.set_WRC0MiscEnable(0x1F);
   
   bar.null_WRC0RxIntLim().set_Lim(10).setTo(bar);
   bar.null_WRC0TxIntLim().set_Lim(10).setTo(bar);
  } 
  
  {
   BarSwitch bar;

   bar.null_SwitchControl()
      .setTo(bar);

   bar.null_SwitchStatPort()
      .setbit(SwitchStatPort_Port0Enable|SwitchStatPort_Port1Enable)
      .setTo(bar);

   bar.null_SwitchTxPriType()
      .setTo(bar);

   bar.null_SwitchRate()
      .set_Host(3)
      .set_Sliver(3)
      .setTo(bar);

   bar.null_SwitchTxShortGap()
      .set_Thresh(11)
      .setTo(bar);
   
   bar.null_SwitchTxStart()
      .set_Len(32)
      .setTo(bar);
   
   bar.null_SwitchRxFlowControl()
      .setbit(SwitchRxFlowControl_Port0Enable|SwitchRxFlowControl_Port1Enable)
      .setTo(bar);
  }
  
  {
   BarPort0 bar;

   bar.null_PortControl()
      .setTo(bar);
   
   bar.null_PortFIFOLen()
      .set_RxLen(PortFIFOLen_RxLen_Default0)
      .set_TxLen(PortFIFOLen_TxLen_Default0)
      .setTo(bar);
   
   bar.null_PortTxFIFOControl()
      .set_WordLen(0xC0)
      .set_Rem(4)
      .set_Mode(PortTxFIFOControl_Mode_Normal)
      .setTo(bar); 
   
   bar.null_PortVLANControl()
      .setTo(bar);
   
   bar.null_PortTxPriMap()
      .set_Pri0(0)
      .set_Pri1(0)
      .set_Pri2(0)
      .set_Pri3(0)
      .set_Pri4(0)
      .set_Pri5(0)
      .set_Pri6(0)
      .set_Pri7(0)
      .setTo(bar);
   
   bar.null_PortRxDMAPriMap()
      .set_P1Pri0(0)
      .set_P1Pri1(0)
      .set_P1Pri2(0)
      .set_P1Pri3(0)
      .set_P2Pri0(0)
      .set_P2Pri1(0)
      .set_P2Pri2(0)
      .set_P2Pri3(0)
      .setTo(bar);
  }
  
  {
   BarPort1 bar;
   
   bar.null_PortControl()
      .setTo(bar);
   
   bar.null_PortFIFOLen()
      .set_RxLen((Field_PortFIFOLen_RxLen)(PortFIFOLen_RxLen_Default+3))
      .set_TxLen((Field_PortFIFOLen_TxLen)(PortFIFOLen_TxLen_Default-3))
      .setTo(bar);
   
   bar.null_PortTxFIFOControl()
      .set_WordLen(0xC0)
      .set_Rem(4)
      .set_Mode(PortTxFIFOControl_Mode_Normal)
      .set_HostRem(8)
      .setTo(bar);
   
   bar.null_PortVLANControl()
      .setTo(bar);
   
   bar.null_PortTxPriMap()
      .set_Pri0(0)
      .set_Pri1(0)
      .set_Pri2(0)
      .set_Pri3(0)
      .set_Pri4(0)
      .set_Pri5(0)
      .set_Pri6(0)
      .set_Pri7(0)
      .setTo(bar);

   bar.null_PortMACHi()
      .set_Byte0(address1.address[0])
      .set_Byte1(address1.address[1])
      .setTo(bar);
   
   bar.null_PortMACLo()
      .set_Byte2(address1.address[2])
      .set_Byte3(address1.address[3])
      .set_Byte4(address1.address[4])
      .set_Byte5(address1.address[5])
      .setTo(bar);
  }
  
  {
   BarALE bar;

   bar.null_ALEControl()
      .setbit(ALEControl_ClearTable)
      .setTo(bar);
   
   bar.null_ALEControl()
      .setbit(ALEControl_EnableALE)
      .setTo(bar);
   
   bar.null_ALEPortControl()
      .set_State(ALEPortControl_State_Forward)
      .set(bar.to_ALEPort0Control());
   
   bar.null_ALEPortControl()
      .set_State(ALEPortControl_State_Forward)
      .set(bar.to_ALEPort1Control());
  } 
  
  {
   BarDMA bar;

   // TODO
   
  }
  
  {
   BarMDIO bar;
   
   // TODO
   
  }
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

void EthControl::show()
 {
  using namespace AM3359::ETH;

#if 0
  
  {
   BarWR bar;
   
   Printf(Con,"WRControl = #;\n",bar.get_WRControl());
   Printf(Con,"WRIntControl = #;\n",bar.get_WRIntControl());
   
   Printf(Con,"WRC0RxThreshEnable = #;\n",bar.get_WRC0RxThreshEnable());
   Printf(Con,"WRC0RxEnable = #;\n",bar.get_WRC0RxEnable());
   Printf(Con,"WRC0TxEnable = #;\n",bar.get_WRC0TxEnable());
   Printf(Con,"WRC0MiscEnable = #;\n",bar.get_WRC0MiscEnable());
   
   Printf(Con,"WRC0RxIntLim = #;\n",bar.get_WRC0RxIntLim());
   Printf(Con,"WRC0TxIntLim = #;\n",bar.get_WRC0TxIntLim());
   
#if 0   
   
   Printf(Con,"WRC1RxThreshEnable = #;\n",bar.get_WRC1RxThreshEnable());
   Printf(Con,"WRC1RxEnable = #;\n",bar.get_WRC1RxEnable());
   Printf(Con,"WRC1TxEnable = #;\n",bar.get_WRC1TxEnable());
   Printf(Con,"WRC1MiscEnable = #;\n",bar.get_WRC1MiscEnable());
   
   Printf(Con,"WRC1RxIntLim = #;\n",bar.get_WRC1RxIntLim());
   Printf(Con,"WRC1TxIntLim = #;\n",bar.get_WRC1TxIntLim());
   
   Printf(Con,"WRC2RxThreshEnable = #;\n",bar.get_WRC2RxThreshEnable());
   Printf(Con,"WRC2RxEnable = #;\n",bar.get_WRC2RxEnable());
   Printf(Con,"WRC2TxEnable = #;\n",bar.get_WRC2TxEnable());
   Printf(Con,"WRC2MiscEnable = #;\n",bar.get_WRC2MiscEnable());
   
   Printf(Con,"WRC2RxIntLim = #;\n",bar.get_WRC2RxIntLim());
   Printf(Con,"WRC2TxIntLim = #;\n",bar.get_WRC2TxIntLim());
   
#endif   
   
   Printf(Con,"WRRGMIIStatus = #;\n",bar.get_WRRGMIIStatus());
  }
  
#endif  
  
#if 0
  
  {
   BarSwitch bar;
   
   Printf(Con,"SwitchControl = #;\n",bar.get_SwitchControl());
   Printf(Con,"SwitchStatPort = #;\n",bar.get_SwitchStatPort());
   Printf(Con,"SwitchTxPriType = #;\n",bar.get_SwitchTxPriType());
   Printf(Con,"SwitchRate = #;\n",bar.get_SwitchRate());
   Printf(Con,"SwitchTxShortGap = #;\n",bar.get_SwitchTxShortGap());
   Printf(Con,"SwitchTxStart = #;\n",bar.get_SwitchTxStart());
   Printf(Con,"SwitchRxFlowControl = #;\n",bar.get_SwitchRxFlowControl()); // Port0Enable
   Printf(Con,"SwitchVLANLType = #;\n",bar.get_SwitchLType());             
   Printf(Con,"SwitchTSVLANLType = #;\n",bar.get_SwitchTSLType());          
   Printf(Con,"SwitchDLRLType = #;\n\n",bar.get_SwitchDLRLType());         
  }
  
#endif  
  
#if 0
  
  {
   BarPort0 bar;
   
   Printf(Con,"PortControl = #;\n",bar.get_PortControl());
   Printf(Con,"PortFIFOLen = #;\n",bar.get_PortFIFOLen());
   Printf(Con,"PortFIFOUse = #;\n",bar.get_PortFIFOUse());
   Printf(Con,"PortTxFIFOControl = #;\n",bar.get_PortTxFIFOControl());
   Printf(Con,"PortVLANControl = #;\n",bar.get_PortVLANControl());
   Printf(Con,"PortTxPriMap = #;\n",bar.get_PortTxPriMap());
   Printf(Con,"PortTxDMAPriMap = #;\n",bar.get_PortTxDMAPriMap());
   Printf(Con,"PortRxDMAPriMap = #;\n",bar.get_PortRxDMAPriMap());
   Printf(Con,"PortTOSPriMap0 = #;\n",bar.get_PortTOSPriMap0());
   Printf(Con,"PortTOSPriMap1 = #;\n",bar.get_PortTOSPriMap1());
   Printf(Con,"PortTOSPriMap2 = #;\n",bar.get_PortTOSPriMap2());
   Printf(Con,"PortTOSPriMap3 = #;\n",bar.get_PortTOSPriMap3());
   Printf(Con,"PortTOSPriMap4 = #;\n",bar.get_PortTOSPriMap4());
   Printf(Con,"PortTOSPriMap5 = #;\n",bar.get_PortTOSPriMap5());
   Printf(Con,"PortTOSPriMap6 = #;\n",bar.get_PortTOSPriMap6());
   Printf(Con,"PortTOSPriMap7 = #;\n\n",bar.get_PortTOSPriMap7());
  }
  
#endif
  
#if 0
  
  {
   BarPort1 bar;
   
   Printf(Con,"PortControl = #;\n",bar.get_PortControl());
   Printf(Con,"PortFIFOLen = #;\n",bar.get_PortFIFOLen());
   Printf(Con,"PortFIFOUse = #;\n",bar.get_PortFIFOUse());
   Printf(Con,"PortTxFIFOControl = #;\n",bar.get_PortTxFIFOControl());
   Printf(Con,"PortVLANControl = #;\n",bar.get_PortVLANControl());
   Printf(Con,"PortTxPriMap = #;\n",bar.get_PortTxPriMap());
   Printf(Con,"PortTimeSync = #;\n",bar.get_PortTimeSync());
   Printf(Con,"PortMACHi = #;\n",bar.get_PortMACHi());
   Printf(Con,"PortMACLo = #;\n",bar.get_PortMACLo());
   Printf(Con,"PortSendPercent = #;\n",bar.get_PortSendPercent());
   Printf(Con,"PortTOSPriMap0 = #;\n",bar.get_PortTOSPriMap0());
   Printf(Con,"PortTOSPriMap1 = #;\n",bar.get_PortTOSPriMap1());
   Printf(Con,"PortTOSPriMap2 = #;\n",bar.get_PortTOSPriMap2());
   Printf(Con,"PortTOSPriMap3 = #;\n",bar.get_PortTOSPriMap3());
   Printf(Con,"PortTOSPriMap4 = #;\n",bar.get_PortTOSPriMap4());
   Printf(Con,"PortTOSPriMap5 = #;\n",bar.get_PortTOSPriMap5());
   Printf(Con,"PortTOSPriMap6 = #;\n",bar.get_PortTOSPriMap6());
   Printf(Con,"PortTOSPriMap7 = #;\n\n",bar.get_PortTOSPriMap7());
  }
  
#endif  
  
#if 0
  
  {
   BarPort2 bar;
   
   Printf(Con,"PortControl = #;\n",bar.get_PortControl());
   Printf(Con,"PortFIFOLen = #;\n",bar.get_PortFIFOLen());
   Printf(Con,"PortFIFOUse = #;\n",bar.get_PortFIFOUse());
   Printf(Con,"PortTxFIFOControl = #;\n",bar.get_PortTxFIFOControl());
   Printf(Con,"PortVLANControl = #;\n",bar.get_PortVLANControl());
   Printf(Con,"PortTxPriMap = #;\n",bar.get_PortTxPriMap());
   Printf(Con,"PortTimeSync = #;\n",bar.get_PortTimeSync());
   Printf(Con,"PortMACHi = #;\n",bar.get_PortMACHi());
   Printf(Con,"PortMACLo = #;\n",bar.get_PortMACLo());
   Printf(Con,"PortSendPercent = #;\n",bar.get_PortSendPercent());
   Printf(Con,"PortTOSPriMap0 = #;\n",bar.get_PortTOSPriMap0());
   Printf(Con,"PortTOSPriMap1 = #;\n",bar.get_PortTOSPriMap1());
   Printf(Con,"PortTOSPriMap2 = #;\n",bar.get_PortTOSPriMap2());
   Printf(Con,"PortTOSPriMap3 = #;\n",bar.get_PortTOSPriMap3());
   Printf(Con,"PortTOSPriMap4 = #;\n",bar.get_PortTOSPriMap4());
   Printf(Con,"PortTOSPriMap5 = #;\n",bar.get_PortTOSPriMap5());
   Printf(Con,"PortTOSPriMap6 = #;\n",bar.get_PortTOSPriMap6());
   Printf(Con,"PortTOSPriMap7 = #;\n\n",bar.get_PortTOSPriMap7());
  }
  
#endif
  
#if 0
  
  {
   BarSliver1 bar;
   
   Printf(Con,"SliverControl = #;\n",bar.get_SliverControl());     // FullDuplex CtrlA
   Printf(Con,"SliverStatus = #;\n",bar.get_SliverStatus());
   Printf(Con,"SliverSoftReset = #;\n",bar.get_SliverSoftReset());
   Printf(Con,"SliverRxMaxLen = #;\n",bar.get_SliverRxMaxLen());   // 1522
   Printf(Con,"SliverBOFFTest = #;\n",bar.get_SliverBOFFTest());
   Printf(Con,"SliverRxPause = #;\n",bar.get_SliverRxPause());
   Printf(Con,"SliverTxPause = #;\n",bar.get_SliverTxPause());
   Printf(Con,"SliverEMControl = #;\n",bar.get_SliverEMControl());
   Printf(Con,"SliverRxPriMap = #;\n",bar.get_SliverRxPriMap());
   Printf(Con,"SliverTxGap = #;\n\n",bar.get_SliverTxGap());
  }
  
#endif
  
#if 0
  
  {
   BarSliver2 bar;
   
   Printf(Con,"SliverControl = #;\n",bar.get_SliverControl());
   Printf(Con,"SliverStatus = #;\n",bar.get_SliverStatus());
   Printf(Con,"SliverSoftReset = #;\n",bar.get_SliverSoftReset());
   Printf(Con,"SliverRxMaxLen = #;\n",bar.get_SliverRxMaxLen());
   Printf(Con,"SliverBOFFTest = #;\n",bar.get_SliverBOFFTest());
   Printf(Con,"SliverRxPause = #;\n",bar.get_SliverRxPause());
   Printf(Con,"SliverTxPause = #;\n",bar.get_SliverTxPause());
   Printf(Con,"SliverEMControl = #;\n",bar.get_SliverEMControl());
   Printf(Con,"SliverRxPriMap = #;\n",bar.get_SliverRxPriMap());
   Printf(Con,"SliverTxGap = #;\n\n",bar.get_SliverTxGap());
  }
  
#endif  
  
#if 0
  
  {
   BarTimeSync bar;
   
   Printf(Con,"TimeSyncControl = #;\n",bar.get_TimeSyncControl());
   Printf(Con,"TimeSyncTSPush = #;\n",bar.get_TimeSyncTSPush());
   Printf(Con,"TimeSyncTSValue = #;\n",bar.get_TimeSyncTSValue());
   Printf(Con,"TimeSyncTSLoad = #;\n",bar.get_TimeSyncTSLoad());
  }
  
#endif  

#if 1
  
  {
   BarALE bar;
   
   Printf(Con,"ALEControl = #;\n",bar.get_ALEControl());
   Printf(Con,"ALEPrescale = #;\n",bar.get_ALEPrescale());
   Printf(Con,"ALEUnknownVLAN = #;\n",bar.get_ALEUnknownVLAN());
   Printf(Con,"ALETableControl = #;\n",bar.get_ALETableControl());
   Printf(Con,"ALEPort0Control = #;\n",bar.get_ALEPort0Control());
   Printf(Con,"ALEPort1Control = #;\n",bar.get_ALEPort1Control());
   Printf(Con,"ALEPort2Control = #;\n",bar.get_ALEPort2Control());
   Printf(Con,"ALEPort3Control = #;\n",bar.get_ALEPort3Control());
   Printf(Con,"ALEPort4Control = #;\n",bar.get_ALEPort4Control());
   Printf(Con,"ALEPort5Control = #;\n",bar.get_ALEPort5Control());
  }
  
#endif  

#if 0
  
  {
   Printf(Con," = #;\n",bar.get_());
  }
  
#endif  
 }

EthControl::EthControl()
 : InstanceLock<EthControl>("Eth")
 {
  connect();
  enable();
  
  show();
  
  reset();
  
  //show();
  
  prepare();
  
  //show();
 }
   
EthControl::~EthControl()
 {
  reset();
  disable();
 }

void EthControl::enablePort1(bool full_duplex)
 {
  using namespace AM3359::ETH;
  
  BarSliver1 bar;

  bar.null_SliverControl()
     .setbit(SliverControl_RxFlowControlEnable|SliverControl_TxFlowControlEnable
             |SliverControl_GMIIEnable|SliverControl_TxPaceEnable)
     .setbitIf(full_duplex,SliverControl_FullDuplex)         
     .setTo(bar);
 }

void EthControl::setPort1(bool full_duplex)
 {
  using namespace AM3359::ETH;
  
  BarSliver1 bar;

  bar.get_SliverControl()
     .clearbit(SliverControl_FullDuplex)
     .setbitIf(full_duplex,SliverControl_FullDuplex)         
     .setTo(bar);
 }

} // namespace Dev
} // namespace CCore


