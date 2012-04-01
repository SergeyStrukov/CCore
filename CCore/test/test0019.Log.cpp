/* test0019.Log.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Log.h>

namespace App {

namespace Private_0019 {

/* enum LogSource */ 

enum LogSource
 {
  LogSourceCRT,
  
  LogSourceTask,
  LogSourceSem,
  LogSourceMutex,
  LogSourceEvent,
  LogSourceMultiSem,
  
  LogSourceUserMin = 10,
  LogSourceUserMax = 31
 };
 
const char * GetTextDesc(LogSource src)
 {
  static const char *const Table[]=
   {
    "CRT",
    "Task",
    "Sem",
    "Mutex",
    "Event",
    
    "MultiSem",
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
 
  return Table[src];
 } 
 
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

/* Log */
 
typedef LogCategory_enum<LogSource,LogType> Cat;

typedef LogFilter_enum<LogSource,LogType> Filter;
 
inline Cat operator | (LogSource src,LogType type) { return Cat(src,type); }
 
UserLog<Cat,LogStamp,Filter> Log("TestLog",10_KByte);

} // namespace Private_0019
 
using namespace Private_0019; 
 
/* Testit<19> */ 

template<>
const char *const Testit<19>::Name="Test19 Log";

template<>
bool Testit<19>::Main() 
 { 
  //Log.setFilter(Filter(LogSourceTask|LogEvent));
 
  Log(LogSourceTask|LogEvent,"start");
  
  Log(LogSourceTask|LogDebug,"point #;",1);
  Log(LogSourceTask|LogDebug,"point #;",2);
  Log(LogSourceTask|LogDebug,"point #; #;",1,2);
  Log(LogSourceTask|LogDebug,"point #; #; #;",1,2,3);
  Log(LogSourceTask|LogEvent,"point #;",10);
  Log(LogSourceTask|LogEvent,"point #;",20);
 
  Log(LogSourceTask|LogEvent,"finish");
  
  Printf(Con,"no filter\n\n#;",PrintLog(Log,100));
  Printf(Con,"\nfiltered\n\n#;",PrintLog(Log,100,Filter(LogSourceTask|LogDebug)));
  
  for(ulen cnt=10000; cnt ;cnt--)
    {
     Log(LogSourceTask|LogEvent,"cnt = #;",cnt);
    }
    
  PrintFile out("testLog.txt");  
  
  Putobj(out,PrintLog(Log,250));
  
  return true;
 }
 
} // namespace App
 
