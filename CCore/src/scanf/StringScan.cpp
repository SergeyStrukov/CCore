/* StringScan.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
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
 
#include <CCore/inc/scanf/StringScan.h>
 
namespace CCore {

/* struct StringScanOpt */

StringScanOpt::StringScanOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  if( ParseChar_try(dev,'.') && Parse_try(dev,type) )
    {
     if( !dev.finish() ) setDefault();
    }
  else
    {
     setDefault();
    }
 }

} // namespace CCore
 

