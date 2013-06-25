/* SysNet.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/sys/SysNet.h>
#include <CCore/inc/sys/SysAbort.h>

#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Exception.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <sys/eventfd.h>

namespace CCore {
namespace Sys {

namespace Private_SysNet {

/* class Address */

class Address : NoCopy
 {
  private:
  
   struct sockaddr_in addr;
  
  private:
  
   void setFamily(sa_family_t address_family=AF_INET);
  
   void setPort(Net::UDPort udport);
  
   void setAddress(Net::IPAddress address);
  
  public:
  
   Address() {}
  
   explicit Address(Net::UDPort udport);
  
   explicit Address(Net::UDPoint udpoint);
   
   // get
   
   Net::UDPoint get();
  
   // raw
  
   struct sockaddr * getPtr() { return (struct sockaddr *)&addr; }
  
   ulen getLen() const { return sizeof addr; }
 };

void Address::setFamily(sa_family_t address_family)
 {
  addr.sin_family=address_family;
 }

void Address::setPort(Net::UDPort udport)
 {
  addr.sin_port=htons(udport);
 }

void Address::setAddress(Net::IPAddress address)
 {
  addr.sin_addr.s_addr=htonl(address.get());
 }

Address::Address(Net::UDPort udport)
 : addr{}
 {
  setFamily();
  setPort(udport);
 }

Address::Address(Net::UDPoint udpoint)
 : addr{}
 {
  setFamily();
  setPort(udpoint.port);
  setAddress(udpoint.address);
 }

Net::UDPoint Address::get()
 {
  uint32 ip=ntohl(addr.sin_addr.s_addr);
  uint16 port=ntohs(addr.sin_port);
  
  return Net::UDPoint(Net::IPAddress(ip),port);
 }

} // namespace Private_SysNet

using namespace Private_SysNet;

/* struct UDPSocket */

auto UDPSocket::Open(Net::UDPort udport) noexcept -> OpenType
 {
  Type sockid=socket(AF_INET,SOCK_DGRAM,0);
  
  if( sockid==-1 ) return {sockid,NonNullError()};
  
  Address address(udport);
  
  if( bind(sockid,address.getPtr(),address.getLen())==-1 )
    {
     auto error=NonNullError();
     
     ::close(sockid); // ignore unprobable error
     
     return {-1,error};
    }
  
  return {sockid,NoError};
 }

ErrorType UDPSocket::Close(Type sockid) noexcept
 {
  if( ::close(sockid)==-1 ) return NonNullError();
  
  return NoError;
 }

WaitResult UDPSocket::Wait_in(Type sockid,MSec timeout) noexcept
 {
  pollfd list[1];
  
  list[0].fd=sockid;
  list[0].events=POLLIN;
  
  int result=poll(list,1,+timeout);
  
  if( result==-1 ) return Wait_error;
  
  if( result==0 ) return Wait_timeout;
  
  if( !(list[0].revents&POLLIN) ) return Wait_error;
  
  return WaitResult(0);
 }

ErrorType UDPSocket::Outbound(Type sockid,Net::UDPoint dst,PtrLen<const uint8> data) noexcept
 {
  Address address(dst);
  
  auto result=sendto(sockid,data.ptr,data.len,0,address.getPtr(),address.getLen());
  
  if( result==-1 ) return NonNullError();
  
  if( (ulen)result!=data.len ) return Error_Socket;
  
  return NoError;
 }

auto UDPSocket::Inbound(Type sockid,PtrLen<uint8> buf) noexcept -> InResult
 {
  Address address;
  socklen_t address_len=address.getLen();
  
  auto result=recvfrom(sockid,buf.ptr,buf.len,0,address.getPtr(),&address_len);
  
  if( result==-1 ) return {{},0,NonNullError()};
  
  if( (ulen)result>buf.len || address_len!=address.getLen() ) return {{},0,Error_Socket};
  
  return {address.get(),(ulen)result,NoError};
 }

/* struct AsyncUDPSocket */

struct AsyncUDPSocket::AsyncState
 {
  DLink<AsyncState> link;
  
  Type sockid;
  
  enum OpType
   {
    Nop,
    Inbound,
    Outbound
   };
  
  OpType op_type;
  
  struct OutboundArgs
   {
    Net::UDPoint dst;
    PtrLen<const uint8> data;
   };
  
  struct InboundArgs
   {
    PtrLen<uint8> buf;
   };
  
  union Args
   {
    OutboundArgs outbound;
    InboundArgs inbound;
    
    Args() {}
    
   } args;
  
  void prepareOutbound(Type sockid_,Net::UDPoint dst,PtrLen<const uint8> data)
   {
    sockid=sockid_;
    op_type=Outbound;
    
    args.outbound.dst=dst;
    args.outbound.data=data;
   }
   
  void prepareInbound(Type sockid_,PtrLen<uint8> buf)
   {
    sockid=sockid_;
    op_type=Inbound;
    
    args.inbound.buf=buf;
   }
  
  void cancel()
   {
    op_type=Nop;
   }
 };

typedef DLink<AsyncUDPSocket::AsyncState>::CircularAlgo<&AsyncUDPSocket::AsyncState::link> Algo;

auto AsyncUDPSocket::Open(Net::UDPort udport) noexcept -> OpenType
 {
  Type sockid=socket(AF_INET,SOCK_DGRAM,0);
  
  if( sockid==-1 ) return {sockid,NonNullError()};
  
  Address address(udport);
  
  if( bind(sockid,address.getPtr(),address.getLen())==-1 )
    {
     auto error=NonNullError();
    
     ::close(sockid); // ignore unprobable error
    
     return {-1,error};
    }
  
  return {sockid,NoError};
 }

ErrorType AsyncUDPSocket::Close(Type sockid) noexcept
 {
  if( ::close(sockid)==-1 ) return NonNullError();
  
  return NoError;
 }

auto AsyncUDPSocket::StartOutbound(Type sockid,Async async,Net::UDPoint dst,PtrLen<const uint8> data) noexcept -> OutResult
 {
  async->prepareOutbound(sockid,dst,data);
  
  return {true,NoError};
 }

ErrorType AsyncUDPSocket::CompleteOutbound(Type sockid,Async async) noexcept
 {
  Address address(async->args.outbound.dst);
  
  PtrLen<const uint8> data=async->args.outbound.data;
  
  auto result=sendto(sockid,data.ptr,data.len,0,address.getPtr(),address.getLen());
  
  if( result==-1 ) return NonNullError();
  
  if( (ulen)result!=data.len ) return Error_Socket;
  
  return NoError;
 }

auto AsyncUDPSocket::StartInbound(Type sockid,Async async,PtrLen<uint8> buf) noexcept -> StartInResult
 {
  async->prepareInbound(sockid,buf);
  
  return {true,{}};
 }

auto AsyncUDPSocket::CompleteInbound(Type sockid,Async async) noexcept -> InResult
 {
  Address address;
  socklen_t address_len=address.getLen();
  
  PtrLen<uint8> buf=async->args.inbound.buf;
  
  auto result=recvfrom(sockid,buf.ptr,buf.len,0,address.getPtr(),&address_len);
  
  if( result==-1 ) return {{},0,NonNullError()};
  
  if( (ulen)result>buf.len || address_len!=address.getLen() ) return {{},0,Error_Socket};
  
  return {address.get(),(ulen)result,NoError};
 }

ErrorType AsyncUDPSocket::open(Net::UDPort udport) noexcept
 {
  list=0;
  
  OpenType result=Open(udport);
  
  sockid=result.sockid;
  
  return result.error; 
 }

ErrorType AsyncUDPSocket::close() noexcept
 {
  for(Algo::Cur cur(list); +cur ;++cur) cur->cancel();
  
  return Close(sockid);
 }

auto AsyncUDPSocket::startOutbound(Async async,Net::UDPoint dst,PtrLen<const uint8> data) noexcept -> OutResult
 {
  list=Algo::InsTopFirst(list,async);
  
  return StartOutbound(sockid,async,dst,data);
 }

ErrorType AsyncUDPSocket::completeOutbound(Async async) noexcept
 {
  list=Algo::DelTop(list,async);
  
  return CompleteOutbound(sockid,async);
 }

auto AsyncUDPSocket::startInbound(Async async,PtrLen<uint8> buf) noexcept -> StartInResult
 {
  list=Algo::InsTopFirst(list,async);
  
  return StartInbound(sockid,async,buf);
 }

auto AsyncUDPSocket::completeInbound(Async async) noexcept -> InResult
 {
  list=Algo::DelTop(list,async);
  
  return CompleteInbound(sockid,async);
 }

/* class AsyncUDPSocketWait::Engine */

class AsyncUDPSocketWait::Engine : public MemBase_nocopy
 {
   typedef AsyncUDPSocket::AsyncState AsyncState;
 
   class State : NoCopy , public NoThrowFlagsBase
    {
      AsyncState state;
      
     public: 
      
      ulen slot;
      
      State() : slot(0) {}
      
      ~State() {}
      
      bool prepare(struct pollfd &ret)
       {
        switch( state.op_type )
          {
           case AsyncState::Inbound : ret.events=POLLIN; break;
           
           case AsyncState::Outbound : ret.events=POLLOUT; break;
           
           default: return false;
          }
        
        ret.fd=state.sockid;
        
        return true;
       }
      
      AsyncState * getAsync() { return &state; }
    };
   
   class FdSem : NoCopy
    {
      int fd;
     
     public: 
      
      FdSem()
       {
        fd=eventfd(0,EFD_SEMAPHORE);
        
        if( fd==-1 )
          {
           int error=errno;
          
           Printf(Exception,"eventfd() : #;",error);
          }
       }
      
      ~FdSem()
       {
        AbortIf( close(fd)==-1 ,"CCore::Sys::AsyncUDPSocketWait::Engine::FdSem::~FdSem()");
       }
      
      void prepare(struct pollfd &ret)
       {
        ret.fd=fd;
        ret.events=POLLIN;
       }
      
      void give()
       {
        AbortIf( eventfd_write(fd,1)==-1 ,"CCore::Sys::AsyncUDPSocketWait::Engine::FdSem::give()");
       }
      
      void take()
       {
        eventfd_t value;
        
        AbortIf( eventfd_read(fd,&value)==-1 ,"CCore::Sys::AsyncUDPSocketWait::Engine::FdSem::take()");
       }
    };
   
   SimpleArray<State> state_buf;
   SimpleArray<AsyncState *> async_buf;
   
   SimpleArray<struct pollfd> poll_buf;
   SimpleArray<ulen> index_buf;
   
   FdSem sem;
   
   ulen count;
   bool sem_first;
   
  private:
    
   static WaitResult WaitSome(struct pollfd *buf,ulen len,MSec timeout);
   
   static WaitResult Wait(struct pollfd &data,TimeScope time_scope);
   
   static WaitResult WaitAll(struct pollfd *buf,ulen len,MSec timeout);
   
   void rollWait(ulen slot,ulen index);

  public:
 
   explicit Engine(ulen async_count);
 
   ~Engine() {}
 
   AsyncState ** getAsyncs() { return async_buf.getPtr(); }
 
   bool addWait(ulen index);
 
   bool delWait(ulen index);
 
   WaitResult wait(MSec timeout);
 
   void interrupt() { sem.give(); }
 
   WaitResult waitAll(MSec timeout);
 };

WaitResult AsyncUDPSocketWait::Engine::WaitSome(struct pollfd *buf,ulen len,MSec timeout)
 {
  int result=poll(buf,len,+timeout);
  
  if( result==-1 ) return Wait_error;
  
  if( result==0 ) return Wait_timeout;
  
  for(ulen i=0; i<len ;i++)
    {
     if( buf[i].events&buf[i].revents ) return WaitResult(i);
    }
  
  return Wait_error;
 }

WaitResult AsyncUDPSocketWait::Engine::Wait(struct pollfd &data,TimeScope time_scope)
 {
  int result=poll(&data,1,+time_scope.get());
  
  if( result==-1 ) return Wait_error;
  
  if( result==0 ) return Wait_timeout;
  
  if( data.events&data.revents ) return WaitResult(0); 
   
  return Wait_error;
 }

WaitResult AsyncUDPSocketWait::Engine::WaitAll(struct pollfd *buf,ulen len,MSec timeout)
 {
  TimeScope time_scope(timeout);
  
  for(auto r=Range(buf,len); +r ;++r)
    {
     WaitResult result=Wait(*r,time_scope);
     
     if( result<0 ) return result;
    }
  
  return WaitResult(0);
 }

void AsyncUDPSocketWait::Engine::rollWait(ulen slot,ulen index)
 {
  if( slot<count )
    {
     ulen i=Replace(index_buf[count],index);
     
     index_buf[slot]=i;
     
     state_buf[i].slot=slot;

     state_buf[index].slot=count;
    }
 }

AsyncUDPSocketWait::Engine::Engine(ulen async_count)
 : state_buf(async_count),
   async_buf(async_count),
   poll_buf(async_count+2),
   index_buf(async_count+1),
   count(0),
   sem_first(true)
 {
  for(ulen i=0; i<async_count ;i++) async_buf[i]=state_buf[i].getAsync();
 }

bool AsyncUDPSocketWait::Engine::addWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].slot!=0 ) return false;
  
  ulen slot=++count;
  
  state_buf[index].slot=slot;
  index_buf[slot]=index;
  
  return true;
 }

bool AsyncUDPSocketWait::Engine::delWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].slot==0 ) return false;
  
  ulen slot=Replace_null(state_buf[index].slot);
  
  if( slot<count )
    {
     ulen i=index_buf[count];
     
     index_buf[slot]=i;
     
     state_buf[i].slot=slot;
    }
   
  count--;
   
  return true;
 }

WaitResult AsyncUDPSocketWait::Engine::wait(MSec timeout)
 {
  // prepare
  {
   for(ulen i=0,len=count; i<len ;i++)
     {
      ulen slot=i+1;
      ulen index=index_buf[slot];
     
      if( !state_buf[index].prepare(poll_buf[slot]) ) return WaitResult(index);
     }
  }
  
  // wait
  
  WaitResult slot;
  
  if( sem_first )
    {
     sem.prepare(poll_buf[0]);
     
     slot=WaitSome(poll_buf.getPtr(),count+1,timeout);
     
     if( slot<0 ) return slot;
     
     if( slot==0 ) 
       {
        sem_first=false;
        
        sem.take();
        
        return Wait_interrupt;
       }
    }
  else
    {
     sem.prepare(poll_buf[count+1]);
     
     slot=WaitSome(poll_buf.getPtr()+1,count+1,timeout);
     
     if( slot<0 ) return slot;
     
     if( (ulen)slot==count ) 
       {
        sem.take();
       
        return Wait_interrupt;
       }
     
     slot=WaitResult(slot+1);
     
     sem_first=true;
    }
  
  ulen index=index_buf[slot];
  
  rollWait(slot,index);
  
  return WaitResult(index);
 }

WaitResult AsyncUDPSocketWait::Engine::waitAll(MSec timeout)
 {
  ulen slot=0;
   
  for(ulen i=0,len=count; i<len ;i++)
    {
     ulen index=index_buf[i+1];
     
     if( state_buf[index].prepare(poll_buf[slot]) ) slot++;
    }
   
  if( !slot ) return WaitResult(0);
  
  return WaitAll(poll_buf.getPtr(),slot,timeout);
 }

/* struct AsyncUDPSocketWait */

ErrorType AsyncUDPSocketWait::init(ulen async_count) noexcept
 {
  if( async_count>MaxAsyncs ) return ErrorType(EINVAL);
  
  SilentReportException report;
  
  try
    {
     obj=new Engine(async_count);
     
     asyncs=obj->getAsyncs();
     
     return NoError;
    }
  catch(CatchType)
    {
     return ErrorType(ENOMEM);
    }
 }
  
void AsyncUDPSocketWait::exit() noexcept
 {
  delete Replace_null(obj);
  
  asyncs=0;
 }
  
bool AsyncUDPSocketWait::addWait(ulen index) noexcept
 {
  return obj->addWait(index);
 }
  
bool AsyncUDPSocketWait::delWait(ulen index) noexcept
 {
  return obj->delWait(index);
 }
  
WaitResult AsyncUDPSocketWait::wait(MSec timeout) noexcept
 {
  return obj->wait(timeout);
 }
  
void AsyncUDPSocketWait::interrupt() noexcept
 {
  obj->interrupt();
 }
  
WaitResult AsyncUDPSocketWait::waitAll(MSec timeout) noexcept
 {
  return obj->waitAll(timeout);
 }
  
} // namespace Sys
} // namespace CCore
 

