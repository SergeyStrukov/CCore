/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
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

#include "process/GoodEstimate.h"

/* Main() */

namespace App {

using namespace CCore;

int Main(StrLen file_name)
 {
  CondLang clang(file_name);
  Lang lang(clang);
  TopLang top(clang);
  
  // good test
  {
   GoodTest test(top);
   
   while( test.step() );
   
   PrintCon out(Con);
   
   if( !test.check(out) )
     {
      out.flush();
     
      Printf(Exception,"Sanity test failed");
     }
  }
  
  return 0;
 }

} // namespace App

/* main() */ 

using namespace CCore;

int main(int argc,const char *argv[])
 {
  MemScope mem_scope;
  
  try
    {
     ReportException report;
    
     {
      Printf(Con,"--- CondLangLR1 1.00 ---\n--- Copyright (c) 2013 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=2 )
        {
         Printf(Con,"Usage: CondLangLR1 <file.lang>\n");
         
         return 1;
        }

      return App::Main(argv[1]);
     } 
     
     report.guard();
    }
  catch(CatchType)   
    {
     return 1;
    }
  
  return 0;
 }

