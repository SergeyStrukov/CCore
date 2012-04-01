/* PTPConProc.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef PTPServer_PTPConProc_h
#define PTPServer_PTPConProc_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Fifo.h>
#include <CCore/inc/CharProp.h>

#include <CCore/inc/net/PTPConBase.h>

#include "ProcBase.h"

namespace App {

/* using */ 

using Net::PTPCon::TriggerMask;

/* classes */ 

class PTPConWrite;

class PTPConRead;

class PTPConProc;

/* class PTPConWrite */ 

class PTPConWrite : NoCopy
 {
   static const ulen BufLen = 128 ; // power of 2
 
   uint32 next_number;
   uint32 write_ticks;
   
   struct Frame
    {
     DynArray<char> text;
     uint32 write_ticks;
     bool ok;
     
     Frame() : ok(false) {}
     
     bool set(StrLen text,uint32 write_ticks);
      
     bool tick();
     
     bool print();
    };
    
   Frame buf[BufLen]; 
   ulen ind;
   bool ok;
   
  private:
  
   static ulen Next(ulen ind) { return (ind+1)%BufLen; }
  
   static void Print(StrLen text);
   
   bool shift();
   
   void set(uint32 n,StrLen text);
   
  public:
  
   PTPConWrite();
   
   ~PTPConWrite();
   
   void open(uint32 write_timeout_msec);
   
   bool operator () (uint32 number,StrLen text);
   
   void tick();
   
   void close();
 };
 
/* class PTPConRead */ 

class PTPConRead : public Funchor_nocopy
 {
   Net::PTP::ServerDevice *ptp;

   uint32 read_ticks;
   
   uint32 number;
   LenType len;
   uint32 ticks;
   
   bool is_started;
   
   class Buf : NoCopy
    {
      FifoBuf<char,1000> fifo;
      ulen avail;
      TriggerMask trigger_mask;
      bool is_opened;
      
     private: 
      
      struct Output;
      
      void fill(PtrLen<uint8> data);
      
     public:
     
      Buf();
      
      ~Buf();
      
      void open(const TriggerMask &trigger_mask);
      
      bool put(char ch);
      
      bool pump(PacketList &complete_list,
                Outbound &outbound,
                Net::PTP::ServerDevice *ptp,
                uint32 number,
                LenType len,
                bool allow_empty);
      
      void close();
    };
    
   Mutex mutex;
      
   Outbound outbound;
   Buf buf; 
   
  private:
  
   void pump(PacketList &complete_list,bool allow_empty);
   
   void stop(PacketList &complete_list);
   
   void cancel(PacketHeader *packet);
   
   PacketFunction function_cancel() { return FunctionOf(this,&PTPConRead::cancel); }
   
  public:
  
   explicit PTPConRead(Net::PTP::ServerDevice *ptp);
   
   ~PTPConRead();
   
   void open(uint32 read_timeout_msec,const TriggerMask &trigger_mask);
   
   ErrorIdType start(Inbound &inbound,uint32 number,LenType len);
   
   void tick();
   
   void close();
   
   // main task
   
   bool put(char ch);
 };
 
/* class PTPConProc */ 

class PTPConProc : ProcBase
 {
   XPoint client;
   
   char name[Net::PTPCon::MaxNameLen];
   ulen name_len;
   
   Net::PTPCon::ConId con_id;
   
   bool is_opened;
   bool write_ok;
   bool exit_on_close;
   
   PTPConWrite writer;
   PTPConRead reader;
   
   Mutex mutex;
   
   const char *ins_text;
 
  private:
  
   void setInsText(const char *text);
  
   StrLen getName() const { return StrLen(name,name_len); }
   
   void do_close();
  
   ErrorIdType open(XPoint client,
                    uint32 write_timeout_msec,
                    uint32 read_timeout_msec,
                    const TriggerMask &trigger_mask,
                    StrLen name);
                    
   ErrorIdType read(Inbound &inbound,const Net::PTPCon::ConId &con_id,uint32 number,LenType len);                
                    
   ErrorIdType write(const Net::PTPCon::ConId &con_id,uint32 number,StrLen text);                
  
   ErrorIdType close(const Net::PTPCon::ConId &con_id);
  
  private:
  
   void function_Open(Inbound &inbound);
   
   void function_Read(Inbound &inbound);
   
   void function_Write(Inbound &inbound);
   
   void function_Close(Inbound &inbound);
  
  public:
  
   PTPConProc(ServerProcBase *base,bool exit_on_close);
   
   ~PTPConProc();
   
   void inbound(Inbound &inbound);
   
   void tick();
   
   void session(XPoint point);
   
   bool exist(FunctionIdType function_id);
   
   // main task
   
   bool put(char ch) { return reader.put(ch); }
   
   const char * ins();
 };
 
} // namespace App
 
#endif

