/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Run.h"
#include "LangBuilder.h"

/* Main() */

namespace App {

int Main(StrLen lang_name,StrLen file_name,StrLen CCORE_Root)
 {
  Lang::Builder builder(lang_name);
  
  LangInput::Builder input(file_name);
  
  input.extract(builder);
  
  Lang lang(builder);
  
  Run run(lang);
  
  return run.run(CCORE_Root);
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
      Printf(Con,"--- LangLR1 1.00 ---\n--- Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=4 )
        {
         Printf(Con,"Usage: LangLR1 <lang-name> <file.lang> <CCore-Root>\n");
         
         return 1;
        }

      return App::Main(argv[1],argv[2],argv[3]);
     } 
     
     report.guard();
    }
  catch(CatchType)   
    {
     return 1;
    }
  
  return 0;
 }

