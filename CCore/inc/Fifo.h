/* Fifo.h */ 
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

#ifndef CCore_inc_Fifo_h
#define CCore_inc_Fifo_h

#include <CCore/inc/Swap.h>
 
namespace CCore {

/* classes */ 

template <class T> class Fifo;

template <class T,ulen Len> class FifoBuf;

/* class Fifo<T> */ 

template <class T> 
class Fifo : NoCopy
 {
   T *const buf;
   const ulen len;
   
   ulen put_ind;
   ulen get_ind;
   ulen count;
   
  private:
  
   ulen next(ulen ind) const { return (ind+1<len)?ind+1:0; }
 
  public:
  
   Fifo(T *buf_,ulen len_)
    : buf(buf_),
      len(len_)
    {
     put_ind=0;
     get_ind=0;
     count=0;
    }
    
   ulen getCount() const { return count; }
   
   bool isEmpty() const { return count==0; }
   
   bool isFull() const { return count==len; }
   
   void reset()
    {
     put_ind=0;
     get_ind=0;
     count=0;
    }
   
   // put
   
   template <class Func>
   bool put_gen(Func func)
    {
     if( count<len )
       {
        func(buf[put_ind]);
        
        put_ind=next(put_ind);
        count++;
       
        return true;
       }
       
     return false;  
    }
    
   bool put(const T &obj) { return put_gen( [&] (T &dst) { dst=obj; } ); }
   
   bool put_swap(T &obj) { return put_gen( [&] (T &dst) { Swap(dst,obj); } ); }
   
   // get
   
   template <class Func>
   bool get_gen(Func func)
    {
     if( count )
       {
        func(buf[get_ind]);
        
        get_ind=next(get_ind);
        count--;
        
        return true;
       }
       
     return false;  
    }
    
   bool get(T &obj) { return get_gen( [&] (const T &src) { obj=src; } ); }
    
   bool get_swap(T &obj) { return get_gen( [&] (T &src) { Swap(src,obj); } ); }
 };
 
/* class FifoBuf<T,ulen Len> */ 

template <class T,ulen Len> 
class FifoBuf : public Fifo<T>
 {
   T buf[Len];
   
  public:
  
   FifoBuf() : Fifo<T>(buf,Len) {}
  
   ~FifoBuf() {}
 };
 
} // namespace CCore
 
#endif
 

