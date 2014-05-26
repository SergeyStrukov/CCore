/* PSecCore.cpp */ 
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
 
#include <CCore/inc/net/PSecCore.h>
 
#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/crypton/PlatformSHA.h>
#include <CCore/inc/crypton/PlatformAES.h>
#include <CCore/inc/UIntSplit.h>

namespace CCore {
namespace Net {
namespace PSec {

/* class TestMasterKey */

using DefEncrypt = Crypton::AES256 ; // TODO Platform

using DefDecrypt = Crypton::AESInverse256 ; // TODO Platform

static const ulen DefKeyCount = 100 ;

TestMasterKey::TestMasterKey()
 {
 }
   
TestMasterKey::~TestMasterKey()
 {
 }

AbstractCryptFunc * TestMasterKey::createEncrypt() const
 {
  return new CryptFunc<DefEncrypt>();
 }

AbstractCryptFunc * TestMasterKey::createDecrypt() const
 {
  return new CryptFunc<DefDecrypt>();
 }

AbstractHashFunc * TestMasterKey::createHash() const
 {
  return new HashFunc<Crypton::PlatformSHA512>();
 }

AbstractRandomGen * TestMasterKey::createRandom() const
 {
  return new RandomGen<PlatformRandom>();
 }

ulen TestMasterKey::getKLen() const
 {
  return DefEncrypt::KeyLen;
 }

LifeLim TestMasterKey::getLifeLim() const
 {
  return LifeLim(UIntMax(),UIntMax());
 }

void TestMasterKey::getKey0(uint8 key[]) const
 {
  Range(key,DefEncrypt::KeyLen).set((uint8)DefKeyCount);
 }

ulen TestMasterKey::getKeySetLen() const
 {
  return DefKeyCount;
 }

void TestMasterKey::getKey(ulen index,uint8 key[]) const
 {
  Range(key,DefEncrypt::KeyLen).set((uint8)index);
 }

/* class RandomEngine */

void RandomEngine::addRandom(ulen count)
 {
  uint8 temp[ExtLen];
  
  for(; count>=ExtLen ;count-=ExtLen)
    {
     auto r=Range(temp);
    
     random->fill(r);
   
     hash->add(Range_const(r));
    }
  
  if( count )
    {
     auto r=Range(temp,count);
   
     random->fill(r);
  
     hash->add(Range_const(r));
    }
 }

ulen RandomEngine::addFifo(ulen count)
 {
  return fifo.get(count, [=] (const uint8 *ptr,ulen len) { hash->add(Range(ptr,len)); } );
 }

RandomEngine::RandomEngine(MasterKey &master_key)
 : random(master_key.createRandom()),
   hash(master_key.createHash())
 {
  buf=0;
  len=hash->getHLen();
  off=0;
 }

RandomEngine::~RandomEngine()
 {
 }

uint8 RandomEngine::next()
 {
  if( !buf )
    {
     addRandom(2*ExtLen+len);
    
     buf=hash->finish();
    }
  
  if( off>=len )
    {
     hash->add(Range(buf,len));
     
     ulen count=addFifo(ExtLen);
     
     addRandom(2*ExtLen-count);
     
     buf=hash->finish();
    }
  
  return buf[off++];
 }

/* class KeySet */

void KeySet::activate_base(ulen index)
 {
  Rec &rec=key_set[index];
 
  KeyIndex key_index=rec.base.makeKeyIndex(index);
  
  rec.active_index=active_count;
  
  active_list[active_count++]=key_index;
 }
   
void KeySet::activate_next(ulen index)
 {
  Rec &rec=key_set[index];
 
  KeyIndex key_index=rec.next.makeKeyIndex(index);
  
  rec.active_index=active_count;
  
  active_list[active_count++]=key_index;
 }
 
void KeySet::deactivate(ulen index)
 {
  Rec &rec=key_set[index];
  
  ulen i=rec.active_index;
  
  if( i<(--active_count) )
    {
     KeyIndex key_index=active_list[active_count];
         
     active_list[i]=key_index;
     
     key_set[GetIndex(key_index)].active_index=i;
    }
 }

KeySet::KeySet(MasterKey &master_key)
 : klen(master_key.getKLen()),
   life_lim(master_key.getLifeLim()),
   key_set(master_key.getKeySetLen()),
   key_buf(klen*(1+2*key_set.getLen())),
   active_list(key_set.getLen()),
   active_count(0)
 {
  uint8 *ptr=key_buf.getPtr();
  
  key0=ptr; ptr+=klen;
  
  for(ulen index=0,len=key_set.getLen(); index<len ;index++) 
    {
     Rec &rec=key_set[index];
    
     rec.base.key=ptr; ptr+=klen;
     rec.next.key=ptr; ptr+=klen;
     
     rec.base.state=KeyGreen;
     rec.base.life_lim=life_lim;
     
     activate_base(index);
    }
 }

KeySet::~KeySet()
 {
  Range(key_buf).set_null();
 }

bool KeySet::setEncryptKey(KeyIndex key_index,ulen use_count)
 {
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return false;

  Rec &rec=key_set[index];
  
  KeyIndex serial=GetSerial(key_index);
  
  if( rec.base.state<KeyRed && rec.base.testSerial(serial) ) 
    {
     encrypt_key=rec.base.key;
     
     rec.base.life_lim.use(use_count);
    
     return true;
    }
    
  if( rec.next.state<KeyRed && rec.next.testSerial(serial) ) 
    {
     encrypt_key=rec.base.key;
    
     rec.next.life_lim.use(use_count);
     
     return true;
    }
    
  return false;  
 }

bool KeySet::setDecryptKey(KeyIndex key_index)
 {
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return false;

  Rec &rec=key_set[index];
  
  KeyIndex serial=GetSerial(key_index);
  
  if( rec.base.state<KeyDead && rec.base.testSerial(serial) ) 
    {
     decrypt_key=rec.base.key;
    
     return true;
    }
    
  if( rec.next.state<KeyDead && rec.next.testSerial(serial) ) 
    {
     decrypt_key=rec.base.key;
    
     return true;
    }
    
  return false;  
 }

/* class ProcessorCore */

ulen ProcessorCore::selectIndex(ulen len)
 {
  UIntSplit<uint64,uint8> split;
  
  for(unsigned i=0; i<8 ;i++) split[i]=random();
  
  return split.get()%len;
 }

ProcessorCore::ProcessorCore(MasterKey &master_key)
 : encrypt(master_key.createEncrypt()),
   decrypt(master_key.createDecrypt()),
   hash(master_key.createHash()),
   random_engine(master_key),
   key_set(master_key)
 {
  blen=encrypt->getBLen();
  hlen=hash->getHLen();
 }

ProcessorCore::~ProcessorCore()
 {
 }

auto ProcessorCore::selectEncryptKey(ulen use_count) -> SelectResult
 {
  auto list=key_set.getActiveList();
  
  if( !list ) return Nothing;
  
  KeyIndex ret=list[selectIndex(list.len)];
  
  if( key_set.setEncryptKey(ret,use_count) ) return ret;
     
  return Nothing; 
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 

