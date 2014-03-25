/* SysCon.cpp */ 
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
 
#include <CCore/inc/sys/SysCon.h>

#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysCon {

extern "C"
void __std_debug_console(const char *ptr,ulen len);

/* class ImpCon */

class ImpCon : public ConBase
 {
  private:
   
   virtual void attachDefaultInput(ConInputFunction)
    {
     // no input
    }
   
   virtual void detachDefaultInput()
    {
    }
   
   virtual void defaultOutput(NanoPacket<char> packet)
    {
     if( !packet ) return;

     __std_debug_console(packet.getData(),packet.getDataLen());
     
     packet.free();
    }
   
   virtual void enablePacket()
    {
    }
   
   virtual void disablePacket()
    {
    }
   
   virtual void showStat()
    {
    }
   
  public:
   
   ImpCon(TextLabel name,void *mem,ulen max_data_len,ulen count)
    : ConBase(name,mem,max_data_len,count)
    {
    }
   
   ~ImpCon()
    {
    }
 };

/* class DefaultCon */

class DefaultCon : NoCopy
 {
   static const ulen MaxDataLen = 512 ;
   static const ulen Count   = 100 ;
   static const ulen MemLen  = ConBase::MemLen(MaxDataLen,Count) ;
   
  private: 
 
   InitStorage<MemLen> storage;
   
   ImpCon dev;
   
  public:
  
   DefaultCon() : dev("!SysCon",storage.getMem(),MaxDataLen,Count) {}
   
   ~DefaultCon() {}
   
   ConBase * getBase() { return &dev; }
   
   static const char * GetTag() { return "SysCon"; }
 };
 
PlanInitObject<DefaultCon,PlanInitReq<Dev::GetPlanInitNode_Dev>
                         ,PlanInitReq<GetPlanInitNode_TaskCore> > Object CCORE_INITPRI_1 ;

} // namespace Private_SysCon
 
using namespace Private_SysCon; 
 
PlanInitNode * GetPlanInitNode_SysCon() { return &Object; }
 
/* class ConBase */

ConBase * ConBase::GetObject() { return Object->getBase(); }

} // namespace Sys
} // namespace CCore
 

