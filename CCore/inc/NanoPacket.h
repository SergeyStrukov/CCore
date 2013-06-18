/* NanoPacket.h */ 
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

#ifndef CCore_inc_NanoPacket_h
#define CCore_inc_NanoPacket_h

#include <CCore/inc/List.h>
#include <CCore/inc/Move.h>

#include <CCore/inc/task/FastMutex.h>
 
namespace CCore {

/* functions */ 

void NanoPacketListExitAbort();

void NanoPacketPoolExitAbort();

/* classes */ 

template <class POD> class NanoPacket;

template <class POD> class NanoPacketList;

template <class POD> class NanoPacketPool;

/* class NanoPacket<POD> */ 

template <class POD>
class NanoPacket
 {
   static_assert( std::is_pod<POD>::value ,"CCore::NanoPacket<POD> : POD must be POD");
   
   typedef Function<void (NanoPacket<POD> packet)> NanoPacketFunction;

   struct Header
    {
     ulen data_len;
     ulen max_data_len;
   
     NanoPacketFunction free_function;
   
     DLink<Header> link;
     
     Header(ulen max_data_len_,NanoPacketFunction free_function_)
      : data_len(0),
        max_data_len(max_data_len_),
        free_function(free_function_)
      {
      }
    };
 
   static const ulen Delta = Align(sizeof (Header)) ;
   
   typedef typename DLink<Header>::template CircularAlgo<&Header::link> Algo;
   
  private:
  
   Header *ptr;
   
  private: 
   
   NanoPacket(Header *ptr_) : ptr(ptr_) {}
   
   friend class NanoPacketList<POD>;
   
  public: 
   
   // constructors
  
   static constexpr ulen AllocLen(ulen max_data_len) { return Align(Delta+max_data_len*sizeof (POD)); }
  
   NanoPacket() : ptr(0) {}
 
   NanoPacket(NothingType) : ptr(0) {}
   
   NanoPacket(Place<void> place,ulen max_data_len,NanoPacketFunction free_function)
    {
     ptr=new(place) Header(max_data_len,free_function);
    }
   
   // methods
   
   bool operator + () const { return ptr!=0; }
   
   bool operator ! () const { return ptr==0; }
 
   void free() 
    {
     auto func=ptr->free_function;
     
     func(Replace_null(*this)); 
    }
   
   // data
    
   POD * getData() const { return PlaceAt(ptr)+Delta; } 
   
   ulen getDataLen() const { return ptr->data_len; }
   
   ulen getMaxDataLen() const { return ptr->max_data_len; }
   
   PtrLen<POD> getRange() const { return Range(getData(),ptr->data_len); }
   
   PtrLen<POD> getMaxRange() const { return Range(getData(),ptr->max_data_len); }
   
   PtrLen<POD> setDataLen(ulen len) { ptr->data_len=len; return Range(getData(),len); }
 };
 
/* class NanoPacketList<POD> */ 
 
template <class POD> 
class NanoPacketList : NoCopy
 {
   typename NanoPacket<POD>::Algo::Top list;
 
  public:
  
   NanoPacketList() {}
   
   ~NanoPacketList() 
    {
     if( +list ) NanoPacketListExitAbort();
    }
   
   bool operator + () const { return +list; }
   
   bool operator ! () const { return !list; }
   
   void put(NanoPacket<POD> packet)
    {
     list.ins_last(packet.ptr);
    }
   
   void put_first(NanoPacket<POD> packet)
    {
     list.ins_first(packet.ptr);
    }
   
   NanoPacket<POD> get()
    {
     return list.del_first();
    }
   
   void freeAll()
    {
     for(;;)
       {
        NanoPacket<POD> packet=get();
        
        if( !packet ) break;
        
        packet.free();
       }
    }
    
   void cleanAll() { list.init(); }
   
   // swap/move object
    
   void objSwap(NanoPacketList<POD> &obj)
    {
     Swap(list,obj.list);
    }
   
   explicit NanoPacketList(ToMoveCtor<NanoPacketList<POD> > obj)
    : list(Replace_null(obj->list))
    {
    }
   
   NanoPacketList<POD> * objMove(Place<void> place)
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
 
/* class NanoPacketPool<POD> */ 

template <class POD> 
class NanoPacketPool : FastMutexBase , public Funchor
 {
   NanoPacketList<POD> list;
   
   ulen use_count;
   
  private:
  
   virtual void post_free() {}
  
   void free(NanoPacket<POD> packet)
    {
     packet.setDataLen(0);

     {
      Lock lock(*this);
     
      list.put_first(packet);
     
      use_count--;
     }
     
     post_free(); 
    }
    
   Function<void (NanoPacket<POD> packet)> function_free() { return FunctionOf(this,&NanoPacketPool::free); }
 
  public:
  
   NanoPacketPool(void *mem,ulen max_data_len,ulen count) // aligned mem, 
                                                          // NanoPacket<POD>::AllocLen(max_data_len)*count length 
    : use_count(0)
    {
     Place<void> place(mem);
     
     ulen alloc_len=NanoPacket<POD>::AllocLen(max_data_len);
     
     auto func=function_free();
     
     for(ulen cnt=count; cnt ;cnt--,place+=alloc_len)
       {
        NanoPacket<POD> packet(place,max_data_len,func);
        
        list.put(packet);
       }
    }
   
   ~NanoPacketPool()
    {
     {
      Lock lock(*this);
      
      if( use_count ) NanoPacketPoolExitAbort();
     }
    
     list.cleanAll();
    }
   
   NanoPacket<POD> try_get()
    {
     Lock lock(*this);
     
     NanoPacket<POD> ret=list.get();
     
     if( +ret ) use_count++;
     
     return ret;
    }
 };
 
} // namespace CCore
 
#endif
 

