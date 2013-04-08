/* Optional.h */ 
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

#ifndef CCore_inc_Optional_h
#define CCore_inc_Optional_h

#include <CCore/inc/Tree.h>
#include <CCore/inc/MemBase.h>

namespace CCore {

/* classes */

class Optional;

/* class Optional */

class Optional : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     TreeLink<Node,unsigned> link;
     
     virtual ~Node() {}
    };
   
   typedef TreeLink<Node,unsigned>::RadixAlgo<&Node::link> Algo;
   
   template <class T>
   struct ObjNode : Node
    {
     T obj;
     
     ObjNode() : obj{} {}
     
     virtual ~ObjNode() {}
    };
   
   Algo::Root root;
   unsigned max_slot;
   
  private: 
  
   template <class T>
   static T * GetObject(Node *node);
   
   static void Destroy(Node *node); 
   
  public:
 
   explicit Optional(unsigned max_slot_) : max_slot(max_slot_) {}
   
   ~Optional() { Destroy(root.root); }
   
   template <unsigned slot,class T>
   T * try_take();
   
   template <unsigned slot,class T>
   T * take();
 };

template <class T>
T * Optional::GetObject(Node *node)
 {
  return &(static_cast<ObjNode<T> *>(node)->obj);
 }

template <unsigned slot,class T>
T * Optional::try_take()
 {
  if( Node *node=root.find(slot) ) return GetObject<T>(node);
  
  return 0;
 }

template <unsigned slot,class T>
T * Optional::take()
 {
  Algo::PrepareIns prepare(root,slot,0,max_slot);
  
  if( prepare.found ) return GetObject<T>(prepare.found);
  
  ObjNode<T> *node=new ObjNode<T>();
  
  prepare.complete(node);
  
  return GetObject<T>(node);
 }

} // namespace CCore
 
#endif
 

