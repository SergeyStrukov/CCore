/* Collector.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_array_Collector_h
#define CCore_inc_array_Collector_h
 
#include <CCore/inc/array/ArrayBase.h>

#include <CCore/inc/List.h>

namespace CCore {

/* classes */

struct CollectorHeader;

class DefaultCollectorHeader;

template <class T,class Algo=ArrayAlgo<T> > class Collector;

/* struct CollectorHeader */

struct CollectorHeader
 {
  ulen len;
  ulen maxlen;
  
  DLink<CollectorHeader> link;
    
  void init(ulen maxlen_)
   {
    len=0;
    maxlen=maxlen_;
   }
   
  void exit() {}
 };

/* class DefaultCollectorHeader */

class DefaultCollectorHeader
 {
   static CollectorHeader DefaultObject;
   
   template <class T,class Algo> friend class Collector;
 };

/* class Collector<T,Algo> */

template <class T,class Algo> 
class Collector : NoCopy
 {
   typedef DLink<CollectorHeader>::LinearAlgo<&CollectorHeader::link> ListAlgo;
   
   typedef ArrayBase<T,CollectorHeader,Algo> Base;
   
  private:
  
   ulen block_len;
   
   ListAlgo::FirstLast list;
   ulen list_len;
   
   CollectorHeader *cur;
   
  private: 
   
   CollectorHeader * provide() // provides not default ptr with room for 1 elements
    {
     CollectorHeader *ptr=cur;
     
     if( ptr->len<ptr->maxlen ) return ptr;
     
     CollectorHeader *new_ptr=Base::Create(block_len);
     
     if( ptr->maxlen )
       {
        list.ins_last(ptr);
        
        list_len+=ptr->len;
       }
     
     cur=new_ptr;
     
     return new_ptr;
    }
   
   CollectorHeader * provide(ulen extra_len) // provides not default ptr with room for extra_len elements
    {
     CollectorHeader *ptr=cur;
     
     if( extra_len<=Base::GetExtraLen(ptr) && ptr->maxlen ) return ptr;

     CollectorHeader *new_ptr=Base::Create(Max(block_len,extra_len));
     
     if( ptr->maxlen )
       {
        Base::Shrink_extra(ptr);
        
        list.ins_last(ptr);
        
        list_len+=ptr->len;
       }
     
     cur=new_ptr;
     
     return new_ptr;
    }
   
   bool pop()
    {
     Base::Destroy(cur);
     
     if( CollectorHeader *ptr=list.del_last() )
       {
        list_len-=ptr->len;
        
        cur=ptr;
        
        return true;
       }
     else
       {
        cur=&DefaultCollectorHeader::DefaultObject;
        
        return false;
       }
    }
   
   PtrLen<T> do_extract(Place<void> place)
    {
     ulen len=getLen();
     
     ListAlgo::FirstLast work=Replace_null(list);
     
     list_len=0;
     
     if( cur->maxlen )
       {
        work.ins_last(Replace(cur,&DefaultCollectorHeader::DefaultObject));
       }
     
     PtrLen<T> ret(place,len);
     
     while( CollectorHeader *ptr=work.del_first() )
       {
        place=Base::MoveAndDestroy(ptr,place);
       }
      
     return ret;
    }
   
   PtrLen<T> do_copy(Place<void> place) const
    {
     ulen len=getLen();
     
     typename Algo::template CreateGuardNoThrow<Algo::Copy_no_throw> guard(place,len);
     
     for(auto curlist=list.start(); +curlist ;++curlist)
       {
        auto range=Range_const(Base::GetPtr(curlist.ptr),curlist->len);
        
        for(; +range ;++range,++guard) new(guard.at()) T(*range);
       }
     
     if( cur->len )
       {
        auto range=Range_const(Base::GetPtr(cur),cur->len);
        
        for(; +range ;++range,++guard) new(guard.at()) T(*range);
       }
     
     return guard.disarm();
    }
   
  private:
   
   struct Extractor
    {
     Collector *obj;
     
     explicit Extractor(Collector *obj_) : obj(obj_) {}

     ulen getLen() const { return obj->getLen(); }
     
     PtrLen<T> operator () (Place<void> place) { return obj->do_extract(place); }
    };
   
   struct Copyrator
    {
     const Collector *obj;
     
     explicit Copyrator(const Collector *obj_) : obj(obj_) {}

     ulen getLen() const { return obj->getLen(); }
     
     PtrLen<T> operator () (Place<void> place) { return obj->do_copy(place); }
    };
   
  public:
   
   // constructors
   
   static const ulen DefaultBlockLen = 1024 ;
   static const ulen MinBlockLen = 10 ;
   
   explicit Collector(ulen block_len_=DefaultBlockLen)
    : block_len(Max(MinBlockLen,block_len_)),
      list_len(0)
    {
     cur=&DefaultCollectorHeader::DefaultObject;
    }
   
   ~Collector()
    {
     while( CollectorHeader *ptr=list.del_first() ) Base::Destroy(ptr);
      
     Base::Destroy(cur);
    }
   
   // methods
   
   ulen getLen() const 
    {  
     return list_len+cur->len;
    }
   
   void erase()
    {
     Collector<T,Algo> temp;
     
     Swap(*this,temp);
    }
   
   template <class Container>
   void extractTo(Container &ret)
    {
     Container temp(DoBuild,Extractor(this));
     
     Swap(temp,ret);
    }
   
   template <class Container>
   void copyTo(Container &ret) const
    {
     Container temp(DoBuild,Copyrator(this));
     
     Swap(temp,ret);
    }
   
   PtrLen<T> flat()
    {
     ulen len=getLen();
     
     if( !len ) return Nothing;
     
     CollectorHeader *ptr=Base::Create(len);
     
     PtrLen<T> ret=Base::Extend(ptr,Extractor(this));
     
     cur=ptr;
     
     return ret;
    }
   
   // shrink 
   
   ulen shrink(ulen delta_len)
    {
     ulen ret=0;
     
     do
       {
        ulen count=Base::Shrink(cur,delta_len);
        
        if( count==delta_len ) return ret+count;
        
        ret+=count;
        delta_len-=count;
       }
     while( pop() );
     
     return ret;
    }
    
   bool shrink_one()
    {
     do
       {
        if( Base::Shrink_one(cur) ) return true;
       }
     while( pop() );
     
     return false;
    }
    
   ulen shrink_all()
    {
     ulen ret=getLen();
     
     while( CollectorHeader *ptr=list.del_first() ) Base::Destroy(ptr);
      
     Base::Destroy(cur);
     
     list_len=0;
     
     cur=&DefaultCollectorHeader::DefaultObject;
     
     return ret;
    }
    
   // extend
   
   PtrLen<T> extend_raw(ulen delta_len)
    {
     return Base::Extend_raw(provide(delta_len),delta_len);
    }
   
   PtrLen<T> extend_default(ulen delta_len)
    {
     return Base::Extend_default(provide(delta_len),delta_len);
    }
   
   template <class ... SS>
   PtrLen<T> extend_fill(ulen delta_len,SS && ... ss)
    {
     return Base::Extend_fill(provide(delta_len),delta_len, std::forward<SS>(ss)... );
    }
    
   PtrLen<T> extend_copy(ulen delta_len,const T src[])
    {
     return Base::Extend_copy(provide(delta_len),delta_len,src);
    }
   
   template <class S>
   PtrLen<T> extend_cast(ulen delta_len,const S src[])
    {
     return Base::Extend_cast(provide(delta_len),delta_len,src);
    }
   
   PtrLen<T> extend_swap(ulen delta_len,T objs[])
    {
     return Base::Extend_swap(provide(delta_len),delta_len,objs);
    }
   
   template <class Creator>
   PtrLen<T> extend(ulen delta_len,Creator creator)
    {
     return Base::Extend(provide(delta_len),delta_len,creator);
    }
   
   template <class Builder>
   PtrLen<T> extend(Builder builder)
    {
     return Base::Extend(provide(builder.getLen()),builder);
    }
   
   // append
   
   T * append_raw()
    {
     return Base::Append_raw(provide());
    }
   
   T * append_default()
    {
     return Base::Append_default(provide());
    }
    
   template <class ... SS> 
   T * append_fill(SS && ... ss) 
    {
     return Base::Append_fill(provide(), std::forward<SS>(ss)... );
    }
   
   T * append_copy(const T &src)
    {
     return Base::Append_copy(provide(),src);
    }
   
   T * append_swap(T &obj)
    {
     return Base::Append_swap(provide(),obj);
    }
   
   template <class Creator>
   T * append(Creator creator)
    {
     return Base::Append(provide(),creator);
    }
   
   // swap/move object
   
   void objSwap(Collector<T,Algo> &obj)
    {
     Swap(block_len,obj.block_len);
     Swap(list,obj.list);
     Swap(list_len,obj.list_len);
     Swap(cur,obj.cur);
    }
   
   explicit Collector(ToMoveCtor<Collector<T,Algo> > obj)
    : block_len(obj->block_len),
      list(Replace_null(obj->list)),
      list_len(obj->list_len),
      cur(Replace(obj->cur,&DefaultCollectorHeader::DefaultObject))
    {
    } 
    
   Collector<T,Algo> * objMove(Place<void> place)
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
 

