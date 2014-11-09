/* DevEth.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevEth_h
#define CCore_inc_dev_DevEth_h

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/net/NetBase.h>
#include <CCore/inc/InstanceLock.h>
 
namespace CCore {
namespace Dev {

/* classes */

class EthControl;

/* class EthControl */

class EthControl : InstanceLock<EthControl>
 {
   Net::MACAddress address1;
   Net::MACAddress address2;
 
  private:
   
   static Net::MACAddress MakeAddress(uint32 hi,uint32 lo);
  
   void connect();
   
   void enable();
   
   void reset();
   
   void disable();
   
  public:
  
   EthControl();
   
   ~EthControl();
   
   const Net::MACAddress & getAddress1() const { return address1; }
   
   const Net::MACAddress & getAddress2() const { return address2; }
 };

} // namespace Dev
} // namespace CCore
 
#endif


