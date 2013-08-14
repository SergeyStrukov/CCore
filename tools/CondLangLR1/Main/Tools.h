/* Tools.h */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CondLangLR1_Tools_h
#define CondLangLR1_Tools_h

#include <CCore/inc/Print.h>
#include <CCore/inc/TextTools.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

namespace App {

/* using */

using namespace CCore;

/* words */

enum ElementNullType
 {
  ElementNull = 0
 };

enum ElementOneType
 {
  ElementOne = 1
 };

/* TrackStage() */

template <class ... TT>
void TrackStage(const char *format,const TT & ... tt)
 {
  Printf(Con,format,tt...);
  
  Putch(Con,'\n','\n');
 }

/* SetCmp() */

template <class T>
bool SetCmp(T &x,const T &a) 
 {
  if( x!=a )
    {
     x=a;
     
     return true;
    }
  
  return false;
 }

/* classes */

struct PosStr;

struct DescBase;

class TrackStep;

/* struct PosStr */

struct PosStr
 {
  TextPos pos;
  StrLen str;
  
  PosStr() {}
  
  explicit PosStr(TextPos pos_) : pos(pos_) {}
  
  PosStr(TextPos pos_,StrLen str_) : pos(pos_),str(str_) {}
 };

/* struct DescBase */

struct DescBase : NoCopy , NoThrowFlagsBase
 {
  ulen index = MaxULen ;
  StrLen name;
  
  DescBase() {}
  
  bool operator + () const { return index!=MaxULen; }
  
  bool operator ! () const { return index==MaxULen; }
 };

/* class TrackStep */

class TrackStep : NoCopy
 {
   ulen count = 0 ;
   
  public:
  
   TrackStep() {}
   
   void step() 
    {
     ++count;
     
     if( count%100==0 )
       {
        Printf(Con,"  step #;\r",count);
       }
    }
   
   void finish()
    {
     Printf(Con,"  step #;\n\n",count);
    }
 };

} // namespace App

#endif
