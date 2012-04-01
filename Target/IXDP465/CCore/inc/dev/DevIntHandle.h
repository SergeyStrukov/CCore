/* DevIntHandle.h */ 
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

#ifndef CCore_inc_dev_DevIntHandle_h
#define CCore_inc_dev_DevIntHandle_h

#include <CCore/inc/PlanInit.h>

namespace CCore {
namespace Dev {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_DevIntHandle();

/* enum IntSource */ 

enum IntSource
 {
  Int_NPE_A,
  Int_NPE_B,
  Int_NPE_C,

  Int_QMLO,
  Int_QMHI,

  Int_T0,
  Int_T1,

  Int_I2C,

  Int_USBHost,
  Int_USBDev,

  Int_UART1,
  Int_UART0,
  
  Int_PCI,
  Int_PCI_DMA1,
  Int_PCI_DMA2,
  
  Int_PCI_Slot0,
  Int_PCI_Slot1,
  Int_PCI_Slot2,
  Int_PCI_Slot3,
  
  Int_TableLen
 };
 
/* functions */ 

void SetupIntHandler(IntSource intsrc,Function<void (void)> handle_int); 

void CleanupIntHandler(IntSource intsrc); 

void EnableInt(IntSource intsrc);

void DisableInt(IntSource intsrc);

} // namespace Dev
} // namespace CCore
 
#endif

