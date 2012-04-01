/* test1023.DDLEngine.cpp */ 
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/String.h>
#include <CCore/inc/OwnPtr.h>

#include <CCore/inc/ddl/DDLEngine.h>

namespace App {

namespace Private_1023 {

/* type Engine */

typedef DDL::FileEngine<DDL::FileName,FileToMem> Engine;

/* class Test */

class Test : NoCopy
 {
   PrintFile out;
   OwnPtr<Engine> engine;
   
  public:
   
   Test(StrLen file_name)
    : out(file_name),
      engine(new Engine(out))
    {
    }
   
   ~Test()
    {
    }
   
   void operator () (StrLen src_file_name)
    {
     Printf(out,"/* #; */\n\n",src_file_name);
     
     auto result=engine->process(src_file_name);
     
     if( !result )
       {
        Putobj(out,"\n\n");
       }
     else
       {
        Printf(out,"/* result */\n\n#;\n\n",*result.eval);
       }
    }
 };

/* test() */

static void test(StrLen file_name,StrLen src_file_name)
 {
  Test test(file_name);
  
  test(src_file_name);
 }

static void test(StrLen name)
 {
  String file_name=StringCat(name,".txt");
  String src_file_name=StringCat("../../../HCore/files/",name,".ddl");
  
  test(Range(file_name),Range(src_file_name));
 }

} // namespace Private_1023
 
using namespace Private_1023; 
 
/* Testit<1023> */ 

template<>
const char *const Testit<1023>::Name="Test1023 DDLEngine";

template<>
bool Testit<1023>::Main() 
 {
  test("sample");
  
  return true;
 }
 
} // namespace App
 
