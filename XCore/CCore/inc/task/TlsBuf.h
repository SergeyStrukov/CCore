/* TlsBuf.h */ 
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

#ifndef CCore_inc_task_TlsBuf_h
#define CCore_inc_task_TlsBuf_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/List.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_TlsBuf();

/* consts */ 

const ulen TlsLen = 128 ;

/* classes */ 

class TlsBuf;

/* class TlsBuf */ 

class TlsBuf : NoCopy
 {
   typedef void * Item;
   
   Item buf[TlsLen];
   
   DLink<TlsBuf> link;
   
  public:
  
   TlsBuf();
   
   ~TlsBuf();
   
   Item & operator [] (ulen index) { return buf[index]; }
   
   struct AllocResult
    {
     ulen index;
     bool ok;
     
     AllocResult(NothingType) : index(0),ok(false) {}
     
     AllocResult(ulen index_) : index(index_),ok(true) {}
    };
   
   class Host;
   
   static AllocResult Alloc() noexcept;
   
   static void Free(ulen index) noexcept;
 };
 
} // namespace CCore
 
#endif
 

