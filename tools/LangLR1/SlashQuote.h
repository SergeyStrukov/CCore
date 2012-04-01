/* SlashQuote.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_SlashQuote_h
#define LangLR1_SlashQuote_h

#include "Lang.h"

namespace App {

/* classes */

class SlashQuote;

/* class SlashQuote */ 
  
class SlashQuote
 {
   StrLen str;
   
  private: 
   
   template <class P>
   static void Put(P &out,char ch)
    {
     if( ch=='"' )
       {
        out.put('\\');
        out.put('"');
       }
     else
       {
        out.put(ch);
       }
    }
   
  public: 
  
   SlashQuote(const Lang &lang,TIndex t) : str(lang.getTextDesc(t)) {}
  
   template <class P>
   void print(P &out) const;
 };

template <class P>
void SlashQuote::print(P &out) const
 {
  for(auto s=str; +s ;++s) Put(out,*s);
 }

} // namespace App

#endif
