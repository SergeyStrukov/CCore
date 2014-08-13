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

#include <CCore/inc/net/PacketEndpointDevice.h>
#include <CCore/inc/PacketSet.h>

#include <CCore/inc/net/PSecCore.h>

#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/ObjHost.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

const ulen DefaultKeySetLen = 10 ;

const uint32 DefaultTTL = 3600 ; // 1 hour

const uint32 DefaultUTL = 100000000 ;

const ulen NonceLen = 128 ;

constexpr MSec RetryTimeout = 1_sec ;

const unsigned MaxRetry = 100 ;

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

struct AbstractClientId;

class ClientNegotiant;

struct AbstractClientProfile;

struct AbstractClientDataBase;

struct AbstractEndpointManager;

class ServerNegotiant;

/* struct CryptAlgoSelect */

struct CryptAlgoSelect
 {
  uint8 crypt_id = CryptID_AES256 ;
  uint8 hash_id = HashID_SHA512 ;
  uint8 dhg_id = DHGroupID_II ;
  
  // constructors
  
  CryptAlgoSelect() {}
  
  CryptAlgoSelect(CryptID crypt_id_,HashID hash_id_,DHGroupID dhg_id_) 
   : crypt_id(crypt_id_),hash_id(hash_id_),dhg_id(dhg_id_) {}
  
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
   struct CreateCryptCtx;
   struct CreateHashCtx;
   struct CreateKeyGenCtx;
   
   static ulen GetKLen(CryptAlgoSelect algo_select);
   
   static ulen GetHLen(CryptAlgoSelect algo_select);
   
   static ulen GetSecretLen(CryptAlgoSelect algo_select,ulen klen);
   
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

/* struct AbstractClientId */

struct AbstractClientId : MemBase_nocopy
 {
  virtual ~AbstractClientId() {}
  
  virtual uint8 getLen() const =0;
  
  virtual void getId(uint8 buf[ /* Len */ ]) const =0;
 };

/* type PrimeKey */

using PrimeKey = OwnPtr<AbstractHashFunc> ;

/* type ClientId */

using ClientId = OwnPtr<AbstractClientId> ;

/* type */

using SKey = OwnPtr<MasterKey> ;

/* class ClientNegotiant */

class ClientNegotiant : NoCopy
 {
  public:
  
   enum State
    {
     State_Ready,
     State_Started,
     State_Done
    };
  
  private:
  
   class Proc : NoCopy
    {
     public: 
    
      Proc(ClientId &client_id,PrimeKey &client_key,PrimeKey &server_key);
      
      ~Proc();
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      bool inbound(PtrLen<const uint8> data);
      
      PtrLen<const uint8> getSendData() const;
    };
  
   class Engine : NoCopy , PacketEndpointDevice::InboundProc
    {
      PacketEndpointDevice *dev;
      
      Mutex mutex;
      
      Proc proc;
      SecTimer timer;
      unsigned retry_count;
      
     private:
      
      // InboundProc
    
      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
     
      virtual void tick();
    
     public:
    
      Engine(PacketEndpointDevice *dev,ClientId &client_id,PrimeKey &client_key,PrimeKey &server_key);
      
      ~Engine();
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      State getState() const;
      
      State wait(MSec timeout);
      
      State wait(TimeScope time_scope);
      
      void getSessionKey(SKey &skey);
    };
  
  private:
  
   ObjHook hook;
   
   Engine engine;
  
  public:
  
   ClientNegotiant(StrLen ep_dev_name,ClientId &client_id,PrimeKey &client_key,PrimeKey &server_key);
   
   ~ClientNegotiant();
   
   void start(PtrLen<const CryptAlgoSelect> algo_list) { engine.start(algo_list); }
   
   template <class ... TT>
   void start(TT ... tt)
    {
     CryptAlgoSelect algo_list[]={tt...};
     
     start(Range_const(algo_list));
    }
   
   State getState() const { return engine.getState(); }
   
   State wait(MSec timeout) { return engine.wait(timeout); }
   
   State wait(TimeScope time_scope) { return engine.wait(time_scope); }
   
   void getSessionKey(SKey &skey) { return engine.getSessionKey(skey); }
 };

/* struct AbstractClientProfile */

struct AbstractClientProfile : MemBase_nocopy
 {
  virtual ~AbstractClientProfile() {}
 };

/* type ClientProfile */

using ClientProfile = OwnPtr<AbstractClientProfile> ; 

/* struct AbstractClientDataBase */

struct AbstractClientDataBase : MemBase_nocopy
 {
  virtual ~AbstractClientDataBase() {}
  
  virtual bool findClient(PtrLen<const uint8> client_id,PrimeKey &client_key,ClientProfile &client_profile) =0;
 };

/* struct AbstractEndpointManager */

struct AbstractEndpointManager : MemBase_nocopy
 {
  virtual ~AbstractEndpointManager() {}

  virtual ulen getBufLen() const =0; 
  
  virtual StrLen createName(char buf[ /* BufLen */ ]) =0;
  
  virtual void open(StrLen ep_dev_name,SKey &skey,ClientProfile &client_profile) =0;
 };

/* class ServerNegotiant */

class ServerNegotiant : NoCopy
 {
  public:
  
   ServerNegotiant(StrLen mp_dev_name,AbstractClientDataBase &client_db,PrimeKey &server_key,AbstractEndpointManager &epman,MSec final_timeout=5_sec);
   
   ~ServerNegotiant();
   
   void start();
   
   void start(PtrLen<const CryptAlgoSelect> algo_list);
   
   template <class ... TT>
   void start(TT ... tt)
    {
     CryptAlgoSelect algo_list[]={tt...};
     
     start(Range_const(algo_list));
    }
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 

