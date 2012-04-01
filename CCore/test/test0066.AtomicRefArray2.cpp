/* test0066.AtomicRefArray2.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0066 {

/* class Engine */

class Engine : public Funchor_nocopy
 {
   typedef AtomicRefArray<unsigned> Array;
  
   Mutex mutex;
   
   Array shared;
   
   PrintFile out;
   
  private:
   
   Array get()
    {
     Mutex::Lock lock(mutex);
     
     return shared;
    }
   
   void put(const Array &a)
    {
     Mutex::Lock lock(mutex);
     
     shared=a;
     
     Printf(out,"#;\n",a.getLen());
    }
   
   void task()
    {
     Random random;
     
     for(ulen cnt=1000000; cnt ;cnt--)
       switch( random.select(10) )
         {
          case 0 :
           {
            auto a=get();

            a.extend_fill(100,666);
            
            if( a.getLen()<10000 ) 
              {
               put(a);
              }
            else
              {
               Array a(500);
               
               put(a);
              }
           }
          break;
          
          case 1 :
           {
            auto a=get();

            a.shrink(10);
            
            put(a);
           }
          break;
          
          default:
           {
            auto a=get();
            
            unsigned sum=0;
            
            for(unsigned x : a) sum+=x;
            
            a.append_copy(sum);
            
            put(a);
           }
         }
    }
   
   Function<void (void)> function_task() { return FunctionOf(this,&Engine::task); }
  
  public: 
   
   Engine() : out("test0066.txt") {}
   
   ~Engine() {}
   
   void run(ulen count)
    {
     RunTasks run;
     
     run(count,function_task());
    }
 };

} // namespace Private_0066
 
using namespace Private_0066; 
 
/* Testit<66> */ 

template<>
const char *const Testit<66>::Name="Test66 AtomicRefArray2";

template<>
bool Testit<66>::Main() 
 {
  Engine engine;
  
  engine.run(10);
  
  return true;
 }
 
} // namespace App
 
