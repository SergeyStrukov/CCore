/* ScanTools.h */ 
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

#ifndef CCore_inc_scanf_ScanTools_h
#define CCore_inc_scanf_ScanTools_h
 
#include <CCore/inc/TextTools.h>

namespace CCore {

/* CharBaseValue() */

inline int CharBaseValue(char ch,unsigned base)
 {
  int dig=CharHexValue(ch);
  
  if( (unsigned)dig>=base ) return -1;
  
  return dig;
 }

/* SkipSpace() */

template <class S>
void SkipSpace(S &inp)
 {
  for(; +inp && CharIsSpace(*inp) ;++inp);
 }

/* PassChars() */

template <class S>
void PassChars(S &)
 {
  // do nothing
 }

template <class S,class C,class ... CC>
void PassChars(S &inp,C ch,CC ... cc)
 {
  if( +inp && (*inp)==char(ch) )
    {
     ++inp;
        
     PassChar(inp,cc...);
    }
  else
    {
     inp.fail();
    }
 }

/* PassOneOfChar() */

template <class S,class Func>
void PassOneOfChar(S &inp,Func func)
 {
  if( +inp && func(*inp) )
    {
     ++inp;
    }
  else
    {
     inp.fail();
    }
 }

} // namespace CCore
 
#endif
 

