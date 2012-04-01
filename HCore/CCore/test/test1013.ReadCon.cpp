/* test1013.ReadCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/CharProp.h>

namespace App {

namespace Private_1013 {


} // namespace Private_1013
 
using namespace Private_1013; 
 
/* Testit<1013> */ 

template<>
const char *const Testit<1013>::Name="Test1013 ReadCon";

template<>
bool Testit<1013>::Main() 
 { 
  ReadCon con;
  
  con.put("Type 'x' to stop\n\n");
  
  for(char ch; (ch=con.get())!='x' ;) 
    {
     Printf(Con,"#;\n",CharCode(ch));
    }
    
  con.put("Type 'x' to exit\n\n");
  
  for(char ch;;) 
    {
     if( !con.get(3_sec,ch) )
       {
        Printf(Con,"input timeout\n");
        
        continue;
       }
       
     if( ch=='x' ) break;
     
     Printf(Con,"#;\n",CharCode(ch));
    }
    
  return true;
 }
 
} // namespace App
 
