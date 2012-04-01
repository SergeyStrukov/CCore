/* CDef.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_libc_CDef_h
#define CCore_inc_libc_CDef_h

#include <CCore/inc/libc/CBase.h>

namespace LibC_Internal {

/* functions */ 

template <class T>
inline T Min(T a,T b) { return (a<b)?a:b; }
 
inline void * PtrAdd(void *ptr,Size s)
 {
  return static_cast<char *>(ptr)+s;
 }       
          
inline void * PtrSub(void *ptr,Size s)
 {
  return static_cast<char *>(ptr)-s;
 }       
    
inline const void * PtrAdd(const void *ptr,Size s)
 {
  return static_cast<const char *>(ptr)+s;
 }       
          
inline const void * PtrSub(const void *ptr,Size s)
 {
  return static_cast<const char *>(ptr)-s;
 }       
    
inline int DecValue(char ch)
 {
  if( ch>='0' && ch<='9' ) return ch-'0';
  
  return -1;
 }
 
inline int OctValue(char ch)
 {
  if( ch>='0' && ch<='7' ) return ch-'0';
  
  return -1;
 }
 
inline int HexValue(char ch)
 {
  if( ch>='0' && ch<='9' ) return ch-'0';
  
  switch( ch )
    {
     case 'a' : case'A' : return 10;
     case 'b' : case'B' : return 11;
     case 'c' : case'C' : return 12;
     case 'd' : case'D' : return 13;
     case 'e' : case'E' : return 14;
     case 'f' : case'F' : return 15;
    }
  
  return -1;
 }
 
/* classes */ 

struct AutoCast;

struct Link;

struct ParseSize;

/* struct AutoCast */ 

struct AutoCast
 {
  void *ptr;
  
  AutoCast(void *ptr_) : ptr(ptr_) {}
  
  template <class T>
  operator T * () const { return static_cast<T *>(ptr); }
 };
 
/* struct Link */  
 
struct Link
 {
  Link *prev;
  Link *next;   
  
  void empty()
   {
    prev=this;
    next=this;
   }
   
  bool isEmpty() const { return next==this; }
   
  void ins(Link *a,Link *b,Link *c) 
   {
    b->prev=a;
    b->next=c;
    
    a->next=b;
    c->prev=b;
   }
     
  void insBefore(Link *link) 
   {
    ins(prev,link,this);
   }
      
  void insAfter(Link *link) 
   {
    ins(this,link,next);
   }
   
  void del(Link *a,Link *b) 
   {
    a->next=b;
    b->prev=a;
   }
      
  void del()
   {
    del(prev,next);
   }
 };
 
/* struct ParseSize */ 

struct ParseSize
 {
  Size value;
  const char *str;
  
  explicit ParseSize(const char *str);
 };
  
} // namespace LibC_Internal
 
#endif



