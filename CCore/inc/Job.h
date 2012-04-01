/* Job.h */ 
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

#ifndef CCore_inc_Job_h
#define CCore_inc_Job_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/SingleHost.h>
#include <CCore/inc/Starter.h>

#include <CCore/inc/sys/SysProp.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_JobHost();

/* types */

typedef Function<void (void)> JobType;

typedef Starter<JobType> JobStarterType;

/* classes */ 

class CustomJob;

class Job;

/* class CustomJob */

class CustomJob : JobStarterType::Start
 {
  public:
   
   CustomJob(JobStarterType *starter,JobType job)
    : JobStarterType::Start(starter,job)
    {
     job();
    }
   
   ~CustomJob() {}
 };

/* class Job */ 

class Job : SingleHook<JobStarterType> , CustomJob
 {
  private:
   
   static SingleHost<JobStarterType> & GetHost();
  
  public:
  
   explicit Job(JobType job) 
    : SingleHook<JobStarterType>(GetHost()),
      CustomJob(getPtr(),job) 
    { 
    }
   
   ~Job() {}
   
   class Init;
 };
 
/* class Job::Init */

 //
 // Only single Job::Init
 //

class Job::Init : NoCopy
 {
   JobStarterType starter;
   
   struct RunTask : JobStarterType::Run 
    {
     RunTask(JobStarterType &starter,unsigned task_count) 
      : JobStarterType::Run(starter)
      { 
       run(task_count); 
      }
     
    } run_task;
   
   SingleMaster<JobStarterType> master;
 
  public:
  
   static unsigned DefaultTaskCount()
    {
     unsigned cpu=Sys::GetCpuCount();
     
     return (cpu>1)?(cpu-1):1;
    }
  
   explicit Init(unsigned task_count=DefaultTaskCount());
   
   ~Init();
 };
 
} // namespace CCore
 
#endif
 

