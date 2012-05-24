/* Target.h */
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

#ifndef ARMGo_inc_Target_h
#define ARMGo_inc_Target_h

#include <inc/ArmBase.h>

#include <CCore/inc/FIFO.h>
#include <CCore/inc/Print.h>

namespace App {

/* using */

using namespace ARMCore;

using ARMCore::Bits;

/* enum IntSource */

enum IntSource
 {
  IntUART0   = 15,
  IntUART1   = 13,
  
  IntTimer0  =  5,
  IntTimer1  = 11,
  IntTimerTS = 14,
  IntTimerWD = 16
 };

/* classes */

class UARTDev; 

class INTDev;

class GPIODev;

class OSTDev;

class Target;

/* class UARTDev */

class UARTDev : NoCopy
 {
   INTDev &devINT;
   Word mask;
   
   //Word rx;         //  0  RO
   //Word tx;         //  0  WO
   Word intEnable;    //  4
   
   Word divLo;        //  0
   Word divHi;        //  4
   
   //Word status;     //  8  RO
   Word fifoControl;  //  8  WO
   
   Word lineControl;  // 12
   Word modemControl; // 16
   Word lineStatus;   // 20  RO
   Word modemStatus;  // 24  RO
   Word scratch;      // 28
   
  private:
   
   class TxBuf : NoCopy
    {
      Byte data;
      bool has_data;
      
     public:
      
      TxBuf() 
       {
        data=0;
        has_data=false;
       }
      
      bool isEmpty() const { return !has_data; }
      
      bool isFull() const { return has_data; }
      
      bool put(Byte val)
       {
        if( has_data ) return false;
        
        data=val;
        has_data=true;
        
        return true;
       }
      
      bool get(Byte &ret)
       {
        if( !has_data ) return false;
        
        ret=data;
        has_data=false;
        
        return true;
       }
    };
   
   FifoBuf<Byte,64> tx_fifo;
   TxBuf tx_buf;
   
   class Tick : NoCopy
    {
      uint32 cnt;
      uint32 div;
      
     public:
      
      Tick() 
       {
        cnt=0;
        div=60000;
       }
      
      bool tick()
       {
        if( cnt )
          {
           cnt--;
           
           return false;
          }
        else
          {
           cnt=div;
           
           return true;
          }
       }
    };

   Tick tick;
   
   class PrintBuf : NoCopy
    {
      static const ulen Len = 128 ;
     
      char buf[Len];
      ulen len;
     
     public:
     
      PrintBuf() { len=0; }
      
      ~PrintBuf() { flush(); }
      
      void put(Byte ch)
       {
        if( len>=Len ) flush();
        
        buf[len++]=ch;
       }
      
      void flush()
       {
        if( len )
          {
           PrintCon::Print(buf,len);
          
           len=0;
          }
       }
    };
   
   PrintBuf print_buf;
   
  private: 
  
   Word divBit() const { return lineControl&Bit(7); }
   
   Word fifoBit() const { return fifoControl&Bit(0); }
   
   Word txBit() const { return lineStatus&Bit(5); }
   
   Byte getRx();
   
   void putTx(Byte ch);
   
   void cfgFIFO(Word value);
   
   void cfgIntEnable(Word value);
   
   Word getStatus();
   
   void syncInt();
   
   void setTxBits(bool full,bool empty);
   
   void syncTxFIFO();
   
   void syncTxBuf();
   
   bool getTx(Byte &ret);
   
  public: 
  
   UARTDev(INTDev &devINT,unsigned num);
   
   ~UARTDev();
   
   // device
   
   void reset();
   
   void step();
   
   MemUnit getD(Word address); 
   
   NegMemTag putD(Word address,Word value);
   
   // flush
   
   void flush() { print_buf.flush(); }
 };

/* class INTDev */

class INTDev : NoCopy
 {
   Word status;             //  0  RO
   Word enable;             //  4
   Word select;             //  8
   //Word statusIRQ;        // 12  RO
   //Word statusFIQ;        // 16  RO
   
   Word priority;           // 20
   
   //Word priorityIRQHi;    // 24  RO
   //Word priorityFIQHi;    // 28  RO
   
   Word status2;            // 32  RO
   Word enable2;            // 36 
   Word select2;            // 40
   //Word statusIRQ2;       // 44  RO
   //Word statusFIQ2;       // 48  RO
   
   Word hi_priority_enable; // 52
   
  private:
   
   static unsigned GetHi(Word set);
   
   unsigned getHi(Word set,Word set2);
   
   Word getIRQHi();
   
   Word getFIQHi();
   
  public: 
   
   INTDev();
   
   ~INTDev();
   
   // device
   
   void reset();
   
   void step() {}
   
   MemUnit getD(Word address); 
   
   NegMemTag putD(Word address,Word value);
   
   // int output
   
   bool getIRQ() { return (status&enable&~select)|(status2&enable2&~select2); }
   
   bool getFIQ() { return (status&enable& select)|(status2&enable2& select2); }
   
   // int status
   
   void setInt(Word mask) { BitSet(status,mask); }
   
   void clearInt(Word mask) { BitClear(status,mask); }
   
   void setInt(bool on,Word mask) { if( on ) setInt(mask); else clearInt(mask); }
   
   void setInt2(Word mask) { BitSet(status2,mask); }
   
   void clearInt2(Word mask) { BitClear(status2,mask); }
   
   void setInt2(bool on,Word mask) { if( on ) setInt2(mask); else clearInt2(mask); }
 };

/* class GPIODev */

class GPIODev : NoCopy
 {
   INTDev &devINT;
  
   Word out;         //  0
   Word outDisable;  //  4
   Word inp;         //  8  RO
   Word intStatus;   // 12  RW1C
   
   Word intType1;    // 16
   Word intType2;    // 20
   Word clkType;     // 24
  
  public: 
  
   explicit GPIODev(INTDev &devINT);
   
   ~GPIODev();
   
   // device
   
   void reset();
   
   void step() {}
   
   MemUnit getD(Word address); 
   
   NegMemTag putD(Word address,Word value); 
 };

/* class OSTDev */

class OSTDev : NoCopy
 {
   INTDev &devINT;
   
   Word time_stamp; //  0
   
   Word time0;      //  4  RO
   Word reload0;    //  8
   
   Word time1;      // 12  RO
   Word reload1;    // 16
   
   Word watch_dog;  // 20
   Word wdControl;  // 24
   Word wdKey;      // 28
   
   Word status;     // 32  RW1C
   
   Word tsCmp;      // 36
   Word tsCfg;      // 40
   Word tsPrescale; // 44
   
   Word t0Cfg;      // 48
   Word t0Prescale; // 52
   
   Word t1Cfg;      // 56
   Word t1Prescale; // 60
  
   bool run_flag;
   
  private:
   
   class Tick : NoCopy
    {
      uint32 cnt;
      uint32 div;
      bool pause;
      
     public:
      
      Tick() { set(0,0,0); }
      
      void set(bool pauseBit,bool scaleBit,uint32 prescale)
       {
        pause = pauseBit && ( scaleBit || prescale ) ;
        
        div = (scaleBit?((prescale+1)*12):((prescale+1)*9))-1 ;
        
        cnt = 0 ;
       }
      
      bool tick()
       {
        if( pause ) return false; 
        
        if( cnt )
          {
           cnt--;
           
           return false;
          }
        else
          {
           cnt=div;
           
           return true;
          }
       }
    };
   
   Tick tick0;
   Tick tick1;
   Tick tickTS;
   Tick tickWD;
   
  private: 
   
   static const Word WDKey   = 0x482E ;
   
   static const Word BitT0   = Bit(0) ;
   static const Word BitT1   = Bit(1) ;
   static const Word BitTS   = Bit(2) ;
   static const Word BitWD   = Bit(3) ;
   static const Word BitWarm = Bit(4) ;
   
   void syncInt();
   
   void setTick0();
   void setTick1();
   void setTickTS();
   
  public:
  
   explicit OSTDev(INTDev &devINT);
   
   ~OSTDev();
   
   // device
   
   void reset();
   
   void step();
   
   MemUnit getD(Word address); 
   
   NegMemTag putD(Word address,Word value);
   
   // run/stop
   
   bool getRunFlag() const { return run_flag; }
   
   void stop() { run_flag=false; }
 };

/* class Target */

class Target : NoCopy
 {
   INTDev devINT;
   UARTDev devUART0;
   UARTDev devUART1;
   GPIODev devGPIO;
   OSTDev devOST;
   
  private:
   
   enum DevSpace
    {
     DevSpace_Void,
     
     DevSpace_UART0, // 0xC800 0xxx
     DevSpace_UART1, // 0xC800 1xxx
     DevSpace_INT,   // 0xC800 3xxx
     DevSpace_GPIO,  // 0xC800 4xxx
     DevSpace_OST    // 0xC800 5xxx
    };
   
   static DevSpace SelectSpace(Word address);
   
   static const Word Mask = Field(12) ; 
   
  public:
  
   Target();
   
   ~Target();
   
   ulen getMemLen() const { return 64_MByte; }
   
   void reset(); 
   
   void step() 
    { 
     devINT.step();
     devUART0.step();
     devUART1.step();
     devGPIO.step();
     devOST.step();
    }
   
   bool getRunFlag() 
    { 
     if( devOST.getRunFlag() ) return true;
     
     devUART0.flush();
     
     return false;
    }
   
   MemUnit getX(Word address) 
    { 
     if( address==StopAddress ) 
       {
        Printf(Con,"Stop address abort\n\n");
       
        devOST.stop();
       }
     
     return MemTag_Void; 
    }
   
   MemUnit getD(Word address); 
   
   MemUnit getH(Word) { return MemTag_Void; }
   
   MemUnit getB(Word) { return MemTag_Void; }
   
   NegMemTag putD(Word address,Word value); 
   
   NegMemTag putH(Word,Half) { return MemTag_Void; }
   
   NegMemTag putB(Word,Byte) { return MemTag_Void; }
   
   bool getIRQ() { return devINT.getIRQ(); }
   
   bool getFIQ() { return devINT.getFIQ(); }
 };

} // namespace App

#endif

