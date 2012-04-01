/* IXP465.CP15.h */ 
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

#ifndef CCore_inc_dev_IXP465_CP15_h
#define CCore_inc_dev_IXP465_CP15_h

#include <CCore/inc/dev/IXP465.h>

namespace IXP465 {
namespace CP15 {

/* IXP465.CP15.desc -> IXP465.CP15.gen.h */ 

#include <CCore/inc/dev/IXP465.CP15.gen.h>

/* CP15 */ 

Type_ID Get_ID() noexcept;
  
Type_CacheType Get_CacheType() noexcept;

Type_Control Get_Control() noexcept;

void Set_Control(Type_Control value) noexcept;

Type_AuxControl Get_AuxControl() noexcept;

void Set_AuxControl(Type_AuxControl value) noexcept;

Type_TTBase Get_TTBase() noexcept;

void Set_TTBase(Type_TTBase value) noexcept;

Type_DomainAC Get_DomainAC() noexcept;

void Set_DomainAC(Type_DomainAC value) noexcept;

Type_PID Get_PID() noexcept;

void Set_PID(Type_PID value) noexcept;

void Wait() noexcept;

} // namespace CP15 
} // namespace IXP465
 
#endif

