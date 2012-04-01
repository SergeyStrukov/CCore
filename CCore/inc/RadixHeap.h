/* RadixHeap.h */ 
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

#ifndef CCore_inc_RadixHeap_h
#define CCore_inc_RadixHeap_h

#include <CCore/inc/List.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/ScanBit.h>

namespace CCore {

/* functions */ 

void RadixHeapAbort();

/* classes */ 

struct RadixHeapBlock;

class RadixHeapStore_small;

class RadixHeapStore_large;

class RadixHeapStore;

template <class Mem> class RadixHeap;

/* struct RadixHeapBlock */ 

struct RadixHeapBlock
 {
  ulen len;      // aligned && >= Delta()
  ulen prev_len;
  ulen flags;
  ulen magic;
  
  enum Flags : ulen
   {
    FirstBit = 0x01,
    LastBit  = 0x02,
    LockBit  = 0x04
   };
 
  // props
  
  bool isLarge() const { return (flags&(FirstBit|LastBit))==(FirstBit|LastBit); } 
   
  // mem <-> block 
  
  static constexpr ulen Delta() { return Align(sizeof (RadixHeapBlock)); }
  
  Place<void> getMem() { return PlaceAt(this)+Delta(); }
  
  ulen getMemLen() const { return len-Delta(); }
   
  static RadixHeapBlock * GetBlock(void *mem) { return PlaceAt(mem)-Delta(); }
   
  static const RadixHeapBlock * GetBlock(const void *mem) { return PlaceAt(mem)-Delta(); }
   
  // move
  
  RadixHeapBlock * getNext() { return PlaceAt(this)+len; }
   
  RadixHeapBlock * getPrev() { return PlaceAt(this)-prev_len; } 
  
  RadixHeapBlock * getFreePrev()
   {
    if( flags&FirstBit ) return 0;
    
    RadixHeapBlock *prev=getPrev();
    
    if( prev->flags&LockBit ) return 0;
    
    return prev;
   }
   
  RadixHeapBlock * getFreeNext()
   {
    if( flags&LastBit ) return 0;
    
    RadixHeapBlock *next=getNext();
    
    if( next->flags&LockBit ) return 0;
    
    return next;
   } 
  
  // lock/unlock 
   
  ulen stamp() const { return ulen( len^ulen(this)^flags ); }
   
  void init_magic() { magic=~stamp(); }
   
  Space lock() 
   {
    BitSet(flags,LockBit);
    
    flags|=ulen(ClockTimer::Get()<<3);
    
    magic=stamp();
   
    return Space(getMem(),getMemLen());
   }
   
  RadixHeapBlock * unlock()
   {
    if( !(flags&LockBit) || magic!=stamp() ) RadixHeapAbort();
    
    flags&=(FirstBit|LastBit);
    
    init_magic();
    
    return this;
   }
   
  static RadixHeapBlock * Unlock(void *mem) { return GetBlock(mem)->unlock(); }
  
  // init
  
  void init(ulen len_)
   {
    len=len_;
    prev_len=0;
    flags=FirstBit|LastBit;
    init_magic();
   }
 
  // split
  
  RadixHeapBlock * split(ulen new_len) // return next block
   {
    ulen next_len=len-new_len;
    ulen next_flags;
   
    if( flags&LastBit )
      {
       BitClear(flags,LastBit);
       
       next_flags=LastBit;
      } 
    else
      {
       RadixHeapBlock *next=getNext();
       
       next->prev_len=next_len;
       
       next_flags=0;
      }
      
    len=new_len;
    init_magic();
    
    RadixHeapBlock *next=getNext();
    
    next->len=next_len;
    next->prev_len=new_len;
    next->flags=next_flags;
    next->init_magic();
    
    return next;   
   }
 
  // unite
  
  void unite(ulen new_len)
   {
    len=new_len;
    init_magic();
    
    getNext()->prev_len=new_len;
   }
   
  void unite_last(ulen new_len)
   {
    len=new_len;
    BitSet(flags,LastBit);
    init_magic();
   }
 
  static void Unite(RadixHeapBlock *a,RadixHeapBlock *b)
   {
    if( b->flags&LastBit )
      a->unite_last(a->len+b->len);
    else
      a->unite(a->len+b->len);
   }
 
  static void Unite(RadixHeapBlock *a,RadixHeapBlock *b,RadixHeapBlock *c)
   {
    if( c->flags&LastBit )
      a->unite_last(a->len+b->len+c->len);
    else
      a->unite(a->len+b->len+c->len);
   }
   
  // check
  
  static unsigned Check(void *mem,ulen len); // !=0 value means error
                                             //
                                             // 1 -- no FirstBit in the first block 
                                             // 2 -- too large block length
                                             // 3 -- too small block length
                                             // 4 -- not aligned block length
                                             // 5 -- prev_len!=len
                                             // 6 -- locked block with broken stamp
                                             // 7 -- bad last block length
                                             // 8 -- not aligned last block length
                                             // 9 -- locked last block with broken stamp
                                             //
 };
 
/* class RadixHeapStore_small */ 

class RadixHeapStore_small : NoCopy
 {
   static const ulen Len = 8 ;
   
   typedef Meta::Select<Quick::ScanMSBitIsFast, ScanBit<ScanMSBitAlgo,Len> ,
                                                ScanBit<ScanLSBitAlgo,Len> > Bits;
  
  public:
  
   struct Node 
    {
     DLink<Node> link;
    };
   
   static const ulen IndexLim = Bits::IndexLim ;

  private: 
  
   typedef DLink<Node>::LinearAlgo<&Node::link> Algo;
   
   Algo::Top tops[IndexLim];
   Bits bits;
  
  public:
  
   RadixHeapStore_small();
  
   void ins(Node *node,ulen ind);
  
   void del(Node *node,ulen ind);
  
   Node * find_and_del(ulen ind);
 };
 
/* class RadixHeapStore_large */ 

class RadixHeapStore_large : NoCopy
 {
  public:
  
   struct Node 
    {
     TreeUpLink<Node,ulen> link;
    };
    
  private:  
  
   typedef TreeUpLink<Node,ulen>::RadixAlgo<&Node::link> Algo;
  
   Algo::Root root;
   ulen max_ind;
  
  public:
  
   explicit RadixHeapStore_large(ulen max_ind_) : max_ind(max_ind_) {}
  
   void ins(Node *node,ulen ind);
  
   void del(Node *node,ulen ind);
  
   Node * find_and_del(ulen ind);
 };
 
/* class RadixHeapStore */ 

class RadixHeapStore : NoCopy
 {
   RadixHeapStore_small small;
   RadixHeapStore_large large;
  
  private:
  
   static ulen Index(ulen len) { return (len-MinLen)/MaxAlign; }
   
  public:
  
   static const ulen MinLen = RadixHeapBlock::Delta()+Align(sizeof (RadixHeapStore_small::Node)) ; 
  
   RadixHeapStore(ulen max_len) : large(Index(Max(max_len,MinLen))) {}
 
   void ins(RadixHeapBlock *block);
  
   void del(RadixHeapBlock *block);
  
   RadixHeapBlock * find_and_del(ulen len);
 };
 
/* class RadixHeap<Mem> */ 

 //
 // class Mem
 //  {
 //    const ulen max_store_len; // aligned
 //
 //   public:
 //
 //    Mem(...);
 //
 //    void cleanup(bool clean);
 //
 //    ulen getMaxStoreLen() const { return max_store_len; }
 //
 //    RadixHeapBlock * alloc(ulen blen);            // blen aligned 
 //                                                  // ( blen<=max_store_len ) => ( ret->len<=max_store_len )
 //
 //    void free(RadixHeapBlock *block);             // block!=0
 //
 //    bool extend(RadixHeapBlock *block,ulen blen); // block!=0, blen aligned, blen>block->len
 //
 //    ulen shrink(RadixHeapBlock *block,ulen blen); // block!=0, blen aligned, blen<=block->len , return delta
 //  };
 //
 
template <class Mem> 
class RadixHeap : NoCopy
 {
   Mem large_mem;
   RadixHeapStore store;
   ulen count;

  private:

   static bool TooLarge(ulen len)
    {
     return len>AlignDown( MaxULen-RadixHeapBlock::Delta() );
    }
    
   static ulen BLen(ulen len)
    {
     ulen blen=RadixHeapBlock::Delta()+Align(len);
  
     return Max(blen,RadixHeapStore::MinLen);
    }
    
   bool super(ulen blen) const { return blen>large_mem.getMaxStoreLen(); }
   
   void cut(RadixHeapBlock *block,ulen blen)
    {
     if( block->len-blen>=RadixHeapStore::MinLen ) store.ins(block->split(blen));
    }
  
  public:
  
   template <class ... SS>
   explicit RadixHeap(SS && ... ss)
    : large_mem( std::forward<SS>(ss)... ),
      store(large_mem.getMaxStoreLen()),
      count(0)
    {
    }  
   
   ~RadixHeap()
    {
     large_mem.cleanup(!count);
    }
 
   bool isEmpty() const { return count==0; }
  
   Space alloc(ulen len);               // ret.len!=0 on success (==memlen)
  
   ulen getLen(const void *mem);        // mem!=0, return memlen
   
   ulen free(void *mem);                // mem!=0, return memlen
   
   DeltaLen extend(void *mem,ulen len); // mem!=0

   DeltaLen shrink(void *mem,ulen len); // mem!=0
 };
 
template <class Mem> 
Space RadixHeap<Mem>::alloc(ulen len)
 {
  if( TooLarge(len) ) return Nothing;
  
  ulen blen=BLen(len);
  
  if( super(blen) )
    {
     RadixHeapBlock *block=large_mem.alloc(blen);
     
     if( !block ) return Nothing;
     
     count++;
    
     return block->lock();
    }
  else
    {
     RadixHeapBlock *block=store.find_and_del(blen);

     if( !block )
       {
        block=large_mem.alloc(blen);
        
        if( !block ) return Nothing;
       }
       
     cut(block,blen);
     
     count++;
       
     return block->lock();
    }
 }
   
template <class Mem> 
ulen RadixHeap<Mem>::getLen(const void *mem)
 {
  const RadixHeapBlock *block=RadixHeapBlock::GetBlock(mem);
  
  return block->getMemLen();
 }
 
template <class Mem> 
ulen RadixHeap<Mem>::free(void *mem)
 {
  RadixHeapBlock *block=RadixHeapBlock::Unlock(mem);
  ulen ret=block->getMemLen();
  
  count--;
  
  if( RadixHeapBlock *prev=block->getFreePrev() )
    {
     store.del(prev);
    
     if( RadixHeapBlock *next=block->getFreeNext() )
       {
        store.del(next);
        
        RadixHeapBlock::Unite(prev,block,next);
       }
     else 
       {
        RadixHeapBlock::Unite(prev,block);
       }
       
     block=prev;  
    }
  else
    {
     if( RadixHeapBlock *next=block->getFreeNext() )
       {              
        store.del(next);
        
        RadixHeapBlock::Unite(block,next);
       }
     else 
       {
        // do nothing
       }
    }  
    
  if( block->isLarge() )
    {
     large_mem.free(block);
    }
  else
    {
     store.ins(block);
    }
  
  return ret;  
 }
   
template <class Mem> 
DeltaLen RadixHeap<Mem>::extend(void *mem,ulen len)
 {
  RadixHeapBlock *block=RadixHeapBlock::Unlock(mem);
  
  ulen memlen=block->getMemLen();
  
  if( len<=memlen ) 
    {
     block->lock();
    
     return 0;
    }
  
  ulen blen=block->len;
     
  if( super(blen) )
    {
     if( !TooLarge(len) )
       {
        ulen newblen=BLen(len);
        
        if( large_mem.extend(block,newblen) )
          {
           block->lock();

           return block->len-blen;
          }
       }

     block->lock();  
    
     return Nothing;  
    }

  if( RadixHeapBlock *next=block->getFreeNext() )
    {
     if( len-memlen<=next->len )
       {
        store.del(next);
     
        RadixHeapBlock::Unite(block,next);
        
        ulen newblen=BLen(len);
        
        cut(block,newblen);
        
        block->lock();
        
        return block->len-blen;
       }
    }
    
  block->lock();  
    
  return Nothing;  
 }
  
template <class Mem> 
DeltaLen RadixHeap<Mem>::shrink(void *mem,ulen len)
 {
  RadixHeapBlock *block=RadixHeapBlock::Unlock(mem);
  
  ulen memlen=block->getMemLen();
  
  if( len>memlen )
    {
     block->lock();
     
     return Nothing;
    }
    
  ulen blen=BLen(len);
  
  if( super(block->len) )
    {
     ulen delta=large_mem.shrink(block,blen);

     block->lock();

     return delta;
    }

  if( block->len-blen>=RadixHeapStore::MinLen ) 
    {
     RadixHeapBlock *next=block->split(blen);
     ulen delta=next->len;
     
     block->lock();
     
     if( RadixHeapBlock *next1=next->getFreeNext() )
       {              
        store.del(next1);
        
        RadixHeapBlock::Unite(next,next1);
       }

     store.ins(next);
     
     return delta;
    }
    
  block->lock();  
    
  return 0;  
 }
 
} // namespace CCore
 
#endif
 

