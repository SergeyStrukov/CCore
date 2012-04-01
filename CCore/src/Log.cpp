/* Log.cpp */ 
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
 
#include <CCore/inc/Log.h>

#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* class LogMem */  
 
void LogMem::init(void *mem_,ulen mem_len,bool free_mem_)
 {
  mem=CastPtr(mem_);
  mem_lim=mem+mem_len;
  free_mem=free_mem_;
  
  clear();
 }
   
 // constructors

LogMem::LogMem(ulen mem_len)
 {
  init(MemAlloc(mem_len),mem_len,true);
 }
   
LogMem::LogMem(Space space)
 {
  init(space.mem,space.len,false);
 }
   
LogMem::~LogMem()
 {
  if( free_mem ) MemFree(mem);
 }
   
 // methods

void LogMem::clear()
 {
  ptr=mem;
  lim=mem;
  cut=mem_lim;  
 }
   
void * LogMem::alloc(ulen len)
 {
  if( !TryAlign(len) ) return 0;
  
  if( ptr<lim )
    {
     ulen s=Dist(lim,mem_lim);
     
     if( len<=s )
       {
        void *ret=lim;
        
        lim+=len;
        
        return ret;
       }
       
     s=Dist(mem,ptr);  
     
     if( len<s )
       {
        cut=lim;
        lim=mem+len;
        
        return mem;
       }
       
     return 0;  
    }
    
  if( ptr>lim )  
    {
     ulen s=Dist(lim,ptr);
     
     if( len<s )
       {
        void *ret=lim;
        
        lim+=len;
        
        return ret;
       }
       
     return 0;  
    }
    
  ulen s=Dist(lim,mem_lim);
     
  if( len<s )
    {
     void *ret=lim;
        
     lim+=len;
        
     return ret;
    }
       
  return 0;  
 }
   
void LogMem::free(void *ret)
 {
  lim=CastPtr(ret);
  
  if( lim==mem && lim!=ptr )
    {
     lim=cut;
     cut=mem_lim;
    } 
 }
   
void LogMem::del(void *beg)
 {
  if( ptr<lim )
    {
     ptr=CastPtr(beg);
  
     if( ptr==lim )
       {
        ptr=mem;
        lim=mem;
       }
    }
  else
    {
     ptr=CastPtr(beg);

     if( ptr==cut )
       {
        ptr=mem;
        cut=mem_lim;
       }
    }  
 }
 
} // namespace CCore
 

