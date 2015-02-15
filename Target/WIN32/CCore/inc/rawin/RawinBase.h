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
 
namespace CCore {
namespace Rawin {

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

struct Point;

struct Pane;

class ShowException;

class MainBase;

/* struct Point */ 

struct Point
 {
  int x;
  int y;
  
  Point() : x(0),y(0) {}
  
  Point(int x_,int y_) : x(x_),y(y_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",x,y);
   }
 };
 
inline Point operator + (Point a,Point b) { return Point(a.x+b.x,a.y+b.y); }
 
inline Point operator - (Point a,Point b) { return Point(a.x-b.x,a.y-b.y); }
 
inline Point Sup(Point a,Point b) { return Point(Max(a.x,b.x),Max(a.y,b.y)); }
 
inline bool Fit(Point a,Point b) { return a.x<=b.x && a.y<=b.y ; }
 
/* struct Pane */ 

struct Pane
 {
  int x;
  int y;
  int dx;
  int dy;
  
  Pane() : x(0),y(0),dx(0),dy(0) {}
  
  Pane(int x_,int y_,int dx_,int dy_) : x(x_),y(y_),dx(dx_),dy(dy_) {}
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#; +#;,#; +#;)",x,dx,y,dy);
   }
 };
 
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
 

