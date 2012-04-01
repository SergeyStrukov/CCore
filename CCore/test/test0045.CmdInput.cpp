/* test0045.CmdInput.cpp */ 
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

#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>

namespace App {

namespace Private_0045 {

/* class Target */ 

class Target : public NoCopyBase<CmdInput::Target>
 {
   bool run_flag;
 
  private:
  
   void empty(StrLen) {}
  
   void help(StrLen arg) { Printf(Con,"help #.q;\n",arg); }
   
   void stop(StrLen arg) { Printf(Con,"stop #.q;\n",arg); }
   
   void stat(StrLen arg) { Printf(Con,"stat #.q;\n",arg); }
   
   void stat_ip(StrLen arg) { Printf(Con,"stat_ip #.q;\n",arg); }
   
   void exit(StrLen arg) { Printf(Con,"exit #.q;\n",arg); run_flag=false; }
   
   void exec(StrLen arg) { Printf(Con,"exec #.q;\n",arg); }
   
   virtual void buildCmdList(CmdInput &input)
    {
     addCommand(input,"",&Target::empty);
     addCommand(input,"help",&Target::help);
     addCommand(input,"stop",&Target::stop);
     addCommand(input,"stat",&Target::stat);
     addCommand(input,"stat_ip",&Target::stat_ip);
     addCommand(input,"exit",&Target::exit);
     addCommand(input,"exec",&Target::exec);
    }
 
  public:
  
   Target() : run_flag(true) {}
   
   ~Target() {}
   
   bool operator + () const { return run_flag; }
   
   bool operator ! () const { return !run_flag; }
 };
 
/* class Test */  

class Test : NoCopy
 {
   Target target;
   
   CmdInputCon<ReadCon> input;
   
  public: 
  
   Test()
    : input(target,"test> ")
    {
    }
    
   ~Test()
    {
    } 
    
   void run()
    {
     while( +target )
       {
        input.command();
       }
    }  
 };
 
} // namespace Private_0045
 
using namespace Private_0045; 
 
/* Testit<45> */ 

template<>
const char *const Testit<45>::Name="Test45 CmdInput";

template<>
bool Testit<45>::Main() 
 { 
  Test test;
  
  test.run();
 
  return true;
 }
 
} // namespace App
 
