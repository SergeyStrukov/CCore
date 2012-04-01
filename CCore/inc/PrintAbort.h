/* PrintAbort.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintAbort_h
#define CCore_inc_PrintAbort_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/Abort.h>
 
namespace CCore {

/* PrintAbort() */

template <class ... TT>
void PrintAbort(const char *format,const TT & ... tt)
 {
  char buf[TextBufLen];
  PrintBuf out(Range(buf));
  
  Printf(out,format,tt...);
  
  Abort(out.close());
 }

} // namespace CCore
 
#endif
 

