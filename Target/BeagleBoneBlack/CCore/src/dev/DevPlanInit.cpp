/* DevPlanInit.cpp */ 
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
 
#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/dev/DevIntHandle.h>
 
namespace CCore {
namespace Dev {

#if 0

/* init/exit functions */ 

static const uint32 TTBase = 0x4000 ;
  
static_assert( TTBase%MMU::TTAlign==0 ,"CCore::Dev::TTBase is not aligned");

static void ClearTT(MMU::TTEntry *base)
 {
  using namespace MMU;
  
  for(unsigned i=0; i<TTLen ;i++) base[i].disable();
 }
 
static void FillTTRegion(MMU::TTEntry *base,unsigned off,unsigned len,unsigned flags)
 {
  for(; len ;off++,len--) base[off].section(off,0,flags);
 }
 
static void BuildTT()
 {
  using namespace MMU;
 
  TTEntry *base=(TTEntry *)TTBase;
   
  ClearTT(base);
  
  FillTTRegion(base,0x000,0x080,Section_AP_UNO|Section_Cache|Section_Buff); // RAM
   
  FillTTRegion(base,0x001,0x001,Section_AP_UNO); // RAM  No cache
   
  FillTTRegion(base,0x480,0x080,Section_AP_UNO); // PCI
  FillTTRegion(base,0x500,0x020,Section_AP_UNO); // Flash
  FillTTRegion(base,0x540,0x020,Section_AP_UNO); // FPGA
  FillTTRegion(base,0x600,0x040,Section_AP_UNO); // QM
  FillTTRegion(base,0x700,0x100,Section_AP_UNO); // Regs
  FillTTRegion(base,0xC00,0x400,Section_AP_UNO); // Regs
 }
 
static void EnableMMUandCache()
 {
  using namespace CP15;
   
  Type_DomainAC dac;
   
  dac.set_D0(DomainAC_D0_DescAccess)
     .set_D1(DomainAC_D1_DescAccess)
     .set_D2(DomainAC_D2_DescAccess)
     .set_D3(DomainAC_D3_DescAccess)
     .set_D4(DomainAC_D4_DescAccess)
     .set_D5(DomainAC_D5_DescAccess)
     .set_D6(DomainAC_D6_DescAccess)
     .set_D7(DomainAC_D7_DescAccess)
     .set_D8(DomainAC_D8_DescAccess)
     .set_D9(DomainAC_D9_DescAccess)
     .set_D10(DomainAC_D10_DescAccess)
     .set_D11(DomainAC_D11_DescAccess)
     .set_D12(DomainAC_D12_DescAccess)
     .set_D13(DomainAC_D13_DescAccess)
     .set_D14(DomainAC_D14_DescAccess)
     .set_D15(DomainAC_D15_DescAccess);
  
  Set_DomainAC(dac);
   
  Type_AuxControl aux;
   
  aux.set_MD(AuxControl_MD_WB_RA);
   
  Set_AuxControl(aux);
   
  Set_PID(0);
   
  Set_TTBase(TTBase);
   
  Type_Control ctrl;
   
  ctrl.setbit(Control_I|
              Control_Z|
              Control_B|
              Control_C|
              Control_A|
              Control_M)
      .set_Ones(Control_Ones_Fill);        
   
  Set_Control(ctrl);
   
  Wait();
 }
 
void Init_CPU()
 {
  BuildTT();
  
  EnableMMUandCache();
 }
 
#endif

/* GetPlanInitNode_...() */ 

namespace Private_DevPlanInit {

struct Empty
 {
  static const char * GetTag() { return "Dev"; }
 };
 
PlanInitObject<Empty,PlanInitReq<GetPlanInitNode_DevIntHandle> > Object CCORE_INITPRI_1 ;

} // namespace Private_DevPlanInit
 
using namespace Private_DevPlanInit; 
 
PlanInitNode * GetPlanInitNode_Dev() { return &Object; }
 
} // namespace Dev
} // namespace CCore
 

