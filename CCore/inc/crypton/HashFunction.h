/* HashFunction.h */ 
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

#ifndef CCore_inc_crypton_HashFunction_h
#define CCore_inc_crypton_HashFunction_h
 
#include <CCore/inc/crypton/Forget.h>

namespace CCore {
namespace Crypton {

/* functions */

void GuardNoHashKey();

/* classes */

template <class T> class HashFunction;

template <class T,ulen L=T::DigestLen> class KeyedHashFunction;

/* class HashFunction<T> */

template <class T> 
class HashFunction : NoCopy
 {
  public:
 
   // length in octets
 
   static const ulen DigestLen = T::DigestLen ;
   
   static const ulen BlockLen  = T::BlockLen ;
  
   static const char * GetName() { return T::GetName(); }

  private:
   
   T func;
   
  public:
   
   // constructors
   
   HashFunction() { reset(); }
   
   ~HashFunction() { func.forget(); }
   
   // methods
   
   void reset() { func.reset(); }
   
   void add(const uint8 *data,ulen len) { func.add(data,len); }
   
   void add(PtrLen<const uint8> data) { add(data.ptr,data.len); }
   
   void finish(uint8 digest[DigestLen]) { func.finish(digest); func.reset(); }
 };

/* class KeyedHashFunction<T,L> */

template <class T,ulen L> 
class KeyedHashFunction : NoCopy
 {
  public:

   // length in octets

   static const ulen DigestLen = L ;
   
   static const ulen BlockLen  = T::BlockLen ;
 
   static const char * GetName() { return T::GetName(); }
   
  private:
   
   static const ulen DLen = T::DigestLen ;
   
   static_assert( DigestLen<=DLen ,"CCore::Crypton::KeyedHashFunction<T,L> : L > T::DigestLen");
   static_assert( DLen<=BlockLen ,"CCore::Crypton::KeyedHashFunction<T,L> : T::DigestLen > T::BlockLen");
   
  private:
   
   T hash1start;
   T hash2start;
   T hash1;
   bool ok;
   
  private: 
   
   void guardKey() const
    {
     if( !ok ) GuardNoHashKey();
    }
   
   void clean()
    {
     hash1start.forget();
     hash2start.forget();
     hash1.forget();
     
     ok=false;
    }
   
   static void Mask(uint8 *restrict dst/* [BlockLen] */,const uint8 *src,ulen src_len,uint8 mask)
    {
     for(auto s=Range(src,src_len); +s ;++s,++dst) *dst=(*s)^mask;
     
     Range(dst,BlockLen-src_len).set(mask);
    }
   
   static void Init(uint8 (&key1)[BlockLen],uint8 (&key2)[BlockLen],const uint8 *key,ulen key_len)
    {
     Mask(key1,key,key_len,0x36);
     Mask(key2,key,key_len,0x5C);
    }

   static void Init_long(uint8 (&key1)[BlockLen],uint8 (&key2)[BlockLen],const uint8 *key,ulen key_len)
    {
     uint8 key0[DLen];
     
     T hash;
     
     hash.reset();
     
     hash.add(key,key_len);
     
     hash.finish(key0);
     
     Init(key1,key2,key0,DLen);
     
     Forget(key0);
     hash.forget();
    }
   
  public:
   
   // constructors
  
   KeyedHashFunction() { clean(); }
  
   ~KeyedHashFunction() { clean(); }
  
   KeyedHashFunction(const uint8 *key_,ulen key_len) { clean(); key(key_,key_len); }
   
   explicit KeyedHashFunction(PtrLen<const uint8> key_) { clean(); key(key_); }
   
   // methods
   
   void key(const uint8 *key,ulen key_len)
    {
     uint8 key1[BlockLen];
     uint8 key2[BlockLen];
     
     if( key_len<=BlockLen )
       {
        Init(key1,key2,key,key_len);
       }
     else
       {
        Init_long(key1,key2,key,key_len);
       }

     hash1start.reset();
     hash2start.reset();
     
     hash1start.add(key1,BlockLen);
     hash2start.add(key2,BlockLen);
     
     hash1=hash1start;
     
     ok=true;
    }
   
   void key(PtrLen<const uint8> key_) { key(key_.ptr,key_.len); }
   
   void unkey() { clean(); }
   
   void reset() 
    {
     guardKey();
     
     hash1=hash1start;
    }
  
   void add(const uint8 *data,ulen len)
    {
     guardKey();

     hash1.add(data,len);
    }
  
   void add(PtrLen<const uint8> data) { add(data.ptr,data.len); }
  
   void finish(uint8 digest[DigestLen])
    {
     guardKey();
     
     // digest1
     
     uint8 digest1[DLen];

     hash1.finish(digest1);
     
     // digest2

     uint8 digest2[DLen];
     
     T hash2;
     
     hash2=hash2start;
     
     hash2.add(digest1,DLen);
     
     hash2.finish(digest2);
     
     // digest
     
     Range(digest,DigestLen).copy(digest2);
     
     hash1=hash1start;
     
     Forget(digest1);
     Forget(digest2);
     hash2.forget();
    }
 };

} // namespace Crypton
} // namespace CCore
 
#endif
 

