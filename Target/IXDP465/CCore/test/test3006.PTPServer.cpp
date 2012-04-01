/* test3006.PTPServer.cpp */ 
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

#include <CCore/inc/LineInput.h>

#include <CCore/inc/net/PTPSupport.h>

namespace App {

namespace Private_3006 {

/* class Engine */  

class Engine : NoCopy
 {
   Net::NanoUDPEndpointDevice udp;
   
   ObjMaster udp_master;
 
   Net::PTP::ClientDevice ptp;
   PacketSet<uint8> pset;
   
   ObjMaster ptp_master;
   
   struct Fill
    {
     uint8 first;
     ulen len;
     
     Fill(uint8 first_,ulen len_) : first(first_),len(len_) {}
     
     ulen getLen() const { return len; }
     
     void fill(PtrLen<uint8> r) const
      {
       for(uint8 b=first; +r ;++r,++b) *r=b;
      }
    };
    
  private: 
  
   void exist(Net::PTP::ServiceIdType service_id,Net::PTP::FunctionIdType function_id)
    {
     Net::PTP::Support_Exist exist(&ptp,pset);
      
     exist.perform(TimeScope(10_sec),service_id,function_id);
      
     Printf(Con,"exist(#;,#;) = #;\n",service_id,function_id,exist.getResult());
    }
    
   void error_desc(Net::PTP::ServiceIdType service_id,
                   Net::PTP::FunctionIdType function_id,
                   Net::PTP::ErrorIdType error_id) 
    {
     Net::PTP::Support_ErrorDesc desc(&ptp,pset);
     
     desc.perform(TimeScope(10_sec),service_id,function_id,error_id);
     
     Printf(Con,"desc(#;,#;,#;) = #;\n",service_id,function_id,error_id,desc.getDesc());
    }               
    
   void seed()
    {
     Net::PTP::Support_Seed seed(&ptp,pset);
      
     seed.perform_guarded(TimeScope(10_sec));
      
     Printf(Con,"seed1 = #16.16i; seed2 = #16.16i;\n",seed.getSeed1(),seed.getSeed2());
    }
    
   void echo(uint8 first,ulen len,uint32 delay_msec)
    {
     Net::PTP::Support_Echo echo(&ptp,pset);
     
     Fill fill(first,len);
      
     echo.perform_guarded(TimeScope(2500_msec),delay_msec,fill);
      
     Printf(Con,"#;\n\n",PrintDump(echo.getEcho()));
    }
   
  public:
  
   explicit Engine(Net::UDPoint dst)
    : udp("IP",Net::PTPClientUDPort,false,dst),
      udp_master(udp,"udp"),
      ptp("udp"),
      pset(10),
      ptp_master(ptp,"ptp")
    {
    }
    
   ~Engine()
    {
    } 
    
   void run()
    {
     ptp.support_guarded(10_sec);
     
     Printf(Con,"max in  = #;\nmax out = #;\n",ptp.getMaxInboundInfoLen(),ptp.getMaxOutboundInfoLen());
     
#if 1     
     
     exist(1,1);
     exist(1,10);
     exist(2,1);
     exist(3,1);
     
     error_desc(0,0,1);
     error_desc(0,0,2);
     error_desc(0,0,100);
     
     seed();
     
     echo(10,20,1000);
     echo(20,20,2000);
     //echo(30,20,3000);
     
#endif     
     
     // PTPCon
     
     Net::PTPCon::ClientDevice con_device("ptp");
   
     ObjMaster con_master(con_device,"con");
     
     Net::PTPCon::Cfg cfg(Net::PTPCon::TriggerAll);
     
     PTPConOpenClose con_openclose("con","test3006",cfg);
   
     PrintPTPCon con("con");
     
     LineInput<ReadPTPCon> line(con_openclose);
     
     for(;;)
       {
        PtrLen<const char> cmd;
        
        if( !line.get(TimeScope(10_sec),cmd) )
          {
           Printf(Con,"input timeout\n");
          
           continue;
          }
        
        if( cmd.equal(StrLen("exit")) )
          {
           break;
          }
        else if( cmd.equal(StrLen("print")) )  
          {
           for(ulen cnt=1000; cnt ;cnt--)
             {
              Printf(con,"--------------------------- cnt = #; -------------------------------\n",cnt);
             }
       
           con.flush();  
          }
        else
          {
           Printf(con,"\"#;\"\n",StrLen(cmd));
           
           con.flush();
          }  
       }
       
     Task::Sleep(1_sec);
    } 
    
   void showStat()
    {
     ShowStat(ptp,"PTP client");
    } 
 };
 
} // namespace Private_3006
 
using namespace Private_3006; 
 
/* Testit<3006> */ 

template<>
const char *const Testit<3006>::Name="Test3006 PTPServer";

template<>
bool Testit<3006>::Main() 
 { 
  IPEngine ip_engine;
  
  Engine engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  engine.run();
  
  engine.showStat();
  
  ip_engine.showStat();
  
  return true;
 }
 
} // namespace App
 
