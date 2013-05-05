/* PTPBoot.cpp */ 
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
 
#include <CCore/inc/net/PTPBoot.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/net/PTPServerDevice.h>
 
namespace CCore {
namespace Net {
namespace PTPBoot {

/* class BootClient */ 

void BootClient::complete_alloc(PacketHeader *packet_)
 {
  Packet<uint8,AllocExt> packet=packet_;
  
  AllocExt *ext=packet.getExt();
  
  if( status.set(ext) )
    {
     index=ext->index;
    }
  
  packet.popExt().complete();
 }
 
void BootClient::complete_write(PacketHeader *packet_) 
 {
  Packet<uint8,WriteExt> packet=packet_;
  
  WriteExt *ext=packet.getExt();
  
  if( !ext->isOk() )
    {
     if( status_flag++ )
       {
        status_flag--;
       }
     else
       {
        status.set(ext);
       }
    }
  
  packet.popExt().complete();
 }
 
void BootClient::complete_boot(PacketHeader *packet_)
 {
  Packet<uint8,BootExt> packet=packet_;
  
  BootExt *ext=packet.getExt();
  
  status.set(ext);
  
  packet.popExt().complete();
 }
 
BootClient::BootClient(StrLen ptp_dev_name,MSec timeout_,ulen max_packets)
 : hook(ptp_dev_name),
   ptp(hook),
   pset("BootClient",max_packets),
   timeout(timeout_)
 {
  write_format=ptp->getFormat_guarded<WriteExt>("CCore::Net::PTPBoot::BootClient::BootClient(...)");
 }
   
BootClient::~BootClient()
 {
 }
   
IndexType BootClient::alloc(AddressType address,AddressType len)
 {
  TimeScope time_scope(timeout);
  
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     status.setNoPacket();
    }
  else
    {
     Packet<uint8,AllocExt> packet2=packet.pushExt<AllocExt>();  
  
     packet2.pushCompleteFunction(function_complete_alloc());
  
     AllocInput input(address,len);
 
     ptp->start(packet2,input);
  
     pset.wait(time_scope);
    }
  
  status.guard<AllocExt>(Exception,ptp,pset,"CCore::Net::PTPBoot::BootClient::alloc(...)",time_scope);
  
  return index;
 }
   
void BootClient::write(IndexType index,AddressType off,PtrLen<const uint8> data)
 {
  status_flag=0;
  
  status.statusOk();
 
  while( +data )
    {
     Packet<uint8> packet=pset.get(timeout);
     
     if( !packet )
       {
        pset.cancel_and_wait();
        
        Printf(Exception,"CCore::Net::PTPBoot::BootClient::write(...) : no packet");
       }
       
     ulen max_len=packet.getMaxDataLen(write_format).len;
     
     if( !max_len )
       {
        packet.complete();
        
        pset.cancel_and_wait();
        
        Printf(Exception,"CCore::Net::PTPBoot::BootClient::write(...) : no room");
       }
       
     PtrLen<const uint8> frame=data.takeup(max_len);  
       
     packet.setDataLen(write_format,frame.len).copy(frame.ptr);  
       
     Packet<uint8,WriteExt> packet2=packet.pushExt<WriteExt>();  
     
     packet2.pushCompleteFunction(function_complete_write());
     
     WriteInput input(index,off,frame.len);
     
     off+=frame.len;
     
     ptp->start_format(packet2,input);  
    }
    
  pset.wait(timeout);  
    
  status.guard<WriteExt>(Exception,ptp,pset,"CCore::Net::PTPBoot::BootClient::write(...)",timeout);  
 }
   
void BootClient::boot(AddressType entry_point,FlagType flags)
 {
  TimeScope time_scope(timeout);
  
  Packet<uint8> packet=pset.get(time_scope);
  
  if( !packet )
    {
     status.setNoPacket();
    }
  else
    {
     Packet<uint8,BootExt> packet2=packet.pushExt<BootExt>();  
     
     packet2.pushCompleteFunction(function_complete_boot());
     
     BootInput input(entry_point,flags);
    
     ptp->start(packet2,input);
     
     pset.wait(time_scope);
    }
  
  status.guard<BootExt>(Exception,ptp,pset,"CCore::Net::PTPBoot::BootClient::boot(...)",time_scope);
 }
 
/* class BootInfo::PTPServerProc */ 

class BootInfo::PTPServerProc : NoCopy , ServerProc
 {
   ObjHook hook;
   
   ServerDevice *ptp;
   
   Mutex mutex;
   
   BootInfo &boot_info;
   
  private:
  
   struct Inbound;
   
   struct WriteInputTailed;
   
   struct ErrorDescOutput;
 
   void support_Len(Inbound &inbound);
   
   void support_Seed(Inbound &inbound);
   
   void support_Session(Inbound &inbound);
   
   void support_ErrorDesc(Inbound &inbound);
   
   void boot_alloc(Inbound &inbound);
   
   void boot_write(Inbound &inbound);
   
   void boot_boot(Inbound &inbound);
  
  private:
  
   virtual void inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info);
    
   virtual void tick();
   
  public: 
  
   PTPServerProc(BootInfo &boot_info,StrLen ptp_server_name);
   
   ~PTPServerProc();
   
   void waitActiveComplete(MSec timeout);
 };
 
struct BootInfo::PTPServerProc::Inbound : NoCopy
 {
  ServerDevice *ptp;
  
  TransIndex idx;
  
  Packet<uint8> packet;
  
  RangeGetDev dev;
  
  ServiceFunction serv_func;
  
  Inbound(PTP::ServerDevice *ptp_,TransIndex idx_,Packet<uint8> packet_,PtrLen<const uint8> client_info)
   : ptp(ptp_),
     idx(idx_),
     packet(packet_),
     dev(client_info) 
   {
    dev(serv_func);
   }
   
  template <class T> 
  bool input(T &input)
   {
    dev(input);
    
    if( !dev.finish() )
      {
       error(Error_BadInput);
      
       return false;
      }
      
    return true;  
   }
   
  void error(ErrorIdType error_id); 
  
  template <class T>
  void info(const T &output);
   
  void cancel()
   {
    Replace_null(packet).complete();
  
    ptp->send_cancel(idx);
   }
 };
 
void BootInfo::PTPServerProc::Inbound::error(ErrorIdType error_id)
 {
  Result result(serv_func,error_id);
  
  auto len=SaveLen(result);
  
  if( packet.checkDataLen(len) )
    {
     PtrLen<uint8> info=packet.setDataLen(len);
     
     BufPutDev dev(info.ptr);
        
     dev(result);
        
     ptp->send_info(idx,Replace_null(packet),Range_const(info));
    }
  else
    {
     cancel();
    }
 }
 
template <class T>
void BootInfo::PTPServerProc::Inbound::info(const T &output)
 {
  Result result(serv_func,NoError);
  
  auto len=SaveLen(result,output);
  
  if( packet.checkDataLen(len) )
    {
     PtrLen<uint8> info=packet.setDataLen(len);
     
     BufPutDev dev(info.ptr);
        
     dev(result,output);
        
     ptp->send_info(idx,Replace_null(packet),Range_const(info));
    }
  else
    {
     cancel();
    }
 }
 
struct BootInfo::PTPServerProc::WriteInputTailed
 {
  WriteInput base;
  PtrLen<const uint8> data;
  
  // load object
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev(base);
    
    if( base.len>base.MaxLen )
      dev.fail();
    else
      data=dev.getFinalRange(base.len);
   }
 };
 
struct BootInfo::PTPServerProc::ErrorDescOutput
 {
  PTPSupport::ErrorDescOutput base;
  PtrLen<const uint8> data;
  
  static StrLen GetErrorDesc(ErrorIdType error_id);
  
  explicit ErrorDescOutput(ErrorIdType error_id)
   {
    StrLen str=GetErrorDesc(error_id);
    
    base.len=str.len;
    
    data=Mutate<const uint8>(str);
   }
  
  // save object
   
  template <class Dev>
  void save(Dev &dev) const
   {
    dev(base);
    
    dev.put(data);
   }
 }; 
 
StrLen BootInfo::PTPServerProc::ErrorDescOutput::GetErrorDesc(ErrorIdType error_id) 
 {
  switch( error_id )
    {
     case NoError          : return "Ok";
     case Error_BadInput   : return "Bad input";
     case Error_NoFunction : return "No function";
     case Error_Exhausted  : return "No memory";
     
     default:
     case Error_Unknown    : return "Unknown";
    }
 }
 
void BootInfo::PTPServerProc::support_Len(Inbound &inbound)
 {
  PTPSupport::LenInput input;
  
  if( inbound.input(input) )
    {
     PTPSupport::LenOutput output(Min<LenType>(input.to_server_info_len,ptp->getMaxInboundInfoLen()),
                                  Min<LenType>(input.to_client_info_len,ptp->getMaxOutboundInfoLen()));
  
     inbound.info(output);
    }
 }
   
void BootInfo::PTPServerProc::support_Seed(Inbound &inbound)
 {
  PTPSupport::SeedInput input;
  
  if( inbound.input(input) )
    {
     PTPSupport::SeedOutput output(0,0);
     
     inbound.info(output);
    }
 }
   
void BootInfo::PTPServerProc::support_Session(Inbound &inbound)
 {
  PTPSupport::SessionInput input;
  
  if( inbound.input(input) )
    {
     PTPSupport::SessionOutput output;
     
     inbound.info(output);
    }
 }
   
void BootInfo::PTPServerProc::support_ErrorDesc(Inbound &inbound)
 {
  PTPSupport::ErrorDescInput input;
  
  if( inbound.input(input) )
    {
     ErrorDescOutput output(input.error_id);
     
     inbound.info(output);
    }
 }
   
void BootInfo::PTPServerProc::boot_alloc(Inbound &inbound)
 {
  AllocInput input;
  
  if( inbound.input(input) )
    {
     try
       {
        IndexType index;
        
        {
         Mutex::Lock lock(mutex);
         
         index=boot_info.alloc(input.address,input.len);
        }
    
        AllocOutput output(index);
     
        inbound.info(output);
       }
     catch(CatchType)  
       {
        inbound.error(Error_Exhausted);
       }
    }
 }
   
void BootInfo::PTPServerProc::boot_write(Inbound &inbound)
 {
  WriteInputTailed input;
  
  if( inbound.input(input) )
    {
     try
       {
        {
         Mutex::Lock lock(mutex);
         
         boot_info.write(input.base.index,input.base.off,input.data);
        } 
    
        WriteOutput output;
     
        inbound.info(output);
       }
     catch(CatchType)  
       {
        inbound.error(Error_BadInput);
       }
    }
 }
   
void BootInfo::PTPServerProc::boot_boot(Inbound &inbound)
 {
  BootInput input;
  
  if( inbound.input(input) )
    {
     {
      Mutex::Lock lock(mutex);
         
      boot_info.boot(input.entry_point,input.flags);
     } 
    
     BootOutput output;
     
     inbound.info(output);
     
     boot_info.signal_complete();
    }
 }
   
void BootInfo::PTPServerProc::inbound(XPoint,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  SilentReportException report;
  
  Inbound inbound(ptp,idx,packet,client_info);
 
  if( !inbound.dev )
    {
     inbound.cancel();
    }
  else
    {
     switch( inbound.serv_func.service_id )
       {
        case PTPSupport::ServiceId :
         {
          switch( inbound.serv_func.function_id )
            {
             case PTPSupport::FunctionId_Len       : support_Len(inbound); break;
             case PTPSupport::FunctionId_Seed      : support_Seed(inbound); break;
             case PTPSupport::FunctionId_Session   : support_Session(inbound); break;
             case PTPSupport::FunctionId_ErrorDesc : support_ErrorDesc(inbound); break;
             
             default: inbound.error(Error_NoFunction);
            }
         }
        break;
        
        case ServiceId :
         {
          switch( inbound.serv_func.function_id )
            {
             case FunctionId_Alloc : boot_alloc(inbound); break;
             case FunctionId_Write : boot_write(inbound); break;
             case FunctionId_Boot  : boot_boot(inbound); break;
             
             default: inbound.error(Error_NoFunction);
            }
         }
        break;
        
        default: inbound.error(Error_NoFunction);
       }
    }  
 }
    
void BootInfo::PTPServerProc::tick()
 {
  // do nothing
 }
   
BootInfo::PTPServerProc::PTPServerProc(BootInfo &boot_info_,StrLen ptp_server_name)
 : hook(ptp_server_name),
   ptp(hook),
   mutex("BootInfo::PTPServerProc.mutex"),
   boot_info(boot_info_)
 {
  ptp->attach(this);
 }
   
BootInfo::PTPServerProc::~PTPServerProc()
 {
  ptp->detach();
 }
 
void BootInfo::PTPServerProc::waitActiveComplete(MSec timeout)
 {
  ptp->waitActiveComplete(timeout);  
 }

/* class BootInfo */ 

BootInfo::Sect::Sect(AddressType address_,AddressType len_)
 : address(address_),
   len(len_)
 {
  if( len_>MaxULen )
    {
     Printf(Exception,"CCore::Net::PTPBoot::BootInfo::Sect::Sect(,len=#;) : overflow",len_);
    }

  data.extend_default((ulen)len_);
 }
      
BootInfo::Sect::~Sect()
 {
 }
      
void BootInfo::Sect::write(AddressType off,PtrLen<const uint8> frame)
 {
  if( off>len || frame.len>(len-off) )
    {
     Printf(Exception,"CCore::Net::PTPBoot::BootInfo::Sect::write(off=#;,len=#;) : bad place",off,frame.len);
    }
 
  frame.copyTo(data.getPtr()+off);
 }
      
IndexType BootInfo::alloc(AddressType address,AddressType len)
 {
  ulen ret=table.getLen();
  
  if( ret>IndexType(UIntMax()) )
    {
     Printf(Exception,"CCore::Net::PTPBoot::BootInfo::alloc(...) : too many sections");
    }
  
  table.append_fill(address,len);
  
  return (IndexType)ret;
 }
   
void BootInfo::write(IndexType index,AddressType off,PtrLen<const uint8> data)
 {
  if( index>=table.getLen() )
    {
     Printf(Exception,"CCore::Net::PTPBoot::BootInfo::write(#;,...) : bad index",index);
    }
    
  table[(ulen)index].write(off,data);  
 }
 
BootInfo::BootInfo()
 : entry_point(0),
   flags(0)
 {
 }
   
BootInfo::~BootInfo()
 {
 }
   
void BootInfo::get(StrLen ptp_server_name,MSec timeout)
 {
  PTPServerProc proc(*this,ptp_server_name);
  
  wait_complete();
  
  proc.waitActiveComplete(timeout);  
 }
 
} // namespace PTPBoot
} // namespace Net
} // namespace CCore
 

