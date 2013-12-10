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

} // namespace DDL2
} // namespace CCore
 
#endif
 

