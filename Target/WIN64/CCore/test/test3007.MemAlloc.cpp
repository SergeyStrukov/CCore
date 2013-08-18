/* test3007.MemAlloc.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/MemBase.h>

namespace App {

namespace Private_3007 {


} // namespace Private_3007
 
using namespace Private_3007; 
 
/* Testit<3007> */ 

template<>
const char *const Testit<3007>::Name="Test3007 MemAlloc";

template<>
bool Testit<3007>::Main() 
 {
  for(ulen len=1_MByte; len ;len<<=1)
    {
     Printf(Con,"len = #.h; MB\n",len/1_MByte);
     
     void *ptr=TryMemAlloc(len);
     
     if( !ptr ) 
       {
        Printf(Con,"no memory\n");
       
        return true;
       }
     
     {
      char ch=0;
      
      for(auto r=Range((char *)ptr,len); +r ;++r)
        {
         *r=ch++;
        }
     }
     
     MemFree(ptr);
    }
  
  return true;
 }
 
} // namespace App
 
