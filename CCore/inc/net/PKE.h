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

const ulen MaxClientIDLen = 255 ;

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
  PKE_Done,
  
  PKE_ServerError = 100,
  PKE_ClientError = 101
 };

/* functions */

bool IsValid(CryptID crypt_id);

bool IsValid(HashID hash_id);

bool IsValid(DHGroupID dhg_id);

AbstractCryptFunc * CreateEncrypt(CryptID crypt_id);

AbstractCryptFunc * CreateDecrypt(CryptID crypt_id);

AbstractHashFunc * CreateHash(HashID hash_id);

AbstractHashFunc * CreateKeyedHash(HashID hash_id,PtrLen<const uint8> key);

AbstractDHGroup * CreateDHGroup(DHGroupID dhg_id);

ulen GetKLen(CryptID crypt_id);

ulen GetHLen(HashID hash_id);

ulen GetGLen(DHGroupID dhg_id);

/* classes */

//enum PKError;

struct CryptAlgoSelect;

struct SessionKeyParam;

class SessionKey;

struct AbstractClientID;

class ClientID;

struct ClientDatabase;

struct NegotiantData;

class ClientNegotiant;

class ServerNegotiant;

/* enum PKError */

enum PKError : uint32
 {
  PKENoError = 0 ,
  PKError_NoClientID,
  PKError_Exhausted,
  PKError_NoAlgo,
  PKError_NoAccess,
  PKError_NoLimit
 };

const char * GetTextDesc(PKError error);

/* struct CryptAlgoSelect */

struct CryptAlgoSelect : NoThrowFlagsBase
 {
  uint8 crypt_id = CryptID_AES256 ;
  uint8 hash_id = HashID_SHA256 ;
  uint8 dhg_id = DHGroupID_II ;
  
  // constructors
  
  CryptAlgoSelect() {}
  
  CryptAlgoSelect(CryptID crypt_id_,HashID hash_id_,DHGroupID dhg_id_) : crypt_id(crypt_id_),hash_id(hash_id_),dhg_id(dhg_id_) {}
  
  // methods
  
  bool operator == (const CryptAlgoSelect &obj) const
   {
    return crypt_id==obj.crypt_id && hash_id==obj.hash_id && dhg_id==obj.dhg_id ;
   }
  
  bool operator != (const CryptAlgoSelect &obj) const
   {
    return !(*this==obj);
   }
  
  // methods
  
  bool isValid() const { return IsValid(CryptID(crypt_id)) && IsValid(HashID(hash_id)) && IsValid(DHGroupID(dhg_id)) ; }
  
  AbstractCryptFunc * createEncrypt() const { return CreateEncrypt(CryptID(crypt_id)); }

  AbstractCryptFunc * createDecrypt() const { return CreateDecrypt(CryptID(crypt_id)); }

  AbstractHashFunc * createHash() const { return CreateHash(HashID(hash_id)); }

  AbstractDHGroup * createDHGroup() const { return CreateDHGroup(DHGroupID(dhg_id)); }
  
  ulen getKLen() const { return GetKLen(CryptID(crypt_id)); }

  ulen getHLen() const { return GetHLen(HashID(hash_id)); }

  ulen getGLen() const { return GetGLen(DHGroupID(dhg_id)); }
  
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

  bool fit() const
   {
    return Fit(MinKeySetLen,keyset_len,MaxKeySetLen) && Fit(MinTTL,ttl,MaxTTL) && Fit(MinUTL,utl,MaxUTL) ;
   }
  
  void cap()
   {
    keyset_len=Cap(MinKeySetLen,keyset_len,MaxKeySetLen);
    ttl=Cap(MinTTL,ttl,MaxTTL);
    utl=Cap(MinUTL,utl,MaxUTL);
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

   struct GetSecretLenCtx;
   struct CreateKeyGenCtx;
   
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

struct AbstractClientID : MemBase_nocopy
 {
  virtual ~AbstractClientID() {}
  
  virtual uint8 getLen() const =0;
  
  virtual void getID(uint8 buf[ /* Len */ ]) const =0;
 };

/* type ClientIDPtr */

using ClientIDPtr = OwnPtr<AbstractClientID> ;

/* class ClientID */

class ClientID : public AbstractClientID 
 {
   uint8 name[MaxClientIDLen];
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

/* struct ClientDatabase */

struct ClientDatabase
 {
  enum FindErrorCode : uint32
   {
    Find_Ok = 0,
    
    FindError_NoMemory,
    FindError_NoClientID
   };
  
  virtual FindErrorCode findClient(PtrLen<const uint8> client_id,PrimeKeyPtr &client_key,ClientProfilePtr &client_profile) const =0;
 };

/* struct NegotiantData */

struct NegotiantData : NoCopy
 {
  // machines
  
  PlatformRandom random;

  OwnPtr<AbstractCryptFunc> encrypt;
  OwnPtr<AbstractCryptFunc> decrypt;
  OwnPtr<AbstractHashFunc> hash;
  OwnPtr<AbstractDHGroup> dhg;
  
  DirectConvolution direct_conv;
  InverseConvolution inverse_conv;

  // id part
  
  uint8 client_id[MaxClientIDLen];
  uint8 client_id_len;
  
  AbstractHashFunc *client_key;
  AbstractHashFunc *server_key;
  
  // key part
  
  XPoint point;
  CryptAlgoSelect algo;
  uint8 server_nonce[NonceLen];
  uint8 client_nonce[NonceLen];
  
  ulen blen;
  ulen hlen;
  ulen glen;
  
  uint8 x[MaxGLen];
  uint8 gx[MaxGLen];
  uint8 gy[MaxGLen];
  uint8 gxy[MaxGLen];
  
  NegotiantData();
  
  ~NegotiantData();
  
  PtrLen<const uint8> getClientID() const { return Range(client_id,client_id_len); }
  
  void prepare(AbstractClientID *client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  void prepare(AbstractHashFunc *client_key,AbstractHashFunc *server_key);
  
  bool create();
  
  void keyGen();
  
  void clientKeyGen();
  
  void serverKeyGen();
  
  void clientGen();
  
  void serverGen();
  
  // encrypt/decrypt packets
  
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
  
  void setCounts();
  
  bool testCounts();
  
  void keyBufGen();
  
  void clientKeyBufGen();
  
  void serverKeyBufGen();
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
     State_Done,
     State_ClientError,
     State_ServerError,
     State_Timeout
    };
  
  private:
  
   class Proc : NoCopy
    {
      State state = State_Null ;
      PKError error = PKENoError ;
    
      PrimeKeyPtr client_key;
      PrimeKeyPtr server_key;
      
      CryptAlgoSelect algo_list[MaxAlgos];
      ulen algo_count = 0 ;
      
      MasterKeyPtr skey;
      
      uint8 send_buf[MaxPKETransLen];
      ulen send_len = 0 ;
      
      using InboundFunc = bool (Proc::*)(PtrLen<const uint8> data) ;
      
      InboundFunc inbound_func;
      
      NegotiantData neg_data;
      
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
      
      void build_error();
      
      void build_encrypted_error();
      
      bool process_error(PtrLen<const uint8> data);
      
     public: 
    
      Proc();
      
      ~Proc();
      
      State getState() const { return state; }
      
      PKError getError() const { return error; }
      
      void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param);
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      void stop() { state=State_Timeout; }
      
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
      
      State getState() const;
      
      PKError getError() const;
      
      void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param);
      
      void start(PtrLen<const CryptAlgoSelect> algo_list);
      
      void getSessionKey(MasterKeyPtr &skey);
    };
  
  private:
  
   ObjHook hook;
   
   Engine engine;
  
  public:
  
   ClientNegotiant(StrLen ep_dev_name,Function<void (void)> done_func);
   
   ~ClientNegotiant();
   
   State getState() const { return engine.getState(); }
   
   PKError getError() const { return engine.getError(); }
   
   void prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param={}) { engine.prepare(client_id,client_key,server_key,param); }
   
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
        InboundFinal,
        InboundServerError,
        InboundClientError
       };
      
      using InboundFunc = InboundResult (Proc::*)(PtrLen<const uint8> data);
      
      InboundFunc inbound_func;
      
      PrimeKeyPtr client_key;
      ClientProfilePtr client_profile;
      
      NegotiantData neg_data;
      
     private:
      
      InboundResult process1(XPoint point,PtrLen<const uint8> data);
      
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
      
      void build_error(PKError error);
      
      void build_encrypted_error(PKError error);
      
      InboundResult process_error(PtrLen<const uint8> data);
      
     public:
    
      explicit Proc(Engine *engine);
      
      ~Proc();
      
      bool inbound_first(XPoint point,PtrLen<const uint8> data,PacketList &list); // true to del
      
      bool inbound(PtrLen<const uint8> data,PacketList &list); // true to del
      
      bool tick(PacketList &list); // true to del
    };
  
   class Engine : NoCopy , PacketMultipointDevice::InboundProc
    {
      PacketMultipointDevice *dev;
      
      PacketFormat outbound_format;
      
      const ClientDatabase &client_db;
      PrimeKeyPtr server_key;
      EndpointManager &epman;
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
      
      void prepare_error(XPoint point,PKError error,PacketList &list);
      
      // InboundProc
    
      virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);
     
      virtual void tick();
    
     public:
    
      Engine(PacketMultipointDevice *dev,const ClientDatabase &client_db,EndpointManager &epman,ulen max_clients,MSec final_timeout);
      
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

   ServerNegotiant(StrLen mp_dev_name,const ClientDatabase &client_db,EndpointManager &epman,ulen max_clients=DefaultMaxClients,MSec final_timeout=5_sec);
   
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
 

