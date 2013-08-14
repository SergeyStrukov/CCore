/* StateTrace.cpp */
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

#include "StateTrace.h"

namespace App {

/* class StateTrace */

Trace StateTrace::BackTrace::build() const
 {
  if( !ok ) return {}; 
  
  DoRaw do_raw(len);
  RefArray<ulen> ret(do_raw);
  
  const BackTrace *cur=this;
  
  for(auto p=RangeReverse(ret.modify()); +p ;++p)
    {
     *p=cur->element;
     
     cur=cur->from;
    }
  
  return ret;
 }

StateTrace::StateTrace(PtrLen<const Desc> table)
 {
  DynArray<const Desc *> buf(DoReserve,table.len);
  
  DynArray<BackTrace> trace(table.len);
  
  // start
  {
   buf.append_copy(table.ptr);
   
   trace[0].start();
  }
  
  // process
  {
   for(ulen index=0; index<buf.getLen() ;index++)
     {
      const Desc *cur=buf[index];
      const BackTrace *from=&(trace[cur->index]);
      
      for(auto &trans : cur->transitions )
        {
         const Desc *dst=trans.dst;
         
         if( trace[dst->index].setCmp(from,trans.element) )
           {
            buf.append_copy(dst);
           }
        }
     }
  }
  
  Swap(trace,this->trace);
 }

} // namespace App
