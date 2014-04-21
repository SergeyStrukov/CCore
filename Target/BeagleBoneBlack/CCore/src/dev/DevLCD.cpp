/* DevLCD.cpp */
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

#include <CCore/inc/dev/DevLCD.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/dev/AM3359.LCD.h>
#include <CCore/inc/dev/AM3359.PRCM.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>

namespace CCore {
namespace Dev {

/* class LCD */

LCD::Mode::Mode(const Video::EDIDMode &mode)
 {
  hback=mode.hblank-mode.hsync_off-mode.hsync_pulse;
  hlen=mode.hlen;
  hfront=mode.hsync_off;
  hsync=mode.hsync_pulse;
  
  vback=mode.vblank-mode.vsync_off-mode.vsync_pulse;
  vlen=mode.vlen;
  vfront=mode.vsync_off;
  vsync=mode.vsync_pulse;
 }

LCD::LCD()
 {
 }

 // init

void LCD::enable(uint32 clock)
 {
  // enable LCD
  {
   using namespace AM3359::PRCM;
   
   setClock(clock);
   
   // connect clock
   {
    DPLLBar dpll_bar;
    
    dpll_bar.null_LCDClockSelect()
            .set_Source(LCDClockSelect_Source_DISP_PLL_CLKOUTM2)
            .setTo(dpll_bar);
   }
   
   // enable LCD
   {
    PERBar per_bar;
    
    per_bar.null_ClockStandbyControl()
           .set_Mode(ClockStandbyControl_Mode_Enable)
           .set(per_bar.to_LCD());
    
    while( per_bar.get_LCD().get_IdleStatus()!=ClockStandbyControl_IdleStatus_Running );
   }
  }
  
  // connect LCD pads 
  {
   using namespace AM3359::CONTROL;
   
   Bar bar;
   
   bar.null_PadMux()
      .set_MuxMode(0)
      .setbit(PadMux_NoPullUpDown)
      .set(bar.to_Conf_LCD_DATA0())
      .set(bar.to_Conf_LCD_DATA1())
      .set(bar.to_Conf_LCD_DATA2())
      .set(bar.to_Conf_LCD_DATA3())
      .set(bar.to_Conf_LCD_DATA4())
      .set(bar.to_Conf_LCD_DATA5())
      .set(bar.to_Conf_LCD_DATA6())
      .set(bar.to_Conf_LCD_DATA7())
      .set(bar.to_Conf_LCD_DATA8())
      .set(bar.to_Conf_LCD_DATA9())
      .set(bar.to_Conf_LCD_DATA10())
      .set(bar.to_Conf_LCD_DATA11())
      .set(bar.to_Conf_LCD_DATA12())
      .set(bar.to_Conf_LCD_DATA13())
      .set(bar.to_Conf_LCD_DATA14())
      .set(bar.to_Conf_LCD_DATA15())
      .set(bar.to_Conf_LCD_VSYNC())
      .set(bar.to_Conf_LCD_HSYNC())
      .set(bar.to_Conf_LCD_PCLK())
      .set(bar.to_Conf_LCD_AC_BIAS_EN());
  }
 }

void LCD::reset_first()
 {
  using namespace AM3359::LCD;
  
  Bar bar;
  
  bar.null_ClockEnable()
     .setbit(ClockEnable_Core|ClockEnable_DMA)
     .setTo(bar);
  
  bar.null_Reset()
     .setbit(Reset_Core|Reset_DMA)
     .setTo(bar);
  
  AM3359::Delay(16);
  
  bar.null_Reset()
     .setTo(bar);
 }

void LCD::setClock(uint32 clock)
 {
  using namespace AM3359::PRCM;
  
  WKUPBar wkup_bar;
   
  {
   wkup_bar.get_DISPClockMode()
           .set_En(PLLClockMode_En_MNBypass)
           .set(wkup_bar.to_DISPClockMode());
   
   while( wkup_bar.get_DISPIdleStatus().maskbit(PLLIdleStatus_Bypass|PLLIdleStatus_Locked)!=PLLIdleStatus_Bypass );
  } 
   
  {
   wkup_bar.get_DISPClockSelect()
           .set_Div(24-1) // assume OSC_M is 24 MHz
           .set_Mul(clock)
           .set(wkup_bar.to_DISPClockSelect()); 
   
   wkup_bar.get_DISPDivM2()
           .set_M2(1)
           .set(wkup_bar.to_DISPDivM2());
   
   AM3359::Delay(1000);
  } 
   
  { 
   wkup_bar.get_DISPClockMode()
           .set_En(PLLClockMode_En_Lock)
           .set(wkup_bar.to_DISPClockMode());
    
   while( wkup_bar.get_DISPIdleStatus().maskbit(PLLIdleStatus_Bypass|PLLIdleStatus_Locked)!=PLLIdleStatus_Locked );
  } 
 }

Video::FrameBuf<Video::Color565> LCD::init_first(const Mode &mode,Space video_space)
 {
  ulen len=16+mode.hlen*mode.vlen;
  
  if( len>video_space.len/2 )
    {
     Printf(Exception,"CCore::Dev::LCD::init(...) : video space is too short");
    }
  
  uint16 *base=static_cast<uint16 *>(video_space.mem);
  uint16 *lim=base+len;
  
  base[0]=(4<<12);
  
  Video::FrameBuf<Video::Color565> ret(base+16,mode.hlen,mode.vlen);
  
  using namespace AM3359::LCD;
  
  Bar bar;

  bar.null_SysConfig()
     .set_IdleMode(SysConfig_IdleMode_SmartIdle)
     .set_StandbyMode(SysConfig_StandbyMode_SmartStandby)
     .setTo(bar);
  
  bar.null_Control()
     .setbit(Control_Raster|Control_UnderflowRestart)
     .set_PCLKDiv(2)
     .setTo(bar);
  
  bar.null_LCDDMAControl()
     .set_BurstSize(2)
     .set_FIFOReady(4)
     .set_DMAPri(0)
     .setTo(bar);
  
  bar.set_LCDDMAFB0Base((uint32)base);
  
  bar.set_LCDDMAFB0Lim((uint32)lim);
  
  Type_SplitHLen split_HLen(mode.hlen-1);
  Type_SplitHSync split_HSync(mode.hsync-1);
  Type_SplitHFront split_HFront(mode.hfront-1);
  Type_SplitHBack split_HBack(mode.hback-1);
  Type_SplitVLen split_VLen(mode.vlen-1);
  
  bar.null_RasterTiming0()
     .set_HLen_lsb(split_HLen.get_lsb())
     .set_HSync_lsb(split_HSync.get_lsb())
     .set_HFront_lsb(split_HFront.get_lsb())
     .set_HBack_lsb(split_HBack.get_lsb())
     .setbitIf(split_HLen.maskbit(SplitHLen_msb),RasterTiming0_HLen_msb)
     .setTo(bar);
  
  bar.null_RasterTiming1()
     .set_VLen_lsb(split_VLen.get_lsb())
     .set_VSync(mode.vsync-1)
     .set_VFront(mode.vfront)
     .set_VBack(mode.vback)
     .setTo(bar);
  
  bar.null_RasterTiming2()
     .set_HFront_msb(split_HFront.get_msb())
     .set_HBack_msb(split_HBack.get_msb())
     .set_HSync_msb(split_HSync.get_msb())
     .setbitIf(split_VLen.maskbit(SplitVLen_msb),RasterTiming2_VLen_msb)
     .setbit(RasterTiming2_SyncEdge|RasterTiming2_InvHSync)
     .setTo(bar);
  
  bar.null_RasterControl()
     .setbit(RasterControl_LCDEn|RasterControl_LCDTFT|RasterControl_STN565)
     .set_PalMode(RasterControl_PalMode_Both)
     .setTo(bar);
  
  return ret;
 }

} // namespace Dev
} // namespace CCore
