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

#include <CCore/inc/Exception.h>

#include <CCore/inc/dev/DevPlanInit.h>
#include <CCore/inc/dev/DevI2C.h>
#include <CCore/inc/dev/DevVideo.h>

#include <CCore/inc/video/SimpleConsole.h>

#include <__std_init.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysCon {

/* class ImpCon */

class ImpCon : public ConBase
 {
   Dev::VideoControl dev;
 
   Mutex mutex;
   ::CCore::Atomic flag;
   
   Video::SimpleConsole<Video::Color16> con;
   
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
     
     {
      Mutex::Lock lock(mutex);
      
      flag=1;

      con.print(Range_const(packet.getRange()));
      
      flag=0;
     }
     
     packet.free();
    }
   
   virtual void enablePacket()
    {
     // 1
     {
      Dev::I2C i2c(Dev::I2C_0);
     
      i2c.enable();
      i2c.reset();
     }
     
     // 2
     {
      if( dev.init() )
        {
         con.init(dev.getFrameBuf());
        }
     }
    }
   
   virtual void disablePacket()
    {
    }
   
   virtual void showStat()
    {
    }
   
  public:
   
   ImpCon(TextLabel name,void *mem,ulen max_data_len,ulen count)
    : ConBase(name,mem,max_data_len,count),
      mutex("!DebugCon")
    {
    }
   
   ~ImpCon()
    {
    }
   
   void debug_print(PtrLen<const char> str)
    {
     Dev::IntLock lock;
     
     if( !flag ) con.print(str);
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
   
   void debug_print(PtrLen<const char> str)
    {
     dev.debug_print(str);
    }
   
   static const char * GetTag() { return "SysCon"; }
 };
 
PlanInitObject<DefaultCon,PlanInitReq<Dev::GetPlanInitNode_Dev>
                         ,PlanInitReq<GetPlanInitNode_TaskCore> > Object CCORE_INITPRI_1 ;

void DebugPrint(PtrLen<const char> str)
 {
  if( !Object ) return;
  
  Object->debug_print(str);
 }

} // namespace Private_SysCon
 
using namespace Private_SysCon; 
 
PlanInitNode * GetPlanInitNode_SysCon() { return &Object; }
 
/* class ConBase */

ConBase * ConBase::GetObject() { return Object->getBase(); }

} // namespace Sys
} // namespace CCore
 
#if 1

using namespace CCore;

void __std_debug_init(void)
 {
 }

void __std_debug(const char *zstr)
 {
  Sys::DebugPrint(StrLen(zstr));
 }

void __std_debug2(const char *ptr,__std_len_t len)
 {
  Sys::DebugPrint(Range(ptr,len));
 }

void __std_debug_console(const char *ptr,__std_len_t len)
 {
  Sys::DebugPrint(Range(ptr,len));
 }

#include <CCore/inc/dev/AM3359.h>

void __std_debug_trap(unsigned LR,unsigned trap)
 {
  if( trap==0 ) return;
  
  using namespace AM3359::CP15;
  
  char buf[TextBufLen];
  
  PrintBuf out(Range(buf));
  
  switch( trap )
    {
     case 1 : // Undefined
      {
       Printf(out,"Undefined PC = #9.hi;",LR-4);
      }
     break; 
    
     case 3 : // Prefetch
      {
       Printf(out,"Prefetch PC = #9.hi; #; #9.hi;",LR-4,GetInstructionFaultStatus(),GetInstructionFaultAddress());
      }
     break;
     
     case 4 : // Data
      {
       Printf(out,"Data PC = #9.hi; #; #9.hi;",LR-8,GetDataFaultStatus(),GetDataFaultAddress());
      }
     break;
     
     default:
      {
       Printf(out,"LR = #9.hi; trap = #;",LR,trap);
      }
    }
  
  Sys::DebugPrint(out.close());
 }

#endif


