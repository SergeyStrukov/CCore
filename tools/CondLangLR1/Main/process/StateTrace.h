/* StateTrace.h */
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

#ifndef CondLangLR1_process_StateTrace_h
#define CondLangLR1_process_StateTrace_h

#include "StateCompress.h"

namespace App {

/* classes */

struct Trace;

class StateTrace;

/* struct Trace */

struct Trace : NoThrowFlagsBase 
 {
  bool ok;
  RefArray<ulen> trace;
  
  // constructors
  
  Trace() : ok(false) {}
  
  Trace(RefArray<ulen> trace_) : ok(true),trace(trace_) {}
  
  // print object
  
  using PrintOptType = ExtLangOpt ;
  
  template <class P>
  void print(P &out,ExtLangOpt opt) const
   {
    if( ok )
      {
       auto p=Range(trace);
       
       if( +p )
         {
          Putobj(out,opt[*p]);
          
          for(++p; +p ;++p)
            {
             Putch(out,' ');
             Putobj(out,opt[*p]);
            }
         }
       else
         {
          Putobj(out,"NULL");
         }
      }
    else
      {
       Putobj(out,"NO-TRACE");
      }
   }
 };

/* class StateTrace */

class StateTrace : NoCopy
 {
   using Desc = StateCompressBase::StateDesc ;
  
   struct BackTrace : NoCopy , NoThrowFlagsBase
    {
     bool ok;
     
     const BackTrace *from;
     ulen element;
     ulen len;
     
     BackTrace() : ok(false) {}
     
     void start()
      {
       ok=true;
       len=0;
      }
     
     bool setCmp(const BackTrace *from_,ulen element_)
      {
       if( ok ) return false;
       
       ok=true;
       from=from_;
       element=element_;
       len=LenAdd(from_->len,1);
       
       return true;
      }

     Trace build() const;
    };
   
  private: 
  
   DynArray<BackTrace> trace;
   
  private:
  
   explicit StateTrace(PtrLen<const Desc> table);
   
  public:

   template <class Compress>
   explicit StateTrace(const Compress &compress) : StateTrace(compress.getStateTable()) {} 
   
   ~StateTrace() {}
   
   Trace operator [] (ulen index) const { return trace[index].build(); }
 };

} // namespace App

#endif
