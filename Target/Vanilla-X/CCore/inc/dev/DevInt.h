/* DevInt.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevInt_h
#define CCore_inc_dev_DevInt_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Dev {

/* functions */ 

bool IsIntContext() noexcept;

/* classes */ 

class IntLock;

/* class IntLock */ 

class IntLock : NoCopy
 {
   bool enable;

  public:

   IntLock() { enable=Internal::Disable(); }
 
   ~IntLock() { if( enable ) Internal::Enable(); }
   
   struct Internal
    {
     static bool Disable() noexcept;
     
     static void Enable() noexcept;
    };
 };
 
} // namespace Dev
} // namespace CCore
 
#endif

