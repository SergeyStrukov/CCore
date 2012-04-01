/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: exectest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

/* main() */ 

using namespace CCore;

int main(int argc,const char *argv[])
 {
  ReportException report;
  
  try
    {
     {
      PrintFile out("args.txt");
      
      for(int i=0; i<argc ;i++) Printf(out,"argv[#;] = #.q;\n",i,argv[i]);
     }

     report.guard();
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
