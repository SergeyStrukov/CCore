/* test0067.BinarySearch.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.03
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/algon/BinarySearch.h>

namespace App {

namespace Private_0067 {


} // namespace Private_0067
 
using namespace Private_0067; 
 
/* Testit<67> */ 

template<>
const char *const Testit<67>::Name="Test67 BinarySearch";

template<>
bool Testit<67>::Main() 
 {
  const int Len = 10 ;
  
  int buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i]=i;
  
  for(int i=0; i<=Len ;i++)
    { 
     PtrLen<int> r=Range(buf);
  
     Algon::BinarySearch_greater_or_equal(r,i);
     
     Printf(Con,"i = #; , found ",i);
     
     if( +r ) Printf(Con,"#;\n",*r); else Printf(Con,"none\n"); 
    }   
  
  return true;
 }
 
} // namespace App
 
