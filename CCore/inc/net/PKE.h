/* PKE.h */ 
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

#ifndef CCore_inc_net_PKE_h
#define CCore_inc_net_PKE_h

#include <CCore/inc/net/PSecCore.h>

#include <CCore/inc/SaveLoad.h>
 
namespace CCore {
namespace Net {
namespace PSec {

/* consts */

const ulen DefaultKeySetLen = 10 ;

const uint32 DefaultTTL = 3600 ; // 1 hour

const uint32 DefaultUTL = 100000000 ; 

/* enum CryptID */

enum CryptID : uint8
 {
  CryptID_AES128,
  CryptID_AES192,
  CryptID_AES256
  
  // may be continued
 };

/* enum HashID */

enum HashID : uint8
 {
  HashID_SHA1,
  HashID_SHA224,
  HashID_SHA256,
  HashID_SHA384,
  HashID_SHA512
  
  // may be continued
 };

/* enum DHGroupID */

enum DHGroupID : uint8
 {
  DHGroupID_I,
  DHGroupID_II
  
  // may be continued
 };

/* classes */

struct CryptAlgoSelect;

struct SessionKeyParam;

class SessionKey;

/* struct CryptAlgoSelect */

struct CryptAlgoSelect
 {
  uint8 crypt_id = CryptID_AES256 ;
  uint8 hash_id = HashID_SHA512 ;
  uint8 dhg_id = DHGroupID_II ;
  
  // constructors
  
  CryptAlgoSelect() {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<uint8,uint8,uint8>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(crypt_id,hash_id,dhg_id);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(crypt_id,hash_id,dhg_id);
   }
 };

/* struct SessionKeyParam */

struct SessionKeyParam
 {
  uint16 keyset_len = DefaultKeySetLen ;
  uint32 ttl = DefaultTTL ;
  uint32 utl = DefaultUTL ;
  
  // constructors
  
  SessionKeyParam() {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<uint16,uint32,uint32>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(keyset_len,ttl,utl);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(keyset_len,ttl,utl);
   }
 };

/* class SessionKey */

class SessionKey : public MasterKey
 {
   static const ulen RandomWarpLen = 128 ;
  
   CryptAlgoSelect algo_select;
   SessionKeyParam param;
   
   ulen klen;
   ulen ktotal;
   ulen secret_len;
   
   DynArray<uint8> key_buf;

  private:

   struct GetKLenCtx;
   struct GetHLenCtx;
   struct GetSecretLenCtx;
   
   static ulen GetKLen(CryptAlgoSelect algo_select);
   
   static ulen GetHLen(CryptAlgoSelect algo_select);
   
   static ulen GetSecretLen(CryptAlgoSelect algo_select,ulen klen);
   
  private: 
   
   template <class T>
   static AbstractCryptFunc * CreateCrypt() { return new CryptFunc<T>(); } 
   
   template <class T>
   static AbstractHashFunc * CreateHash() { return new HashFunc<T>(); }
   
   template <class T>
   AbstractKeyGen * createKeyGen(OwnPtr<AbstractHashFunc> &hash) const
    {
     auto *ret=new KeyGen<T>(hash,klen);
     
     ret->takeSecret().copy(key_buf.getPtr()+ktotal);
     
     return ret;
    }
   
  public:
  
   SessionKey(CryptAlgoSelect algo_select,SessionKeyParam param);
   
   virtual ~SessionKey();
   
   PtrLen<uint8> takeKeyBuf() { return Range(key_buf); }
   
   // MasterKey
   
   // factory

   virtual AbstractCryptFunc * createEncrypt() const;
   
   virtual AbstractCryptFunc * createDecrypt() const;
   
   virtual AbstractHashFunc * createHash() const;
   
   virtual AbstractKeyGen * createKeyGen() const;
   
   virtual AbstractRandomGen * createRandom() const;
   
   // keys
   
   virtual ulen getKLen() const;
   
   virtual LifeLim getLifeLim() const;
   
   virtual void getKey0(uint8 key[ /* KLen */ ]) const;
   
   virtual ulen getKeySetLen() const;
   
   virtual void getKey(ulen index,uint8 key[ /* KLen */ ]) const;
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 

