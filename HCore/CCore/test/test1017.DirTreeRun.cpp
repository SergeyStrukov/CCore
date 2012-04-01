/* test1017.DirTreeRun.cpp */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/ElementPool.h>

namespace App {

namespace Private_1017 {

/* class Proc */

class Proc : NoCopy
 {
   PrintFile out;
   ulen off;
   
   ElementPool pool;
   int next;
   
  private:
   
   int getNext() { return next++; }
  
  public:
   
   Proc() : out("test1017.txt"),off(0),next(0) {}
   
   ~Proc() {}
   
   typedef int DataType;
   
   DataType * dir(StrLen root)
    {
     Printf(out,"path = #;\ndir = .\n",root);
     
     off=3;
     
     return pool.create<int>(getNext());
    }
   
   DataType * dir(StrLen path,StrLen name,DataType *parent)
    {
     RepeatChar rep(off,' ');
     
     Printf(out,"#;path = #;\n#;number = #;\n#;dir = #;\n",rep,path,rep,*parent,rep,name);
     
     off+=3;
     
     return pool.create<int>(getNext());
    }
   
   void file(StrLen path,StrLen name,DataType *parent)
    {
     RepeatChar rep(off,' ');
     
     Printf(out,"#;path = #;\n#;number = #;\n#;file = #;\n#;-----\n",rep,path,rep,*parent,rep,name,rep);
    }
   
   void enddir(StrLen path,StrLen name,DataType *parent)
    {
     off-=3;
     
     RepeatChar rep(off,' ');
     
     Printf(out,"#;path = #;\n#;enddir = #;\n#;number = #;\n#;=====\n",rep,path,rep,name,rep,*parent,rep);
    }
 };

} // namespace Private_1017
 
using namespace Private_1017; 
 
/* Testit<1017> */ 

template<>
const char *const Testit<1017>::Name="Test1017 DirTreeRun";

template<>
bool Testit<1017>::Main() 
 {
  Proc proc;
  DirTreeRun run("../CCore");
  
  run.apply(proc);
  
  return true;
 }
 
} // namespace App
 
