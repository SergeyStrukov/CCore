/* DevSerial.h */ 
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

#ifndef CCore_inc_dev_DevSerial_h
#define CCore_inc_dev_DevSerial_h

#include <CCore/inc/Counters.h>

#include <CCore/inc/sys/SysCon.h>

namespace CCore {
namespace Dev {

/* consts */ 

enum SerialSelect
 {
  Serial_0,
  Serial_1
 };
 
/* functions : NOT LOCKED */ 

void SerialInit(SerialSelect select); 

void SerialPollOut(SerialSelect select,const char *ptr,ulen len); 

void SerialPollOut(SerialSelect select,PtrLen<const char> str); 

void SerialPollTxEmpty(SerialSelect select);

void SerialExit(SerialSelect select);
 
/* classes */ 

//enum SerialEvent;

class SerialControl;

class SerialWriter;

class Serial;

/* enum SerialEvent */ 

enum SerialEvent
 {
  Serial_Rx,
  Serial_Tx,

  Serial_RxOverflowFIFO,
  Serial_RxOverflow,
  Serial_RxParity,
  Serial_RxFrame,
  Serial_RxBreak,
  
  Serial_Int,
  Serial_CTS,
  
  SerialEventLim
 };
 
const char * GetTextDesc(SerialEvent ev); 

/* types */ 
 
typedef Counters<SerialEvent,SerialEventLim> SerialCounters;

/* class SerialControl : NOT LOCKED */ 

class SerialControl : NoCopy
 {
   SerialSelect select;
   
  private: 
 
   void disable();
   
   void enableFIFO();
   void disableFIFO();
   
   void setMode(); // 115200 8n1
   void enableModem();
   
   void enable();
   void enableInt();
   
  public:
  
   explicit SerialControl(SerialSelect select_) : select(select_) {}
   
   void init();
   void exit();
   
   void setupInt(Function<void (void)> handle_int);
   void cleanupInt();

   void disableTxInt();
   void enableTxInt();
   
   struct Status;
   struct ModemStatus;
   
   void pollTxEmpty();
   void pollTxReady();

   void put(uint8 ch);
   uint8 get();
   
   void pollOut(uint8 ch) { pollTxReady(); put(ch); }
    
   void pollOut(PtrLen<const char> str);
    
   void pollOut(const char *ptr,ulen len) { pollOut(Range(ptr,len)); }
 };
 
/* class SerialWriter */ 

class SerialWriter : NoCopy
 {
  public:
  
   struct GetResult
    {
     bool ok;
     char ch;
        
     GetResult(NothingType) : ok(false),ch(0) {}
        
     GetResult(char ch_) : ok(true),ch(ch_) {}
    };
   
  private:
  
   NanoPacketList<char> list;
   NanoPacket<char> packet;
   PtrLen<char> data;
   bool eol;
      
  private:
     
   GetResult get_cur();
   
  public:
  
   SerialWriter(); 
   
   ~SerialWriter(); 
      
   GetResult get();
   
   void write(NanoPacket<char> packet); // IntLocked
   
   void objSwap(SerialWriter &obj)
    {
     Swap(list,obj.list);
     Swap(packet,obj.packet);
     Swap(data,obj.data);
     Swap(eol,obj.eol);
    }
 };
    
/* class Serial */ 

class Serial : public Funchor_nocopy
 {
   SerialControl ctrl;
   SerialCounters stat;
   Sys::ConInputFunction input_int;
   bool packet_mode;
   
   SerialWriter writer;
   bool cts_flag;
   
  private:
  
   static Sys::ConInputResult DefaultConInputFunction_int(char ch);
   
   void handle_error(SerialControl::Status status);
   void handle_char(char ch);
   void handle_input(SerialControl::Status status);
   bool handle_output();
  
   void handle_int();
   
   void checkCTS();
      
  public:
  
   explicit Serial(SerialSelect select);
   
   ~Serial();
   
   bool write(NanoPacket<char> packet); 
   
   void enablePacket();
   
   bool disablePacket();
   
   void complete();
   
   void attachConInput(Sys::ConInputFunction input_int);
   
   void detachConInput();
   
   void getStat(SerialCounters &ret);
 };
 
} // namespace Dev
} // namespace CCore
 
#endif

