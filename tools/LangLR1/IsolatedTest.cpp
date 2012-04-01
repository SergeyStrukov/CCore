/* IsolatedTest.cpp */
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

#include "IsolatedTest.h"

namespace App {

/* class IsolatedTest */

void IsolatedTest::set(NIndex nt)
 {
  if( !flag[nt] )
    {
     flag[nt]=true;
     
     list[list_len++]=nt;
    }
 }

void IsolatedTest::step(NIndex nt)
 {
  for(auto p=getStep(step_list[nt]); +p ;++p) set(*p);
 }

OffLen IsolatedTest::buildStep(NIndex nt)
 {
  ulen off=step_pool.getLen();
  
  ulen ext_len=0;
  
  for(auto p=lang.getRules(nt); +p ;++p)
    {
     auto q=p->str;
     
     ext_len+=q.len;
    }
  
  NIndex *buf=step_pool.extend_raw(ext_len).ptr;
  NIndex *out=buf;
  
  for(auto p=lang.getRules(nt); +p ;++p)
    {
     auto q=p->str;
     
     for(; +q ;++q) if( q->isNIndex() ) *(out++)=q->getNIndex();
    }
  
  ulen len=Dist(buf,out);
  
  Sort(buf,len);
  
  len=RemoveDup(buf,len);
  
  step_pool.shrink(ext_len-len);
  
  return OffLen(off,len);
 }

IsolatedTest::IsolatedTest(const Lang &lang_)
 : lang(lang_),
   flag(lang.getNIndexLim()),
   list(lang.getNIndexLim()),
   list_len(0),
   step_list(lang.getNIndexLim())
 {
  for(auto p=lang.getResult(); +p ;++p) set(*p);
  
  for(auto p=lang.getNRange(); +p ;++p) step_list[*p]=buildStep(*p);
 }
   
IsolatedTest::~IsolatedTest()
 {
 }
   
bool IsolatedTest::step()
 {
  for(ulen i=list_len; i-- ;)
    {
     step(list[i]);

     list_len--;

     if( i<list_len ) list[i]=list[list_len];
    }

  return list_len!=0;
 }

} // namespace App

