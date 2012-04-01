/* CPrintf.cpp */ 
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

#include <CCore/inc/libc/CPrintf.h>

namespace LibC_Internal {

/* functions */ 

Size StrLen(const char *str)
 {
  const char *end=str;
  
  while( *end ) end++;
  
  return Size( end-str );
 }
 
Size StrLen(const char *str,Size len)
 {
  Size cnt=len;
  
  for(; cnt && (*str) ;cnt--,str++);
  
  return len-cnt;
 }
   
/* enum PrintfRegister */ 

const char * GetHexDigits(PrintfRegister reg)
 {
  static const char *const table[]=
   {
    "0123456789ABCDEF",
    "0123456789abcdef"
   };
      
  return table[reg]; 
 }
 
char GetHexSign(PrintfRegister reg)
 {
  return "Xx"[reg];
 }
 
/* struct PrintfFlags */ 

const char * PrintfFlags::parse(const char *str)
 {
  minus=false;
  plus=false;
  space=false;
  pound=false;
  zero=false;
  
  for(;;str++)
    switch( *str )
      {
       case '-' : minus=true; break;
       case '+' : plus=true;  break;
       case ' ' : space=true; break;
       case '#' : pound=true; break;
       case '0' : zero=true;  break;
       
       default: return str;
      }
 }
 
/* struct ParsePrintfPrefix */ 

ParsePrintfPrefix::ParsePrintfPrefix(const char *s)
 {
  switch( *s )
    {
     case 'j' : value=Printf_j; break;
     case 'z' : value=Printf_z; break;
     case 't' : value=Printf_t; break;
     case 'L' : value=Printf_L; break;
     
     case 'l' :
      {
       if( s[1]=='l' )
         {
          value=Printf_ll;  
          s++;
         }
       else
         {  
          value=Printf_l;  
         }
      }
     break; 
      
     case 'h' :
      {
       if( s[1]=='h' )
         {
          value=Printf_hh;  
          s++;
         }
       else
         {  
          value=Printf_h;  
         }
      }
     break; 
     
     default:
      {
       value=Printf_none;
       str=s;
      }
     return;
    }
    
  str=s+1;  
 }
  
} // namespace LibC_Internal
 
