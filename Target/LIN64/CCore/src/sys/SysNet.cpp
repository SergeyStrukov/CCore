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

namespace CCore {
namespace Sys {

/* struct UDPSocket */

ErrorType UDPSocket::open(Net::UDPort /*udport*/) noexcept
 {
  // TODO

  return NoError;
 }
  
ErrorType UDPSocket::close() noexcept
 {
  // TODO

  return NoError;
 }
  
ErrorType UDPSocket::outbound(Net::UDPoint /*dst*/,PtrLen<const uint8> /*data*/) noexcept
 {
  // TODO

  return NoError;
 }
  
WaitResult UDPSocket::wait_in(MSec /*timeout*/) noexcept
 {
  // TODO

  return Wait_error;
 }
  
WaitResult UDPSocket::wait_in(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return Wait_error;
 }
  
auto UDPSocket::inbound(PtrLen<uint8> /*buf*/) noexcept -> InResult
 {
  // TODO

  return InResult{};
 }

/* struct AsyncUDPSocket */

ErrorType AsyncUDPSocket::open(Net::UDPort /*udport*/) noexcept
 {
  // TODO

  return NoError;
 }
  
ErrorType AsyncUDPSocket::close() noexcept
 {
  // TODO

  return NoError;
 }
  
auto AsyncUDPSocket::startOutbound(Async /*async*/,Net::UDPoint /*dst*/,PtrLen<const uint8> /*data*/) noexcept -> OutResult
 {
  // TODO

  return OutResult{};
 }
  
ErrorType AsyncUDPSocket::completeOutbound(Async /*async*/) noexcept
 {
  // TODO

  return NoError;
 }
  
auto AsyncUDPSocket::startInbound(Async /*async*/,PtrLen<uint8> /*buf*/) noexcept -> StartInResult
 {
  // TODO

  return StartInResult{};
 }
  
auto AsyncUDPSocket::completeInbound(Async /*async*/) noexcept -> InResult
 {
  // TODO

  return InResult{};
 }

/* struct AsyncUDPSocketWait */
  
ErrorType AsyncUDPSocketWait::init(ulen /*async_count*/) noexcept
 {
  // TODO

  return NoError;
 }
  
void AsyncUDPSocketWait::exit() noexcept
 {
  // TODO
 }
  
AsyncUDPSocket::Async AsyncUDPSocketWait::getAsync(ulen /*index*/) noexcept
 {
  // TODO

  return 0;
 }
  
bool AsyncUDPSocketWait::addWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
bool AsyncUDPSocketWait::delWait(ulen /*index*/) noexcept
 {
  // TODO

  return false;
 }
  
WaitResult AsyncUDPSocketWait::wait(MSec /*timeout*/) noexcept
 {
  // TODO

  return Wait_error;
 }
  
WaitResult AsyncUDPSocketWait::wait(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return Wait_error;
 }
  
void AsyncUDPSocketWait::interrupt() noexcept
 {
  // TODO
 }
  
WaitResult AsyncUDPSocketWait::waitAll(MSec /*timeout*/) noexcept
 {
  // TODO

  return Wait_error;
 }
  
WaitResult AsyncUDPSocketWait::waitAll(TimeScope /*time_scope*/) noexcept
 {
  // TODO

  return Wait_error;
 }

} // namespace Sys
} // namespace CCore
 

