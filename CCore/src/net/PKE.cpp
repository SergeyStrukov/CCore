/* PKE.cpp */ 
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
 
#include <CCore/inc/net/PKE.h>
 
#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/crypton/PlatformSHA.h>
#include <CCore/inc/crypton/PlatformAES.h>
#include <CCore/inc/crypton/DHExp.h>

#include <CCore/inc/TypeSwitch.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Net {
namespace PSec {

/* case lists */

using EncryptCaseList = Meta::CaseList<Meta::Case<uint8,CryptID_AES128,Crypton::PlatformAES128>,
                                       Meta::Case<uint8,CryptID_AES192,Crypton::PlatformAES192>,
                                       Meta::Case<uint8,CryptID_AES256,Crypton::PlatformAES256> > ;

using DecryptCaseList = Meta::CaseList<Meta::Case<uint8,CryptID_AES128,Crypton::PlatformAESInverse128>,
                                       Meta::Case<uint8,CryptID_AES192,Crypton::PlatformAESInverse192>,
                                       Meta::Case<uint8,CryptID_AES256,Crypton::PlatformAESInverse256> > ;

using HashCaseList = Meta::CaseList<Meta::Case<uint8,HashID_SHA1  ,Crypton::PlatformSHA1  >,
                                    Meta::Case<uint8,HashID_SHA224,Crypton::PlatformSHA224>,
                                    Meta::Case<uint8,HashID_SHA256,Crypton::PlatformSHA256>,
                                    Meta::Case<uint8,HashID_SHA384,Crypton::PlatformSHA384>,
                                    Meta::Case<uint8,HashID_SHA512,Crypton::PlatformSHA512> > ;

using DHGCaseList = Meta::CaseList<Meta::Case<uint8,DHGroupID_I ,Crypton::DHExp<Crypton::DHModI > >,
                                   Meta::Case<uint8,DHGroupID_II,Crypton::DHExp<Crypton::DHModII> > > ;

/* functions */

namespace Private_PKE {

struct CreateCryptCtx
 {
  using RetType = AbstractCryptFunc * ;
  
  template <class T>
  static RetType call() { return new CryptFunc<T>(); }
  
  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::Create(En/De)crypt(#;) : unknown crypt_id",crypt_id);
    
    return 0;
   }
 };

struct CreateHashCtx
 {
  using RetType = AbstractHashFunc * ;
  
  template <class T>
  static RetType call() { return new HashFunc<T>(); }
  
  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::CreateHash(#;) : unknown hash_id",hash_id);
    
    return 0;
   }
 };

struct CreateDHGroupCtx
 {
  using RetType = AbstractDHGroup * ;
  
  template <class T>
  static RetType call() { return new DHGroup<T>(); }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::CreateDHGroup(#;) : unknown dhg_id",dhg_id);
    
    return 0;
   }
 };

} // namespace Private_PKE

using namespace Private_PKE;

AbstractCryptFunc * CreateEncrypt(CryptID crypt_id)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(crypt_id,CreateCryptCtx());
 }

AbstractCryptFunc * CreateDecrypt(CryptID crypt_id)
 {
  return Meta::TypeSwitch<DecryptCaseList>::Switch(crypt_id,CreateCryptCtx());
 }

AbstractHashFunc * CreateHash(HashID hash_id)
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(hash_id,CreateHashCtx());
 }

AbstractDHGroup * CreateDHGroup(DHGroupID dhg_id)
 {
  return Meta::TypeSwitch<DHGCaseList>::Switch(dhg_id,CreateDHGroupCtx());
 }

/* class SessionKey */

struct SessionKey::GetKLenCtx
 {
  using RetType = ulen ;
  
  template <class T>
  static RetType call()
   {
    return T::KeyLen;
   }
  
  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::GetKLen(...) : unknown crypt_id #;",crypt_id);
    
    return 0;
   }
 };

struct SessionKey::GetHLenCtx
 {
  using RetType = ulen ;
  
  template <class T>
  static RetType call()
   {
    return T::DigestLen;
   }
  
  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::GetHLen() : unknown hash_id #;",hash_id);
    
    return 0;
   }
 };

struct SessionKey::GetSecretLenCtx
 {
  using RetType = ulen ;
  
  ulen klen;
  ulen hlen;
  
  GetSecretLenCtx(ulen klen_,ulen hlen_) : klen(klen_),hlen(hlen_) {}
  
  template <class T>
  RetType call()
   {
    return KeyGen<T>::GetSecretLen(klen,hlen);
   }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::GetSecretLen() : unknown dhg_id #;",dhg_id);
    
    return 0;
   }
 };

struct SessionKey::CreateKeyGenCtx
 {
  using RetType = AbstractKeyGen * ;
  
  const SessionKey *obj;
  OwnPtr<AbstractHashFunc> &hash;
  
  CreateKeyGenCtx(const SessionKey *obj_,OwnPtr<AbstractHashFunc> &hash_) : obj(obj_),hash(hash_) {}
  
  template <class T>
  RetType call() { return obj->createKeyGen<T>(hash); }
  
  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::createKeyGen() : unknown dhg_id #;",dhg_id);
    
    return 0;
   }
 };

ulen SessionKey::GetKLen(CryptAlgoSelect algo_select)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(algo_select.crypt_id,GetKLenCtx());
 }

ulen SessionKey::GetHLen(CryptAlgoSelect algo_select)
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(algo_select.hash_id,GetHLenCtx());
 }

ulen SessionKey::GetSecretLen(CryptAlgoSelect algo_select,ulen klen)
 {
  ulen hlen=GetHLen(algo_select);
  
  return Meta::TypeSwitch<DHGCaseList>::Switch(algo_select.dhg_id,GetSecretLenCtx(klen,hlen));
 }

SessionKey::SessionKey(CryptAlgoSelect algo_select_,SessionKeyParam param_)
 : algo_select(algo_select_),
   param(param_),
   klen(GetKLen(algo_select_)),
   ktotal( LenOf(ulen(1)+param_.keyset_len,klen) ),
   secret_len( GetSecretLen(algo_select_,klen) ),
   key_buf( LenAdd(ktotal,secret_len,RandomWarpLen) )
 {
 }
   
SessionKey::~SessionKey()
 {
  Crypton::Forget(algo_select);
  Crypton::Forget(param);
  
  Crypton::ForgetRange(Range(key_buf));
 }
   
AbstractCryptFunc * SessionKey::createEncrypt() const
 {
  return CreateEncrypt(CryptID(algo_select.crypt_id));
 }
   
AbstractCryptFunc * SessionKey::createDecrypt() const
 {
  return CreateDecrypt(CryptID(algo_select.crypt_id));
 }
   
AbstractHashFunc * SessionKey::createHash() const
 {
  return CreateHash(HashID(algo_select.hash_id));
 }
   
AbstractKeyGen * SessionKey::createKeyGen() const
 {
  OwnPtr<AbstractHashFunc> hash(createHash());
  
  return Meta::TypeSwitch<DHGCaseList>::Switch(algo_select.dhg_id,CreateKeyGenCtx(this,hash));
 }
   
AbstractRandomGen * SessionKey::createRandom() const
 {
  return new RandomGen<PlatformRandom>(Range(key_buf.getPtr()+ktotal+secret_len,RandomWarpLen));
 }
   
ulen SessionKey::getKLen() const
 {
  return klen;
 }
   
LifeLim SessionKey::getLifeLim() const
 {
  return LifeLim(param.ttl,param.utl);
 }
   
void SessionKey::getKey0(uint8 key[]) const
 {
  Range(key_buf.getPtr(),klen).copyTo(key);
 }
   
ulen SessionKey::getKeySetLen() const
 {
  if( param.keyset_len==0 || param.keyset_len>0x4000 )
    {
     Printf(Exception,"CCore::Net::PSec::SessionKey::getKeySetLen() : bad keyset length #;",param.keyset_len);
    }
  
  return param.keyset_len;
 }
   
void SessionKey::getKey(ulen index,uint8 key[]) const
 {
  Range(key_buf.getPtr()+klen*(index+1),klen).copyTo(key);
 }

/* struct NegData */

NegData::NegData()
 {
 }

NegData::~NegData()
 {
  Crypton::ForgetRange(Range(x));
  Crypton::ForgetRange(Range(gxy));
  Crypton::ForgetRange(Range(key));
 }

bool NegData::create()
 {
  SilentReportException report;
  
  try
    {
     encrypt.set(CreateEncrypt(CryptID(algo.crypt_id)));
     decrypt.set(CreateDecrypt(CryptID(algo.crypt_id)));
     hash.set(CreateHash(HashID(algo.hash_id)));
     dhg.set(CreateDHGroup(DHGroupID(algo.dhg_id)));
     
     glen=dhg->getGLen();
     
     return true;
    }
  catch(...)
    {
     return false;
    }
 }

void NegData::keyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  uint8 temp[SaveLenCounter<XPoint>::SaveLoadLen];
  
  {
   BufPutDev dev(temp);
   
   dev.use<BeOrder>(point);
  }
  
  ulen client_hlen=client_key->getHLen();
  ulen server_hlen=server_key->getHLen();
  
  PtrLen<uint8> dst(key,encrypt->getKLen());
  
  for(;;)
    {
     client_key->add(Range_const(temp));
     client_key->add(client_id);
     client_key->add(Range_const(client_nonce));
     client_key->add(Range_const(server_nonce));
     client_key->add(Range_const(gxy,glen));
     
     const uint8 *client_digest=client_key->finish();
     
     server_key->add(Range_const(client_digest,client_hlen));
     server_key->add(Range_const(temp));
     client_key->add(client_id);
     server_key->add(Range_const(client_nonce));
     server_key->add(Range_const(server_nonce));
     server_key->add(Range_const(gxy,glen));
     
     const uint8 *server_digest=server_key->finish();
     
     if( server_hlen<dst.len )
       {
        (dst+=server_hlen).copy(server_digest);
        
        client_key->add(Range_const(server_digest,server_hlen));
       }
     else
       {
        dst.copy(server_digest);
        
        Printf(Con,"key =\n#;\n\n",PrintDump(Range_const(key,encrypt->getKLen())));
        
        return;
       }
    }
 }

void NegData::clientKeyGen(AbstractClientID *client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  uint8 len=client_id->getLen();
  uint8 temp[255];
  
  client_id->getID(temp);
  
  keyGen(Range_const(temp,len),client_key,server_key);
 }

void NegData::serverKeyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  dhg->pow(gy,x,gxy);
  
  keyGen(client_id,client_key,server_key);
 }

void NegData::clientGen()
 {
  random.fill(Range(client_nonce));
  
  random.fill(Range(x,glen));
  
  dhg->pow(x,gx);
  
  dhg->pow(gy,x,gxy);
 }

void NegData::serverGen()
 {
  random.fill(Range(server_nonce));
  
  random.fill(Range(x,glen));
  
  dhg->pow(x,gx);
 }

/* class ClientNegotiant::Proc */

void ClientNegotiant::Proc::build1()
 {
  BufPutDev dev(send_buf);
  
  dev(*client_id);
  
  SaveRange(algo_list,algo_count,dev);
  
  send_len=Dist(send_buf,dev.getRest());
 }

bool ClientNegotiant::Proc::test_algo() const
 {
  for(const CryptAlgoSelect &algo : Range(algo_list,algo_count) ) if( algo==neg_data.algo ) return true;
  
  return false;
 }

bool ClientNegotiant::Proc::process2(PtrLen<const uint8> data)
 {
  RangeGetDev dev(data);
  
  dev.use<BeOrder>(neg_data.point);
  
  LoadRange(Range(neg_data.server_nonce),dev);
  
  dev(neg_data.algo);
  
  if( !dev || !test_algo() ) return false;
  
  if( !neg_data.create() ) return false;
  
  dev.get(neg_data.gy,neg_data.glen);
  
  if( !dev.finish() ) return false;
  
  neg_data.clientGen();
  
  neg_data.clientKeyGen(client_id.getPtr(),client_key.getPtr(),server_key.getPtr());
  
  build3();
  
  inbound_func=&Proc::process4;
  
  return true;
 }

void ClientNegotiant::Proc::build3()
 {
  BufPutDev dev(send_buf);
  
  dev.use<BeOrder>(neg_data.point);
  
  dev.put(Range_const(neg_data.client_nonce));

  dev.put(Range_const(neg_data.gx,neg_data.glen));
  
  send_len=Dist(send_buf,dev.getRest());
 }

bool ClientNegotiant::Proc::process4(PtrLen<const uint8> data)
 {
  // TODO
  
  return false;
 }

ClientNegotiant::Proc::Proc()
 {
 }

ClientNegotiant::Proc::~Proc()
 {
 }

void ClientNegotiant::Proc::prepare(ClientID &client_id_,PrimeKey &client_key_,PrimeKey &server_key_)
 {
  if( state!=State_Null )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : not null");
    }
  
  Swap(client_id,client_id_);
  Swap(client_key,client_key_);
  Swap(server_key,server_key_);
  
  if( !client_id )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no client id");
    }
  
  if( !client_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no client key");
    }
  
  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no server key");
    }
 }

void ClientNegotiant::Proc::start(PtrLen<const CryptAlgoSelect> algo_list_)
 {
  if( state!=State_Ready )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::start(...) : not prepared");
    }
  
  if( algo_list_.len>MaxAlgos )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::start(...) : too many algos");
    }
  
  algo_list_.copyTo(algo_list);
  
  algo_count=algo_list_.len;
  
  skey.set(0);
  
  state=State_Started;
  
  build1();
  
  inbound_func=&Proc::process2;
 }

bool ClientNegotiant::Proc::inbound(PtrLen<const uint8> data)
 {
  if( state==State_Started ) return (this->*inbound_func)(data);

  return false;
 }

/* class ClientNegotiant::Engine */

Packet<uint8> ClientNegotiant::Engine::prepare_send()
 {
  tick_count=StartTickCount;
  retry_count=MaxRetry;
  
  Packet<uint8> ret=pset.try_get();
  
  if( !ret ) return Nothing;
  
  PtrLen<const uint8> data=proc.getSendData();
  
  if( ret.checkDataLen(outbound_format,data.len) )
    {
     ret.setDataLen(outbound_format,data.len).copy(data.ptr);
     
     return ret;
    }
  else
    {
     ret.complete();
     
     return Nothing;
    }
 }

void ClientNegotiant::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Packet<uint8> send;
  bool done=false;
  
  {
   Mutex::Lock lock(mutex);
   
   if( proc.inbound(data) ) 
     {
      if( proc.getState()==State_Started )
        {
         send=prepare_send();
        }
      else
        {
         tick_count=0;
         retry_count=0;
         done=true;
        }
     }
  } 
  
  packet.complete();
  
  if( +send ) dev->outbound(send);
  
  if( done ) done_func();
 }

void ClientNegotiant::Engine::tick()
 {
  Packet<uint8> send;
  
  {
   Mutex::Lock lock(mutex);
   
   if( retry_count )
     {
      if( tick_count )
        {
         tick_count--;
        }
      else
        {
         retry_count--;
         tick_count=StartTickCount;
         
         send=prepare_send();
        }
     }
  }
  
  if( +send ) dev->outbound(send);
 }

ClientNegotiant::Engine::Engine(PacketEndpointDevice *dev_,Function<void (void)> done_func_)
 : dev(dev_),
   done_func(done_func_),
   pset("PSec::ClientNegotiant.pset"),
   mutex("PSec::ClientNegotiant.mutex")
 {
  outbound_format=dev->getOutboundFormat();
 }

ClientNegotiant::Engine::~Engine()
 {
 }

void ClientNegotiant::Engine::prepare(ClientID &client_id,PrimeKey &client_key,PrimeKey &server_key)
 {
  Mutex::Lock lock(mutex);
  
  proc.prepare(client_id,client_key,server_key);
 }

void ClientNegotiant::Engine::start(PtrLen<const CryptAlgoSelect> algo_list)
 {
  Packet<uint8> send;
  
  {
   Mutex::Lock lock(mutex);
  
   proc.start(algo_list);
   
   send=prepare_send();
  } 
  
  if( +send ) dev->outbound(send);
 }

auto ClientNegotiant::Engine::getState() const -> State
 {
  Mutex::Lock lock(mutex);
  
  return proc.getState();
 }

void ClientNegotiant::Engine::getSessionKey(SKey &skey)
 {
  Mutex::Lock lock(mutex);
  
  proc.getSessionKey(skey);
 }

/* class ClientNegotiant */

ClientNegotiant::ClientNegotiant(StrLen ep_dev_name,Function<void (void)> done_func)
 : hook(ep_dev_name),
   engine(hook,done_func)
 {
 }

ClientNegotiant::~ClientNegotiant()
 {
 }

/* class ServerNegotiant::Proc */

bool ServerNegotiant::Proc::process1(XPoint point,PtrLen<const uint8> data)
 {
  RangeGetDev dev(data);
  
  dev(client_id_len);
  
  dev.get(client_id,client_id_len);
    
  if( !dev ) return false;
  
  CryptAlgoSelect selected_algo;
  bool flag=false;
  
  while( dev.getRest().len )
    {
     CryptAlgoSelect algo;
     
     dev(algo);
     
     if( !dev ) return false;
     
     if( !flag && engine->filter(algo) )
       {
        selected_algo=algo;
        flag=true;
       }
    }
  
  if( !flag ) return false;
  
  if( !engine->client_db.findClient(Range_const(client_id,client_id_len),client_key,client_profile) ) return false;
  
  neg_data.point=point;
  neg_data.algo=selected_algo;
  
  if( !neg_data.create() ) return false;
  
  neg_data.serverGen();
  
  build2();
  
  inbound_func=&Proc::process3;
  
  return true;
 }

void ServerNegotiant::Proc::build2()
 {
  BufPutDev dev(send_buf);
  
  dev.use<BeOrder>(neg_data.point);
  
  dev.put(Range_const(neg_data.server_nonce));
  
  dev(neg_data.algo);
  
  dev.put(Range_const(neg_data.gx,neg_data.glen));
  
  send_len=Dist(send_buf,dev.getRest());
 }

auto ServerNegotiant::Proc::process3(PtrLen<const uint8> data) -> InboundResult
 {
  RangeGetDev dev(data);
  
  XPoint point;
  
  dev.use<BeOrder>(point);
  
  dev.get(Range(neg_data.client_nonce));
  
  dev.get(Range(neg_data.gy,neg_data.glen));
  
  if( !dev.finish() || point!=neg_data.point ) return InboundDrop;
  
  neg_data.serverKeyGen(Range_const(client_id,client_id_len),client_key.getPtr(),engine->server_key.getPtr());
  
  build4();
  
  inbound_func=&Proc::process5;
  
  return InboundOk;
 }

void ServerNegotiant::Proc::build4()
 {
  // TODO
  
  send_len=0;
 }

auto ServerNegotiant::Proc::process5(PtrLen<const uint8> data) -> InboundResult
 {
  // TODO
  
  return InboundDrop;
 }

auto ServerNegotiant::Proc::process_final(PtrLen<const uint8> data) -> InboundResult
 {
  if( process1(neg_data.point,data) )
    {
     return InboundOk;
    }
  else
    {
     return InboundFinal;
    }
 }

ServerNegotiant::Proc::Proc(Engine *engine_)
 : engine(engine_)
 {
 }

ServerNegotiant::Proc::~Proc()
 {
 }

bool ServerNegotiant::Proc::inbound_first(XPoint point,PtrLen<const uint8> data,PacketList &list)
 {
  if( process1(point,data) )
    {
     tick_count=StartTickCount;
     retry_count=MaxRetry;
    
     engine->prepare_send(point,Range_const(send_buf,send_len),list);
     
     return false;
    }
  
  return true;
 }

void ServerNegotiant::Proc::inbound(PtrLen<const uint8> data,PacketList &list)
 {
  switch( (this->*inbound_func)(data) ) 
    {
     case InboundOk :
      {
       tick_count=StartTickCount;
       retry_count=MaxRetry;
       
       engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
      }
     break;
     
     case InboundLast :
      {
       tick_count=engine->final_tick_count;
       retry_count=1;
       
       engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
      }
     break;
     
     case InboundFinal :
      {
       engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
      }
     break; 
    }
 }

bool ServerNegotiant::Proc::tick(PacketList &list)
 {
  if( retry_count )
    {
     if( tick_count )
       {
        tick_count--;
       }
     else
       {
        if( --retry_count )
          {
           tick_count=StartTickCount;
          
           engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
          }
        else
          {
           retry_count=1;
           
           return true;
          }
       }
    }
  
  return false;
 }

/* class ServerNegotiant::Engine */

bool ServerNegotiant::Engine::filter(const CryptAlgoSelect &algo) const
 {
  if( algo_filter )
    {
     for(const CryptAlgoSelect &obj : algo_list ) if( algo==obj ) return true;
     
     return false;
    }
  
  return true;
 }

void ServerNegotiant::Engine::prepare_send(XPoint point,PtrLen<const uint8> send_data,PacketList &list)
 {
  Packet<uint8> packet=pset.try_get();
  
  if( !packet ) return;
  
  if( packet.checkDataLen(outbound_format,send_data.len) )
    {
     packet.setDataLen(outbound_format,send_data.len).copy(send_data.ptr);
     
     list.put(packet.pushExt<XPoint>(point));
    }
  else
    {
     packet.complete();
    }
 }

void ServerNegotiant::Engine::send(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() ) 
    {
     Packet<uint8,XPoint> packet=packet_;
     XPoint point=*packet.getExt();
     
     dev->outbound(point,packet.popExt());
    }
 }

void ServerNegotiant::Engine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  PacketList list;
  
  {
   Mutex::Lock lock(mutex);
   
   if( enable )
     {
      if( map.getCount()<max_clients )
        {
         SilentReportException report;
        
         try
           {
            auto result=map.find_or_add(point,this);
            
            if( result.new_flag )
              {
               if( result.obj->inbound_first(point,data,list) )
                 {
                  map.del(point);
                 }
              }
            else
              {
               result.obj->inbound(data,list);
              } 
           }
         catch(...)
           {
           }
        }
      else
        {
         if( auto *obj=map.find(point) ) obj->inbound(data,list);
        }
     }
  }
  
  packet.complete();

  send(list);
 }

void ServerNegotiant::Engine::tick()
 {
  PacketList list;

  {
   Mutex::Lock lock(mutex);
   
   if( enable )
     {
      const ulen Len = 100 ;
     
      XPoint todel[Len];
      ulen count=0;
     
      map.applyIncr( [&] (XPoint point,Proc &proc) { if( proc.tick(list) && count<Len ) todel[count++]=point; } );
      
      for(XPoint point : Range(todel,count) ) map.del(point);
     }
  }
  
  send(list);
 }

ServerNegotiant::Engine::Engine(PacketMultipointDevice *dev_,AbstractClientDataBase &client_db_,AbstractEndpointManager &epman_,ulen max_clients_,MSec final_timeout)
 : dev(dev_),
   client_db(client_db_),
   epman(epman_),
   max_clients(max_clients_),
   pset("PSec::ServerNegotiant.pset"),
   mutex("PSec::ServerNegotiant.mutex")
 {
  outbound_format=dev->getOutboundFormat();
  
  final_tick_count=((+final_timeout)*InboundTicksPerSec)/1000+1;
 }

ServerNegotiant::Engine::~Engine()
 {
 }

void ServerNegotiant::Engine::prepare(PrimeKey &server_key_)
 {
  Mutex::Lock lock(mutex);
  
  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::prepare(...) : already started");
    }
  
  Swap(server_key,server_key_);
  
  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::prepare(...) : no server key");
    }
 }

void ServerNegotiant::Engine::start()
 {
  Mutex::Lock lock(mutex);
  
  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : already started");
    }
  
  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : not prepared");
    }
  
  enable=true;
 }

void ServerNegotiant::Engine::start(PtrLen<const CryptAlgoSelect> algo_list_)
 {
  Mutex::Lock lock(mutex);
  
  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : already started");
    }

  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : not prepared");
    }
  
  algo_list.extend_copy(algo_list_.len,algo_list_.ptr);
  
  algo_filter=true;
  enable=true;
 }

/* class ServerNegotiant */

ServerNegotiant::ServerNegotiant(StrLen mp_dev_name,AbstractClientDataBase &client_db,AbstractEndpointManager &epman,ulen max_clients,MSec final_timeout)
 : hook(mp_dev_name),
   engine(hook,client_db,epman,max_clients,final_timeout)
 {
 }

ServerNegotiant::~ServerNegotiant() 
 {
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 

