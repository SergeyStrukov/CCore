/* MD5.h */ 
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

#ifndef CCore_inc_crypton_MD5_h
#define CCore_inc_crypton_MD5_h
 
#include <CCore/inc/crypton/HashFunction.h>

namespace CCore {
namespace Crypton {

/* classes */

struct MD5Core;

/* struct MD5Core */

struct MD5Core
 {
  // consts
  
  static const ulen BlockWordLen = 16 ;
  static const ulen BlockLen = BlockWordLen*4 ;
  static const ulen TailLen = 8 ;
  static const ulen DigestLen = 16 ;
  
  static const char * GetName() { return "MD5"; }
  
  // data
  
  struct State
   {
    uint32 A;
    uint32 B;
    uint32 C;
    uint32 D;
    
    static uint32 Func1(uint32 x,uint32 y,uint32 z);
    static uint32 Func2(uint32 x,uint32 y,uint32 z);
    static uint32 Func3(uint32 x,uint32 y,uint32 z);
    static uint32 Func4(uint32 x,uint32 y,uint32 z);
    
    static void Round1(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift); 
    static void Round2(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift); 
    static void Round3(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift); 
    static void Round4(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift);
    
    static void Round1(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen]);
    static void Round2(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen]);
    static void Round3(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen]);
    static void Round4(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen]);
    
    void reset();
    
    void forget()
     {
      Forget(A);
      Forget(B);
      Forget(C);
      Forget(D);
     }
    
    void step(const uint32 X[BlockWordLen]);
    
    void step(const uint8 buf[BlockLen]);
    
    void finish(uint8 digest[DigestLen]);
   };
  
  State state;
  
  struct Buf
   {
    uint8 buf[BlockLen];
    unsigned len;
    
    uint64 bitlen;
    
    void reset();
    
    void forget()
     {
      Forget(buf);
      Forget(len);
      Forget(bitlen);
     }
    
    template <class Func>
    void add(PtrLen<const uint8> data,Func func);
    
    template <class Func>
    void finish(Func func);
   };
  
  Buf buf;

  // methods
  
  void reset();
  
  void forget() 
   {
    state.forget();
    buf.forget();
   }
  
  void add(const uint8 *data,ulen len);
  
  void finish(uint8 digest[DigestLen]);
 };

/* types */

using MD5 = HashFunction<MD5Core> ;

using KeyedMD5 = KeyedHashFunction<MD5Core> ;

} // namespace Crypton
} // namespace CCore
 
#endif
 

