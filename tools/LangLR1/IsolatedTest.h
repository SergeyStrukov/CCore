/* IsolatedTest.h */
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

#ifndef LangLR1_IsolatedTest_h
#define LangLR1_IsolatedTest_h

#include "Lang.h"

namespace App {

/* classes */

class IsolatedTest;

/* class IsolatedTest */

class IsolatedTest : NoCopy
 {
   const Lang &lang;
  
   DynArray<bool> flag;
   DynArray<NIndex> list;
   ulen list_len;
   
   DynArray<NIndex> step_pool;
   DynArray<OffLen> step_list;
   
  private: 
  
   PtrLen<const NIndex> getStep(OffLen rec) const { return rec.cut(step_pool.getPtr()); }
   
   void set(NIndex nt);
   
   void step(NIndex nt);
   
   OffLen buildStep(NIndex nt);
   
  public:
  
   explicit IsolatedTest(const Lang &lang);
   
   ~IsolatedTest();
   
   bool step();
   
   template <class P>
   bool check(P &out) const;
 };

template <class P>
bool IsolatedTest::check(P &out) const
 {
  bool ret=true;
  
  for(auto p=lang.getNRange(); +p ;++p)
    if( !flag[*p] )
      {
       Printf(out,"Isolated non-terminal : #;\n",lang.getTextDesc(*p));
       
       ret=false;
      }

  return ret;
 }

} // namespace App

#endif

