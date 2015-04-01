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

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/AM3359.LCD.h>
#include <CCore/inc/dev/AM3359.PRCM.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>

namespace CCore {
namespace Dev {

/* class LCD */

LCD::Mode::Mode(const Video::EDIDTimingDesc &desc)
 {
  hback=desc.hblank-desc.hsync_off-desc.hsync_pulse;
  hlen=desc.hlen;
  hfront=desc.hsync_off;
  hsync=desc.hsync_pulse;
  
  vback=desc.vblank-desc.vsync_off-desc.vsync_pulse;
  vlen=desc.vlen;
  vfront=desc.vsync_off;
  vsync=desc.vsync_pulse;
  
  if( hlen<16 || hlen>2048 || (hlen&15)!=0
      || hfront<1 || hfront>1024
      || hsync<1 || hsync>1024
      || hback<1 || hback>1024
      || vlen<1 || vlen>2048
      || vfront>255
      || vsync<1 || vsync>64
      || vback>255
    )
    {
     Printf(Exception,"CCore::Dev::LCD::Mode::Mode(...) : unsupported video geometry");
    }
 }

LCD::FrameBuf16::FrameBuf16(uint32 hlen,uint32 vlen,Space video_space)
 {
  ulen len=16+hlen*vlen;
  
  if( len>video_space.len/2 )
    {
     Printf(Exception,"CCore::Dev::LCD::FrameBuf16::FrameBuf16(hlen=#;,vlen=#;,{...,#;}) : video space is too short",hlen,vlen,video_space.len);
    }
  
  uint16 *base=static_cast<uint16 *>(video_space.mem);
  uint16 *lim=base+len;
  
  base[0]=(1u<<14);
  
  Range(base+1,15).set_null();
  
  this->plane=Video::ColorPlane(base+16,(Video::Coord)hlen,(Video::Coord)vlen,Video::DLineType(hlen*2u));
  this->base=base;
  this->lim=lim;
 }

LCD::FrameBuf24::FrameBuf24(uint32 hlen,uint32 vlen,Space video_space)
 {
  ulen len=32+3*hlen*vlen;
  
  if( len>video_space.len )
    {
     Printf(Exception,"CCore::Dev::LCD::FrameBuf24::FrameBuf24(hlen=#;,vlen=#;,{...,#;}) : video space is too short",hlen,vlen,video_space.len);
    }
  
  uint8 *base=static_cast<uint8 *>(video_space.mem);
  uint8 *lim=base+len;
  
  base[0]=0;
  base[1]=(1u<<6);
  
  Range(base+2,30).set_null();

  this->plane=Video::ColorPlane(base+32,(Video::Coord)hlen,(Video::Coord)vlen,Video::DLineType(hlen*3u));
  this->base=base;
  this->lim=lim;
 }

LCD::FrameBuf32::FrameBuf32(uint32 hlen,uint32 vlen,Space video_space)
 {
  ulen len=8+hlen*vlen;
  
  if( len>video_space.len/4 )
    {
     Printf(Exception,"CCore::Dev::LCD::FrameBuf32::FrameBuf32(hlen=#;,vlen=#;,{...,#;}) : video space is too short",hlen,vlen,video_space.len);
    }
  
  uint32 *base=static_cast<uint32 *>(video_space.mem);
  uint32 *lim=base+len;
  
  base[0]=(1u<<14);
  
  Range(base+1,7).set_null();
  
  this->plane=Video::ColorPlane(base+8,(Video::Coord)hlen,(Video::Coord)vlen,Video::DLineType(hlen*4u));
  this->base=base;
  this->lim=lim;
 }

void LCD::init_first()
 {
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
 }

void LCD::init(const Mode &mode,void *base,void *lim,ColorFormat fmt)
 {
  using namespace AM3359::LCD;
  
  Bar bar;

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
  
  Bits_RasterControl flags=RasterControl_LCDEn|RasterControl_LCDTFT;
  
  switch( fmt )
    {
     case ColorFormat16 : flags=flags|RasterControl_STN565; break;
     case ColorFormat24 : flags=flags|RasterControl_TFT24; break;
     case ColorFormat32 : flags=flags|RasterControl_TFT24|RasterControl_TFT24Unpacked; break;
    }
  
  bar.null_RasterControl()
     .setbit(flags)
     .set_PalMode(RasterControl_PalMode_Both)
     .setTo(bar);
 }

void LCD::handle_int()
 {
  using namespace AM3359::LCD;
  
  Bar bar;
  
  auto status=bar.get_IRQStatus();
  
  status.setTo(bar);
  
  if( status.maskbit(IRQStatus_RasterFrameDone) )
    {
     switch( stop_flag )
       {
        case 0 :
         {
          stop_flag=1;
         }
        break;
        
        case 1 :
         {
          bar.get_RasterControl()
             .clearbit(RasterControl_LCDEn)
             .setTo(bar);
          
          stop_flag=2;
         }
        break;
        
        case 2 :
         {
          sem.give_int();
          
          stop_flag=3;
         }
        break; 
       }
    }
 }

LCD::LCD()
 : InstanceLock<LCD>("LCD")
 {
 }

LCD::~LCD()
 {
  CleanupIntHandler(Int_LCDCINT);
 }

 // init

void LCD::enable(uint32 clock)
 {
  Mutex::Lock lock(ControlMutex);
  
  // enable LCD
  {
   using namespace AM3359::PRCM;
   
   setClock(clock);
   
   // connect clock
   {
    BarDPLL dpll_bar;
    
    dpll_bar.null_LCDClockSelect()
            .set_Source(LCDClockSelect_Source_DISP_PLL_CLKOUTM2)
            .setTo(dpll_bar);
   }
   
   // enable LCD
   {
    BarPER per_bar;
    
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
  Mutex::Lock lock(ControlMutex);
  
  using namespace AM3359::PRCM;
  
  BarWKUP wkup_bar;
   
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

Video::ColorPlane LCD::init_first16(const Mode &mode,Space video_space)
 {
  FrameBuf16 frame(mode.hlen,mode.vlen,video_space);
  
  init_first();
  
  init(mode,frame.base,frame.lim,ColorFormat16);
  
  return frame.plane;
 }

Video::ColorPlane LCD::init_first24(const Mode &mode,Space video_space)
 {
  FrameBuf24 frame(mode.hlen,mode.vlen,video_space);

  init_first();
  
  init(mode,frame.base,frame.lim,ColorFormat24);
  
  return frame.plane;
 }

Video::ColorPlane LCD::init_first32(const Mode &mode,Space video_space)
 {
  FrameBuf32 frame(mode.hlen,mode.vlen,video_space);
  
  init_first();
  
  init(mode,frame.base,frame.lim,ColorFormat32);
  
  return frame.plane;
 }

void LCD::stop()
 {
  stop_flag=0;
  
  using namespace AM3359::LCD;
  
  Bar bar;
  
  bar.ones_IRQStatus()
     .set(bar.to_IRQEnableClear());
  
  bar.null_IRQStatus()
     .setbit(IRQStatus_RasterFrameDone)
     .set(bar.to_IRQEnableSet());
  
  SetupIntHandler(Int_LCDCINT,function_handle_int(),15);
  
  sem.take();
  
  CleanupIntHandler(Int_LCDCINT);
  
  bar.ones_IRQStatus()
     .set(bar.to_IRQEnableClear());
  
  bar.null_Reset()
     .setbit(Reset_Core|Reset_DMA)
     .setTo(bar);
  
  AM3359::Delay(16);
  
  bar.null_Reset()
     .setTo(bar);
 }

Video::ColorPlane LCD::init16(const Mode &mode,Space video_space)
 {
  FrameBuf16 frame(mode.hlen,mode.vlen,video_space);
  
  init(mode,frame.base,frame.lim,ColorFormat16);
  
  return frame.plane;
 }

Video::ColorPlane LCD::init24(const Mode &mode,Space video_space)
 {
  FrameBuf24 frame(mode.hlen,mode.vlen,video_space);
  
  init(mode,frame.base,frame.lim,ColorFormat24);
  
  return frame.plane;
 }

Video::ColorPlane LCD::init32(const Mode &mode,Space video_space)
 {
  FrameBuf32 frame(mode.hlen,mode.vlen,video_space);
  
  init(mode,frame.base,frame.lim,ColorFormat32);
  
  return frame.plane;
 }

} // namespace Dev
} // namespace CCore
