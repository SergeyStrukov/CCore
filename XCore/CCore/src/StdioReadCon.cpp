/* StdioReadCon.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/StdioReadCon.h>

#include <CCore/inc/Exception.h>
 
namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_StdioReadCon {

/* class Register */

class Register : public StdioReadCon::Register
 {
  public:
   
   Register() : StdioReadCon::Register("!StdioReadCon") {}
   
   ~Register() {}
   
   static const char * GetTag() { return "StdioReadCon"; }
 };

PlanInitObject<Register,PlanInitReq<GetPlanInitNode_TaskCore>
                       ,PlanInitReq<GetPlanInitNode_Exception>
                       ,PlanInitReq<Sys::GetPlanInitNode_SysCon>
                       > Object CCORE_INITPRI_1 ;

} // namespace Private_StdioReadCon

using namespace Private_StdioReadCon;

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_StdioReadCon() { return &Object; }

/* class StdioReadCon */ 

StdioReadCon::StdioReadCon()
 {
  if( !Object->set(this) )
    {
     Printf(Exception,"CCore::StdioReadCon::StdioReadCon() : occupied");
    }
 }
   
StdioReadCon::~StdioReadCon()
 {
  Object->clear();
  
  asem.wait();
 }
   
StdioReadCon::Register::Register(TextLabel name)
 : mutex(name)
 {
  host=0;
 }
  
StdioReadCon::Register::~Register()
 {
 }
  
bool StdioReadCon::Register::set(StdioReadCon *host_)
 {
  Mutex::Lock lock(mutex);
  
  if( host ) return false;
  
  host=host_;
  
  return true;
 }
  
void StdioReadCon::Register::clear()
 {
  Mutex::Lock lock(mutex);
  
  host=0;
 }

StdioReadCon * StdioReadCon::Register::lock()
 {
  Mutex::Lock lock(mutex);
  
  if( host )
    {
     host->asem.inc();
     
     return host;
    }
   
  return 0; 
 }

StdioReadCon::Access::Access()
 {
  host=Object->lock();
  
  if( host )
    con=&host->con;
  else
    con=0;
 }
      
StdioReadCon::Access::~Access()
 {
  if( host ) host->asem.dec();
 }

} // namespace CCore
 

