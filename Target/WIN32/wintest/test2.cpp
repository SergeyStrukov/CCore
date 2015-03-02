/* test2.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/Win32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/TickTimer.h>
#include <CCore/inc/BinaryFile.h>

#include <CCore/inc/task/TaskEvent.h>

#include "Malevich.h"

namespace App2 {

/* using */ 

using namespace App;

/* classes */

class FileReport;

class Application;

/* class FileReport */

class FileReport : public ReportException
 {
   PrintFile out;
   
  private: 
 
   virtual void print(StrLen str)
    {
     Putobj(out,str);
    }
   
   virtual void end()
    {
     Printf(out,"\n\n#;\n\n",TextDivider());
    }
   
  public:
  
   FileReport() : out("exception-log.txt") {}
   
   ~FileReport() {}
   
   bool show() { return true; }
 };

/* class Application */

class Application : NoCopy
 {
   FileReport report;
   
   Desktop *desktop;
 
   MalevichWindow main_win;
   MalevichWindow win1;
   MalevichWindow win2;
   MalevichWindow win3;
   
  private:
   
   bool pump()
    {
     try
       {
        report.clear();
           
        if( desktop->pump() )
          {
           report.guard();
             
           return true;
          }
        else
          {
           return false;
          } 
       }
     catch(CatchType) 
       {
        if( !report.show() )
          {
           main_win.destroy();
          }
           
        return true;
       } 
    }
   
   void tick()
    {
     try
       {
        report.clear();
        
        TickEntryEvent();
           
        main_win.tick();
        win1.tick();
        win2.tick();
        win3.tick();
        
        TickLeaveEvent();
           
        report.guard();
       }
     catch(CatchType) 
       {
        if( !report.show() )
          {
           main_win.destroy();
          }
       } 
    }
   
  public: 
   
   explicit Application(Desktop *desktop_=DefaultDesktop)
    : desktop(desktop_),
      main_win(desktop_),
      win1(desktop_),
      win2(desktop_),
      win3(desktop_)
    {
    }
   
   ~Application()
    {
    }
   
   int run(CmdDisplay cmd_display)
    {
     Point max_size=desktop->getScreenSize();
     
     main_win.createMain(cmd_display,max_size);
     
     win1.create(Pane(100,100,300,200),max_size);
     
     win2.create(win1.getControl(),Pane(150,150,300,200),max_size);
     win3.create(win1.getControl(),Pane(200,200,300,200),max_size);
     
     report.guard();
     
     TickTimer timer(500_msec);
     
     while( pump() )
       {
        if( timer.poll() ) tick();
        
        desktop->wait(timer.remains());
       }
     
     report.guard();
     
     return 0;
    }
 };

/* testmain() */

int testmain(CmdDisplay cmd_display)
 {
  int ret;
  
  TaskEventRecorder recorder(100_MByte);
  
  try
    {
     TickTask tick_task;
     TaskEventHostType::StartStop start_stop(TaskEventHost,&recorder);
     
     Application app;
    
     ret=app.run(cmd_display);
    }
  catch(CatchType)
    {
     return 1;
    }
  
  BinaryFile dev("test2.bin");
  
  dev(recorder);
  
  return ret;
 }
 
} // namespace App2
 
 
 


