/* test3012.Eth.cpp */ 
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
#include <CCore/test/testNet.h>

#include <CCore/inc/dev/DevEth.h>
#include <CCore/inc/net/NanoIPDevice.h>

#include <CCore/inc/dev/AM3359.ETH.h>

namespace App {

namespace Private_3012 {

/* test1() */

uint32 ReadRxPtr()
 {
  using namespace AM3359::ETH;

  BarDesc bar;
  
  return bar.get_HeadRx(0);
 }

uint32 ReadRxControl()
 {
  using namespace AM3359::ETH;
  
  BarDMA bar;

  return bar.get_DMARxControl();
 }

uint32 ReadRxStatus()
 {
  using namespace AM3359::ETH;
  
  BarWR bar;

  return bar.get_WRC0RxStatus();
 }

class Engine : NoCopy
 {
   Dev::EthControl dev;
   
   static const uint16 PhyAddress     =  0 ;
   static const uint16 StatusReg      =  1 ;
   static const uint16 ExtraStatusReg = 31 ;
   
  private:
   
   uint16 read(uint16 reg)
    {
     dev.startMDIORead(PhyAddress,reg);
       
     while( !dev.MDIOReady() );
     
     auto data=dev.MDIOReadData();
     
     if( !data.ack )
       {
        Printf(Exception,"No Ack");
       }
     
     return data.data;
    }
   
  public:
   
   Engine()
    {
     Printf(Con,"address1 = #;\naddress2 = #;\n",dev.getAddress1(),dev.getAddress2());
    }
   
   ~Engine()
    {
    }
   
   void test0()
    {
     for(unsigned phy=0; phy<32 ;phy++)
       {
        dev.startMDIORead(phy,StatusReg);
          
        while( !dev.MDIOReady() );
        
        auto data=dev.MDIOReadData();

        if( data.ack )
          {
           Printf(Con,"Phy = #.h; Status = #.b;\n",phy,data.data);
          
           return;
          }
       }
     
     Printf(Con,"No phy response\n");
    }
   
   void test1()
    {
     uint16 prev_reg1=read(StatusReg);
     uint16 prev_reg2=read(ExtraStatusReg);
     
     Printf(Con,"#.b; #.b;\n",prev_reg1,prev_reg2);
     
     for(;;)
       {
        uint16 reg1=read(StatusReg);
        uint16 reg2=read(ExtraStatusReg);
        
        if( reg1!=prev_reg1 || reg2!=prev_reg2 )
          {
           Printf(Con,"#.b; #.b;\n",reg1,reg2);
          
           prev_reg1=reg1;
           prev_reg2=reg2;
          }
       }
    }
   
   void test2()
    {
     dev.enablePort(Dev::EthFullDuplex);
     
     Dev::EthBuf buf(2,2);
     
     buf.start();
     
     dev.setRx(buf.getRxList());
     
     dev.startRx();
     
     uint32 prev_reg1=ReadRxPtr();
     uint32 prev_reg2=ReadRxControl();

     Printf(Con,"#.h; #.h;\n",prev_reg1,prev_reg2);
     
     for(;;)
       {
        uint32 reg1=ReadRxPtr();
        uint32 reg2=ReadRxControl();
        
        if( reg1!=prev_reg1 || reg2!=prev_reg2 )
          {
           Printf(Con,"#.h; #.h;\n",reg1,reg2);
          
           prev_reg1=reg1;
           prev_reg2=reg2;
           
           if( reg1==0 )
             {
              buf.start();
             
              dev.setRx(buf.getRxList());
             }
          }
       }
    }
 };

void test1()
 {
  Engine engine;
  
  //engine.test0();
  //engine.test1();
  //engine.test2();
 }

void test2()
 {
  Dev::EthDevice eth;
  
  ObjMaster eth_master(eth,"eth");
  
  Net::NanoIPDevice ip("eth",Net::IPAddress(192,168,99,10),Net::IPAddress(255,255,255,0));
  
  Dev::EthDevice::StartStop start_stop(eth,TaskPriority(5000));
  
  for(;;)
    {
     Task::Sleep(30_sec);

     ShowStat(eth,"Eth");
     ShowStat(ip,"IP");
    }
 }

} // namespace Private_3012
 
using namespace Private_3012; 
 
/* Testit<3012> */ 

template<>
const char *const Testit<3012>::Name="Test3012 Eth";

template<>
bool Testit<3012>::Main() 
 {
  //test1();
  test2();
  
  return true;
 }
 
} // namespace App
 
