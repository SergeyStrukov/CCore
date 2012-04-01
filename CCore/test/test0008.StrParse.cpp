/* test0008.StrParse.cpp */ 
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
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Random.h>

namespace App {

namespace Private_0008 {

/* class Engine */

class Engine : NoCopy
 {
   Random random;
   
  private:
  
   void guard(unsigned num)
    {
     Printf(Exception,"guard #;",num);
    }
   
  public: 
  
   Engine() {}
   
   ~Engine() {}
   
   void test1()
    {
     const uint16 minval=5000u;
     const uint16 maxval=20000u;
    
     uint16 val=random.next16();
     char buf[32];
     PrintBuf out(Range(buf));
     
     Putobj(out,val);
     
     StrLen str=out.close();
     
     //Printf(Con,"str = #;\n",str);
     
     StrParse dev(str);
     
     uint16 ret;
     
     ParseUInt(dev,ret,minval,maxval);
     
     if( val>=minval && val<=maxval )
       {
        if( !dev ) guard(1);
          
        if( ret!=val ) guard(2); 
       }
     else
       {
        if( !!dev ) guard(3);
       }  
    }
    
   void test2()
    {
     const uint16 minval=5000u;
     const uint16 maxval=20000u;
    
     uint16 val=random.next16();
     char buf[32];
     PrintBuf out(Range(buf));
     
     Putobj(out,val);
     
     StrLen str=out.close();
     
     //Printf(Con,"str = #;\n",str);
     
     StrParse dev(str);
     
     uint16 ret;
     
     ParseUInt_empty(dev,ret,0,minval,maxval);
     
     if( val>=minval && val<=maxval )
       {
        if( !dev ) guard(4);
          
        if( ret!=val ) guard(5); 
       }
     else
       {
        if( !!dev ) guard(6);
       }  
    }
 };
 
} // namespace Private_0008
 
using namespace Private_0008; 
 
/* Testit<8> */ 

template<>
const char *const Testit<8>::Name="Test8 StrParse";

template<>
bool Testit<8>::Main() 
 { 
  Engine engine;
  
  for(ulen cnt=100000; cnt ;cnt--) engine.test1();
 
  for(ulen cnt=100000; cnt ;cnt--) engine.test2();
  
  return true;
 }
 
} // namespace App
 
