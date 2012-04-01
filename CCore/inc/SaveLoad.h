/* SaveLoad.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_SaveLoad_h
#define CCore_inc_SaveLoad_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* template */ 

#if 0 
 
  // save/load object

  enum { SaveLoadLen = SaveLenCounter<>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>();
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>();
   }
   
#endif   
   
/* functions */
  
template <class Proxy,class T,class Dev>
void ProxyLoad(T &obj,Dev &dev)
 {
  Proxy proxy;
  
  dev(proxy);
  
  obj=proxy.get();
 }

template <class R,class Dev>
void SaveRange(R r,Dev &dev)
 {
  for(; +r ;++r) dev(*r); 
 }

template <class T,class Dev>
void SaveRange(const T *ptr,ulen len,Dev &dev)
 {
  SaveRange(Range(ptr,len),dev);
 }
  
template <class R,class Dev>
void LoadRange(R r,Dev &dev)
 {
  for(; +r ;++r) dev(*r); 
 }

template <class T,class Dev>
void LoadRange(T *ptr,ulen len,Dev &dev)
 {
  LoadRange(Range(ptr,len),dev);
 }
  
template <class Custom,class R,class Dev>
void SaveRange_use(R r,Dev &dev)
 {
  for(; +r ;++r) dev.template use<Custom>(*r); 
 }

template <class Custom,class T,class Dev>
void SaveRange_use(const T *ptr,ulen len,Dev &dev)
 {
  SaveRange_use<Custom>(Range(ptr,len),dev);
 }
  
template <class Custom,class R,class Dev>
void LoadRange_use(R r,Dev &dev)
 {
  for(; +r ;++r) dev.template use<Custom>(*r); 
 }

template <class Custom,class T,class Dev>
void LoadRange_use(T *ptr,ulen len,Dev &dev)
 {
  LoadRange_use<Custom>(Range(ptr,len),dev);
 }
  
/* classes */ 

struct SaveLoadBe16;

struct SaveLoadBe32;

struct SaveLoadBe64;

struct SaveLoadLe16;

struct SaveLoadLe32;

struct SaveLoadLe64;

struct NeOrder;

struct BeOrder;

struct LeOrder;

template <class T,class Custom> struct SaveAdapter;

template <class T,class Custom> struct LoadAdapter;

template <class Dev> class PutDevBase;

template <class Dev> class GetDevBase;

class BufPutDev;

class BufGetDev;

class CountPutDev;

struct ProbeSet_SaveLoadLen;

template <class T> struct Has_SaveLoadLen;

template <class T> struct Get_SaveLoadLen;

template <bool has_SaveLoadLen,class T> struct SaveLenCounters;

template <bool has_SaveLoadLen,class T,class ... TT> struct SaveLenCounters2;

template <class ... TT> struct SaveLenCounter;

template <bool has_SaveLoadLen,class T,class ... TT> struct SplitLoads;

template <class ... TT> struct SplitLoad;

class RangeGetDev;

/* struct SaveLoadBe16 */ 

struct SaveLoadBe16
 {
  uint8 buf[2];
  
  // constructors
  
  SaveLoadBe16() : buf() {}
  
  SaveLoadBe16(uint8 b0,uint8 b1) 
   {
    buf[0]=b0;
    buf[1]=b1;
   }
  
  explicit SaveLoadBe16(uint16 value)
   {
    buf[0]=uint8(value>>8);
    buf[1]=uint8(value   );
   }
  
  // methods
  
  uint16 get() const 
   { 
    uint16 b0=buf[0];
    uint16 b1=buf[1];
   
    return uint16( (b0<<8)|b1 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 2 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,2);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,2);
   }
 };
 
/* struct SaveLoadBe32 */ 

struct SaveLoadBe32
 {
  uint8 buf[4];
  
  // constructors
  
  SaveLoadBe32() : buf() {}
  
  SaveLoadBe32(uint8 b0,uint8 b1,uint8 b2,uint8 b3) 
   {
    buf[0]=b0;
    buf[1]=b1;
    buf[2]=b2;
    buf[3]=b3;
   }
  
  explicit SaveLoadBe32(uint32 value) 
   {
    buf[0]=uint8(value>>24);
    buf[1]=uint8(value>>16);
    buf[2]=uint8(value>> 8);
    buf[3]=uint8(value    );
   }
  
  // methods
  
  uint32 get() const 
   { 
    uint32 b0=buf[0];
    uint32 b1=buf[1];
    uint32 b2=buf[2];
    uint32 b3=buf[3];
   
    return uint32( (b0<<24)|(b1<<16)|(b2<<8)|b3 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 4 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,4);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,4);
   }
 };
 
/* struct SaveLoadBe64 */ 

struct SaveLoadBe64
 {
  uint8 buf[8];
  
  // constructors
  
  SaveLoadBe64() : buf() {}
  
  SaveLoadBe64(uint8 b0,uint8 b1,uint8 b2,uint8 b3,uint8 b4,uint8 b5,uint8 b6,uint8 b7) 
   {
    buf[0]=b0;
    buf[1]=b1;
    buf[2]=b2;
    buf[3]=b3;
    buf[4]=b4;
    buf[5]=b5;
    buf[6]=b6;
    buf[7]=b7;
   }
  
  explicit SaveLoadBe64(uint64 value) 
   {
    buf[0]=uint8(value>>56);
    buf[1]=uint8(value>>48);
    buf[2]=uint8(value>>40);
    buf[3]=uint8(value>>32);
    buf[4]=uint8(value>>24);
    buf[5]=uint8(value>>16);
    buf[6]=uint8(value>> 8);
    buf[7]=uint8(value    );
   }
  
  // methods
  
  uint64 get() const 
   { 
    uint64 b0=buf[0];
    uint64 b1=buf[1];
    uint64 b2=buf[2];
    uint64 b3=buf[3];
    uint64 b4=buf[4];
    uint64 b5=buf[5];
    uint64 b6=buf[6];
    uint64 b7=buf[7];
   
    return uint64( (b0<<56)|(b1<<48)|(b2<<40)|(b3<<32)|(b4<<24)|(b5<<16)|(b6<<8)|b7 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 8 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,8);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,8);
   }
 };
 
/* struct SaveLoadLe16 */ 

struct SaveLoadLe16
 {
  uint8 buf[2];
  
  // constructors
  
  SaveLoadLe16() : buf() {}
  
  SaveLoadLe16(uint8 b0,uint8 b1) 
   {
    buf[0]=b0;
    buf[1]=b1;
   }
  
  explicit SaveLoadLe16(uint16 value) 
   {
    buf[0]=uint8(value   );
    buf[1]=uint8(value>>8);
   }
  
  // methods
  
  uint16 get() const 
   { 
    uint16 b0=buf[0];
    uint16 b1=buf[1];
   
    return uint16( (b1<<8)|b0 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 2 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,2);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,2);
   }
 };
 
/* struct SaveLoadLe32 */ 

struct SaveLoadLe32
 {
  uint8 buf[4];
  
  // constructors
  
  SaveLoadLe32() : buf() {}
  
  SaveLoadLe32(uint8 b0,uint8 b1,uint8 b2,uint8 b3) 
   {
    buf[0]=b0;
    buf[1]=b1;
    buf[2]=b2;
    buf[3]=b3;
   }
  
  explicit SaveLoadLe32(uint32 value) 
   {
    buf[0]=uint8(value    );
    buf[1]=uint8(value>> 8);
    buf[2]=uint8(value>>16);
    buf[3]=uint8(value>>24);
   }
  
  // methods
  
  uint32 get() const 
   { 
    uint32 b0=buf[0];
    uint32 b1=buf[1];
    uint32 b2=buf[2];
    uint32 b3=buf[3];
   
    return uint32( (b3<<24)|(b2<<16)|(b1<<8)|b0 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 4 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,4);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,4);
   }
 };
 
/* struct SaveLoadLe64 */ 

struct SaveLoadLe64
 {
  uint8 buf[8];
  
  // constructors
  
  SaveLoadLe64() : buf() {}
  
  SaveLoadLe64(uint8 b0,uint8 b1,uint8 b2,uint8 b3,uint8 b4,uint8 b5,uint8 b6,uint8 b7) 
   {
    buf[0]=b0;
    buf[1]=b1;
    buf[2]=b2;
    buf[3]=b3;
    buf[4]=b4;
    buf[5]=b5;
    buf[6]=b6;
    buf[7]=b7;
   }
  
  explicit SaveLoadLe64(uint64 value) 
   {
    buf[0]=uint8(value    );
    buf[1]=uint8(value>> 8);
    buf[2]=uint8(value>>16);
    buf[3]=uint8(value>>24);
    buf[4]=uint8(value>>32);
    buf[5]=uint8(value>>40);
    buf[6]=uint8(value>>48);
    buf[7]=uint8(value>>56);
   }
  
  // methods
  
  uint64 get() const 
   { 
    uint64 b0=buf[0];
    uint64 b1=buf[1];
    uint64 b2=buf[2];
    uint64 b3=buf[3];
    uint64 b4=buf[4];
    uint64 b5=buf[5];
    uint64 b6=buf[6];
    uint64 b7=buf[7];
   
    return uint64( (b7<<56)|(b6<<48)|(b5<<40)|(b4<<32)|(b3<<24)|(b2<<16)|(b1<<8)|b0 ); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 8 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(buf,8);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(buf,8);
   }
 };
 
/* struct NeOrder */ 
 
struct NeOrder
 {
  // empty
 };
 
/* struct BeOrder */ 

struct BeOrder
 {
  template <class Dev>
  static void Save16(uint16 obj,Dev &dev)
   {
    dev(SaveLoadBe16(obj));
   }
   
  template <class Dev>
  static void Save32(uint32 obj,Dev &dev)
   {
    dev(SaveLoadBe32(obj));
   }
   
  template <class Dev>
  static void Save64(uint64 obj,Dev &dev)
   {
    dev(SaveLoadBe64(obj));
   }
   
  template <class Dev>
  static void Load16(uint16 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadBe16>(obj,dev);
   }
   
  template <class Dev>
  static void Load32(uint32 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadBe32>(obj,dev);
   }
   
  template <class Dev>
  static void Load64(uint64 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadBe64>(obj,dev);
   }
 };
 
/* struct LeOrder */ 

struct LeOrder
 {
  template <class Dev>
  static void Save16(uint16 obj,Dev &dev)
   {
    dev(SaveLoadLe16(obj));
   }
   
  template <class Dev>
  static void Save32(uint32 obj,Dev &dev)
   {
    dev(SaveLoadLe32(obj));
   }
   
  template <class Dev>
  static void Save64(uint64 obj,Dev &dev)
   {
    dev(SaveLoadLe64(obj));
   }
   
  template <class Dev>
  static void Load16(uint16 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadLe16>(obj,dev);
   }
   
  template <class Dev>
  static void Load32(uint32 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadLe32>(obj,dev);
   }
   
  template <class Dev>
  static void Load64(uint64 &obj,Dev &dev)
   {
    ProxyLoad<SaveLoadLe64>(obj,dev);
   }
 };
 
/* struct SaveAdapter<T,Custom> */  
 
template <class T,class Custom> 
struct SaveAdapter
 {
  template <class Dev>
  static void Save(const T &obj,Dev &dev) { obj.save(dev); }
 };
 
template <class Custom> 
struct SaveAdapter<uint8,Custom>
 {
  template <class Dev>
  static void Save(uint8 obj,Dev &dev) { dev.put(obj); }
 };
 
template <class Custom> 
struct SaveAdapter<uint16,Custom>
 {
  template <class Dev>
  static void Save(uint16 obj,Dev &dev) { Custom::Save16(obj,dev); }
 };
 
template <class Custom> 
struct SaveAdapter<uint32,Custom>
 {
  template <class Dev>
  static void Save(uint32 obj,Dev &dev) { Custom::Save32(obj,dev); }
 };
 
template <class Custom> 
struct SaveAdapter<uint64,Custom>
 {
  template <class Dev>
  static void Save(uint64 obj,Dev &dev) { Custom::Save64(obj,dev); }
 };
 
/* struct LoadAdapter<T,Custom> */ 

template <class T,class Custom> 
struct LoadAdapter
 {
  template <class Dev>
  static void Load(T &obj,Dev &dev) { obj.load(dev); }
 };
 
template <class Custom> 
struct LoadAdapter<uint8,Custom>
 {
  template <class Dev>
  static void Load(uint8 &obj,Dev &dev) { obj=dev.get(); }
 };
 
template <class Custom> 
struct LoadAdapter<uint16,Custom>
 {
  template <class Dev>
  static void Load(uint16 &obj,Dev &dev) { Custom::Load16(obj,dev); }
 };
 
template <class Custom> 
struct LoadAdapter<uint32,Custom>
 {
  template <class Dev>
  static void Load(uint32 &obj,Dev &dev) { Custom::Load32(obj,dev); }
 };
 
template <class Custom> 
struct LoadAdapter<uint64,Custom>
 {
  template <class Dev>
  static void Load(uint64 &obj,Dev &dev) { Custom::Load64(obj,dev); }
 };
 
/* class PutDevBase<Dev> */  

template <class Dev>
class PutDevBase
 {
  private:
  
   Dev * getDev() { return static_cast<Dev *>(this); }
 
  public:
   
   // put
  
   void put(uint8 value) { getDev()->do_put(value); }
   
   void put(const uint8 *ptr,ulen len) { getDev()->do_put(ptr,len); }
   
   void put(PtrLen<const uint8> data) { getDev()->do_put(data.ptr,data.len); }
   
   PtrLen<uint8> putRange(ulen len) { return getDev()->do_putRange(len); } // may return Nothing
   
   // save
   
   template <class Custom> 
   void use() {}
   
   template <class Custom,class T,class ... TT>
   void use(const T &t,const TT & ... tt)
    {
     SaveAdapter<T,Custom>::Save(t,*this);
     
     use<Custom>(tt...);
    }
    
   template <class ... TT>
   void operator () (const TT & ... tt)
    {
     use<NeOrder>(tt...);
    }
 };
 
/* class GetDevBase<Dev> */ 

template <class Dev>
class GetDevBase
 {
  private:
  
   Dev * getDev() { return static_cast<Dev *>(this); }
 
  public:
   
   // get

   uint8 get() { return getDev()->do_get(); }
   
   void get(uint8 *ptr,ulen len) { getDev()->do_get(ptr,len); }
   
   void get(PtrLen<uint8> buf) { getDev()->do_get(buf.ptr,buf.len); }
   
   PtrLen<const uint8> getRange(ulen len) { return getDev()->do_getRange(len); } // may return Nothing
   
   // load
   
   template <class Custom> 
   void use() {}
   
   template <class Custom,class T,class ... TT>
   void use(T &t,TT & ... tt)
    {
     LoadAdapter<T,Custom>::Load(t,*this);
    
     use<Custom>(tt...);
    }
    
   template <class ... TT>
   void operator () (TT & ... tt)
    {
     use<NeOrder>(tt...);
    }
 }; 
 
/* class BufPutDev */  
 
class BufPutDev : public PutDevBase<BufPutDev>
 {
   uint8 *buf;
 
  public:
  
   explicit BufPutDev(uint8 *buf_) : buf(buf_) {}
   
   // methods
   
   void do_put(uint8 value) { *(buf++)=value; }
   
   void do_put(const uint8 *ptr,ulen len) { Range(ptr,len).copyTo(buf); buf+=len; }
   
   PtrLen<uint8> do_putRange(ulen len) { PtrLen<uint8> ret(buf,len); buf+=len; return ret; }
   
   uint8 * getRest() const { return buf; }
 };
 
/* class BufGetDev */ 

class BufGetDev : public GetDevBase<BufGetDev>
 {
   const uint8 *buf;
 
  public:
  
   explicit BufGetDev(const uint8 *buf_) : buf(buf_) {}
   
   // methods
   
   uint8 do_get() { return *(buf++); }
   
   void do_get(uint8 *ptr,ulen len) { Range(ptr,len).copy(buf); buf+=len; }
   
   PtrLen<const uint8> do_getRange(ulen len) { PtrLen<const uint8> ret(buf,len); buf+=len; return ret; }
   
   const uint8 * getRest() const { return buf; }
 };
 
/* class CountPutDev */ 

class CountPutDev : public PutDevBase<CountPutDev>
 {
   ULenSat count;
   
  public: 
  
   CountPutDev() {}
   
   // methods
   
   operator ULenSat() const { return count; }
   
   void do_put(uint8) { count+=1u; }
   
   void do_put(const uint8 *,ulen len) { count+=len; }
   
   PtrLen<uint8> do_putRange(ulen len) { count+=len; return Nothing; }
 };
 
/* struct ProbeSet_SaveLoadLen */

struct ProbeSet_SaveLoadLen
 {
  template <bool> struct Host;
  
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<T::SaveLoadLen> *) { return true; }
 };

/* struct Has_SaveLoadLen<T> */  

template <class T>
struct Has_SaveLoadLen : Meta::Has<T,ProbeSet_SaveLoadLen> {};
 
template <> 
struct Has_SaveLoadLen<uint8> : Meta::True {};
 
template <> 
struct Has_SaveLoadLen<uint16> : Meta::True {};
 
template <> 
struct Has_SaveLoadLen<uint32> : Meta::True {};
 
template <> 
struct Has_SaveLoadLen<uint64> : Meta::True {};
 
/* struct Get_SaveLoadLen<T> */ 
 
template <class T> 
struct Get_SaveLoadLen
 {
  enum RetType { Ret = T::SaveLoadLen };
 };
 
template <> 
struct Get_SaveLoadLen<uint8> { enum RetType { Ret = 1 }; };
 
template <> 
struct Get_SaveLoadLen<uint16> { enum RetType { Ret = 2 }; };
 
template <> 
struct Get_SaveLoadLen<uint32> { enum RetType { Ret = 4 }; };
 
template <> 
struct Get_SaveLoadLen<uint64> { enum RetType { Ret = 8 }; };
 
/* struct SaveLenCounters<bool has_SaveLoadLen,T> */ 
 
template <class T> 
struct SaveLenCounters<true,T>
 {
  enum FlagType { Has_SaveLoadLen = true };
 
  enum LenType : ulen { SaveLoadLen = Get_SaveLoadLen<T>::Ret };
  
  static ULenSat Count(const T &) { return ulen(SaveLoadLen); }
 };
 
template <class T> 
struct SaveLenCounters<false,T>
 {
  enum FlagType { Has_SaveLoadLen = false };
 
  static ULenSat Count(const T &t)
   {
    CountPutDev dev;
    
    dev(t);
    
    return dev;
   }
 };
 
/* struct SaveLenCounters2<bool has_SaveLoadLen,T,TT> */ 
 
template <class T,class ... TT> 
struct SaveLenCounters2<true,T,TT...>
 {
  enum FlagType { Has_SaveLoadLen = true };
 
  enum LenType : ulen { SaveLoadLen = UIntConstAdd<ulen,Get_SaveLoadLen<T>::Ret,SaveLenCounter<TT...>::SaveLoadLen>::Ret };
  
  static ULenSat Count(const T &,const TT & ...) { return ulen(SaveLoadLen); }
 };
 
template <class T,class ... TT> 
struct SaveLenCounters2<false,T,TT...>
 {
  enum FlagType { Has_SaveLoadLen = false };
 
  static ULenSat Count(const T &t,const TT & ... tt)
   {
    return SaveLenCounter<T>::Count(t)+SaveLenCounter<TT...>::Count(tt...);
   }
 };
 
/* struct SaveLenCounter<TT> */ 

template <> 
struct SaveLenCounter<>
 {
  enum FlagType { Has_SaveLoadLen = true };
 
  enum LenType : ulen { SaveLoadLen = 0 };
 
  static ULenSat Count() { return ulen(SaveLoadLen); }
 };
 
template <class T> 
struct SaveLenCounter<T> : SaveLenCounters<Has_SaveLoadLen<T>::Ret,T> {};
 
template <class T,class S,class ... TT> 
struct SaveLenCounter<T,S,TT...> 
 : SaveLenCounters2< Has_SaveLoadLen<T>::Ret && SaveLenCounter<S,TT...>::Has_SaveLoadLen ,T,S,TT...> {};
 
/* struct SplitLoads<bool has_SaveLoadLen,TT> */ 

template <class T,class ... TT>
struct SplitLoads<true,T,TT...>
 {
  T &first;
  SplitLoad<TT...> rest;
  
  SplitLoads(T &t,TT & ... tt) : first(t),rest(tt...) {}
   
  template <class Custom,class Dev>
  void use(Dev &dev)
   {
    rest.template use_const<Custom>(dev,first);
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_const(Dev &dev,SS & ... ss)
   {
    rest.template use_const<Custom>(dev,ss...,first);
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_rest(Dev &dev,SS & ... ss)
   {
    rest.template use_rest<Custom>(dev,ss...,first);
   }
 };
 
template <class T,class ... TT>
struct SplitLoads<false,T,TT...>
 {
  T &first;
  SplitLoad<TT...> rest;
 
  SplitLoads(T &t,TT & ... tt) : first(t),rest(tt...) {}
  
  template <class Custom,class Dev>
  void use(Dev &dev)
   {
    rest.template use_rest<Custom>(dev,first);
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_const(Dev &dev,SS & ... ss)
   {
    dev.template use_const<Custom>(ss...);
   
    rest.template use_rest<Custom>(dev,first);
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_rest(Dev &dev,SS & ... ss)
   {
    rest.template use_rest<Custom>(dev,ss...,first);
   }
 };
 
/* struct SplitLoad<TT> */ 
   
template <> 
struct SplitLoad<>
 {
  SplitLoad() {}
 
  template <class Custom,class Dev>
  void use(Dev &)
   {
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_const(Dev &dev,SS & ... ss)
   {
    dev.template use_const<Custom>(ss...);
   }
   
  template <class Custom,class Dev,class ... SS>
  void use_rest(Dev &dev,SS & ... ss)
   {
    dev.template use_rest<Custom>(ss...);
   }
 };
 
template <class T,class ... TT> 
struct SplitLoad<T,TT...> : SplitLoads<Has_SaveLoadLen<T>::Ret,T,TT...> 
 {
  explicit SplitLoad(T &t,TT & ... tt) : SplitLoads<Has_SaveLoadLen<T>::Ret,T,TT...>(t,tt...) {}
 };
 
/* class RangeGetDev */ 

class RangeGetDev
 {
   PtrLen<const uint8> range;
   bool nok;
   
  public: 
  
   explicit RangeGetDev(PtrLen<const uint8> range_) : range(range_),nok(false) {}
   
   bool operator ! () const { return nok; }
   
   // get
   
   uint8 get() 
    { 
     if( !range )
       {
        nok=true;
       
        return 0; 
       }
     else
       {  
        uint8 ret=*range;
     
        ++range;
     
        return ret;  
       }
    }
   
   void get(uint8 *ptr,ulen len) 
    { 
     if( range.len<len )
       {
        nok=true;
       }
     else
       {
        (range+=len).copyTo(ptr);
       }  
    }
    
   void get(PtrLen<uint8> buf) { get(buf.ptr,buf.len); }
   
   PtrLen<const uint8> getRange(ulen len) // may return Nothing 
    {
     if( range.len<len )
       {
        nok=true;
        
        return Nothing;
       }
     else
       {
        return range+=len;
       }  
    }
    
   PtrLen<const uint8> getRest() const { return range; }
   
   // extra
   
   PtrLen<const uint8> getFinalRange()
    {
     ulen len=range.len;
     
     return range+=len;
    }
    
   PtrLen<const uint8> getFinalRange(ulen len)
    {
     if( range.len!=len )
       {
        nok=true;
        
        return Nothing;
       }
     else
       {
        return range+=len;
       }  
    }
    
   void fail() { nok=true; }
   
   NegBool finish() { if( +range ) nok=true; return nok; }
   
   // split load
   
   template <class Custom>
   void use_const() {}
    
   template <class Custom,class T,class ... TT>
   void use_const(T &t,TT & ... tt)
    {
     const uint8 *buf=getRange(SaveLenCounter<T,TT...>::SaveLoadLen).ptr;
    
     if( nok ) return;
    
     BufGetDev dev(buf);
    
     dev.use<Custom>(t,tt...);
    }
    
   template <class Custom>
   void use_rest() {}
    
   template <class Custom,class T,class ... TT>
   void use_rest(T &t,TT & ... tt)
    {
     LoadAdapter<T,Custom>::Load(t,*this);
    
     use<Custom>(tt...);
    }
    
   template <class Custom>
   void use() {}
    
   template <class Custom,class T,class ... TT>
   void use(T &t,TT & ... tt)
    {
     SplitLoad<T,TT...> split(t,tt...);
     
     split.template use<Custom>(*this);
    }
    
   template <class ... TT>
   void operator () (TT & ... tt)
    {
     use<NeOrder>(tt...);
    }
 };
 
/* SaveLen() */ 

template <class ... TT>
ULenSat SaveLen(const TT & ... tt)
 {
  return SaveLenCounter<TT...>::Count(tt...);
 }
 
} // namespace CCore
 
#endif
 

