/* test0029.DynArray.cpp */ 
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

namespace Private_0029 {


} // namespace Private_0029
 
using namespace Private_0029; 
 
/* Testit<29> */ 

template<>
const char *const Testit<29>::Name="Test29 DynArray";

template<>
bool Testit<29>::Main() 
 { 
  ReportException report; 
  
  const int buf[]={1,2,3,4,5};
  
  DynArray<int> a;
  
  show(a);
  
  Printf(Con,"#;\n",PrintSet(a.extend_default(2)));
  
  show(a);
  
  a.extend_fill(5,23);
 
  show(a);
  
  Printf(Con,"#;\n",PrintSet(a.extend_copy(5,buf)));
 
  show(a);
  showReverse(a);
  
  DynArray<int> b(DoCopy(6,50),a.getPtr_const());
  
  show(b);
  
  b.append_fill(13);
  
  show(b);
  
  b.shrink_reserve();
  
  show(b);
  
  b.shrink_reserve(10);
  
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
  
  DynArray<int> c{'0','1','2'};
  
  show(c);

  {
   c.apply( [] (int &obj) { obj+=100; } );
  
   show(c);
  } 
  
  {
   int k=0;
  
   c.apply( [&k] (int &obj) { obj+=k++; } );
   
   show(c);
  } 
  
  {
   int k=0;
  
   c.applyReverse( [&k] (int &obj) { obj+=k++; } );
   
   show(c);
  } 
  
  try
    {
     DynArray<X,ArrayAlgo<X,X::Flags> > a;
     
     a.extend_default(5);
    }
  catch(CatchType) {} 
  
  try
    {
     DynArray<X,ArrayAlgo<X,X::Flags> > a(10);
    }
  catch(CatchType) {}
  
  DynArray<DynArray<int> > d{3,3,3};
  
  ulen dn[10];
  
  Range(dn).set(100);
  
  d.extend_cast(10,dn);
  
  for(auto r=Range(d); +r ;++r) Printf(Con,"#;\n",r->getLen());
  
  DynArray<RefArray<int> > e{3,3,3};
  
  ulen en[10];
  
  Range(en).set(100);
  
  e.extend_cast(10,en);
  
  for(auto r=Range(e); +r ;++r) Printf(Con,"#;\n",r->getLen());
  
  return true;
 }
 
} // namespace App
 
