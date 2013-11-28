/* DDL2Value.cpp */
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

#include <CCore/inc/ddl2/DDL2Value.h>

namespace CCore {
namespace DDL2 {

/* DString functions */

ulen DStringLen(StrLen str)
 {
  ulen ret=0;
  
  for(; +str ;++str)
    {
     char ch=*str;
     
     if( ch=='\\' )
       {
        ++str;
        
        ret++;
       }
     else
       {
        ret++;
       }
    }
  
  return ret;
 }

void DString(StrLen str,char *out)
 {
  for(; +str ;++str)
    {
     char ch=*str;
     
     if( ch=='\\' )
       {
        ++str;
        
        *(out++)=MapDChar(*str);
       }
     else
       {
        *(out++)=ch;
       }
    }
 }

} // namespace DDL2
} // namespace CCore
