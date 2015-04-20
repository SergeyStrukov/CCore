/* Partition.h */ 
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

#ifndef CCore_inc_algon_Partition_h
#define CCore_inc_algon_Partition_h

#include <CCore/inc/Swap.h>
 
namespace CCore {
namespace Algon {

/* Partition() */

template <class Ran,class Pred>
Ran Partition(Ran ptr,ulen len,Pred pred) // reorder such that pred(Range(ptr,len)) is 1,1,...,0,0,...
 {
  if( len==0 ) return ptr;
  
  Ran a=ptr;
  Ran b=ptr+(len-1);
  
  while( a<b )
    {
     while( pred(*a) ) 
       {
        a++;
        
        if( a==b ) return pred(*a)?a+1:a;
       }
     
     while( !pred(*b) ) 
       {
        b--;
        
        if( a==b ) return a;
       }
     
     Swap(*a,*b);
     
     a++;
     b--;
    }

  if( b<a ) return a;
  
  return pred(*a)?a+1:a;
 }

template <class T,class Pred>
ulen Partition(PtrLen<T> r,Pred pred)
 {
  return Dist(r.ptr,Partition(r.ptr,r.len,pred));
 }

} // namespace Algon
} // namespace CCore
 
#endif
 

