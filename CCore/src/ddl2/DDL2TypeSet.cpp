/* DDL2TypeSet.cpp */ 
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
 
#include <CCore/inc/ddl2/DDL2TypeSet.h>

#include <CCore/inc/Crc.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>
 
namespace CCore {
namespace DDL2 {

/* class FindNodeMap */

struct FindNodeMap::CrcGen
 {
  Crc32 crc;
  
  CrcGen() {}
  
  void add(StrLen name)
   {
    crc.addRange(name);
    crc.add('#');
   }
  
  operator uint32() const { return crc; }
 };

void FindNodeMap::ToSearch::setCrc()
 {
  CrcGen crcgen;

  crcgen.add(name);
  
  for(auto *ptr=scope; ptr ;ptr=ptr->parent) crcgen.add(ptr->name.getStr());
  
  crc=crcgen;
 }

void FindNodeMap::Rec::setCrc()
 {
  CrcGen crcgen;
  
  for(StrLen name : names ) crcgen.add(name);
  
  crc=crcgen;
 }

CmpResult FindNodeMap::Rec::objCmp(const Rec &obj) const
 {
  if( CmpResult ret=Cmp(crc,obj.crc) ) return ret;
  
  ulen len=names.getLen();
  
  if( CmpResult ret=Cmp(len,obj.names.getLen()) ) return ret;

  for(ulen i=0; i<len ;i++)
    if( CmpResult ret=StrCmp(names[i],obj.names[i]) ) return ret;
  
  return CmpEqual;
 }

CmpResult FindNodeMap::Rec::objCmp(const ToSearch &obj) const
 {
  if( CmpResult ret=Cmp(crc,obj.crc) ) return ret;
  
  ulen len=names.getLen();
  
  if( CmpResult ret=Cmp(len,obj.len) ) return ret;
  
  if( CmpResult ret=StrCmp(names[0],obj.name) ) return ret;
  
  auto *ptr=obj.scope;

  for(ulen i=1; i<len ;i++,ptr=ptr->parent)
    if( CmpResult ret=StrCmp(names[i],ptr->name.getStr()) ) return ret;
  
  return CmpEqual;
 }

ulen FindNodeMap::find(ToSearch ts)
 {
  PtrLen<Rec> r=Range(list);
  
  Algon::BinarySearch_greater_or_equal(r,ts);

  if( +r && *r==ts ) return r->ind;  
  
  return 0;
 }

void FindNodeMap::complete()
 {
  Sort(Range(list));
 }

} // namespace DDL2
} // namespace CCore
 

