/* ShortSort.h */ 
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

#ifndef CCore_inc_sort_ShortSort_h
#define CCore_inc_sort_ShortSort_h

#include <CCore/inc/Swap.h>
 
namespace CCore {

/* classes */ 

template <class Ran> struct SortCtx;

template <class T> struct SortIndexCtx;

template <class Ran,class Ctx=SortCtx<Ran> > struct ShortSort;

/* struct SortCtx<Ran> */ 

template <class Ran> 
struct SortCtx
 {
  static void swap(Ran a,Ran b) { Swap(*a,*b); }
   
  static bool less(Ran a,Ran b) { return *a < *b ; }
 };
 
/* struct SortIndexCtx<T> */ 

template <class T> 
struct SortIndexCtx
 {
  T *base;
  
  SortIndexCtx(T *base_) : base(base_) {}
  
  template <class Ind>
  static void swap(Ind *a,Ind *b) { Swap(*a,*b); }
  
  template <class Ind>
  bool less(const Ind *a,const Ind *b) const { return base[*a] < base[*b] ; }
 };
 
/* struct ShortSort<Ran,Ctx> */ 

template <class Ran,class Ctx> 
struct ShortSort
 {
  // general
 
  static void Sort2(Ran a,Ran b,Ctx ctx);
  
  static void Sort3(Ran a,Ran b,Ran c,Ctx ctx);
  
  static void Sort4(Ran a,Ran b,Ran c,Ran d,Ctx ctx);
  
  static void Sort5(Ran a,Ran b,Ran c,Ran d,Ran e,Ctx ctx);
  
  // array
 
  static void Sort2(Ran a,Ctx ctx) { Sort2(a,a+1,ctx); }
  
  static void Sort3(Ran a,Ctx ctx) { Sort3(a,a+1,a+2,ctx); }
  
  static void Sort4(Ran a,Ctx ctx) { Sort4(a,a+1,a+2,a+3,ctx); }
  
  static void Sort5(Ran a,Ctx ctx) { Sort5(a,a+1,a+2,a+3,a+4,ctx); }
  
  // default
  
  static void Sort2(Ran a) { Sort2(a,Ctx()); }
  
  static void Sort3(Ran a) { Sort3(a,Ctx()); }
  
  static void Sort4(Ran a) { Sort4(a,Ctx()); }
  
  static void Sort5(Ran a) { Sort5(a,Ctx()); }
  
  // combined

  template <class Len>
  static bool Sort(Ran a,Len len,Ctx ctx)
   {
    switch( len )
      {
       case 2 : Sort2(a,ctx); return true;
       case 3 : Sort3(a,ctx); return true;
       case 4 : Sort4(a,ctx); return true;
       case 5 : Sort5(a,ctx); return true;
       
       default: return (len<2);
      }
   }
   
  template <class Len>
  static bool Sort(Ran a,Len len)
   {
    switch( len )
      {
       case 2 : Sort2(a); return true;
       case 3 : Sort3(a); return true;
       case 4 : Sort4(a); return true;
       case 5 : Sort5(a); return true;
       
       default: return (len<2);
      }
   }
 };
 
template <class Ran,class Ctx> 
void ShortSort<Ran,Ctx>::Sort2(Ran a,Ran b,Ctx ctx)
 {
  Used(ctx);
  
  if( ctx.less(b,a) ) ctx.swap(b,a);
 }
  
template <class Ran,class Ctx> 
void ShortSort<Ran,Ctx>::Sort3(Ran a,Ran b,Ran c,Ctx ctx)
 {
  Used(ctx);
  
  if( ctx.less(b,a) )
    {
     if( ctx.less(c,b) )
       {
        ctx.swap(c,a);
       }
     else
       {
        ctx.swap(a,b);
        
        if( ctx.less(c,b) ) ctx.swap(c,b);
       }
    }
  else
    {
     if( ctx.less(c,b) )
       {
        ctx.swap(c,b);
        
        if( ctx.less(b,a) ) ctx.swap(b,a);
       }
    }
 }
  
template <class Ran,class Ctx> 
void ShortSort<Ran,Ctx>::Sort4(Ran a,Ran b,Ran c,Ran d,Ctx ctx)
 {
  Used(ctx);
  
  if( ctx.less(b,a) ) ctx.swap(b,a);
  
  if( ctx.less(d,c) ) ctx.swap(d,c);
  
  if( ctx.less(d,b) )
    {
     ctx.swap(d,b);
     
     if( ctx.less(c,a) )
       {
        ctx.swap(c,a);
        
        if( ctx.less(c,b) ) ctx.swap(c,b);
       }
     else
       {
        ctx.swap(b,c);
       }
    }
  else
    {
     if( ctx.less(c,b) )
       {
        ctx.swap(c,b);
        
        if( ctx.less(b,a) ) ctx.swap(b,a);
       }
    }
 }
  
template <class Ran,class Ctx> 
void ShortSort<Ran,Ctx>::Sort5(Ran a,Ran b,Ran c,Ran d,Ran e,Ctx ctx)
 {
  Used(ctx);
  
  if( ctx.less(b,a) ) ctx.swap(b,a);
  
  if( ctx.less(d,c) ) ctx.swap(d,c);

  if( ctx.less(d,b) )
    {
     if( ctx.less(e,d) )
       {
        ctx.swap(e,b);
        
        if( ctx.less(c,b) ) ctx.swap(c,b);
       }
     else
       {
        if( ctx.less(e,b) )
          {
           ctx.swap(e,b);
           ctx.swap(b,d);
           ctx.swap(b,c);
          }
        else
          {
           ctx.swap(b,d);
           ctx.swap(b,c);
           
           if( ctx.less(b,a) )
             {
              ctx.swap(b,a);
              
              if( ctx.less(c,b) ) ctx.swap(c,b);
             }
           
           return;
          }
       }
     
     if( ctx.less(a,c) )  
       {
        if( ctx.less(b,a) ) ctx.swap(b,a);
       }
     else
       {
        if( ctx.less(d,a) )
          {
           ctx.swap(a,d);
           ctx.swap(a,c);
           ctx.swap(a,b);
          }
        else
          {
           ctx.swap(a,c);
           ctx.swap(a,b);
          }
       }
    }
  else
    {
     if( ctx.less(e,b) )
       {
        ctx.swap(e,d);
        
        if( ctx.less(d,a) )
          {
           ctx.swap(d,a);
           ctx.swap(d,b);
          }
        else
          {
           ctx.swap(b,d);
          }
       }
     else
       {
        if( ctx.less(e,d) )
          {
           ctx.swap(e,d);
          }
        else
          {
           if( ctx.less(c,b) )
             {
              ctx.swap(c,b);
              
              if( ctx.less(b,a) ) ctx.swap(b,a);
             }
             
           return;
          }
       }
       
     if( ctx.less(c,b) )  
       {
        ctx.swap(c,b);
        
        if( ctx.less(b,a) ) ctx.swap(b,a);
       }
     else
       {
        if( ctx.less(d,c) ) ctx.swap(d,c);
       }
    }
 }
  
} // namespace CCore
 
#endif
 

