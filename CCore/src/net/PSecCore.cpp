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
#include <CCore/inc/crypton/DHExp.h>
#include <CCore/inc/UIntSplit.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Net {
namespace PSec {

/* class TestMasterKey */

using DefEncrypt = Crypton::AES256 ;

using DefDecrypt = Crypton::AESInverse256 ;

using DefHash = Crypton::PlatformSHA512 ;

static const ulen DefKeyCount = 10 ;

using DefExp = Crypton::DHExp<Crypton::DHModII> ;

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
  return new HashFunc<DefHash>();
 }

AbstractKeyGen * TestMasterKey::createKeyGen() const
 {
  auto *ret=new KeyGen<DefExp,DefHash,DefEncrypt::KeyLen>;
  
  for(ulen i=0; i<ret->SecretCount ;i++) ret->takeSecret(i).set(uint8(i+1));
  
  return ret; 
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
  return LifeLim(100000,10000);
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

RandomEngine::RandomEngine(const MasterKey &master_key)
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
     
     off=0;
    }
  
  return buf[off++];
 }

/* class KeySet */

static unsigned SetIndex = 1 ;

static Mutex mux;

static PrintFile test("test.txt");

void KeySet::capture()
 {
  Mutex::Lock lock(mux);
  
  Printf(test,"#;\n\n",set_index);
  
  for(ulen i=0,len=key_set.getLen(); i<len ;i++)
    {
     Rec &rec=key_set[i];
    
     Printf(test,"rec[#;]\n",i);
     Printf(test,"  base serial = #; state = #; active = #;\n",rec.base.serial,rec.base.state,rec.base.active);
     Printf(test,"  next serial = #; state = #; active = #;\n",rec.next.serial,rec.next.state,rec.next.active);
     
     if( rec.type!=Packet_None )
       {
        Printf(test,"  #; #;:#;\n\n",rec.type,GetIndex(rec.key_index),GetSerial(rec.key_index));
       }
     else
       {
        Printf(test,"\n");
       }
    }
  
  Printf(test,"----------\n\n");
 }

void KeySet::capture(StrLen type,KeyIndex key_index)
 {
  Mutex::Lock lock(mux);
  
  Printf(test,"#; #;:#;\n",type,GetIndex(key_index),GetSerial(key_index));
  
  capture();
 }

void KeySet::Key::move(Key &obj)
 {
  serial=obj.serial;
  life_lim=obj.life_lim;
  state=Replace(obj.state,KeyDead);
  active=Replace(obj.active,false);
  
  Swap(key,obj.key);
 }

bool KeySet::Key::updateState(LifeLim initial)
 {
  switch( state )
    {
     case KeyGreen :
      {
       if( life_lim.isYellow(initial) ) 
         {
          state=KeyYellow;
          
          return true;
         }
      }
     return false;
     
     case KeyYellow :
      {
       if( life_lim.isRed(initial) ) state=KeyRed;
      }
     return false; 
     
     case KeyRed :
      {
       if( life_lim.isDead() ) state=KeyDead;
      }
     return false;
     
     default: return false;
    }
 }

void KeySet::activate_base(ulen index) // not active
 {
  Rec &rec=key_set[index];
 
  KeyIndex key_index=rec.base.activate(index);
  
  rec.active_index=active_count;
  
  active_list[active_count++]=key_index;
 }
   
void KeySet::activate_next(ulen index) // not active
 {
  Rec &rec=key_set[index];
 
  KeyIndex key_index=rec.next.activate(index);
  
  rec.active_index=active_count;
  
  active_list[active_count++]=key_index;
 }
 
void KeySet::deactivate(ulen index) // active
 {
  Rec &rec=key_set[index];
  
  rec.base.active=false;
  rec.next.active=false;
  
  ulen i=rec.active_index;
  
  if( i<(--active_count) )
    {
     KeyIndex key_index=active_list[active_count];
         
     active_list[i]=key_index;
     
     key_set[GetIndex(key_index)].active_index=i;
    }
 }

void KeySet::flip(ulen index) // base not active
 {
  Rec &rec=key_set[index];
  
  rec.flip();
 }

void KeySet::make_key(Rec &rec,const uint8 gy[])
 {
  key_gen->key(rec.x,gy,rec.next.key);
  
  rec.next.serial=NextSerial(rec.base.serial);
  rec.next.life_lim=life_lim;
  rec.next.state=KeyGreen;
 }

void KeySet::activate_key(Rec &rec,ulen index)
 {
  if( rec.base.active ) deactivate(index);
  
  activate_next(index);
 }

class KeySet::BufInit : NoCopy
 {
   uint8 *ptr;
   ulen len;
   
  public: 
   
   BufInit(uint8 *ptr_,ulen len_) : ptr(ptr_),len(len_) {}
   
   uint8 * get()
    {
     uint8 *ret=ptr;
    
     ptr=ret+len;
    
     return ret;
    }
 };

class KeySet::KeyInit : BufInit
 {
  public: 
   
   KeyInit(uint8 *ptr,ulen klen) : BufInit(ptr,klen) {}
   
   uint8 * operator () () { return get(); }
   
   uint8 * operator () (const MasterKey &master_key)
    {
     uint8 *ret=get();
     
     master_key.getKey0(ret);
     
     return ret;
    }
   
   uint8 * operator () (const MasterKey &master_key,ulen index)
    {
     uint8 *ret=get();
     
     master_key.getKey(index,ret);
     
     return ret;
    }
 };

class KeySet::GenInit : BufInit
 {
  public:
 
   GenInit(uint8 *ptr,ulen glen) : BufInit(ptr,glen) {}
 
   uint8 * operator () () { return get(); }
 };

KeyResponse KeySet::alert(Rec &rec,KeyIndex key_index)
 {
  rec.type=Packet_Alert;
  rec.key_index=key_index;
  rec.repeat.reset();
  
  core.random(Range(rec.x,glen));
  
  key_gen->pow(rec.x,rec.gx);
  
  return KeyResponse(Packet_Alert,key_index,Range_const(rec.gx,glen));
 }

KeySet::KeySet(const MasterKey &master_key,ProcessorCore &core_)
 : set_index(SetIndex++),
   klen(master_key.getKLen()),
   life_lim(master_key.getLifeLim()),
   key_set(master_key.getKeySetLen()),
   key_buf(klen*(1+2*key_set.getLen())),
   active_list(key_set.getLen()),
   key_gen(master_key.createKeyGen()),
   glen(key_gen->getGLen()),
   rekey_buf(glen*(2*key_set.getLen())),
   core(core_)
 {
  KeyInit kinit(key_buf.getPtr(),klen);
  GenInit ginit(rekey_buf.getPtr(),glen);
  
  key0=kinit(master_key);
  
  for(ulen index=0,len=key_set.getLen(); index<len ;index++) 
    {
     Rec &rec=key_set[index];
    
     rec.base.init(kinit(master_key,index),life_lim);
     
     rec.next.init(kinit());
     
     rec.x=ginit();
     rec.gx=ginit();
     
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
  
  if( rec.base.active ) 
    {
     if( rec.base.state<KeyRed )
       {
        encrypt_key=rec.base.key;
       
        rec.base.use(use_count);
       
        return true;
       }
     else
       {
        deactivate(index);
       
        return false;
       }
    }
    
  if( rec.next.active ) 
    {
     if( rec.next.state<KeyRed )
       {
        encrypt_key=rec.next.key;
      
        rec.next.use(use_count);
       
        return true;
       }
     else
       {
        deactivate(index);
        
        return false;
       }
    }
    
  return false;  
 }

bool KeySet::setDecryptKey(KeyIndex key_index)
 {
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return false;

  Rec &rec=key_set[index];
  
  KeyIndex serial=GetSerial(key_index);
  
  if( rec.base.testSerial(serial) ) 
    {
     decrypt_key=rec.base.key;
      
     return true;
    }
    
  if( rec.next.testSerial(serial) ) 
    {
     decrypt_key=rec.next.key;
      
     return true;
    }
    
  return false;  
 }

KeyResponse KeySet::tick()
 {
  capture();
  
  ulen count=key_set.getLen();
  
  if( !count ) return Nothing;
  
  ulen index=tick_index++;
  
  if( tick_index>=count ) tick_index=0;
  
  Rec &rec=key_set[index];
  
  rec.tick();
  
  if( rec.base.updateState(life_lim) )
    {
     if( rec.type==Packet_None )
       {
        return alert(rec,rec.base.makeKeyIndex(index));
       }
     else
       {
        // going to die
       
        return Nothing; 
       }
    }
  
  if( rec.next.updateState(life_lim) )
    {
     if( rec.type==Packet_None )
       {
        flip(index);
        
        return alert(rec,rec.base.makeKeyIndex(index));
       }
     else
       {
        // going to die
       
        return Nothing; 
       }
    }
  
  if( rec.resend() )
    {
     return rec.makeResponse(glen);
    }
  
  return Nothing;
 }

KeyResponse KeySet::alert(KeyIndex key_index,const uint8 gy[])
 {
  capture("alert",key_index);
  
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return Nothing;
  
  Rec &rec=key_set[index];
  
  if( rec.type==Packet_None )
    {
     if( rec.base.active )
       {
        if( rec.base.makeKeyIndex(index)==key_index ) 
          {
           alert(rec,key_index);
           
           rec.type=Packet_Ready;
          
           make_key(rec,gy);
          
           return rec.makeResponse(glen);
          }
        else
          {
           return Nothing;
          }
       }
    
     if( rec.next.active )
       {
        if( rec.next.makeKeyIndex(index)==key_index ) 
          {
           flip(index);
           
           alert(rec,key_index);
          
           rec.type=Packet_Ready;
         
           make_key(rec,gy);
         
           return rec.makeResponse(glen);
          }
        else
          {
           return Nothing;
          }
       }
    }
  
  if( rec.type==Packet_Alert )
    {
     if( rec.key_index!=key_index ) return Nothing;
   
     rec.type=Packet_Ready;
    
     make_key(rec,gy);
    
     return rec.makeResponse(glen);
    }
  
  return Nothing;
 }

KeyResponse KeySet::ready(KeyIndex key_index,const uint8 gy[])
 {
  capture("ready",key_index);
  
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return Nothing;
  
  Rec &rec=key_set[index];
  
  if( rec.type==Packet_Alert )
    {
     if( rec.key_index!=key_index ) return Nothing;
    
     rec.type=Packet_Ready;
     
     make_key(rec,gy);
     
     activate_key(rec,index);
     
     return rec.makeResponse(glen);
    }
  
  if( rec.type==Packet_Ready )
    {
     if( rec.key_index!=key_index ) return Nothing;
    
     rec.type=Packet_Ack;
     
     activate_key(rec,index);
     
     return rec.makeResponse(glen);
    }
  
  return Nothing;
 }

KeyResponse KeySet::ack(KeyIndex key_index)
 {
  capture("ack",key_index);
  
  ulen index=GetIndex(key_index);
  
  if( index>=key_set.getLen() ) return Nothing;
  
  Rec &rec=key_set[index];
  
  if( rec.type==Packet_Ready )
    {
     if( rec.key_index!=key_index ) return Nothing;
   
     rec.type=Packet_Ack;
    
     return rec.makeResponse(glen);
    }
  
  if( rec.type==Packet_Ack )
    {
     if( rec.key_index!=key_index ) return Nothing;
  
     rec.type=Packet_None;
     
     return rec.makeResponse(glen);
    }
  
  if( rec.type==Packet_None )
    {
     return KeyResponse(Packet_Ack,key_index);
    }
  
  return Nothing; 
 }

/* class ProcessorCore */

void ProcessorCore::random(PtrLen<uint8> data)
 {
  for(uint8 &x : data ) x=random();
 }

ulen ProcessorCore::selectIndex(ulen len)
 {
  UIntSplit<uint64,uint8> split;
  
  for(unsigned i=0; i<8 ;i++) split[i]=random();
  
  return split.get()%len;
 }

ulen ProcessorCore::selectLen(ulen min_len,ulen max_len)
 {
  if( min_len>=max_len ) return min_len;
  
  return min_len+selectIndex(max_len-min_len+1);
 }

ProcessorCore::ProcessorCore(const MasterKey &master_key)
 : encrypt(master_key.createEncrypt()),
   decrypt(master_key.createDecrypt()),
   hash(master_key.createHash()),
   random_engine(master_key),
   key_set(master_key,*this)
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

/* class AntiReplay */

AntiReplay::BitFlags::BitFlags()
 {
  Range(bits).set_null();
 }

AntiReplay::BitFlags::~BitFlags()
 {
  Range(bits).set_null();
 }

AntiReplay::Unit AntiReplay::BitFlags::test(SequenceNumber num) const
 {
  return bits[Index(num)]&Mask(num);
 }

void AntiReplay::BitFlags::set(SequenceNumber num)
 {
  bits[Index(num)]|=Mask(num);
 }

void AntiReplay::BitFlags::shift(SequenceNumber shift)
 {
  if( shift>=WinLen )
    {
     Range(bits).set_null();
    }
  else
    {
     unsigned n=unsigned( shift/UnitBits );
     unsigned s=unsigned( shift%UnitBits );
    
     if( s )
       {
        unsigned i=0;
       
        for(unsigned lim=WinUnits-n-1; i<lim ;i++) bits[i]=Shift(bits[i+n+1],bits[i+n],s); 
       
        bits[i]=Shift(0,bits[i+n],s);
        
        for(; i<WinUnits ;i++) bits[i]=0;
       }
     else
       {
        unsigned i=0;
      
        for(unsigned lim=WinUnits-n; i<lim ;i++) bits[i]=bits[i+n]; 
      
        for(; i<WinUnits ;i++) bits[i]=0;
       }
    }
 }

AntiReplay::AntiReplay()
 {
  base=0;
 }

AntiReplay::~AntiReplay()
 {
 }

bool AntiReplay::testReplay(SequenceNumber num) const
 {
  num-=base;
  
  if( num<WinLen ) return flags.test(num);
  
  return num>=WinLen+ForeLen;
 }

void AntiReplay::add(SequenceNumber num)
 {
  num-=base;
  
  if( num<WinLen )
    {
     flags.set(num);
    }
  else
    {
     SequenceNumber shift=num-WinLen+1; 
    
     base+=shift;
    
     flags.shift(shift);
     flags.set(WinLen-1);
    }
 }

} // namespace PSec 
} // namespace Net
} // namespace CCore
 

