/* MergeSort.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sort_MergeSort_h
#define CCore_inc_sort_MergeSort_h

#include <CCore/inc/sort/QuickSort.h>

#include <CCore/inc/MemBase.h> 
 
namespace CCore {

/* classes */ 

template <class Ran,class Ctx=SortCtx<Ran> > struct MergeSort;

/* struct MergeSort<Ran,Ctx> */

template <class Ran,class Ctx>
struct MergeSort
 {
  static const ulen MedLen = 1000 ;
  
  template <class Len>
  static void Permutate(Ran a,Len len,Ctx ctx,Len temp[]);
  
  template <class Len>
  static void Merge(Ran a,Len len,Len len1,Ctx ctx,Len temp[]); // len1 > 0 , len2 > 0
  
  template <class Len>
  static void SubSort(Ran a,Len len,Ctx ctx,Len temp[]);
  
  template <class Len>
  static void Sort(Ran a,Len len,Ctx ctx,Len temp[]); // len >= 2
  
  template <class Len>
  static void DoMedSort(Ran a,Len len,Ctx ctx); // len >= 2
  
  template <class Len>
  static bool MedSort(Ran a,Len len,Ctx ctx);
  
  template <class Len>
  static bool MedSort(Ran a,Len len) { return MedSort(a,len,Ctx()); }
  
  
  template <class Len>
  static void Sort(Ran a,Len len,Ctx ctx);
  
  template <class Len>
  static void Sort(Ran a,Len len) { Sort(a,len,Ctx()); }
 };

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::Permutate(Ran a,Len len,Ctx ctx,Len temp[])
 {
  Len *inv=temp+len;
  
  for(Len i=0; i<len ;i++)
    {
     inv[temp[i]]=i;
    }
  
  for(Len i=0; i<len ;i++)
    {
     Len j=temp[i];
     
     if( j!=i )
       {
        ctx.swap(a+i,a+j);
        
        Len k=inv[i];
        
        temp[k]=j;
        inv[j]=k;
       }
    }
 }

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::Merge(Ran a,Len len,Len len1,Ctx ctx,Len temp[])
 {
  Len i=0;
  Len j=len1;
  
  Len *dst=temp;
  
  for(;;)
    {
     if( ctx.less(a+j,a+i) )
       {
        *(dst++)=j++;
        
        if( j>=len ) 
          {
           while( i<len1 ) *(dst++)=i++;
          
           break;
          }
       }
     else
       {
        *(dst++)=i++;
        
        if( i>=len1 ) 
          {
           while( j<len ) *(dst++)=j++; 
          
           break;
          }
       }
    }
  
  Permutate(a,len,ctx,temp);
 }

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::SubSort(Ran a,Len len,Ctx ctx,Len temp[])
 {
  if( ShortSort<Ran,Ctx>::Sort(a,len,ctx) ) return;
  
  Sort(a,len,ctx,temp);
 }

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::Sort(Ran a,Len len,Ctx ctx,Len temp[])
 {
  Len len1=len/2;
  Len len2=len-len1;
  
  SubSort(a,len1,ctx,temp);
  SubSort(a+len1,len2,ctx,temp); // temp+2*len1
  
  Merge(a,len,len1,ctx,temp);
 }

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::DoMedSort(Ran a,Len len,Ctx ctx)
 {
  Len temp[2*MedLen];
  
  Sort(a,len,ctx,temp);
 }

template <class Ran,class Ctx>
template <class Len>
bool MergeSort<Ran,Ctx>::MedSort(Ran a,Len len,Ctx ctx)
 {
  if( ShortSort<Ran,Ctx>::Sort(a,len,ctx) ) return true;
  
  if( len<=MedLen )
    {
     DoMedSort(a,len,ctx);
    
     return true;
    }
   
  return false; 
 }

template <class Ran,class Ctx>
template <class Len>
void MergeSort<Ran,Ctx>::Sort(Ran a,Len len,Ctx ctx)
 {
  if( ShortSort<Ran,Ctx>::Sort(a,len,ctx) ) return;
  
  if( len<=MedLen )
    {
     DoMedSort(a,len,ctx);
    
     return;
    }
  
  struct TempGuard
   {
    Len *temp;
    
    explicit TempGuard(Len len) 
     {
      if( len<=MaxULen/(2*sizeof (Len)) )
        {
         ulen alloc_len=2*ulen(len)*sizeof (Len);
         
         temp=static_cast<Len *>(TryMemAlloc(alloc_len));
        }
      else
        {
         temp=0;
        }
     }
    
    ~TempGuard() 
     {
      if( temp ) MemFree(temp);
     }
   };
  
  TempGuard guard(len);
  
  if( guard.temp )
    {
     Sort(a,len,ctx,guard.temp);
    }
  else
    {
     QuickSort<Ran,Ctx>::Sort(a,len,ctx);
    }
 }

} // namespace CCore
 
#endif

