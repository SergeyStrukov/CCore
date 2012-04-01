/* UIntMax.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_UIntMax_h
#define CCore_inc_gadget_UIntMax_h
 
#include <CCore/inc/gadget/Meta.h>

namespace CCore {

/* classes */

struct UIntMax;

/* struct UIntMax */

struct UIntMax
 {
  constexpr UIntMax() {}
   
  template <class UInt>
  constexpr operator UInt() const 
   { 
    static_assert( Meta::IsUInt<UInt>::Ret ,"UIntMax::operator UInt() : UInt must be an unsigned integral type");
     
    return UInt(-1); 
   }
 };

} // namespace CCore
 
#endif
 

