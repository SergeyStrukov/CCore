/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

#include <CCore/inc/net/PTPConDevice.h>

#include <CCore/inc/RedirectPTPCon.h>

namespace App {

int main2();

} // namespace App
 
/* main() */ 

int main()
 {
  using namespace App;

  int ret;
  
  try
    {
     ReportException report;
     
     {
      IPEngine ip_engine;
  
      HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
      Net::PTPCon::ClientDevice ptp_con("ptp");
     
      ObjMaster ptp_con_master(ptp_con,"ptp_con");
      
      Net::PTPCon::Cfg cfg(Net::PTPCon::TriggerAll);
  
      RedirectPTPCon redirect("ptp_con","test",cfg);

      ret=main2();
     }
 
     report.guard();
    }
  catch(CatchType)
    {
     return 1;
    }

  return ret;
 }
 
