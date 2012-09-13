/* IntelAES.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_IntelAES_h
#define CCore_inc_crypton_IntelAES_h

#include <CCore/inc/crypton/AES.h>
#include <CCore/inc/Swap.h>

namespace CCore {
namespace Crypton {

/* functions */

bool DetectIntelAES();

void GuardIntelAESNotAvailable();

inline void GuardIntelAES()
 {
  if( !DetectIntelAES() ) GuardIntelAESNotAvailable();
 }

/* classes */

template <class T,class S> struct IntelAESBase;

template <class T,class S> struct IntelAESInverseBase;

struct IntelAES128Func;

struct IntelAES192Func;

struct IntelAES256Func;

struct IntelAESInverse128Func;

struct IntelAESInverse192Func;

struct IntelAESInverse256Func;

/* struct IntelAESBase<T,S> */

template <class T,class S> 
struct IntelAESBase : T
 {
  using T::round_key;
  using T::BlockLen;
  
  IntelAESBase() { GuardIntelAES(); }
  
  void apply(const uint8 *src,uint8 *restrict dst) const
   {
    Range(dst,BlockLen).copy(src);
    
    apply(dst);
   }
   
  void apply(uint8 *src_dst) const
   {
    S::Intel(round_key,src_dst);
   }
 };

/* struct IntelAESInverseBase<T,S> */

template <class T,class S> 
struct IntelAESInverseBase : T
 {
  using T::round_key;
  using T::BlockLen;
  using T::Rounds;
  using T::MixColumnsInverse;
 
  IntelAESInverseBase() { GuardIntelAES(); }
  
  static void SwapBlocks(uint8 *ptr1,uint8 *ptr2)
   {
    for(ulen cnt=BlockLen; cnt ;cnt--,ptr1++,ptr2++) Swap(*ptr1,*ptr2);
   }

  void key(const uint8 *src)
   {
    T::key(src);
    
    for(ulen i=1; i<Rounds ;i++)
      {
       MixColumnsInverse(round_key+BlockLen*i);
      }
    
    for(ulen i=0; i<(Rounds+1)/2 ;i++)
      {
       uint8 *ptr1=round_key+BlockLen*i; 
       uint8 *ptr2=round_key+BlockLen*(Rounds-i);
       
       SwapBlocks(ptr1,ptr2);
      }
   }
  
  void apply(const uint8 *src,uint8 *restrict dst) const
   {
    Range(dst,BlockLen).copy(src);
    
    apply(dst);
   }
   
  void apply(uint8 *src_dst) const
   {
    S::Intel(round_key,src_dst);
   }
 };

/* struct IntelAES128Func */

struct IntelAES128Func : IntelAESBase<AES<AES128Param>,IntelAES128Func> 
 {
  static const char * GetName() { return "IntelAES128"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* struct IntelAES192Func */

struct IntelAES192Func : IntelAESBase<AES<AES192Param>,IntelAES192Func>
 {
  static const char * GetName() { return "IntelAES192"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* struct IntelAES256Func */

struct IntelAES256Func : IntelAESBase<AES<AES256Param>,IntelAES256Func> 
 {
  static const char * GetName() { return "IntelAES256"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* struct IntelAESInverse128Func */

struct IntelAESInverse128Func : IntelAESInverseBase<AESInverse<AES128Param>,IntelAESInverse128Func>
 {
  static const char * GetName() { return "IntelAESInverse128"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* struct IntelAESInverse192Func */

struct IntelAESInverse192Func : IntelAESInverseBase<AESInverse<AES192Param>,IntelAESInverse192Func>
 {
  static const char * GetName() { return "IntelAESInverse192"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* struct IntelAESInverse256Func */

struct IntelAESInverse256Func : IntelAESInverseBase<AESInverse<AES256Param>,IntelAESInverse256Func>
 {
  static const char * GetName() { return "IntelAESInverse256"; }
  
  static void Intel(const uint8 *round_key,uint8 *block);
 };

/* types */

typedef BlockCipher<IntelAES128Func> IntelAES128;

typedef BlockCipher<IntelAES192Func> IntelAES192;

typedef BlockCipher<IntelAES256Func> IntelAES256;

typedef BlockCipher<IntelAESInverse128Func> IntelAESInverse128;

typedef BlockCipher<IntelAESInverse192Func> IntelAESInverse192;

typedef BlockCipher<IntelAESInverse256Func> IntelAESInverse256;

} // namespace Crypton
} // namespace CCore
 
#endif
 

