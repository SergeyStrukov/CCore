/* Info.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/video/Info.h>
 
namespace CCore {
namespace Video {

/* class InfoFromString */

StrLen InfoFromString::Impl::CutLine(StrLen &str)
 {
  for(StrLen next=str; +next ;++next)
    {
     char ch=*next;
     
     if( ch=='\r' || ch=='\n' )
       {
        StrLen ret=str.prefix(next);
        
        ++next;
        
        if( ch=='\r' && +next && *next=='\n' ) ++next;
        
        str=next;
        
        return ret;
       }
    }
  
  return Replace_null(str);
 }

InfoFromString::Impl::Impl(StrLen str)
 : buf(DoReserve,100)
 {
  while( +str )
    {
     StrLen line=CutLine(str);
     
     buf.append_fill(line);
    }
  
  buf.shrink_extra();
 }

InfoFromString::Impl::~Impl()
 {
 }

ulen InfoFromString::Impl::getLineCount() const
 {
  return buf.getLen();
 }

StrLen InfoFromString::Impl::getLine(ulen index) const
 {
  return Range(buf.at(index));
 }

InfoFromString::InfoFromString(StrLen str)
 : Info(new Impl(str))
 {
 }

InfoFromString::~InfoFromString()
 {
 }

} // namespace Video
} // namespace CCore
 

