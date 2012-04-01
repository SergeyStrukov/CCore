/* test1008.MultiSem.cpp */ 
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
#include <CCore/test/testRun.h>

namespace App {

namespace Private_1008 {

/* Take...() */

ulen Take(MultiSemBase &msem) { return msem.take(); }
 
ulen TakeTimed(MultiSemBase &msem) { return msem.take(1_msec); }

/* class Data<TakeFunc> */
  
template <ulen TakeFunc(MultiSemBase &)>
class Data : public Funchor_nocopy
 {
   static const ulen Num = 5    ;
   static const ulen Rep = 1000 ;
   
  private: 
  
   MultiSem<Num+1> msem;
   AntiSem asem;
   ulen total[Num];
   bool wait_flag;
   
  private: 
   
   void take()
    {
     ulen count[Num]={};
     
     ulen timeout_count=0;
     
     for(;;)
       {
        ulen index=TakeFunc(msem);
        
        if( index==0 ) 
          {
           timeout_count++;
           
           continue;
          }
        
        index--;
   
        if( index<Num )
          {
           count[index]++;
           
           asem.dec();
          }
        else
          {
           for(ulen i=0; i<Num ;i++) total[i]+=count[i];
        
           msem.give(Num+1);
           
           if( timeout_count ) Printf(Con,"timeout = #;\n",timeout_count);
         
           return;
          }
       }
    }
   
   void give_loop(ulen index)
    {
     for(ulen rep=Rep; rep ;rep--) 
       {
        msem.give(index+1);
          
        //Task::Sleep(1*tuMSec);
       }
    }
   
   Function<void (void)> function_take() { return FunctionOf(this,&Data::take); }
   
   void stop()
    {
     if( wait_flag ) asem.wait();  
    
     msem.give(Num+1);
    }
    
   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }
   
  public: 

   Data() : msem("TestMSem"),total() { asem.add(Num*Rep); }
  
   void run()
    {
     Data *data=this;
     
     wait_flag=false;
     
     RunTasks run(function_stop());
     
     run(Num,function_take());
     
     for(ulen index=0; index<Num ;index++) run( [=] () -> void { data->give_loop(index); } );
     
     wait_flag=true;
    }
   
   void show(StrLen name)
    {
     Printf(Con,"#; give #;\n\n",name,Num*Rep);
     
     for(ulen i=0; i<Num ;i++) Printf(Con,"total[#;] = #;\n",i,total[i]);
     
     Printf(Con,"\n\n");
    }
 };
 
} // namespace Private_1008
 
using namespace Private_1008; 
 
/* Testit<1008> */ 

template<>
const char *const Testit<1008>::Name="Test1008 MultiSem";

template<>
bool Testit<1008>::Main() 
 { 
  {
   Data<Take> data;
  
   data.run();
  
   data.show("Take");
  } 
 
  {
   Data<TakeTimed> data;
  
   data.run();
  
   data.show("TakeTimed");
  } 
 
  return true;
 }
 
} // namespace App
 
