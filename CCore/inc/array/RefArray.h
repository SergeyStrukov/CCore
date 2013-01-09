/* RefArray.h */ 
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

#ifndef CCore_inc_array_RefArray_h
#define CCore_inc_array_RefArray_h
 
#include <CCore/inc/array/ArrayBase.h>

#include <CCore/inc/RefPtr.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */ 

struct RefArrayHeader;

class DefaultRefArrayHeader;

template <class T,class Algo> class RefArrayBase;

template <class T,class Algo=ArrayAlgo<T> > class RefArray;
 
/* struct RefArrayHeader */ 

struct RefArrayHeader
 {
  ulen len;
  ulen maxlen;
  ulen refs; // has indeterminant value for default object due to race condition
    
  void init(ulen maxlen_)
   {
    len=0;
    maxlen=maxlen_;
    refs=1;
   }
   
  void exit() {}
  
  void incRef() { refs++; }
  
  bool decRef() { return !--refs; }
  
  bool isShared() { return maxlen==0 || refs>1 ; }
 };
 
/* class DefaultRefArrayHeader */ 

class DefaultRefArrayHeader
 {
   static RefArrayHeader DefaultObject;
   
   template <class T,class Algo> friend class RefArrayBase;
 };
 
/* class RefArrayBase<T,Algo> */ 
 
template <class T,class Algo> 
class RefArrayBase
 {
   friend class RefArray<T,Algo>;
   
   typedef ArrayBase<T,RefArrayHeader,Algo> Base;
  
   struct RefAlgo
    {
     static void IncRef(RefArrayHeader *ptr) { ptr->incRef(); }
  
     static bool DecRef(RefArrayHeader *ptr) { return ptr->decRef(); }
  
     static void Destroy(RefArrayHeader *ptr) { Base::Destroy(ptr); }
    };
 
   // data
   
   RefPtr<RefArrayHeader,RefAlgo> ptr;
  
   // constructors
   
   RefArrayBase() 
    : ptr(&DefaultRefArrayHeader::DefaultObject)
    {
    }
   
   explicit RefArrayBase(RefPtr<RefArrayHeader,RefAlgo> &ptr_)
    : ptr(ObjToMove(ptr_))
    {
    }
  
   explicit RefArrayBase(ulen maxlen) 
    : ptr(Base::Create(maxlen))
    {
    }
  
   ~RefArrayBase() 
    {
    }
 };
  
/* class RefArray<T,Algo> */ 
  
template <class T,class Algo> 
class RefArray : RefArrayBase<T,Algo>
 {
   typedef typename RefArrayBase<T,Algo>::Base Base;
   
   using RefArrayBase<T,Algo>::ptr;
   
  private: 
  
   void unshare()
    {
     RefArray<T,Algo> temp(DoCopy(getLen(),getMaxLen()),getPtr());
     
     Swap(*this,temp);
    }
    
   ulen shrink_shared(ulen delta_len) 
    {
     ulen len=getLen();
     
     if( len<delta_len ) delta_len=len;
     
     if( delta_len==0 ) return 0;
     
     len-=delta_len;
    
     RefArray<T,Algo> temp(DoCopy(len,getMaxLen()),getPtr());
     
     Swap(*this,temp);
     
     return delta_len;
    }
 
   void provide_shared(ulen extra_len)
    {
     ulen maxlen;
     
     if( extra_len<=getExtraLen() ) 
       maxlen=getMaxLen();
     else
       maxlen=Algo::ProvideLen(getLen(),getMaxLen(),extra_len);  
    
     RefArray<T,Algo> temp(DoCopy(getLen(),maxlen),getPtr());
     
     Swap(*this,temp);
    }
    
   RefArrayHeader * provide() // provides not default ptr with room for 1 elements
    {
     if( ptr->isShared() )
       {
        provide_shared(1);
       }
     else
       {
        ptr.update( Base::Provide_one );
       }  
     
     return ptr.getPtr();
    }
   
   RefArrayHeader * provide(ulen extra_len) // provides not default ptr with room for extra_len elements
    {
     if( ptr->isShared() )
       {
        provide_shared(extra_len);
       }
     else
       {
        ptr.update( [=] (RefArrayHeader *hptr) -> RefArrayHeader * { return Base::Provide(hptr,extra_len); } );
       }  
     
     return ptr.getPtr();
    } 
 
  public:
  
   // constructors
   
   RefArray() {}
   
   template <class S>
   explicit RefArray(std::initializer_list<S> il) 
    : RefArrayBase<T,Algo>(il.size())
    {
     Base::Extend_cast(ptr.getPtr(),il.size(),il.begin());
    }
   
   explicit RefArray(ulen len) 
    : RefArrayBase<T,Algo>(len)
    {
     Base::Extend_default(ptr.getPtr(),len);
    }
   
   RefArray(ulen len,ulen maxlen) 
    : RefArrayBase<T,Algo>(maxlen)
    {
     GuardLen(len,maxlen);
     
     Base::Extend_default(ptr.getPtr(),len);
    }
    
   RefArray(DoReserveType,ulen maxlen) 
    : RefArrayBase<T,Algo>(maxlen) 
    {
    }
    
   explicit RefArray(DoRaw dotype) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_raw(ptr.getPtr(),dotype.getLen());
    }
   
   template <class ... SS> 
   explicit RefArray(DoFill dotype,SS && ... ss) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_fill(ptr.getPtr(),dotype.getLen(), std::forward<SS>(ss)... );
    }
    
   RefArray(DoCopy dotype,const T src[]) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_copy(ptr.getPtr(),dotype.getLen(),src);
    }
 
   template <class S>
   RefArray(DoCast dotype,const S src[]) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_cast(ptr.getPtr(),dotype.getLen(),src);
    }
   
   RefArray(DoSwap dotype,T objs[]) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_swap(ptr.getPtr(),dotype.getLen(),objs);
    }
   
   template <class Creator> 
   RefArray(DoCreate dotype,Creator creator) 
    : RefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend(ptr.getPtr(),dotype.getLen(),creator);
    }
    
   template <class Builder> 
   RefArray(DoBuildType,Builder builder) 
    : RefArrayBase<T,Algo>(builder.getLen())
    {
     Base::Extend(ptr.getPtr(),builder);
    }
    
   ~RefArray() {}
   
   // range access
   
   const T * getPtr() const { return Base::GetSafePtr(ptr.getPtr()); }
   
   const T * getPtr_const() const { return Base::GetSafePtr(ptr.getPtr()); }
   
   ulen getLen() const { return ptr->len; }
   
   ulen getMaxLen() const { return ptr->maxlen; }
   
   ulen getExtraLen() const { return Base::GetExtraLen(ptr.getPtr()); }
   
   // index access
   
   const T & operator [] (ulen index) const
    {
     return Base::GetPtr(ptr.getPtr())[index];
    }
   
   const T & at(ulen index) const
    {
     GuardIndex(index,getLen());
    
     return Base::GetPtr(ptr.getPtr())[index];
    }
   
   // methods
   
   PtrLen<T> modify()
    {
     if( ptr->isShared() ) unshare();
     
     return PtrLen<T>(Base::GetPtr(ptr.getPtr()),getLen());
    }
   
   PtrLenReverse<T> modifyReverse() { return RangeReverse(modify()); }
     
   void cloneTo(RefArray<T,Algo> &ret) const
    {
     RefArray<T,Algo> temp(DoCopy(getLen(),getMaxLen()),getPtr());
     
     Swap(ret,temp);
    }
    
   void reserve(ulen extra_len)
    {
     provide(extra_len);
    }
   
   void erase()
    {
     RefArray<T,Algo> temp;
     
     Swap(*this,temp);
    } 
    
   // shrink
   
   ulen shrink(ulen delta_len)
    {
     if( ptr->isShared() )
       {
        return shrink_shared(delta_len);
       }
     else
       {
        return Base::Shrink(ptr.getPtr(),delta_len);
       }
    }
    
   bool shrink_one()
    {
     if( ptr->isShared() )
       {
        return shrink_shared(1);
       }
     else
       {
        return Base::Shrink_one(ptr.getPtr());
       }
    }
    
   ulen shrink_all()
    {
     if( ptr->isShared() )
       {
        return shrink_shared(getLen());
       }
     else
       {
        return Base::Shrink_all(ptr.getPtr());
       }
    }
    
   void shrink_extra()
    {
     Base::Shrink_extra(ptr.getPtr());
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
   
   // apply
   
   template <class FuncInit>
   void apply_modify(FuncInit func_init) { Algon::ApplyToRange(modify(),func_init); }
   
   template <class FuncInit>
   void apply(FuncInit func_init) const { Algon::ApplyToRange(Range(*this),func_init); }
   
   template <class FuncInit>
   void applyReverse_modify(FuncInit func_init) { Algon::ApplyToRange(modifyReverse(),func_init); }
   
   template <class FuncInit>
   void applyReverse(FuncInit func_init) const { Algon::ApplyToRange(RangeReverse(*this),func_init); }
   
   // swap/move objects
   
   void objSwap(RefArray<T,Algo> &obj)
    {
     Swap(ptr,obj.ptr);
    }
   
   explicit RefArray(ToMoveCtor<RefArray<T,Algo> > obj)
    : RefArrayBase<T,Algo>(obj->ptr)
    {
    }
   
   RefArray<T,Algo> * objMove(Place<void> place)
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
 

