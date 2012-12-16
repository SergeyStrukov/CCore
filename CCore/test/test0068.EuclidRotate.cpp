/* test0068.EuclidRotate.cpp */ 
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

#include <CCore/inc/algon/EuclidRotate.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_0068 {


} // namespace Private_0068
 
using namespace Private_0068; 
 
/* Testit<68> */ 

template<>
const char *const Testit<68>::Name="Test68 EuclidRotate";

template<>
bool Testit<68>::Main() 
 {
  const int Len = 10 ;
  
  int buf[Len];
  
  for(int i=0; i<Len ;i++) buf[i]=i;
  
  for(ulen len=0; len<=(ulen)Len ;len++)
    {
     PtrLen<int> r=Range(buf);
     
     Algon::EuclidRotate_prefix(r,len);
     
     Printf(Con,"#;\n",PrintSet(r));
     
     Algon::EuclidRotate_suffix(r,len);
     
     Printf(Con,"#;\n\n",PrintSet(r));
    }
  
  return true;
 }
 
} // namespace App
 
