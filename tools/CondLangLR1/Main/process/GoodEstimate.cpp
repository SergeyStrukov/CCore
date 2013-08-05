/* GoodEstimate.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "GoodEstimate.h"

namespace App {

/* class GoodTest */

auto GoodTest::mul(MulRec rec) const -> Type
 {
  Type ret=rec.first;

  for(auto p=getMul(rec); +p ;++p) ret=ret*flags[*p];
   
  return ret; 
 }

auto GoodTest::step(ulen synt_index) -> SetResult
 {
  auto p=getStep(step_list[synt_index]);
  
  Type result;
  
  if( !p ) 
    {
     result=Empty;
    }
  else
    {
     result=mul(*p);
     
     for(++p; +p ;++p) result=result+mul(*p);
    }
  
  return flags[synt_index].set(result);
 }

auto GoodTest::buildMul(PtrLen<const LangBase::Element> args) -> MulRec
 {
  ulen off=mul_pool.getLen();
  bool good=false;
  
  ulen ext_len=args.len;
  
  ulen *buf=mul_pool.extend_raw(ext_len).ptr;
  ulen *out=buf;
  
  ulen delta=lang.getAtomCount();

  for(; +args ;++args)
    if( args->index>=delta )
      {
       *(out++)=args->index-delta;
      }
    else
      {
       good=true;
      }
  
  ulen len=Dist(buf,out);
  
  mul_pool.shrink(ext_len-len);
  
  return MulRec(off,len,good);
 }

OffLen GoodTest::buildStep(const LangBase::Synt &synt)
 {
  ulen off=step_pool.getLen();
  
  auto p=synt.rules;
  
  ulen len=p.len;
  
  MulRec *out=step_pool.extend_default(len).ptr;
  
  for(; +p ;++p,++out) *out=buildMul(p->args);
  
  return OffLen(off,len);
 }

GoodTest::GoodTest(const LangClassBase &lang_)
 : lang(lang_), 
   flags(lang.getSyntCount()),
   list(lang.getSyntCount()),
   list_len(0),
   mul_pool(DoReserve,128),
   step_pool(DoReserve,128),
   step_list(lang.getSyntCount())
 {
  for(auto synts=lang.getSynts(); +synts ;++synts) 
    {
     list[list_len++]=synts->index;
     
     step_list[synts->index]=buildStep(*synts);
    }
 }

GoodTest::~GoodTest()
 {
 }

bool GoodTest::step()
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
