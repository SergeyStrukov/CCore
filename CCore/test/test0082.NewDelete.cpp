/* test0082.NewDelete.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.04
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/NewDelete.h>
#include <CCore/inc/MemBase.h>

namespace App {

namespace Private_0082 {

/* class Test */

class Test : NoCopy
 {
   int num;
   
  public:
   
   explicit Test(int num_) 
    : num(num_)
    {
     if( num==666 )
       {
        Printf(Exception,"test");
       }
    
     Printf(Con,"Test(#;)\n",num);
    }
   
   ~Test()
    {
     Printf(Con,"~Test(#;)\n",num);
    }
 };

/* struct AllocInit */

struct AllocInit
 {
  public:
  
   AllocInit() {}
   
   typedef AllocInit AllocType;
   
   void * alloc(ulen len)
    {
     Printf(Con,"alloc() : len = #;\n",len);
     
     return MemAlloc(len);
    }
   
   void free(void *mem,ulen len)
    {
     Printf(Con,"free() : len = #;\n",len);
     
     MemFree(mem);
    }
 };

} // namespace Private_0082
 
using namespace Private_0082; 
 
/* Testit<82> */ 

template<>
const char *const Testit<82>::Name="Test82 NewDelete";

template<>
bool Testit<82>::Main() 
 {
  Test *test=New<Test>(AllocInit(),12345);
  
  Delete(AllocInit(),test);
  
  try
    {
     New<Test>(AllocInit(),666);
    }
  catch(CatchType)
    {
     ReportException::Clear();
    }
  
  return true;
 }
 
} // namespace App
 
