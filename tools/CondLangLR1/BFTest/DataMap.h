/* DataMap.h */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-BFTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef BFTest_DataMap_h
#define BFTest_DataMap_h

#include <CCore/inc/ddl2/DDL2TypeSet.h>

namespace App {

/* using */

using namespace CCore;

/* TypeDef */

#include "../LangTypeDef.gen.h"

/* functions */

template <class T>
bool Checkin(T *ptr,PtrLen<T> range)
 {
  if( ptr==0 ) return false;
  
  ulen index=ptr->index;
  
  return index<range.len && ptr==range.ptr+index ; 
 }

template <class T>
bool Checkin_null(T *ptr,PtrLen<T> range)
 {
  if( ptr==0 ) return true;
  
  ulen index=ptr->index;
  
  return index<range.len && ptr==range.ptr+index ; 
 }

/* classes */

class DataMap;

/* class DataMap */

class DataMap : NoCopy
 {
   void *mem;
   
   TypeDef::Lang lang;
   
  private: 

   void sanity_atoms();
   void sanity_synts();
   void sanity_lang();
   void sanity_rules();
   void sanity_top_rules();
   void sanity_states();
   void sanity_finals();
   
  public: 
  
   explicit DataMap(StrLen file_name);
   
   ~DataMap();
   
   const TypeDef::Lang & getLang() const { return lang; }
   
   void sanity();
 };

} // namespace App

#endif

