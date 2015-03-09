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

template <ulen Len=TextBufLen> class CapString;

/* class CapString<ulen Len> */

template <ulen Len> 
class CapString : NoCopy
 {
   static_assert( Len>1 ,"CCore::CapString<Len> : Len must be > 1");
 
   char buf[Len];
   
  public:
   
   explicit CapString(StrLen str)
    {
     Replace_min<ulen>(str.len,Len-1); // cap length
    
     str.copyTo(buf);
    
     buf[str.len]=0;
    }
   
   operator const char * () const { return buf; }
 };

} // namespace CCore
 
#endif
 

