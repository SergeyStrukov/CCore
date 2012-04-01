/* NoCopy.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_NoCopy_h
#define CCore_inc_gadget_NoCopy_h
 
namespace CCore {

/* classes */ 

struct NoCopyType;

template <class ... TT> struct ImpNoCopyBase;
 
/* struct NoCopyType */ 

struct NoCopyType
 {
  NoCopyType() = default ;
  
  NoCopyType(const NoCopyType &) = delete ;
   
  void operator = (const NoCopyType &) = delete ;
 };
 
/* struct ImpNoCopyBase<TT> */

template <class ... TT> 
struct ImpNoCopyBase : TT ...
 {
  ImpNoCopyBase() = default ;
    
  ImpNoCopyBase(const ImpNoCopyBase &) = delete ;
   
  void operator = (const ImpNoCopyBase &) = delete ;
 };

/* type NoCopyBase<TT> */
 
template <class ... TT>
using NoCopyBase = ImpNoCopyBase<TT...> ;

/* type NoCopy */ 
 
typedef NoCopyType NoCopy; 
 
} // namespace CCore
 
#endif
 

