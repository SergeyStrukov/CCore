/* IntScan.cpp */ 
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
 
#include <CCore/inc/scanf/IntScan.h>

#include <CCore/inc/StrParse.h>
 
namespace CCore {

/* struct IntScanOpt */

IntScanOpt::IntScanOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  if( ParseChar_try(dev,'.') )
    {
     if( Parse_try(dev,scan_base) )
       {
        base=0;
       }
     else
       {
        scan_base=IntScanNone;
        
        ParseUInt(dev,base,MinScanIntBase,MaxScanIntBase);
       }

     if( !dev.finish() ) setDefault();
    }
  else
    {
     setDefault();
    }
 }

} // namespace CCore
 

