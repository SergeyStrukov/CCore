/* PrintError.h */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintError_h
#define CCore_inc_PrintError_h

#include <CCore/inc/Printf.h>
 
#include <CCore/inc/sys/SysError.h>

namespace CCore {

/* classes */ 

class PrintError;

/* class PrintError */ 

class PrintError
 {
   Sys::ErrorType error;
   
  public: 
  
   explicit PrintError(Sys::ErrorType error_) : error(error_) {}
   
   template <class P>
   void print(P &out) const
    {
     char buf[TextBufLen];

     Sys::ErrorDesc desc;

     if( desc.init(error,Range(buf)) )
       {
        out.put(desc.str,desc.len);
       }
     else
       {
        Printf(out,"Unknown system error code #;",error);
       }
    }
 };
 
} // namespace CCore
 
#endif
 

