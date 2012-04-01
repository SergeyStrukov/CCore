/* DevIntHandle.cpp */ 
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

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/dev/IXP465.INT.h>

#include <CCore/inc/task/TaskMonitor.h>

#include <__std_init.h>

namespace CCore {
namespace Dev {

/* using */ 

using namespace IXP465;

/* GetPlanInitNode_...() */ 

namespace Private_DevIntHandle {

const INT::Int MapIntSource[Int_TableLen]=
 {
  INT::Int_NPE_A,
  INT::Int_NPE_B,
  INT::Int_NPE_C,

  INT::Int_QMLO,
  INT::Int_QMHI,

  INT::Int_T0,
  INT::Int_T1,

  INT::Int_I2C,

  INT::Int_USBHost,
  INT::Int_USBDev,

  INT::Int_UART1,
  INT::Int_UART0,
  
  INT::Int_PCI,
  INT::Int_PCI_DMA1,
  INT::Int_PCI_DMA2,
  
  INT::Int_GPIO11,
  INT::Int_GPIO10,
  INT::Int_GPIO9,
  INT::Int_GPIO8
 };

class IntTable
 {
   Function<void (void)> table[Int_TableLen];
   
   bool reg_select[Int_TableLen];
   INT::IntBit bit[Int_TableLen];
  
  public:

   IntTable()
    {
     for(ulen i=0; i<Int_TableLen ;i++)
       {
        INT::Int num=MapIntSource[i];
     
        reg_select[i]=bit[i].set(num);
       }
    }
   
   ~IntTable() {}
 
   void set(IntSource intsrc,Function<void (void)> handle_int) { table[intsrc]=handle_int; }
   
   void clear(IntSource intsrc) { set(intsrc,Nothing); }
   
   void enable(IntSource intsrc)
    {
     INT::Bar bar;
     
     if( reg_select[intsrc] )
       {
        bar.get_Enable2()
           .setbit(bit[intsrc])
           .set(bar.to_Enable2());
       }
     else
       {
        bar.get_Enable()
           .setbit(bit[intsrc])
           .set(bar.to_Enable()); 
       }
    }
    
   void disable(IntSource intsrc) 
    {
     INT::Bar bar;
     
     if( reg_select[intsrc] )
       {
        bar.get_Enable2()
           .clearbit(bit[intsrc])
           .set(bar.to_Enable2());
       }
     else
       {
        bar.get_Enable()
           .clearbit(bit[intsrc])
           .set(bar.to_Enable());
       }
    }
    
   void dispatch()
    {
     INT::Bar bar;
     
     auto status=bar.get_IRQStatus();
     auto status2=bar.get_IRQStatus2();
     
     for(ulen i=0; i<Int_TableLen ;i++)
       {
        if( reg_select[i] )
          {
           if( status2.maskbit(bit[i]) ) table[i]();
          }
        else
          {
           if( status.maskbit(bit[i]) ) table[i]();
          }
       }
    }
 };
 
class IntEngine : public IntTable
 {
  public:
  
   IntEngine();
    
   ~IntEngine();
   
   static const char * GetTag() { return "DevIntHandle"; }
 };
 
PlanInitObject<IntEngine> Object CCORE_INITPRI_1 ;

extern "C" {

void IRQ_main()
 {
  TaskMonitor::Internal::BeginInt();
 
  Object->dispatch();
  
  TaskMonitor::Internal::EndInt();
 }
 
} // extern "C"
 
IntEngine::IntEngine()
 {
  INT::Bar bar;

  bar.null_Status()
     .set(bar.to_Enable())
     .set(bar.to_Select());
  
  bar.null_Status2()
     .set(bar.to_Enable2())
     .set(bar.to_Select2());
     
  __std_intsetup(IRQ_main);
 }
    
IntEngine::~IntEngine()
 {
  INT::Bar bar;
  
  bar.null_Status()
     .set(bar.to_Enable());
  
  bar.null_Status2()
     .set(bar.to_Enable2());
  
  __std_intcleanup();
 }
 
} // namespace Private_DevIntHandle
 
using namespace Private_DevIntHandle; 
 
PlanInitNode * GetPlanInitNode_DevIntHandle() { return &Object; }
 
/* functions */ 

void SetupIntHandler(IntSource intsrc,Function<void (void)> handle_int)
 {
  IntLock lock;

  Object->set(intsrc,handle_int);
  
  Object->enable(intsrc);
 }
 
void CleanupIntHandler(IntSource intsrc)
 {
  IntLock lock;

  Object->disable(intsrc);
  
  Object->clear(intsrc);
 }
 
void EnableInt(IntSource intsrc)
 {
  IntLock lock;

  Object->enable(intsrc);
 }
 
void DisableInt(IntSource intsrc)
 {
  IntLock lock;

  Object->disable(intsrc);
 }
 
} // namespace Dev
} // namespace CCore
 

