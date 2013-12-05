/* DDL2MapTools.cpp */ 
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
 
#include <CCore/inc/ddl2/DDL2MapTools.h>
 
#include <CCore/inc/Exception.h>
#include <CCore/inc/Sort.h>

namespace CCore {
namespace DDL2 {

/* functions */

void GuardMapTooDeep()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : too deep");
 }

void GuardMapNameDuplication()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : const name duplication");
 }

void GuardMapStructNameDuplication()
 {
  Printf(Exception,"CCore::DDL2::Map : struct name duplication");
 }

void GuardMapLenOverflow()
 {
  Printf(Exception,"CCore::DDL2::(Typed)Map : len overflow");
 }

/* class TypeComparer */

struct TypeComparer::CmpRet
 {
  CmpResult result;
  
  CmpRet() : result(CmpEqual) {}
  
  CmpRet(unsigned a,unsigned b) : result(Cmp(a,b)) {}
  
  CmpRet(CmpResult result_) : result(result_) {}
 };

struct TypeComparer::CmpFunc
 {
  TypeComparer cmp;
  
  CmpFunc(EvalResult *eval,unsigned level) : cmp(eval,level) {}
  
  CmpRet operator () (TypeNode::Base *a,TypeNode::Base *b) 
   { 
    return Cmp(a->type,b->type); 
   } 
  
  CmpRet operator () (TypeNode::Ptr *a,TypeNode::Ptr *b) 
   { 
    return cmp(a->type_node,b->type_node); 
   }
  
  struct Rec
   {
    TypeNode *type;
    unsigned flag;
    
    void set(TypeNode *type_,unsigned flag_)
     {
      type=type_;
      flag=flag_;
     }
   };
  
  static Rec * Fill(Rec *out,TypeList *type_list,unsigned flag)
   {
    for(TypeListNode &node : *type_list )
      {
       out->set(node.type_node,flag);
       
       ++out;
      }
    
    return out;
   }
  
  CmpResult finish(PtrLen<Rec> range)
   {
    while( +range )
      {
       TypeNode *type=range->type;
       unsigned flags=range->flag;
       
       ++range;
       
       for(; +range && !cmp(type,range->type) ;++range) flags|=range->flag;
       
       switch( flags )
         {
          case 1 : return CmpGreater;
          case 2 : return CmpLess;
         }
      }
    
    return CmpEqual;
   }
  
  CmpRet operator () (TypeNode::PolyPtr *a,TypeNode::PolyPtr *b) 
   {
    ulen count=LenAdd(a->type_list->count,b->type_list->count);
    
    TempArray<Rec,100> buf(count);
    
    auto range=Range(buf.getPtr(),count);
    
    Fill(Fill(range.ptr,a->type_list,1),b->type_list,2);
    
    IncrSort(range, [=] (const Rec &a,const Rec &b) { return cmp(a.type,b.type)<0; } );
    
    return finish(range);
   }
  
  CmpRet operator () (TypeNode::Array *a,TypeNode::Array *b) 
   { 
    return cmp(a->type_node,b->type_node); 
   } 
  
  CmpRet operator () (TypeNode::ArrayLen *a,TypeNode::ArrayLen *b) 
   { 
    if( CmpResult ret=cmp(a->type_node,b->type_node) ) return ret;
    
    return cmp(a->len_node,b->len_node);
   } 
  
  CmpRet operator () (StructNode *a,StructNode *b)
   {
    return Cmp(a->index,b->index);
   }
 };

CmpResult TypeComparer::operator () (TypeNode *a,TypeNode *b)
 {
  if( !level ) GuardMapTooDeep();
  
  return TypeAdapter::Binary<CmpRet>(a,b,CmpFunc(eval,level-1)).result;
 }

} // namespace DDL2
} // namespace CCore
 

