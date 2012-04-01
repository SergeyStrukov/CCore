/* Job.cpp */ 
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
 
#include <CCore/inc/Job.h>

#include <CCore/inc/MemBase.h>
 
namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_Job {

struct DefaultHost : SingleHost<JobStarterType>
 {
  DefaultHost() : SingleHost<JobStarterType>("!DefaultJobHost") {}
  
  static const char * GetTag() { return "JobHost"; }
 };
 
PlanInitObject<DefaultHost,PlanInitReq<GetPlanInitNode_MemBase> > Object CCORE_INITPRI_1 ;

} // namespace Private_Job
 
using namespace Private_Job; 

PlanInitNode * GetPlanInitNode_JobHost() { return &Object; }

/* class Job */ 

SingleHost<JobStarterType> & Job::GetHost() { return *Object; }

/* class Job::Init */ 

Job::Init::Init(unsigned task_count)
 : run_task(starter,task_count),
   master(GetHost(),"JobStarter",starter)
 {
  master.guard();
 }
   
Job::Init::~Init()
 {
 }
  
} // namespace CCore
 

