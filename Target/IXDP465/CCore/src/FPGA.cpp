/* FPGA.cpp */ 
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
 
#include <CCore/inc/FPGA.h>
 
#include <CCore/inc/Exception.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

#include <CCore/inc/dev/DevRW.h>

namespace CCore {

#include "FPGA.data"
 
/* functions */ 

static void LoadFPGA()
 {
  const uint8 Prog = 1 ;
  const uint8 Init = 2 ;
  const uint8 Done = 4 ;
 
  Dev::RegRW cpld_reg(0x54000000);
  Dev::RegRW fpga_reg(0x54100000);
  
  cpld_reg.set<uint8>(3,Prog); Task::Sleep(2_msec);
  cpld_reg.set<uint8>(3,   0); Task::Sleep(2_msec);
  
  cpld_reg.set<uint8>(3,Prog); Task::Sleep(2_msec);
  
  bool ok=false;
  
  for(MSecTimer timer; timer.less(1000) ;)
    {
     if( cpld_reg.get<uint8>(3)&Init )
       {
        ok=true;
        
        break;
       }
    }
    
  if( !ok )
    {
     Printf(Exception,"CCore::LoadFPGA() : no init signal");
    }
    
  for(auto r=Range(FPGACode); +r ;++r) fpga_reg.set<uint8>(0,*r);
      
  for(MSecTimer timer; timer.less(1000) ;)
    {
     if( cpld_reg.get<uint8>(3)&Done ) 
       {
        return;
       }
    }
    
  Printf(Exception,"CCore::LoadFPGA() : no done signal");
 }
 
bool InitFPGA()
 {
  Dev::RegRW reg(0x54100000);
  
  reg.set<uint8>(0,8);
  
  if( reg.get<uint8>(1)==128+83 ) return true;
  
  LoadFPGA();
  
  // disconnect all lines
  
  for(unsigned i=0; i<16 ;i++)
    {
     reg.set<uint8>(0,i);
     reg.set<uint8>(1,128+127);
    }
  
  // connect PCI int lines to GPIO lines
  
  reg.set<uint8>(0,8);
  reg.set<uint8>(1,128+83);
  
  reg.set<uint8>(0,9);
  reg.set<uint8>(1,128+82);
  
  reg.set<uint8>(0,10);
  reg.set<uint8>(1,128+81);
  
  reg.set<uint8>(0,11);
  reg.set<uint8>(1,128+80);

  return false;
 }
 
} // namespace CCore
 

