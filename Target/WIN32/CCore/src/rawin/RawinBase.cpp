/* RawinBase.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/rawin/RawinBase.h>

#include <CCore/inc/sys/SysAbort.h>
 
namespace CCore {
namespace Rawin {

/* class ShowException */ 

void ShowException::print(StrLen str)
 {
  out.put(str.ptr,str.len);
 }
 
void ShowException::end()
 {
  out.put('\n');
 }
   
ShowException::ShowException(ShowExceptionFunc func_)
 : buf(Len),
   out(Range(buf)),
   func(func_)
 {
 }
   
ShowException::~ShowException()
 {
 }
 
void ShowException::clear()
 {
  ReportException::clear();
  
  out.init(Range(buf));
 }
   
bool ShowException::show()
 {
  if( silent ) return true;
  
  switch( func(out.closeZStr(),out.getOverflowFlag()) )
    {
     case ExceptionAction_Abort : Sys::AbortProcess();
     
     case ExceptionAction_Exit : return false;
     
     case ExceptionAction_ContinueSilent : silent=true; // falldown;
     
     default: return true;
    }
 }
 
/* class MainBase */ 

MainBase::MainBase(ShowExceptionFunc func)
 : report(func)
 {
 }

MainBase::~MainBase()
 {
 }

int MainBase::run()
 {
  try
    {
     report.clear();
    
     do_run();
     
     report.guard();
     
     return 0;
    }
  catch(CatchType) 
    {
     report.show();
    
     return 1;
    }
 }
   
} // namespace Rawin
} // namespace CCore
 

