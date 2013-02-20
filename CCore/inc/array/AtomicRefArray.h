/* AtomicRefArray.h */ 
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

#ifndef CCore_inc_array_AtomicRefArray_h
#define CCore_inc_array_AtomicRefArray_h
 
#include <CCore/inc/array/ArrayBase.h>

#include <CCore/inc/RefPtr.h>

#include <CCore/inc/sys/SysAtomic.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */ 

struct AtomicRefArrayHeader;

class DefaultAtomicRefArrayHeader;

template <class T,class Algo> class AtomicRefArrayBase;

template <class T,class Algo=ArrayAlgo<T> > class AtomicRefArray;
 
/* struct AtomicRefArrayHeader */ 

struct AtomicRefArrayHeader
 {
  ulen len;
  ulen maxlen;
  Sys::Atomic refs;
    
  void init(ulen maxlen_)
   {
    len=0;
    maxlen=maxlen_;
    refs=Sys::Atomic{1};
   }
   
  void exit() {}
  
  void incRef() { refs++; }
  
  bool decRef() { return (refs--)==1; }
  
  bool isShared() { return refs>1 ; }
 };
 
/* class DefaultAtomicRefArrayHeader */ 

class DefaultAtomicRefArrayHeader
 {
   static AtomicRefArrayHeader DefaultObject;
   
   template <class T,class Algo> friend class AtomicRefArrayBase;
 };
 
/* class AtomicRefArrayBase<T,Algo> */ 
 
template <class T,class Algo> 
class AtomicRefArrayBase
 {
   friend class AtomicRefArray<T,Algo>;
   
   typedef ArrayBase<T,AtomicRefArrayHeader,Algo> Base;
  
   struct RefAlgo
    {
     static void IncRef(AtomicRefArrayHeader *ptr) { ptr->incRef(); }
  
     static bool DecRef(AtomicRefArrayHeader *ptr) { return ptr->decRef(); }
  
     static void Destroy(AtomicRefArrayHeader *ptr) { Base::Destroy(ptr); }
    };
 
   // data
   
   RefPtr<AtomicRefArrayHeader,RefAlgo> ptr;
  
   // constructors
   
   AtomicRefArrayBase() 
    : ptr(&DefaultAtomicRefArrayHeader::DefaultObject)
    {
     ptr->incRef();
    }
   
   explicit AtomicRefArrayBase(RefPtr<AtomicRefArrayHeader,RefAlgo> &ptr_)
    : ptr(ObjToMove(ptr_))
    {
    }
  
   explicit AtomicRefArrayBase(ulen maxlen) 
    : ptr(Base::Create(maxlen))
    {
    }
  
   ~AtomicRefArrayBase() 
    {
    }
 };
  
/* class AtomicRefArray<T,Algo> */ 
  
template <class T,class Algo> 
class AtomicRefArray : AtomicRefArrayBase<T,Algo>
 {
   typedef typename AtomicRefArrayBase<T,Algo>::Base Base;
   
   using AtomicRefArrayBase<T,Algo>::ptr;
   
  private: 
  
   void unshare()
    {
     AtomicRefArray<T,Algo> temp(DoCopy(getLen(),getMaxLen()),getPtr());
     
     Swap(*this,temp);
    }
    
   ulen shrink_shared(ulen delta_len) 
    {
     ulen len=getLen();
     
     if( len<delta_len ) delta_len=len;
     
     if( delta_len==0 ) return 0;
     
     len-=delta_len;
    
     AtomicRefArray<T,Algo> temp(DoCopy(len,getMaxLen()),getPtr());
     
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
    
     AtomicRefArray<T,Algo> temp(DoCopy(getLen(),maxlen),getPtr());
     
     Swap(*this,temp);
    }
    
   AtomicRefArrayHeader * provide() // provides not default ptr with room for 1 elements
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
   
   AtomicRefArrayHeader * provide(ulen extra_len) // provides not default ptr with room for extra_len elements
    {
     if( ptr->isShared() )
       {
        provide_shared(extra_len);
       }
     else
       {
        ptr.update( [=] (AtomicRefArrayHeader *hptr) -> AtomicRefArrayHeader * { return Base::Provide(hptr,extra_len); } );
       }  
     
     return ptr.getPtr();
    } 
 
  public:
  
   // constructors
   
   AtomicRefArray() {}
   
   template <class S>
   explicit AtomicRefArray(std::initializer_list<S> il) 
    : AtomicRefArrayBase<T,Algo>(il.size())
    {
     Base::Extend_cast(ptr.getPtr(),il.size(),il.begin());
    }
   
   explicit AtomicRefArray(ulen len) 
    : AtomicRefArrayBase<T,Algo>(len)
    {
     Base::Extend_default(ptr.getPtr(),len);
    }
   
   AtomicRefArray(ulen len,ulen maxlen) 
    : AtomicRefArrayBase<T,Algo>(maxlen)
    {
     GuardLen(len,maxlen);
     
     Base::Extend_default(ptr.getPtr(),len);
    }
    
   AtomicRefArray(DoReserveType,ulen maxlen) 
    : AtomicRefArrayBase<T,Algo>(maxlen) 
    {
    }
    
   explicit AtomicRefArray(DoRaw dotype) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_raw(ptr.getPtr(),dotype.getLen());
    }
   
   template <class ... SS> 
   explicit AtomicRefArray(DoFill dotype,SS && ... ss) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_fill(ptr.getPtr(),dotype.getLen(), std::forward<SS>(ss)... );
    }
    
   AtomicRefArray(DoCopy dotype,const T src[]) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_copy(ptr.getPtr(),dotype.getLen(),src);
    }
 
   template <class S>
   AtomicRefArray(DoCast dotype,const S src[]) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_cast(ptr.getPtr(),dotype.getLen(),src);
    }
   
   AtomicRefArray(DoSwap dotype,T objs[]) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_swap(ptr.getPtr(),dotype.getLen(),objs);
    }
   
   template <class Creator> 
   AtomicRefArray(DoCreate dotype,Creator creator) 
    : AtomicRefArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend(ptr.getPtr(),dotype.getLen(),creator);
    }
    
   template <class Builder> 
   AtomicRefArray(DoBuildType,Builder builder) 
    : AtomicRefArrayBase<T,Algo>(builder.getLen())
    {
     Base::Extend(ptr.getPtr(),builder);
    }
    
   ~AtomicRefArray() {}
   
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
     
   void cloneTo(AtomicRefArray<T,Algo> &ret) const
    {
     AtomicRefArray<T,Algo> temp(DoCopy(getLen(),getMaxLen()),getPtr());
     
     Swap(ret,temp);
    }
    
   void reserve(ulen extra_len)
    {
     provide(extra_len);
    }
   
   void erase()
    {
     AtomicRefArray<T,Algo> temp;
     
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
     if( ptr->isShared() )
       {
        // cannot do anything, ignore
       }
     else
       {
        Base::Shrink_extra(ptr.getPtr());
       }
    } 
    
   void shrink_reserve(ulen maxlen)
    {
     if( ptr->isShared() )
       {
        // cannot do anything, ignore
       }
     else
       {
        Base::Shrink_reserve(ptr.getPtr(),maxlen);
       }
    }
    
   void shrink_reserve()
    {
     if( ptr->isShared() )
       {
        // cannot do anything, ignore
       }
     else
       {
        Base::Shrink_reserve(ptr.getPtr());
       }
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
   
   void objSwap(AtomicRefArray<T,Algo> &obj)
    {
     Swap(ptr,obj.ptr);
    }
   
   explicit AtomicRefArray(ToMoveCtor<AtomicRefArray<T,Algo> > obj)
    : AtomicRefArrayBase<T,Algo>(obj->ptr)
    {
    }
   
   AtomicRefArray<T,Algo> * objMove(Place<void> place)
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
 

