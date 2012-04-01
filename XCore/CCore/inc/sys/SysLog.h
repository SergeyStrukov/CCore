/* SysLog.h */ 
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

#ifndef CCore_inc_sys_SysLog_h
#define CCore_inc_sys_SysLog_h

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/Log.h>
#include <CCore/inc/PlanInit.h>

//#define CCORE_SYS_LOG_ENABLE

namespace CCore {
namespace Sys {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_SysLog();

/* classes */ 

//enum LogSource;

//enum LogType;

class LogAccess;

class LogCursor;

class LogFilterAccess;

class PrintLog;

/* enum LogSource */ 

enum LogSource
 {
  LogSourceCRT,
  
  LogSourceTask,
  LogSourceMutex,
  LogSourceSem,
  LogSourceEvent,
  LogSourceAntiSem,
  LogSourceResSem,
  LogSourceMultiSem,
  LogSourceMultiEvent,
  
  LogSourceUserMin = 10,
  LogSourceUserMax = 31
 };
 
const char * GetTextDesc(LogSource src); 
 
/* enum LogType */ 

enum LogType
 {
  LogDebug,
  LogEvent,
  LogError,
  LogAlert,
  
  LogTypeUserMin = 10,
  LogTypeUserMax = 31
 };
 
const char * GetTextDesc(LogType type); 

/* types */ 

typedef LogCategory_enum<LogSource,LogType> LogCategory;

typedef LogFilter_enum<LogSource,LogType> LogFilter;

/* functions */  
 
inline LogCategory operator | (LogSource src,LogType type) { return LogCategory(src,type); }
 
/* class LogAccess */ 
 
class LogAccess : Dev::IntLock
 {
   void *mem;
 
  public:
  
   LogAccess(LogCategory cat,ulen msg_len);
   
   ~LogAccess();
   
   operator void * () const { return mem; }
   
   void commit(LogMsgBase<LogCategory,LogStamp> *msg);
 };
 
/* class LogCursor */ 

class LogCursor : NoCopy
 {
   const LogMsgBase<LogCategory,LogStamp> *cur;
   ulen count;
 
  public:
  
   explicit LogCursor(ulen count);
   
   ~LogCursor();
   
   // object ptr
   
   bool operator + () const { return cur!=0; }
   
   bool operator ! () const { return cur==0; }
   
   const LogMsgBase<LogCategory,LogStamp> * getPtr() const { return cur; }
   
   const LogMsgBase<LogCategory,LogStamp> & operator * () const { return *cur; }
    
   const LogMsgBase<LogCategory,LogStamp> * operator -> () const { return cur; }
   
   // cursor
   
   void operator ++ ();
 };
 
/* class LogFilterAccess */  

class LogFilterAccess : Dev::IntLock
 {
   LogFilter *filter;
 
  public:
  
   LogFilterAccess();
   
   ~LogFilterAccess() {}
   
   LogFilter * getPtr() const { return filter; }
   
   LogFilter & operator * () const { return *getPtr(); }
   
   LogFilter * operator -> () const { return getPtr(); }
 };
 
/* class PrintLog */ 

class PrintLog
 {
   ulen count;
   LogFilter filter;
   
  public:
  
   explicit PrintLog(ulen count_,LogFilter filter_=LogFilter()) : count(count_),filter(filter_) {}
   
   void print(PrintBase &out) const;
 };
 
/* Log() */ 

#ifdef CCORE_SYS_LOG_ENABLE

template <class ... TT>
void Log(LogCategory cat,const char *format,const TT & ... tt) 
 {
  typedef LogMsg<LogCategory,LogStamp,TT...> MsgType;
  
  LogAccess access(cat,sizeof (MsgType));
 
  if( access )
    {
     MsgType *msg=new(PlaceAt(access)) MsgType(cat,format,tt...);
     
     access.commit(msg);
    } 
 }
 
#else

template <class ... TT>
void Log(LogCategory,const char *,const TT & ...) {}
 
#endif
 
} // namespace Sys
} // namespace CCore
 
#endif
 

