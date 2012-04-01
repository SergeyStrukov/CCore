/* TaskPriority.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/task/TaskPriority.h>
 
namespace CCore {

/* struct PrintTaskPriority */

PrintTaskPriority::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);
  
  ParseUInt_empty(dev,width,0);
  
  Parse_empty(dev,align);
  
  if( !dev.finish() ) setDefault();
 }

} // namespace CCore
 

