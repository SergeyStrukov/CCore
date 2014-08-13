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

struct SessionKey::CreateCryptCtx
 {
  using RetType = AbstractCryptFunc * ;
  
  template <class T>
  static RetType call() { return new CryptFunc<T>(); }
  
  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::create(En/De)crypt() : unknown crypt_id #;",crypt_id);
    
    return 0;
   }
 };

struct SessionKey::CreateHashCtx
 {
  using RetType = AbstractHashFunc * ;
  
  template <class T>
  static RetType call() { return new HashFunc<T>(); }
  
  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::createHash() : unknown hash_id #;",hash_id);
    
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
  return Meta::TypeSwitch<EncryptCaseList>::Switch(algo_select.crypt_id,CreateCryptCtx());
 }
   
AbstractCryptFunc * SessionKey::createDecrypt() const
 {
  return Meta::TypeSwitch<DecryptCaseList>::Switch(algo_select.crypt_id,CreateCryptCtx());
 }
   
AbstractHashFunc * SessionKey::createHash() const
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(algo_select.hash_id,CreateHashCtx());
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

/* class ClientNegotiant::Engine */

void ClientNegotiant::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
 }

void ClientNegotiant::Engine::tick()
 {
 }

ClientNegotiant::Engine::Engine(PacketEndpointDevice *dev_,ClientId &client_id,PrimeKey &client_key,PrimeKey &server_key)
 : dev(dev_),
   proc(client_id,client_key,server_key)
 {
 }

ClientNegotiant::Engine::~Engine()
 {
 }

void ClientNegotiant::Engine::start(PtrLen<const CryptAlgoSelect> algo_list)
 {
  Mutex::Lock lock(mutex);
  
  proc.start(algo_list);
 }

auto ClientNegotiant::Engine::getState() const -> State
 {
 }

auto ClientNegotiant::Engine::wait(MSec timeout) -> State
 {
 }

auto ClientNegotiant::Engine::wait(TimeScope time_scope) -> State
 {
 }

void ClientNegotiant::Engine::getSessionKey(SKey &skey)
 {
 }

/* class ClientNegotiant */

ClientNegotiant::ClientNegotiant(StrLen ep_dev_name,ClientId &client_id,PrimeKey &client_key,PrimeKey &server_key)
 : hook(ep_dev_name),
   engine(hook,client_id,client_key,server_key)
 {
 }

ClientNegotiant::~ClientNegotiant()
 {
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 

