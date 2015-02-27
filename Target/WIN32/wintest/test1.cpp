/* test1.cpp */
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

namespace App1 {

/* using */ 

using namespace App;

/* classes */

class FileReport;

class MainWindow;

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

/* testmain() */

int testmain(CmdDisplay cmd_display)
 {
  FileReport report;
  
  try
    {
     Desktop *desktop=DefaultDesktop;
     MalevichWindow main_win(desktop);
     
     main_win.createMain(cmd_display,desktop->getScreenSize());
     
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
 
} // namespace App1
 
 
 


