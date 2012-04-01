/* DDLMsgReport.cpp */
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ddl/DDLMsgReport.h>

namespace CCore {
namespace DDL {

/* class MsgReport */

void MsgReport::print(StrLen str)
 {
  SilentReportException report;
  
  try
    {
     msg.put(str.ptr,str.len);
    }
  catch(...) {}
 }

} // namespace DDL
} // namespace CCore


