/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ShapeLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ShapeLab.h>
#include <inc/SmoothDrag.h>

#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/WindowReport.h>

#include <CCore/inc/TaskMemStack.h>

namespace App {

/* classes */

class Client;

struct Param;

class Application;

/* class Client */

class Client : public ClientWindow
 {
   ShapeLab window;
  
  public:
   
   explicit Client(SubWindowHost &host) : window(host) { sub_win=&window; }
   
   ~Client() {}
 };

/* struct Param */

struct Param : WindowReportParamOf<SmoothDragShape>
 {
  Param()
   {
   }
 };

/* class Application */

class Application : public ApplicationBase
 {
   const CmdDisplay cmd_display;
   
   DragWindowOf<SmoothDragShape> main_win;
   
   ExceptionClient exception_client;
   Client client;
   
  private:
  
   virtual void clearException() noexcept(EnableNoExcept)
    {
     exception_client.clear();
    }
   
   virtual void guardException()
    {
     exception_client.guard();
    }
   
   virtual void showException() noexcept(EnableNoExcept)
    {
     exception_client.show();
    }
   
   virtual void prepare()
    {
     Point max_size=desktop->getScreenSize();
     
     main_win.createMain(cmd_display,max_size,String("ShapeLab"));
    }
   
   virtual void beforeLoop() noexcept(EnableNoExcept)
    {
     exception_client.beforeLoop();
    }
   
   virtual void afterLoop() noexcept(EnableNoExcept)
    {
     exception_client.afterLoop();
    }
   
   virtual void final()
    {
     // do nothing
    }
   
  public: 
   
   explicit Application(WindowReportBase &report,CmdDisplay cmd_display_,Param &param)
    : ApplicationBase(param.desktop,param.tick_period),
      cmd_display(cmd_display_),
      main_win(param.desktop,param.drag_cfg),
      exception_client(main_win,report,param.cfg),
      client(main_win)
    {
     main_win.bindAlertClient(exception_client);
     main_win.bindClient(client);
    }
   
   ~Application()
    {
    }
 };

/* Main() */

int Main(CmdDisplay cmd_display)
 {
  try
    {
     TaskMemStack tms(64_KByte);
     
     Param param;
     WindowReportOf<SmoothDragShape> report(param);
    
     Application app(report,cmd_display,param);
    
     return app.run();
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace App


