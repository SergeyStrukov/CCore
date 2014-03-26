/* DevIntHandle.cpp */ 
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

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/task/TaskMonitor.h>
#include <CCore/inc/task/TaskEvent.h>

#include <__std_init.h>

#include <CCore/inc/dev/AM3359.INTC.h>

namespace CCore {
namespace Dev {

/* GetPlanInitNode_...() */ 

namespace Private_DevIntHandle {

class IntTable : NoCopy
 {
   Function<void (void)> table[Int_TableLen];
   
   static uint32 Bank(uint32 int_source) { return int_source>>5; }
   
   static uint32 Bit(uint32 int_source) { return uint32(1)<<(int_source&31); }
   
  public:
 
   IntTable()
    {
    }
   
   ~IntTable()
    {
    }
   
   void set(uint32 int_source,Function<void (void)> handle_int,unsigned priority)
    {
     AM3359::INTC::Bar intc;
     
     intc.null_TypePriorityCfg().set_Priority(priority).set(intc.to_TypePriorityCfg(int_source));
     
     table[int_source]=handle_int;
    }
   
   void clear(uint32 int_source)
    {
     table[int_source]=Nothing;
    }
   
   void enable(uint32 int_source)
    {
     AM3359::INTC::Bar intc;
     
     switch( Bank(int_source) )
       {
        case 0 : intc.set_ClearMask0(Bit(int_source)); break; 
        case 1 : intc.set_ClearMask1(Bit(int_source)); break; 
        case 2 : intc.set_ClearMask2(Bit(int_source)); break; 
        case 3 : intc.set_ClearMask3(Bit(int_source)); break; 
       }
    }
   
   void disable(uint32 int_source)
    {
     AM3359::INTC::Bar intc;
     
     switch( Bank(int_source) )
       {
        case 0 : intc.set_SetMask0(Bit(int_source)); break; 
        case 1 : intc.set_SetMask1(Bit(int_source)); break; 
        case 2 : intc.set_SetMask2(Bit(int_source)); break; 
        case 3 : intc.set_SetMask3(Bit(int_source)); break; 
       }
    }
   
   void dispatch(uint32 int_source)
    {
     table[int_source]();
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
  using namespace AM3359::INTC;
  
  TaskEventHost.add<TaskSwitchEvent>(TaskNumber::EnterInt);
  
  TaskMonitor::Internal::BeginInt();
  
  Bar intc;
 
  Object->dispatch(intc.get_ActiveIRQ().get_Number());
  
  intc.null_NextActive().setbit(NextActive_IRQ).setTo(intc);
  
  TaskMonitor::Internal::EndInt();
  
  TaskEventHost.add<TaskSwitchEvent>(TaskNumber::LeaveInt);
 }
 
} // extern "C"

IntEngine::IntEngine()
 {
  using namespace AM3359::INTC;
  
  Bar intc;
  
  intc.null_SysConfig().setbit(SysConfig_Reset).setTo(intc);
  
  while( intc.get_SysStatus().maskbit(SysStatus_ResetDone)==0 );
  
  intc.null_Protection().setbit(Protection_Enable).setTo(intc);
  
  intc.null_Idle().setbit(Idle_Func).setTo(intc);
  
  intc.null_PriorityMask().set_Threshold(0xFF).setTo(intc);
  
  intc.set_SetMask0_ones();
  intc.set_SetMask1_ones();
  intc.set_SetMask2_ones();
  intc.set_SetMask3_ones();
  
  for(uint32 ind=0; ind<128 ;ind++)
    intc.null_TypePriorityCfg().set(intc.to_TypePriorityCfg(ind));
  
  __std_intsetup(IRQ_main);
 }
 
IntEngine::~IntEngine()
 {
  AM3359::INTC::Bar intc;
  
  intc.set_SetMask0_ones();
  intc.set_SetMask1_ones();
  intc.set_SetMask2_ones();
  intc.set_SetMask3_ones();
  
  __std_intcleanup();
 }

} // namespace Private_DevIntHandle
 
using namespace Private_DevIntHandle;

PlanInitNode * GetPlanInitNode_DevIntHandle() { return &Object; }

/* functions */ 

void SetupIntHandler(IntSource int_source,Function<void (void)> handle_int,unsigned priority)
 {
  IntLock lock;

  Object->set(int_source,handle_int,priority);
  
  Object->enable(int_source);
 }

void CleanupIntHandler(IntSource int_source)
 {
  IntLock lock;

  Object->disable(int_source);
  
  Object->clear(int_source);
 }

void EnableInt(IntSource int_source)
 {
  IntLock lock;

  Object->enable(int_source);
 }

void DisableInt(IntSource int_source)
 {
  IntLock lock;

  Object->disable(int_source);
 }

} // namespace Dev
} // namespace CCore
