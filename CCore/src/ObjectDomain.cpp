/* ObjectDomain.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/ObjectDomain.h>

#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class ObjectDomain */

void * ObjectDomain::alloc(ulen len)
 {
  if( len>getAvail() ) collect();
  
  if( len>getAvail() ) GuardNoMem(len);
  
  if( void *ret=try_alloc(len) ) 
    {
     total_len+=len;
    
     return ret;
    }
  
  collect();
  
  void *ret=try_alloc(len);
  
  if( !ret ) GuardNoMem(len);
  
  total_len+=len;
  
  return ret;
 }

void ObjectDomain::free(void *mem,ulen len)
 {
  total_len-=len;
  
  free(mem);
 }

void * ObjectDomain::try_alloc(ulen len)
 {
  return TryMemAlloc(len);
 }

void ObjectDomain::free(void *mem)
 {
  MemFree(mem);
 }

void ObjectDomain::add(ObjBase *obj)
 {
  if( addlock_flag )
    {
     Abort("Fatal error: object domain addlock");
    }
  
  ulen index=list.getLen();
  
  list.append_fill(obj);
  
  obj->index=index;
 }

void ObjectDomain::cleanup()
 {
  if( Replace_null(cleanup_flag) )
    {
     collect();
    
     if( getObjectCount() )
       {
        Abort("Fatal error: object domain leak");
       }
    }
 }

ObjectDomain::ObjectDomain(ulen max_total_len_)
 : total_len(0),
   max_total_len(max_total_len_),
   cleanup_flag(true),
   addlock_flag(false)
 {
 }

ObjectDomain::~ObjectDomain()
 {
  cleanup();
 }

 // collect

void ObjectDomain::swap(ulen index1,ulen index2)
 {
  ObjRec *base=list.getPtr();
  
  ObjBase *obj1=base[index1].obj;
  ObjBase *obj2=base[index2].obj;
  
  base[index1].obj=obj2;
  base[index2].obj=obj1;
  
  obj2->index=index1;
  obj1->index=index2;
 }

void ObjectDomain::markAlive(ObjBase *obj)
 {
  if( obj )
    {
     ulen index=obj->index;
     
     if( index>=preserved )
       {
        if( index!=preserved )
          {
           swap(preserved,index);
          }
        
        preserved++;
       }
    }
 }

void ObjectDomain::collect()
 {
  ObjRec *base=list.getPtr();
  ulen len=list.getLen();
  
  ulen init_preserved=0;
  
  for(ulen index=0; index<len ;index++)
    {
     ObjBase *cur=base[index].obj;
    
     if( cur->ref_count )
       {
        if( index!=init_preserved )
          {
           swap(index,init_preserved);
          }
        
        init_preserved++;
       }
    }
  
  preserved=init_preserved;
  
  for(ulen index=0; index<preserved ;index++)
    {    
     ObjBase *cur=base[index].obj;
      
     cur->keepAlive(this); // may increase preserved
    }
  
  for(ulen index=0,lim=preserved; index<lim ;index++)
    {
     ObjBase *cur=base[index].obj;
     
     cur->breakWeak(lim);
    }
  
  // destroy >=preserved
  
  addlock_flag=true;
  
  ulen delta=len-preserved;
  
  for(auto r=Range(base+preserved,delta); +r ;++r) 
    {
     ObjBase *obj=r->obj;
     
     obj->destroy(this);
    }
  
  list.shrink(delta);
  list.shrink_reserve();
  
  addlock_flag=false;
 }

} // namespace CCore
 

