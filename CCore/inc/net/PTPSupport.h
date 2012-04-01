/* PTPSupport.h */ 
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

#ifndef CCore_inc_net_PTPSupport_h
#define CCore_inc_net_PTPSupport_h

#include <CCore/inc/net/PTPClientDevice.h>
 
namespace CCore {
namespace Net {
namespace PTP {

/* functions */ 

bool GuardSupportNoPacket(ExceptionType ex,const char *name);

bool GuardSupportTransFailed(ExceptionType ex,const char *name,TransResult trans_result);

bool GuardSupportError(ExceptionType ex,const char *name,StrLen str);

/* classes */ 

struct TransStatus;

template <class Ext,class Result> class Support;

class Support_Exist;

class Support_ErrorDesc;

class Support_Seed;

class Support_Echo;

/* struct TransStatus */ 

struct TransStatus
 {
  TransResult trans_result;
  ErrorIdType error_id;
  bool no_packet;
  bool ok;
  
  TransStatus() 
   {
    trans_result=Trans_Initial;
    error_id=Error_Unknown;
    no_packet=false;
    ok=false;
   }
  
  void statusOk() { ok=true; }
  
  void setNoPacket() { ok=false; no_packet=true; }
  
  void setError(TransResult trans_result_,ErrorIdType error_id_)
   {
    ok=false;
    no_packet=false;
    trans_result=trans_result_;
    error_id=error_id_;
   }
   
  void setTransError(TransResult trans_result_)
   {
    ok=false;
    no_packet=false;
    trans_result=trans_result_;
    error_id=Error_Unknown;
   }
   
  template <class Ext> 
  bool set(Ext *ext) 
   {
    if( ext->isOk() )
      {
       statusOk();
       
       return true;
      }
      
    setError(ext->result,ext->error_id);  
      
    return false;  
   }
 
  template <class TimeoutType> 
  bool guard(ExceptionType ex,ClientDevice *client,PacketSet<uint8> &pset,const char *name,TimeoutType timeout,ServiceIdType service_id,FunctionIdType function_id); 
  
  template <class Ext,class TimeoutType> 
  bool guard(ExceptionType ex,ClientDevice *client,PacketSet<uint8> &pset,const char *name,TimeoutType timeout)
   {
    return guard(ex,client,pset,name,timeout,Ext::ServiceId,Ext::FunctionId);
   }
 };
  
/* class Support<Ext,Result> */ 

template <class Ext,class Result>
class Support : public Funchor_nocopy
 {
   ClientDevice *client;
   PacketSet<uint8> &pset;
   
  private:
  
   void complete(PacketHeader *packet_)
    {
     Packet<uint8,Ext> packet=packet_;
     
     Ext *ext=packet.getExt();
     
     if( ext->isOk() )
       {
        result.setOk(*ext,packet);
       }
     else 
       {
        result.setError(ext->result,ext->error_id);
       }
     
     packet.popExt().complete();
    }
    
   PacketFunction function_complete() { return FunctionOf(this,&Support::complete); }
   
  public: 
  
   Result result;
   
   Support(ClientDevice *client_,PacketSet<uint8> &pset_) : client(client_),pset(pset_) {}
   
   template <class TimeoutType,class ... SS>
   bool perform(TimeoutType timeout,SS ... ss)
    {
     Packet<uint8> packet=pset.get(timeout);
     
     if( !packet ) 
       {
        result.setNoPacket();
       
        return false;
       }
     
     Packet<uint8,Ext> packet2=packet.pushExt<Ext>();
     
     packet2.pushCompleteFunction(function_complete());
     
     client->support(packet2,ss...);
     
     pset.wait(timeout);
     
     return result.ok;
    }
    
   template <class TimeoutType,class Fill,class ... SS>
   bool perform_fill(TimeoutType timeout,Fill &fill,SS ... ss)
    {
     Packet<uint8> packet=pset.get(timeout);
     
     if( !packet ) 
       {
        result.setNoPacket();
       
        return false;
       }
       
     auto format=client->getFormat<Ext>();
     
     if( !format )
       {
        packet.complete();
       
        result.setNoFill();
       
        return false;
       }
     
     ulen len=fill.getLen();
       
     if( !packet.checkDataLen(format.format,len) )
       {
        packet.complete();
        
        result.setNoFill();
        
        return false;
       }
       
     fill.fill(packet.setDataLen(format.format,len));
     
     Packet<uint8,Ext> packet2=packet.pushExt<Ext>();
     
     packet2.pushCompleteFunction(function_complete());
     
     client->support(packet2,ss...);
     
     pset.wait(timeout);
     
     return result.ok;
    }
    
   template <class TimeoutType> 
   bool guard(ExceptionType ex,const char *name,TimeoutType timeout)
    {
     return result.template guard<Ext>(ex,client,pset,name,timeout);
    }
 };
 
/* class Support_Exist */ 

class Support_Exist : NoCopy 
 {
  public:
  
   enum ResultType
    {
     NotExist,
     Exist,
     Unknown
    };
    
   friend const char * GetTextDesc(ResultType result); 
    
  private:
 
   struct Result : NoCopy
    {
     ResultType result;
     bool ok;
     
     Result() : result(Unknown) {}
     
     void setOk(const PTPSupport::ExistExt &ext,Packet<uint8,PTPSupport::ExistExt>) { ok=true; result=(ext.exist?Exist:NotExist); }
     
     void setNoPacket() { ok=false; result=Unknown; }
     
     void setError(TransResult,ErrorIdType) { ok=false; result=Unknown; }
    };
 
   Support<PTPSupport::ExistExt,Result> support;
 
  public:
  
   Support_Exist(ClientDevice *client,PacketSet<uint8> &pset) : support(client,pset) {}
   
   template <class TimeoutType>
   bool perform(TimeoutType timeout,ServiceIdType service_id,FunctionIdType function_id) 
    { 
     return support.perform(timeout,service_id,function_id); 
    }
    
   ResultType getResult() const { return support.result.result; }
 };
 
/* class Support_ErrorDesc */ 

class Support_ErrorDesc : NoCopy
 {
   struct Result : NoCopy
    {
     PacketBuf pbuf;
     PtrLen<const char> desc;
     bool ok;
     
     Result() : ok(false) {}
     
     void setOk(PTPSupport::ErrorDescExt &ext,Packet<uint8,PTPSupport::ErrorDescExt> packet) 
      { 
       ok=true; 
       
       packet.detach(pbuf);
       
       desc=Mutate<const char>(ext.desc);
      }
     
     void setNoPacket() { ok=false; }
     
     void setError(TransResult,ErrorIdType) { ok=false; }
     
     StrLen getDesc() const
      {
       if( ok ) return desc;
     
       return "Unknown error";
      }
    };
    
   Support<PTPSupport::ErrorDescExt,Result> support;
   
  public: 
  
   Support_ErrorDesc(ClientDevice *client,PacketSet<uint8> &pset) : support(client,pset) {}
   
   template <class TimeoutType>
   bool perform(TimeoutType timeout,ServiceIdType service_id,FunctionIdType function_id,ErrorIdType error_id) 
    { 
     return support.perform(timeout,service_id,function_id,error_id); 
    }
    
   StrLen getDesc() const { return support.result.getDesc(); }
 };
 
template <class TimeoutType> 
bool TransStatus::guard(ExceptionType ex,ClientDevice *client,PacketSet<uint8> &pset,const char *name,TimeoutType timeout,ServiceIdType service_id,FunctionIdType function_id)
 {
  if( ok ) return true;
  
  if( no_packet ) return GuardSupportNoPacket(ex,name);
    
  if( trans_result ) return GuardSupportTransFailed(ex,name,trans_result); 
    
  Support_ErrorDesc desc(client,pset);
  
  desc.perform(timeout,service_id,function_id,error_id);
  
  return GuardSupportError(ex,name,desc.getDesc());
 }
 
/* class Support_Seed */  
 
class Support_Seed : NoCopy
 {
   struct Result : TransStatus
    {
     uint64 seed1;
     uint64 seed2;
     
     Result() : seed1(0),seed2(0) {}
     
     void setOk(const PTPSupport::SeedExt &ext,Packet<uint8,PTPSupport::SeedExt>) 
      {
       statusOk();
      
       seed1=ext.seed1;
       seed2=ext.seed2;
      }
    };
 
   Support<PTPSupport::SeedExt,Result> support;
   
  public: 
  
   Support_Seed(ClientDevice *client,PacketSet<uint8> &pset) : support(client,pset) {}
   
   template <class TimeoutType>
   bool perform(TimeoutType timeout) 
    { 
     return support.perform(timeout); 
    }
    
   template <class TimeoutType>
   void perform_guarded(TimeoutType timeout) 
    { 
     if( !perform(timeout) ) support.guard(Exception,"CCore::Net::PTP::Support_Seed::perform(...)",timeout);
    }
    
   uint64 getSeed1() const { return support.result.seed1; } 
    
   uint64 getSeed2() const { return support.result.seed2; } 
 };
 
/* class Support_Echo */ 
 
class Support_Echo : NoCopy
 {
   struct Result : TransStatus
    {
     PacketBuf pbuf;
     PtrLen<const uint8> echo;
   
     Result() {}
     
     void setOk(PTPSupport::EchoExt &ext,Packet<uint8,PTPSupport::EchoExt> packet)
      {
       statusOk();
       
       packet.detach(pbuf);
       
       echo=ext.data;
      }
      
     void setNoFill()
      {
       setNoPacket();
      }
      
     PtrLen<const uint8> getEcho() const
      {
       if( ok ) return echo;
       
       return Nothing;
      }
    };
    
   Support<PTPSupport::EchoExt,Result> support;
   
  public: 
  
   Support_Echo(ClientDevice *client,PacketSet<uint8> &pset) : support(client,pset) {}
   
   template <class TimeoutType,class Fill>
   bool perform(TimeoutType timeout,uint32 delay_msec,Fill &fill) 
    { 
     return support.perform_fill(timeout,fill,delay_msec); 
    }
    
   template <class TimeoutType,class Fill>
   void perform_guarded(TimeoutType timeout,uint32 delay_msec,Fill &fill) 
    { 
     if( !perform(timeout,delay_msec,fill) ) support.guard(Exception,"CCore::Net::PTP::Support_Echo::perform(...)",timeout);
    }
    
   PtrLen<const uint8> getEcho() const { return support.result.getEcho(); }
 };
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 
#endif
 

