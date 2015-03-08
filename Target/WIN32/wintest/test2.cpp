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
#include <CCore/inc/BinaryFile.h>
#include <CCore/inc/video/ApplicationBase.h>

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

class Application : public ApplicationBase
 {
   const CmdDisplay cmd_display;
  
   FileReport report;
   
   MalevichWindow main_win;
   MalevichWindow win1;
   MalevichWindow win2;
   MalevichWindow win3;
   
  private:
  
   virtual void clearException()
    {
     report.clear();
    }
   
   virtual void guardException()
    {
     report.guard();
    }
   
   virtual void showException()
    {
     if( !report.show() ) main_win.destroy();
    }
   
   virtual void prepare()
    {
     Point max_size=desktop->getScreenSize();
     
     main_win.createMain(cmd_display,max_size);
     
     win1.create(Pane(100,100,300,200),max_size);
     
     win2.create(win1.getControl(),Pane(150,150,300,200),max_size);
     win3.create(win1.getControl(),Pane(200,200,300,200),max_size);
    }
   
   virtual void do_tick()
    {
     TickEntryEvent();
        
     main_win.tick();
     win1.tick();
     win2.tick();
     win3.tick();
     
     TickLeaveEvent();
    }
   
  public: 
   
   explicit Application(CmdDisplay cmd_display_)
    : ApplicationBase(500_msec),
      cmd_display(cmd_display_),
      main_win(desktop),
      win1(desktop),
      win2(desktop),
      win3(desktop)
    {
    }
   
   ~Application()
    {
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
     
     Application app(cmd_display);
    
     ret=app.run();
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
 
 
 


