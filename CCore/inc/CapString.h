/* CapString.h */ 
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

#ifndef CCore_inc_CapString_h
#define CCore_inc_CapString_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */

template <ulen MaxLen=TextBufLen> class CapString;

/* class CapString<ulen MaxLen> */

template <ulen MaxLen> 
class CapString : NoCopy
 {
   static_assert( MaxLen>0 ,"CCore::CapString<MaxLen> : MaxLen must be > 0");
 
   char buf[MaxLen+1];
   
  public:
   
   explicit CapString(StrLen str)
    {
     Replace_min(str.len,MaxLen); // cap length
    
     str.copyTo(buf);
    
     buf[str.len]=0;
    }
   
   operator const char * () const { return buf; }
 };

} // namespace CCore
 
#endif
 

