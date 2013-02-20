/* test0080.DeferCall-speed.cpp */ 
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

#include <CCore/inc/DeferCall.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_0080 {

/* class Window */

class Window : NoCopy
 {
   unsigned count = 0 ;
   MSecTimer timer;
   
  private:
   
   void put(int,int,int)
    {
     if( (count++)==0 ) timer.reset();
     
     if( count==10000000 )
       {
        auto time=timer.get();
        
        Printf(Con,"time = #; nsec per message\n",time/10);
       
        DeferCallQueue::Stop();
       }
    }
 
  public:
   
   Window() 
    : input(this)
    {
    }
   
   ~Window() 
    {
    }
   
   class Input : DeferInput<Window>
    {
      friend class Window;
    
      explicit Input(Window *window) : DeferInput<Window>(window) {} 
      
      ~Input() {}
      
     public:
    
      void put(int a,int b,int c) { try_post(&Window::put,a,b,c); }
    };
   
   Input input;
 };

/* class Queue */

class Queue : public DeferCallQueue
 {
   Window *window;
   
  public:
  
   Queue() 
    {
     activate();
    }
   
   ~Queue() 
    {
     deactivate();
    }
   
   void set(Window &window_) { window=&window_; }
   
   void forward(TimeScope) override
    {
     for(int a=1; a<=10 ;a++) window->input.put(a,2,3);
    }
 };

} // namespace Private_0080
 
using namespace Private_0080; 
 
/* Testit<80> */ 

template<>
const char *const Testit<80>::Name="Test80 DeferCall-speed";

template<>
bool Testit<80>::Main() 
 {
  Printf(Con,"MaxLen = #;\n",DeferCallHeap::GetMaxLen());
  
  Queue queue;
  
  Window window;
  
  queue.set(window);
  
  Queue::Loop();
  
  return true;
 }
 
} // namespace App
 
