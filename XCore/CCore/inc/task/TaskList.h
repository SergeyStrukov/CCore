/* TaskList.h */ 
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

#ifndef CCore_inc_task_TaskList_h
#define CCore_inc_task_TaskList_h

#include <CCore/inc/task/AutoText.h>
#include <CCore/inc/task/TaskMonitor.h>

#include <CCore/inc/TimeScope.h>

namespace CCore {

/* classes */ 

class TaskBase;

class TaskList;

/* class TaskBase */ 

class TaskBase : public TaskMonitor::Link
 {
   TaskPriority actual_priority;
   
   DLink<TaskBase> link;
   TaskList *list;
   
   TaskList *owned_list;
   
  private: 
   
   friend class TaskList;
   
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
 
   // IntLocked
   
   void changePriority(TaskPriority old_pri,TaskPriority new_pri);
   
   TaskBase * burst_step(TaskPriority pri);
   
   void burst(TaskPriority pri);

   TaskPriority calcPriority();
   
   TaskBase * relieve_step();
   
   void relieve();
   
  protected: 
   
   void delList(); // IntLocked
   
   void guardList();
   
   void setIdlePriority() { actual_priority=IdleTaskPriority; } // IntLocked
   
   bool preempt(const TaskBase *task) const { return Preempt(getPriority(),task->getPriority()); }
  
  public: 
  
   TaskBase(TextLabel name,TaskPriority priority);
   
   ~TaskBase() {}
 };

/* class TaskList */  

class TaskList : NoCopy
 {
   DLink<TaskList> link;
   TaskBase *owner;
   TaskPriority priority; // valid only if owner!=0
 
   DLink<TaskBase>::CircularAlgo<&TaskBase::link>::Top top;
   
  private: 
  
   typedef DLink<TaskList>::CircularAlgo<&TaskList::link> Algo;
    
   friend class TaskBase; 
   
   struct FindResult;
  
   // IntLocked
   
   TaskBase * getTopOwner();
   
    // find
   
   FindResult find();
  
   FindResult find_preempt(TaskPriority priority);
   
   TaskBase * find_relaxed(TaskPriority priority);
   
    // del
  
   void do_del(TaskBase *task);
   
   TaskBase * del(TaskBase *task);
   
    // priority
  
   void changePriority(TaskBase *task,TaskPriority old_priority,TaskPriority new_priority);
   
   TaskPriority calcPriority();
  
   bool recalcPriority();
   
   static TaskPriority CalcPriority(TaskList *list,TaskPriority priority);
   
  public:
  
   TaskList();
   
   ~TaskList();
  
   // IntLocked
   
   TaskList(TaskList &list,ulen &count);
   
    // methods
   
   bool operator + () const { return +top; }
   
   bool operator ! () const { return !top; }
   
    // owner
   
   TaskBase * getOwner() const { return owner; } 
  
   void setOwner(TaskBase *task);   // assume owner==0
  
   void clearOwner(TaskBase *task); // assume task==owner
   
    // put
  
   void put(TaskBase *task);
   
    // get
  
   TaskBase * get();
  
   TaskBase * get_relaxed(TaskPriority priority);
  
   TaskBase * get_first();
  
   TaskBase * get_preempt(TaskPriority priority);
  
   TaskBase * get_preempt(TaskBase *task) { return get_preempt(task->actual_priority); }
 };
 
} // namespace CCore
 
#endif
 

