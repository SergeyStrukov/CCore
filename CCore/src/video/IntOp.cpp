/* IntOp.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/video/IntOp.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Video {

/* guard functions */

void IntGuardAssert()
 {
  Printf(Exception,"CCore::Video::IntGuard(...) : integer operation fault");
 }

} // namespace Video
} // namespace CCore
 

