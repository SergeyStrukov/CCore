/* SysData.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysData_h
#define CCore_inc_sys_SysData_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Sys {

/* classes */

template <ulen Len> struct SysData;

/* struct SysData<ulen Len> */

template <ulen Len>
struct SysData
 {
  typename std::aligned_storage<Len>::type storage;
  
  void * getMem() { return &storage; }
  
  template <class T>
  T * getObj()
   {
    static_assert( std::is_pod<T>::value ,"CCore::Sys::SysData::getObj<T>() : T must be POD");    
    
    static_assert( sizeof (T) <= Len ,"CCore::Sys::SysData::getObj<T>() : T is too large");
    
    return static_cast<T *>(getMem());
   }
 };

} // namespace Sys
} // namespace CCore
 
#endif
 

