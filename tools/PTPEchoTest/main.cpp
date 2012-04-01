/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: PTPEchoTest 1.00
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
#include <CCore/inc/ReadCon.h>

#include <CCore/inc/net/UDPDevice.h>
#include <CCore/inc/net/PTPEchoTest.h>

namespace App {

/* using */ 

using namespace CCore;

/* classes */

class Engine;

/* class Engine */ 

class Engine : public CmdInput::Target
 {
   Net::UDPMultipointDevice udp;
   
   ObjMaster udp_master;
   
   Net::PTP::ServerDevice ptp;
   
   ObjMaster ptp_master;

   Net::PTP::EchoTest echo;
   
   Net::UDPMultipointDevice::StatInfo base_udp_info;
   Net::PTP::ServerDevice::StatInfo base_info;
   
   CmdInputCon<ReadCon> cmd_input;
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

   Engine();

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
  Net::UDPMultipointDevice::StatInfo udp_info;
  
  udp.getStat(udp_info);
  
  udp_info-=base_udp_info;
  
  Net::PTP::ServerDevice::StatInfo info;
  
  ptp.getStat(info);
  
  info-=base_info;
 
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
  Putobj(Con,"commands: stat clear help exit\n");
 }

void Engine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&Engine::cmd_nothing);
  addCommand(input,"exit",&Engine::cmd_exit);
  addCommand(input,"stat",&Engine::cmd_stat);
  addCommand(input,"clear",&Engine::cmd_clear);
  addCommand(input,"help",&Engine::cmd_help);
 }
 
Engine::Engine()
 : udp(Net::PTPServerUDPort),
   udp_master(udp,"udp"),
   ptp("udp"),
   ptp_master(ptp,"ptp"),
   echo("ptp"),
   cmd_input(*this,"PTP-ECHO> ")
 {
 }
 
Engine::~Engine()
 {
 }
 
int Engine::run()
 {
  Net::UDPMultipointDevice::StartStop start_stop(udp);

  for(run_flag=true; run_flag ;) cmd_input.command();
  
  return 0;
 }
 
} // namespace App
 
/* main() */ 

using namespace App;

int main()
 {
  ReportException report;
  
  try
    {
     int ret;
     
     {
      Putobj(Con,"--- PTPEchoTest 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");
      
      Engine engine;

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
 
