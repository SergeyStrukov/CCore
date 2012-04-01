/* DevSignal.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevSignal_h
#define CCore_inc_dev_DevSignal_h

namespace CCore {
namespace Dev {

/* enum Signal */ 

enum Signal
 {
  Signal_0,
  Signal_1,
  Signal_2,
  Signal_3,
  Signal_4,
  Signal_5,
  Signal_6,
  Signal_7
 };
 
/* functions */ 

void EnableSignal(Signal s);

void DisableSignal(Signal s);

void SetSignal(Signal s,bool value);

void SetSignal(Signal s);
 
void ClearSignal(Signal s);

} // namespace Dev
} // namespace CCore
 
#endif




