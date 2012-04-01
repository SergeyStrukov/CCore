/* NonEmptyTest.h */
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

#ifndef LangLR1_NonEmptyTest_h
#define LangLR1_NonEmptyTest_h

#include "Lang.h"
#include "NonEmptyEstimate.h"

namespace App {

/* classes */

class NonEmptyTest;

/* class NonEmptyTest */

class NonEmptyTest : NoCopy , NonEmptyEstimate
 {
   const Lang &lang;
 
   DynArray<Type> flag;
   DynArray<NIndex> list;
   ulen list_len;
   
   DynArray<NIndex> mul_pool;
   
   struct MulRec : OffLen
    {
     Type first;
     
     MulRec() {}
     
     MulRec(ulen off,ulen len,bool good) : OffLen(off,len),first(good?Good:Null) {}
    };
   
   DynArray<MulRec> step_pool;
   
   DynArray<OffLen> step_list;
   
  private:
   
   PtrLen<const NIndex> getMul(MulRec rec) const { return rec.cut(mul_pool.getPtr()); }
   
   PtrLen<const MulRec> getStep(OffLen rec) const { return rec.cut(step_pool.getPtr()); }
   
   Type mul(MulRec rec) const;
   
   SetResult step(NIndex nt);
   
   MulRec buildMul(PtrLen<const NTIndex> str);
   
   OffLen buildStep(NIndex nt);
   
  public:
   
   explicit NonEmptyTest(const Lang &lang);
   
   ~NonEmptyTest();
   
   bool step();
   
   template <class P>
   bool check(P &out) const;
 };

template <class P>
bool NonEmptyTest::check(P &out) const
 {
  bool ret=true;

  for(auto p=lang.getNRange(); +p ;++p)
    if( flag[*p].isBad() )
      {
       Printf(out,"Bad non-terminal #; : #;\n",lang.getTextDesc(*p),flag[*p].badDesc());
     
       ret=false;
      }

  return ret;
 }

} // namespace App

#endif
