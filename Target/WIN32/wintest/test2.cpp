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

#include "Malevich.h"

namespace App2 {

/* using */ 

using namespace App;

/* classes */

class FileReport;

class TestWindow;

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
 };

/* class TestWindow */

class TestWindow : public MalevichWindow
 {
  public:
  
   TestWindow() {}
   
   virtual ~TestWindow() {}
 };

/* testmain() */

int testmain(CmdDisplay cmd_display)
 {
  FileReport report;
  
  try
    {
     TestWindow main_win;
     TestWindow win1;
     TestWindow win2;
     TestWindow win3;
     
     main_win.createMain(cmd_display);
     
     win1.create(Pane(100,100,300,200));
     
     win2.create(win1.getControl(),Pane(150,150,300,200));
     win3.create(win1.getControl(),Pane(200,200,300,200));
     
     while( DefaultDesktop->pump() )
       {
        DefaultDesktop->wait(10_msec);
       }
     
     return 0;
    }
  catch(...)
    {
     return 1;
    }
 }
 
} // namespace App2
 
 
 


