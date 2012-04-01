/* SysCon.cpp */ 
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
 
#include <CCore/inc/sys/SysCon.h>

#include <CCore/inc/dev/DevSerial.h>
#include <CCore/inc/dev/DevPlanInit.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysCon {

/* class SerialBase */

class SerialBase : public ConBase
 {
   Dev::Serial serial;
 
  private:
   
   virtual void attachDefaultInput(ConInputFunction input_any)
    {
     serial.attachConInput(input_any);
    }
   
   virtual void detachDefaultInput()
    {
     serial.detachConInput();
    }
   
   virtual void defaultOutput(NanoPacket<char> packet)
    {
     if( serial.write(packet) ) serial.complete();
    }
   
   virtual void enablePacket()
    {
     serial.enablePacket();
    }
   
   virtual void disablePacket()
    {
     if( serial.disablePacket() ) serial.complete();
    }
   
   virtual void showStat()
    {
     Dev::SerialCounters stat;
    
     serial.getStat(stat);
     
     auto npc=getNoPacketCount();
     
     Printf(Con,"\n#;\n\n#20; = #;\n#20;\n\n#;\n",Title("Con stat"),"No packets",npc,stat,TextDivider());
    }
   
  public:
   
   SerialBase(TextLabel name,void *mem,ulen max_data_len,ulen count)
    : ConBase(name,mem,max_data_len,count),
      serial(Dev::Serial_0)
    {
    }
   
   ~SerialBase()
    {
    }
 };

/* class SerialCon */

class SerialCon : NoCopy
 {
   static const ulen MaxDataLen = 512 ;
   static const ulen Count   = 100 ;
   static const ulen MemLen  = ConBase::MemLen(MaxDataLen,Count) ;
   
  private: 
 
   InitStorage<MemLen> storage;
   
   SerialBase base;
   
  public:
  
   SerialCon() : base("!SysCon",storage.getMem(),MaxDataLen,Count) {}
   
   ~SerialCon() {}
   
   ConBase * getBase() { return &base; }
   
   static const char * GetTag() { return "SysCon"; }
 };
 
PlanInitObject<SerialCon,PlanInitReq<Dev::GetPlanInitNode_Dev>
                        ,PlanInitReq<GetPlanInitNode_TaskCore> > Object CCORE_INITPRI_1 ;

} // namespace Private_SysCon
 
using namespace Private_SysCon; 
 
PlanInitNode * GetPlanInitNode_SysCon() { return &Object; }
 
/* class ConBase */

ConBase * ConBase::GetObject() { return Object->getBase(); }

} // namespace Sys
} // namespace CCore
 

