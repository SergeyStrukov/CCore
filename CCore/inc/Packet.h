/* Packet.h */ 
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

#ifndef CCore_inc_Packet_h
#define CCore_inc_Packet_h

#include <CCore/inc/Timer.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Move.h>

#include <CCore/inc/task/Atomic.h>
 
namespace CCore {

/* consts */ 

const ulen MaxPacketExtLen = Align(256) ;

const ulen MaxPacketCompleteFunctions = 8 ;

const ulen DefaultPacketMaxDataLen = 1600 ;

enum PacketCancelState
 {
  Packet_NoCancelFunction,
  Packet_HasCancelFunction,
  Packet_Cancelled
 };
 
enum LenStatus
 {
  Len_ok,
  Len_too_short,
  Len_too_long
 };
    
/* functions */ 

void GuardLenSubTooShort(const char *name,ulen len,ulen delta);

inline ulen LenSub(const char *name,ulen len,ulen delta) // always > 0 
 {
  if( len<=delta ) GuardLenSubTooShort(name,len,delta);
  
  return len-delta;
 }
 
/* classes */ 

struct PacketFormat;

class PacketBuf;

template <class ... TT> struct PacketDeepExtLen;

class PacketHeader;

template <class POD,class ... TT> struct PacketExtType;

template <ulen Index,class ... TT> struct PacketDeepExt;

template <ulen Index,class POD,class ... TT> struct PacketForgetExt;
   
template <class POD,class ... TT> class Packet;

class PacketCanceller;

class PacketList;

/* types */ 

typedef SecTimer::ValueType TimeStamp;

typedef Function<void (PacketHeader *)> PacketFunction;

/* struct PacketFormat */ 

struct PacketFormat
 {
  ulen prefix;
  ulen max_data;
  ulen suffix;
  
   // prefix + suffix + max_data <= MaxULen
  
  PacketFormat()
   {
    prefix=0;
    max_data=0;
    suffix=0;
   }
  
  PacketFormat(NothingType)
   {
    prefix=0;
    max_data=0;
    suffix=0;
   }
  
  ulen getMaxTotalLen() const { return prefix+max_data+suffix; }
   
  PacketFormat addPrefix(ulen prefix_len) const; 
  
  PacketFormat addSuffix(ulen suffix_len) const;
  
  PacketFormat addPrefixSuffix(ulen prefix_len,ulen suffix_len) const; 
  
  ulen add(ulen len) const // return total_len; 
   { 
    ulen delta=prefix+suffix;
    
    return len+delta; 
   }
   
  struct SubResult
   {
    ulen len;
    LenStatus status;
    
    SubResult(ulen len_,LenStatus status_) : len(len_),status(status_) {}
     
    bool isTooShort() const { return status==Len_too_short; }
    
    bool notFitFormat() const { return status!=Len_ok; }
   };
  
  SubResult sub(ulen total_len) const // return len;
   {
    ulen delta=prefix+suffix;
    
    if( total_len>=delta ) 
      {
       ulen len=total_len-delta;
       
       if( len<=max_data ) return SubResult(len,Len_ok);
       
       return SubResult(max_data,Len_too_long);
      }
    
    return SubResult(0,Len_too_short);
   }
   
  bool checkLen(ULenSat len,ulen max_total_len) const
   {
    ulen delta=prefix+suffix;
    
    return len<=max_data && len.value+delta<=max_total_len ;
   }
  
  bool check(ulen total_len) const
   {
    ulen delta=prefix+suffix;
    
    return total_len>=delta && total_len<=delta+max_data ;
   }
   
  template <class T>
  PtrLen<T> cut(PtrLen<T> range) const // assume check(range.len)
   {
    return range.inner(prefix,suffix);
   }
   
  template <class T>
  PtrLen<T> cutPrefix(PtrLen<T> range) const // assume check(range.len)
   {
    return range.prefix(prefix);
   }
   
  template <class T>
  PtrLen<T> cutSuffix(PtrLen<T> range) const // assume check(range.len)
   {
    return range.suffix(suffix);
   }
   
  template <class T> 
  struct CutResult
   {
    PtrLen<T> range;
    LenStatus status;
    
    CutResult(PtrLen<T> range_,LenStatus status_) : range(range_),status(status_) {}
    
    LenStatus operator ! () const { return status==Len_too_short; } 
   }; 
   
  template <class T>
  CutResult<T> cutMax(PtrLen<T> range) const
   {
    ulen delta=prefix+suffix;
   
    if( range.len>=delta ) 
      {
       ulen len=range.len-delta;
       
       if( len<=max_data ) return CutResult<T>(range.part(prefix,len),Len_ok);
      
       return CutResult<T>(range.part(prefix,max_data),Len_too_long);
      }
    
    return CutResult<T>(Nothing,Len_too_short);
   }
 };
 
/* class PacketBuf */  
 
class PacketBuf : NoCopy
 {
   void *data;
   ulen max_data_len;
   ulen data_len;
   
  private: 
   
   static void GuardLenAbort();
   
   void guardLen(ulen data_len) const
    {
     if( data_len>max_data_len ) GuardLenAbort();
    }
   
  public:
   
   // constructors
  
   PacketBuf();
   
   explicit PacketBuf(ulen max_data_len);
   
   ~PacketBuf();
   
   // methods
   
   bool provide(ulen max_data_len);
   
   void detach();
   
   void moveTo(PacketBuf &pbuf);
   
   // data methods
   
   bool noSpace() const { return !max_data_len; }
   
   ulen getMaxRawLen() const { return max_data_len; }
   
   ulen getRawLen() const { return data_len; }
   
   void setRawLen(ulen data_len_) { guardLen(data_len_); data_len=data_len_; }
   
   Place<void> getRaw() { return PlaceAt(data); }
 };
 
/* struct PacketDeepExtLen<TT> */ 
 
template <class T,class ... TT> 
struct PacketDeepExtLen<T,TT...> : Meta::DefConst<ulen,( Align(sizeof (T)) + PacketDeepExtLen<TT...>::Ret )> {};

template <> 
struct PacketDeepExtLen<> : Meta::DefConst<ulen,0> {};
 
/* class PacketHeader */ 

class PacketHeader : NoCopy
 {
   PacketBuf pbuf;
   
   TimeStamp time_stamp;
   
   Atomic cancel_state; // PacketCancelState
   PacketFunction cancel_function;
   void *cancel_arg;
  
   PacketFunction stack[MaxPacketCompleteFunctions];
   ulen stack_len;
   
   ulen ext_len;
  
   DLink<PacketHeader> link;
   bool in_list;
  
  private: 
   
   static void PushCompleteFunctionAbort();
 
   static void PopCompleteFunctionAbort();
 
   static void PushExtAbort();
   
  private:

   void initList();
   
   typedef DLink<PacketHeader>::CircularAlgo<&PacketHeader::link> Algo;
    
   friend class PacketList;
   
  public:
   
   // constructors
   
   static constexpr ulen Delta() { return Align(sizeof (PacketHeader)); }
   
   static constexpr ulen AllocLen() { return Delta()+MaxPacketExtLen; }
  
   explicit PacketHeader(PacketFunction complete_function) noexcept(EnableNoExcept);
   
   void recycle(PacketFunction complete_function);
   
   ~PacketHeader() {}
   
   // complete
   
   void pushCompleteFunction(PacketFunction complete_function) 
    {
     if( stack_len>=MaxPacketCompleteFunctions ) PushCompleteFunctionAbort();
    
     stack[stack_len++]=complete_function;
    }
   
   PacketFunction popCompleteFunction() 
    {
     if( stack_len==0 ) PopCompleteFunctionAbort();
    
     return Replace_null(stack[--stack_len]);
    }
  
   void complete() { popCompleteFunction()(this); }
   
   // cancel
   
   PacketCancelState setCancelFunction(PacketFunction cancel_function,void *cancel_arg=0);
   
   PacketCancelState clearCancelFunction();
   
   PacketCancelState getCancelFunction(PacketFunction &ret);
   
   void * getCancelArg() const { return cancel_arg; }
   
   // stamp
  
   TimeStamp getStamp() const { return time_stamp; }
  
   bool isOld(TimeStamp now,TimeStamp how_old) const { return now-time_stamp>how_old; }
  
   void stamp() { time_stamp=SecTimer::Get(); }
   
   // ext
   
   Place<void> getExtBase() { return PlaceAt(this)+Delta(); }
    
   template <class T,class ... SS>
   T * pushExt(SS && ... ss)
    {
     static_assert( sizeof (T)<=MaxPacketExtLen ,"CCore::PacketHeader::pushExt<T>(...) : T is too large");
     
     auto place=getExtBase()+ext_len;
     
     if( ext_len>MaxPacketExtLen-Align(sizeof (T)) ) PushExtAbort();
     
     T *ret=new(place) T( std::forward<SS>(ss)... );
     
     ext_len+=Align(sizeof (T));
    
     return ret;
    }
   
   template <class T>
   T * getExt()
    {
     ulen off=ext_len-Align(sizeof (T));
     
     return getExtBase()+off;
    }
    
   template <class T,class ... TT>  // T, T1, T2, ... , Ttop
   T * getDeepExt()
    {
     ulen off=ext_len-PacketDeepExtLen<T,TT...>::Ret;
     
     return getExtBase()+off;
    }
    
   template <class T>
   void popExt()
    {
     ulen off=( ext_len-=Align(sizeof (T)) );
     
     T *ext=getExtBase()+off;
     
     ext->~T();
    }
    
   // data attach/detach 
   
   bool provide(ulen max_data_len=DefaultPacketMaxDataLen);
   
   void detach();
   
   void attach(PacketBuf &pbuf);
   
   void detach(PacketBuf &pbuf);
   
   void detach(PacketHeader *dst);
   
   // raw data
   
   bool noSpace() const { return pbuf.noSpace(); }
    
   ulen getMaxRawLen() const { return pbuf.getMaxRawLen(); }
   
   ulen getRawLen() const { return pbuf.getRawLen(); }
   
   void setRawLen(ulen data_len) { pbuf.setRawLen(data_len); }
   
   Place<void> getRaw() { return pbuf.getRaw(); }
 };
 
/* struct PacketExtType<POD,TT> */ 

template <class POD>
struct PacketExtType<POD>
 {
  typedef void TopType;
  
  typedef void PopType;
 };
 
#if 0
 
template <class POD,class T,class ... TT>
struct PacketExtType<POD,TT...,T>
 {
  typedef T TopType;
  
  typedef Packet<POD,TT...> PopType;
 };

#else
 
template <class POD,class T>
struct PacketExtType<POD,T>
 {
  typedef T TopType;
  
  typedef Packet<POD> PopType;
  
  template <class ... SS>
  struct AddPopType
   {
    typedef Packet<POD,SS...> Ret;
   };
 };
 
template <class POD,class S,class T,class ... TT>
struct PacketExtType<POD,S,T,TT...>
 {
  typedef typename PacketExtType<POD,T,TT...>::TopType TopType;
  
  typedef typename PacketExtType<POD,T,TT...>::template AddPopType<S>::Ret PopType;
  
  template <class ... SS>
  struct AddPopType
   {
    typedef typename PacketExtType<POD,T,TT...>::template AddPopType<SS...,S>::Ret Ret;
   };
 };
 
#endif

/* PacketDeepExt<ulen Index,TT> */  
 
template <ulen Index,class T,class ... TT> 
struct PacketDeepExt<Index,T,TT...> : PacketDeepExt<Index-1,TT...> {};
 
template <class T,class ... TT> 
struct PacketDeepExt<1,T,TT...>
 {
  typedef T GetType;
  
  static T * Get(PacketHeader *packet) { return packet->getDeepExt<T,TT...>(); }
 };
 
/* struct PacketForgetExt<ulen Index,POD,TT> */  
 
template <ulen Index,class POD,class T,class ... TT> 
struct PacketForgetExt<Index,POD,T,TT...> : PacketForgetExt<Index-1,POD,TT...> {};
 
template <class POD,class T,class ... TT>
struct PacketForgetExt<1,POD,T,TT...>
 {
  typedef Packet<POD,TT...> RetType;
 };
 
/* class Packet<POD,TT> */  

template <class POD,class ... TT> // T1, T2, ... , Ttop
class Packet
 {
   static_assert( std::is_pod<POD>::value ,"CCore::Packet<POD,...> : POD must be pod");
     
  private:
   
   PacketHeader *packet;
   
  public:
   
   // constructors
  
   Packet() : packet(0) {}
   
   Packet(NothingType) : packet(0) {}
   
   Packet(PacketHeader *packet_) : packet(packet_) {}
   
   // props
   
   PacketHeader * operator + () const { return packet; }
   
   bool operator ! () const { return packet==0; }
   
   PacketHeader * getPtr() const { return packet; }
   
   // complete
   
   void pushCompleteFunction(PacketFunction complete_function) { packet->pushCompleteFunction(complete_function); }
   
   PacketFunction popCompleteFunction() { return packet->popCompleteFunction(); }
  
   void complete() { Replace_null(packet)->complete(); }
   
   // cancel
   
   PacketCancelState setCancelFunction(PacketFunction cancel_function,void *cancel_arg=0) { return packet->setCancelFunction(cancel_function,cancel_arg); }
   
   PacketCancelState clearCancelFunction() { return packet->clearCancelFunction(); }
   
   void * getCancelArg() { return packet->getCancelArg(); }
   
   // stamp
  
   TimeStamp getStamp() { return packet->getStamp(); }
  
   bool isOld(TimeStamp now,TimeStamp how_old) { return packet->isOld(now,how_old); }
  
   void stamp() { packet->stamp(); }
   
   // ext
   
   template <class T,class ... SS>
   Packet<POD,TT...,T> pushExt(SS && ... ss) 
    { 
     PacketHeader *ret=Replace_null(packet);
     
     ret->pushExt<T>( std::forward<SS>(ss)... );
     
     return ret; 
    }
    
   typename PacketExtType<POD,TT...>::TopType * getExt()
    {
     return packet->getExt<typename PacketExtType<POD,TT...>::TopType>();
    }
    
   typename PacketExtType<POD,TT...>::PopType popExt() 
    {
     PacketHeader *ret=Replace_null(packet);
     
     ret->popExt<typename PacketExtType<POD,TT...>::TopType>();
     
     return ret; 
    }
 
   template<ulen Index>
   typename PacketDeepExt<Index,TT...>::GetType * getDeepExt()
    {
     return PacketDeepExt<Index,TT...>::Get(packet);
    }
    
   template<ulen Index>
   typename PacketForgetExt<Index,POD,TT...>::RetType forgetExt()
    {
     return Replace_null(packet);
    }
 
   // data attach/detach 
   
   bool provide(ulen max_data_len) { return packet->provide(max_data_len*sizeof (POD)); }
   
   bool provide() { return packet->provide(); }
 
   void detach() { packet->detach(); }
   
   void attach(PacketBuf &pbuf) { packet->attach(pbuf); }
   
   void detach(PacketBuf &pbuf) { packet->detach(pbuf); }
   
   void detach(PacketHeader *dst) { packet->detach(dst); }
   
   template <class ... SS>
   void detach(Packet<POD,SS...> dst) { packet->detach(dst.getPtr()); }
   
   // data 
   
   bool noSpace() { return packet->noSpace(); }
    
   ulen getMaxDataLen() { return packet->getMaxRawLen()/sizeof (POD); }
   
   ulen getDataLen() { return packet->getRawLen()/sizeof (POD); }
   
   POD * getData() { return packet->getRaw(); }
    
   PtrLen<POD> getMaxRange() { return Range(getData(),getMaxDataLen()); }
   
   PtrLen<POD> getRange() { return Range(getData(),getDataLen()); }
  
   bool checkDataLen(ULenSat data_len)
    {
     return data_len<=getMaxDataLen();
    }
   
   PtrLen<POD> setDataLen(ULenSat data_len) // assume checkDataLen(data_len)
    { 
     ulen raw_len=data_len.value*sizeof (POD); 
     
     packet->setRawLen(raw_len);
     
     return Range(getData(),data_len.value);
    }
    
   // format
   
   PacketFormat::SubResult getMaxDataLen(PacketFormat format) 
    { 
     return format.sub(getMaxDataLen()); 
    }
   
   PacketFormat::SubResult getDataLen(PacketFormat format) 
    { 
     return format.sub(getDataLen()); 
    }
   
   PacketFormat::CutResult<POD> getMaxRange(PacketFormat format) 
    { 
     return format.cutMax(getMaxRange()); 
    }
   
   bool checkRange(PacketFormat format) 
    { 
     return format.check(getDataLen()); 
    }
   
   PtrLen<POD> getRange(PacketFormat format) // assume checkRange(format)
    { 
     return format.cut(getRange()); 
    }
   
   PtrLen<POD> getPrefix(PacketFormat format) // assume checkRange(format)
    { 
     return format.cutPrefix(getRange()); 
    }
   
   PtrLen<POD> getSuffix(PacketFormat format) // assume checkRange(format)
    { 
     return format.cutSuffix(getRange()); 
    }
   
   bool checkDataLen(PacketFormat format,ULenSat data_len)
    {
     return format.checkLen(data_len,getMaxDataLen());
    }
   
   PtrLen<POD> setDataLen(PacketFormat format,ULenSat data_len) // assume checkDataLen(format,data_len)
    { 
     setDataLen(format.add(data_len.value)); 
     
     return Range(getData()+format.prefix,data_len.value);
    }
 };
 
/* functions */  

inline PacketHeader * GetPacketHeader(PacketHeader *packet) { return packet; }
 
template <class POD,class ... TT>
PacketHeader * GetPacketHeader(Packet<POD,TT...> packet) { return packet.getPtr(); }
 
template <class POD,class T>
void DropPacketExt(PacketHeader *packet_)
 {
  Packet<POD,T> packet=packet_;
  
  packet.popExt().complete();
 }
 
/* class PacketCanceller */ 

class PacketCanceller : NoCopy
 {
   PacketHeader *packet;
   PacketFunction cancel_function;
   
  public: 
   
   template <class P>
   explicit PacketCanceller(P packet_) : packet(GetPacketHeader(packet_)) {}
   
   bool getCancelFunction() { return packet->getCancelFunction(cancel_function)==Packet_HasCancelFunction; }
   
   void cancel() { cancel_function(packet); }
 };

/* class PacketList */ 

class PacketList : NoCopy
 {
   PacketHeader::Algo::Top list;
   ulen count;
   ulen total_len;
   
  private:
  
   void post_ins(PacketHeader *packet);
  
   void post_del(PacketHeader *packet);
   
  public:
   
   // constructors
  
   PacketList();
  
   ~PacketList();
   
   ulen getCount() const { return count; }
   
   ulen getTotalLen() const { return total_len; }
   
   // put
   
   void put(PacketHeader *packet);
   
   void put_first(PacketHeader *packet);
   
   template <class P>
   void put(P packet) { put(GetPacketHeader(packet)); }
  
   template <class P>
   void put_first(P packet) { put_first(GetPacketHeader(packet)); }
   
   // get
   
   PacketHeader * get();
   
   PacketHeader * get_last();
   
   // del
   
   void del(PacketHeader *packet);
    
   template <class P>
   void del(P packet) { del(GetPacketHeader(packet)); }
   
   // methods
   
   void complete();
  
   void moveOld(TimeStamp how_old,PacketList &dest);
   
   // swap/move object
   
   void objSwap(PacketList &obj)
    {
     Swap(list,obj.list);
     Swap(count,obj.count);
     Swap(total_len,obj.total_len);
    }
   
   explicit PacketList(ToMoveCtor<PacketList> obj)
    : list(obj->list),
      count(Replace_null(obj->count)),
      total_len(obj->total_len)
    {
    }
   
   PacketList * objMove(Place<void> place)
    {
     return CtorMove(this,place);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
} // namespace CCore
 
#endif
 

