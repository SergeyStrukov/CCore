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

#include <CCore/inc/Sort.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/algon/BinarySearch.h>

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

/* class StringSetScan */

PtrLen<StrLen> StringSetScan::Select(PtrLen<StrLen> r,char ch,ulen off)
 {
  Algon::BinarySearch_if(r, [=] (StrLen a) { return a.len>off && a[off]>=ch ; } );
  
  return Algon::BinarySearch_if(r, [=] (StrLen a) { return a[off]>ch ; } );
 }

PtrLen<StrLen> StringSetScan::Select(PtrLen<StrLen> r,ulen off)
 {
  return Algon::BinarySearch_if(r, [=] (StrLen a) { return a.len>off; } );
 }

StringSetScan::StringSetScan(std::initializer_list<const char *> zstr_list)
 : list(zstr_list)
 {
  IncrSort(Range(list), [] (StrLen a,StrLen b) { return StrLess(a,b); } );
 }

StringSetScan::~StringSetScan()
 {
 }

} // namespace CCore
 

