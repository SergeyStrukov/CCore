/* test0046.Printf.cpp */ 
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

#include <CCore/inc/PrintTitle.h>

namespace App {

namespace Private_0046 {

/* class Test */

class Test : NoCopy
 {
   int val;
   
  public:
   
   Test() : val(54321) {}
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#.h;",val);
    }
 };
 
} // namespace Private_0046
 
using namespace Private_0046; 
 
/* Testit<46> */ 

template<>
const char *const Testit<46>::Name="Test46 Printf";

template<>
bool Testit<46>::Main() 
 { 
  Printf(Con,"#;\n",PrintTitle(12345));
  
  Test test;
  
  Printf(Con,"#;\n",PrintTitle(test));
  
  Printf(Con,"\n#;\n\n",TextDivider());
  
  Printf(Con,"#;\n",100_msec);
  Printf(Con,"#;\n",2345_msec);
  Printf(Con,"#;\n",100_msec+100_sec);
  Printf(Con,"#;\n",100_msec+5_sec+10_min);
  
  Printf(Con,"\n#;\n\n",TextDivider());
  
  Printf(Con,"--- #10l; ---\n",12345);
  Printf(Con,"--- #10i; ---\n",12345);
  Printf(Con,"--- #10r; ---\n",12345);
  Printf(Con,"--- #+10.5l; ---\n",12345);
  Printf(Con,"--- #+10.hi; ---\n",12345);
  Printf(Con,"--- #10.hi; ---\n",-12345);
  
  Printf(Con,"\n#;\n\n",TextDivider());
  
  return true;
 }
 
} // namespace App
 
