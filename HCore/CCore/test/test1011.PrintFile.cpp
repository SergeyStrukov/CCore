/* test1011.PrintFile.cpp */ 
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

namespace App {

namespace Private_1011 {


} // namespace Private_1011
 
using namespace Private_1011; 
 
/* Testit<1011> */ 

template<>
const char *const Testit<1011>::Name="Test1011 PrintFile";

template<>
bool Testit<1011>::Main() 
 { 
  PrintFile out("testPrintFile.txt",Open_ToWrite|Open_AutoDelete);
  
  for(ulen i=0; i<100000 ;i++)
    Printf(out,"--- Line #10l; -----------------------------------\n",i);
  
  out.preserveFile();
  
  out.close();
 
  return true;
 }
 
} // namespace App
 
