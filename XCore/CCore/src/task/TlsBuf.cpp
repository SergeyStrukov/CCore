/* TlsBuf.cpp */ 
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
 
#include <CCore/inc/task/TlsBuf.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class TlsBuf::Host */ 

class TlsBuf::Host : NoCopy
 {
   DLink<TlsBuf>::LinearAlgo<&TlsBuf::link>::Top top;
   
   bool flags[TlsLen];
   
   struct Rec
    {
     SLink<Rec> link;
    };
    
   Rec recs[TlsLen]; 
   
   SLink<Rec>::LinearAlgo<&Rec::link>::Top rec_top; 
 
  public:
  
   Host() 
    : flags()
    {
     for(auto r=Range(recs); +r ;++r) rec_top.ins(r.ptr);
    }
   
   ~Host()
    {
    }
   
   void add(TlsBuf *obj)
    {
     top.ins(obj);
    }
   
   void del(TlsBuf *obj)
    {
     top.del(obj);
    }
   
   AllocResult alloc()
    {
     if( Rec *rec=rec_top.del() )
       {
        ulen index=Dist(recs,rec);
        
        flags[index]=true;
        
        for(auto cur=top.start(); +cur ;++cur) (*cur)[index]=0;
        
        return index;
       }  
     else
       {
        return Nothing;
       }
    }
   
   void free(ulen index)
    {
     if( index>=TlsLen ) Abort("Fatal error : bad TLS index");
     
     if( !flags[index] ) Abort("Fatal error : TLS index is free");
     
     flags[index]=false;
     
     rec_top.ins(recs+index);
    }
    
   static const char * GetTag() { return "TlsBuf"; } 
 };
 
/* GetPlanInitNode_...() */ 

namespace Private_TlsBuf {

PlanInitObject<TlsBuf::Host> Object CCORE_INITPRI_1 ;

} // namespace Private_TlsBuf
 
using namespace Private_TlsBuf; 
 
PlanInitNode * GetPlanInitNode_TlsBuf() { return &Object; }
 
/* class TlsBuf */ 

TlsBuf::TlsBuf() 
 : buf() 
 {
  Dev::IntLock lock;
 
  Object->add(this);
 }
   
TlsBuf::~TlsBuf() 
 {
  Dev::IntLock lock;
 
  Object->del(this);
 }
   
auto TlsBuf::Alloc() noexcept -> AllocResult
 {
  Dev::IntLock lock;
 
  return Object->alloc();
 }
 
void TlsBuf::Free(ulen index) noexcept
 {
  Dev::IntLock lock;
 
  Object->free(index);
 }
 
} // namespace CCore
 

