/* Exception.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/Exception.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/TlsSlot.h>

namespace CCore {

/* GetPlanInitNode_...() */ 

namespace Private_Exception {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("Exception") {}
 };
 
Slot Object CCORE_INITPRI_1 ;

} // namespace Private_Exception
 
using namespace Private_Exception;
 
PlanInitNode * GetPlanInitNode_Exception() { return &Object; }
 
/* class ReportException */ 

ReportException * ReportException::Top()
 {
  return static_cast<ReportException *>(Object.get());
 }
   
void ReportException::SetTop(ReportException *top)
 {
  Object.set(top);
 }
   
ReportException * ReportException::Start(ExceptionType ex)
 {
  ReportException *report=Top();
  
  if( report )
    {
     report->nok=true;
     
     report->start(ex);
    }
  else
    {
     Print(GetTextDesc(ex));
    }
  
  return report;
 }
 
void ReportException::Add(ReportException *report,const char *ptr,ulen len)
 {
  if( report )
    {
     report->add(ptr,len);
    }
  else
    {
     Print(StrLen(ptr,len));
    }
 }
   
void ReportException::End(ReportException *report)
 {
  if( report )
    {
     report->end();
    }
  else
    {
     Print("\n\n");
    }
 }
   
void ReportException::Print(StrLen str) 
 { 
  PrintCon::Print(str); 
 }
 
void ReportException::print(StrLen str)
 {
  Print(str);
 }
 
void ReportException::start(ExceptionType ex)
 {
  print(GetTextDesc(ex));
 }
  
void ReportException::add(const char *ptr,ulen len)
 {
  print(StrLen(ptr,len));
 }
   
void ReportException::end()
 {
  print("\n\n");
 }
 
ReportException::ReportException()
 : nok(false)
 {
  SetTop( Algo::InsTop(Top(),this) );
 }
   
ReportException::~ReportException()
 {
  SetTop( Algo::DelTop(Top(),this) );
 }
 
void ReportException::Clear()
 {
  ReportException *report=Top();
  
  if( report ) report->clear();
 }

/* class SilentReportException */ 

void SilentReportException::print(StrLen)
 {
 }
  
void SilentReportException::start(ExceptionType)
 {
 }
  
void SilentReportException::add(const char *,ulen)
 {
 }
   
void SilentReportException::end()
 {
 }
   
SilentReportException::SilentReportException()
 {
 }
   
SilentReportException::~SilentReportException()
 {
 }
   
/* class PrintException */ 

PtrLen<char> PrintException::do_provide(ulen)
 {
  return Range(buf);
 }
   
void PrintException::do_flush(char *ptr,ulen len)
 {
  ReportException::Add(report,ptr,len);
 }
   
PrintException::PrintException()
 : ex(Exception),
   do_throw(false)
 {
  report=ReportException::Start(ex);
 }
   
PrintException::PrintException(ExceptionType ex_)
 : ex(ex_),
   do_throw(ex_==Exception)
 {
  report=ReportException::Start(ex_);
 }
   
PrintException::~PrintException() noexcept(false)
 {
  flush();
  
  ReportException::End(report);
    
  if( do_throw ) throw CatchType(); 
 }
 
} // namespace CCore
 

