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
 
namespace CCore {
namespace Dev {

/* classes */

class EthControl;

/* class EthControl */

class EthControl : NoCopy
 {
  private:
  
   static void InitControl();
   
   static void InitPRMC();
   
   static void InitEth();
  
  public:
  
   EthControl();
   
   ~EthControl();
 };

} // namespace Dev
} // namespace CCore
 
#endif


