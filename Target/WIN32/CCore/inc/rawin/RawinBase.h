/* RawinBase.h */ 
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

#ifndef CCore_inc_rawin_RawinBase_h
#define CCore_inc_rawin_RawinBase_h

#include <CCore/inc/Exception.h>
#include <CCore/inc/SafeBuf.h>
#include <CCore/inc/video/Point.h>
 
namespace CCore {
namespace Rawin {

/* using */

using Video::Point;
using Video::Pane;

/* types */

enum ExceptionAction
 {
  ExceptionAction_Abort,
  ExceptionAction_Exit,
  ExceptionAction_Continue,
  ExceptionAction_ContinueSilent
 };

using ShowExceptionFunc = ExceptionAction (*)(const char *text,bool more_text) ;

/* classes */ 

class ShowException;

class MainBase;

/* class ShowException */ 

class ShowException : public ReportException
 {
   static const ulen Len = 4_KByte ;
 
   SafeBuf buf;
   PrintBuf out;
   
   bool silent = false ;
   ShowExceptionFunc func;
   
  private: 
 
   virtual void print(StrLen str);
   
   virtual void end();
   
  public:
  
   explicit ShowException(ShowExceptionFunc func);
   
   ~ShowException();
   
   void clear();
   
   bool show();
 };
 
/* class MainBase */ 

class MainBase : NoCopy
 {
  protected: 
  
   ShowException report;
  
  private:
  
   virtual void do_run()=0;
   
  public:
  
   explicit MainBase(ShowExceptionFunc func);
   
   ~MainBase();
   
   int run();
 };
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

