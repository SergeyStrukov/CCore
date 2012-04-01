/* PrintPTPCon.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_print_PrintPTPCon_h
#define CCore_inc_print_PrintPTPCon_h
 
#include <CCore/inc/net/PTPConDevice.h>

#include <CCore/inc/Fifo.h>

namespace CCore {

/* classes */ 

class PTPConOpenClose;

class ReadPTPCon;

class PrintPTPCon;

/* class PTPConOpenClose */ 

class PTPConOpenClose : NoCopy
 {
   ObjHook hook;
   
   Net::PTPCon::ClientDevice *con;
   
   Net::PTPCon::ClientDevice::OpenClose open_close;
   
   PacketFormat format;
   
  public: 
   
   // constructors
  
   PTPConOpenClose(StrLen con_dev_name,StrLen name,const Net::PTPCon::Cfg &cfg=DefaultValue());
   
   ~PTPConOpenClose();
   
   // read
   
   typedef Net::PTPCon::ClientDevice::InputProc InputProc;
  
   void start_read(InputProc *proc) { con->start_read(proc); }
   
   void stop_read() { con->stop_read(); }
   
   // write
   
   PacketFormat getWriteFormat() const { return format; }
   
   void write(Packet<uint8> packet) { con->write(packet); }
 };
 
/* class ReadPTPCon */ 

class ReadPTPCon : NoCopy , PTPConOpenClose::InputProc
 {
   static const ulen FifoLen = 128 ;
 
   PTPConOpenClose &con_openclose;
   
   Mutex mutex;
   Sem sem;
   PacketSet<uint8> pset;
   MSec timeout;
   
   FifoBuf<char,FifoLen> fifo;
   
  private: 
 
   virtual void input(PacketBuf &pbuf,PtrLen<const uint8> str);
   
   virtual void stop();
   
   bool do_get(char &ret);
   
  public:
   
   // constructors
   
   explicit ReadPTPCon(PTPConOpenClose &con_openclose,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);
   
   ~ReadPTPCon();
   
   // get
  
   char get();
   
   bool get(MSec timeout,char &ret);
   
   bool get(TimeScope time_scope,char &ret);
   
   // put, ignore errors
   
   void put(char ch) { put(&ch,1); }
   
   void put(const char *str,ulen len);
   
   void put(StrLen str) { put(str.ptr,str.len); }
 };
 
/* class PrintPTPCon */ 

class PrintPTPCon : public PrintBase
 {
   ObjHook hook;
   
   Net::PTPCon::ClientDevice *con;
   
   PacketFormat format;
   MSec timeout;
   bool enable_exceptions;
   
   PacketSet<uint8> pset;
   
   Packet<uint8> packet;
   
  private: 
 
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len);
   
  public:
  
   explicit PrintPTPCon(StrLen con_dev_name,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets); 
   
   ~PrintPTPCon();
   
   void enableExceptions() { enable_exceptions=true; }
   
   void flush_and_wait();
 };
 
} // namespace CCore
 
#endif
 

