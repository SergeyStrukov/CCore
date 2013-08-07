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
  auto muls=getStep(step_list[synt_index]);
  
  Type result;
  
  if( !muls ) 
    {
     result=Empty;
    }
  else
    {
     result=mul(*muls);
     
     for(++muls; +muls ;++muls) result=result+mul(*muls);
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
  
  for(; +args ;++args)
    args->apply( [&] (const LangBase::AtomDesc *) { good=true; } , 
                 [&] (const LangBase::SyntDesc *synt) { *(out++)=synt->index; } );
  
  ulen len=Dist(buf,out);
  
  mul_pool.shrink(ext_len-len);
  
  return MulRec(off,len,good);
 }

OffLen GoodTest::buildStep(const LangBase::SyntDesc &synt)
 {
  ulen off=step_pool.getLen();
  
  auto rules=synt.rules;
  
  ulen len=rules.len;
  
  MulRec *out=step_pool.extend_default(len).ptr;
  
  for(; +rules ;++rules,++out) *out=buildMul(rules->args);
  
  return OffLen(off,len);
 }

GoodTest::GoodTest(const Lang &lang_)
 : lang(lang_), 
   flags(lang.getSyntCount()),
   list(lang.getSyntCount()),
   list_len(0),
   mul_pool(DoReserve,1024),
   step_pool(DoReserve,1024),
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
