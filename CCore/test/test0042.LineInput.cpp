/* test0042.LineInput.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/LineInput.h>
#include <CCore/inc/ReadCon.h>

namespace App {

namespace Private_0042 {


} // namespace Private_0042
 
using namespace Private_0042; 
 
/* Testit<42> */ 

template<>
const char *const Testit<42>::Name="Test42 LineInput";

template<>
bool Testit<42>::Main() 
 { 
  LineInput<ReadCon> line;
  
  for(;;)
    {
     Putobj(Con,"test> ");
     
     StrLen str=line.get();
     
     Printf(Con,"#.q;\n",str);
     
     if( str.equal(StrLen("exit")) ) break;
    }
    
  Putobj(Con,"test> ");
  
  for(TimeScope time_scope(3_sec);;)
    {
     StrLen str;
     
     if( line.get(time_scope,str) )
       {
        Printf(Con,"#.q;\n",str);
        
        if( str.equal(StrLen("exit")) ) break;
        
        Putobj(Con,"test> ");
       }
     else
       {
        Putobj(Con,".....\b\b\b\b\b");
        
        Task::Sleep(300_msec);
        
        Putobj(Con,"     \b\b\b\b\b");
        
        time_scope.nextScope();
       }
    }
    
  return true;
 }
 
} // namespace App
 
