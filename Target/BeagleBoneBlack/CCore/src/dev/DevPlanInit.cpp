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

#include <CCore/inc/dev/AM3359.h>

#include <__std_init.h>
 
namespace CCore {
namespace Dev {

const ulen TTLen = 1<<12 ;

const unsigned TTableBaseBits = 14 ;

const unsigned SectionBaseBits = 20 ;

extern uint32 TTable[TTLen];

static bool IsDEV(uint32 i)
 {
  uint32 address=i<<SectionBaseBits;
  
  return address>=0x40000000 && address<0x80000000 ;
 }

static bool IsRAM(uint32 i)
 {
  uint32 address=i<<SectionBaseBits;
  
  return address>=0x80000000 && address<0xA0000000 ;
 }

static bool TestAddress(uint32 address,uint32 base,uint32 len)
 {
  return address>=base && (address-base)<len ;
 }

static bool IsShared(uint32 i,uint32 sbase1,uint32 slen1,uint32 sbase2,uint32 slen2)
 {
  uint32 address=i<<SectionBaseBits;
  
  return TestAddress(address,sbase1,slen1) || TestAddress(address,sbase2,slen2) ;
 }

void Init_CPU() 
 {
  using namespace AM3359::CP15;
  
  // prepare TTable
  {
   uint32 sbase1=(uint32)__std_get_shared_mem();
   uint32 slen1=__std_get_shared_mem_len();
   
   uint32 sbase2=(uint32)__std_get_video_mem();
   uint32 slen2=__std_get_video_mem_len();
   
   for(uint32 i=0; i<TTLen ;i++) 
     {
      if( IsDEV(i) )
        {
         Type_SectionDesc desc;
        
         desc.setbit(SectionDesc_SBO|SectionDesc_AP0)
             .set_Domain(0)
             .set_Base(i);
         
         TTable[i]=desc;
        }
      else
        {
         if( IsRAM(i) )
           {
            if( IsShared(i,sbase1,slen1,sbase2,slen2) )
              {
               Type_SectionDesc desc;
              
               desc.setbit(SectionDesc_SBO|SectionDesc_AP0|SectionDesc_TEX0|SectionDesc_S)
                   .set_Domain(0)
                   .set_Base(i);
               
               TTable[i]=desc;
              }
            else
              {
               Type_SectionDesc desc;
              
               desc.setbit(SectionDesc_SBO|SectionDesc_AP0|SectionDesc_TEX2|SectionDesc_B|SectionDesc_C)
                   .set_Domain(0)
                   .set_Base(i);
               
               TTable[i]=desc;
              } 
           }
         else
           {
            Type_SectionDesc desc;
            
            TTable[i]=desc;
           }
        }
     }
  }
  
  // set TTControl
  {
   Type_TTControl val;
   
   SetTTControl(val);
  }
  
  // set TTBase0
  {
   uint32 base=(uint32)(uint32 *)TTable;
   
   if( base<<(32-TTableBaseBits) ) __std_abort("Fatal error : TTable is not aligned");
   
   Type_TTBase0 val;
   
   val.setbit(TTBase0_C)
      .set_Base(base>>TTableBaseBits);
   
   SetTTBase0(val);
  }
  
  // set DomainAccessControl
  {
   Type_DomainAccessControl val;
   
   val.set_D0(DomainAccessControl_D0_Manager);
   
   SetDomainAccessControl(val);
  }
  
  // set AuxControl
  {
   auto val=GetAuxControl();
   
   val.setbit(AuxControl_L2EN);
   
   SetAuxControl(val);
  }
  
  // set FCSE
  {
   Type_FCSE val;
   
   SetFCSE(val);
  }
  
  // set ContextID
  {
   Type_ContextID val;
   
   SetContextID(val);
  }
  
  // invalidate
  {
   InvalidateTLB();
   InvalidateInstructionCaches();
   InvalidateDataCaches();
  }
  
  //return;
  
  // set Control
  {
   Type_Control val;
   
   val.setbit(Control_AFE|Control_M|Control_A|Control_Z|Control_I|Control_C)  
      .set_SBO(Control_SBO_Ones);
   
   SetControl(val);
  }
 }

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
 

