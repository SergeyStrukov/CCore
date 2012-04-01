/* test1018.AsyncFile.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/String.h>
#include <CCore/inc/Timer.h>

#include <CCore/inc/AsyncFileDevice.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/AsyncFileToMem.h>

namespace App {

namespace Private_1018 {

/* consts */

const unsigned LineCount = 1000000 ;
const unsigned FileCount = 10 ;

/* FillFile() */

template <class P>
void FillFile(P &out)
 {
  for(unsigned line=1; line<=LineCount ;line++)
    Printf(out,"--- #7; ---------------------------\n",line);
 }

/* class ATask */

class ATask
 {
   unsigned ind;
   MSec timeout;
  
  public:
   
   ATask(unsigned ind_,MSec timeout_=DefaultTimeout) : ind(ind_),timeout(timeout_) {}
   
   String buildName() const { return Stringf("host:atest#;.txt",ind); }
   
   void operator () ()
    {
     String name=buildName();
     PrintAsyncFile out(Range(name),Open_ToWrite,timeout);
     
     //out.setLargeWriteLen(256*KByte);
        
     FillFile(out);
     
     Printf(Con,"#; done\n",name);
    }
 };

/* class STask */

class STask
 {
   unsigned ind;
  
  public:
   
   explicit STask(unsigned ind_) : ind(ind_) {}
   
   String buildName() const { return Stringf("test#;.txt",ind); }
   
   void operator () ()
    {
     String name=buildName();
     PrintFile out(Range(name));
        
     FillFile(out);
     
     Printf(Con,"#; done\n",name);
    }
 };

/* class AEngine */

class AEngine : NoCopy
 {
   SecTimer timer;
   MSec timeout;
  
  public:
   
   explicit AEngine(MSec timeout_=DefaultTimeout) : timeout(timeout_) {}
   
   ~AEngine() 
    { 
     Printf(Con,"\natime = #; sec\n\n",timer.get());
    }
   
   void run()
    {
     RunTasks run;
     
     for(unsigned i=1; i<=FileCount ;i++) run(ATask(i,timeout));
    }
 };

/* class SEngine */

class SEngine : NoCopy
 {
   SecTimer timer; 
  
  public:
   
   SEngine() {}
   
   ~SEngine() 
    { 
     Printf(Con,"\nstime = #; sec\n\n",timer.get());
    }
   
   void run()
    {
     RunTasks run;
     
     for(unsigned i=1; i<=FileCount ;i++) run(STask(i));
    }
 };

} // namespace Private_1018
 
using namespace Private_1018; 
 
/* Testit<1018> */ 

template<>
const char *const Testit<1018>::Name="Test1018 AsyncFile";

template<>
bool Testit<1018>::Main() 
 {
  AsyncFileDevice af;
  
  ObjMaster af_master(af,"host");
  
#if 1

  {
   AEngine aengine;
  
   aengine.run();
  }
  
  {
   SEngine sengine;
  
   sengine.run();
  }
  
  {
   for(unsigned i=1; i<=FileCount ;i++)
     {
      String aname=ATask(i).buildName();
      String sname=STask(i).buildName();
      
      FileToMem sfile(Range(sname));
      AsyncFileToMem afile(Range(aname));
      
      if( !Range(sfile).equal(Range(afile)) )
        {
         Printf(Con,"difference #;\n",i);
         
         return false;
        }
     }
   
   Printf(Con,"match\n");
  }
  
  {
   String aname=ATask(1).buildName();
   
   PacketRead read(Range(aname));
   
   Putobj(Con,read);
  }
  
#else
  
  {
   AEngine aengine(10*tuMSec);
  
   aengine.run();
  }
  
#endif  
  
  return true;
 }
 
} // namespace App
 
