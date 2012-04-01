/* PTPSupport.cpp */ 
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
 
#include <CCore/inc/net/PTPSupport.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Net {
namespace PTP {

/* functions */ 

bool GuardSupportNoPacket(ExceptionType ex,const char *name)
 {
  Printf(ex,"#; : no packet for transaction",name);
  
  return false;
 }
 
bool GuardSupportTransFailed(ExceptionType ex,const char *name,TransResult trans_result)
 {
  Printf(ex,"#; : transaction failed : #;",name,trans_result);
  
  return false;
 }
 
bool GuardSupportError(ExceptionType ex,const char *name,StrLen str)
 {
  Printf(ex,"#; : transaction error : #;",name,str);
  
  return false;
 }
 
/* class Support_Exist */ 

const char * GetTextDesc(Support_Exist::ResultType result)
 {
  switch( result )
    {
     case Support_Exist::NotExist : return "NotExist";
     
     case Support_Exist::Exist : return "Exist";
     
     default: return "Unknown";
    }
 }
 
} // namespace PTP
} // namespace Net
} // namespace CCore
 

