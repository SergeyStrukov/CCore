/* SupportProc.h */ 
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

#ifndef PTPServer_SupportProc_h
#define PTPServer_SupportProc_h

#include <CCore/inc/Random.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Tree.h>

#include <CCore/inc/net/PTPSupportBase.h>

#include "ProcBase.h"

namespace App {

/* classes */ 

class ProcEcho;

class SupportProc;

/* class ProcEcho */ 

class ProcEcho : NoCopy
 {
   struct Ext
    {
     TreeUpLink<Ext,XPoint> link1;
     TreeUpLink<Ext,uint32> link2;
     DLink<Ext> link;
    
     TransIndex idx;
     Packet<uint8,Ext> packet;
     PtrLen<const uint8> server_info;
     
     uint32 getDelay() const { return link2.key; }
     
     void subDelay(uint32 delta) { link2.key-=delta; }
    };
    
   typedef TreeUpLink<Ext,XPoint>::RadixAlgo<&Ext::link1> Algo1;
   typedef TreeUpLink<Ext,uint32>::RadixAlgo<&Ext::link2> Algo2;
   
   Algo1::Root root1;
   Algo2::Root root2;
   DLink<Ext>::CircularAlgo<&Ext::link>::Top list;
   
   uint32 cur_tick;
   uint32 min_delay;
   
  private:
  
   void add(XPoint point,uint32 delay_tick,Ext *ext);
   
   void del(Ext *ext);
   
   void kill(Ext *ext);
   
   void send(Ext *ext,Net::PTP::ServerDevice *ptp);
   
  public:
  
   ProcEcho();
   
   ~ProcEcho();
   
   void put(XPoint point,uint32 delay_msec,TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info);
   
   void tick(Net::PTP::ServerDevice *ptp);
   
   void purge(XPoint point);
 };
 
/* class SupportProc */ 

class SupportProc : ProcBase
 {
   LenType to_server_info_len;
   LenType to_client_info_len;
   
   Random random;
   
   ProcEcho echo;
   
   ServerProcBase *base;
   
  private: 
   
   void set(ulen max_outbound_info_len,ulen max_inbound_info_len);
  
  private:
  
   void function_Len(Inbound &inbound);
  
   void function_Seed(Inbound &inbound);
   
   void function_Session(Inbound &inbound);
   
   void function_Echo(Inbound &inbound);
   
   void function_ErrorDesc(Inbound &inbound);
   
   void function_Exist(Inbound &inbound);
   
  public: 
  
   explicit SupportProc(ServerProcBase *base);
   
   ~SupportProc();
   
   void inbound(Inbound &inbound);
   
   void tick();
   
   void session(XPoint point);
   
   bool exist(FunctionIdType function_id);
 };
 
} // namespace App
 
#endif

