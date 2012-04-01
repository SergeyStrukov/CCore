/* ArrayAlgo.h */ 
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

#ifndef CCore_inc_array_ArrayAlgo_h
#define CCore_inc_array_ArrayAlgo_h
 
#include <CCore/inc/Move.h>
#include <CCore/inc/Tuple.h>

namespace CCore {

/* functions */ 

void GuardArrayOverflow(ulen len,ulen maxlen,ulen extra_len);

/* classes */ 

struct ProbeSet_Default_no_throw;

struct ProbeSet_Copy_no_throw;

template <class T> struct NoThrowFlags;

template <class T,bool no_throw> struct Creator_default;

template <class T,class ... SS> struct Creator_fill;

template <class T,bool no_throw> struct Creator_copy;

template <class T,class S> struct Creator_cast;

template <class T,class Algo> struct Creator_swap;

template <class T> struct ArrayAlgoBase;

template <class T> struct ArrayAlgoBase_nodtor;

template <class T,class Flags=NoThrowFlags<T> > struct ArrayAlgo_mini;

template <class T> struct ArrayAlgo_pod;

template <class T,class Flags=NoThrowFlags<T> > struct ArrayAlgo_class;

struct ProbeSet_ArrayAlgoType;

template <class T> struct Has_ArrayAlgoType;
 
template <bool has_ArrayAlgoType,bool is_pod,class T,class Flags> struct ArrayAlgos;

template <class T,class Flags=NoThrowFlags<T> > struct ArrayAlgo;

/* struct ProbeSet_Default_no_throw */

struct ProbeSet_Default_no_throw
 {
  template <bool> struct Host;

  template <class T>
  static constexpr bool Probe(...) { return Meta::HasNoThrowDefault<T>::Ret; }

  template <class T>
  static constexpr bool Probe(Host<T::Default_no_throw> *) { return T::Default_no_throw; }
 };

/* struct ProbeSet_Copy_no_throw */

struct ProbeSet_Copy_no_throw
 {
  template <bool> struct Host;

  template <class T>
  static constexpr bool Probe(...) { return Meta::HasNoThrowCopy<T>::Ret; }

  template <class T>
  static constexpr bool Probe(Host<T::Copy_no_throw> *) { return T::Copy_no_throw; }
 };

/* struct NoThrowFlags<T> */

template <class T> 
struct NoThrowFlags
 {
  enum NoThrowFlagType
   {
    Default_no_throw = ProbeSet_Default_no_throw::Probe<T>(0),
    Copy_no_throw = ProbeSet_Copy_no_throw::Probe<T>(0)
   };
  
  // warning
  
  template <class S> struct NutDefault;
  template <class S> struct NutCopy;
  
  enum NotUsedType
   {
    NotUsed = Meta::Warning< NutDefault<T> , !Default_no_throw >::NotUsed() + 
              Meta::Warning< NutCopy<T> , !Copy_no_throw >::NotUsed()
   };
 };

/* struct Creator_default<T,bool no_throw> */ 
 
template <class T,bool no_throw> 
struct Creator_default
 {
  enum NoThrowFlagType { NoThrow = no_throw };
  
  Creator_default() {}
  
  T * operator () (Place<void> place) noexcept( EnableNoExcept && no_throw )
   {
    return new(place) T();
   }
 };
 
/* struct Creator_fill<T,SS> */ 

template <class T,class ... SS> 
struct Creator_fill
 {
  enum NoThrowFlagType { NoThrow = false };
  
  ForwardTuple<SS...> ss;
  
  explicit Creator_fill(SS && ... ss_) : ss( std::forward<SS>(ss_)... ) {}
  
  T * operator () (Place<void> place)
   {
    T *ret;
      
    ss.call( [&ret,place] (SS && ... ss) { ret=new(place) T( std::forward<SS>(ss)... ); } );
      
    return ret;
   }
 };
 
/* struct Creator_copy<T,bool no_throw> */ 

template <class T,bool no_throw> 
struct Creator_copy
 {
  enum NoThrowFlagType { NoThrow = no_throw };
  
  const T *src;
  
  explicit Creator_copy(const T *src_) : src(src_) {}
  
  T * operator () (Place<void> place) noexcept( EnableNoExcept && no_throw )
   {
    return new(place) T(*(src++));
   }
 };
 
/* struct Creator_cast<T,S> */ 
 
template <class T,class S> 
struct Creator_cast
 {
  enum NoThrowFlagType { NoThrow = false };
  
  const S *src;
  
  explicit Creator_cast(const S *src_) : src(src_) {}
  
  T * operator () (Place<void> place)
   {
    return new(place) T(*(src++));
   }
 };
 
/* struct Creator_swap<T,Algo> */ 

template <class T,class Algo> 
struct Creator_swap
 {
  enum NoThrowFlagType { NoThrow = true };
  
  T *objs;
  
  explicit Creator_swap(T *objs_) : objs(objs_) {}
  
  T * operator () (Place<void> place) noexcept(EnableNoExcept)
   {
    return Algo::Create_swap(place,*(objs++));
   }
 };

/* struct ArrayAlgoBase<T> */

template <class T> 
struct ArrayAlgoBase
 {
  //
  //  assume ~T() no-throw
  //
  
  //
  //  Create() : clean on throw
  //
  
  class BuildGuard : NoCopy
   {
     Place<void> place;
     T *ptr;
     ulen len;
     
    public:
     
     explicit BuildGuard(Place<void> place_) : place(place_),ptr(place_),len(0) {}
     
     ~BuildGuard() { if( len ) Destroy(ptr,len); }
     
     Place<void> at() const { return place; }
     
     void operator ++ () { place+=sizeof (T); len++; }
     
     PtrLen<T> disarm() { return Range(ptr,Replace_null(len)); }
   };
 
  class CreateGuard : public BuildGuard
   {
    public:
     
     CreateGuard(Place<void> place,ulen /*final_len*/) : BuildGuard(place) {}
     
     ~CreateGuard() {}
   };
 
  class CreateGuard_nothrow : NoCopy
   {
     Place<void> place;
     T *ptr;
     ulen final_len;
     
    public:
     
     CreateGuard_nothrow(Place<void> place_,ulen final_len_) : place(place_),ptr(place_),final_len(final_len_) {}
     
     Place<void> at() const { return place; }
     
     void operator ++ () { place+=sizeof (T); }
     
     PtrLen<T> disarm() { return Range(ptr,final_len); }
   };
  
  template <bool no_throw,class Base = Meta::Select<no_throw, CreateGuard_nothrow , CreateGuard > >
  class CreateGuardNoThrow : public Base 
   {
    public:
     
     CreateGuardNoThrow(Place<void> place,ulen final_len) : Base(place,final_len) {}
    
     ~CreateGuardNoThrow() {}
   };
  
  template <class Creator>
  static PtrLen<T> Create(Place<void> place,ulen len,Creator creator)
   {
    CreateGuardNoThrow<Creator::NoThrow> guard(place,len);
    
    FunctorTypeOf<Creator> func(creator);
    
    for(; len ;len--,++guard) func(guard.at());
    
    return guard.disarm();
   }
  
  //
  //  single Destroy() : no-throw
  // 
  
  static void Destroy(T *ptr) noexcept(EnableNoExcept)
   {
    ptr->~T();
   }
  
  // 
  //  Destroy() : no-throw
  //
  
  static void Destroy(T *ptr,ulen len) noexcept(EnableNoExcept)
   {
    for(; len ;len--,ptr++) Destroy(ptr);
   }
 };

/* struct ArrayAlgoBase_nodtor<T> */

template <class T> 
struct ArrayAlgoBase_nodtor
 {
  //
  //  assume ~T() is trivial
  //
  
  //
  //  Create()
  //
 
  class BuildGuard : NoCopy
   {
     Place<void> place;
     T *ptr;
     ulen len;
     
    public:
     
     explicit BuildGuard(Place<void> place_) : place(place_),ptr(place_),len(0) {}
     
     Place<void> at() const { return place; }
     
     void operator ++ () { place+=sizeof (T); len++; }
     
     PtrLen<T> disarm() { return Range(ptr,len); }
   };
  
  class CreateGuard : NoCopy
   {
     Place<void> place;
     T *ptr;
     ulen final_len;
     
    public:
     
     CreateGuard(Place<void> place_,ulen final_len_) : place(place_),ptr(place_),final_len(final_len_) {}
     
     Place<void> at() const { return place; }
     
     void operator ++ () { place+=sizeof (T); }
     
     PtrLen<T> disarm() { return Range(ptr,final_len); }
   };
  
  typedef CreateGuard CreateGuard_nothrow;
  
  template <bool no_throw>
  class CreateGuardNoThrow : public CreateGuard 
   {
    public:
     
     CreateGuardNoThrow(Place<void> place,ulen final_len) : CreateGuard(place,final_len) {}
    
     ~CreateGuardNoThrow() {}
   };
  
  template <class Creator>
  static PtrLen<T> Create(Place<void> place,ulen len,Creator creator)
   {
    PtrLen<T> ret(place,len);
    
    FunctorTypeOf<Creator> func(creator);
    
    for(; len ;len--,place+=sizeof (T)) func(place);

    return ret;
   }
  
  //
  //  single Destroy() : empty
  // 
  
  static void Destroy(T *)
   {
   }
  
  // 
  //  Destroy() : empty
  //
  
  static void Destroy(T *,ulen)
   {
   }
 };

/* type ArrayAlgoBase_class<T> */

template <class T> 
using ArrayAlgoBase_class = Meta::Select< Meta::HasNoDtor<T>::Ret , ArrayAlgoBase_nodtor<T> , ArrayAlgoBase<T> > ;

/* struct ArrayAlgo_mini<T,Flags> */ 

template <class T,class Flags> 
struct ArrayAlgo_mini : ArrayAlgoBase<T>
 {
  //
  //  assume ~T() no-throw
  //
 
  using ArrayAlgoBase<T>::Create;
 
  //
  //  Create...() : clean on throw
  //
 
  enum PropFlagType
   {
    Default_no_throw = Flags::Default_no_throw,
    Copy_no_throw = Flags::Copy_no_throw,
    
    MoveTo_exist = false
   };
 
  static PtrLen<T> Create_raw(Place<void> place,ulen len)
   {
    return Create(place,len,Creator_default<T,Default_no_throw>());
   }
  
  static PtrLen<T> Create_default(Place<void> place,ulen len)
   {
    return Create(place,len,Creator_default<T,Default_no_throw>());
   }
   
  template <class ... SS> 
  static PtrLen<T> Create_fill(Place<void> place,ulen len,SS && ... ss)
   {
    return Create(place,len,Creator_fill<T,SS...>( std::forward<SS>(ss)... ));
   }
  
  static PtrLen<T> Create_copy(Place<void> place,ulen len,const T src[])
   {
    return Create(place,len,Creator_copy<T,Copy_no_throw>(src));
   }
  
  template <class S>
  static PtrLen<T> Create_cast(Place<void> place,ulen len,const S src[])
   {
    return Create(place,len,Creator_cast<T,S>(src));
   }
 };
 
/* struct ArrayAlgo_pod<T> */ 

template <class T> 
struct ArrayAlgo_pod : ArrayAlgoBase_nodtor<T>
 {
  using ArrayAlgoBase_nodtor<T>::Create;
  
  //
  //  Create...()
  //
 
  enum PropFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true,
    
    MoveTo_exist = true
   };
 
  static PtrLen<T> Create_raw(Place<void> place,ulen len)
   {
    PtrLen<T> ret(place,len);
    
    return ret;
   }
  
  static PtrLen<T> Create_default(Place<void> place,ulen len)
   {
    PtrLen<T> ret(place,len);
    
    ret.set_null();

    return ret;
   }
   
  template <class ... SS> 
  static PtrLen<T> Create_fill(Place<void> place,ulen len,SS && ... ss)
   {
    return Create(place,len,Creator_fill<T,SS...>( std::forward<SS>(ss)... ));
   }
  
  static PtrLen<T> Create_copy(Place<void> place,ulen len,const T src[])
   {
    PtrLen<T> ret(place,len);
    
    ret.copy(src);

    return ret;
   }
  
  template <class S>
  static PtrLen<T> Create_cast(Place<void> place,ulen len,const S src[])
   {
    return Create(place,len,Creator_cast<T,S>(src));
   }
  
  static PtrLen<T> Create_swap(Place<void> place,ulen len,T objs[])
   {
    PtrLen<T> ret(place,len);
    
    ret.copy(objs);
    
    Range(objs,len).set_null(); // may be excessive 

    return ret;
   }
   
  //
  //  Single : no-throw
  // 
  
  static T * Create_swap(Place<void> place,T &obj)
   {
    T *ret=new(place) T(obj);
    
    obj=T(); // may be excessive
    
    return ret;
   }
   
  //
  //  ProvideLen() : double extension
  // 
  
  static ulen ProvideLen(ulen len,ulen maxlen,ulen extra_len)
   {
    return Max<ulen>(LenAdd(len,extra_len),2*maxlen);
   }
   
  // 
  //  MoveTo() : no-throw
  //
  
  static PtrLen<T> MoveTo(T *ptr,ulen len,Place<void> place) noexcept(EnableNoExcept)
   {
    PtrLen<T> ret(place,len);
    
    ret.copy(ptr);
    
    return ret;
   }
 };
 
/* struct ArrayAlgo_class<T,Flags> */ 

template <class T,class Flags> 
struct ArrayAlgo_class : ArrayAlgoBase_class<T>
 {
  //
  //  assume ~T() , Move(T *,Place<void>) , Swap(T &,T &) no-throw
  //
 
  using ArrayAlgoBase_class<T>::Create;
  
  //
  //  Create...() : clean on throw
  //
  
  enum PropFlagType
   {
    Default_no_throw = Flags::Default_no_throw,
    Copy_no_throw = Flags::Copy_no_throw,
    
    MoveTo_exist = true
   };
 
  static PtrLen<T> Create_raw(Place<void> place,ulen len)
   {
    return Create(place,len,Creator_default<T,Default_no_throw>());
   }
  
  static PtrLen<T> Create_default(Place<void> place,ulen len)
   {
    return Create(place,len,Creator_default<T,Default_no_throw>());
   }
   
  template <class ... SS> 
  static PtrLen<T> Create_fill(Place<void> place,ulen len,SS && ... ss)
   {
    return Create(place,len,Creator_fill<T,SS...>( std::forward<SS>(ss)... ));
   }
  
  static PtrLen<T> Create_copy(Place<void> place,ulen len,const T src[])
   {
    return Create(place,len,Creator_copy<T,Copy_no_throw>(src));
   }
  
  template <class S>
  static PtrLen<T> Create_cast(Place<void> place,ulen len,const S src[])
   {
    return Create(place,len,Creator_cast<T,S>(src));
   }
  
  static PtrLen<T> Create_swap(Place<void> place,ulen len,T objs[])
   {
    return Create(place,len,Creator_swap<T,ArrayAlgo_class<T> >(objs));
   }
   
  //
  //  Single
  // 
  
  static T * Create_swap(Place<void> place,T &obj) noexcept(EnableNoExcept)
   {
    T *ret=new(place) T();
    
    Swap(*ret,obj);
    
    return ret;
   }
   
  //
  //  ProvideLen() : double extension
  // 
  
  static ulen ProvideLen(ulen len,ulen maxlen,ulen extra_len)
   {
    return Max<ulen>(LenAdd(len,extra_len),2*maxlen);
   }
   
  // 
  //  MoveTo() : no-throw
  //

  static PtrLen<T> MoveTo(T *ptr,ulen len,Place<void> place) noexcept(EnableNoExcept)
   {
    PtrLen<T> ret(place,len);
    
    for(; len ;len--,ptr++,place+=sizeof (T)) Move(ptr,place);
    
    return ret;
   }
 };
 
/* struct ProbeSet_ArrayAlgoType */

struct ProbeSet_ArrayAlgoType
 {
  template <class T> struct Host;
  
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<typename T::ArrayAlgoType> *) { return true; }
 };

/* struct Has_ArrayAlgoType<T> */ 

template <class T> 
struct Has_ArrayAlgoType : Meta::Has<T,ProbeSet_ArrayAlgoType> {};
 
/* struct ArrayAlgos<bool has_ArrayAlgoType,bool is_pod,T,Flags> */ 

template <bool is_pod,class T,class Flags> 
struct ArrayAlgos<true,is_pod,T,Flags> : T::ArrayAlgoType {};
 
template <class T,class Flags> 
struct ArrayAlgos<false,true,T,Flags> : ArrayAlgo_pod<T> {};
 
template <class T,class Flags> 
struct ArrayAlgos<false,false,T,Flags> : ArrayAlgo_class<T,Flags> {};
 
/* struct ArrayAlgo<T,Flags> */ 
 
template <class T,class Flags> 
struct ArrayAlgo : ArrayAlgos<Has_ArrayAlgoType<T>::Ret,std::is_pod<T>::value,T,Flags> {};
 
} // namespace CCore
 
#endif
 

