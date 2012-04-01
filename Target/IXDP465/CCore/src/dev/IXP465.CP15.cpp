/* IXP465.CP15.cpp */ 
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

#include <CCore/inc/dev/IXP465.CP15.h>

namespace IXP465 {
namespace CP15 {

/* CP15 */

#if 0

 // Fake code

Type_ID Get_ID() noexcept { return Type_ID(); }
  
Type_CacheType Get_CacheType() noexcept { return Type_CacheType(); }
 
Type_Control Get_Control() noexcept { return Type_Control(); }
 
void Set_Control(Type_Control) noexcept {}
 
Type_AuxControl Get_AuxControl() noexcept { return Type_AuxControl(); }
 
void Set_AuxControl(Type_AuxControl) noexcept {}
 
Type_TTBase Get_TTBase() noexcept { return Type_TTBase(); }
 
void Set_TTBase(Type_TTBase) noexcept {}
 
Type_DomainAC Get_DomainAC() noexcept { return Type_DomainAC(); }
 
void Set_DomainAC(Type_DomainAC) noexcept {}
 
Type_PID Get_PID() noexcept { return Type_PID(); }
 
void Set_PID(Type_PID) noexcept {}
 
void Wait() noexcept {}
 
#endif
 
} // namespace CP15 
} // namespace IXP465
 
