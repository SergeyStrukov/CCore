/* WindowReport.cpp */ 
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
 
//#include <CCore/inc/video/WindowReport.h>
#include "WindowReport.h"
 
namespace CCore {
namespace Video {

/* class WindowReport::Store */

WindowReport::Store::Store()
 {
 }

WindowReport::Store::~Store()
 {
 }

PtrLen<char> WindowReport::Store::startMsg()
 {
  return Empty; 
 }

void WindowReport::Store::endMsg(PtrLen<char> rest)
 {
 }

void WindowReport::Store::divide()
 {
 }

/* class WindowReport */

void WindowReport::print(StrLen str)
 {
  if( !msg )
    {
     buf=store.startMsg();
     
     msg=true;
    }
  
  Replace_min(str.len,buf.len);
  
  str.copyTo(buf.ptr);
  
  buf+=str.len;
 }

void WindowReport::end()
 {
  store.endMsg(buf);
  
  msg=false;
 }

WindowReport::WindowReport(Config &cfg_)
 : cfg(cfg_)
 {
 }

WindowReport::~WindowReport()
 {
 }

void WindowReport::clear()
 {
  ReportException::clear();
  
  store.divide();
 }

bool WindowReport::show()
 {
  win->alert();
  
  return true;
 }

} // namespace Video
} // namespace CCore
 

