/* test0041.String.cpp */ 
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

#include <CCore/inc/String.h>

namespace App {

namespace Private_0041 {


} // namespace Private_0041
 
using namespace Private_0041; 
 
/* Testit<41> */ 

template<>
const char *const Testit<41>::Name="Test41 String";

template<>
bool Testit<41>::Main() 
 { 
  ReportException report;
  
  String a("string_a");
  String b("string_b");
  String c("string_c");
  
  Printf(Con,"a = #;\n",a);
  Printf(Con,"b = #;\n",b);
  Printf(Con,"c = #;\n\n",c);
  
  a=b;
  b=c;
 
  Printf(Con,"a = #20l;\n",a);
  Printf(Con,"b = #20r;\n",b);
  Printf(Con,"c = #20c;\n\n",c);
  
  Printf(Con,"a+b = #;\n",a+b);
  Printf(Con,"a+\" XXX\" = #;\n",a+" XXX");
  
  Printf(Con,"#;\n",StringCat(c," cat ",1000));
  
  Printf(Con,"#;\n",Stringf("a = #; b = #;",100,200));
  
  PrintString out(50000);
  
  for(ulen i=0; i<1000 ;i++) Printf(out,"------------------ #; ----------------------\n",i);
  
  Putobj(Con,out.close());
  
  for(ulen i=5000; i<6000 ;i++) Printf(out,"------------------ #; ----------------------\n",i);
  
  try { Putobj(Con,out.close()); } catch(CatchType) {}
  
  return true;
 }
 
} // namespace App
 
