/* AM3359.ETH.h */
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

#ifndef CCore_inc_dev_AM3359_ETH_h
#define CCore_inc_dev_AM3359_ETH_h
 
#include <CCore/inc/dev/AM3359.h>
#include <CCore/inc/dev/DevRW.h>

namespace AM3359 {
namespace ETH {

/* AM3359.ETH.desc -> AM3359.ETH.gen.h */

#include <CCore/inc/dev/AM3359.ETH.gen.h>

/* struct BarSwitch */

struct BarSwitch : SwitchBar<CCore::Dev::RegRW>
 {
  BarSwitch() : SwitchBar<CCore::Dev::RegRW>(0x4A100000) {}
 };

/* struct BarPort0 */

struct BarPort0 : Port0Bar<CCore::Dev::RegRW>
 {
  BarPort0() : Port0Bar<CCore::Dev::RegRW>(0x4A100100) {}
 };

/* struct BarPort1 */

struct BarPort1 : Port1Bar<CCore::Dev::RegRW>
 {
  BarPort1() : Port1Bar<CCore::Dev::RegRW>(0x4A100200) {}
 };

/* struct BarPort2 */

struct BarPort2 : Port2Bar<CCore::Dev::RegRW>
 {
  BarPort2() : Port2Bar<CCore::Dev::RegRW>(0x4A100300) {}
 };

/* struct BarDMA */

struct BarDMA : DMABar<CCore::Dev::RegRW>
 {
  BarDMA() : DMABar<CCore::Dev::RegRW>(0x4A100800) {}
 };

/* struct BarStat */

struct BarStat : StatBar<CCore::Dev::RegRW>
 {
  BarStat() : StatBar<CCore::Dev::RegRW>(0x4A100900) {}
 };

/* struct BarDesc */

struct BarDesc : DescBar<CCore::Dev::RegRW>
 {
  BarDesc() : DescBar<CCore::Dev::RegRW>(0x4A100A00) {}
 };

/* struct BarTimeSync */

struct BarTimeSync : TimeSyncBar<CCore::Dev::RegRW>
 {
  BarTimeSync() : TimeSyncBar<CCore::Dev::RegRW>(0x4A100C00) {}
 };

/* struct BarALE */

struct BarALE : ALEBar<CCore::Dev::RegRW>
 {
  BarALE() : ALEBar<CCore::Dev::RegRW>(0x4A100D00) {}
 };

/* struct BarSliver1 */

struct BarSliver1 : SliverBar<CCore::Dev::RegRW>
 {
  BarSliver1() : SliverBar<CCore::Dev::RegRW>(0x4A100D80) {}
 };

/* struct BarSliver2 */

struct BarSliver2 : SliverBar<CCore::Dev::RegRW>
 {
  BarSliver2() : SliverBar<CCore::Dev::RegRW>(0x4A100DC0) {}
 };

/* struct BarWR */

struct BarWR : WRBar<CCore::Dev::RegRW>
 {
  BarWR() : WRBar<CCore::Dev::RegRW>(0x4A101200) {}
 };

/* struct BarMDIO */

struct BarMDIO : MDIOBar<CCore::Dev::RegRW>
 {
  BarMDIO() : MDIOBar<CCore::Dev::RegRW>(0x4A101000) {}
 };

} // namespace ETH
} // namespace AM3359

#endif

