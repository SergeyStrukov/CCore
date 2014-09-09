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

#include <CCore/inc/crypton/Forget.h>

#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

const ulen MinBLen = 8 ;

const ulen MaxBLen = 64 ;

const ulen MinKLen = 16 ;

const ulen MaxKLen = 512 ;

const ulen MinHLen = 16 ;

const ulen MaxHLen = 64 ;

const ulen MinGLen = 64 ;

const ulen MaxGLen = 512 ;

const ulen DLen = 15 ;

const unsigned RepeatTimeout = 20 ; // sec

const unsigned PingRepeatTimeout = 5 ; // sec

enum Packets
 {
  Packet_Data,
  
  Packet_Alert,
  Packet_Ready,
  Packet_Ack,
  Packet_Stop,
  
  Packet_Ping,
  Packet_Pong,
  Packet_Close,
  
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
  static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::Net::PSec::PosDec<UInt,UInt1> : UInt must be an unsigned integral type");
  static_assert( Meta::IsUInt<UInt1>::Ret ,"CCore::Net::PSec::PosDec<UInt,UInt1> : UInt1 must be an unsigned integral type");
  
  if( val<=var )
    var-=(UInt)val;
  else
    var=0;
 }

inline bool IsLifetimePacket(Packets type)
 {
  switch( type )
    {
     case Packet_Ping :
     case Packet_Pong :
     case Packet_Close : return true;
     
     default: return false;
    }
 }

/* classes */

struct AlgoLen;

struct AbstractCryptFunc;

template <class Crypt> class CryptFunc;

struct AbstractHashFunc;

template <class Hash> class HashFunc;

struct AbstractKeyGen;

template <class Exp> class KeyGen;

struct AbstractDHGroup;

template <class Exp> class DHGroup;

struct AbstractRandomGen;

template <class Rand> class RandomGen;

struct LifeLim;

struct MasterKey;

struct AbstractClientProfile;

struct EndpointManager;

class TestMasterKey;

class RandomEngine;

struct ControlResponse;

class KeySet;

template <class A,class B> class Convolution;

class ConvolutionMul;

template <uint8 K> class ConvolutionMulConst;

template <uint8 ... KK> struct ConvolutionParam;

class DirectConvolution;

class InverseConvolution;

class ProcessorCore;

class AntiReplay;

class KeepAlive;

/* struct AlgoLen */

struct AlgoLen : NoThrowFlagsBase
 {
  ulen blen;
  ulen hlen;
  
  AlgoLen(ulen blen_,ulen hlen_) : blen(blen_),hlen(hlen_) {}
 };

/* struct AbstractCryptFunc */

struct AbstractCryptFunc : MemBase_nocopy
 {
  virtual ~AbstractCryptFunc() {}
  
  virtual ulen getBLen() const =0;
  
  virtual ulen getKLen() const =0;
  
  virtual void key(const uint8 key[ /* KLen */ ])=0;
  
  virtual void apply(uint8 block[ /* BLen */ ]) const =0;
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
     static_assert( Crypt::BlockLen>=MinBLen && Crypt::BlockLen<=MaxBLen ,"CCore::Net::PSec::CryptFunc<...> : bad BLen");
     
     return Crypt::BlockLen;
    }
   
   virtual ulen getKLen() const
    {
     static_assert( Crypt::KeyLen>=MinKLen && Crypt::KeyLen<=MaxKLen ,"CCore::Net::PSec::CryptFunc<...> : bad KLen");
     
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
  
  virtual const uint8 * finish()=0; /* [HLen] */
 };

/* class HashFunc<Hash> */

template <class Hash> 
class HashFunc : public AbstractHashFunc  
 {
   Hash hash;
   
   uint8 digest[Hash::DigestLen];
   
  public:
  
   HashFunc() {}
   
   explicit HashFunc(PtrLen<const uint8> key) { hash.key(key); }
   
   virtual ~HashFunc() { Crypton::Forget(digest); }
   
   // AbstractHashFunc
   
   virtual ulen getHLen() const
    {
     static_assert( Hash::DigestLen>=MinHLen && Hash::DigestLen<=MaxHLen ,"CCore::Net::PSec::HashFunc<...> : bad HLen");
     
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
  
  virtual void pow(const uint8 x[ /* GLen */ ],uint8 gx[ /* GLen */ ])=0;
  
  virtual void key(const uint8 x[ /* GLen */ ],const uint8 gy[ /* GLen */ ],uint8 key[ /* KLen */ ])=0;
 };

/* class KeyGen<Exp> */

template <class Exp> 
class KeyGen : public AbstractKeyGen 
 {
   static const ulen GLen = Exp::GLen ;

   Exp exp;
   
   OwnPtr<AbstractHashFunc> hash;
   ulen klen;
   ulen hlen;

   DynArray<uint8> secret_buf;
   
   uint8 gxy[GLen];
   uint8 gxys[GLen];
   
  public:
   
   static ulen GetSecretLen(ulen klen,ulen hlen) { return GLen*(1+(klen+hlen-1)/hlen); }
   
   KeyGen(OwnPtr<AbstractHashFunc> &hash_,ulen klen_)
    : hash(hash_.detach()),
      klen(klen_),
      hlen(hash->getHLen()),
      secret_buf(GetSecretLen(klen,hlen))
    {
    }
   
   virtual ~KeyGen()
    { 
     Crypton::Forget(gxy);
     Crypton::Forget(gxys);
     
     Crypton::ForgetRange(Range(secret_buf)); 
    }
   
   // common secret
   
   ulen getSecretCount() const { return secret_buf.getLen()/GLen; }
   
   PtrLen<uint8> takeSecret(ulen index) { return Range(secret_buf.getPtr()+index*GLen,GLen); }
   
   PtrLen<uint8> takeSecret() { return Range(secret_buf); }
   
   // AbstractKeyGen
   
   virtual ulen getGLen() const
    { 
     static_assert( GLen>=MinGLen && GLen<=MaxGLen ,"CCore::Net::PSec::KeyGen<...> : bad GLen");
     
     return GLen; 
    }
   
   virtual ulen getKLen() const
    { 
     return klen; 
    }
   
   virtual void pow(const uint8 x[],uint8 gx[])
    {
     exp.pow(x,gx);
    }
   
   virtual void key(const uint8 x[],const uint8 gy[],uint8 key[])
    {
     const uint8 *ptr=secret_buf.getPtr();
     
     exp.pow(gy,x,gxy);
     exp.pow(gxy,ptr,gxys); ptr+=GLen;
     
     PtrLen<uint8> out(key,klen);
     
     while( ulen delta=Min(hlen,out.len) )
       {
        hash->add(Range_const(gxys));
        hash->add(Range_const(ptr,GLen)); ptr+=GLen;
        
        const uint8 *digest=hash->finish();
        
        (out+=delta).copy(digest);
       }
    }
 };

/* struct AbstractDHGroup */

struct AbstractDHGroup : MemBase_nocopy
 {
  virtual ~AbstractDHGroup() {}
  
  virtual ulen getGLen() const =0;

  virtual void pow(const uint8 a[ /* GLen */ ],const uint8 x[ /* GLen */ ],uint8 ax[ /* GLen */ ])=0;
  
  virtual void pow(const uint8 x[ /* GLen */ ],uint8 gx[ /* GLen */ ])=0;
 };

/* class DHGroup<Exp> */

template <class Exp> 
class DHGroup : public AbstractDHGroup 
 {
   Exp exp;
   
  public: 
   
   DHGroup() {}
   
   virtual ~DHGroup() {}
   
   // AbstractDHGroup
   
   virtual ulen getGLen() const
    { 
     static_assert( Exp::GLen>=MinGLen && Exp::GLen<=MaxGLen ,"CCore::Net::PSec::DHGroup<...> : bad GLen");
     
     return Exp::GLen; 
    }
   
   virtual void pow(const uint8 a[],const uint8 x[],uint8 ax[])
    {
     exp.pow(a,x,ax);
    }
   
   virtual void pow(const uint8 x[],uint8 gx[])
    {
     exp.pow(x,gx);
    }
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
   
   explicit RandomGen(PtrLen<const uint8> data) { rand.warp(data); }
   
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
  
  virtual void getKey0(uint8 key[ /* KLen */ ]) const =0;
  
  virtual ulen getKeySetLen() const =0;
  
  virtual void getKey(ulen index,uint8 key[ /* KLen */ ]) const =0;
 };

/* type MasterKeyPtr */

using MasterKeyPtr = OwnPtr<MasterKey> ;

/* struct AbstractClientProfile */

struct AbstractClientProfile : MemBase_nocopy
 {
  virtual ~AbstractClientProfile() {}
 };

/* type ClientProfilePtr */

using ClientProfilePtr = OwnPtr<AbstractClientProfile> ; 

/* struct EndpointManager */

struct EndpointManager
 {
  enum OpenErrorCode : uint32
   {
    Open_Ok = 0,
    
    OpenError_NoMemory,
    OpenError_OpenLimit,
    OpenError_NoAccess
   };
  
  virtual OpenErrorCode open(XPoint pke_point,MasterKeyPtr &skey,ClientProfilePtr &client_profile)=0;
  
  virtual void close(XPoint psec_point)=0;
  
  virtual void closeAll()=0;
  
  virtual AbstractClientProfile * getClientProfile(XPoint psec_point)=0; // only inside inbound processing
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
      
      ~Fifo() { Crypton::Forget(buf); }
    };
   
   Fifo fifo;
  
   OwnPtr<AbstractRandomGen> random;
   OwnPtr<AbstractHashFunc> hash;

   const uint8 *buf;
   ulen len;
   ulen off;
   
   uint8 temp[ExtLen];
   
  private:
  
   void addRandom(ulen count);
   
   ulen addFifo(ulen count);
   
   void addTimeStamp();
 
  public:
  
   explicit RandomEngine(const MasterKey &master_key);
   
   ~RandomEngine();
   
   uint8 next();
   
   void fill(PtrLen<uint8> data);
   
   void feed(PtrLen<const uint8> block) { fifo.put(block); }
 };

/* struct ControlResponse */

struct ControlResponse : NoCopy
 {
  Packets type;
  KeyIndex key_index;
  PtrLen<const uint8> gx;
  
  uint8 temp[MaxGLen];
  
  ControlResponse() : type(Packet_None),key_index(0) {}
  
  ~ControlResponse() { Crypton::ForgetRange(Range(temp,gx.len)); }
  
  void set(Packets type_) { type=type_; }
  
  void set(Packets type_,KeyIndex key_index_) { type=type_; key_index=key_index_; }
  
  void set(Packets type,KeyIndex key_index,PtrLen<const uint8> gx);
 };

/* class KeySet */

class KeySet : NoCopy
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
     
     void reset() { timeout=RepeatTimeout; }
     
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
    
     bool resend() const { return !repeat ; }
     
     void makeResponse(ControlResponse &resp,ulen glen)
      { 
       repeat.reset();
       
       if( type==Packet_Ack ) 
         resp.set(type,key_index);
       else
         resp.set(type,key_index,Range_const(gx,glen));
      }
     
     void flip()
      {
       base.move(next);
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
   
   static KeyIndex NextSerial(KeyIndex serial) { return KeyIndex( (serial+1)&3u ); }
   
   void activate_base(ulen index);
   
   void activate_next(ulen index);
   
   void deactivate(ulen index);
   
   void flip(ulen index);
   
   void make_key(Rec &rec,const uint8 gy[]);
   
   void activate_key(Rec &rec,ulen index);
   
  private: 
   
   OwnPtr<AbstractKeyGen> key_gen;
   
   ulen glen;
   
   DynArray<uint8> rekey_buf;
   
   RandomEngine &random;
   
  private: 
   
   void alert(Rec &rec,KeyIndex key_index);
   
   void alert(ControlResponse &resp,Rec &rec,KeyIndex key_index);
   
  public:
  
   KeySet(const MasterKey &master_key,RandomEngine &random);
   
   ~KeySet();
   
   // keys
   
   const uint8 * getKey0() const { return key0; }
   
   PtrLen<const KeyIndex> getActiveList() const { return Range(active_list).prefix(active_count); }
   
   bool selectEncryptKey(KeyIndex key_index,ulen use_count);
   
   const uint8 * getEncryptKey() const { return encrypt_key; }
   
   bool selectDecryptKey(KeyIndex key_index);
   
   const uint8 * getDecryptKey() const { return decrypt_key; }
   
   // key exchange
   
   ulen getGLen() const { return glen; }
   
   void tick(ControlResponse &resp);
   
   void alert(ControlResponse &resp,KeyIndex key_index,const uint8 gy[]);
   
   void ready(ControlResponse &resp,KeyIndex key_index,const uint8 gy[]);
   
   void ack(ControlResponse &resp,KeyIndex key_index);
   
   void stop(KeyIndex key_index);
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
  
   Convolution()
    { 
     start(); 
    }
   
   ~Convolution()
    {
     Crypton::Forget(a);
     Crypton::Forget(b);
    }
   
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

using ConvolutionParamB = ConvolutionParam<4,5,6,7> ;

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
   
   void random(PtrLen<uint8> data) { random_engine.fill(data); }
   
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
   
   void applyEncrypt(uint8 block[ /* BLen */ ])
    {
     direct_conv.apply(Range(block,blen));
     
     encrypt->apply(block); 
     
     feed(block); 
    }
   
   // decrypt
   
   bool selectDecryptKey(KeyIndex key_index) { return key_set.selectDecryptKey(key_index); }
   
   void setDecryptKey0() { decrypt->key(key_set.getKey0()); }
   
   void setDecryptKey() { decrypt->key(key_set.getDecryptKey()); }
   
   void startDecrypt() { inverse_conv.start(); }
   
   void applyDecrypt(uint8 block[ /* BLen */ ])
    { 
     decrypt->apply(block);
     
     inverse_conv.apply(Range(block,blen));
    }
   
   // hash
   
   void add(PtrLen<const uint8> data) { hash->add(data); }  
   
   const uint8 * finish() { return hash->finish(); }
   
   // key exchange
   
   ulen getGLen() const { return key_set.getGLen(); }
   
   void tick(ControlResponse &resp) { key_set.tick(resp); }
   
   void alert(ControlResponse &resp,KeyIndex key_index,const uint8 gy[]) { key_set.alert(resp,key_index,gy); }
   
   void ready(ControlResponse &resp,KeyIndex key_index,const uint8 gy[]) { key_set.ready(resp,key_index,gy); }
   
   void ack(ControlResponse &resp,KeyIndex key_index) { key_set.ack(resp,key_index); }
   
   void stop(KeyIndex key_index) { key_set.stop(key_index); }
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

/* class KeepAlive */

class KeepAlive : NoCopy
 {
   unsigned start_tick_count;
   unsigned tick_count;
  
  public:
  
   explicit KeepAlive(MSec keep_alive_timeout=Null);
   
   void reset() { tick_count=start_tick_count; }
   
   void tick(ControlResponse &resp);
 };

} // namespace PSec 
} // namespace Net
} // namespace CCore
 
#endif
 

