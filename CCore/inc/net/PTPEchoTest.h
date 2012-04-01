/* PTPEchoTest.h */ 
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

#ifndef CCore_inc_net_PTPEchoTest_h
#define CCore_inc_net_PTPEchoTest_h

#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/PTPServerDevice.h>
 
namespace CCore {
namespace Net {
namespace PTP {

/* classes */ 

class EchoTest;

/* class EchoTest */ 

class EchoTest : NoCopy , ServerProc
 {
   ObjHook hook;
   
   ServerDevice *ptp;
 
  private:
  
   void cancel(TransIndex idx,Packet<uint8> packet);
  
   virtual void inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info);
    
   virtual void tick();
   
  public: 
  
   static const ServiceIdType ServiceId = 10000 ;
   static const FunctionIdType FunctionId = 1 ;
   
   static const ulen DeltaLen = 12 ;
   
   struct Ext;
  
   explicit EchoTest(StrLen ptp_server_name);
   
   ~EchoTest();
 };
 
/* struct EchoTest::Ext */  

struct EchoTest::Ext : ExtBase<EchoTest::ServiceId,EchoTest::FunctionId,MovePacketBuf>
 {
  struct InputType // + uint8 info[len];
   {
    static const uint32 MaxLen = MaxInfoLen ;
   
    uint32 len;
    
    explicit InputType(ulen len_) : len(len_) {}
    
    // save object
    
    enum { SaveLoadLen = SaveLenCounter<uint32>::SaveLoadLen };
  
    template <class Dev>
    void save(Dev &dev) const
     {
      dev.template use<BeOrder>(len);
     }
   };
   
  struct OutputType
   {
    PtrLen<const uint8> info;
    
    // load object
    
    template <class Dev>
    void load(Dev &dev)
     {
      info=dev.getFinalRange();
     }
   };
   
  PtrLen<const uint8> info; 
  
  void done(const OutputType &output)
   {
    info=output.info;
   }
 };
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 
#endif
 

