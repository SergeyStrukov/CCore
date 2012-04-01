/* SysLog.cpp */ 
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
 
#include <CCore/inc/sys/SysLog.h>

#include <CCore/inc/sys/SysMemSpace.h>

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

namespace Private_SysLog {

/* class SysLog */

class SysLog
 {
   LogFilter filter;
   LogStorage<LogCategory,LogStamp> storage;
   
  public: 
  
   SysLog() : storage(AllocLogSpace()) {}
  
   ~SysLog() {}
   
   void * alloc(LogCategory cat,ulen msg_len)
    {
     if( filter(cat) ) return 0;
     
     return storage.alloc(msg_len);
    }
 
   void free(void *mem) { storage.free(mem); }
   
   void commit(void *mem,LogMsgBase<LogCategory,LogStamp> *msg) { storage.commit(mem,msg); }
   
   LogFilter * getFilterPtr() { return &filter; }
   
   ulen getCount() const { return storage.getCount(); }
   
   void getCounter(LogCounter &ret) { storage.getCounter(ret); }
   
   const LogMsgBase<LogCategory,LogStamp> * startCursor() { return storage.startCursor(); }
   
   const LogMsgBase<LogCategory,LogStamp> * startCursor(ulen &count) 
    {
     count=storage.getCount();
     
     return storage.startCursor(); 
    }
   
   const LogMsgBase<LogCategory,LogStamp> * nextCursor() { return storage.nextCursor(); }
   
   void stopCursor() { storage.stopCursor(); }
   
   static const char * GetTag() { return "SysLog"; }
 };
 
PlanInitObject<SysLog> Object CCORE_INITPRI_1 ;

/* class Access */

class Access : Dev::IntLock
 {
   SysLog *ptr;
   
  public:
  
   Access() { ptr=Object.getPtr(); }
   
   ~Access() {}
   
   SysLog * operator -> () const { return ptr; }
 };
 
} // namespace Private_SysLog
 
using namespace Private_SysLog; 
 
PlanInitNode * GetPlanInitNode_SysLog() { return &Object; }
 
/* enum LogSource */ 

const char * GetTextDesc(LogSource src)
 {
  static const char *const Table[]=
   {
    "CRT",
    
    "Task",
    "Mutex",
    "Sem",
    "Event",
    "AntiSem",
    "ResSem",
    "MultiSem",
    "MultiEvent",
    
    "Sys9",
    
    "User10",
    "User11",
    "User12",
    "User13",
    "User14",
    "User15",
    "User16",
    "User17",
    "User18",
    "User19",
    "User20",
    "User21",
    "User22",
    "User23",
    "User24",
    "User25",
    "User26",
    "User27",
    "User28",
    "User29",
    "User30",
    "User31"
   }; 
 
  return Table[src];
 } 
 
/* enum LogType */ 

const char * GetTextDesc(LogType type)
 {
  static const char *const Table[]=
   {
    "Debug",
    "Event",
    "Error",
    "Alert",
    
    "Sys4",
    "Sys5",
    "Sys6",
    "Sys7",
    "Sys8",
    "Sys9",
    
    "User10",
    "User11",
    "User12",
    "User13",
    "User14",
    "User15",
    "User16",
    "User17",
    "User18",
    "User19",
    "User20",
    "User21",
    "User22",
    "User23",
    "User24",
    "User25",
    "User26",
    "User27",
    "User28",
    "User29",
    "User30",
    "User31"
   }; 
 
  return Table[type];
 }
 
/* class LogAccess */  

LogAccess::LogAccess(LogCategory cat,ulen msg_len)
 {
  mem=Object->alloc(cat,msg_len);
 }
   
LogAccess::~LogAccess()
 {
  if( mem ) Object->free(mem); 
 }
   
void LogAccess::commit(LogMsgBase<LogCategory,LogStamp> *msg)
 {
  Object->commit(mem,msg);
  
  mem=0;
 }
 
/* class LogCursor */ 

LogCursor::LogCursor(ulen count_) 
 : count(count_)
 {
  if( count )
    {
     ulen msg_count;
     
     cur=Access()->startCursor(msg_count);
     
     if( count<msg_count )
       {
        ulen cnt=msg_count-count;
        
        count=msg_count-1;
        
        for(; cnt ;cnt--) ++(*this); // count is decremented here
       }
     else
       {  
        count--;
       } 
    }
  else
    {
     cur=0;
    }  
 }
   
LogCursor::~LogCursor()
 {
  if( !cur ) return;

  Access()->stopCursor();
 }
   
void LogCursor::operator ++ ()
 {
  if( !cur ) return;
 
  if( count )
    {
     count--;
     
     cur=Access()->nextCursor();
    }
  else
    {
     cur=0;
     
     Access()->stopCursor();
    }  
 }
 
/* class LogFilterAccess */  

LogFilterAccess::LogFilterAccess()
 {
  filter=Object->getFilterPtr();
 }
   
/* class PrintLog */ 

void PrintLog::print(PrintBase &out) const
 {
  LogCounter cnt;
  
  Access()->getCounter(cnt);
 
  Printf(out,"#;\n#;\n#;\n",Title("SysLog"),cnt,TextDivider());
  
  for(LogCursor cur(count); +cur ;++cur) 
    if( !filter(cur->getCategory())  )
      Putobj(out,*cur);
 }
 
} // namespace Sys
} // namespace CCore
 

