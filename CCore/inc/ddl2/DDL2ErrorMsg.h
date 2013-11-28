/* DDL2ErrorMsg.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl2_DDL2ErrorMsg_h
#define CCore_inc_ddl2_DDL2ErrorMsg_h

#include <CCore/inc/Printf.h>

namespace CCore {
namespace DDL2 {

/* consts */

const ulen ErrorMsgCap = 100 ;

/* classes */

class ErrorMsg;

/* class ErrorMsg */

class ErrorMsg : NoCopy
 {
   PrintBase &msg;
  
   ulen error_cap;
   
  public: 
   
   explicit ErrorMsg(PrintBase &msg_) : msg(msg_) { reset(); }
   
   bool operator + () const { return error_cap!=ErrorMsgCap; }
   
   bool operator ! () const { return error_cap==ErrorMsgCap; }
   
   PrintBase & getMsg() { return msg; }
   
   void reset()
    {
     error_cap=ErrorMsgCap;
    }
   
   template <class ... SS>
   void operator () (const char *format,SS && ... ss)
    {
     if( error_cap )
       {
        error_cap--;
        
        Printf(msg,format, std::forward<SS>(ss)... );
        
        Putch(msg,'\n');
       }
    }
 };

} // namespace DDL2
} // namespace CCore

#endif



