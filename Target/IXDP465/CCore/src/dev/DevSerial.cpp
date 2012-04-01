/* DevSerial.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/dev/DevSerial.h>

#include <CCore/inc/dev/DevInt.h>
#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/IXP465.UART.h>

#include <CCore/inc/Abort.h>

namespace CCore {
namespace Dev {

/* using */ 

using namespace IXP465;

/* functions */  

void SerialInit(SerialSelect select)
 {
  SerialControl ctrl(select);
  
  ctrl.init();
 }
 
void SerialPollOut(SerialSelect select,const char *ptr,ulen len)
 {
  SerialControl ctrl(select);
  
  ctrl.pollOut(ptr,len);
 }
 
void SerialPollOut(SerialSelect select,PtrLen<const char> str)
 {
  SerialControl ctrl(select);
  
  ctrl.pollOut(str);
 }
 
void SerialPollTxEmpty(SerialSelect select)
 {
  SerialControl ctrl(select);
  
  ctrl.pollTxEmpty();
 }
 
void SerialExit(SerialSelect select)
 {
  SerialControl ctrl(select);
  
  ctrl.exit();
 }
 
/* enum SerialEvent */ 

const char * GetTextDesc(SerialEvent ev)
 {
  static const char *const Table[]=
   {
    "Rx chars",         // Serial_Rx
    "Tx chars",         // Serial_Tx

    "FIFO overflow",    // Serial_RxOverflowFIFO
    "Rx overflow",      // Serial_RxOverflow
    "Rx parity error",  // Serial_RxParity
    "Rx frame error",   // Serial_RxFrame
    "Rx line break",    // Serial_RxBreak
    
    "Int",              // Serial_Int
    "CTS change",       // Serial_CTS
    
    ""
   };
 
  return Table[ev];
 }
 
/* class SerialControl */ 

void SerialControl::disable()
 {
  UART::Bar bar(select);

  bar.null_IntEnable()
     .setTo(bar);
 }
   
void SerialControl::enableFIFO()
 {
  UART::Bar bar(select);
  
  bar.null_FIFOControl()
     .setbit(UART::FIFOControl_Enable|UART::FIFOControl_ResetRxFIFO|UART::FIFOControl_ResetTxFIFO)
     .set_RxLevel(UART::FIFOControl_RxLevel_Level32)
     .setTo(bar);
 }
 
void SerialControl::disableFIFO()
 {
  UART::Bar bar(select);

  bar.null_FIFOControl()
     .setTo(bar);
 }
   
void SerialControl::setMode()
 {
  UART::Bar bar(select);

  UART::Type_LineControl lc;
   
  lc.set_Bits(UART::LineControl_Bits_Bit8)
    .set_ParityBits(UART::LineControl_ParityBits_Bit0)
    .set_StopBits(UART::LineControl_StopBits_Bit1);
     
  lc.setbit(UART::LineControl_DivAccess)
    .setTo(bar);
     
  uint16 div=UART::SpeedDiv_115200;
   
  bar.null_DivHi()
     .set_Div(uint8(div>>8))
     .setTo(bar);
      
  bar.null_DivLo()
     .set_Div(uint8(div))
     .setTo(bar);
  
  lc.clearbit(UART::LineControl_DivAccess)
    .setTo(bar);
 }
 
void SerialControl::enableModem()
 {
  UART::Bar bar(select);
  
  bar.null_ModemControl()
     .setbit(UART::ModemControl_RTS|UART::ModemControl_OUT2)
     .setTo(bar);
 }
 
void SerialControl::enable()
 {
  UART::Bar bar(select);
  
  bar.null_IntEnable()
     .setbit(UART::IntEnable_Unit)
     .setTo(bar);
 }
 
void SerialControl::enableInt()
 {
  UART::Bar bar(select);
  
  bar.null_IntEnable()
     .setbit(UART::IntEnable_Rx|UART::IntEnable_RxError|UART::IntEnable_RxTO|UART::IntEnable_ModemStatus|UART::IntEnable_Unit)
     .setTo(bar);
 }
 
void SerialControl::init()
 {
  disable();
  
  setMode();
  enableModem();
  disableFIFO();
  
  enable();
 }
 
void SerialControl::exit()
 {
  disable();
 }
   
void SerialControl::setupInt(Function<void (void)> handle_int)
 {
  disable();

  enableFIFO();
  
  SetupIntHandler( (select==Serial_0)?Int_UART0:Int_UART1 ,handle_int);
  
  enableInt();
 }
 
void SerialControl::cleanupInt()
 {
  disable();

  CleanupIntHandler( (select==Serial_0)?Int_UART0:Int_UART1 );
  
  disableFIFO();
  
  enable();
 }
 
void SerialControl::disableTxInt()
 {
  UART::Bar bar(select);
  
  bar.get_IntEnable()
     .clearbit(UART::IntEnable_Tx)
     .setTo(bar);
 }
 
void SerialControl::enableTxInt()
 {
  UART::Bar bar(select);
  
  bar.get_IntEnable()
     .setbit(UART::IntEnable_Tx)
     .setTo(bar);
 }
 
struct SerialControl::Status : UART::Type_LineStatus
 {
  static UART::Type_LineStatus Get(SerialControl &ctrl)
   {
    UART::Bar bar(ctrl.select);
  
    return bar.get_LineStatus();
   }
 
  explicit Status(SerialControl &ctrl) : UART::Type_LineStatus(Get(ctrl)) {}
 };
 
struct SerialControl::ModemStatus : UART::Type_ModemStatus
 {
  static UART::Type_ModemStatus Get(SerialControl &ctrl)
   {
    UART::Bar bar(ctrl.select);
    
    return bar.get_ModemStatus();
   }
  
  explicit ModemStatus(SerialControl &ctrl) : UART::Type_ModemStatus(Get(ctrl)) {}
 };

void SerialControl::pollTxEmpty()
 {
  while( Status(*this).maskbit(UART::LineStatus_TxEmpty)==0 );
 }
 
void SerialControl::pollTxReady()
 {
  while( Status(*this).maskbit(UART::LineStatus_TxReady)==0 );
 }
 
void SerialControl::put(uint8 ch)
 {
  UART::Bar bar(select);
  
  bar.null_Tx()
     .set_Byte(ch)
     .setTo(bar);
 }
 
uint8 SerialControl::get()
 {
  UART::Bar bar(select);
  
  return bar.get_Rx().get_Byte();
 } 
 
void SerialControl::pollOut(PtrLen<const char> str)
 {
  for(; +str ;++str)
    {
     char ch=*str;
     
     if( ch=='\n' ) 
       {
        pollOut('\r');
        pollOut('\n');
       }
     else
       {
        pollOut(ch);
       }  
    }
 }
 
/* class SerialWriter */ 

SerialWriter::SerialWriter()
 {
  eol=false;
 }
   
SerialWriter::~SerialWriter()
 {
  if( +packet ) packet.free();
  
  list.freeAll();
 }
   
auto SerialWriter::get_cur() -> GetResult
 {
  if( eol ) 
    {
     eol=false;
     
     return '\n';
    }
  
  if( +data ) 
    {
     char ret=*data;
     
     ++data;
     
     if( ret=='\n' )
       {
        eol=true;
        
        return '\r';
       }
     
     return ret;
    }
    
  return Nothing;  
 }
 
auto SerialWriter::get() -> GetResult
 {
  GetResult ret=get_cur();
  
  while( !ret.ok ) 
    {
     if( +packet )
       {
        data=Nothing;
        
        packet.free(); 
       }
       
     packet=list.get();
       
     if( +packet )
       {
        data=packet.getRange();
        
        ret=get_cur();
       }
     else
       {
        break;
       }  
    }
  
  return ret;
 }
 
void SerialWriter::write(NanoPacket<char> packet)
 {
  if( +packet ) list.put(packet);
 }
 
/* class Serial */ 

Sys::ConInputResult Serial::DefaultConInputFunction_int(char ch)
 {
  if( ch==3 ) // ^C 
    {
     Abort("--- ^C abort ---");
    }

  if( ch=='\r' || ch=='\n' ) return Sys::Con_EOL;
  
  return Sys::Con_Echo;
 }
 
void Serial::handle_error(SerialControl::Status status) 
 {
  if( status.maskbit(UART::LineStatus_RxOverflow) )
    {
     stat.count(Serial_RxOverflow);
    }
    
  if( status.maskbit(UART::LineStatus_RxParity) )  
    {
     stat.count(Serial_RxParity);
    }
    
  if( status.maskbit(UART::LineStatus_RxFrame) )  
    {
     stat.count(Serial_RxFrame);
    }
    
  if( status.maskbit(UART::LineStatus_RxBreak) )  
    {
     stat.count(Serial_RxBreak);
    }
 }
 
void Serial::handle_char(char ch)
 {
  switch( input_int(ch) )
    {
     case Sys::Con_Drop :
      {
       stat.count(Serial_RxOverflowFIFO);
      }
     break;
              
     case Sys::Con_Echo :
      {
       stat.count(Serial_Rx);
                
       ctrl.put(ch);
      }
     break;
              
     case Sys::Con_NoEcho :
      {
       stat.count(Serial_Rx);
      }
     break;
              
     case Sys::Con_EOL :
      {
       stat.count(Serial_Rx);
                
       ctrl.put('\r');
       ctrl.put('\n');
      }
     break;
    }
 }
 
void Serial::handle_input(SerialControl::Status status)
 {
  uint8 ch=ctrl.get();
      
  if( status.maskbit(UART::LineStatus_RxOverflow
                    |UART::LineStatus_RxParity
                    |UART::LineStatus_RxFrame
                    |UART::LineStatus_RxBreak) )
    {
     handle_error(status);
    }
  else
    {
     handle_char(ch);
    }
 }
 
bool Serial::handle_output()
 {
  if( !cts_flag )
    {
     ctrl.disableTxInt();
     
     return false;  
    }
  
  auto result=writer.get();
        
  if( !result.ok )
    {
     ctrl.disableTxInt();
     
     return false;  
    }
  else
    {
     stat.count(Serial_Tx);
           
     ctrl.put(result.ch);
     
     return true;
    }
 }
 
void Serial::handle_int()
 {
  stat.count(Serial_Int);
  
  SerialControl::ModemStatus mstatus(ctrl);
  
  if( mstatus.maskbit(UART::ModemStatus_DeltaCTS) ) 
    {
     checkCTS();
     
     stat.count(Serial_CTS);
    }
  
  for(ulen cnt=64; cnt ;cnt--)
    {
     SerialControl::Status status(ctrl);
      
     if( status.maskbit(UART::LineStatus_RxReady) )
       {
        handle_input(status);
       } 
     else if( status.maskbit(UART::LineStatus_TxReady) )  
       {
        if( !handle_output() ) break;
       }
     else
       {
        break;
       }
    }
 }

void Serial::checkCTS()
 {
  SerialControl::ModemStatus mstatus(ctrl);
  
  if( mstatus.maskbit(UART::ModemStatus_CTS) )
    {
     cts_flag=true;
     
     ctrl.enableTxInt();
    }
  else
    {
     cts_flag=false;
    }
 }

Serial::Serial(SerialSelect select)
 : ctrl(select),
   input_int(DefaultConInputFunction_int),
   packet_mode(false)
 {
  ctrl.init();
 }
   
Serial::~Serial()
 {
  if( disablePacket() ) complete();
  
  ctrl.pollTxEmpty();
  
  ctrl.exit();
 }
 
bool Serial::write(NanoPacket<char> packet)
 {
  IntLock lock;
  
  writer.write(packet);
  
  if( packet_mode ) 
    {
     ctrl.enableTxInt();
     
     return false;
    }
  else
    {
     return true;
    }  
 }
 
void Serial::enablePacket()
 {
  IntLock lock;
  
  if( packet_mode ) return;
  
  ctrl.setupInt(FunctionOf(this,&Serial::handle_int));
  
  packet_mode=true;
  
  checkCTS();
 }
   
bool Serial::disablePacket()
 {
  IntLock lock;
  
  if( !packet_mode ) return false;
  
  ctrl.pollTxEmpty();
  
  ctrl.cleanupInt();
  
  packet_mode=false;
  
  return true;
 }
 
void Serial::complete()
 {
  SerialWriter temp;
  
  {
   IntLock lock;
   
   Swap(temp,writer);
  }
 
  for(;;)
    {
     SerialWriter::GetResult result=temp.get();
        
     if( !result.ok )
       {
        return;  
       }
     else
       {
        ctrl.pollOut(result.ch); // mt unstable
        
        IntLock lock;
        
        stat.count(Serial_Tx);
       }
    }
 }
 
void Serial::attachConInput(Sys::ConInputFunction input_int_)
 {
  IntLock lock;
  
  input_int=input_int_;
 }
   
void Serial::detachConInput()
 {
  IntLock lock;
  
  input_int=DefaultConInputFunction_int;
 }
 
void Serial::getStat(SerialCounters &ret)
 {
  IntLock lock;
  
  ret=stat;
 }
 
} // namespace Dev
} // namespace CCore
 


