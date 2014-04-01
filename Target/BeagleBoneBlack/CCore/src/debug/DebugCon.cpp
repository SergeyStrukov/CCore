/* DebugCon.cpp */
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

#include <CCore/inc/Gadget.h>

#include <CCore/inc/dev/DevInt.h>

using namespace CCore;

namespace Debug {

//- Common -------------------------------------------------------------------------------

/* types */

using octet = unsigned char ;

using Address = uint32 ;
using Register = uint32 ;

/* Delay() */

inline void Delay(volatile unsigned count)
 {
  for(; count ;count--);
 }

/* Bit() */

inline constexpr Register Bit(unsigned num) { return Register(1)<<num; }

/* Bits() */

inline constexpr Register Bits() { return 0; }

template <class T,class ... TT>
inline constexpr Register Bits(T t,TT ... tt) { return Bit(t)|Bits(tt...); }

/* BitField() */

inline constexpr Register BitFieldMask(unsigned msb) { return Bit(msb+1)-1; }

inline constexpr Register BitFieldMask(unsigned msb,unsigned lsb) { return BitFieldMask(msb-lsb)<<lsb; } 

/* Octet2() */

inline unsigned Octet2(octet lsb,octet msb) { return lsb|(unsigned(msb)<<8); }

/* classes */

struct BitField;

class RegOp;

/* struct BitField */

struct BitField
 {
  unsigned msb;
  unsigned lsb;
  
  constexpr BitField(unsigned msb_) : msb(msb_),lsb(0) {}
  
  constexpr BitField(unsigned msb_,unsigned lsb_) : msb(msb_),lsb(lsb_) {}
  
  constexpr operator Register() const { return BitFieldMask(msb,lsb); }
  
  Register insert(Register value) const { return (value&BitFieldMask(msb-lsb,0))<<lsb; }
  
  Register insert(Register full,Register value) const { return (full&~BitFieldMask(msb,lsb))|insert(value); }
  
  Register extract(Register value) const { return (value&BitFieldMask(msb,lsb))>>lsb; }
 };

/* class RegOp */

class RegOp
 {
   Address address;
   
  public: 
   
   explicit RegOp(Address address_) : address(address_) {}
   
   Register get() const { return *(volatile Register *)address; }
   
   void put(Register value) { *(volatile Register *)address=value; }
   
   operator Register() const { return get(); }
   
   void operator = (Register value) { put(value); }
   
   void bitset(Register bits) { put(get()|bits); }
   
   void bitclear(Register bits) { put(get()&~bits); }
   
   void bitset(Register clearbits,Register bits) { put((get()&~clearbits)|bits); }
   
   Register extract(BitField field) { return field.extract(get()); }
   
   void insert(BitField field,Register value) { put(field.insert(get(),value)); }
 };

/* Reg() */

inline RegOp Reg(Address address) { return RegOp(address); } 

inline RegOp Reg(Address base,Address offset) { return RegOp(base+offset); }

//- Light --------------------------------------------------------------------------------

namespace Light {

/* base addresses */

const Address GPIO1 = 0x4804C000 ;

/* registers */

const Address OE     = 0x134 ;
const Address OUT    = 0x13C ;
const Address CLROUT = 0x190 ;
const Address SETOUT = 0x194 ;

  constexpr BitField LightMask=BitField(24,21);

/* functions */

inline void Init()
 {
  Reg(GPIO1,OE).insert(LightMask,0);
  
  Reg(GPIO1,OUT)=0;
 }

inline void Set(Register mask) // 4 lsb
 {
  Reg(GPIO1,OUT)=LightMask.insert(mask);
 }

inline void On(Register mask) // 4 lsb
 {
  Reg(GPIO1,SETOUT)=LightMask.insert(mask);
 }

inline void Off(Register mask) // 4 lsb
 {
  Reg(GPIO1,CLROUT)=LightMask.insert(mask);
 }

} // namespace Light

//- Stop ---------------------------------------------------------------------------------

inline void Stop(unsigned mask) // 4 lsb
 {
  const unsigned DelayCount=0x10000000;
  
  for(;;)
    {
     Light::Set(mask); 
     
     Delay(5*DelayCount);
     
     Light::Set(0);
     
     for(unsigned cnt=3; cnt ;cnt--)
       {
        Light::On(Bit(0)); Delay(DelayCount/8);
        Light::On(Bit(1)); Delay(DelayCount/8);
        Light::On(Bit(2)); Delay(DelayCount/8);
        Light::On(Bit(3)); Delay(DelayCount/8);
        
        Light::Off(Bit(0)); Delay(DelayCount/8);
        Light::Off(Bit(1)); Delay(DelayCount/8);
        Light::Off(Bit(2)); Delay(DelayCount/8);
        Light::Off(Bit(3)); Delay(DelayCount/8);
       }
    }
 }

//- PRCM ---------------------------------------------------------------------------------

namespace PRCM {

/* base addresses */

const Address CM_PERBase  = 0x44E00000 ;
const Address CM_WKUPBase = 0x44E00400 ;
const Address CM_DPLLBase = 0x44E00500 ;

/* registers */

const Address CM_PER_L4LS_CLKSTCTRL = 0x000 ;
const Address CM_PER_LCDC_CLKCTRL   = 0x018 ;
const Address CM_PER_TIMER2_CLKCTRL = 0x080 ;
const Address CM_PER_TIMER3_CLKCTRL = 0x084 ;
const Address CM_PER_TIMER4_CLKCTRL = 0x088 ;
const Address CM_PER_TIMER5_CLKCTRL = 0x0EC ;
const Address CM_PER_TIMER6_CLKCTRL = 0x0F0 ;
const Address CM_PER_TIMER7_CLKCTRL = 0x07C ;

   const Register StandbyStatus = Bit(18) ;
   constexpr BitField IdleStatus = BitField(17,16) ;
   constexpr BitField Status = BitField(18,16) ;
   constexpr BitField Mode = BitField(1,0) ;
   
const Address CM_IDLEST_DPLL_DISP = 0x48 ;

   const Register ST_DPLL_CLK  = Bit(0) ;
   const Register ST_MN_BYPASS = Bit(8) ;

const Address CM_CLKSEL_DPLL_DISP = 0x054 ;

   constexpr BitField DPLL_MULT = BitField(18,8) ;
   constexpr BitField DPLL_DIV = BitField(6,0) ;

const Address CM_CLKMODE_DPLL_DISP = 0x098 ;

   constexpr BitField DPLL_EN = BitField(2,0) ;

const Address CM_DIV_M2_DPLL_DISP = 0x0A4 ;

   const Register ST_DPLL_CLKOUT = Bit(9) ;
   constexpr BitField DPLL_CLKOUT_DIV = BitField(4,0) ;
   
const Address CLKSEL_LCDC_PIXEL_CLK = 0x034 ;

   constexpr BitField LCD_CLKSEL = BitField(1,0) ;
   
const Address CLKSEL_TIMER2_CLK = 0x008 ;
const Address CLKSEL_TIMER3_CLK = 0x00C ;
const Address CLKSEL_TIMER4_CLK = 0x010 ;

   constexpr BitField TIMER_CLKSEL = BitField(1,0) ;
   
/* classes */

class CM_PER_Instance;

class CM_WKUP_Instance;

class CM_DPLL_Instance;

/* class CM_PER_Instance */

class CM_PER_Instance
 {
   Address address;
  
  private:
  
   RegOp reg(Address offset) { return Reg(address,offset); }
  
  public:
  
   explicit CM_PER_Instance(Address address_=CM_PERBase) : address(address_) {}
   
   // LCD
   
   bool getLCDStandbyStatus() 
    {
     return reg(CM_PER_LCDC_CLKCTRL)&StandbyStatus;
    }
   
   Register getLCDIdleStatus()
    {  
     return reg(CM_PER_LCDC_CLKCTRL).extract(IdleStatus);
    }
   
   Register getLCDStatus()
    {
     return reg(CM_PER_LCDC_CLKCTRL).extract(Status);
    }
   
   void enableLCD()
    {
     reg(CM_PER_LCDC_CLKCTRL).insert(Mode,2);
    }

   // L4LSClocks
   
   Register getL4LSClocksStatus()
    {
     return reg(CM_PER_L4LS_CLKSTCTRL);
    }
   
   // Timer2
   
   Register getTimer2IdleStatus()
    {  
     return reg(CM_PER_TIMER2_CLKCTRL).extract(IdleStatus);
    }
   
   Register getTimer2Mode()
    {
     return reg(CM_PER_TIMER2_CLKCTRL).extract(Mode);
    }
   
   void enableTimer2()
    {
     reg(CM_PER_TIMER2_CLKCTRL).insert(Mode,2);
    }
   
   // Timer3
   
   Register getTimer3IdleStatus()
    {  
     return reg(CM_PER_TIMER3_CLKCTRL).extract(IdleStatus);
    }
   
   Register getTimer3Mode()
    {
     return reg(CM_PER_TIMER3_CLKCTRL).extract(Mode);
    }
   
   void enableTimer3()
    {
     reg(CM_PER_TIMER3_CLKCTRL).insert(Mode,2);
    }
   
   // Timer4
   
   Register getTimer4IdleStatus()
    {  
     return reg(CM_PER_TIMER4_CLKCTRL).extract(IdleStatus);
    }
   
   Register getTimer4Mode()
    {
     return reg(CM_PER_TIMER4_CLKCTRL).extract(Mode);
    }
   
   void enableTimer4()
    {
     reg(CM_PER_TIMER4_CLKCTRL).insert(Mode,2);
    }
 };

/* class CM_WKUP_Instance */

class CM_WKUP_Instance
 {
   Address address;

  private:

   RegOp reg(Address offset) { return Reg(address,offset); }

  public:

   explicit CM_WKUP_Instance(Address address_=CM_WKUPBase) : address(address_) {}
   
   // DISP
   
   void initDISP(Register clock) // MHz
    {
     reg(CM_CLKMODE_DPLL_DISP).insert(DPLL_EN,4);
     
     while( (reg(CM_IDLEST_DPLL_DISP)&ST_MN_BYPASS)==0 );
     
     
     reg(CM_CLKSEL_DPLL_DISP)=DPLL_MULT.insert(clock)|DPLL_DIV.insert(24-1); // assume OSC_M is 24 MHz
     
     reg(CM_DIV_M2_DPLL_DISP).insert(DPLL_CLKOUT_DIV,1);
     
     
     reg(CM_CLKMODE_DPLL_DISP).insert(DPLL_EN,7);
     
     while( (reg(CM_IDLEST_DPLL_DISP)&ST_DPLL_CLK)==0 );
    }
   
   bool testDISP() { return reg(CM_DIV_M2_DPLL_DISP)&ST_DPLL_CLKOUT; }
 };

/* class CM_DPLL_Instance */

class CM_DPLL_Instance
 {
   Address address;
 
  private:
 
   RegOp reg(Address offset) { return Reg(address,offset); }
 
  public:
 
   explicit CM_DPLL_Instance(Address address_=CM_DPLLBase) : address(address_) {}
   
   // LCD
   
   void setLCDDISPClock() { reg(CLKSEL_LCDC_PIXEL_CLK).insert(LCD_CLKSEL,0); }
   
   // Timer2
   
   Register getTimer2Clock()
    {
     return reg(CLKSEL_TIMER2_CLK).extract(TIMER_CLKSEL);
    }
   
   void setTimer2Clock(Register value)
    {
     reg(CLKSEL_TIMER2_CLK).insert(TIMER_CLKSEL,value);
    }
   
   // Timer3
   
   Register getTimer3Clock()
    {
     return reg(CLKSEL_TIMER3_CLK).extract(TIMER_CLKSEL);
    }
   
   void setTimer3Clock(Register value)
    {
     reg(CLKSEL_TIMER3_CLK).insert(TIMER_CLKSEL,value);
    }
   
   // Timer4
   
   Register getTimer4Clock()
    {
     return reg(CLKSEL_TIMER4_CLK).extract(TIMER_CLKSEL);
    }
   
   void setTimer4Clock(Register value)
    {
     reg(CLKSEL_TIMER4_CLK).insert(TIMER_CLKSEL,value);
    }
  };

} // namespace PRCM

//- I2C ----------------------------------------------------------------------------------

namespace I2C {

/* instances */

const Address I2C0 = 0x44E0B000 ;
const Address I2C1 = 0x4802A000 ;
const Address I2C2 = 0x4819C000 ;

/* registers */

const Address SYSC          = 0x010 ;

   const Register SoftReset = Bit(1) ;

const Address SYSS          = 0x090 ;

   const Register ResetDone = Bit(0) ;

const Address IRQSTATUS_RAW = 0x024 ;
const Address IRQSTATUS     = 0x028 ;
const Address IRQENABLE_SET = 0x02C ;
const Address IRQENABLE_CLR = 0x030 ;
const Address WE            = 0x034 ;

   const Register IRQ_BusBusy      = Bit(12) ;
   const Register IRQ_TXReady      = Bit(4) ;
   const Register IRQ_TXReadyShort = Bit(14) ;
   const Register IRQ_RXReady      = Bit(3) ;
   const Register IRQ_RXReadyShort = Bit(13) ;
   const Register IRQ_NACK         = Bit(1) ;
   const Register IRQ_BusLost      = Bit(0) ;
   const Register IRQ_Complete     = Bit(2) ;
   constexpr BitField IRQ_ALL      = BitField(14,0); 

const Address BUF           = 0x094 ;

   const Register RXFIFO_clear = Bit(14) ;
   constexpr BitField RXFIFO_threshold = BitField(13,8) ;   
   const Register TXFIFO_clear = Bit(6) ;
   constexpr BitField TXFIFO_threshold = BitField(5,0) ;   

const Address CNT           = 0x098 ;

   constexpr BitField DataCount = BitField(15,0) ;
   
const Address DATA          = 0x09C ;

   constexpr BitField Data = BitField(7,0) ;

const Address CON           = 0x0A4 ;

   const Register Enable = Bit(15) ;
   const Register STT    = Bit(0) ;
   const Register STP    = Bit(1) ;
   const Register TXMode = Bit(9) ;
   const Register Master = Bit(10) ;

const Address OA            = 0x0A8 ;
const Address SA            = 0x0AC ;

   constexpr BitField SlaveAddress = BitField(9,0) ; 

const Address PSC           = 0x0B0 ;

   constexpr BitField Prescale = BitField(7,0) ;

const Address SCLL          = 0x0B4 ;

   constexpr BitField LoTime = BitField(7,0) ;

const Address SCLH          = 0x0B8 ;

   constexpr BitField HiTime = BitField(7,0) ;

const Address BUFSTAT       = 0x0C0 ;

   constexpr BitField FIFODepth      = BitField(15,14) ;
   constexpr BitField RXFIFO_ToRead  = BitField(13,8) ;
   constexpr BitField TXFIFO_ToWrite = BitField(5,0) ;

/* classes */

class Instance;

/* class Instance */
   
enum Error
 {
  NoError = 0,
  
  Error_Timeout,
  Error_TXFault,
  Error_RXFault
 };

class Instance
 {
   static const unsigned Timeout = 1000000 ;

   Address address;
   
  private:
   
   RegOp reg(Address offset) { return Reg(address,offset); }
   
   Error wait_bus()
    {
     unsigned timeout=Timeout;
     
     while( reg(IRQSTATUS_RAW)&IRQ_BusBusy )
       {
        if( !--timeout ) return Error_Timeout;
       }
     
     return NoError;
    }
   
   Error start_tx(ulen len,bool with_stop)
    {
     reg(CNT)=DataCount.insert(len);
     
     if( Error ret=wait_bus() ) return ret;
     
     reg(CON).bitset(STT|STP|TXMode|Master,with_stop?(STT|STP|TXMode|Master):(STT|TXMode|Master));
     
     return NoError;
    }
   
   Error wait_tx(octet data)
    {
     unsigned timeout=Timeout;
     
     Register status;
     
     const Register Mask=IRQ_BusLost|IRQ_NACK|IRQ_TXReady|IRQ_TXReadyShort;
     
     while( ( status=(reg(IRQSTATUS_RAW)&Mask) )==0 )
       {
        if( !--timeout ) 
          {
           return Error_Timeout;
          }
       }
     
     if( status&(IRQ_BusLost|IRQ_NACK) ) 
       {
        reg(IRQSTATUS)=status;
        
        return Error_TXFault;
       }
     
     reg(DATA)=Data.insert(data);
     
     reg(IRQSTATUS)=status;
     
     return NoError;
    }
   
   Error wait_txcomplete()
    {
     unsigned timeout=Timeout;
     
     Register status;
     
     const Register Mask=IRQ_BusLost|IRQ_NACK|IRQ_Complete;
     
     while( ( status=(reg(IRQSTATUS_RAW)&Mask) )==0 )
       {
        if( !--timeout ) return Error_Timeout;
       }
     
     reg(IRQSTATUS)=IRQ_ALL;
     
     return (status==IRQ_Complete)?NoError:Error_TXFault;
    }
   
   Error wait_tx_complete(octet data)
    {
     if( Error ret=wait_tx(data) ) 
       {
        wait_txcomplete();
       
        reg(BUF).bitset(TXFIFO_clear);
        
        return ret;
       }
     
     return NoError;
    }
   
   Error start_rx(ulen len)
    {
     reg(CNT)=DataCount.insert(len);
     
     if( Error ret=wait_bus() ) return ret;
     
     reg(CON).bitset(STT|STP|TXMode|Master,STT|STP|Master);
     
     return NoError;
    }
   
   Error wait_rx(octet &data)
    {
     unsigned timeout=Timeout;
     
     Register status;
     
     const Register Mask=IRQ_BusLost|IRQ_NACK|IRQ_RXReady|IRQ_RXReadyShort;
     
     while( ( status=(reg(IRQSTATUS_RAW)&Mask) )==0 )
       {
        if( !--timeout ) return Error_Timeout;
       }
     
     if( status&(IRQ_BusLost|IRQ_NACK) ) 
       {
        reg(IRQSTATUS)=status;
        
        return Error_RXFault;
       }
     
     data=(octet)reg(DATA).extract(Data);
     
     reg(IRQSTATUS)=status;
     
     return NoError;
    }
   
   Error wait_rxcomplete()
    {
     unsigned timeout=Timeout;
     
     Register status;
     
     const Register Mask=IRQ_BusLost|IRQ_NACK|IRQ_Complete;
     
     while( ( status=(reg(IRQSTATUS_RAW)&Mask) )==0 )
       {
        if( !--timeout ) return Error_Timeout;
       }
     
     reg(IRQSTATUS)=IRQ_ALL;
     
     return (status==IRQ_Complete)?NoError:Error_RXFault;
    }
   
  public:
   
   explicit Instance(Address address_) : address(address_) {}
   
   // initialization
   
   void reset()
    {
     reg(SYSC).bitset(SoftReset);
     
     while( reg(SYSC)&SoftReset );
    }
   
   void init(octet own_address,bool fast=false)
    {
     reg(CON)=0;
     
     reg(PSC)=Prescale.insert(4-1); // 48 MHz -> 12 MHz
     
     if( fast ) // 12 MHz clock
       {
        const unsigned div=30; // -> 400 kHz
       
        reg(SCLL)=LoTime.insert(div/2-7);
        reg(SCLH)=HiTime.insert(div/2-5);
       }
     else
       {
        const unsigned div=120; // -> 100 kHz
      
        reg(SCLL)=LoTime.insert(div/2-7);
        reg(SCLH)=HiTime.insert(div/2-5);
       }
     
     Register fifo=getFIFODepth();
     Register threshold=(4<<fifo)-1;
     
     reg(BUF)=RXFIFO_threshold.insert(threshold)|TXFIFO_threshold.insert(threshold);
     
     reg(OA)=SlaveAddress.insert(own_address);
     
     reg(CON)=Enable;
    }
   
   void init_fast(octet own_address) { init(own_address,true); }
   
   Register getFIFODepth() { return reg(BUFSTAT).extract(FIFODepth); }
   
   // operational
   
   void setSlave(octet address) { reg(SA)=SlaveAddress.insert(address); }
   
   Error read(octet *ptr,ulen len)
    {
     if( Error ret=start_rx(len) ) return ret;
     
     for(; len ;len--,ptr++)
       {
        if( Error ret=wait_rx(*ptr) ) 
          {
           wait_rxcomplete();
           
           reg(BUF).bitset(RXFIFO_clear);
           
           return ret;
          }
       }
     
     return wait_rxcomplete();
    }
   
   Error read(octet address,octet *ptr,ulen len,bool with_stop=true)
    {
     if( Error ret=write_address(address,with_stop) ) return ret;
     
     return read(ptr,len);
    }
   
   Error read(octet address1,octet address2,octet *ptr,ulen len,bool with_stop=true)
    {
     if( Error ret=write_address(address1,address2,with_stop) ) return ret;
     
     return read(ptr,len);
    }
   
   Error write(const octet *ptr,ulen len,bool with_stop=true)
    {
     if( Error ret=start_tx(len,with_stop) ) return ret;
     
     for(; len ;len--,ptr++)
       {
        if( Error ret=wait_tx_complete(*ptr) ) return ret; 
       }
     
     return wait_txcomplete();
    }
   
   Error write(octet address,const octet *ptr,ulen len,bool with_stop=true)
    {
     if( Error ret=start_tx(len+1,with_stop) ) return ret;
     
     if( Error ret=wait_tx_complete(address) ) return ret;
     
     for(; len ;len--,ptr++)
       {
        if( Error ret=wait_tx_complete(*ptr) ) return ret; 
       }
     
     return wait_txcomplete();
    }
   
   Error write(octet address1,octet address2,const octet *ptr,ulen len,bool with_stop=true)
    {
     if( Error ret=start_tx(len+2,with_stop) ) return ret;
     
     if( Error ret=wait_tx_complete(address1) ) return ret;
     
     if( Error ret=wait_tx_complete(address2) ) return ret;
     
     for(; len ;len--,ptr++)
       {
        if( Error ret=wait_tx_complete(*ptr) ) return ret; 
       }
     
     return wait_txcomplete();
    }
   
   Error write_address(octet address,bool with_stop=true)
    {
     if( Error ret=start_tx(1,with_stop) ) return ret;
     
     if( Error ret=wait_tx_complete(address) ) return ret;
     
     return wait_txcomplete();
    }
   
   Error write_address(octet address1,octet address2,bool with_stop=true)
    {
     if( Error ret=start_tx(2,with_stop) ) return ret;
     
     if( Error ret=wait_tx_complete(address1) ) return ret;
     
     if( Error ret=wait_tx_complete(address2) ) return ret;
     
     return wait_txcomplete();
    }
 };

} // namespace I2C

//- EDID ---------------------------------------------------------------------------------

namespace EDID {

/* consts */

const ulen Len = 128 ;

/* classes */

struct Mode;

/* struct Mode */

struct Mode
 {
  bool ok;
  
  unsigned hlen;        // 12 bit
  unsigned hblank;      // 12 bit
  unsigned hsync_off;   // 10 bit
  unsigned hsync_pulse; // 10 bit
  
  unsigned vlen;        // 12 bit
  unsigned vblank;      // 12 bit
  unsigned vsync_off;   // 6 bit
  unsigned vsync_pulse; // 6 bit
  
  unsigned clock;       // 16 bit, 10 kHz unit
  
  octet flags;
  
  Mode() {}
  
  explicit Mode(const octet buf[Len])
   : ok(false)
   {
    if( buf[0]!=0x00 || buf[1]!=0xFF || buf[2]!=0xFF || buf[3]!=0xFF || 
        buf[4]!=0xFF || buf[5]!=0xFF || buf[6]!=0xFF || buf[7]!=0x00 ) return;
    
    {
     octet sum=0;
     const octet *ptr=buf;
     
     for(ulen cnt=Len; cnt ;cnt--) sum+=*(ptr++);
     
     if( sum ) return;
    }
 
    {
     const octet *desc=buf+54;
     
     clock=Octet2(desc[0],desc[1]);
     
     hlen=Octet2(desc[2],desc[4]>>4);
     hblank=Octet2(desc[3],desc[4]&0x0F);
     
     vlen=Octet2(desc[5],desc[7]>>4);
     vblank=Octet2(desc[6],desc[7]&0x0F);
     
     hsync_off=Octet2(desc[8],desc[11]>>6);
     hsync_pulse=Octet2(desc[9],(desc[11]>>4)&0x02);
     
     vsync_off=Octet2(desc[10]>>4,(desc[11]>>2)&0x02);
     vsync_pulse=Octet2(desc[10]&0x0F,desc[11]&0x02);
     
     flags=desc[17];
    }
    
    ok=true;
   }
  
  bool isInterlaced() const { return flags&Bit(7); }
  
  octet syncType() const { return (flags>>3)&0x02; } // 11 -- digital separate, 10 -- digital composite
  
  bool hsyncPos() const { return flags&Bit(1); }
  
  bool vsyncPos() const { return flags&Bit(2); }
 };

} // namespace EDID

//- HDMI ---------------------------------------------------------------------------------

namespace HDMI {

/* CEC registers */

const Address CEC_ENAMODS = 0xFF ;

   const Register CEC_ENAMODS_EN_CEC    = Bit(0) ;
   const Register CEC_ENAMODS_EN_HDMI   = Bit(1) ;
   const Register CEC_ENAMODS_EN_RXSENS = Bit(2) ;
   const Register CEC_ENAMODS_DIS_CCLK  = Bit(5) ;
   const Register CEC_ENAMODS_DIS_FRO   = Bit(6) ;
   
const Address CEC_FRO_IM_CLK_CTRL = 0xFB ;

   const Register CEC_FRO_IM_CLK_CTRL_FRO_DIV   = Bit(0) ;
   const Register CEC_FRO_IM_CLK_CTRL_IMCLK_SEL = Bit(1) ;
   const Register CEC_FRO_IM_CLK_CTRL_ENA_OTP   = Bit(6) ;
   const Register CEC_FRO_IM_CLK_CTRL_GHOST_DIS = Bit(7) ;

const Address CEC_RXSHPDLEV = 0xFE ;

   const Register CEC_RXSHPDLEV_RXSENS = Bit(0) ;
   const Register CEC_RXSHPDLEV_HPD    = Bit(1) ;
   
/* HDMI page 0 */
   
const Address VERSION_LSB = 0x00 ;
const Address VERSION_MSB = 0x02 ;

const Address MAIN_CNTRL0 = 0x01 ;

   const Register MAIN_CNTRL0_SR     = Bit(0) ;
   const Register MAIN_CNTRL0_DECS   = Bit(1) ; 
   const Register MAIN_CNTRL0_DEHS   = Bit(2) ; 
   const Register MAIN_CNTRL0_CECS   = Bit(3) ;
   const Register MAIN_CNTRL0_CEHS   = Bit(4) ;
   const Register MAIN_CNTRL0_SCALER = Bit(7) ;
   
const Address SOFTRESET = 0x0A ;

   const Register SOFTRESET_AUDIO     = Bit(0) ;
   const Register SOFTRESET_I2CMASTER = Bit(1) ;
   
const Address DDC_DISABLE = 0x0B ;

const Address REG_INT_FLAGS_2 = 0x11 ;

   const Register INT_FLAGS_2_EDID_BLK_RD = Bit(1) ;

const Address ENA_VP_0 = 0x18 ;
const Address ENA_VP_1 = 0x19 ;
const Address ENA_VP_2 = 0x1A ;

const Address VIP_CNTRL_0 = 0x20 ;

   const Register VIP_CNTRL_0_MIRR_A     = Bit(7) ;
   const Register VIP_CNTRL_0_MIRR_B     = Bit(3) ;
   constexpr BitField VIP_CNTRL_0_SWAP_A = BitField(6,4) ;
   constexpr BitField VIP_CNTRL_0_SWAP_B = BitField(2,0) ;

const Address VIP_CNTRL_1 = 0x21 ;

   const Register VIP_CNTRL_1_MIRR_C     = Bit(7) ;
   const Register VIP_CNTRL_1_MIRR_D     = Bit(3) ;
   constexpr BitField VIP_CNTRL_1_SWAP_C = BitField(6,4) ;
   constexpr BitField VIP_CNTRL_1_SWAP_D = BitField(2,0) ;

const Address VIP_CNTRL_2 = 0x22 ;

   const Register VIP_CNTRL_2_MIRR_E     = Bit(7) ;
   const Register VIP_CNTRL_2_MIRR_F     = Bit(3) ;
   constexpr BitField VIP_CNTRL_2_SWAP_E = BitField(6,4) ;
   constexpr BitField VIP_CNTRL_2_SWAP_F = BitField(2,0) ;
   
const Address VIP_CNTRL_3 = 0x23 ;

   const Register VIP_CNTRL_3_X_TGL   = Bit(0) ;
   const Register VIP_CNTRL_3_H_TGL   = Bit(1) ;
   const Register VIP_CNTRL_3_V_TGL   = Bit(2) ;
   const Register VIP_CNTRL_3_EMB     = Bit(3) ;
   const Register VIP_CNTRL_3_SYNC_DE = Bit(4) ;
   const Register VIP_CNTRL_3_SYNC_HS = Bit(5) ;
   const Register VIP_CNTRL_3_DE_INT  = Bit(6) ;
   const Register VIP_CNTRL_3_EDGE    = Bit(7) ;
        
const Address VIP_CNTRL_4 = 0x24 ;

   const Register VIP_CNTRL_4_CCIR656     = Bit(4) ;
   const Register VIP_CNTRL_4_656_ALT     = Bit(5) ;
   const Register VIP_CNTRL_4_TST_656     = Bit(6) ;
   const Register VIP_CNTRL_4_TST_PAT     = Bit(7) ;
   constexpr BitField VIP_CNTRL_4_BLC     = BitField(1,0) ;
   constexpr BitField VIP_CNTRL_4_BLANKIT = BitField(3,2) ;
      
const Address VIP_CNTRL_5 = 0x25 ;

   const Register VIP_CNTRL_5_CKCASE = Bit(0) ;
   constexpr BitField VIP_CNTRL_5_SP_CNT = BitField(2,1) ;
      
const Address MUX_VP_VIP_OUT = 0x27 ;

const Address MAT_CONTRL = 0x80 ;

  const Register MAT_CONTRL_MAT_BP     = Bit(2) ;
  constexpr BitField MAT_CONTRL_MAT_SC = BitField(1,0) ;

const Address VIDFORMAT = 0xA0 ;

const Address REFPIX         = 0xA1 ;
const Address REFLINE        = 0xA3 ;
const Address NPIX           = 0xA5 ;
const Address NLINE          = 0xA7 ;
const Address VS_LINE_STRT_1 = 0xA9 ;
const Address VS_PIX_STRT_1  = 0xAB ;
const Address VS_LINE_END_1  = 0xAD ;
const Address VS_PIX_END_1   = 0xAF ;
const Address VS_LINE_STRT_2 = 0xB1 ;
const Address VS_PIX_STRT_2  = 0xB3 ;
const Address VS_LINE_END_2  = 0xB5 ;
const Address VS_PIX_END_2   = 0xB7 ;
const Address HS_PIX_START   = 0xB9 ;
const Address HS_PIX_STOP    = 0xBB ;
const Address VWIN_START_1   = 0xBD ;
const Address VWIN_END_1     = 0xBF ;
const Address VWIN_START_2   = 0xC1 ;
const Address VWIN_END_2     = 0xC3 ;
const Address DE_START       = 0xC5 ;
const Address DE_STOP        = 0xC7 ;

const Address TBG_CNTRL_0 = 0xCA ;

   const Register TBG_CNTRL_0_TOP_TGL   = Bit(0) ;
   const Register TBG_CNTRL_0_TOP_SEL   = Bit(1) ;
   const Register TBG_CNTRL_0_DE_EXT    = Bit(2) ;
   const Register TBG_CNTRL_0_TOP_EXT   = Bit(3) ;
   const Register TBG_CNTRL_0_FRAME_DIS = Bit(5) ;
   const Register TBG_CNTRL_0_SYNC_MTHD = Bit(6) ;
   const Register TBG_CNTRL_0_SYNC_ONCE = Bit(7) ;

const Address TBG_CNTRL_1 = 0xCB ;
      
   const Register TBG_CNTRL_1_H_TGL    = Bit(0) ;
   const Register TBG_CNTRL_1_V_TGL    = Bit(1) ;
   const Register TBG_CNTRL_1_TGL_EN   = Bit(2) ;
   const Register TBG_CNTRL_1_X_EXT    = Bit(3) ;
   const Register TBG_CNTRL_1_H_EXT    = Bit(4) ;
   const Register TBG_CNTRL_1_V_EXT    = Bit(5) ;
   const Register TBG_CNTRL_1_DWIN_DIS = Bit(6) ;
      
const Address ENABLE_SPACE = 0xD6 ;

const Address HVF_CNTRL_0 = 0xE4 ;

   const Register HVF_CNTRL_0_SM  = Bit(7) ;
   const Register HVF_CNTRL_0_RWB = Bit(6) ; 
   constexpr BitField HVF_CNTRL_0_PREFIL = BitField(3,2) ;
   constexpr BitField HVF_CNTRL_0_INTPOL = BitField(1,0) ;
   
const Address HVF_CNTRL_1 = 0xE5 ;

   const Register HVF_CNTRL_1_FOR         = Bit(0) ;
   const Register HVF_CNTRL_1_YUVBLK      = Bit(1) ;
   const Register HVF_CNTRL_1_SEMI_PLANAR = Bit(6) ;
   constexpr BitField HVF_CNTRL_1_VQR = BitField(3,2) ;
   constexpr BitField HVF_CNTRL_1_PAD = BitField(5,4) ;
   
const Address RPT_CNTRL = 0xF0 ;

/* HDMI page 2 */
   
const Address PLL_SERIAL_1 = 0x00 ;

   const Register PLL_SERIAL_1_SRL_FDN    = Bit(0) ;
   const Register PLL_SERIAL_1_SRL_MAN_IZ = Bit(6) ;
   constexpr BitField PLL_SERIAL_1_SRL_IZ = BitField(2,1) ;

const Address PLL_SERIAL_2 = 0x01 ;

   constexpr BitField PLL_SERIAL_2_SRL_NOSC = BitField(1,0) ;
   constexpr BitField PLL_SERIAL_2_SRL_PR   = BitField(7,4) ;

const Address PLL_SERIAL_3 = 0x02 ;

   const Register PLL_SERIAL_3_SRL_CCIR     = Bit(0) ;
   const Register PLL_SERIAL_3_SRL_DE       = Bit(2) ;
   const Register PLL_SERIAL_3_SRL_PXIN_SEL = Bit(4) ;
   
const Address SERIALIZER   = 0x03 ;
const Address BUFFER_OUT   = 0x04 ;
const Address PLL_SCG1     = 0x05 ;
const Address PLL_SCG2     = 0x06 ;
const Address PLL_SCGN1    = 0x07 ;
const Address PLL_SCGN2    = 0x08 ;
const Address PLL_SCGR1    = 0x09 ;
const Address PLL_SCGR2    = 0x0A ;
const Address AUDIO_DIV    = 0x0E ;

const Address SEL_CLK      = 0x11 ;

   const Register SEL_CLK_SEL_CLK1        = Bit(0) ;
   const Register SEL_CLK_ENA_SC_CLK      = Bit(3) ;
   constexpr BitField SEL_CLK_SEL_VRF_CLK = BitField(2,1) ;

const Address ANA_GENERAL     = 0x12 ;

/* HDMI page 0x09 */

const Address REG_EDID_DATA_0 = 0x00 ; // 128 registers -- EDID block

const Address REG_EDID_CTRL     = 0xFA ;
const Address REG_DDC_ADDR      = 0xFB ;
const Address REG_DDC_OFFS      = 0xFC ;
const Address REG_DDC_SEGM_ADDR = 0xFD ;
const Address REG_DDC_SEGM      = 0xFE ;

/* HDMI page 0x11 */
   
const Address AIP_CNTRL_0 = 0x00 ;

   const Register AIP_CNTRL_0_RST_FIFO = Bit(0) ;
   const Register AIP_CNTRL_0_SWAP     = Bit(1) ;
   const Register AIP_CNTRL_0_LAYOUT   = Bit(2) ;
   const Register AIP_CNTRL_0_ACR_MAN  = Bit(5) ;
   const Register AIP_CNTRL_0_RST_CTS  = Bit(6) ;

const Address ENC_CNTRL = 0x0D ;

   const Register ENC_CNTRL_RST_ENC      = Bit(0) ;
   const Register ENC_CNTRL_RST_SEL      = Bit(1) ;
   constexpr BitField ENC_CNTRL_CTL_CODE = BitField(3,2) ; 
   
/* HDMI page 0x12 */

const Address TX3 = 0x9A ;

const Address TX4 = 0x9B ;

   const Register TX4_PD_RAM = Bit(1) ;

const Address TX33 = 0xB8 ;   

   const Register TX33_HDMI = Bit(1) ;
   
/* classes */

class Instance;

/* class Instance */

enum Error
 {
  NoError = 0,
  
  Error_Timeout,
  Error_TXFault,
  Error_RXFault,
  
  Error_BadVersion,
  Error_EDIDTimeout
 };

struct Detect
 {
  bool plug;
  bool power;
 };

struct ModeGeometry
 {
  Register htotal;
  Register hdisplay;
  Register hsync_start;
  Register hsync_end;
  
  Register vtotal;
  Register vdisplay;
  Register vsync_start;
  Register vsync_end;
  
  ModeGeometry() {}
  
  ModeGeometry(const EDID::Mode &mode) 
   {
    htotal=mode.hlen+mode.hblank;
    hdisplay=mode.hlen;
    hsync_start=mode.hlen+mode.hsync_off;
    hsync_end=mode.hlen+mode.hsync_off+mode.hsync_pulse;
    
    vtotal=mode.vlen+mode.vblank;
    vdisplay=mode.vlen;
    vsync_start=mode.vlen+mode.vsync_off;
    vsync_end=mode.vlen+mode.vsync_off+mode.vsync_pulse;
   }
 };

struct ModeProp
 {
  Register clock;
  
  bool negHSync;
  bool negVSync;
  
  ModeProp() {}
  
  ModeProp(const EDID::Mode &mode)
   {
    clock=mode.clock*10;
    
    negHSync=!mode.hsyncPos();
    negVSync=!mode.vsyncPos();
   }
 };

struct ModeDesc
 {
  Register div;
  Register rep;
  
  bool negHSync;
  bool negVSync;
  
  Register ref_line;
  Register ref_pix;
  Register n_line;
  Register n_pix;
  
  Register vs1_line_s;
  Register vs1_line_e;
  Register vs1_pix_s;
  Register vs1_pix_e;
  
  Register vs2_line_s;
  Register vs2_line_e;
  Register vs2_pix_s;
  Register vs2_pix_e;
  
  Register vwin1_line_s;
  Register vwin1_line_e;
  
  Register vwin2_line_s;
  Register vwin2_line_e;
  
  Register de_pix_s;
  Register de_pix_e;
  
  Register hs_pix_s;
  Register hs_pix_e;
  
  ModeDesc() {}
  
  ModeDesc(const ModeGeometry &geom,const ModeProp &prop)
   {
    n_pix  = geom.htotal ;
    n_line = geom.vtotal ;
    
    hs_pix_s = geom.hsync_start - geom.hdisplay ;
    hs_pix_e = geom.hsync_end   - geom.hdisplay ;
    
    de_pix_s = geom.htotal - geom.hdisplay ;
    de_pix_e = de_pix_s + geom.hdisplay ;
    
    ref_pix  = 3 + geom.hsync_start - geom.hdisplay ;
    ref_line = 1 + geom.vsync_start - geom.vdisplay ;
    
    vwin1_line_s = geom.vtotal - geom.vsync_start - 1 ;
    vwin1_line_e = vwin1_line_s + geom.vdisplay ;
    
    vs1_pix_s    = geom.hsync_start - geom.hdisplay ;
    vs1_pix_e    = geom.hsync_start - geom.hdisplay ;
    
    vs1_line_s   = geom.vsync_start - geom.vdisplay ;
    vs1_line_e   = geom.vsync_end - geom.vdisplay ;
    
    vwin2_line_s = 0 ;
    vwin2_line_e = 0 ;
    
    vs2_pix_s    = 0 ;
    vs2_pix_e    = 0 ;
    
    vs2_line_s   = 0 ;
    vs2_line_e   = 0 ;
    
    div = 148500/prop.clock ;
    rep = 0 ;
    negHSync = prop.negHSync ;
    negVSync = prop.negVSync ;
   }
 };

class Instance
 {
   static const unsigned Timeout = 1000000 ;
   
   I2C::Instance dev;
   octet cec_address;
   octet hdmi_address;
   
   Register version;
   
  private:
   
   void setCEC() { dev.setSlave(cec_address); }
   
   Error read(octet address,octet &data)
    {
     return (Error)(unsigned)dev.read(address,&data,1);
    }
   
   Error write(octet address,octet data)
    {
     return (Error)(unsigned)dev.write(address,&data,1);
    }

   void setHDMI() { dev.setSlave(hdmi_address); }
   
   Error setPage(octet page) { return write(0xFF,page); } 

   Error bitset(octet address,octet bits)
    {
     octet data;
     
     if( auto ret=read(address,data) ) return ret;
     
     data|=bits;
     
     return write(address,data);
    }
   
   Error bitclear(octet address,octet bits)
    {
     octet data;
     
     if( auto ret=read(address,data) ) return ret;
     
     data&=~bits;
     
     return write(address,data);
    }
   
   Error write16(octet address,Register value)
    {
     octet buf[2]={octet(value>>8),octet(value)};
     
     return (Error)(unsigned)dev.write(address,buf,2);
    }
   
   Error read(octet address,octet *ptr,ulen len)
    {
     return (Error)(unsigned)dev.read(address,ptr,len);
    }
   
  public:
  
   Instance(Address i2c_address,octet cec_address_,octet hdmi_address_) 
    : dev(i2c_address),cec_address(cec_address_),hdmi_address(hdmi_address_) {}
   
   Instance() : Instance(I2C::I2C0,0x34,0x70) {}
   
   // initialization
   
   void init_I2C()
    {
     dev.reset();
     dev.init_fast(0x01);
    }
   
   Error init()
    {
     setCEC();
     
     if( auto ret=write(CEC_ENAMODS,CEC_ENAMODS_EN_HDMI|CEC_ENAMODS_EN_RXSENS) ) return ret;
     
     // reset
     
     setHDMI();
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(SOFTRESET,SOFTRESET_AUDIO|SOFTRESET_I2CMASTER) ) return ret;
     
     Delay(50000000);
     
     if( auto ret=write(SOFTRESET,0) ) return ret;
     
     Delay(50000000);
     
     if( auto ret=bitset(MAIN_CNTRL0,MAIN_CNTRL0_SR) ) return ret;
     
     if( auto ret=bitclear(MAIN_CNTRL0,MAIN_CNTRL0_SR) ) return ret;
     
     // set PLL
     
     if( auto ret=setPage(2) ) return ret;
     
     if( auto ret=write(PLL_SERIAL_1,0x00) ) return ret;
     
     if( auto ret=write(PLL_SERIAL_2,PLL_SERIAL_2_SRL_NOSC.insert(1)) ) return ret;
     
     if( auto ret=write(PLL_SERIAL_3,0x00) ) return ret;
     
     if( auto ret=write(SERIALIZER,0x00) ) return ret;
     
     if( auto ret=write(BUFFER_OUT,0x00) ) return ret;
     
     if( auto ret=write(PLL_SCG1,0x00) ) return ret;
     
     if( auto ret=write(AUDIO_DIV,3) ) return ret;
     
     if( auto ret=write(SEL_CLK,SEL_CLK_SEL_CLK1|SEL_CLK_ENA_SC_CLK) ) return ret;
     
     if( auto ret=write(PLL_SCGN1,0xFA) ) return ret;
     
     if( auto ret=write(PLL_SCGN2,0x00) ) return ret;
     
     if( auto ret=write(PLL_SCGR1,0x5B) ) return ret;
     
     if( auto ret=write(PLL_SCGR2,0x00) ) return ret;
     
     if( auto ret=write(PLL_SCG2,0x10) ) return ret;
     
     // set MUX
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(MUX_VP_VIP_OUT,0x24) ) return ret;
     
     // get version
     
     {
      octet lsb,msb;
      
      if( auto ret=read(VERSION_LSB,lsb) ) return ret;
      if( auto ret=read(VERSION_MSB,msb) ) return ret;
      
      version=(Register(msb)<<8)|lsb;
      
      if( (version&~0x30)!=0x0301 ) return Error_BadVersion;
     }
     
     // enable DDC
     
     if( auto ret=write(DDC_DISABLE,0) ) return ret;
     
     // set DDC clock
     
     if( auto ret=setPage(0x12) ) return ret;
     
     if( auto ret=write(TX3,39) ) return ret;
     
     // finish 
     
     setCEC();
     
     if( auto ret=write(CEC_FRO_IM_CLK_CTRL,CEC_FRO_IM_CLK_CTRL_GHOST_DIS|CEC_FRO_IM_CLK_CTRL_IMCLK_SEL) ) return ret;
     
     return NoError;
    }
   
   Detect detect()
    {
     setCEC();

     octet data;
     
     if( read(CEC_RXSHPDLEV,data) ) return {false,false};
     
     return {bool(data&CEC_RXSHPDLEV_HPD),bool(data&CEC_RXSHPDLEV_RXSENS)};
    }
   
   Error enableVIP()
    {
     setHDMI();
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(ENA_VP_0,0xFF) ) return ret;
     if( auto ret=write(ENA_VP_1,0xFF) ) return ret;
     if( auto ret=write(ENA_VP_2,0xFF) ) return ret;
     
     if( auto ret=write(VIP_CNTRL_0,VIP_CNTRL_0_SWAP_A.insert(2)|VIP_CNTRL_0_SWAP_B.insert(3)) ) return ret;
     if( auto ret=write(VIP_CNTRL_1,VIP_CNTRL_1_SWAP_C.insert(0)|VIP_CNTRL_1_SWAP_D.insert(1)) ) return ret;
     if( auto ret=write(VIP_CNTRL_2,VIP_CNTRL_2_SWAP_E.insert(4)|VIP_CNTRL_2_SWAP_F.insert(5)) ) return ret;
     
     return NoError;
    }
   
   Error disableVIP()
    {
     setHDMI();
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(ENA_VP_0,0) ) return ret;
     if( auto ret=write(ENA_VP_1,0) ) return ret;
     if( auto ret=write(ENA_VP_2,0) ) return ret;
     
     return NoError;
    }
   
   Error setMode(const ModeDesc &mode)
    {
     setHDMI();
     
     if( auto ret=setPage(0x11) ) return ret;
     
     if( auto ret=bitset(AIP_CNTRL_0,AIP_CNTRL_0_RST_FIFO) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=bitset(TBG_CNTRL_1,TBG_CNTRL_1_DWIN_DIS) ) return ret;
     
     if( auto ret=setPage(0x12) ) return ret;
     
     if( auto ret=bitclear(TX33,TX33_HDMI) ) return ret;
     
     if( auto ret=setPage(0x11) ) return ret;
     
     if( auto ret=write(ENC_CNTRL,ENC_CNTRL_CTL_CODE.insert(0)) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(HVF_CNTRL_0,HVF_CNTRL_0_PREFIL.insert(0)|HVF_CNTRL_0_INTPOL.insert(0)) ) return ret;
     
     if( auto ret=write(VIP_CNTRL_5,VIP_CNTRL_5_SP_CNT.insert(0)) ) return ret;
     
     if( auto ret=write(VIP_CNTRL_4,VIP_CNTRL_4_BLANKIT.insert(0)|VIP_CNTRL_4_BLC.insert(0)) ) return ret;
     
     if( auto ret=setPage(2) ) return ret;
     
     if( auto ret=bitclear(PLL_SERIAL_3,PLL_SERIAL_3_SRL_CCIR) ) return ret;
     
     if( auto ret=bitclear(PLL_SERIAL_1,PLL_SERIAL_1_SRL_MAN_IZ) ) return ret;
     
     if( auto ret=bitclear(PLL_SERIAL_3,PLL_SERIAL_3_SRL_DE) ) return ret;
     
     if( auto ret=write(SERIALIZER,0) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(HVF_CNTRL_1,HVF_CNTRL_1_VQR.insert(0)) ) return ret;
     
     if( auto ret=write(RPT_CNTRL,0) ) return ret;
     
     if( auto ret=setPage(2) ) return ret;
     
     if( auto ret=write(SEL_CLK,SEL_CLK_SEL_VRF_CLK.insert(0)|SEL_CLK_SEL_CLK1|SEL_CLK_ENA_SC_CLK) ) return ret;
     
     if( auto ret=write(PLL_SERIAL_2,PLL_SERIAL_2_SRL_NOSC.insert(mode.div)|PLL_SERIAL_2_SRL_PR.insert(mode.rep)) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=bitset(MAT_CONTRL,MAT_CONTRL_MAT_BP) ) return ret;
     
     if( auto ret=setPage(2) ) return ret;
     
     if( auto ret=write(ANA_GENERAL,0x09) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=write(TBG_CNTRL_0,TBG_CNTRL_0_SYNC_MTHD) ) return ret;
     
     if( auto ret=write(VIP_CNTRL_3,0) ) return ret;
     
     if( auto ret=bitset(VIP_CNTRL_3,VIP_CNTRL_3_SYNC_HS) ) return ret;
     
     if( mode.negHSync )
       {
        if( auto ret=bitset(VIP_CNTRL_3,VIP_CNTRL_3_H_TGL) ) return ret;
       }
     
     if( mode.negVSync )
       {
        if( auto ret=bitset(VIP_CNTRL_3,VIP_CNTRL_3_V_TGL) ) return ret;
       }
     
     if( auto ret=write(TBG_CNTRL_1,TBG_CNTRL_1_TGL_EN|(mode.negHSync?TBG_CNTRL_1_H_TGL:0)|(mode.negVSync?TBG_CNTRL_1_V_TGL:0)) ) return ret;
     
     if( auto ret=write(VIDFORMAT,0x00) ) return ret;
     
     if( auto ret=write16(REFPIX,mode.ref_pix) ) return ret;
     if( auto ret=write16(REFLINE,mode.ref_line) ) return ret;
     if( auto ret=write16(NPIX,mode.n_pix) ) return ret;
     if( auto ret=write16(NLINE,mode.n_line) ) return ret;
     if( auto ret=write16(VS_LINE_STRT_1,mode.vs1_line_s) ) return ret;
     if( auto ret=write16(VS_PIX_STRT_1,mode.vs1_pix_s) ) return ret;
     if( auto ret=write16(VS_LINE_END_1,mode.vs1_line_e) ) return ret;
     if( auto ret=write16(VS_PIX_END_1,mode.vs1_pix_e) ) return ret;
     if( auto ret=write16(VS_LINE_STRT_2,mode.vs2_line_s) ) return ret;
     if( auto ret=write16(VS_PIX_STRT_2,mode.vs2_pix_s) ) return ret;
     if( auto ret=write16(VS_LINE_END_2,mode.vs2_line_e) ) return ret;
     if( auto ret=write16(VS_PIX_END_2,mode.vs2_pix_e) ) return ret;
     if( auto ret=write16(HS_PIX_START,mode.hs_pix_s) ) return ret;
     if( auto ret=write16(HS_PIX_STOP,mode.hs_pix_e) ) return ret;
     if( auto ret=write16(VWIN_START_1,mode.vwin1_line_s) ) return ret;
     if( auto ret=write16(VWIN_END_1,mode.vwin1_line_e) ) return ret;
     if( auto ret=write16(VWIN_START_2,mode.vwin2_line_s) ) return ret;
     if( auto ret=write16(VWIN_END_2,mode.vwin2_line_e) ) return ret;
     if( auto ret=write16(DE_START,mode.de_pix_s) ) return ret;
     if( auto ret=write16(DE_STOP,mode.de_pix_e) ) return ret;
     
     if( auto ret=write(ENABLE_SPACE,0x01) ) return ret;
     
     if( auto ret=bitclear(TBG_CNTRL_0,TBG_CNTRL_0_SYNC_ONCE) ) return ret;
     
     return NoError;
    }
   
   Error readEDID(octet block[EDID::Len],unsigned number)
    {
     setHDMI();
     
     if( auto ret=setPage(0x12) ) return ret;
     
     if( auto ret=bitclear(TX4,TX4_PD_RAM) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=bitset(REG_INT_FLAGS_2,INT_FLAGS_2_EDID_BLK_RD) ) return ret;
     
     if( auto ret=setPage(0x09) ) return ret;
     
     if( auto ret=write(REG_DDC_ADDR,0xA0) ) return ret;
     
     if( auto ret=write(REG_DDC_OFFS,(number&1)?128:0) ) return ret;
     
     if( auto ret=write(REG_DDC_SEGM_ADDR,0x60) ) return ret;
     
     if( auto ret=write(REG_DDC_SEGM,number/2) ) return ret;
     
     if( auto ret=write(REG_EDID_CTRL,1) ) return ret;
     
     if( auto ret=write(REG_EDID_CTRL,0) ) return ret;
     
     if( auto ret=setPage(0) ) return ret;

     for(unsigned timeout=Timeout;;)
       {
        octet status;
        
        if( auto ret=read(REG_INT_FLAGS_2,status) ) return ret;
        
        if( status&INT_FLAGS_2_EDID_BLK_RD ) break;
       
        if( !--timeout ) 
          {
           if( auto ret=bitclear(REG_INT_FLAGS_2,INT_FLAGS_2_EDID_BLK_RD) ) return ret;
           
           if( auto ret=setPage(0x12) ) return ret;
          
           if( auto ret=bitset(TX4,TX4_PD_RAM) ) return ret;
          
           return Error_EDIDTimeout;
          }
       }
     
     if( auto ret=setPage(0x09) ) return ret;
     
     //if( auto ret=read(REG_EDID_DATA_0,block,EDID::Len) ) return ret;
     {
      for(ulen i=0; i<EDID::Len ;i++) 
        if( auto ret=read(octet(REG_EDID_DATA_0+i),block[i]) ) return ret;
     }
     
     if( auto ret=setPage(0) ) return ret;
     
     if( auto ret=bitclear(REG_INT_FLAGS_2,INT_FLAGS_2_EDID_BLK_RD) ) return ret;
     
     if( auto ret=setPage(0x12) ) return ret;
     
     if( auto ret=bitset(TX4,TX4_PD_RAM) ) return ret;
     
     return NoError;
    }
 };

} // namespace HDMI

//- Font ---------------------------------------------------------------------------------

namespace Font {

/* consts */

const ulen DY = 18 ;
const ulen DX = 10 ;

/* classes */

struct Glyph;

/* struct Glyph */

struct Glyph
 {
  static const bool Table[];
  static const bool NoCharTable[];
  
  const bool *pixel; // DX*DY
  
  explicit Glyph(char ch=' ')
   {
    unsigned index=(unsigned char)ch;
    
    if( index>=32 && index<128 )
      pixel=Table+(index-32)*DX*DY;
    else
      pixel=NoCharTable;
   }
  
  bool operator () (ulen x,ulen y) const { return pixel[x+y*DX]; }
 };

const bool Glyph::Table[]=
 {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
  0, 1, 0, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 1, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 1, 0, 0,
  0, 0, 0, 1, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 0, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 1, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 1, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 1, 1,
  0, 1, 1, 0, 0, 0, 0, 0, 1, 1,
  0, 1, 1, 0, 0, 1, 1, 1, 1, 1,
  0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 1,
  0, 1, 1, 0, 0, 1, 1, 0, 1, 1,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 1, 1, 0, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 1, 1, 0, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 };

const bool Glyph::NoCharTable[]=
 {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 1, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 1, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 };

} // namespace Font

//- Video --------------------------------------------------------------------------------

namespace Video {

/* enum ColorName */

enum ColorName
 {
  Black     = 0x000000 ,
  Red       = 0xFF0000 ,
  Green     = 0x00FF00 ,
  Blue      = 0x0000FF ,
  Gray      = 0x808080 ,
  LightGray = 0xC0C0C0 ,
  White     = 0xFFFFFF
 };

/* classes */

struct Color;

struct FrameBuf;

struct CharPanel; 

/* struct Color */

struct Color
 {
  uint8 red;
  uint8 green;
  uint8 blue;
  
  Color() : red(0),green(0),blue(0) {}
  
  Color(ColorName cname) : red(cname>>16),green(cname>>8),blue(cname) {}
  
  Color(uint8 red_,uint8 green_,uint8 blue_) : red(red_),green(green_),blue(blue_) {}
  
  static uint16 Pack565(uint16 r,uint16 g,uint16 b) { return (r<<11)|(g<<5)|b; }
  
  uint16 pack565() const { return Pack565(red>>3,green>>2,blue>>3); }
 };

/* struct FrameBuf */

struct FrameBuf
 {
  uint16 *base;
  ulen dx;
  ulen dy;
  
  FrameBuf() : base(0),dx(0),dy(0) {}
  
  FrameBuf(uint16 *base_,ulen dx_,ulen dy_) : base(base_),dx(dx_),dy(dy_) {}
  
  void pixel(ulen x,ulen y,Color color)
   {
    base[x+y*dx]=color.pack565();
   }
  
  void hLine(ulen y,Color color)
   {
    for(ulen x=0; x<dx ;x++) pixel(x,y,color);
   }
  
  void vLine(ulen x,Color color)
   {
    for(ulen y=0; y<dy ;y++) pixel(x,y,color);
   }
  
  void erase(Color color)
   {
    for(ulen y=0; y<dy ;y++) hLine(y,color);
   }
 
  void glyph(ulen x,ulen y,Font::Glyph glyph,Color back,Color fore)
   {
    for(ulen fx=0; fx<Font::DX ;fx++)
      for(ulen fy=0; fy<Font::DY ;fy++)
        {
         Color col;
         
         if( glyph(fx,fy) ) col=fore; else col=back;
        
         pixel(x+fx,y+fy,col);
        }
   }
 };

/* struct CharPanel */

struct CharPanel
 {
  FrameBuf out;
  Color back;
  Color fore;
  Color line;
  ulen dx;
  ulen dy;
  
  CharPanel() : dx(0),dy(0) {}
  
  explicit CharPanel(FrameBuf out_,Color back_=Black,Color fore_=LightGray,Color line_=Gray) 
   : out(out_),
     back(back_),
     fore(fore_),
     line(line_)
   {
    dx=out.dx/Font::DX;
    dy=out.dy/Font::DY;
    
    out.erase(back);
   }
  
  void operator () (ulen x,ulen y,char ch)
   {
    out.glyph(x*Font::DX,y*Font::DY,Font::Glyph(ch),back,fore);
   }
  
  void eraseLine(ulen y)
   {
    y*=Font::DY;
    
    for(ulen fy=0; fy<Font::DY ;fy++) out.hLine(y+fy,back);
   }
  
  void eraseLineLine(ulen y)
   {
    y*=Font::DY;
    
    for(ulen fy=0; fy<Font::DY-1 ;fy++) out.hLine(y+fy,back);
    
    out.hLine(y+Font::DY-1,line);
   }
 };

/* Console functions */

InitExitObject<CharPanel> Display;
 
ulen DisplayX;
ulen DisplayY;

void ConsoleInit(FrameBuf out)
 {
  Display.init(CharPanel(out));
  
  DisplayX=0;
  DisplayY=0;
 }

void NewLine()
 {
  if( !Display ) return;
  
  bool flag=Dev::IntLock::Internal::Disable();
  
  DisplayX=0;
  
  if( ++DisplayY>=Display->dy )
    {
     DisplayY=0;
    }
  
  if( DisplayY+1<Display->dy )
    {
     Display->eraseLine(DisplayY);
     Display->eraseLineLine(DisplayY+1);
    }
  else
    {
     Display->eraseLine(DisplayY);
     Display->eraseLineLine(0);
    }
  
  if( flag ) Dev::IntLock::Internal::Enable();
 }

void ConsoleOut(char ch)
 {
  if( !Display ) return;
  
  bool flag=Dev::IntLock::Internal::Disable();
  
  switch( ch )
    {
     case '\r' : DisplayX=0; break;
     
     case '\n' : NewLine(); break;
     
     case '\b' : if( DisplayX>0 ) DisplayX--; break;
      
     default:
      {
       (*Display)(DisplayX,DisplayY,ch);
       
       if( ++DisplayX>=Display->dx ) NewLine();
      }
    }
  
  if( flag ) Dev::IntLock::Internal::Enable();
 }

void ConsoleOut(char ch,ulen len)
 {
  if( !Display ) return;
  
  for(; len ;len--) ConsoleOut(ch);
 }

void ConsoleOut(const char *ptr,ulen len)
 {
  if( !Display ) return;
  
  for(; len ;ptr++,len--) ConsoleOut(*ptr);
 }

} // namespace Video 

//- LCD ----------------------------------------------------------------------------------

namespace LCD {

/* instances */

const Address LCDBase = 0x4830E000 ;

/* registers */

const Address CTRL = 0x004 ;

   const Register LCD_Raster = Bit(0) ;
   const Register HWRestart  = Bit(1) ;
   constexpr BitField CLKDiv = BitField(15,8) ;
   
const Address RASTER_CTRL = 0x028 ;

   const Register LCD_Enable   = Bit(0) ;
   const Register LCF_TFT      = Bit(7) ;
   const Register STN565       = Bit(24) ;
   constexpr BitField PalMode  = BitField(21,20) ;
   
const Address RASTER_TIMING_0  = 0x02C ;

   constexpr BitField HBackLSB  = BitField(31,24) ; 
   constexpr BitField HFrontLSB = BitField(23,16) ; 
   constexpr BitField HSyncLSB  = BitField(15,10) ; 
   constexpr BitField HLenLSB   = BitField(9,4) ; 
   constexpr BitField HLenMSB   = BitField(3,3) ;

const Address RASTER_TIMING_1  = 0x030 ;

   constexpr BitField VBack   = BitField(31,24) ; 
   constexpr BitField VFront  = BitField(23,16) ; 
   constexpr BitField VSync   = BitField(15,10) ; 
   constexpr BitField VLenLSB = BitField(9,0) ; 

const Address RASTER_TIMING_2  = 0x034 ;

   const Register SyncControl    = Bit(25) ;
   const Register SyncOnFalling  = Bit(24) ;
   const Register OEActiveLow    = Bit(23) ;
   const Register DataOnFalling  = Bit(22) ;
   const Register HSyncActiveLow = Bit(21) ;
   const Register VSyncActiveLow = Bit(20) ;
   constexpr BitField HSyncMSB   = BitField(30,27) ; 
   constexpr BitField VLenMSB    = BitField(26,26) ; 
   constexpr BitField HBackMSB   = BitField(5,4) ; 
   constexpr BitField HFrontMSB  = BitField(1,0) ;

const Address RASTER_SUBPANEL  = 0x038 ;

const Address RASTER_SUBPANEL2 = 0x03C ;

const Address LCDDMA_CTRL = 0x40 ;

   const Register DualFB    = Bit(0) ;
   const Register BEReorder = Bit(1) ;
   const Register ByteSwap  = Bit(3) ;
   constexpr BitField BurstSize = BitField(6,4) ;
   constexpr BitField FIFOReady = BitField(10,8) ;
   constexpr BitField DMAPri    = BitField(18,6) ;

const Address LCDDMA_FB0_BASE = 0x044 ;

const Address LCDDMA_FB0_CEILING = 0x048 ;

const Address LCDDMA_FB1_BASE = 0x04C ;

const Address LCDDMA_FB1_CEILING = 0x050 ;

const Address SYSCONFIG = 0x054 ;

  constexpr BitField IdleMode    = BitField(3,2) ;
  constexpr BitField StandbyMode = BitField(5,4) ;

const Address IRQSTATUS_RAW   = 0x058 ;
const Address IRQSTATUS       = 0x05C ;
const Address IRQENABLE_SET   = 0x060 ;
const Address IRQENABLE_CLEAR = 0x064 ;

   const Register IRQ_EOF0      = Bit(8) ;
   const Register IRQ_Underflow = Bit(5) ;
   const Register IRQ_Done      = Bit(0) ;

const Address CLKC_ENABLE = 0x06C ;

   const Register DMA_Enable  = Bit(2) ;
   const Register LIDD_Enable = Bit(1) ;
   const Register Core_Enable = Bit(0) ;

const Address CLKC_RESET = 0x070 ;

   const Register Main_Reset = Bit(3) ;
   const Register DMA_Reset  = Bit(2) ;
   const Register LIDD_Reset = Bit(1) ;
   const Register Core_Reset = Bit(0) ;
   
/* classes */
   
class Instance;   

/* class Instance */

struct Geometry
 {
  Register hback;  // 1-1024
  Register hlen;   // 16-2048 multiple of 16
  Register hfront; // 1-1024
  Register hsync;  // 1-1024
  
  Register vback;  // 0-255
  Register vlen;   // 1-2048 
  Register vfront; // 0-255
  Register vsync;  // 1-64
  
  Geometry() {}
  
  Geometry(const EDID::Mode &mode)
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
 };

class Instance
 {
   Address address;
   
  private:
   
   RegOp reg(Address offset) { return Reg(address,offset); }
   
  public:
   
   explicit Instance(Address address_=LCDBase) : address(address_) {}
   
   // initialization
   
   void first_reset()
    {
     reg(CLKC_ENABLE).bitset(DMA_Enable|Core_Enable);
     
     reg(CLKC_RESET).bitset(DMA_Reset|Core_Reset);
     
     Delay(16);
     
     reg(CLKC_RESET).bitclear(DMA_Reset|Core_Reset);
    }

   Video::FrameBuf init(uint16 *fb,const Geometry &geom)
    {
     reg(SYSCONFIG)=IdleMode.insert(2)|StandbyMode.insert(2);
     
     reg(CTRL)=LCD_Raster|HWRestart|CLKDiv.insert(2);
     
     reg(LCDDMA_CTRL)=BurstSize.insert(2)|FIFOReady.insert(4)|DMAPri.insert(0);
     
     reg(LCDDMA_FB0_BASE)=(Register)fb;
     
     reg(LCDDMA_FB0_CEILING)=(Register)(fb+16+geom.hlen*geom.vlen);
     
     fb[0]=(4<<12);
     
     reg(RASTER_TIMING_0)=HBackLSB.insert(geom.hback-1)|
                          HFrontLSB.insert(geom.hfront-1)|
                          HSyncLSB.insert(geom.hsync-1)|
                          HLenLSB.insert((geom.hlen-16)>>4)|
                          HLenMSB.insert((geom.hlen-16)>>10);
     
     reg(RASTER_TIMING_1)=VBack.insert(geom.vback)|
                          VFront.insert(geom.vfront)|
                          VSync.insert(geom.vsync-1)|
                          VLenLSB.insert(geom.vlen-1);
     
     reg(RASTER_TIMING_2)=HSyncMSB.insert((geom.hsync-1)>>6)|
                          VLenMSB.insert((geom.vlen-1)>>10)|
                          HBackMSB.insert((geom.hback-1)>>8)|
                          HFrontMSB.insert((geom.hfront-1)>>8)|SyncControl; 
     
     reg(IRQSTATUS)=IRQ_EOF0|IRQ_Underflow;
     
     reg(RASTER_CTRL)=LCD_Enable|LCF_TFT|STN565|PalMode.insert(2);
     
     return Video::FrameBuf(fb+16,geom.hlen,geom.vlen);
    }
   
   Register getIRQ() { return reg(IRQSTATUS_RAW); }
   
   void clearIRQ(Register mask) { reg(IRQSTATUS)=mask; }
 };

} // namespace LCD

} // namespace Debug

using namespace Debug;

#include <__std_init.h>

void __std_debug_init(void)
 {
  // PRCM
  {
   PRCM::CM_WKUP_Instance clk;
   PRCM::CM_DPLL_Instance src;
   PRCM::CM_PER_Instance per;
   
   clk.initDISP(200);
   
   src.setLCDDISPClock();
   
   per.enableLCD();
   
   while( per.getLCDStatus()!=0 );
   
   if( !clk.testDISP() ) Stop(15);
  }
  
  // Connect LCD PADS
  {
   for(Address addr=0x8A0; addr<=0x8EC ;addr+=4) Reg(0x44E10000,addr)=Bit(3);
  }
  
  EDID::Mode mode;

  // Init HDMI
  {
   HDMI::Instance hdmi;
   
   hdmi.init_I2C();
   
   if( hdmi.init() ) Stop(15);
   
   octet buf[EDID::Len];
   
   if( hdmi.readEDID(buf,0) ) Stop(15);
   
   mode=EDID::Mode(buf);
   
   if( hdmi.setMode(HDMI::ModeDesc(mode,mode)) ) Stop(15);
   
   if( hdmi.enableVIP() ) Stop(15);
  }

  // Init LCD
  { 
   LCD::Instance lcd;
   
   lcd.first_reset();
   
   auto frame=lcd.init((uint16 *)0x80000000,mode);
   
   Video::ConsoleInit(frame);
  }
 }

void __std_debug(const char *zstr)
 {
  StrLen str(zstr);
  
  Video::NewLine();
  Video::ConsoleOut(str.ptr,str.len);
 }

void __std_debug2(const char *ptr,__std_len_t len)
 {
  Video::NewLine();
  Video::ConsoleOut(ptr,len);
 }

void __std_debug_console(const char *ptr,__std_len_t len)
 {
  Video::ConsoleOut(ptr,len);
 }

#include <CCore/inc/Print.h>

#include <CCore/inc/dev/AM3359.h>

void __std_debug_trap(unsigned LR,unsigned trap)
 {
  using namespace AM3359::CP15;
  
  char buf[TextBufLen];
  
  PrintBuf out(Range(buf));
  
  switch( trap )
    {
     case 1 : // Undefined
      {
       Printf(out,"Undefined PC = #9.hi;",LR-4);
      }
     break; 
    
     case 3 : // Prefetch
      {
       Printf(out,"Prefetch PC = #9.hi; #; #9.hi;",LR-4,GetInstructionFaultStatus(),GetInstructionFaultAddress());
      }
     break;
     
     case 4 : // Data
      {
       Printf(out,"Data PC = #9.hi; #; #9.hi;",LR-8,GetDataFaultStatus(),GetDataFaultAddress());
      }
     break;
     
     default:
      {
       Printf(out,"LR = #9.hi; trap = #;",LR,trap);
      }
    }
  
  __std_debug(out.closeZStr());
 }

