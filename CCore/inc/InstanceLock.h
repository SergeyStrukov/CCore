/* InstanceLock.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_InstanceLock_h
#define CCore_inc_InstanceLock_h

#include <CCore/inc/task/Atomic.h>
 
namespace CCore {

/* functions */

void GuardInstanceLockTaken(StrLen name);

/* classes */

template <class T,ulen Count=1> class InstanceLock;

/* class InstanceLock<T,ulen Count> */

template <class T,ulen Count> 
class InstanceLock : NoCopy
 {
   ulen index;
   
  private: 
   
   static Sys::Atomic Lock[Count];
   
  public:
 
   explicit InstanceLock(StrLen name,ulen index_=0) // index<Count
    : index(index_)
    {
     GuardIndex(index_,Count);
    
     auto lock=Lock[index_]++;
     
     if( lock )
       {
        Lock[index_]--;
        
        GuardInstanceLockTaken(name);
       }
    }
   
   ~InstanceLock()
    {
     Lock[index]--;
    }
   
   ulen getInstanceIndex() const { return index; }
 };

template <class T,ulen Count> 
Sys::Atomic InstanceLock<T,Count>::Lock[Count]={};
   
} // namespace CCore
 
#endif
 

