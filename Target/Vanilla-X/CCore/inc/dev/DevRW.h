/* DevRW.h */ 
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

#ifndef CCore_inc_dev_DevRW_h
#define CCore_inc_dev_DevRW_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Dev {

/* types */  

typedef uint32 AddressType;
   
/* functions */ 

template <class UInt>
UInt VarGet(const void *ptr) noexcept;

template <class UInt>
void VarSet(void *ptr,UInt value) noexcept;

template <class UInt>
UInt VarGet(AddressType address) { return VarGet<UInt>((const void *)address); }
 
template <class UInt>
void VarSet(AddressType address,UInt value) { VarSet<UInt>((void *)address,value); }
 
/* classes */ 

class RegRW;

/* class RegRW */ 

class RegRW
 {
   AddressType base_address;
 
  public:
  
   explicit RegRW(AddressType base_address_) : base_address(base_address_) {}
   
   template <class UInt>
   UInt get(uint32 address) { return VarGet<UInt>(base_address+address); }
   
   template <class UInt>
   void set(uint32 address,UInt value) { VarSet<UInt>(base_address+address,value); }
 };
 
} // namespace Dev
} // namespace CCore
 
#endif
 

