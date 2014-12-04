/* CreateAt.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_CreateAt_h
#define CCore_inc_gadget_CreateAt_h

#include <CCore/inc/gadget/Place.h>
 
namespace CCore {

/* CreateAt() */

template <class T,class ... SS>
void CreateAt(T &obj,SS && ... ss)
 {
  new(PlaceAt(&obj)) T( std::forward<SS>(ss)... );
 }

} // namespace CCore
 
#endif
 

