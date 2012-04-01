/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Exception.h>
#include <CCore/inc/FileToMem.h>

#include "Generate.h"

namespace App {

/* classes */ 

class Engine;

/* class Engine */ 

class Engine : NoCopy
 {
   StrLen desc_file_name;
   StrLen gen_file_name;
 
  public:
  
   Engine(StrLen desc_file_name_,StrLen gen_file_name_)
    : desc_file_name(desc_file_name_),
      gen_file_name(gen_file_name_)
    {
    }
   
   ~Engine()
    {
     Printf(Con,"#;\n\n",Title("the end"));
    }
    
   int run()
    {
     Printf(Con,"desc = #;\ngen = #;\n\n",desc_file_name,gen_file_name);

     FileToMem file(desc_file_name);

     Parser parser(Mutate<const char>(Range(file)));

     if( !parser ) return 1;

     Generate(parser,gen_file_name);

     return 0;
    } 
 };
 
} // namespace App
 
/* main() */ 

using namespace App;

int main(int argc,const char *argv[]) 
 { 
  ReportException report;
 
  try
    {
     int ret;

     {
      Putobj(Con,"--- Regen 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=3 )
        {
         Printf(Con,"Usage: Regen <desc-file-name> <gen-file-name>\n\n");
         
         return 1;
        }
      
      Engine engine(argv[1],argv[2]);
  
      ret=engine.run();
     } 
     
     report.guard();

     return ret;
    }
  catch(CatchType)   
    {
     return 1;
    }
 }

