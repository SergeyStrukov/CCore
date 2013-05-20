/* ScanBase.cpp */ 
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
 
#include <CCore/inc/scanf/ScanBase.h>
 
namespace CCore {

/* class ScanBase */

void ScanBase::updateTextPos(char ch)
 {
  if( +buf )
    {
     if( ( ch=='\r' && *buf!='\n' ) || ch=='\n' )
       {
        text_pos.nextLine();
       }
     else
       {
        text_pos.nextPos();
       }
    }
  else
    {
     if( ch=='\r' || ch=='\n' )
       {
        text_pos.nextLine();
       }
     else
       {
        text_pos.nextPos();
       }
    }
 }

void ScanBase::operator ++ () 
 { 
  char ch=*buf;
  
  ++buf; 
  
  if( !buf ) 
    try 
      { 
       pump(); 
      } 
    catch(...) 
      {
       updateTextPos(ch);
      
       throw;
      }
  
  updateTextPos(ch);
 }

} // namespace CCore
 

