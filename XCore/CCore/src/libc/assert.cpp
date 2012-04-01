/* assert.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <assert.h>

#include <CCore/inc/PrintAbort.h>

using namespace CCore;

/* __std_assert_failed() */ 

int __std_assert_failed(const char *cond,const char *file_name,int line,const char *func_name)
 {
  PrintAbort("\nassertion ( #; ) failed\n#;:#;\nfunction #;\n\n",cond,file_name,line,func_name);
 
  return 0;
 }
 
  
