/* DDL2TypeSet.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
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

#ifndef CCore_inc_ddl2_DDL2TypeSet_h
#define CCore_inc_ddl2_DDL2TypeSet_h

#include <CCore/inc/ddl2/DDL2TypedMap.h>
 
namespace CCore {
namespace DDL2 {

/* HasName() */

inline bool HasNames(ScopeNode *) { return true; }

template <class ... TT>
bool HasNames(ScopeNode *scope_node,StrLen name,TT ... scope)
 {
  if( StrCmp(scope_node->name.getStr(),name) ) return false;
  
  return HasNames(scope_node->parent,scope...);
 }

template <class Node,class ... TT>
bool HasName(Node *node,StrLen name,TT ... scope)
 {
  if( StrCmp(node->name.getStr(),name) ) return false;
  
  if( node->depth!=Meta::TypeListLen<TT...>::Ret ) return false;
  
  return HasNames(node->parent,scope...);
 }

/* SetFieldOffsets() */

inline void SetFieldOffsets(FieldNode *field_node)
 {
  if( field_node ) GuardBadStructure();
 }

template <class ... TT>
void SetFieldOffsets(FieldNode *field_node,StrLen name,ulen offset,TT ... args)
 {
  if( !field_node ) GuardBadStructure();
  
  if( StrCmp(field_node->name.getStr(),name) ) GuardBadStructure();
  
  field_node->index=offset;
  
  SetFieldOffsets(field_node->next,args...);
 }

template <class ... TT>
void SetFieldOffsets(StructNode *struct_node,TT ... args)
 {
  SetFieldOffsets(struct_node->field_list.beg,args...);
 }

/* classes */

template <class ... TT> struct GuardFieldTypes;

class FindNodeMap;

/* struct GuardFieldTypes<TT> */

template <> 
struct GuardFieldTypes<>
 {
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &,FieldNode *field_node) 
   {
    if( field_node ) GuardBadStructure();
   }
  
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &,StructNode *struct_node) 
   {
    if( struct_node->field_list.beg ) GuardBadStructure();
   }
 };

template <class T,class ... TT> 
struct GuardFieldTypes<T,TT...>
 {
  template <class TypeSet>
  GuardFieldTypes(const TypeSet &type_set,FieldNode *field_node)
   {
    if( !field_node ) GuardBadStructure();
    
    if( !MapTypeCheck<T>::Match(type_set,field_node->type_node) ) GuardBadStructure();
    
    GuardFieldTypes<TT...>(type_set,field_node->next);
   }

  template <class TypeSet>
  GuardFieldTypes(const TypeSet &type_set,StructNode *struct_node)
   : GuardFieldTypes(type_set,struct_node->field_list.beg) 
   {
   }
 };

/* class FindNodeMap */

class FindNodeMap : NoCopy
 {
   struct CrcGen;
 
   struct ToSearch
    {
     uint32 crc;
     ulen len;
     StrLen name;
     DDL2::ScopeNode *scope;
     
     void setCrc();
     
     template <class T>
     explicit ToSearch(T *node)
      {
       len=node->depth+1;
       name=node->name.getStr();
       scope=node->parent;
       
       setCrc();
      }
    };
 
   struct Rec : NoCopy , CmpComparable<Rec> , NoThrowFlagsBase
    {
     ulen ind;
     DynArray<StrLen> names;
     uint32 crc;
     
     void setCrc();
     
     template <class ... TT>
     explicit Rec(ulen ind_,TT ... tt) : ind(ind_),names({tt...}) { setCrc(); }
     
     // cmp objects 
     
     CmpResult objCmp(const Rec &obj) const;
     
     CmpResult objCmp(const ToSearch &obj) const;
     
     bool operator >= (const ToSearch &ts) const { return objCmp(ts)>=0; }
     
     bool operator == (const ToSearch &ts) const { return objCmp(ts)==0; }
     
     // swap/move objects
     
     void objSwap(Rec &obj)
      {
       Swap(ind,obj.ind);
       Swap(names,obj.names);
       Swap(crc,obj.crc);
      }
     
     explicit Rec(ToMoveCtor<Rec> obj)
      : ind(obj->ind),
        names(ObjToMove(obj->names)),
        crc(obj->crc)
      {
      }

     Rec * objMove(Place<void> place)
      {
       return CtorMove(this,place);
      }
    };
   
   DynArray<Rec> list; 
 
  private: 
   
   ulen find(ToSearch ts);
   
  public:
 
   FindNodeMap() : list(DoReserve,100) {}
   
   ~FindNodeMap() {}

   template <class ... TT>
   void add(ulen ind,TT ... tt) { list.append_fill(ind,tt...); }
   
   void complete();
   
   template <class T>
   ulen find(T *node) { return find(ToSearch(node)); }
 };

} // namespace DDL2
} // namespace CCore
 
#endif
 

