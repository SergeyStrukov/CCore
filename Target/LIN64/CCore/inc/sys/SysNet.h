/* SysNet.h */ 
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

#ifndef CCore_inc_sys_SysNet_h
#define CCore_inc_sys_SysNet_h
 
#include <CCore/inc/sys/SysWait.h>
#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/net/UDPoint.h>

namespace CCore {
namespace Sys {

/* classes */

struct UDPSocket;

struct AsyncUDPSocket;

struct AsyncUDPSocketWait;

/* struct UDPSocket */

struct UDPSocket
 {
  // public
  
  struct InResult
   {
    Net::UDPoint src;
    ulen len;
    ErrorType error;
   };
  
  // public
  
  ErrorType open(Net::UDPort udport) noexcept;
  
  ErrorType close() noexcept;
  
  ErrorType outbound(Net::UDPoint dst,PtrLen<const uint8> data) noexcept;
  
  WaitResult wait_in(MSec timeout) noexcept;
  
  WaitResult wait_in(TimeScope time_scope) noexcept;
  
  InResult inbound(PtrLen<uint8> buf) noexcept;
 };

/* struct AsyncUDPSocket */

struct AsyncUDPSocket
 {
  // public
  
  struct AsyncState;
  
  typedef AsyncState * Async;
  
  struct OutResult
   {
    bool pending;
    ErrorType error;
   };
  
  struct InResult
   {
    ErrorType error;
    Net::UDPoint src;
    ulen len;
   };
  
  struct StartInResult
   {
    bool pending;
    InResult result;
   };
  
  // public
  
  ErrorType open(Net::UDPort udport) noexcept;
  
  ErrorType close() noexcept;
  
  OutResult startOutbound(Async async,Net::UDPoint dst,PtrLen<const uint8> data) noexcept;
  
  ErrorType completeOutbound(Async async) noexcept;
  
  StartInResult startInbound(Async async,PtrLen<uint8> buf) noexcept;
  
  InResult completeInbound(Async async) noexcept;
 };

/* struct AsyncUDPSocketWait */

struct AsyncUDPSocketWait
 {
  // public
  
  static const ulen MaxAsyncs = 50 ;
  
  ErrorType init(ulen async_count) noexcept;
  
  void exit() noexcept;
  
  AsyncUDPSocket::Async getAsync(ulen index) noexcept;
  
  bool addWait(ulen index) noexcept;
  
  bool delWait(ulen index) noexcept;
  
  WaitResult wait(MSec timeout) noexcept;
  
  WaitResult wait(TimeScope time_scope) noexcept;
  
  void interrupt() noexcept; // async , semaphore
  
  WaitResult waitAll(MSec timeout) noexcept;
  
  WaitResult waitAll(TimeScope time_scope) noexcept;
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

