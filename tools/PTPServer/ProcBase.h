/* ProcBase.h */ 
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

#ifndef PTPServer_ProcBase_h
#define PTPServer_ProcBase_h

#include <CCore/inc/Print.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintTime.h>

#include <CCore/inc/net/PTPServerDevice.h>

#include "ErrorIds.h"

namespace App {

/* using */ 

using namespace CCore;

using Net::XPoint;

using Net::PTP::ServiceIdType;
using Net::PTP::FunctionIdType;
using Net::PTP::ServiceFunction;
using Net::PTP::LenType;
using Net::PTP::BoolType;
using Net::PTP::FlagType;

using Net::PTP::TransIndex;

/* functions */ 

inline uint32 ToTicks(uint32 time_msec) 
 {
  Replace_min(time_msec,(uint32(-1)-999)/Net::InboundTicksPerSec);
  
  return (time_msec*Net::InboundTicksPerSec+999)/1000; 
 }
 
/* classes */ 

class Log;

template <class T> struct Tailed;

struct Inbound;

struct Outbound;

class ServerProcBase;

class ProcBase;

/* class Log */ 

class Log : NoCopy
 {
   PrintFile out;
   SecTimer timer;
   
  public:
  
   Log();
   
   ~Log();
   
   void flush() { out.flush(); }
   
   template <class ... TT>
   void operator () (const char *format,const TT & ... tt)
    {
     Printf(out,"\n[#;] ",PrintTime(timer.get()));
    
     Printf(out,format,tt...);
     
     Putch(out,'\n');
    }
 };
 
/* struct Tailed<T> */ 

template <class T> 
struct Tailed
 {
  T base;
  PtrLen<const uint8> tail;
  
  Tailed() : base(),tail() {}
  
  template <class ... SS>
  Tailed(const uint8 *ptr,SS && ... ss) : base(ss...),tail(ptr,base.len) {}
  
  // save/load object
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev(base);
    
    dev.put(tail);
   }
   
  template <class Dev>
  void load(Dev &dev)
   {
    dev(base);
    
    if( base.len>base.MaxLen )
      dev.fail();
    else
      tail=dev.getRange(base.len);
   }
 };
 
/* struct Inbound */ 

struct Inbound : NoCopy
 {
  XPoint point;
  TransIndex idx;
  
  ServiceFunction serv_func;
  ErrorIdType error_id;
  RangeGetDev dev;
  
  Packet<uint8> packet;
  
  Inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info);
  
  ErrorIdType operator ! () const { return error_id; }
  
  void complete()
   {
    if( +packet ) packet.complete();
   }
  
  template <class T>
  bool getInput(T &t)
   {
    dev(t);
    
    if( !dev.finish() ) 
      {
       error_id=Error_BadInput;
       
       return false;
      }
      
    return true;  
   }
  
  void send_cancel(Net::PTP::ServerDevice *ptp);
  
  void send_error(Net::PTP::ServerDevice *ptp);
  
  template <class T>
  void send_info(const T &t,Net::PTP::ServerDevice *ptp)
   {
    Net::PTP::Result result(serv_func,NoError);
  
    auto len=SaveLen(result,t);
     
    if( packet.checkDataLen(len) )
      {
       PtrLen<uint8> info=packet.setDataLen(len);
        
       BufPutDev dev(info.ptr);
        
       dev(result,t);
        
       ptp->send_info(idx,Replace_null(packet),Range_const(info));
      }
    else
      {
       send_cancel(ptp);
      }
   }

  template <class T>
  PtrLen<uint8> send_buf(ulen max_len)
   {
    ulen off=SaveLenCounter<Net::PTP::Result,T>::SaveLoadLen;
    
    if( off>=packet.getMaxDataLen() ) return Nothing;
    
    Replace_min<ulen>(max_len,packet.getMaxDataLen()-off);
    Replace_min<ulen>(max_len,T::MaxLen);
    
    return Range(packet.getData()+off,max_len);
   }
   
  template <class T> 
  void send_info_tailed(const T &t,Net::PTP::ServerDevice *ptp)
   {
    Net::PTP::Result result(serv_func,NoError);
  
    auto len=SaveLen(result,t)+t.len;
     
    if( packet.checkDataLen(len) )
      {
       PtrLen<uint8> info=packet.setDataLen(len);
        
       BufPutDev dev(info.ptr);
        
       dev(result,t);
        
       ptp->send_info(idx,Replace_null(packet),Range_const(info));
      }
    else
      {
       send_cancel(ptp);
      }
   }
 };
 
/* struct Outbound */ 
 
struct Outbound : NoCopy
 {
  TransIndex idx;
  ServiceFunction serv_func;
  
  Packet<uint8,bool> packet;
  
  bool init(Inbound &inbound,PacketFunction cancel_function);
  
  void send_cancel(Net::PTP::ServerDevice *ptp); 
  
  struct CancelExt
   {
    Net::PTP::ServerDevice *ptp;
    TransIndex idx;
    
    CancelExt(Net::PTP::ServerDevice *ptp_,TransIndex idx_) : ptp(ptp_),idx(idx_) {}
     
    void operator () () { ptp->send_cancel(idx); } 
      
    static void Complete(PacketHeader *packet); 
   };
    
  void send_cancel(PacketList &complete_list,Net::PTP::ServerDevice *ptp);
  
  struct InfoExt
   {
    Net::PTP::ServerDevice *ptp;
    TransIndex idx;
    PtrLen<const uint8> server_info;
     
    InfoExt(Net::PTP::ServerDevice *ptp_,TransIndex idx_,PtrLen<const uint8> server_info_) : ptp(ptp_),idx(idx_),server_info(server_info_) {}
     
    void operator () (Packet<uint8> packet) { ptp->send_info(idx,packet,server_info); }
      
    static void Complete(PacketHeader *packet); 
   };
   
  void send_info(PacketList &complete_list,Net::PTP::ServerDevice *ptp,PtrLen<const uint8> server_info); 
   
  void send_error(PacketList &complete_list,Net::PTP::ServerDevice *ptp,ErrorIdType error_id);
  
  template <class T>
  void send_info(PacketList &complete_list,const T &t,Net::PTP::ServerDevice *ptp)
   {
    Net::PTP::Result result(serv_func,NoError);
  
    auto len=SaveLen(result,t);
     
    if( packet.checkDataLen(len) )
      {
       PtrLen<uint8> info=packet.setDataLen(len);
        
       BufPutDev dev(info.ptr);
        
       dev(result,t);
       
       send_info(complete_list,ptp,Range_const(info));
      }
    else
      {
       send_cancel(complete_list,ptp);
      }
   }
 };
 
/* class ServerProcBase */ 

class ServerProcBase : NoCopy
 {
  protected:
  
   Log log;
   
   ObjHook hook;
   
   Net::PTP::ServerDevice *ptp;
   
  public: 
  
   explicit ServerProcBase(StrLen ptp_server_name);
   
   ~ServerProcBase();
   
   Log & getLog() { return log; }
   
   Net::PTP::ServerDevice * getPTP() { return ptp; }
   
   virtual void session(XPoint point)=0;
    
   virtual bool exist(ServiceIdType service_id,FunctionIdType function_id)=0; 
 };
 
/* class ProcBase */ 

class ProcBase : NoCopy
 {
  protected:
  
   Log &log;
   Net::PTP::ServerDevice *ptp;
   
  public:
  
   explicit ProcBase(ServerProcBase *base) : log(base->getLog()),ptp(base->getPTP()) {}
 };
 
} // namespace App
 
#endif



