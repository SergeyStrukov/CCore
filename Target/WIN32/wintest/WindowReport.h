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

//#include <CCore/inc/video/DragWindow.h>
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
   
   static const ulen MaxMsgLen = Align(256) ;
   static const ulen MaxMsgCount = 100 ;
   
   class Store : NoCopy
    {
      struct Header
       {
        Header *next;
        ulen len;
        bool done;
        bool divide; // after this message
       };
      
      static const ulen Delta = Align(sizeof (Header)) ;
      
      static StrLen GetStr(Header *ptr) { return StrLen(PlaceAt(ptr)+Delta,ptr->len); }
      
      static PtrLen<char> GetBuf(Header *ptr) { return PtrLen<char>(PlaceAt(ptr)+Delta,ptr->len); }
      
      static void * GetNext(Header *ptr) { return PlaceAt(ptr)+Delta+Align(ptr->len); }
      
     private:
      
      void *mem;
      void *lim;
      
      Header *head;
      Header *tail;
      
     private:
     
      Header * try_alloc();
      
      Header * alloc();
      
      void free();
      
     public:
    
      Store();
      
      ~Store();
      
      PtrLen<char> startMsg();
      
      void endMsg(PtrLen<char> rest);
      
      void divide();
      
      template <class Func>
      void apply(Func func) const // func(StrLen text,bool divide)
       {
        for(Header *ptr=head; ptr ;ptr=ptr->next) if( ptr->done ) func(GetStr(ptr),ptr->divide);
       }
    };
   
   Store store;
   PtrLen<char> buf;
   bool msg = false ;
   
  private: 
  
   Config &cfg;
   
   bool non_empty = false ;
   
   ulen off = 0 ;
   ulen lines = 0 ;
   
   ulen visible_lines = 0 ;
   Coord text_by = 0 ;
   Coord text_dy = 0 ;
   
  private:
  
   virtual void print(StrLen str);
   
   virtual void end();
   
   static ulen Lines(StrLen text);
   
   void setLines();
   
  public:
  
   explicit WindowReport(Config &cfg);
   
   virtual ~WindowReport();
   
   void clear();
   
   bool show();
   
   // drawing
   
   virtual void layout(Point size);
   
   virtual void draw(FrameBuf<DesktopColor> buf,bool drag_active) const;
   
   // base
   
   virtual void alive();
   
   // keyboard
   
   virtual void key(VKey vkey,KeyMod kmod);
   
   virtual void key(VKey vkey,KeyMod kmod,unsigned repeat);
   
  private:
   
   // Signal connectors
   
   void updateConfig() { win->redraw(true); }
   
   SignalConnector<WindowReport> connector_updateConfig;
 };

} // namespace Video
} // namespace CCore
 
#endif
 

