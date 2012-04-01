/* QuickSort.h */ 
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

#ifndef CCore_inc_sort_QuickSort_h
#define CCore_inc_sort_QuickSort_h

#include <CCore/inc/sort/HeapSort.h>
 
namespace CCore {

/* classes */ 

template <class Ran,class Ctx=SortCtx<Ran> > struct QuickSort;

/* struct QuickSort<Ran,Ctx> */ 

template <class Ran,class Ctx>
struct QuickSort
 {
  static Ran PartitionP(Ran a,Ran b,Ran p,Ctx ctx); // a <= b , p outside [a,b]
 
  static Ran PartitionA(Ran a,Ran b,Ctx ctx);       // a < b
  
  static Ran PartitionB(Ran a,Ran b,Ctx ctx);       // a < b
  
  static Ran Partition(Ran a,Ran b,Ran c,Ctx ctx);  // a < b < c
  
  template <class Len>
  static void Sort(Ran a,Len len,Ctx ctx);
  
  template <class Len>
  static void Sort(Ran a,Len len) { Sort(a,len,Ctx()); }
 };
 
template <class Ran,class Ctx>
Ran QuickSort<Ran,Ctx>::PartitionP(Ran a,Ran b,Ran p,Ctx ctx)
 {
  Used(ctx);
  
  while( a < b )
    {
     while( !ctx.less(p,a) )
       {
        ++a;
      
        if( a == b ) return a;
       }
     
     while( !ctx.less(b,p) )  
       {
        --b;
      
        if( a == b ) return a;
       }
       
     ctx.swap(a,b);  
     
     ++a;
     --b;
    }
    
  return a;  
 }
 
template <class Ran,class Ctx>
Ran QuickSort<Ran,Ctx>::PartitionA(Ran a,Ran b,Ctx ctx)
 {
  Ran p=PartitionP(a+1,b,a,ctx);
  
  if( ctx.less(a,p) )
    {
     --p;
     
     if( a < p ) ctx.swap(a,p);
    }
  else
    {
     ctx.swap(a,p);
    }
    
  return p;
 }
  
template <class Ran,class Ctx>
Ran QuickSort<Ran,Ctx>::PartitionB(Ran a,Ran b,Ctx ctx)
 {
  Ran p=PartitionP(a,b-1,b,ctx);
 
  if( ctx.less(p,b) )
    {
     ++p;
     
     if( p < b ) ctx.swap(b,p);
    }
  else
    {
     ctx.swap(b,p);
    }
    
  return p;    
 }
 
template <class Ran,class Ctx>
Ran QuickSort<Ran,Ctx>::Partition(Ran a,Ran b,Ran c,Ctx ctx)
 {
  if( ctx.less(a,b) )
    {
     if( ctx.less(c,b) )
       {
        if( ctx.less(a,c) )
          return PartitionB(a,c,ctx);
        else
          return PartitionA(a,c,ctx);
       }
    }
  else
    {
     if( ctx.less(b,c) )
       {
        if( ctx.less(a,c) )
          return PartitionA(a,c,ctx);
        else
          return PartitionB(a,c,ctx);
       }
    }
  
  for(;;)
    {
     while( !ctx.less(b,a) )
       {
        ++a;
      
        if( a == b ) return PartitionA(a,c,ctx);
       }
     
     while( !ctx.less(c,b) )  
       {
        --c;
      
        if( b == c ) return PartitionB(a,c,ctx);
       }
     
     ctx.swap(a,c);  
   
     ++a;
     --c;
   
     if( a == b )
       {
        if( b == c )
          return b;
        else
          return PartitionA(a,c,ctx);
       }
     else
       {
        if( b == c )
          return PartitionB(a,c,ctx);
       }
    }
 }
  
template <class Ran,class Ctx>
template <class Len>
void QuickSort<Ran,Ctx>::Sort(Ran a,Len len,Ctx ctx)
 {
  Len S=len;
 
  while( !ShortSort<Ran,Ctx>::Sort(a,len,ctx) )
    {
     Len D=len/16;
     
     if( D<S )
       {
        S-=D;
       }
     else
       {
        HeapSort<Ran,Ctx>::Sort(a,len,ctx);
        
        return;
       }
    
     Ran p=Partition(a,a+(len/2),a+(len-1),ctx);
     
     Len len1=Len(p-a);
     Len len2=Len(len-1-len1);
     
     if( len1<=len2 )
       {
        Sort(a,len1,ctx);
        
        a=p+1;
        len=len2;
       }
     else
       {
        Sort(p+1,len2,ctx);
        
        len=len1;
       }
    }
 }
 
} // namespace CCore
 
#endif
 

