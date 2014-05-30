/* PSecCore.h */ 
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

#ifndef CCore_inc_net_PSecCore_h
#define CCore_inc_net_PSecCore_h
 
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/BlockFifo.h>
#include <CCore/inc/Timer.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

const ulen DLen = 15 ;

enum Packets
 {
  Packet_Data,
  Packet_Alert,
  Packet_Ready,
  Packet_Ack,
  
  Packet_None
 };

/* types */

using KeyIndex = uint16 ;

using SequenceNumber = uint32 ;

using PadLen = uint8 ;

using PacketType = uint8 ;

/* functions */

template <class UInt,class UInt1>
void PosDec(UInt &var,UInt1 val)
 {
  if( val<=var )
    var-=(UInt)val;
  else
    var=0;
 }

/* classes */

struct AbstractCryptFunc;

template <class Crypt> class CryptFunc;

struct AbstractHashFunc;

template <class Hash> class HashFunc;

struct AbstractKeyGen;  

struct AbstractRandomGen;

template <class Rand> class RandomGen;

struct LifeLim;

struct MasterKey;

class TestMasterKey;

class RandomEngine;

struct KeyResponse;

class KeySet;

template <class A,class B> class Convolution;

class ConvolutionMul;

template <uint8 K> class ConvolutionMulConst;

template <uint8 ... KK> struct ConvolutionParam;

class DirectConvolution;

class InverseConvolution;

class ProcessorCore;

class AntiReplay;

/* struct AbstractCryptFunc */

struct AbstractCryptFunc : MemBase_nocopy
 {
  virtual ~AbstractCryptFunc() {}
  
  virtual ulen getBLen() const =0;
  
  virtual ulen getKLen() const =0;
  
  virtual void key(const uint8 key[])=0;
  
  virtual void apply(uint8 block[]) const =0;
 };

/* class CryptFunc<Crypt> */

template <class Crypt> 
class CryptFunc : public AbstractCryptFunc 
 {
   Crypt crypt;
   
  public:
  
   CryptFunc() {}
   
   virtual ~CryptFunc() {}
   
   // AbstractCryptFunc
   
   virtual ulen getBLen() const
    {
     return Crypt::BlockLen;
    }
   
   virtual ulen getKLen() const
    {
     return Crypt::KeyLen;
    }
   
   virtual void key(const uint8 key[])
    {
     crypt.key(key);
    }
   
   virtual void apply(uint8 block[]) const
    {
     crypt.apply(block);
    }
 };

/* struct AbstractHashFunc */

struct AbstractHashFunc : MemBase_nocopy
 {
  virtual ~AbstractHashFunc() {}
  
  virtual ulen getHLen() const =0;
  
  virtual void add(PtrLen<const uint8> data)=0;
  
  virtual const uint8 * finish()=0;
 };

/* class HashFunc<Hash> */

template <class Hash> 
class HashFunc : public AbstractHashFunc  
 {
   Hash hash;
   
   uint8 digest[Hash::DigestLen];
   
  public:
  
   HashFunc() {}
   
   virtual ~HashFunc() { Range(digest).set_null(); }
   
   // AbstractHashFunc
   
   virtual ulen getHLen() const
    {
     return Hash::DigestLen;
    }
   
   virtual void add(PtrLen<const uint8> data)
    {
     hash.add(data);
    }
   
   virtual const uint8 * finish()
    {
     hash.finish(digest);
     
     return digest;
    }
 };

/* struct AbstractKeyGen */

struct AbstractKeyGen : MemBase_nocopy
 {
  virtual ~AbstractKeyGen() {}
  
  virtual ulen getGLen() const =0;
  
  virtual ulen getKLen() const =0;
  
  virtual void pow(const uint8 x[],uint8 gx[]) const =0;
  
  virtual void key(const uint8 x[],const uint8 gy[],uint8 key[]) const =0;
 };

/* struct AbstractRandomGen */

struct AbstractRandomGen : MemBase_nocopy
 {
  virtual ~AbstractRandomGen() {}
  
  virtual void fill(PtrLen<uint8> buf)=0;
 };

/* class RandomGen<Rand> */

template <class Rand> 
class RandomGen : public AbstractRandomGen
 {
   Rand rand;
  
  public:
   
   RandomGen() {}
   
   virtual ~RandomGen() {}
   
   // AbstractRandomGen
   
   virtual void fill(PtrLen<uint8> buf)
    { 
     rand.fill(buf); 
    }
 };

/* struct LifeLim */

struct LifeLim
 {
  uint32 ttl; // sec
  uint32 utl;
  
  LifeLim() : ttl(0),utl(0) {}
  
  LifeLim(uint32 ttl_,uint32 utl_) : ttl(ttl_),utl(utl_) {}
  
  bool isYellow(LifeLim initial) const
   {
    return ttl<initial.ttl/2 || utl<initial.utl/2 ;
   }
  
  bool isRed(LifeLim initial) const
   {
    return ttl<initial.ttl/4 || utl<initial.utl/4 ;
   }
  
  bool isDead() const
   {
    return !ttl || !utl ;
   }
  
  template <class UInt>
  void use(UInt use_count) { PosDec(utl,use_count); }
 
  template <class UInt>
  void tick(UInt dtime) { PosDec(ttl,dtime); }
 };

/* struct MasterKey */

struct MasterKey : MemBase_nocopy
 {
  virtual ~MasterKey() {}
  
  // factory

  virtual AbstractCryptFunc * createEncrypt() const =0;
  
  virtual AbstractCryptFunc * createDecrypt() const =0;
  
  virtual AbstractHashFunc * createHash() const =0;
  
  virtual AbstractKeyGen * createKeyGen() const =0;
  
  virtual AbstractRandomGen * createRandom() const =0;
  
  // keys
  
  virtual ulen getKLen() const =0;
  
  virtual LifeLim getLifeLim() const =0;
  
  virtual void getKey0(uint8 key[]) const =0;
  
  virtual ulen getKeySetLen() const =0;
  
  virtual void getKey(ulen index,uint8 key[]) const =0;
 };

/* class TestMasterKey */

class TestMasterKey : public MasterKey
 {
  public:
  
   TestMasterKey();
   
   virtual ~TestMasterKey();
   
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
   
   virtual void getKey0(uint8 key[]) const;
   
   virtual ulen getKeySetLen() const;
   
   virtual void getKey(ulen index,uint8 key[]) const;
 };

/* class RandomEngine */

class RandomEngine : NoCopy
 {
   static const ulen ExtLen = 256 ;
  
   class Fifo : public BlockFifo<uint8>
    {
      static const ulen Len = 2*ExtLen ;
     
      uint8 buf[Len];
      
     public:
     
      Fifo() : BlockFifo<uint8>(buf,Len) {}
      
      ~Fifo() { Range(buf).set_null(); }
    };
   
   Fifo fifo;
  
   OwnPtr<AbstractRandomGen> random;
   OwnPtr<AbstractHashFunc> hash;

   const uint8 *buf;
   ulen len;
   ulen off;
   
  private:
  
   void addRandom(ulen count);
   
   ulen addFifo(ulen count);
 
  public:
  
   explicit RandomEngine(const MasterKey &master_key);
   
   ~RandomEngine();
   
   uint8 next();
   
   void feed(PtrLen<const uint8> block) { fifo.put(block); }
 };

/* struct KeyResponse */

struct KeyResponse
 {
  Packets type;
  KeyIndex key_index;
  PtrLen<const uint8> gx;
  
  KeyResponse(NothingType) : type(Packet_None),key_index(0) {}
  
  KeyResponse(Packets type_,KeyIndex key_index_,PtrLen<const uint8> gx_=Empty) 
   : type(type_),key_index(key_index_),gx(gx_)
   {
   }
 };

/* class KeySet */

class KeySet : NoCopy // TODO
 {
   ulen klen;
   LifeLim life_lim;
  
   enum KeyState
    {
     KeyGreen,
     KeyYellow,
     KeyRed,
     KeyDead
    };
   
   struct Key : NoCopy 
    {
     uint8 *key = 0 ;
     KeyIndex serial = 0 ; // 2 bits
     LifeLim life_lim;
     KeyState state = KeyDead ;
     bool active = false ;
     
     Key() {}
     
     void init(uint8 *key_,LifeLim life_lim_)
      {
       key=key_;
       life_lim=life_lim_;
       state=KeyGreen;
      }
     
     void init(uint8 *key_)
      {
       key=key_;
      }
     
     bool testSerial(KeyIndex serial_) const { return state<KeyDead && serial_==serial ; }
     
     KeyIndex makeKeyIndex(ulen index) const { return KeyIndex( index|(serial<<14) ); }
     
     KeyIndex activate(ulen index) 
      { 
       active=true;
       
       return makeKeyIndex(index); 
      }
     
     void move(Key &obj);
     
     template <class UInt>
     void use(UInt use_count)
      {
       if( state<KeyDead ) life_lim.use(use_count);
      }
     
     template <class UInt>
     void tick(UInt dtime)
      {
       if( state<KeyDead ) life_lim.tick(dtime);
      }
    
     bool updateState(LifeLim initial);    
    };
   
   struct Repeat
    {
     unsigned timeout; // sec
     
     Repeat() { reset(); }
     
     bool operator ! () const { return !timeout; }
     
     void reset() { timeout=20; }
     
     template <class UInt>
     void tick(UInt dtime) { PosDec(timeout,dtime); }
    };
   
   struct Rec : NoThrowFlagsBase
    {
     Key base;
     Key next;
     
     SecDiffTimer timer;
     
     ulen active_index = 0 ;
     
     uint8 *x = 0 ;
     uint8 *gx = 0 ;
     Packets type = Packet_None ;
     KeyIndex key_index = 0 ;
     
     Repeat repeat;
     
     Rec() {}
     
     void tick()
      {
       auto dtime=timer.get();
       
       base.tick(dtime);
       next.tick(dtime);
       
       if( type!=Packet_None ) repeat.tick(dtime);
      }
    
     KeyResponse makeResponse(ulen glen)
      { 
       repeat.reset();
       
       if( type==Packet_Ack ) return KeyResponse(type,key_index);
       
       return KeyResponse(type,key_index,Range_const(gx,glen));
      }
    };
   
   DynArray<Rec> key_set;
   DynArray<uint8> key_buf;
   DynArray<KeyIndex> active_list;
   
   ulen active_count = 0 ;
   
   uint8 *key0 = 0 ;
   const uint8 *encrypt_key = 0 ;
   const uint8 *decrypt_key = 0 ;
   
   ulen tick_index = 0 ;
   
  private:
   
   class BufInit;
   class KeyInit;
   class GenInit;
   
   static ulen GetIndex(KeyIndex key_index) { return ulen( key_index&0x3FFF ); }
   
   static KeyIndex GetSerial(KeyIndex key_index) { return KeyIndex( key_index>>14 ); }
   
   void activate_base(ulen index);
   
   void activate_next(ulen index);
   
   void deactivate(ulen index);
   
   void flip(ulen index);
   
  private: 
   
   OwnPtr<AbstractKeyGen> key_gen;
   
   ulen glen;
   
   DynArray<uint8> rekey_buf;
   
   ProcessorCore &core;
   
  private: 
   
   KeyResponse alert(Rec &rec,KeyIndex key_index);
   
  public:
  
   KeySet(const MasterKey &master_key,ProcessorCore &core);
   
   ~KeySet();
   
   // keys
   
   const uint8 * getKey0() const { return key0; }
   
   PtrLen<const KeyIndex> getActiveList() const { return Range(active_list).prefix(active_count); }
   
   bool setEncryptKey(KeyIndex key_index,ulen use_count);
   
   const uint8 * getEncryptKey() const { return encrypt_key; }
   
   bool setDecryptKey(KeyIndex key_index);
   
   const uint8 * getDecryptKey() const { return decrypt_key; }
   
   // key exchange
   
   ulen getGLen() const { return glen; }
   
   KeyResponse tick();
   
   KeyResponse alert(KeyIndex key_index,const uint8 gy[]);
   
   KeyResponse ready(KeyIndex key_index,const uint8 gy[]);
   
   KeyResponse ack(KeyIndex key_index);
 };

/* class Convolution<A,B> */

template <class A,class B>
class Convolution : NoCopy
 {
   uint8 a[A::Len];
   uint8 b[B::Len];
   
  private:
   
   template <ulen Len>
   static void Push(uint8 (&buf)[Len],uint8 x)
    {
     buf[Len-1]=x;
    }
  
   template <class K,ulen Len>
   static uint8 MulAdd(const K (&k)[Len],uint8 (&buf)[Len],uint8 x)
    {
     x^=k[Len-1](buf[0]);
     
     for(ulen i=1; i<Len ;i++) 
       {
        uint8 t=buf[i];
       
        x^=k[Len-1-i](t);
        
        buf[i-1]=t;
       }
     
     return x;
    }
   
  public:
  
   Convolution() { start(); }
   
   ~Convolution() { start(); }
   
   void start()
    {
     Range(a).set_null();
     Range(b).set_null();
    }
   
   uint8 next(uint8 x)
    {
     uint8 y=x;
     
     y=MulAdd(A::Mul,a,y);
     y=MulAdd(B::Mul,b,y);
     
     Push(a,x);
     Push(b,y);
     
     return y;
    }
 };

/* class ConvolutionMul */

class ConvolutionMul
 {
   const uint8 *table;
  
  public: 
   
   explicit ConvolutionMul(const uint8 *table_) : table(table_) {}
  
   uint8 operator () (uint8 x) const { return table[x]; }
   
   static uint8 MulX(uint8 a)
    {
     if( a&0x80 )
       return uint8( (a<<1)^0x1b );
     else
       return uint8( a<<1 );
    }
   
   static uint8 Mul(uint8 a,uint8 b)
    {
     uint8 ret=0;
     
     for(; b ;b>>=1,a=MulX(a)) if( b&1 ) ret^=a;
     
     return ret;
    }
 };

/* class ConvolutionMulConst<uint8 K> */

template <uint8 K>
class ConvolutionMulConst : public ConvolutionMul 
 {
   class TableInit
    {
      uint8 table[256];
     
     public:
     
      TableInit()
       {
        for(ulen i=0; i<256 ;i++) table[i]=Mul(K,uint8(i));
       }
      
      operator const uint8 * () const { return table; }
    };
 
   static TableInit Table;
 
  public:
  
   ConvolutionMulConst() : ConvolutionMul(Table) {}
 };

template <uint8 K>
typename ConvolutionMulConst<K>::TableInit ConvolutionMulConst<K>::Table;

/* struct ConvolutionParam<uint8 ... KK> */

template <uint8 ... KK>
struct ConvolutionParam
 {
  static const ulen Len = sizeof ... (KK) ;
  
  static const ConvolutionMul Mul[Len]; 
 };

template <uint8 ... KK>
const ConvolutionMul ConvolutionParam<KK...>::Mul[Len]={ ConvolutionMulConst<KK>() ... }; 

/* class DirectConvolution */

using ConvolutionParamA = ConvolutionParam<1,2,3> ;

using ConvolutionParamB = ConvolutionParam<4,5,6> ;

class DirectConvolution : NoCopy
 {
   Convolution<ConvolutionParamA,ConvolutionParamB> conv;
  
  public:
  
   DirectConvolution() {}
   
   ~DirectConvolution() {}
   
   void start() { conv.start(); }
   
   void apply(PtrLen<uint8> block) { for(uint8 &x : block ) x=conv.next(x); }
 };

/* class InverseConvolution */

class InverseConvolution : NoCopy
 {
   Convolution<ConvolutionParamB,ConvolutionParamA> conv;
   
  public:
  
   InverseConvolution() {}
   
   ~InverseConvolution() {}
   
   void start() { conv.start(); }
   
   void apply(PtrLen<uint8> block) { for(uint8 &x : block ) x=conv.next(x); }
 };

/* class ProcessorCore */

class ProcessorCore : NoCopy
 {
   OwnPtr<AbstractCryptFunc> encrypt;
   OwnPtr<AbstractCryptFunc> decrypt;
   OwnPtr<AbstractHashFunc> hash;
 
   ulen blen;
   ulen hlen;
   
   RandomEngine random_engine;
   
   KeySet key_set;
   
   DirectConvolution direct_conv;
   InverseConvolution inverse_conv;
   
  private:
   
   void feed(const uint8 block[]) { random_engine.feed(Range(block,blen)); }
   
  public:
  
   explicit ProcessorCore(const MasterKey &master_key);
   
   ~ProcessorCore();
   
   // properties
   
   ulen getBLen() const { return blen; }
   
   ulen getHLen() const { return hlen; }
   
   // random
   
   uint8 random() { return random_engine.next(); }
   
   void random(PtrLen<uint8> data);
   
   ulen selectIndex(ulen len);
   
   ulen selectLen(ulen min_len,ulen max_len);
   
   // encrypt
   
   struct SelectResult
    {
     KeyIndex key_index;
     bool ok;
     
     SelectResult(NothingType) : key_index(0),ok(false) {}
     
     SelectResult(KeyIndex key_index_) : key_index(key_index_),ok(true) {}
    };
   
   SelectResult selectEncryptKey(ulen use_count);
   
   void setEncryptKey0() { encrypt->key(key_set.getKey0()); }
   
   void setEncryptKey() { encrypt->key(key_set.getEncryptKey()); }
   
   void startEncrypt() { direct_conv.start(); }
   
   void applyEncrypt(uint8 block[])
    {
     direct_conv.apply(Range(block,blen));
     
     encrypt->apply(block); 
     
     feed(block); 
    }
   
   // decrypt
   
   bool setDecryptKey(KeyIndex key_index) { return key_set.setDecryptKey(key_index); }
   
   void setDecryptKey0() { decrypt->key(key_set.getKey0()); }
   
   void setDecryptKey() { decrypt->key(key_set.getDecryptKey()); }
   
   void startDecrypt() { inverse_conv.start(); }
   
   void applyDecrypt(uint8 block[])
    { 
     decrypt->apply(block);
     
     inverse_conv.apply(Range(block,blen));
    }
   
   // hash
   
   void add(PtrLen<const uint8> data) { hash->add(data); }  
   
   const uint8 * finish() { return hash->finish(); }
   
   // key exchange
   
   ulen getGLen() const { return key_set.getGLen(); }
   
   KeyResponse tick() { return key_set.tick(); }
   
   KeyResponse alert(KeyIndex key_index,const uint8 gy[]) { return key_set.alert(key_index,gy); }
   
   KeyResponse ready(KeyIndex key_index,const uint8 gy[]) { return key_set.ready(key_index,gy); }
   
   KeyResponse ack(KeyIndex key_index) { return key_set.ack(key_index); }
 };

/* class AntiReplay */

class AntiReplay : NoCopy
 {
   using Unit = unsigned ;
   
   static const unsigned UnitBits = Meta::UIntBits<Unit>::Ret ;
   static const unsigned WinUnits = 128 ;
   static const SequenceNumber WinLen = UnitBits*WinUnits ;
   static const SequenceNumber ForeLen = 1000000 ;
   
   SequenceNumber base;
   
   class BitFlags : NoCopy
    {
      Unit bits[WinUnits];
     
     private:
      
      static unsigned Index(SequenceNumber num) { return num/UnitBits; }
      
      static Unit Mask(SequenceNumber num) { return Unit(1)<<(num%UnitBits); }
      
      static Unit Shift(Unit hi,Unit lo,unsigned shift) { return (lo>>shift)|(hi<<(UnitBits-shift)); }
      
     public:
     
      BitFlags();
      
      ~BitFlags();
      
      Unit test(SequenceNumber num) const;
      
      void set(SequenceNumber num);
      
      void shift(SequenceNumber shift);
    };
   
   BitFlags flags;
  
  public:
  
   AntiReplay();
   
   ~AntiReplay();
   
   bool testReplay(SequenceNumber num) const;
   
   void add(SequenceNumber num);
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 

