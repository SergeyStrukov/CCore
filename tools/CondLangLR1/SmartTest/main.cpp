/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-SmartTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include "Process.h"

/* main() */ 

using namespace CCore;

int main(int argc,const char *argv[])
 {
  MemScope mem_scope;
  
  try
    {
     ReportException report;
    
     {
      Printf(Con,"--- CondLangLR1-SmartTest 1.00 ---\n--- Copyright (c) 2013 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=2 )
        {
         Printf(Con,"Usage: SmartTest <file.ddl>\n");
         
         return 1;
        }

      App::Process(argv[1]);
     } 
     
     report.guard();
     
     return 0;
    }
  catch(CatchType)   
    {
     return 1;
    }
 }

