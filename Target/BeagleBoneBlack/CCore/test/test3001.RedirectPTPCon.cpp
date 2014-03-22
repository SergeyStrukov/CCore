/* test3001.RedirectPTPCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

#include <CCore/inc/net/PTPConDevice.h>

#include <CCore/inc/RedirectPTPCon.h>
#include <CCore/inc/ReadCon.h>
#include <CCore/inc/CmdInput.h>

namespace App {

namespace Private_3001 {

/* class Target */ 

class Target : NoCopy , public CmdInput::Target
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
 
} // namespace Private_3001
 
using namespace Private_3001; 
 
/* Testit<3001> */ 

template<>
const char *const Testit<3001>::Name="Test3001 RedirectPTPCon";

template<>
bool Testit<3001>::Main() 
 { 
  IPEngine ip_engine;
  
  HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  Net::PTPCon::ClientDevice ptp_con("ptp");
  
  ObjMaster ptp_con_master(ptp_con,"ptp_con");
  
  Net::PTPCon::Cfg cfg(Net::PTPCon::TriggerAll);
  
  RedirectPTPCon redirect("ptp_con","test3001",cfg);
  
  for(int i=0; i<1000 ;i++)
    Printf(Con,"--- #4; -----------------------------\n",i);
  
  Test test;
  
  test.run();
  
  return true;
 }
 
} // namespace App
 
