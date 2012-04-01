/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/CmdInput.h>

#include <CCore/inc/net/AsyncUDPDevice.h>

#include "ServerProc.h"

namespace App {

/* classes */

struct Options;

class Engine;

/* struct Options */ 

struct Options
 {
  bool exit_on_close;
  
  Options() : exit_on_close(false) {}
  
  bool parse(int argc,const char *argv[])
   {
    if( argc<2 ) return true;
    if( argc>2 ) return false;
    
    StrLen a1(argv[1]);
    
    if( a1.len==1 && a1[0]=='c' )
      {
       exit_on_close=true;
       
       return true;
      }
      
    return false;  
   }
 };
 
/* class Engine */ 

class Engine : public CmdInput::Target
 {
   Net::AsyncUDPMultipointDevice udp;
   
   ObjMaster udp_master;
   
   Net::PTP::ServerDevice ptp;
   
   ObjMaster ptp_master;
   
   Net::AsyncUDPMultipointDevice::StatInfo base_udp_info;
   
   Net::PTP::ServerDevice::StatInfo base_info;
   
   CmdInputCon<ServerProc> cmd_input;
   bool run_flag;
   
  private:

   void clearStat();

   void printStat();
   
   void cmd_nothing(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_stat(StrLen arg);
   void cmd_clear(StrLen arg);
   void cmd_help(StrLen arg);
   
   virtual void buildCmdList(CmdInput &input);
   
  public:

   explicit Engine(bool exit_on_close);

   ~Engine();

   int run();
 };
 
void Engine::clearStat()
 {
  udp.getStat(base_udp_info);
  
  ptp.getStat(base_info);
 }
 
void Engine::printStat()
 {
  Net::PTP::ServerDevice::StatInfo info;
  
  ptp.getStat(info);
  
  info-=base_info;
 
  Net::AsyncUDPMultipointDevice::StatInfo udp_info;
  
  udp.getStat(udp_info);
  
  udp_info-=base_udp_info;
  
  Printf(Con,"\n#15;\n#15;\n",info,udp_info);
 }
 
void Engine::cmd_nothing(StrLen)
 {
 }

void Engine::cmd_exit(StrLen)
 {
  printStat();
  
  run_flag=false;
 }

void Engine::cmd_stat(StrLen)
 {
  printStat();
 }

void Engine::cmd_clear(StrLen)
 {
  clearStat();
 }

void Engine::cmd_help(StrLen)
 {
  Printf(Con,"commands: stat clear help exit\n");
 }

void Engine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&Engine::cmd_nothing);
  addCommand(input,"exit",&Engine::cmd_exit);
  addCommand(input,"stat",&Engine::cmd_stat);
  addCommand(input,"clear",&Engine::cmd_clear);
  addCommand(input,"help",&Engine::cmd_help);
 }
 
Engine::Engine(bool exit_on_close)
 : udp(Net::PTPServerUDPort),
   udp_master(udp,"udp"),
   ptp("udp"),
   ptp_master(ptp,"ptp"),
   cmd_input(*this,"PTPS> ","ptp",exit_on_close)
 {
 }
 
Engine::~Engine()
 {
 }
 
int Engine::run()
 {
  Net::AsyncUDPMultipointDevice::StartStop start_stop(udp);

  for(run_flag=true; run_flag ;) cmd_input.command();
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main(int argc,const char *argv[])
 {
  ReportException report;

  try
    {
     int ret;
     
     {
      Putobj(Con,"--- PTPServer 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");
      
      Options opt;
      
      if( !opt.parse(argc,argv) )
        {
         Putobj(Con,"Usage: PTPServer [c]\n");
           
         return 1;
        }
      
      Engine engine(opt.exit_on_close);

      ret=engine.run();
     } 
 
     report.guard();
     
     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
