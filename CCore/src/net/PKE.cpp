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

/* class ClientID */

template <class T>
void ClientID::init(PtrLen<T> name_)
 {
  if( name_.len>255 )
    {
     Printf(Exception,"CCore::Net::PSec::ClientID::ClientID(...) : name is too long");
    }
  
  len=(uint8)name_.len;
  
  name_.copyTo(name);
 }

ClientID::ClientID(StrLen name)
 {
  init(name);
 }
   
ClientID::ClientID(PtrLen<const uint8> name)
 {
  init(name);
 }

ClientID::~ClientID()
 {
 }

uint8 ClientID::getLen() const
 {
  return len;
 }

void ClientID::getID(uint8 buf[ /* Len */ ]) const
 {
  Range(name,len).copyTo(buf);
 }

/* class HashPrimeKey */

HashPrimeKey::HashPrimeKey(HashID hash_id,PtrLen<const uint8> key)
 {
  switch( hash_id )
    {
     case HashID_SHA1   : hash.set(new HashFunc<Crypton::PlatformKeyedSHA1>(key)); break;
     case HashID_SHA224 : hash.set(new HashFunc<Crypton::PlatformKeyedSHA224>(key)); break;
     case HashID_SHA256 : hash.set(new HashFunc<Crypton::PlatformKeyedSHA256>(key)); break;
     case HashID_SHA384 : hash.set(new HashFunc<Crypton::PlatformKeyedSHA384>(key)); break;
     case HashID_SHA512 : hash.set(new HashFunc<Crypton::PlatformKeyedSHA512>(key)); break;
     
     default:
      {
       Printf(Exception,"CCore::Net::PSec::HashPrimeKey::HashPrimeKey(hash_id=#;,...) : unknown hash id",hash_id);
      }
    }
 }
   
HashPrimeKey::~HashPrimeKey()
 {
 }
   
ulen HashPrimeKey::getHLen() const
 {
  return hash->getHLen();
 }
   
void HashPrimeKey::add(PtrLen<const uint8> data)
 {
  hash->add(data);
 }
   
const uint8 * HashPrimeKey::finish()
 {
  return hash->finish();
 }
   
/* struct NegData */

NegData::NegData()
 {
 }

NegData::~NegData()
 {
  Crypton::ForgetRange(Range(x));
  Crypton::ForgetRange(Range(gxy));
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
     
     hlen=hash->getHLen();
     blen=encrypt->getBLen();
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
  
  uint8 key[MaxKLen];
  
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
        
        encrypt->key(key);
        decrypt->key(key);
        
        Crypton::ForgetRange(Range(key));
        
        return;
       }
    }
 }

void NegData::clientKeyGen(PtrLen<const uint8> client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  keyGen(client_id,client_key,server_key);
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

BufPutDev NegData::start(uint8 *buf,uint16 type)
 {
  BufPutDev dev(buf);
  
  uint8 len=random.next8();
  
  dev(len);
  
  random.fill(dev.putRange(len));
  
  dev.putRange(2u);
  
  dev.use<BeOrder>(type);  
  
  return dev;
 }

ulen NegData::finish(uint8 *buf,BufPutDev dev)
 {
  ulen len=Dist(buf,dev.getRest());
  
  ulen rlen=buf[0];
  uint16 plen=uint16( len-(rlen+5u) );
  
  {
   BufPutDev temp(buf+(rlen+1u));
   
   temp.use<BeOrder>(plen);
  }   
  
  hash->add(Range_const(buf,len));
  
  dev.put(Range(hash->finish(),hlen));

  len+=hlen;
  
  ulen count=(len+(blen-1u))/blen;
  ulen total=count*blen;
  
  random.fill(dev.putRange(total-len));
  
  direct_conv.start();
  
  direct_conv.apply(Range(buf,total));
  
  for(; count ;count--,buf+=blen) encrypt->apply(buf);
  
  return total;
 }

PKEType NegData::process(PtrLen<const uint8> &data)
 {
  uint8 *buf=const_cast<uint8 *>(data.ptr);
  ulen len=data.len;
  
  if( !len || len%blen ) return PKE_None;
  
  ulen count=len/blen;
  
  for(uint8 *ptr=buf; count ;count--,ptr+=blen) decrypt->apply(ptr);
  
  inverse_conv.start();
  
  inverse_conv.apply(Range(buf,len));
  
  ulen rlen=buf[0];
  
  if( len<(rlen+5u) ) return PKE_None;
  
  BufGetDev dev(buf+(rlen+1u));
  
  uint16 plen;
  uint16 type;
  
  dev.use<BeOrder>(plen,type);
  
  ulen dlen=rlen+5u+plen;
  
  if( len<dlen+hlen ) return PKE_None;
  
  hash->add(Range_const(buf,dlen));
  
  if( !Range(hash->finish(),hlen).equal(buf+dlen) ) return PKE_None; 
  
  data.ptr=buf+(rlen+5u);
  data.len=plen;
  
  return PKEType(type);
 }

bool NegData::createSKey()
 {
  SilentReportException report;
  
  try
    {
     SessionKey *session_key=new SessionKey(algo,param);
    
     skey.set(session_key);
     
     key_buf=session_key->takeKeyBuf();
     
     return true;
    }
  catch(...)
    {
     return false;
    }
 }

void NegData::setCounts(AbstractHashFunc *server_key)
 {
  ulen len=key_buf.len;
  ulen server_hlen=server_key->getHLen();
  
  ulen count=(len+server_hlen-1)/server_hlen;
  
  if( count<=10 )
    {
     rep_count=1;
     max_count=count;
    }
  else
    {
     if( count<=20 )
       rep_count=2;
     else if( count<=30 )
       rep_count=3;
     else if( count<=40 )
       rep_count=4;
     else if( count<=50 )
       rep_count=5;
     else if( count<=60 )
       rep_count=6;
     else if( count<=70 )
       rep_count=7;
     else if( count<=80 )
       rep_count=8;
     else if( count<=90 )
       rep_count=9;
     else
       rep_count=10;
     
     max_count=(count+rep_count-1)/rep_count;
    }
  
  cur_count=max_count;
 }

bool NegData::testCounts(AbstractHashFunc *server_key)
 {
  ulen len=key_buf.len;
  ulen server_hlen=server_key->getHLen();
  
  return len<=server_hlen*rep_count*max_count;
 }

void NegData::keyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  ulen client_hlen=client_key->getHLen();
  ulen server_hlen=server_key->getHLen();
  
  for(ulen cnt=rep_count; cnt ;cnt--)
    {
     client_key->add(Range_const(client_nonce));
     client_key->add(Range_const(server_nonce));
     client_key->add(Range_const(gxy,glen));
     
     const uint8 *client_digest=client_key->finish();
     
     server_key->add(Range_const(client_digest,client_hlen));
     server_key->add(Range_const(client_nonce));
     server_key->add(Range_const(server_nonce));
     server_key->add(Range_const(gxy,glen));
     
     const uint8 *server_digest=server_key->finish();
     
     if( server_hlen<key_buf.len )
       {
        (key_buf+=server_hlen).copy(server_digest);
        
        client_key->add(Range_const(server_digest,server_hlen));
       }
     else
       {
        key_buf.copy(server_digest);
        
        key_buf=Empty;
        
        return;
       }
    }
 }

void NegData::clientKeyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  keyBufGen(client_key,server_key);
 }

void NegData::serverKeyBufGen(AbstractHashFunc *client_key,AbstractHashFunc *server_key)
 {
  dhg->pow(gy,x,gxy);
  
  keyBufGen(client_key,server_key);
 }

/* class ClientNegotiant::Proc */

void ClientNegotiant::Proc::build1()
 {
  BufPutDev dev(send_buf);
  
  dev(client_id_len);
  
  dev.put(Range_const(client_id,client_id_len));
  
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
  
  neg_data.clientKeyGen(Range_const(client_id,client_id_len),client_key.getPtr(),server_key.getPtr());
  
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
  if( neg_data.process(data)!=PKE_ServerAck ) return false;
  
  RangeGetDev dev(data);
  
  CryptAlgoSelect algo;
  XPoint point=0;
  uint8 len=0;
  
  dev.use<BeOrder>(algo,point,len);
  
  PtrLen<const uint8> id=dev.getRange(len);
  
  if( !dev.finish() ) return false;
  
  if( algo!=neg_data.algo || point!=neg_data.point || !id.equal(Range_const(client_id,client_id_len)) ) return false;
  
  build5();
  
  inbound_func=&Proc::process6;
  
  return true;
 }

void ClientNegotiant::Proc::build5()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientAck);
  
  dev.use<BeOrder>(neg_data.algo,neg_data.point,client_id_len);
  
  dev.put(Range_const(client_id,client_id_len));
  
  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process6(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_ServerParam ) return false;
  
  RangeGetDev dev(data);
  
  SessionKeyParam temp;
  
  dev(temp);
  
  if( !dev.finish() ) return false;
  
  neg_data.param.select(temp);
  
  build7();
  
  inbound_func=&Proc::process8;
  
  return true;
 }

void ClientNegotiant::Proc::build7()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientParam);
  
  dev(neg_data.param);
  
  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process8(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_FirstServerSKey ) return false;
  
  RangeGetDev dev(data);

  dev.use<BeOrder>(neg_data.rep_count,neg_data.max_count);
  
  neg_data.cur_count=neg_data.max_count;
  
  dev.get(Range(neg_data.server_nonce));
  
  dev.get(Range(neg_data.gy,neg_data.glen));
  
  if( !dev.finish() ) return false;
  
  if( !neg_data.createSKey() ) return false;

  if( !neg_data.testCounts(server_key.getPtr()) ) return false;
  
  neg_data.clientGen();
  
  neg_data.clientKeyBufGen(client_key.getPtr(),server_key.getPtr());
  
  build9();
  
  if( !--neg_data.cur_count )
    {
     inbound_func=&Proc::process11;
    }
  else
    {
     inbound_func=&Proc::process10;
    }
  
  return true;
 }

void ClientNegotiant::Proc::build9()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientSKey);
  
  dev.use<BeOrder>(neg_data.cur_count);
  
  dev.put(Range_const(neg_data.client_nonce));
  
  dev.put(Range_const(neg_data.gx,neg_data.glen));
  
  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process10(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_ServerSKey ) return false;
  
  RangeGetDev dev(data);

  uint32 count=0;
  
  dev.use<BeOrder>(count);
  
  dev.get(Range(neg_data.server_nonce));
  
  dev.get(Range(neg_data.gy,neg_data.glen));
  
  if( !dev.finish() ) return false;
  
  if( count!=neg_data.cur_count ) return false;

  neg_data.clientGen();
  
  neg_data.clientKeyBufGen(client_key.getPtr(),server_key.getPtr());
  
  build9();
  
  if( !--neg_data.cur_count )
    {
     inbound_func=&Proc::process11;
    }
  
  return true;
 }

bool ClientNegotiant::Proc::process11(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_Done ) return false;

  if( +data ) return false;
  
  state=State_Done;
  
  return true;
 }

ClientNegotiant::Proc::Proc()
 {
 }

ClientNegotiant::Proc::~Proc()
 {
 }

void ClientNegotiant::Proc::prepare(ClientIDPtr &client_id_,PrimeKeyPtr &client_key_,PrimeKeyPtr &server_key_,SessionKeyParam param_)
 {
  if( state!=State_Null )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : not null");
    }
  
  neg_data.param=param_;
  
  Swap(client_key,client_key_);
  Swap(server_key,server_key_);
  
  if( !client_id_ )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no client id");
    }
  
  client_id_len=client_id_->getLen();
  
  client_id_->getID(client_id);
  
  if( !client_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no client key");
    }
  
  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no server key");
    }
  
  state=State_Ready;
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
  
  dev->attach(this);
 }

ClientNegotiant::Engine::~Engine()
 {
  dev->detach();
 }

void ClientNegotiant::Engine::prepare(ClientIDPtr &client_id,PrimeKeyPtr &client_key,PrimeKeyPtr &server_key,SessionKeyParam param)
 {
  Mutex::Lock lock(mutex);
  
  proc.prepare(client_id,client_key,server_key,param);
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

void ClientNegotiant::Engine::getSessionKey(MasterKeyPtr &skey)
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
  BufPutDev dev=neg_data.start(send_buf,PKE_ServerAck);
  
  dev.use<BeOrder>(neg_data.algo,neg_data.point,client_id_len);
  
  dev.put(Range_const(client_id,client_id_len));
  
  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process5(PtrLen<const uint8> data) -> InboundResult
 {
  if( neg_data.process(data)!=PKE_ClientAck ) return InboundDrop;
  
  RangeGetDev dev(data);
  
  CryptAlgoSelect algo;
  XPoint point=0;
  uint8 len=0;
  
  dev.use<BeOrder>(algo,point,len);
  
  PtrLen<const uint8> id=dev.getRange(len);
  
  if( !dev.finish() ) return InboundDrop;
  
  if( algo!=neg_data.algo || point!=neg_data.point || !id.equal(Range_const(client_id,client_id_len)) ) return InboundDrop;
  
  build6();
  
  inbound_func=&Proc::process7;
  
  final_send_len=0;
  
  return InboundOk;
 }

void ServerNegotiant::Proc::build6()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ServerParam);
  
  dev(engine->param);
  
  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process7(PtrLen<const uint8> data) -> InboundResult
 {
  if( neg_data.process(data)!=PKE_ClientParam ) return InboundDrop;
  
  RangeGetDev dev(data);
  
  dev(neg_data.param);
  
  if( !dev.finish() ) return InboundDrop;
  
  if( !neg_data.param.test() ) return InboundDrop;
  
  if( !neg_data.createSKey() ) return InboundDrop;
  
  build8();
  
  inbound_func=&Proc::process9;
  
  return InboundOk;
 }

void ServerNegotiant::Proc::build8()
 {
  neg_data.setCounts(engine->server_key.getPtr());
  
  neg_data.serverGen();

  BufPutDev dev=neg_data.start(send_buf,PKE_FirstServerSKey);
  
  dev.use<BeOrder>(neg_data.rep_count,neg_data.max_count);
  
  dev.put(Range_const(neg_data.server_nonce));
  
  dev.put(Range_const(neg_data.gx,neg_data.glen));
  
  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process9(PtrLen<const uint8> data) -> InboundResult
 {
  if( neg_data.process(data)!=PKE_ClientSKey ) return InboundDrop;
  
  RangeGetDev dev(data);

  uint32 count=0;
  
  dev.use<BeOrder>(count);
  
  dev.get(Range(neg_data.client_nonce));
  
  dev.get(Range(neg_data.gy,neg_data.glen));
  
  if( !dev.finish() ) return InboundDrop;
  
  if( count!=neg_data.cur_count ) return InboundDrop;

  neg_data.serverKeyBufGen(client_key.getPtr(),engine->server_key.getPtr());
  
  if( !--neg_data.cur_count )
    {
     build11();
     
     inbound_func=&Proc::process_final;
     
     return InboundLast;
    }
  else
    {
     build10();
     
     return InboundOk;
    }
 }

void ServerNegotiant::Proc::build10()
 {
  neg_data.serverGen();

  BufPutDev dev=neg_data.start(send_buf,PKE_ServerSKey);
  
  dev.use<BeOrder>(neg_data.cur_count);
  
  dev.put(Range_const(neg_data.server_nonce));
  
  dev.put(Range_const(neg_data.gx,neg_data.glen));
  
  send_len=neg_data.finish(send_buf,dev);
 }

void ServerNegotiant::Proc::build11()
 {
  BufPutDev dev=neg_data.start(final_send_buf,PKE_Done);
  
  final_send_len=neg_data.finish(final_send_buf,dev);
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
       
       engine->epman.open(neg_data.point,neg_data.skey,client_profile);
       
       engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
      }
     break;
     
     case InboundFinal :
      {
       engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
      }
     break; 
     
     case InboundDrop :
      {
       if( final_send_len )
         {
          engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
         }
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

ServerNegotiant::Engine::Engine(PacketMultipointDevice *dev_,AbstractClientDataBase &client_db_,EndpointManager &epman_,ulen max_clients_,MSec final_timeout)
 : dev(dev_),
   client_db(client_db_),
   epman(epman_),
   max_clients(max_clients_),
   pset("PSec::ServerNegotiant.pset"),
   mutex("PSec::ServerNegotiant.mutex")
 {
  outbound_format=dev->getOutboundFormat();
  
  final_tick_count=((+final_timeout)*InboundTicksPerSec)/1000+1;
  
  dev->attach(this);
 }

ServerNegotiant::Engine::~Engine()
 {
  dev->detach();
 }

void ServerNegotiant::Engine::prepare(PrimeKeyPtr &server_key_,SessionKeyParam param_)
 {
  Mutex::Lock lock(mutex);
  
  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::prepare(...) : already started");
    }

  param=param_;
  
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

ServerNegotiant::ServerNegotiant(StrLen mp_dev_name,AbstractClientDataBase &client_db,EndpointManager &epman,ulen max_clients,MSec final_timeout)
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
 

