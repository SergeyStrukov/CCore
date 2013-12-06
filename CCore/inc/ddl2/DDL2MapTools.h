/* DDL2MapTools.h */ 
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

#ifndef CCore_inc_ddl2_DDL2MapTools_h
#define CCore_inc_ddl2_DDL2MapTools_h

#include <CCore/inc/ddl2/DDL2Eval.h>
 
namespace CCore {
namespace DDL2 {

/* functions */

void GuardMapTooDeep();

void GuardMapNameDuplication();

void GuardMapLenOverflow();

inline ulen MapAddLen(ulen a,ulen b) 
 {
  ulen ret=a+b;
  
  if( ret<a ) GuardMapLenOverflow();
  
  return ret;
 }

inline ulen MapMulLen(ulen a,ulen b)
 {
  if( a && b>ulen(-1)/a ) GuardMapLenOverflow();
  
  return a*b;
 }

/* classes */

class TypeComparer;

class NameKey;

/* class TypeComparer */

class TypeComparer
 {
   EvalResult *eval;
   unsigned level;
   
   struct CmpRet;
   struct CmpFunc;
   
  public: 
   
   TypeComparer(EvalResult *eval_,unsigned level_) : eval(eval_),level(level_) {}
   
   CmpResult operator () (TypeNode *a,TypeNode *b);
   
   CmpResult operator () (LenNode &a,LenNode &b) { return Cmp(eval->getLen(a),eval->getLen(b)); }
 };

/* class NameKey */

class NameKey : CmpComparable<NameKey>
 {
   StrLen name;
   ScopeNode *parent;
   uint32 hash;
   
  private: 
  
   struct Cur;
  
   Cur getCur() const;
  
   void setHash();
  
  public:
  
   // constructors
  
   NameKey() : parent(0),hash(0) {}
  
   template <class T>
   explicit NameKey(T *node) : name(node->name.getStr()),parent(node->parent) { setHash(); }
  
   explicit NameKey(const StrLen &name_) : name(name_),parent(0) { setHash(); }
  
   // cmp objects 
  
   CmpResult objCmp(const NameKey &obj) const;
 };

} // namespace DDL2
} // namespace CCore
 
#endif
 

