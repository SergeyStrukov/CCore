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

#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Abort.h>
 
namespace CCore {

/* class ObjectDomain */

void * ObjectDomain::alloc(ulen len)
 {
  return MemAlloc(len);
 }

void ObjectDomain::free(void *mem)
 {
  MemFree(mem);
 }

bool ObjectDomain::enableAlloc(ulen len)
 {
  if( len>getAvail() ) collect();
  
  return len<=getAvail();
 }

void ObjectDomain::add(ObjBase *obj)
 {
  ulen index=list.getLen();
  
  list.append_fill(obj);
  
  obj->index=index;
  
  total_len+=obj->len;
 }

ObjectDomain::ObjectDomain(ulen max_total_len_)
 : total_len(0),
   max_total_len(max_total_len_)
 {
 }

ObjectDomain::~ObjectDomain()
 {
  collect();
  
  if( getObjectCount() )
    {
     Abort("Fatal error: object domain leak");
    }
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
      
     cur->keepAlive(this);
    } 
  
  // destroy >=preserved
  
  ulen delta=len-preserved;
  
  for(auto r=Range(base+preserved,delta); +r ;++r) 
    {
     ObjBase *obj=r->obj;
     
     total_len-=obj->len;
     
     obj->destroy(this);
    }
  
  list.shrink(delta);
  list.shrink_reserve();  
 }

} // namespace CCore
 

