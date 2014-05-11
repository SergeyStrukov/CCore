/* DevHDMI.cpp */
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

#include <CCore/inc/dev/DevHDMI.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace CCore {
namespace Dev {

/* class HDMI */

HDMI::RegRW::RegRW(StrLen i2c_dev_name)
 : hook(i2c_dev_name),
   dev(hook)
 {
 }

HDMI::RegRW::~RegRW()
 {
 }

uint8 HDMI::RegRW::get(uint8 slave_address,uint8 address) 
 {
  uint8 ret;
  
  dev->exchange(slave_address,Range_const(&address,1),Range(&ret,1));
  
  return ret;
 }

void HDMI::RegRW::set(uint8 slave_address,uint8 address,uint8 value) 
 {
  uint8 temp[]={address,value};
  
  dev->write(slave_address,Range_const(temp));
 }

void HDMI::RegRW::set(uint8 slave_address,uint8 address,uint8 value1,uint8 value2) 
 {
  uint8 temp[]={address,value1,value2};
  
  dev->write(slave_address,Range_const(temp));
 }

template <>
uint8 HDMI::CECRegRW::get<uint8>(AddressType address)
 {
  return dev.get(SlaveAddress,address);
 }

template <>
void HDMI::CECRegRW::set<uint8>(AddressType address,uint8 value)
 {
  dev.set(SlaveAddress,address,value);
 }

void HDMI::HDMIRegRW::setPage(uint8 page_)
 {
  if( page!=page_ )
    {
     dev.set(SlaveAddress,0xFF,page_);
    
     page=page_;
    }
 }

template <>
uint8 HDMI::HDMIRegRW::get<uint8>(AddressType address)
 {
  setPage(uint8(address>>8));
  
  return dev.get(SlaveAddress,uint8(address));
 }

template <>
void HDMI::HDMIRegRW::set<uint8>(AddressType address,uint8 value)
 {
  setPage(uint8(address>>8));
  
  dev.set(SlaveAddress,uint8(address),value);
 }

template <>
void HDMI::HDMIRegRW::set<uint16>(AddressType address,uint16 value)
 {
  setPage(uint8(address>>8));
  
  dev.set(SlaveAddress,uint8(address),uint8(value>>8),uint8(value));
 }

HDMI::HDMI(StrLen i2c_dev_name)
 : regRW(i2c_dev_name),
   barCEC(regRW),
   barHDMI(regRW)
 {
 }

HDMI::~HDMI()
 {
 }

void HDMI::init()
 {
  using namespace NXP::HDMI;
  
  // enable
  
  barCEC.null_CECEnable()
        .setbit(CECEnable_EnHDMI|CECEnable_EnRxSense)
        .setTo(barCEC);
  
  // reset
  
  barHDMI.null_SoftReset()
         .setbit(SoftReset_Audio|SoftReset_I2C)
         .setTo(barHDMI);
  
  Task::Sleep(50_msec);
  
  barHDMI.null_SoftReset()
         .setTo(barHDMI);
  
  Task::Sleep(50_msec);
  
  barHDMI.get_MainControl0()
         .setbit(MainControl0_SoftReset)
         .setTo(barHDMI);
  
  barHDMI.get_MainControl0()
         .clearbit(MainControl0_SoftReset)
         .setTo(barHDMI);
  
  // PLL
  
  barHDMI.null_PLLSerial1()
         .setTo(barHDMI);
  
  barHDMI.null_PLLSerial2()
         .set_NOSC(1)
         .setTo(barHDMI);
  
  barHDMI.null_PLLSerial3()
         .setTo(barHDMI);
  
  barHDMI.null_Serializer()
         .setTo(barHDMI);
  
  barHDMI.null_BufferOut()
         .setTo(barHDMI);
  
  barHDMI.null_PLLSCG1()
         .setTo(barHDMI);
  
  barHDMI.null_AudioDiv()
         .set_Div(3)
         .setTo(barHDMI);
  
  barHDMI.null_SelectCLK()
         .setbit(SelectCLK_CLK1|SelectCLK_EnSC)
         .setTo(barHDMI);
  
  barHDMI.set_PLLSCGN1(0xFA);
  
  barHDMI.set_PLLSCGN2(0);
  
  barHDMI.set_PLLSCGR1(0x5B);
  
  barHDMI.set_PLLSCGR2(0);
  
  barHDMI.null_PLLSCG2()
         .setbit(PLLSCG2_SelCLKIN)
         .setTo(barHDMI);
  
  // MUX
  
  barHDMI.null_MuxVPVIPOut()
         .set_Blue(0)
         .set_Green(1)
         .set_Red(2)
         .setTo(barHDMI);
  
  // check version
  
  uint8 vlo=barHDMI.get_VersionLSB().clearbit(VersionLSB_NotS|VersionLSB_NotH);
  uint8 vhi=barHDMI.get_VersionMSB();
  
  if( vhi!=3 || vlo!=1 )
    {
     Printf(Exception,"CCore::Dev::HDMI::init() : bad HDMI version");
    }
  
  // DDC
  
  barHDMI.null_DDCDisable()
         .setTo(barHDMI);
  
  // DDC clock

  barHDMI.set_TX3(39);
  
  // finish
  
  barCEC.null_CEC_FRO_IMCLK()
        .setbit(CEC_FRO_IMCLK_IMCLK|CEC_FRO_IMCLK_DisGhost)
        .setTo(barCEC);
  
  barCEC.null_CECIntEnable()
        .setbit(CECIntEnable_RxSense|CECIntEnable_Plug)
        .setTo(barCEC);
  
  barHDMI.set_IntFlags0(0);
  
  barHDMI.set_IntFlags1(0);
  
  barHDMI.null_IntFlags2().setTo(barHDMI);
 }

auto HDMI::detect() -> Detect
 {
  using namespace NXP::HDMI;
  
  auto status=barCEC.get_CECStatus();
  
  return Detect(status.maskbit(CECStatus_Plug),status.maskbit(CECStatus_RxSense));
 }

auto HDMI::getIntInfo() -> IntInfo
 {
  using namespace NXP::HDMI;
  
  auto int_status=barCEC.get_CECIntStatus();
  auto int_source=barCEC.get_CECIntSource();

  bool edid=false;
  
  if( int_source.maskbit(CECIntSource_HDMI) )
    {
     edid=barHDMI.get_IntFlags2().maskbit(IntFlags2_EDID);
    }
  
  return IntInfo(int_status.maskbit(CECIntStatus_Plug),int_status.maskbit(CECIntStatus_RxSense),edid);
 }

void HDMI::enableVIP()
 {
  barHDMI.null_VP0Control()
         .set_SwapA(2)
         .set_SwapB(3)
         .setTo(barHDMI);
  
  barHDMI.null_VP1Control()
         .set_SwapC(0)
         .set_SwapD(1)
         .setTo(barHDMI);
  
  barHDMI.null_VP2Control()
         .set_SwapE(4)
         .set_SwapF(5)
         .setTo(barHDMI);
  
  barHDMI.set_VP0Enable(0xFF);
  barHDMI.set_VP1Enable(0xFF);
  barHDMI.set_VP2Enable(0xFF);
 }

void HDMI::disableVIP()
 {
  barHDMI.set_VP0Enable(0);
  barHDMI.set_VP1Enable(0);
  barHDMI.set_VP2Enable(0);
 }

void HDMI::startReadEDID(unsigned number)
 {
  using namespace NXP::HDMI;
  
  barHDMI.get_TX4()
         .clearbit(TX4_RAM)
         .setTo(barHDMI);
  
  barHDMI.get_IntFlags2()
         .setbit(IntFlags2_EDID)
         .setTo(barHDMI);
  
  barHDMI.set_DDCAddress(0xA0);
  
  barHDMI.set_DDCOff((number&1)?128:0);
  
  barHDMI.set_DDCSegAddr(0x60);
  
  barHDMI.set_DDCSeg(number/2);
  
  barHDMI.get_DDCControl()
         .setbit(DDCControl_Read)
         .setTo(barHDMI);
  
  barHDMI.get_DDCControl()
         .clearbit(DDCControl_Read)
         .setTo(barHDMI);
 }

void HDMI::readEDID(uint8 block[Video::EDIDLen])
 {
  using namespace NXP::HDMI;
  
  for(ulen i=0; i<Video::EDIDLen ;i++) block[i]=barHDMI.get_EDIDBlock(i);
 }

void HDMI::finishReadEDID()
 {
  using namespace NXP::HDMI;
  
  barHDMI.get_IntFlags2()
         .clearbit(IntFlags2_EDID)
         .setTo(barHDMI);
  
  barHDMI.get_TX4()
         .setbit(TX4_RAM)
         .setTo(barHDMI);
 }

HDMI::Mode::Mode(const Video::EDIDMode &mode)
 {
  htotal=mode.hlen+mode.hblank;
  hdisplay=mode.hlen;
  hsync_start=mode.hlen+mode.hsync_off;
  hsync_end=mode.hlen+mode.hsync_off+mode.hsync_pulse;
  
  vtotal=mode.vlen+mode.vblank;
  vdisplay=mode.vlen;
  vsync_start=mode.vlen+mode.vsync_off;
  vsync_end=mode.vlen+mode.vsync_off+mode.vsync_pulse;
  
  pixel_clock=mode.pixel_clock;
  
  hsync_neg=!mode.hsyncPos();
  vsync_neg=!mode.vsyncPos();
 }

void HDMI::setMode(const Mode &mode)
 {
  uint32 div=148500/mode.pixel_clock;
  uint32 rep=0;
  
  using namespace NXP::HDMI;
  
  barHDMI.get_AIPControl0()
         .setbit(AIPControl0_ResetFIFO)
         .setTo(barHDMI);
  
  barHDMI.null_TBGControl1()
         .setbit(TBGControl1_DisDWIN)
         .setTo(barHDMI);
         
  barHDMI.get_TX33()
         .clearbit(TX33_HDMI)
         .setTo(barHDMI);
  
  barHDMI.null_ENCControl()
         .set_Code(0) 
         .setTo(barHDMI);
  
  barHDMI.null_HVFControl0()
         .set_IntPol(0)
         .set_Prefil(0)
         .setTo(barHDMI);
  
  barHDMI.null_VP5Control()
         .set_SPCnt(0)
         .setTo(barHDMI);
  
  barHDMI.null_VP4Control()
         .set_BlankIt(0)
         .set_BLC(0)
         .setTo(barHDMI);
  
  barHDMI.get_PLLSerial3()
         .clearbit(PLLSerial3_CCIR)
         .setTo(barHDMI);
  
  barHDMI.get_PLLSerial1()
         .clearbit(PLLSerial1_ManIZ)
         .setTo(barHDMI);
  
  barHDMI.get_PLLSerial3()
         .clearbit(PLLSerial3_DE)
         .setTo(barHDMI);
  
  barHDMI.null_Serializer()
         .setTo(barHDMI);
  
  barHDMI.null_HVFControl1()
         .set_VQR(0)
         .setTo(barHDMI);
  
  barHDMI.set_RepControl(0);
  
  barHDMI.null_SelectCLK()
         .setbit(SelectCLK_EnSC|SelectCLK_CLK1)
         .set_VRFCLK(0)
         .setTo(barHDMI);
  
  barHDMI.null_PLLSerial2()
         .set_NOSC(div)
         .set_PR(rep)
         .setTo(barHDMI);
  
  barHDMI.null_MatControl()
         .setbit(MatControl_BP)
         .setTo(barHDMI);
  
  barHDMI.set_ANAGeneral(0x09);
  
  barHDMI.null_VP3Control()
         .set_SpSync(2)
         .setbitIf(mode.hsync_neg,VP3Control_HTgl)
         .setbitIf(mode.vsync_neg,VP3Control_VTgl)
         .setTo(barHDMI);
  
  barHDMI.null_TBGControl1()
         .setbit(TBGControl1_EnTgl)
         .setbitIf(mode.hsync_neg,TBGControl1_HTgl)
         .setbitIf(mode.vsync_neg,TBGControl1_VTgl)
         .setTo(barHDMI);
  
  barHDMI.null_VIDFormat()
         .set_Format(0)
         .setTo(barHDMI);
  
  uint16 ref_pix=uint16( 2 + mode.hsync_end - mode.hdisplay );
  uint16 ref_line=uint16( 1 + mode.vsync_start - mode.vdisplay );
  uint16 num_pix=uint16( mode.htotal );
  uint16 num_line=uint16( mode.vtotal );
  
  uint16 vs1_line_s=uint16( mode.vsync_start - mode.vdisplay );
  uint16 vs1_line_e=uint16( mode.vsync_end - mode.vdisplay );
  uint16 vs1_pix_s=uint16( mode.hsync_start - mode.hdisplay );
  uint16 vs1_pix_e=uint16( mode.hsync_start - mode.hdisplay );
  
  uint16 vs2_line_s=0;
  uint16 vs2_line_e=0;
  uint16 vs2_pix_s=0;
  uint16 vs2_pix_e=0;
  
  uint16 hs_pix_s=uint16( mode.hsync_start - mode.hdisplay );
  uint16 hs_pix_e=uint16( mode.hsync_end   - mode.hdisplay );
  
  uint16 vwin1_line_s=uint16( mode.vtotal - mode.vdisplay - 1 );
  uint16 vwin1_line_e=uint16( mode.vtotal - 1 );
  
  uint16 vwin2_line_s=0;
  uint16 vwin2_line_e=0;
  
  uint16 de_pix_s=uint16( mode.htotal - mode.hdisplay );
  uint16 de_pix_e=uint16( mode.htotal );
  
  barHDMI.set_RefPix(ref_pix);
  barHDMI.set_RefLine(ref_line);
  barHDMI.set_NumPix(num_pix);
  barHDMI.set_NumLine(num_line);
  
  barHDMI.set_VS1LineS(vs1_line_s);
  barHDMI.set_VS1LineE(vs1_line_e);
  barHDMI.set_VS1PixS(vs1_pix_s);
  barHDMI.set_VS1PixE(vs1_pix_e);
  
  barHDMI.set_VS2LineS(vs2_line_s);
  barHDMI.set_VS2LineE(vs2_line_e);
  barHDMI.set_VS2PixS(vs2_pix_s);
  barHDMI.set_VS2PixE(vs2_pix_e);
  
  barHDMI.set_HSPixS(hs_pix_s);
  barHDMI.set_HSPixE(hs_pix_e);
  
  barHDMI.set_VWin1LineS(vwin1_line_s);
  barHDMI.set_VWin1LineE(vwin1_line_e);
  
  barHDMI.set_VWin2LineS(vwin2_line_s);
  barHDMI.set_VWin2LineE(vwin2_line_e);
  
  barHDMI.set_DEPixS(de_pix_s);
  barHDMI.set_DEPixE(de_pix_e);
  
  barHDMI.set_EnSpace(0x01);
  
  barHDMI.null_TBGControl0()
         .setTo(barHDMI);
 }

} // namespace Dev
} // namespace CCore


