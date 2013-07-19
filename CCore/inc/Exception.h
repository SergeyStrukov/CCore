/* Exception.h */ 
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

#ifndef CCore_inc_Exception_h
#define CCore_inc_Exception_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/PlanInit.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_Exception();

/* classes */ 

class ReportException;

class SilentReportException;

class PrintException;

template <class T> class CustomThrow;

template <class T> class PrintCustomException;

/* class ReportException */ 

class ReportException : NoCopy
 {
   DLink<ReportException> link;
   bool nok;
   
   typedef DLink<ReportException>::LinearAlgo<&ReportException::link> Algo;
   
  private:
  
   static ReportException * Top(); 
   
   static void SetTop(ReportException *top);
   
   static ReportException * Start(ExceptionType ex);
   
   static void Add(ReportException *report,const char *ptr,ulen len);
   
   static void End(ReportException *report);
   
   friend class PrintException;
 
  protected:
  
   static void Print(StrLen str);
  
   virtual void print(StrLen str);
  
   virtual void start(ExceptionType ex);
  
   virtual void add(const char *ptr,ulen len);
   
   virtual void end();
  
  public:
  
   ReportException();
   
   ~ReportException();
   
   bool operator + () const { return !nok; }
   
   bool operator ! () const { return nok; }
   
   void clear() { nok=false; }
  
   void guard() { if( nok ) throw CatchType(); }
   
   static void Clear();
 };
 
/* class SilentReportException */ 

class SilentReportException : public ReportException
 {
  private:
  
   virtual void print(StrLen str);
  
   virtual void start(ExceptionType ex);
  
   virtual void add(const char *ptr,ulen len);
   
   virtual void end();
   
  public:
  
   SilentReportException();
   
   ~SilentReportException();
 };
 
/* class PrintException */ 

class PrintException : public PrintBase
 {
   ExceptionType ex;
   ReportException *report;
   
   char buf[TextBufLen];
   bool do_throw;
 
  private:
  
   virtual PtrLen<char> do_provide(ulen hint_len);
   
   virtual void do_flush(char *ptr,ulen len);
   
  protected: 
   
   PrintException();
   
  public:
  
   explicit PrintException(ExceptionType ex); 
   
   ~PrintException() noexcept(false);
 };
 
template <> 
struct PrintOutAdapter<ExceptionType> 
 {
  typedef PrintException PrintOutType;
 };

/* class CustomThrow<T> */ 

template <class T> 
class CustomThrow : NoCopy
 {
   T obj;
   
  public: 
   
   template <class ... SS>
   explicit CustomThrow(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
   
   ~CustomThrow() { throw obj; }
 };
 
/* class PrintCustomException<T> */ 

template <class T> 
class PrintCustomException : public CustomThrow<T> , public PrintException
 {
  public:
   
   template <class ... SS>
   explicit PrintCustomException(SS && ... ss) : CustomThrow<T>( std::forward<SS>(ss)... ) {}
 };

} // namespace CCore
 
#endif
 

