/* stdlib.cpp */ 
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

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <CCore/inc/SpecialMemBase.h>

using namespace CCore;

/* malloc() */ 

void * malloc(size_t size)
 {
  void *ret=TryMemAlloc(size);
  
  if( !ret ) errno=ENOMEM;
  
  return ret;
 }
 
void * calloc(size_t elem_count,size_t elem_size)
 {
  if( elem_size!=0 && elem_count>size_t(-1)/elem_size ) 
    {
     errno=ENOMEM;
     
     return 0;
    }
 
  size_t s=elem_count*elem_size;
 
  void *ret=malloc(s);
  
  if( ret ) memset(ret,0,s);
  
  return ret;
 }
 
void * realloc(void *mem,size_t size)
 {
  if( !mem ) return malloc(size);
  
  if( MemShrink(mem,size) ) return mem;
  
  if( MemExtend(mem,size) ) return mem;
    
  void *ret=malloc(size);
  
  if( !ret ) return 0;
  
  memcpy(ret,mem,MemLen(mem));
  
  MemFree(mem);
  
  return ret;
 }
 
void free(void *mem)
 {
  MemFree(mem);
 }
 
/* malloc_int() */ 

void * malloc_int(size_t size)
 {
  return TryMemAlloc_int(size);
 }
 
void free_int(void *mem)
 {
  MemFree_int(mem);
 }
 
