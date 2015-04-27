/* WindowReport.h */ 
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

#ifndef CCore_inc_video_WindowReport_h
#define CCore_inc_video_WindowReport_h

//#include <CCore/inc/video/FrameWindow.h>
#include "DragWindow.h"

#include <CCore/inc/Exception.h>
 
namespace CCore {
namespace Video {

/* classes */

class WindowReport;

/* class WindowReport */

class WindowReport : public DragClient , public ReportException
 {
  public:
  
   struct Config
    {
     ColorName back = Black ;
     ColorName text = Green ;
     ColorName divider = Red ;
     
     Font text_font;
     
     Config() {}
     
     Signal<> update;
    };
   
  private:
   
   static const ulen MaxMsgLen = 256 ;
   static const ulen MaxMsgCount = 100 ;
   
   class Store : NoCopy
    {
    
     public:
    
      Store();
      
      ~Store();
      
      PtrLen<char> startMsg();
      
      void endMsg(PtrLen<char> rest);
      
      void divide();
    };
   
   Config &cfg;
   
   Store store;
   PtrLen<char> buf;
   bool msg = false ;
  
  private:
  
   virtual void print(StrLen str);
   
   virtual void end();
   
  public:
  
   explicit WindowReport(Config &cfg);
   
   virtual ~WindowReport();
   
   void clear();
   
   bool show();
 };

} // namespace Video
} // namespace CCore
 
#endif
 

