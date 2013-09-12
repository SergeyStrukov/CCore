/* DDLMsgReport.h */
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

#ifndef CCore_inc_ddl_DDLMsgReport_h
#define CCore_inc_ddl_DDLMsgReport_h

#include <CCore/inc/Exception.h>

namespace CCore {
namespace DDL {

/* using */

using MsgReport = ReportExceptionTo<PrintBase> ;

} // namespace DDL
} // namespace CCore
 
#endif
 

