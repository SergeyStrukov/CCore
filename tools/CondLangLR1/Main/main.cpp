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

#include "lang/Lang.h"

/* Main() */

namespace App {

using namespace CCore;

int Main(StrLen lang_name,StrLen file_name,StrLen CCORE_Root)
 {
  Printf(Con,"#.q;\n#.q;\n#.q;\n",lang_name,file_name,CCORE_Root);
  
  Lang lang(file_name);
  
  Putobj(Con,"-----\n");
  
  for(auto atom : lang.getAtoms() ) Printf(Con,"#;) #;\n",atom.index,atom.name);
  
  Putobj(Con,"-----\n");
  
  for(auto synt : lang.getSynts() ) 
    {
     Printf(Con,"#;) #;",synt.index,synt.name);
     
     if( synt.is_lang ) Putobj(Con," !");
     
     if( +synt.kinds )
       {
        Putobj(Con," { ");
       
        for(auto kind : synt.kinds ) Printf(Con,"#;) #; ",kind.index,kind.name);
        
        Putch(Con,'}');
       }
     
     Putch(Con,'\n');
    }
  
  Putobj(Con,"-----\n");
  
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
      
      if( argc!=4 )
        {
         Printf(Con,"Usage: CondLangLR1 <lang-name> <file.lang> <CCore-Root>\n");
         
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

