/* ArrayBase.h */ 
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

#ifndef CCore_inc_array_ArrayBase_h
#define CCore_inc_array_ArrayBase_h

#include <CCore/inc/array/ArrayAlgo.h>

#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* words */ 

enum DoBuildType { DoBuild };
 
enum DoReserveType { DoReserve };
 
/* classes */ 

template <int Sw> class DoSomething;

template <class T,class H,class Algo> struct ArrayBase;

/* class DoSomething<int Sw> */ 

template <int Sw>
class DoSomething
 {
   ulen len;
   ulen maxlen;
   
  public: 
  
   explicit DoSomething(ulen len_) : len(len_),maxlen(len_) {}
  
   DoSomething(ulen len_,ulen maxlen_) : len(len_),maxlen(maxlen_) { GuardLen(len_,maxlen_); }
   
   ulen getLen() const { return len; }
   
   ulen getMaxLen() const { return maxlen; }
 };
 
typedef DoSomething<1> DoRaw;

typedef DoSomething<2> DoFill; 

typedef DoSomething<3> DoCopy; 

typedef DoSomething<4> DoCast; 

typedef DoSomething<5> DoSwap; 

typedef DoSomething<6> DoCreate; 
 
/* struct ArrayBase<T,H,Algo> */ 
 
template <class T,class H,class Algo> 
struct ArrayBase
 {
  static_assert( std::is_pod<H>::value ,"CCore::ArrayBase<T,H,Algo> : H must be POD");
  
  // placement

  static const ulen Delta = Align(sizeof (H)) ;
 
  static T * GetPtr(H *ptr) { return PlaceAt(ptr)+Delta; }
  
  static T * GetSafePtr(H *ptr) 
   { 
    if( ptr->len ) return PlaceAt(ptr)+Delta; 
    
    return 0;
   }
  
  static Place<void> GetExtra(H *ptr) { return PlaceAt(ptr)+(Delta+ptr->len*sizeof (T)); }
  
  static ulen GetExtraLen(H *ptr) { return ptr->maxlen-ptr->len; }
  
  // basic
  
  static H * Alloc(ulen maxlen,ulen mem_len)
   {
    H *ret=PlaceAt(MemAlloc(mem_len)); // POD
    
    ret->init(maxlen);
    
    return ret;
   }
  
  static H * Alloc(ulen maxlen)
   {
    ulen mem_len=LenOf(maxlen,sizeof (T),Delta);
    
    return Alloc(maxlen,mem_len);
   }
  
  static void Free(H *ptr)
   {
    ptr->exit();
   
    MemFree(ptr); // POD
   }
 
  static H * Create(ulen maxlen)
   {
    if( !maxlen ) maxlen=1;
    
    return Alloc(maxlen);
   }
  
  static void Destroy(H *ptr)
   {
    if( ptr->maxlen )
      {
       Algo::Destroy(GetPtr(ptr),ptr->len);

       Free(ptr);
      }
   }
  
  static Place<void> MoveAndDestroy(H *ptr,Place<void> place)
   {
    if( ptr->maxlen )
      {
       ulen len=ptr->len;
       
       Algo::MoveTo(GetPtr(ptr),len,place);
       
       Free(ptr);
       
       return place+len*sizeof(T);
      }
    
    return place;
   }
  
  struct ProvideMove_move
   {
    static H * Do(H *ptr,ulen extra_len) // ptr is not default
     {
      ulen maxlen=Algo::ProvideLen(ptr->len,ptr->maxlen,extra_len);
    
      ulen mem_len=LenOf(maxlen,sizeof (T),Delta);
    
      if( MemExtend(ptr,mem_len) ) 
        {
         ptr->maxlen=maxlen;
      
         return ptr;
        }
    
      H *ret=Alloc(maxlen,mem_len);
       
      ulen len=ptr->len;
       
      Algo::MoveTo(GetPtr(ptr),len,PlaceAt(ret)+Delta);
       
      ret->len=len;
    
      Free(ptr);
    
      return ret;
     }
   };
 
  struct ProvideMove_no_move
   {
    static H * Do(H *ptr,ulen extra_len)
     {
      GuardArrayOverflow(ptr->len,ptr->maxlen,extra_len);

      return 0;
     }
   };
 
  typedef Meta::Select<Algo::MoveTo_exist, ProvideMove_move , ProvideMove_no_move > ProvideMove;
   
  static H * Provide_one(H *ptr) // provides not default ptr with room for 1 elements
   {
    if( GetExtraLen(ptr) ) return ptr;
    
    if( ptr->maxlen==0 ) return Create(1);
   
    return ProvideMove::Do(ptr,1);
   }
  
  static H * Provide(H *ptr,ulen extra_len) // provides not default ptr with room for extra_len elements
   {
    if( ptr->maxlen==0 ) return Create(extra_len);
   
    if( extra_len<=GetExtraLen(ptr) ) return ptr;
    
    return ProvideMove::Do(ptr,extra_len);
   }
  
  // shrink
  
  static ulen Shrink(H *ptr,ulen delta_len)
   {
    ulen len=ptr->len;
    
    if( delta_len>len ) delta_len=len;
    
    if( delta_len )
      {
       len-=delta_len;
      
       ptr->len=len;
      
       Algo::Destroy(GetPtr(ptr)+len,delta_len);
      }
      
    return delta_len;  
   }
  
  static bool Shrink_one(H *ptr)
   {
    if( ulen len=ptr->len )
      {
       len--;
       
       ptr->len=len;
      
       Algo::Destroy(GetPtr(ptr)+len);
       
       return true;
      }
      
    return false;  
   }
  
  static ulen Shrink_all(H *ptr)
   {
    ulen len=ptr->len;
    
    if( len )
      {
       ptr->len=0;
      
       Algo::Destroy(GetPtr(ptr),len);
      }
      
    return len;  
   }
  
  static void Shrink_extra(H *ptr)
   {
    ulen maxlen=ptr->len;
       
    if( !maxlen ) maxlen=1;
    
    if( maxlen<ptr->maxlen )
      {
       ptr->maxlen=maxlen;
      
       MemShrink(ptr,Delta+maxlen*sizeof (T));
      }
   }
  
  // extend : ptr is not default and has enough room for delta_len elements
  
  static PtrLen<T> Extend_raw(H *ptr,ulen delta_len)
   {
    PtrLen<T> ret=Algo::Create_raw(GetExtra(ptr),delta_len);
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  static PtrLen<T> Extend_default(H *ptr,ulen delta_len)
   {
    PtrLen<T> ret=Algo::Create_default(GetExtra(ptr),delta_len);
    
    ptr->len+=delta_len;
    
    return ret;
   }
   
  template <class ... SS>
  static PtrLen<T> Extend_fill(H *ptr,ulen delta_len,SS && ... ss)
   {
    PtrLen<T> ret=Algo::Create_fill(GetExtra(ptr),delta_len, std::forward<SS>(ss)... );
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  static PtrLen<T> Extend_copy(H *ptr,ulen delta_len,const T src[])
   {
    PtrLen<T> ret=Algo::Create_copy(GetExtra(ptr),delta_len,src);
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  template <class S>
  static PtrLen<T> Extend_cast(H *ptr,ulen delta_len,const S src[])
   {
    PtrLen<T> ret=Algo::Create_cast(GetExtra(ptr),delta_len,src);
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  static PtrLen<T> Extend_swap(H *ptr,ulen delta_len,T objs[])
   {
    PtrLen<T> ret=Algo::Create_swap(GetExtra(ptr),delta_len,objs);
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  template <class Creator>
  static PtrLen<T> Extend(H *ptr,ulen delta_len,Creator creator)
   {
    PtrLen<T> ret=Algo::Create(GetExtra(ptr),delta_len,creator);
    
    ptr->len+=delta_len;
    
    return ret;
   }
  
  template <class Builder>
  static PtrLen<T> Extend(H *ptr,Builder builder)
   {
    FunctorTypeOf<Builder> func(builder);
    
    PtrLen<T> ret=func(GetExtra(ptr));
    
    ptr->len+=ret.len;
    
    return ret;
   }
  
  // append : ptr is not default and has enough room for 1 element
  
  static T * Append_raw(H *ptr)
   {
    T *ret=new(GetExtra(ptr)) T;
    
    ptr->len++;
    
    return ret;
   }
  
  static T * Append_default(H *ptr)
   {
    T *ret=new(GetExtra(ptr)) T();
    
    ptr->len++;
    
    return ret;
   }
  
  template <class ... SS> 
  static T * Append_fill(H *ptr,SS && ... ss)
   {
    T *ret=new(GetExtra(ptr)) T( std::forward<SS>(ss)... );
    
    ptr->len++;
    
    return ret;
   }
  
  static T * Append_copy(H *ptr,const T &src)
   {
    T *ret=new(GetExtra(ptr)) T(src);
    
    ptr->len++;
    
    return ret;
   }
  
  static T * Append_swap(H *ptr,T &obj)
   {
    T *ret=Algo::Create_swap(GetExtra(ptr),obj);
    
    ptr->len++;
    
    return ret;
   }
   
  template <class Creator>
  static T * Append(H *ptr,Creator creator)
   {
    FunctorTypeOf<Creator> func(creator);
    
    T *ret=func(GetExtra(ptr));
    
    ptr->len++;
    
    return ret;
   }
 };
 
} // namespace CCore
 
#endif
 

