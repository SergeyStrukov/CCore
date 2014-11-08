/* DevI2C.cpp */ 
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
 
#include <CCore/inc/dev/DevI2C.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/dev/AM3359.I2C.h>
#include <CCore/inc/dev/AM3359.PRCM.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>

namespace CCore {
namespace Dev {

/* class I2C */

using namespace AM3359::I2C; 

const uint32 I2C::DevInstanceTable[I2C_InstanceCount]=
 {
  AM3359::I2C::I2C_0,
  AM3359::I2C::I2C_1,
  AM3359::I2C::I2C_2
 };

const IntSource I2C::IntTable[I2C_InstanceCount]=
 {
  Int_I2C0INT,
  Int_I2C1INT,
  Int_I2C2INT
 };

void I2C::cancel(State state_)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.ones_IRQStatus().set(bar.to_IRQEnableClear());
  
  state=state_;
 
  bar.get_Config().clearbit(Config_Enable|Config_Start|Config_Stop|Config_TXMode|Config_Master).setTo(bar);
 
  bar.null_Counter().set_Count(0).setTo(bar);
  
  bar.get_Config().setbit(Config_Enable).setTo(bar);
 }

void I2C::pumpRX(ulen count)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  if( count>rx_buf.len ) 
    {
     cancel(ErrorRXLen);
     
     sem.give_int();
     
     return;
    }
  
  for(; count ;count--,++rx_buf) *rx_buf=(uint8)bar.get_Data().get_Byte();
 }

void I2C::pumpTX(ulen count)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  if( count>tx_buf.len )
    {
     cancel(ErrorTXLen);
    
     sem.give_int();
    
     return;
    }
  
  for(; count ;count--,++tx_buf) bar.null_Data().set_Byte(*tx_buf).setTo(bar); 
 }

void I2C::handle_int()
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  auto status=bar.get_IRQStatus();
  
  if( status.maskbit(IRQStatus_BusFree) )
    {
     bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQEnableClear());
     
     switch( state )
       {
        case StartRX :
         {
          bar.get_Config().clearbit(Config_Start|Config_Stop|Config_TXMode|Config_Master)
                          .setbit(Config_Start|Config_Stop|Config_Master).setTo(bar);
          
          state=DoRX;
          
          bar.null_IRQStatus().setbit(IRQStatus_BusLost|IRQStatus_NACK|IRQStatus_RXReady|IRQStatus_RXReadyShort|IRQStatus_Complete).set(bar.to_IRQEnableSet());
         }
        break;
        
        case StartTX :
         {
          bar.get_Config().clearbit(Config_Start|Config_Stop|Config_TXMode|Config_Master)
                          .setbit(Config_Start|Config_Stop|Config_TXMode|Config_Master).setTo(bar);
          
          state=DoTX;
          
          bar.null_IRQStatus().setbit(IRQStatus_BusLost|IRQStatus_NACK|IRQStatus_TXReady|IRQStatus_TXReadyShort|IRQStatus_Complete).set(bar.to_IRQEnableSet());
         }
        break;
        
        case StartTXRX :
         {
          bar.get_Config().clearbit(Config_Start|Config_Stop|Config_TXMode|Config_Master)
                          .setbit(Config_Start|Config_TXMode|Config_Master).setTo(bar);
          
          state=DoTXRX;
          
          bar.null_IRQStatus().setbit(IRQStatus_BusLost|IRQStatus_NACK|IRQStatus_TXReady|IRQStatus_TXReadyShort|IRQStatus_Complete).set(bar.to_IRQEnableSet());
         }
        break; 
       }
    }
  else if( status.maskbit(IRQStatus_RXReady) )
    {
     pumpRX(threshold);
    }
  else if( status.maskbit(IRQStatus_TXReady) )
    {
     pumpTX(threshold);
    }
  else if( status.maskbit(IRQStatus_RXReadyShort) )
    {
     ulen count=bar.get_BufStatus().get_RXStat();
    
     pumpRX(count);
    }
  else if( status.maskbit(IRQStatus_TXReadyShort) )
    {
     ulen count=bar.get_BufStatus().get_TXStat();
    
     pumpTX(count);
    }
  else if( status.maskbit(IRQStatus_BusLost) )
    {
     cancel(ErrorBusLost);
     
     sem.give_int();
    }
  else if( status.maskbit(IRQStatus_NACK) )
    {
     cancel(ErrorNACK);
     
     sem.give_int();
    }
  else if( status.maskbit(IRQStatus_Complete) )
    {
     bar.ones_IRQStatus().set(bar.to_IRQEnableClear());
     
     if( state==DoTXRX )
       {
        bar.null_Counter().set_Count(rx_buf.len).setTo(bar);
        
        bar.get_Config().clearbit(Config_Start|Config_Stop|Config_TXMode|Config_Master)
                        .setbit(Config_Start|Config_Stop|Config_Master).setTo(bar);
       
        state=DoRX;
        
        bar.null_IRQStatus().setbit(IRQStatus_BusLost|IRQStatus_NACK|IRQStatus_RXReady|IRQStatus_RXReadyShort|IRQStatus_Complete).set(bar.to_IRQEnableSet());
       }
     else
       {
        state=Complete;
       
        sem.give_int();
       }
    }

  status.setTo(bar);
 }

I2C::I2C(I2CInstance instance)
 : InstanceLock<I2C,I2C_InstanceCount>("I2C",instance),
   dev_instance(DevInstanceTable[instance]),
   int_source(IntTable[instance])
 {
 }

I2C::~I2C()
 {
  CleanupIntHandler(int_source);
 }

 // init

void I2C::enable()
 {
  Mutex::Lock lock(ControlMutex);
  
  {
   using namespace AM3359::PRCM;
   
   switch( getInstanceIndex() )
     {
      case I2C_0 :
       {
        BarWKUP bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C0());
       
        while( bar.get_I2C0().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
      
      case I2C_1 :
       {
        BarPER bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C1());
       
        while( bar.get_I2C1().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
      
      case I2C_2 :
       {
        BarPER bar;
        
        bar.null_ClockControl().set_Mode(ClockControl_Mode_Enable).set(bar.to_I2C2());
       
        while( bar.get_I2C2().get_IdleStatus()!=ClockControl_IdleStatus_Running );
       }
      break;
     }
  } 
  
  {
   using namespace AM3359::CONTROL;
   
   switch( getInstanceIndex() )
     {
      case I2C_0 :
       {
        AM3359::CONTROL::Bar bar;
        
        bar.null_PadMux().setbit(PadMux_RXEn|PadMux_SlowSlew).set_MuxMode(0).set(bar.to_Conf_I2C0_SDA());
        bar.null_PadMux().setbit(PadMux_RXEn|PadMux_SlowSlew).set_MuxMode(0).set(bar.to_Conf_I2C0_SCL());
       }
      break;
      
      case I2C_1 :
       {
        // TODO
       }
      break;
      
      case I2C_2 :
       {
        // TODO
       }
      break;
     }
  }
 }

void I2C::reset()
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.get_SysConfig().setbit(SysConfig_SoftReset).setTo(bar);
  
  while( bar.get_SysConfig().maskbit(SysConfig_SoftReset) );
 }

void I2C::init(bool fast)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.null_Config().setTo(bar);
  
  bar.null_Prescale().set_Div(4-1).setTo(bar); // 48 MHz -> 12 MHz
  
  uint32 div;
  
  if( fast ) // 12 MHz clock
    {
     div=30; // -> 400 kHz 
    }
  else
    {
     div=120; // -> 100 kHz
    }
  
  bar.null_SCLLoTime().set_Time(div/2-7).setTo(bar);
  bar.null_SCLHiTime().set_Time(div/2-5).setTo(bar);
  
  uint32 fifo=bar.get_BufStatus().get_FIFODepth();
  
  threshold=(4u<<fifo);
       
  bar.null_BufControl().set_TXFIFOThreshold(threshold-1).set_RXFIFOThreshold(threshold-1).setTo(bar);
  
  bar.ones_IRQStatus().set(bar.to_IRQEnableClear());
  
  bar.null_Config().setbit(Config_Enable).setTo(bar);
  
  SetupIntHandler(int_source,function_handle_int(),15);
 }

 // methods

void I2C::setSlave7(uint8 address)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.get_Config().clearbit(Config_A10).setTo(bar);

  bar.null_SlaveAddress().set_Address(address&0x7F).setTo(bar);
 }

void I2C::setSlave10(uint16 address)
 {
  Bar bar((AM3359::I2C::Instance)dev_instance);

  bar.get_Config().setbit(Config_A10).setTo(bar);
  
  bar.null_SlaveAddress().set_Address(address&0x3FF).setTo(bar);
 }

bool I2C::tryRead(PtrLen<uint8> buf)
 {
  if( buf.len>0x10000 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryRead({...,#;}) : too long",buf.len);
    }
  
  if( buf.len==0 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryRead({...,#;}) : zero length",buf.len);
    }
  
  state=StartRX;
  rx_buf=buf;
  
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.null_Counter().set_Count(buf.len).setTo(bar);
  
  bar.ones_IRQStatus().setTo(bar);
  
  if( !bar.get_IRQStatusRaw().maskbit(IRQStatus_BusBusy) )
    {
     bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQStatusRaw());
    }
  
  bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQEnableSet());
  
  if( sem.take(timeout) ) return state==Complete;
    
  cancel(ErrorTimeout);
  
  return false;
 }

bool I2C::tryWrite(PtrLen<const uint8> buf)
 {
  if( buf.len>0x10000 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryWrite({...,#;}) : too long",buf.len);
    }
  
  if( buf.len==0 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryWrite({...,#;}) : zero length",buf.len);
    }
  
  state=StartTX;
  tx_buf=buf;
  
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.null_Counter().set_Count(buf.len).setTo(bar);
  
  bar.ones_IRQStatus().setTo(bar);
  
  if( !bar.get_IRQStatusRaw().maskbit(IRQStatus_BusBusy) )
    {
     bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQStatusRaw());
    }
  
  bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQEnableSet());
  
  if( sem.take(timeout) ) return state==Complete;
  
  cancel(ErrorTimeout);
  
  return false;
 }

bool I2C::tryExchange(PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf)
 {
  if( out_buf.len>0x10000 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryExchange(out_buf={...,#;},...) : too long",out_buf.len);
    }
  
  if( out_buf.len==0 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryExchange(out_buf={...,#;},...) : zero length",out_buf.len);
    }
  
  if( in_buf.len>0x10000 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryExchange(...,in_buf={...,#;}) : too long",in_buf.len);
    }
  
  if( in_buf.len==0 )
    {
     Printf(Exception,"CCore::Dev::I2C::tryExchange(...,in_buf={...,#;}) : zero length",in_buf.len);
    }
  
  state=StartTXRX;
  tx_buf=out_buf;
  rx_buf=in_buf;
  
  Bar bar((AM3359::I2C::Instance)dev_instance);
  
  bar.null_Counter().set_Count(out_buf.len).setTo(bar);
  
  bar.ones_IRQStatus().setTo(bar);
  
  if( !bar.get_IRQStatusRaw().maskbit(IRQStatus_BusBusy) )
    {
     bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQStatusRaw());
    }
  
  bar.null_IRQStatus().setbit(IRQStatus_BusFree).set(bar.to_IRQEnableSet());
  
  if( sem.take(timeout) ) return state==Complete;
  
  cancel(ErrorTimeout);
  
  return false;
 }

StrLen I2C::getStateDesc()
 {
  switch( state )
    {
     case ErrorRXLen   : return "RX length mismatch";
     case ErrorTXLen   : return "TX length mismatch";
     case ErrorBusLost : return "bus lost";
     case ErrorNACK    : return "NACK";
     case ErrorTimeout : return "timeout";
   
     default: return "???"; 
    }
 }

 // advanced

void I2C::read(PtrLen<uint8> buf)
 {
  if( !tryRead(buf) )
    {
     Printf(Exception,"CCore::Dev::I2C::read(...) : #;",getStateDesc());
    }
 }

void I2C::write(PtrLen<const uint8> buf)
 {
  if( !tryWrite(buf) )
    {
     Printf(Exception,"CCore::Dev::I2C::write(...) : #;",getStateDesc());
    }
 }

void I2C::exchange(PtrLen<const uint8> out_buf,PtrLen<uint8> in_buf)
 {
  if( !tryExchange(out_buf,in_buf) )
    {
     Printf(Exception,"CCore::Dev::I2C::exchange(...) : #;",getStateDesc());
    }
 }

} // namespace Dev
} // namespace CCore
 

