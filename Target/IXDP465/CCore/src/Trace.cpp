/* Trace.cpp */ 
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
 
#include <CCore/inc/Trace.h>

#include <CCore/inc/dev/DevSerial.h>
 
namespace CCore {

/* functions */ 

void Trace(StrLen str) { Dev::SerialPollOut(Dev::Serial_0,str);  }
 
} // namespace CCore
 

