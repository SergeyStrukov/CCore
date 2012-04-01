/* TextTools.cpp */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/TextTools.h>
 
namespace CCore {

/* struct TextPos */

void TextPos::update(StrLen text)
 {
  while( text.len>=2 )
    {
     char ch=*text;

     if( ch=='\r' ) 
       {
        if( text[1]=='\n' )
          text+=2;
        else 
          ++text;

        nextLine();
       }
     else if( ch=='\n' )
       {
        ++text;

        nextLine();
       }
     else
       {
        ++text;

        nextPos();
       }
    }

  if( +text )
    {
     char ch=*text;

     if( ch=='\r' || ch=='\n' ) 
       {
        nextLine();
       }
     else
       {
        nextPos();
       }
    }
 }

} // namespace CCore
 

