/* test1009.MultiEvent.cpp */ 
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

namespace Private_1009 {

/* Wait...() */

ulen Wait(MultiEventBase &mev) { return mev.wait(); }
 
ulen WaitTimed(MultiEventBase &mev) { return mev.wait(1_msec); }

/* class Data<WaitFunc> */
  
template <ulen WaitFunc(MultiEventBase &)>
class Data : public Funchor_nocopy
 {
   static const ulen Num = 5    ;
   static const ulen Rep = 100000 ;
   
  private: 
  
   MultiEvent<Num+1> mev;
   AntiSem asem;
   ulen total[Num];
   bool wait_flag;
   
  private:
   
   void wait()
    {
     ulen count[Num]={};
     
     ulen timeout_count=0;
     
     for(;;)
       {
        ulen index=WaitFunc(mev);
        
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
        
           mev.trigger(Num+1);
           
           if( timeout_count ) Printf(Con,"timeout = #;\n",timeout_count);
         
           return;
          }
       }
    }
   
   void trigger_loop(ulen index)
    {
     for(ulen rep=Rep; rep ;rep--) 
       {
        asem.inc();
          
        if( !mev.trigger(index+1) ) asem.dec();
          
        //Task::Sleep(1*tuMSec);
       }
    }
   
   Function<void (void)> function_wait() { return FunctionOf(this,&Data::wait); }

   void stop()
    {
     if( wait_flag ) asem.wait();
    
     mev.trigger(Num+1);
    }
   
   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }
   
  public: 

   Data() : mev("TestMev"),total() {}
  
   void run()
    {
     Data *data=this;
     
     wait_flag=false;
     
     RunTasks run_wait(function_stop());
     
     run_wait(Num,function_wait());
     
     RunTasks run_trigger;
     
     for(ulen index=0; index<Num ;index++) run_trigger( [=] () -> void { data->trigger_loop(index); } );
     
     wait_flag=true;  
    }
    
   void show(StrLen name)
    {
     Printf(Con,"#; give #;\n\n",name,Num*Rep);
     
     for(ulen i=0; i<Num ;i++) Printf(Con,"total[#;] = #;\n",i,total[i]);
     
     Printf(Con,"\n\n");
    }
 };
 
} // namespace Private_1009
 
using namespace Private_1009; 
 
/* Testit<1009> */ 

template<>
const char *const Testit<1009>::Name="Test1009 MultiEvent";

template<>
bool Testit<1009>::Main() 
 { 
  {
   Data<Wait> data;
  
   data.run();
  
   data.show("Wait");
  } 
 
  {
   Data<WaitTimed> data;
  
   data.run();
  
   data.show("WaitTimed");
  } 
  
  return true;
 }
 
} // namespace App
 
