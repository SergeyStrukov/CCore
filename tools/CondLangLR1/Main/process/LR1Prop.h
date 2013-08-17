/* LR1Prop.h */
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

#ifndef CondLangLR1_process_LR1Prop_h
#define CondLangLR1_process_LR1Prop_h

#include "LR1Estimate.h"

namespace App {

/* classes */

class LR1PropNonEmpty;

/* class LR1PropNonEmpty */

class LR1PropNonEmpty : public CmpComparable<LR1PropNonEmpty> , public NoThrowFlagsBase 
 {
   bool non_empty;
   
  public:
  
   // constructors
  
   explicit LR1PropNonEmpty(LR1Estimate est) : non_empty(+est) {}
   
   // properties
   
   bool operator + () const { return non_empty; }
   
   bool operator ! () const { return !non_empty; }
   
   // cmp objects
   
   CmpResult objCmp(LR1PropNonEmpty obj) const { return LessCmp(non_empty,obj.non_empty); }
   
   // print object
   
   using PrintOptType = BlockPrintOpt ;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     if( non_empty )
       Putobj(out,"non-empty");
     else
       Putobj(out,"empty");
     
     if( opt.flag ) Putch(out,'\n');
    }
 };

} // namespace App

#endif
