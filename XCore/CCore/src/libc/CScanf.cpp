/* CScanf.cpp */ 
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

#include <CCore/inc/libc/CScanf.h>

namespace LibC_Internal {

/* struct ParseScanfPrefix */ 

ParseScanfPrefix::ParseScanfPrefix(const char *s)
 {
  switch( *s )
    {
     case 'j' : value=Scanf_j; break;
     case 'z' : value=Scanf_z; break;
     case 't' : value=Scanf_t; break;
     case 'L' : value=Scanf_L; break;
     
     case 'l' :
      {
       if( s[1]=='l' )
         {
          value=Scanf_ll;  
          s++;
         }
       else
         {  
          value=Scanf_l;  
         }
      }
     break; 
      
     case 'h' :
      {
       if( s[1]=='h' )
         {
          value=Scanf_hh;  
          s++;
         }
       else
         {  
          value=Scanf_h;  
         }
      }
     break; 
     
     default:
      {
       value=Scanf_none;
       str=s;
      }
     return;
    }
    
  str=s+1;  
 }

} // namespace LibC_Internal
 
