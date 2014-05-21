/* BlockFifo.h */ 
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

#ifndef CCore_inc_BlockFifo_h
#define CCore_inc_BlockFifo_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */ 

template <class T> class BlockFifo;

template <class T,ulen Len> class BlockFifoBuf;

/* class BlockFifo<T> */ 

template <class T> 
class BlockFifo : NoCopy
 {
   T *const buf;
   const ulen len;
   
   ulen off;
   ulen count;
   
  public:
   
   BlockFifo(T *buf_,ulen len_)
    : buf(buf_),
      len(len_) 
    {
     off=0;
     count=0;
    }
   
   ulen getCount() const { return count; }
   
   bool isEmpty() const { return count==0; }
   
   bool isFull() const { return count==len; }
   
   void reset()
    {
     off=0;
     count=0;
    }
   
   // put
   
   template <class Func>
   ulen put(ulen putlen,Func func) // func(T *ptr,ulen len)
    {
     ulen free=len-count;
     
     Replace_min(putlen,free);
     
     ulen putoff=off+count;
     
     if( putoff>=len ) putoff-=len;
     
     ulen rest=len-putoff;
     
     if( putlen<=rest )
       {
        func(buf+putoff,putlen);
       }
     else
       {
        func(buf+putoff,rest);
        func(buf,putlen-rest);
       }
     
     count+=putlen;
     
     return putlen;
    }
   
   ulen put(PtrLen<const T> data)
    {
     return put(data.len, [&] (T *ptr,ulen len) { (data+=len).copyTo(ptr); } );
    }
   
   // get
   
   template <class Func>
   ulen get(ulen getlen,Func func) // func([const] T *ptr,ulen len)
    {
     Replace_min(getlen,count);
     
     ulen rest=len-off;
     
     if( getlen<=rest )
       {
        func(buf+off,getlen);
        
        off+=getlen;
        
        if( off>=len ) off=0;
       }
     else
       {
        func(buf+off,rest);
        
        ulen last=getlen-rest;
        
        func(buf,last);
        
        off=last;
       }
     
     count-=getlen;
     
     return getlen;
    }
 
   ulen get(PtrLen<T> data)
    {
     return get(data.len, [&] (const T *ptr,ulen len) { (data+=len).copyFrom(ptr); } );
    }
 };

/* class BlockFifoBuf<T,ulen Len> */ 

template <class T,ulen Len> 
class BlockFifoBuf : public BlockFifo<T>
 {
   T buf[Len];
   
  public:
  
   BlockFifoBuf() : BlockFifo<T>(buf,Len) {}
  
   ~BlockFifoBuf() {}
 };
 
} // namespace CCore
 
#endif
 

