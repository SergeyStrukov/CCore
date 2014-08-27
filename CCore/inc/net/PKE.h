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

#include <CCore/inc/TreeMap.h>
#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

const uint16 MinKeySetLen     = 5 ;
const uint16 DefaultKeySetLen = 10 ;
const uint16 MaxKeySetLen     = 100 ;

const uint32 MinTTL     = 360 ;   // 6 min 
const uint32 DefaultTTL = 3600 ;  // 1 hour
const uint32 MaxTTL     = 36000 ; // 10 hour

const uint32 MinUTL     = 1000000 ;
const uint32 DefaultUTL = 100000000 ;
const uint32 MaxUTL     = 1000000000 ;

const ulen NonceLen = 128 ;

const unsigned StartTickCount = InboundTicksPerSec*1 ; // 1 sec 

const unsigned MaxRetry = 100 ;

const ulen MaxAlgos = 16 ;

const ulen MaxPKETransLen = 1100 ;

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

/* enum PKEType */

enum PKEType : uint16
 {
  PKE_None      = 0,
  PKE_ServerAck = 1,
  PKE_ClientAck,
  PKE_ServerParam,
  PKE_ClientParam,
  PKE_FirstServerSKey,
  PKE_ClientSKey,
  PKE_ServerSKey,
  PKE_Done
 };

/* functions */

AbstractCryptFunc * CreateEncrypt(CryptID crypt_id);

AbstractCryptFunc * CreateDecrypt(CryptID crypt_id);

AbstractHashFunc * CreateHash(HashID hash_id);

AbstractDHGroup * CreateDHGroup(DHGroupID dhg_id);

/* classes */

struct CryptAlgoSelect;

struct SessionKeyParam;

class SessionKey;

struct AbstractClientID;

class ClientID;

struct AbstractClientDataBase;

class HashPrimeKey;

struct NegData;

class ClientNegotiant;

class ServerNegotiant;

/* struct CryptAlgoSelect */

struct CryptAlgoSelect : NoThrowFlagsBase
 {
  uint8 crypt_id = CryptID_AES256 ;
  uint8 hash_id = HashID_SHA512 ;
  uint8 dhg_id = DHGroupID_II ;
  
  // constructors
  
  CryptAlgoSelect() {}
  
  CryptAlgoSelect(CryptID crypt_id_,HashID hash_id_,DHGroupID dhg_id_) 
   : crypt_id(crypt_id_),hash_id(hash_id_),dhg_id(dhg_id_) {}
  
  // methods
  
  bool operator == (const CryptAlgoSelect &obj) const
   {
    return crypt_id==obj.crypt_id && hash_id==obj.hash_id && dhg_id==obj.dhg_id ;
   }
  
  bool operator != (const CryptAlgoSelect &obj) const
   {
    return !(*this==obj);
   }
  
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
  
  SessionKeyParam(uint16 keyset_len_,uint32 ttl_,uint32 utl_) : keyset_len(keyset_len_),ttl(ttl_),utl(utl_) {}
  
  // methods

  bool test() const
   {
    return keyset_len>=MinKeySetLen && keyset_len<=MaxKeySetLen &&
           ttl>=MinTTL && ttl<=MaxTTL &&
           utl>=MinUTL && utl<=MaxUTL ;
   }
  
  void cap()
   {
    keyset_len=Min(MaxKeySetLen,Max(MinKeySetLen,keyset_len));
    ttl=Min(MaxTTL,Max(MinTTL,ttl));
    utl=Min(MaxUTL,Max(MinUTL,utl));
   }
  
  void select(const SessionKeyParam &obj)
   {
    Replace_min(keyset_len,obj.keyset_len);
    Replace_min(ttl,obj.ttl);
    Replace_min(utl,obj.utl);
    
    cap();
   }
  
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

class SessionKey : public MasterKey , public MemBase_nocopy
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

/* struct AbstractClientID */

struct AbstractClientID
 {
  virtual ~AbstractClientID() {}
  
  virtual uint8 getLen() const =0;
  
  virtual void getID(uint8 buf[ /* Len */ ]) const =0;
 };

/* type ClientIDPtr */

using ClientIDPtr = OwnPtr<AbstractClientID> ;

/* class ClientID */

class ClientID : public AbstractClientID , public MemBase_nocopy
 {
   uint8 name[255];
   uint8 len;
   
  private: 

   template <class T>
   void init(PtrLen<T> name);
   
  public:
  
   explicit ClientID(StrLen name);
   
   explicit ClientID(PtrLen<const uint8> name);
   
   virtual ~ClientID();
   
   // AbstractClientID
   
   virtual uint8 getLen() const;
   
   virtual void getID(uint8 buf[ /* Len */ ]) const;
 };

/* type PrimeKeyPtr */

using PrimeKeyPtr = OwnPtr<AbstractHashFunc> ;

/* struct AbstractClientDataBase */

struct AbstractClientDataBase
 {
  virtual ~AbstractClientDataBase() {}
  
  virtual bool findClient(PtrLen<const uint8> client_id,PrimeKeyPtr &client_key,ClientProfilePtr &client_profile)=0;
 };

/* class HashPrimeKey */

class HashPrimeKey : public AbstractHashFunc , public MemBase_nocopy
 {
   template <class Hash> class HashFunc;
  
   OwnPtr<AbstractHashFunc> hash;
   
  public:
  
   HashPrimeKey(HashID hash_id,PtrLen<const uint8> key);
   
   virtual ~HashPrimeKey();
   
   // AbstractHashFunc
   
   virtual ulen getHLen() const;
   
   virtual void add(PtrLen<const uint8> data);
   
   virtual const uint8 * finish();
 };

/* struct NegData */

struct NegData : NoCopy
 {
  // key part
  
  PlatformRandom random;

  XPoint point;
  uint8 server_nonce[NonceLen];
  uint8 client_nonce[NonceLen];
  CryptAlgoSelect algo;
  
  OwnPtr<AbstractCryptFunc> encrypt;
  OwnPtr<AbstractCryptFunc> decrypt;
  OwnPtr<AbstractHashFunc> hash;
  OwnPtr<AbstractDHGroup> dhg;
  
  DirectConvolution direct_conv;
  InverseConvolution inverse_conv;
  
  ulen hlen;
  ulen blen;
  ulen glen;
  
  uint8 gy[MaxGLen];
  uint8 x[MaxGLen];
  uint8 gx[MaxGLen];
  uint8 gxy[MaxGLen];
  
  NegData();
  
  ~NegData();
  
  bool create();
  
  void keyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void clientKeyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void serverKeyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void clientGen();
  
  void serverGen();
  
  BufPutDev start(uint8 *buf,uint16 type);
  
  ulen finish(uint8 *buf,BufPutDev dev);
  
  PKEType process(PtrLen<const uint8> &data);
  
  // skey part
  
  SessionKeyParam param;
  MasterKeyPtr skey;
  PtrLen<uint8> key_buf;
  
  uint32 rep_count;
  uint32 max_count;
  uint32 cur_count;
  
  bool createSKey();
  
  void setCounts(AbstractHashFunc *server_key);
  
  bool testCounts(AbstractHashFunc *server_key);
  
  void keyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void clientKeyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void serverKeyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key);
 };

/* class ClientNegotiant */

class ClientNegotiant : NoCopy
 {
  public:
  
   enum State
    {
     State_Null,
     State_Ready,
     State_Started,
     State_Done
    };
  
  private:
  
   class Proc : NoCopy
    {
      State state = State_Null ;
    
      uint8 client_id_len = 0 ;
      uint8 client_id[255];
      
      PrimeKeyPtr client_key;
      PrimeKeyPtr server_key;
      
      CryptAlgoSelect algo_list[MaxAlgos];
      ulen algo_count = 0 ;
      
      MasterKeyPtr skey;
      
      uint8 send_buf[MaxPKETransLen];
      ulen send_len = 0 ;
      
      typedef bool (Proc::* InboundFunc)(PtrLen<const uint8> data);
      
      InboundFunc inbound_func;
      
      NegData neg_data;
      
     private: 
      
      void build1();
      
      bool test_algo() const;
      
      bool process2(PtrLen<const uint8> data);
      
      void build3();
      
      bool process4(PtrLen<const uint8> data);
      
      void build5();
      
      bool process6(PtrLen<const uint8> data);
      
      void build7();
      
      bool process8(PtrLen<const uint8> data);
      
      void build9();
      
      bool process10(PtrLen<const uint8> data);
      
      bool process11(PtrLen<const uint8> data);
      
     public: 
    
      Proc();
      
      ~Proc();
      
      void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param);
      
      State getState() const { return state; }
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      bool inbound(PtrLen<const uint8> data);
      
      PtrLen<const uint8> getSendData() const { return Range(send_buf,send_len); }
      
      void getSessionKey(MasterKeyPtr &skey_) { Swap(skey,skey_); }
    };
  
   class Engine : NoCopy , PacketEndpointDevice::InboundProc
    {
      PacketEndpointDevice *dev;
      
      PacketFormat outbound_format;
      
      Function<void (void)> done_func;
      
      PacketSet<uint8> pset;
      
      mutable Mutex mutex;
      
      Proc proc;
      
      unsigned tick_count = 0 ;
      unsigned retry_count = 0 ;
      
     private:
      
      Packet<uint8> prepare_send();
      
      // InboundProc
    
      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);
     
      virtual void tick();
    
     public:
    
      Engine(PacketEndpointDevice *dev,Function<void (void)> done_func);
      
      ~Engine();
      
      void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param);
      
      State getState() const;
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      void getSessionKey(MasterKeyPtr &skey);
    };
  
  private:
  
   ObjHook hook;
   
   Engine engine;
  
  public:
  
   ClientNegotiant(StrLen ep_dev_name,Function<void (void)> done_func);
   
   ~ClientNegotiant();
   
   void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param={}) { engine.prepare(client_id,client_key,server_key,param); }
   
   State getState() const { return engine.getState(); }
   
   void start(PtrLen<const CryptAlgoSelect> algo_list) { engine.start(algo_list); }
   
   template <class ... TT>
   void start(TT ... tt)
    {
     CryptAlgoSelect algo_list[]={tt...};
     
     start(Range_const(algo_list));
    }
   
   void getSessionKey(MasterKeyPtr &skey) { return engine.getSessionKey(skey); }
 };

/* class ServerNegotiant */

class ServerNegotiant : NoCopy
 {
   class Engine;
  
   class Proc : NoCopy
    {
      Engine *engine;
      
      uint8 send_buf[MaxPKETransLen];
      ulen send_len = 0 ;
      
      uint8 final_send_buf[MaxPKETransLen];
      ulen final_send_len = 0 ;
      
      unsigned tick_count = 0 ;
      unsigned retry_count = 0 ;
      
      enum InboundResult
       {
        InboundDrop,
        InboundOk,
        InboundLast,
        InboundFinal
       };
      
      typedef InboundResult (Proc::* InboundFunc)(PtrLen<const uint8> data);
      
      InboundFunc inbound_func;
      
      uint8 client_id_len = 0 ;
      uint8 client_id[255];
      
      PrimeKeyPtr client_key;
      ClientProfilePtr client_profile;
      
      NegData neg_data;
      
      SessionKeyParam param;
      MasterKeyPtr skey;
      PtrLen<uint8> key_buf;
      
     private:
      
      bool process1(XPoint point,PtrLen<const uint8> data);
      
      void build2();
      
      InboundResult process3(PtrLen<const uint8> data);
      
      void build4();
      
      InboundResult process5(PtrLen<const uint8> data);
      
      void build6();
      
      InboundResult process7(PtrLen<const uint8> data);
      
      void build8();
      
      InboundResult process9(PtrLen<const uint8> data);
      
      void build10();
      
      void build11();
      
      InboundResult process_final(PtrLen<const uint8> data);
      
     public:
    
      explicit Proc(Engine *engine);
      
      ~Proc();
      
      bool inbound_first(XPoint point,PtrLen<const uint8> data,PacketList &list); // true to del
      
      void inbound(PtrLen<const uint8> data,PacketList &list);
      
      bool tick(PacketList &list); // true to del
    };
  
   class Engine : NoCopy , PacketMultipointDevice::InboundProc
    {
      PacketMultipointDevice *dev;
      
      PacketFormat outbound_format;
      
      AbstractClientDataBase &client_db;
      PrimeKeyPtr server_key;
      AbstractEndpointManager &epman;
      ulen max_clients;
      unsigned final_tick_count;
      
      SessionKeyParam param;
      
      PacketSet<uint8> pset;
      
      Mutex mutex;
      
      bool enable = false ;
      
      DynArray<CryptAlgoSelect> algo_list;
      bool algo_filter = false ;
      
      RadixTreeMap<XPoint,Proc> map;
      
      friend class Proc;
      
     private:
      
      bool filter(const CryptAlgoSelect &algo) const;
      
      void prepare_send(XPoint point,PtrLen<const uint8> send_data,PacketList &list);
      
      void send(PacketList &list);
      
      // InboundProc
    
      virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);
     
      virtual void tick();
    
     public:
    
      Engine(PacketMultipointDevice *dev,AbstractClientDataBase &client_db,AbstractEndpointManager &epman,ulen max_clients,MSec final_timeout);
      
      ~Engine();
      
      void prepare(PrimeKeyPtr &server_key,SessionKeyParam param);
      
      void start();
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
    };
  
  private:
  
   ObjHook hook;
   
   Engine engine;
  
  public:

   static const ulen DefaultMaxClients = 10000 ;

   ServerNegotiant(StrLen mp_dev_name,AbstractClientDataBase &client_db,AbstractEndpointManager &epman,ulen max_clients=DefaultMaxClients,MSec final_timeout=5_sec);
   
   ~ServerNegotiant();
   
   void prepare(PrimeKeyPtr &server_key,SessionKeyParam param={}) { engine.prepare(server_key,param); }
   
   void start() { engine.start(); }
   
   void start(PtrLen<const CryptAlgoSelect> algo_list) { engine.start(algo_list); }
   
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
 

