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

void EthControl::InitControl()
 {
  AM3359::CONTROL::Bar bar;
  
  Printf(Con,"GMIISelect = #;\n",bar.get_GMIISelect());
  Printf(Con,"EthResetIsolation = #;\n",bar.get_EthResetIsolation());
  Printf(Con,"MAC0Hi = #.h;\n",bar.get_MAC0Hi());
  Printf(Con,"MAC0Lo = #.h;\n",bar.get_MAC0Lo());
  Printf(Con,"MAC1Hi = #.h;\n",bar.get_MAC1Hi());
  Printf(Con,"MAC1Lo = #.h;\n\n",bar.get_MAC1Lo());
  
  Printf(Con,"#;\n",bar.get_Conf_MII1_COL());      // Rx 7
  Printf(Con,"#;\n",bar.get_Conf_MII1_CRS());      // Rx 7
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_ER());    // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TX_EN());    // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_DV());    // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD3());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD2());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD1());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TXD0());     // 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_TX_CLK());   // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RX_CLK());   // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD3());     // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD2());     // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD1());     // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_MII1_RXD0());     // Rx 0
  Printf(Con,"#;\n",bar.get_Conf_RMII1_REF_CLK()); // Rx 7
  Printf(Con,"#;\n",bar.get_Conf_MDIO());          // Rx PullUp 0
  Printf(Con,"#;\n",bar.get_Conf_MDC());           // PullUp 0
  
  // TODO
 }
   
void EthControl::InitPRMC()
 {
  // TODO
 }
   
void EthControl::InitEth()
 {
  // TODO
 }
  
EthControl::EthControl()
 {
  InitControl();
  InitPRMC();
  InitEth();
  
  // TODO
 }
   
EthControl::~EthControl()
 {
  // TODO
 }

} // namespace Dev
} // namespace CCore


