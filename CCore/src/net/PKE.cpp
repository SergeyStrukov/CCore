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

using CryptCaseList = Meta::CaseList<Meta::Case<uint8,CryptID_AES128,Crypton::PlatformAES128>,
                                     Meta::Case<uint8,CryptID_AES192,Crypton::PlatformAES192>,
                                     Meta::Case<uint8,CryptID_AES256,Crypton::PlatformAES256> > ;

using HashCaseList = Meta::CaseList<Meta::Case<uint8,HashID_SHA1,Crypton::PlatformSHA1>,
                                    Meta::Case<uint8,HashID_SHA224,Crypton::PlatformSHA224>,
                                    Meta::Case<uint8,HashID_SHA256,Crypton::PlatformSHA256>,
                                    Meta::Case<uint8,HashID_SHA384,Crypton::PlatformSHA384>,
                                    Meta::Case<uint8,HashID_SHA512,Crypton::PlatformSHA512> > ;

using DHGCaseList = Meta::CaseList<Meta::Case<uint8,DHGroupID_I,Crypton::DHExp<Crypton::DHModI> >,
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

ulen SessionKey::GetKLen(CryptAlgoSelect algo_select)
 {
  return Meta::TypeSwitch<CryptCaseList>::Switch(algo_select.crypt_id,GetKLenCtx());
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
   
AbstractCryptFunc * SessionKey::createEncrypt() const // switch
 {
  switch( algo_select.crypt_id )
    {
     case CryptID_AES128 : return CreateCrypt<Crypton::PlatformAES128>();
     case CryptID_AES192 : return CreateCrypt<Crypton::PlatformAES192>();
     case CryptID_AES256 : return CreateCrypt<Crypton::PlatformAES256>();
     
     default:
      {
       Printf(Exception,"CCore::Net::PSec::SessionKey::createEncrypt() : unknown crypt_id #;",algo_select.crypt_id);
       
       return 0;
      }
    }
 }
   
AbstractCryptFunc * SessionKey::createDecrypt() const // switch
 {
  switch( algo_select.crypt_id )
    {
     case CryptID_AES128 : return CreateCrypt<Crypton::PlatformAESInverse128>();
     case CryptID_AES192 : return CreateCrypt<Crypton::PlatformAESInverse192>();
     case CryptID_AES256 : return CreateCrypt<Crypton::PlatformAESInverse256>();
     
     default:
      {
       Printf(Exception,"CCore::Net::PSec::SessionKey::createDecrypt() : unknown crypt_id #;",algo_select.crypt_id);
       
       return 0;
      }
    }
 }
   
AbstractHashFunc * SessionKey::createHash() const // switch
 {
  switch( algo_select.hash_id )
    {
     case HashID_SHA1   : return CreateHash<Crypton::PlatformSHA1>();
     case HashID_SHA224 : return CreateHash<Crypton::PlatformSHA224>();
     case HashID_SHA256 : return CreateHash<Crypton::PlatformSHA256>();
     case HashID_SHA384 : return CreateHash<Crypton::PlatformSHA384>();
     case HashID_SHA512 : return CreateHash<Crypton::PlatformSHA512>();
     
     default:
      {
       Printf(Exception,"CCore::Net::PSec::SessionKey::createHash() : unknown hash_id #;",algo_select.hash_id);
       
       return 0;
      }
    }
 }
   
AbstractKeyGen * SessionKey::createKeyGen() const // switch
 {
  OwnPtr<AbstractHashFunc> hash(createHash());
  
  switch( algo_select.dhg_id )
    {
     case DHGroupID_I : return createKeyGen<Crypton::DHExp<Crypton::DHModI> >(hash); 
     
     case DHGroupID_II : return createKeyGen<Crypton::DHExp<Crypton::DHModII> >(hash); 
     
     default:
      {
       Printf(Exception,"CCore::Net::PSec::SessionKey::createKeyGen() : unknown dhg_id #;",algo_select.dhg_id);
       
       return 0;
      }
    }
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

} // namespace PSec 
} // namespace Net
} // namespace CCore
 

