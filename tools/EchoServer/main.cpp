/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: EchoServer 1.00
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
#include <CCore/inc/net/EchoDevice.h>

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
   
   Net::EchoDevice echo;
 
   Net::EchoDevice::StatInfo base_info;
   uint64 base_traffic;
   
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
  echo.getStat(base_info);
  
  base_traffic=echo.getTraffic();
 }
 
void Engine::printStat()
 {
  Net::EchoDevice::StatInfo info;
  
  echo.getStat(info);
  
  info-=base_info;
 
  Printf(Con,"\n#15;\n#15; = #;\n\n",info,"traffic",echo.getTraffic()-base_traffic);
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
 : udp(Net::EchoUDPort),
   udp_master(udp,"udp"),
   echo("udp"),
   base_traffic(0),
   cmd_input(*this,"ECHO> ")
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
      Putobj(Con,"--- EchoServer 1.00 ---\n--- Copyright (c) 2010 Sergey Strukov. All rights reserved. ---\n\n");
      
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
 
