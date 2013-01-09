/* test0030.RefArray.cpp */ 
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
#include <CCore/test/testArray.h>

namespace App {

namespace Private_0030 {


} // namespace Private_0030
 
using namespace Private_0030; 
 
/* Testit<30> */ 

template<>
const char *const Testit<30>::Name="Test30 RefArray";

template<>
bool Testit<30>::Main() 
 { 
  ReportException report; 
  
  const int buf[]={1,2,3,4,5};
  
  RefArray<int> a;
  
  show(a);
  
  a.extend_default(2);
  
  show(a);
  
  a.extend_fill(5,23);
 
  show(a);
  
  a.extend_copy(5,buf);
 
  show(a);
  
  RefArray<int> b(DoCopy(6,50),a.getPtr_const());
  
  show(b);
  
  b.append_fill(13);
  
  show(b);
  
  b.shrink_extra();
  
  show(b);
  
  Printf(Con,"delta = #;\n",b.shrink_one());
  
  show(b);
  
  Printf(Con,"delta = #;\n",b.shrink(3));
  
  show(b);
  
  Printf(Con,"delta = #;\n",b.shrink_all());
  
  show(b);
  
  b.shrink_extra();
  
  show(b);
  
  RefArray<int> c{'0','1','2'};
  
  show(c);
  
  {
   c.apply_modify( [] (int &obj) { obj+=100; } );
  
   show(c);
  } 
  
  {
   int k=0;
   
   c.apply_modify( [&k] (int &obj) { obj+=k++; } );
  
   show(c);
  } 
  
  {
   int k=0;
   
   c.applyReverse_modify( [&k] (int &obj) { obj+=k++; } );
  
   show(c);
  } 
  
  try
    {
     RefArray<X,ArrayAlgo<X,X::Flags> > a;
     
     a.extend_default(5);
    }
  catch(CatchType) {} 
  
  try
    {
     RefArray<X,ArrayAlgo<X,X::Flags> > a(10);
    }
  catch(CatchType) {} 

  return true;
 }
 
} // namespace App
 
