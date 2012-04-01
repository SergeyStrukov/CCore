/* test0035.DynArray2.cpp */ 
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

namespace Private_0035 {

/* struct SqList */

struct SqList
 {
  int i;
 
  explicit SqList(int i_) : i(i_) {}
  
  int * operator () (Place<void> place)
   {
    int v=i*i;
    
    i++;
   
    return new(place) int(v);
   }
 };
 
/* struct OddList */

struct OddList
 {
  int i,n;
 
  OddList(int i_,int n_) : i(i_),n(n_) {}
  
  ulen getLen() const { return n; }
  
  PtrLen<int> operator () (Place<void> place)
   {
    int *base=place;
    int *ptr=base;
    
    for(int v=i; v<i+n ;v++) if( v&1 ) *(ptr++)=v;
    
    return Range(base,ptr);
   }
 };
 
/* functions */

void test1()
 {
  DynArray<int> a{1,2,3,4,5};
  
  show(a);
  
  Printf(Con,"len = #; , ",a.getLen());
  
  for(ulen i=0; i<a.getLen() ;i++) Printf(Con," #;",a[i]);
  
  Printf(Con,"\n\n");
 };
 
void test2()
 {
  DynArray<int> a;
  
  a.extend_default(3); show(a);
  
  a.extend_fill(3,1); show(a);
  
  const int buf[3]={2,3,4};
  
  a.extend_copy(3,buf); show(a);
  
  int sbuf[3]={5,6,7};
  
  a.extend_swap(3,sbuf); show(a);
  
  a.extend(3,SqList(7)); show(a);
  
  a.extend(OddList(10,10)); show(a);
 } 
 
} // namespace Private_0035
 
using namespace Private_0035; 
 
/* Testit<35> */ 

template<>
const char *const Testit<35>::Name="Test35 DynArray2";

template<>
bool Testit<35>::Main() 
 { 
  test1();
  test2();
 
  return true;
 }
 
} // namespace App
 
