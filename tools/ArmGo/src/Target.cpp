/* Target.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Target.h>

namespace App {

/* class UARTDev */

Byte UARTDev::getRx()
 {
  return 0;
 }

void UARTDev::putTx(Byte ch)
 {
  if( fifoBit() )
    {
     tx_fifo.put(ch);
     
     syncTxFIFO();
    }
  else
    {
     tx_buf.put(ch);
     
     syncTxBuf();
    }
 }

void UARTDev::cfgFIFO(Word value)
 {
  fifoControl=value;
  
  if( value&Bit(2) ) tx_fifo.reset();
  
  if( fifoBit() ) syncTxFIFO(); else syncTxBuf();
 }

void UARTDev::cfgIntEnable(Word value)
 {
  intEnable=value;
  
  syncInt();
 }

Word UARTDev::getStatus()
 {
  Word ret=0;
  
  if( fifoBit() ) ret|=Bits(6,7);
  
  if( txBit() )
    ret|=2;
  else
    ret|=1;
  
  return ret;
 }

void UARTDev::syncInt()
 {
  devINT.setInt( (intEnable&Bit(1)) && txBit() ,mask);
 }

void UARTDev::setTxBits(bool full,bool empty)
 {
  if( full ) BitClear(lineStatus,Bit(5)); else BitSet(lineStatus,Bit(5));
  
  if( empty ) BitSet(lineStatus,Bit(6)); else BitClear(lineStatus,Bit(6));
 }

void UARTDev::syncTxFIFO()
 {
  setTxBits(tx_fifo.isFull(),tx_fifo.isEmpty());
  
  syncInt();
 }

void UARTDev::syncTxBuf()
 {
  setTxBits(tx_buf.isFull(),tx_buf.isEmpty());
  
  syncInt();
 }

bool UARTDev::getTx(Byte &ret)
 {
  if( fifoBit() )
    {
     bool ok=tx_fifo.get(ret);
     
     syncTxFIFO();
     
     return ok;
    }
  else
    {
     bool ok=tx_buf.get(ret);
     
     syncTxBuf();
     
     return ok;
    }
 }

UARTDev::UARTDev(INTDev &devINT_,unsigned num)
 : devINT(devINT_)
 {
  switch( num )
    {
     case 0 : mask=Bit(IntUART0); break; 
     case 1 : mask=Bit(IntUART1); break; 
    }
  
  reset();
 }
   
UARTDev::~UARTDev()
 {
 }
   
void UARTDev::reset()
 {
  intEnable=0;
  divLo=2;
  divHi=0;
  fifoControl=0;
  lineControl=0;
  modemControl=0;
  lineStatus=0x60;
  modemStatus=0xB0;
  scratch=0;
 }
   
void UARTDev::step()
 {
  if( tick.tick() )
    {
     Byte ch;
     
     if( getTx(ch) )
       {
        print_buf.put(ch);
       }
     else
       {
        print_buf.flush();
       }
    }
 }
   
MemUnit UARTDev::getD(Word address)
 {
  switch( address )
    {
     case  0 : if( divBit() ) return divLo; else return getRx();
     case  4 : if( divBit() ) return divHi; else return intEnable;
     
     case  8 : return getStatus();
     
     case 12 : return lineControl;
     case 16 : return modemControl;
     case 20 : return lineStatus;
     case 24 : return modemStatus;
     case 28 : return scratch;
    }
  
  return MemTag_Void; 
 }
   
NegMemTag UARTDev::putD(Word address,Word value)
 {
  switch( address )
    {
     case  0 : if( divBit() ) divLo=value&Field(8); else putTx(Byte(value));                    return MemTag_Ok;
     case  4 : if( divBit() ) divHi=value&Field(8); else cfgIntEnable(value&Bits(0,1,2,3,4,6)); return MemTag_Ok;
   
     case  8 : cfgFIFO(value&Bits(0,1,2,6,7));                                                  return MemTag_Ok;
     
     case 12 : lineControl=value&Field(8);                                                      return MemTag_Ok;
     case 16 : modemControl=value&Field(5);                                                     return MemTag_Ok;
     case 28 : scratch=value&Field(8);                                                          return MemTag_Ok;
    }
  
  return MemTag_Void; 
 }
   
/* class INTDev */

unsigned INTDev::GetHi(Word set)
 {
  static_assert( Word(-1)==Quick::ScanUInt(-1) ,"Type mismatch");
  
  return Quick::ScanLSBit(set);
 }

unsigned INTDev::getHi(Word set,Word set2)
 {
  if( Word s=set2&hi_priority_enable ) return 32+GetHi(s);
   
  if( set&Field(8) )
    {
     unsigned ret=8;
     unsigned pri=8;
     
     Word bit=1;
     Word reg=priority;
     
     for(unsigned i=0; i<8 ;i++,bit<<=1,reg>>=3)
       {
        if( set&bit )
          {
           unsigned p=reg&Field(3);
           
           if( p<pri )
             {
              ret=i;
              pri=p;
             }
          }
       }
     
     return ret;
    }
  
  if( set ) return GetHi(set);
  
  return 32+GetHi(set2);
 }

Word INTDev::getIRQHi()
 {
  Word set=status&enable&~select;
  Word set2=status2&enable2&~select2;
  
  if( set|set2 ) return (getHi(set,set2)+1)*4;
  
  return 0;
 }

Word INTDev::getFIQHi()
 {
  Word set=status&enable&select;
  Word set2=status2&enable2&select2;
  
  if( set|set2 ) return (getHi(set,set2)+1)*4;
  
  return 0;
 }

INTDev::INTDev()
 {
  reset();
 }
   
INTDev::~INTDev()
 {
 }
   
void INTDev::reset() 
 {
  status=0;
  enable=0;
  select=0;
  
  status2=0;
  enable2=0;
  select2=0;
  
  priority=0xFAC688;
  hi_priority_enable=0;
 }
   
MemUnit INTDev::getD(Word address) 
 { 
  switch( address )
    {
     case  0 : return status; 
     case  4 : return enable; 
     case  8 : return select;
     
     case 12 : return status&enable&~select; // statusIRQ
     case 16 : return status&enable& select; // statusFIQ
     
     case 20 : return priority;

     case 24 : return getIRQHi(); // priorityIRQHi
     case 28 : return getFIQHi(); // priorityFIQHi
     
     case 32 : return status2; 
     case 36 : return enable2;
     case 40 : return select2;
     
     case 44 : return status2&enable2&~select2; // statusIRQ2
     case 48 : return status2&enable2& select2; // statusFIQ2
     
     case 52 : return hi_priority_enable;
    }
  
  return MemTag_Void; 
 }
   
NegMemTag INTDev::putD(Word address,Word value) 
 {
  switch( address )
    {
     case  4 : enable=value;             return MemTag_Ok;
     case  8 : select=value;             return MemTag_Ok;
      
     case 20 : priority=value;           return MemTag_Ok;
      
     case 36 : enable2=value;            return MemTag_Ok;
     case 40 : select2=value;            return MemTag_Ok;
      
     case 52 : hi_priority_enable=value; return MemTag_Ok;
    }
  
  return MemTag_Void; 
 }
   
/* class GPIODev */

GPIODev::GPIODev(INTDev &devINT_)
 : devINT(devINT_)
 { 
  reset();
 }

GPIODev::~GPIODev() 
 {
 }

void GPIODev::reset() 
 {
  out=0;
  outDisable=0x7FFF;
  
  inp=0;
  intStatus=0;
  
  intType1=0;
  intType2=0;
  
  clkType=0x01100000;
 }

MemUnit GPIODev::getD(Word address) 
 {
  switch( address )
    {
     case  0 : return out;
     case  4 : return outDisable;
     case  8 : return Combine(outDisable,inp,out);
     case 12 : return intStatus;
      
     case 16 : return intType1;
     case 20 : return intType2;
     case 24 : return clkType;
    }
  
  return MemTag_Void; 
 }

NegMemTag GPIODev::putD(Word address,Word value) 
 { 
  switch( address )
    {
     case  0 : out=value&Field(16);        return MemTag_Ok;
     case  4 : outDisable=value&Field(16); return MemTag_Ok;
     
     case 12 : BitClear(intStatus,value);  return MemTag_Ok;
      
     case 16 : intType1=value;             return MemTag_Ok;
     case 20 : intType2=value&Field(24);   return MemTag_Ok;
     case 24 : clkType=value&Field(25);    return MemTag_Ok;
    }
  
  return MemTag_Void; 
 }

/* class OSTDev */

void OSTDev::syncInt()
 {
  devINT.setInt(status&BitT0,Bit(IntTimer0));
  devINT.setInt(status&BitT1,Bit(IntTimer1));
  devINT.setInt(status&BitTS,Bit(IntTimerTS));
  devINT.setInt(status&BitWD,Bit(IntTimerWD));
 }

void OSTDev::setTick0()
 {
  tick0.set(t0Cfg&Bit(3),t0Cfg&Bit(2),t0Prescale);
 }

void OSTDev::setTick1()
 {
  tick1.set(t1Cfg&Bit(3),t1Cfg&Bit(2),t1Prescale);
 }

void OSTDev::setTickTS()
 {
  tickTS.set(tsCfg&Bit(1),tsCfg&Bit(0),tsPrescale);
 }

OSTDev::OSTDev(INTDev &devINT_)
 : devINT(devINT_)
 {
  reset();
 }

OSTDev::~OSTDev()
 {
 }

void OSTDev::reset() 
 { 
  time_stamp=1;
  
  time0=0;     
  reload0=0;    
  
  time1=0;      
  reload1=0;    
  
  watch_dog=0xFFFFFFFF;  
  wdControl=0;  
  wdKey=0;      
  
  status=0;     
  
  tsCmp=0;      
  tsCfg=0;      
  tsPrescale=0; 
  
  t0Cfg=0;      
  t0Prescale=0; 
  
  t1Cfg=0;      
  t1Prescale=0; 
  
  setTick0();
  setTick1();
  setTickTS();
  
  run_flag=true; 
 }

void OSTDev::step() 
 {
  // watch-dog
  
  if( wdControl&Bit(2) )
    {
     if( tickWD.tick() )
       {
        if( watch_dog )
          {
           watch_dog--;
          }
        else
          {
           if( wdControl&Bit(0) )
             {
              stop();
             }
           else if( wdControl&Bit(1) )
             {
              status|=(BitWD|BitWarm);
              
              devINT.setInt(Bit(IntTimerWD));
             }
          }
       }
    }
  
  // time-stamp
  
  if( tickTS.tick() )
    {
     time_stamp++;
     
     if( tsCmp && tsCmp==time_stamp )
       {
        status|=BitTS;
       
        devINT.setInt(Bit(IntTimerTS));
       }
    }
  
  // time0
  
  if( reload0&Bit(0) )
    {
     if( tick0.tick() )
       {
        if( time0 )
          {
           time0--;
          }
        else
          {
           time0=Combine(Field(2),t0Cfg,reload0);
             
           if( reload0&Bit(1) ) BitClear(reload0,Bit(0));
           
           status|=BitT0;
           
           devINT.setInt(Bit(IntTimer0));
          }
       }
    }
  
  // time1
  
  if( reload1&Bit(0) )
    {
     if( tick1.tick() )
       {
        if( time1 )
          {
           time1--;
          }
        else
          {
           time1=Combine(Field(2),t1Cfg,reload1);
            
           if( reload1&Bit(1) ) BitClear(reload1,Bit(0));
          
           status|=BitT1;
          
           devINT.setInt(Bit(IntTimer1));
          }
       }
    }
 }

MemUnit OSTDev::getD(Word address) 
 { 
  switch( address )
    {
     case  0 : return time_stamp;
     case  4 : return time0;
     case  8 : return reload0;
     case 12 : return time1;
     case 16 : return reload1;
     case 20 : return watch_dog;
     case 24 : return wdControl;
     case 28 : return wdKey;
     case 32 : return status;
     case 36 : return tsCmp;
     case 40 : return tsCfg;
     case 44 : return tsPrescale;
     case 48 : return t0Cfg;
     case 52 : return t0Prescale; 
     case 56 : return t1Cfg;
     case 60 : return t1Prescale; 
    }
  
  return MemTag_Void; 
 }

NegMemTag OSTDev::putD(Word address,Word value) 
 { 
  switch( address )
    {
     case  0 : time_stamp=value;                            return MemTag_Ok;
     case  8 : reload0=value;                               return MemTag_Ok;
     case 16 : reload1=value;                               return MemTag_Ok;
     
     case 20 : if( wdKey==WDKey ) watch_dog=value;          return MemTag_Ok;
     case 24 : if( wdKey==WDKey ) wdControl=value&Field(3); return MemTag_Ok;
     case 28 : wdKey=value&Field(16);                       return MemTag_Ok;
      
     case 32 : BitClear(status,value); syncInt();           return MemTag_Ok;
      
     case 36 : tsCmp=value;                                 return MemTag_Ok;
     case 40 : tsCfg=value&Field(2);       setTickTS();     return MemTag_Ok;
     case 44 : tsPrescale=value&Field(16); setTickTS();     return MemTag_Ok;
     
     case 48 : t0Cfg=value&Field(4);       setTick0();      return MemTag_Ok;
     case 52 : t0Prescale=value&Field(16); setTick0();      return MemTag_Ok;
     
     case 56 : t1Cfg=value&Field(4);       setTick1();      return MemTag_Ok;
     case 60 : t1Prescale=value&Field(16); setTick1();      return MemTag_Ok;
    }
  
  return MemTag_Void; 
 }

/* class Target */

Target::Target()
 : devUART0(devINT,0),
   devUART1(devINT,1),
   devGPIO(devINT),
   devOST(devINT)
 {
 }

Target::~Target() 
 {
 }

void Target::reset() 
 { 
  devINT.reset();
  devUART0.reset();
  devUART1.reset();
  devGPIO.reset();
  devOST.reset();
 }

auto Target::SelectSpace(Word address) -> DevSpace
 {
  if( (address>>16)==0xC800 )
    {
     switch( (address>>12)&Field(4) )
       {
        case 0 : return DevSpace_UART0; 
        case 1 : return DevSpace_UART1;
        case 3 : return DevSpace_INT;
        case 4 : return DevSpace_GPIO;
        case 5 : return DevSpace_OST;
       }
    }
  
  return DevSpace_Void;
 }

MemUnit Target::getD(Word address) 
 {
  switch( SelectSpace(address) )
    {
     case DevSpace_UART0 : return devUART0.getD(address&Mask);
     case DevSpace_UART1 : return devUART1.getD(address&Mask);
     case DevSpace_INT   : return devINT.getD(address&Mask);
     case DevSpace_GPIO  : return devGPIO.getD(address&Mask);
     case DevSpace_OST   : return devOST.getD(address&Mask);
    }
  
  return MemTag_Void; 
 }

NegMemTag Target::putD(Word address,Word value) 
 { 
  switch( SelectSpace(address) )
    {
     case DevSpace_UART0 : return devUART0.putD(address&Mask,value);
     case DevSpace_UART1 : return devUART1.putD(address&Mask,value);
     case DevSpace_INT   : return devINT.putD(address&Mask,value);
     case DevSpace_GPIO  : return devGPIO.putD(address&Mask,value);
     case DevSpace_OST   : return devOST.putD(address&Mask,value);
    }
  
  return MemTag_Void; 
 }

} // namespace App
