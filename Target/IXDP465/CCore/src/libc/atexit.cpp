/* atexit.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
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

#include <CCore/inc/libc/atexit.h>

#include <CCore/inc/SpecialMemBase.h>
#include <CCore/inc/Task.h>
 
namespace CCore {

/* init/exit functions */ 

namespace Private_atexit {

/* struct Func */ 

struct Func
 {
  struct Ext
   {
    __cxa_atexit_t func;
    void *arg;
    void *dso;
   };
   
  __std_atexit_t func;
  Ext ext;
 
  static Func Create(__std_atexit_t func)
   {
    Func ret;
    
    ret.func=func;
    
    ret.ext.func=0;
    ret.ext.arg=0;
    ret.ext.dso=0;
    
    return ret;
   }
   
  static Func Create(__cxa_atexit_t func,void *arg,void *dso)
   {
    Func ret;
    
    ret.func=0;
    
    ret.ext.func=func;
    ret.ext.arg=arg;
    ret.ext.dso=dso;
    
    return ret;
   }
 
  void operator () ()
   {
    if( func )
      {
       func();
      }
    else
      {
       ext.func(ext.arg);
      }
   }
 };

/* struct FuncBlock */ 
 
const ulen FuncBlockSize = 128 ;

struct FuncBlock
 {
  FuncBlock *prev;
  ulen count;
  Func block[FuncBlockSize];
  
  void set(FuncBlock *prev_,const Func &func)
   {
    prev=prev_;
    count=1;
    block[0]=func;
   }
  
  bool push(const Func &func)
   {
    if( count<FuncBlockSize )
      {
       block[count++]=func;
       
       return true;
      }
      
    return false;  
   } 
   
  bool pop(Func &ret)
   {
    if( count ) 
      {
       ret=block[--count];
       
       return true;
      }
    
    return false;
   } 
   
  static FuncBlock First;
  static FuncBlock * Last; 
  
  static bool Push(const Func &func);
  static bool Pop(Func &ret);
 };
 
FuncBlock FuncBlock::First=
 {
  0,
  0,
  {}
 };

FuncBlock * FuncBlock::Last=&First; 

bool FuncBlock::Push(const Func &func)
 {
  if( Last->push(func) ) return true;

  if( void *mem=TryMemAlloc_int(sizeof (FuncBlock)) )
    {
     FuncBlock *ptr=static_cast<FuncBlock *>(mem);
     
     ptr->set(Last,func);
     
     Last=ptr;
     
     return true;
    }
    
  return false;  
 }
 
bool FuncBlock::Pop(Func &ret)
 {
  FuncBlock *ptr=Last;
  
  if( ptr->pop(ret) ) return true;
    
  if( FuncBlock *prev=ptr->prev )  
    {
     Last=prev;
     
     MemFree_int(ptr);
     
     return prev->pop(ret);
    }
    
  return false;  
 }
 
} // namespace Private_atexit
 
using namespace Private_atexit; 
 
/* init/exit functions */ 

void Exit_atexit()
 {
  for(Func func; FuncBlock::Pop(func) ;) func();
 }
 
} // namespace CCore
 
using namespace CCore;
 
/* atexit() */  
 
int atexit(__std_atexit_t func)
 {
  if( !func ) 
    {
     errno=EBADARG;
    
     return -1; 
    }
  
  Dev::IntLock lock;
    
  return FuncBlock::Push(Func::Create(func))?0:1 ;
 }
 
int __cxa_atexit(__cxa_atexit_t func,void *arg,void *dso)
 {
  if( !func ) 
    {
     errno=EBADARG;
    
     return -1; 
    }
    
  Dev::IntLock lock;
  
  return FuncBlock::Push(Func::Create(func,arg,dso))?0:1 ;
 }
 
