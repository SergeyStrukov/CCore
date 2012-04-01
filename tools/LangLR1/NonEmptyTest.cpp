/* NonEmptyTest.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "NonEmptyTest.h"

namespace App {

/* class NonEmptyTest */

auto NonEmptyTest::mul(MulRec rec) const -> Type
 {
  Type ret=rec.first;

  for(auto p=getMul(rec); +p ;++p) ret=ret*flag[*p];
   
  return ret; 
 }

auto NonEmptyTest::step(NIndex nt) -> SetResult
 {
  auto p=getStep(step_list[nt]);
  
  Type result;
  
  if( !p ) 
    {
     result=Type(Empty);
    }
  else
    {
     result=mul(*p);
     
     for(++p; +p ;++p) result=result+mul(*p);
    }
  
  return flag[nt].set(result);
 }

auto NonEmptyTest::buildMul(PtrLen<const NTIndex> str) -> MulRec
 {
  ulen off=mul_pool.getLen();
  bool good=false;
  
  ulen ext_len=str.len;
  
  NIndex *buf=mul_pool.extend_raw(ext_len).ptr;
  NIndex *out=buf;

  for(; +str ;++str)
    if( str->isNIndex() )
      {
       *(out++)=str->getNIndex();
      }
    else
      {
       good=true;
      }
  
  ulen len=Dist(buf,out);
  
  mul_pool.shrink(ext_len-len);
  
  return MulRec(off,len,good);
 }

OffLen NonEmptyTest::buildStep(NIndex nt)
 {
  ulen off=step_pool.getLen();
  
  auto p=lang.getRules(nt);
  
  ulen len=p.len;
  
  MulRec *out=step_pool.extend_default(len).ptr;
  
  for(; +p ;++p,++out) *out=buildMul(p->str);
  
  return OffLen(off,len);
 }

NonEmptyTest::NonEmptyTest(const Lang &lang_)
 : lang(lang_), 
   flag(lang.getNIndexLim()),
   list(lang.getNIndexLim()),
   list_len(0),
   step_list(lang.getNIndexLim())
 {
  for(auto p=lang.getNRange(); +p ;++p) 
    {
     list[list_len++]=*p;
     
     step_list[*p]=buildStep(*p);
    }
 }

NonEmptyTest::~NonEmptyTest()
 {
 }

bool NonEmptyTest::step()
 {
  bool ret=false;

  for(ulen i=list_len; i-- ;)
    switch( step(list[i]) )
      {
       case ChangeToMax :
        {
         list_len--;

         if( i<list_len ) list[i]=list[list_len];
        }

       case Change : ret=true;
      }

  return ret;
 }

} // namespace App
