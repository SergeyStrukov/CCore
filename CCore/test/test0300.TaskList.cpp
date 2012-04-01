/* test0300.TaskList.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: for XCore 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Abort.h>

namespace App {

namespace Private_0300 {

/* types */

typedef unsigned TaskPriority;

const TaskPriority IdleTaskPriority = TaskPriority(-1) ;

inline bool Preempt(TaskPriority a,TaskPriority b) { return a<b; }

/* classes */

class TaskLink;

class TaskBase;

class TaskList;

/* class TaskLink */

class TaskLink : NoCopy
 {
   TaskPriority priority;
   
  public:

   explicit TaskLink(TaskPriority priority_) : priority(priority_) {}

   TaskPriority getPriority() const { return priority; }
 };

/* class TaskBase */ 

class TaskBase : public TaskLink
 {
   ulen index;
   mutable ulen mark;
   
   static ulen LoopCount;
  
   TaskPriority actual_priority;
   
   DLink<TaskBase> link;
   TaskList *list;
   
   TaskList *owned_list;
   
  private: 
   
   friend class TaskList;
   
   void changePriority(TaskPriority old_pri,TaskPriority new_pri);
   
   TaskBase * burst_step(TaskPriority pri);
   
   void burst(TaskPriority pri);

   TaskPriority calcPriority();
   
   TaskBase * relieve_step();
   
   void relieve();
   
  public: 
  
   TaskBase(TaskPriority priority,ulen index);
   
   void delList();
   
   // extra
   
   static ulen GetLoopCount() { return LoopCount; }
   
   TaskList * getList() { return list; }
   
   void check();
   
   template <class P>
   void print(P &out) const;
   
   // flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* class TaskList */  

class TaskList : NoCopy
 {
   ulen index;
   
   static ulen DeadlockCount; 
  
   DLink<TaskList> link;
   TaskBase *owner;
   TaskPriority priority; // valid only if owner!=0
 
   DLink<TaskBase>::CircularAlgo<&TaskBase::link>::Top top;
   
  private: 
  
   typedef DLink<TaskList>::CircularAlgo<&TaskList::link> Algo;
    
   friend class TaskBase;
   
   TaskPriority find();
   
   void do_del(TaskBase *task);
   
   void changePriority(TaskBase *task,TaskPriority old_priority,TaskPriority new_priority);
   
   TaskPriority calcPriority();
  
   bool recalcPriority();
   
   static TaskPriority CalcPriority(TaskList *list,TaskPriority priority);
   
   TaskBase * getTopOwner(); 
   
  public:
  
   explicit TaskList(ulen index);
   
   // methods
   
   bool operator + () const { return +top; }
   
   bool operator ! () const { return !top; }
   
   // owner
   
   TaskBase * getOwner() { return owner; } 
  
   void setOwner(TaskBase *task);   // assume owner==0
  
   void clearOwner(TaskBase *task); // assume task==owner
   
   // put
  
   void put(TaskBase *task);
   
   // extra
   
   static ulen GetDeadlockCount() { return DeadlockCount; }
  
   void check();
   
   template <class P>
   void print(P &out) const;
   
   template <class P>
   void printInfo(P &out) const;
   
   template <class P>
   static void Print(P &out,TaskList *list);
   
   // flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
ulen TaskList::DeadlockCount = 0 ;

TaskPriority TaskList::find()
 {
  TaskPriority ret=IdleTaskPriority;
  
  for(auto cur=top.start(); +cur ;++cur)
    {
     TaskPriority pri=cur->actual_priority;
     
     if( Preempt(pri,ret) ) ret=pri;
    }
   
  return ret; 
 }

void TaskList::do_del(TaskBase *task)
 {
  if( task->list!=this ) Abort("Fatal error: task is in different list");

  top.del(task);  

  task->list=0;
  
  if( owner )
    {
     TaskPriority pri=task->actual_priority;

     if( !Preempt(priority,pri) )
       {
        if( recalcPriority() ) owner->relieve();
       }
    }
 }
 
void TaskList::changePriority(TaskBase *task,TaskPriority,TaskPriority new_priority)
 {
  task->actual_priority=new_priority;
 }
  
TaskPriority TaskList::calcPriority()
 {
  return priority=find();
 }
  
bool TaskList::recalcPriority()
 {
  TaskPriority pri=find();
  
  if( pri!=priority )
    {
     priority=pri;
     
     return true;
    }
   
  return false; 
 }

TaskPriority TaskList::CalcPriority(TaskList *list,TaskPriority priority)
 {
  for(Algo::Cur cur(list); +cur ;++cur)
    {
     TaskPriority pri=cur->priority;
     
     if( Preempt(pri,priority) ) priority=pri;
    }
    
  return priority;  
 }

TaskBase * TaskList::getTopOwner()
 {
  TaskBase *ret=owner;
  
  while( ret )
    {
     if( TaskList *list=ret->list )
       {
        if( TaskBase *up=list->owner ) ret=up; else break;
       }
     else
       {
        break;
       }
    }
  
  return ret;
 }

TaskList::TaskList(ulen index_)
 : index(index_)
 {
  owner=0;
 }
   
void TaskList::setOwner(TaskBase *task)
 {
  if( owner ) Abort("Fatal error: task list is owned");
 
  owner=task; 
  
  task->owned_list=Algo::InsTopFirst(task->owned_list,this);
  
  task->burst(calcPriority());
 }
  
void TaskList::clearOwner(TaskBase *task)
 {
  if( task!=owner ) Abort("Fatal error: task list has another owner");
 
  owner=0; 
  
  task->owned_list=Algo::DelTop(task->owned_list,this);
  
  task->relieve();
 }
  
void TaskList::put(TaskBase *task)
 {
  if( task==getTopOwner() ) 
    {
     DeadlockCount++;
     
     return;
    }
  
  if( task->list ) Abort("Fatal error : task is in another list");
  
  task->list=this;
  
  top.ins_last(task);
  
  if( owner )
    {
     TaskPriority pri=task->actual_priority;
     
     if( Preempt(pri,priority) )
       {
        priority=pri;
        
        owner->burst(pri);
       }
    }
 }
  
void TaskList::check()
 {
  if( owner && find()!=priority )
    {
     Printf(Exception,"fail 1");
    }
 }
 
template <class P>
void TaskList::print(P &out) const
 {
  if( +top )
    {
     Printf(out,"List[#;] {",index);
     
     auto cur=top.start();
     
     Printf(out," #;",cur->index);
     
     for(++cur; +cur ;++cur) Printf(out,", #;",cur->index);
     
     Printf(out," }\n\n");
    }
 }

template <class P>
void TaskList::printInfo(P &out) const
 {
  if( owner )
    Printf(out," -> {#;!#;!}",index,priority);
  else
    Printf(out," -> {#;}",index);
 }

template <class P>
void TaskList::Print(P &out,TaskList *list)
 {
  Printf(out," {");
  
  Algo::Cur cur(list);
  
  Printf(out," #;",cur->index);
  
  for(++cur; +cur ;++cur) Printf(out,", #;",cur->index);
  
  Printf(out," }");
 }

/* class TaskBase */

ulen TaskBase::LoopCount = 0 ;

void TaskBase::changePriority(TaskPriority old_pri,TaskPriority new_pri)
 {
  if( list )
    {
     list->changePriority(this,old_pri,new_pri);
    }
  else
    {
     actual_priority=new_pri;
    }  
 }

TaskBase * TaskBase::burst_step(TaskPriority pri)
 {
  TaskPriority old_pri=actual_priority;
  
  if( Preempt(pri,old_pri) )
    {
     changePriority(old_pri,pri);
     
     if( list && list->owner && Preempt(pri,list->priority) )
       {
        list->priority=pri;
        
        return list->owner;
       }
    }
    
  return 0;  
 }
   
void TaskBase::burst(TaskPriority pri)
 {
  TaskBase *task=this;
  
  do
    {
     task=task->burst_step(pri);
    }
  while( task );  
 }
 
TaskPriority TaskBase::calcPriority()
 {
  return TaskList::CalcPriority(owned_list,getPriority());
 }
 
TaskBase * TaskBase::relieve_step()
 {
  TaskPriority old_pri=actual_priority;
  
  TaskPriority pri=calcPriority();
 
  if( Preempt(old_pri,pri) )
    {
     changePriority(old_pri,pri);
     
     if( list && list->owner && !Preempt(list->priority,old_pri) )
       {
        if( list->recalcPriority() ) return list->owner;
       }
    }
 
  return 0;
 }
   
void TaskBase::relieve()
 {
  TaskBase *task=this;
  
  do
    {
     task=task->relieve_step();
    }
  while( task );  
 }
 
TaskBase::TaskBase(TaskPriority priority,ulen index_)
 : TaskLink(priority),
   index(index_),
   mark(0),
   actual_priority(priority)
 {
  list=0;
  owned_list=0;
 }

void TaskBase::delList()
 {
  if( list ) list->do_del(this);
 }
 
void TaskBase::check()
 {
  if( actual_priority!=calcPriority() )
    {
     Printf(Exception,"fail 2");
    }
 }

template <class P>
void TaskBase::print(P &out) const
 {
  mark=index;
  
  if( Preempt(getPriority(),actual_priority) )
    {
     Printf(Exception,"fail 3");
    }
  
  if( Preempt(actual_priority,getPriority()) )
    Printf(out,"Task[#;!#;!#;!]",index,getPriority(),actual_priority);
  else
    Printf(out,"Task[#;!#;!]",index,getPriority());
   
  if( owned_list ) TaskList::Print(out,owned_list);
  
  TaskPriority pri=actual_priority;
  
  if( list )
    {
     list->printInfo(out);
     
     TaskBase *ptr=list->owner;
     
     while( ptr )
       {
        if( ptr->mark==index )
          {
           Printf(out," (#;) loop",ptr->index);
           
           LoopCount++;
           
           break;
          }
        
        ptr->mark=index;
        
        Printf(out," (#;!#;!)",ptr->index,ptr->actual_priority);
        
        if( Preempt(pri,ptr->actual_priority) )
          {
           Printf(Exception,"fail 4");
          }
         
        pri=ptr->actual_priority; 
        
        if( ptr->list )
          {
           ptr->list->printInfo(out);
           
           ptr=ptr->list->owner;
          }
        else
          {
           break;
          }
       }
    }
  
  Printf(out,"\n\n");
 }

/* class Engine */

class Engine : NoCopy
 {
   static const ulen TaskCount = 500 ;
   static const ulen ListCount = 100 ;
   static const ulen Repeat = 10 ;
  
  private:
  
   Random random;
   
   DynArray<TaskBase,ArrayAlgo_mini<TaskBase> > task_pool;
   DynArray<TaskList,ArrayAlgo_mini<TaskList> > list_pool;
   
  private:
   
   TaskPriority random_priority() { return random.select(100u,110u); }
   
   void check();
   
   void print();
   
   //---------
   
   void put(TaskBase &task,TaskList &list) { if( !task.getList() ) list.put(&task); }
   
   void del(TaskBase &task) { task.delList(); }
   
   void take(TaskBase &task,TaskList &list) { if( !list.getOwner() && !task.getList() ) list.setOwner(&task); }
   
   void free(TaskList &list) { if( TaskBase *task=list.getOwner() ) list.clearOwner(task); }
   
   //---------
   
   void put(ulen t,ulen i) { put(task_pool[t],list_pool[i]); }
   
   void del(ulen t) { del(task_pool[t]); }
   
   void take(ulen t,ulen i) {  take(task_pool[t],list_pool[i]);  }
   
   void free(ulen i) { free(list_pool[i]); }
   
   //---------
   
   void put() 
    {
     ulen i=random.select(ListCount);
     
     for(ulen cnt=Repeat; cnt ;cnt--) put(random.select(TaskCount),i); 
    }
   
   void del() { del(random.select(TaskCount)); }
   
   void take() 
    {
     ulen t=random.select(TaskCount);
     
     for(ulen cnt=Repeat; cnt ;cnt--) take(t,random.select(ListCount)); 
    }
   
   void free() { free(random.select(ListCount)); }
   
   //---------
   
   void step();
   
  public: 
   
   Engine()
    : task_pool(DoReserve,TaskCount),
      list_pool(DoReserve,ListCount)
    {
     for(ulen index=TaskCount; index ;index--) task_pool.append_fill(random_priority(),index);
     
     for(ulen index=ListCount; index ;index--) list_pool.append_fill(index);
    }
   
   ~Engine()
    {
    }
   
   void run(ulen count)
    {
     for(; count ;count--) step();
     
     print();
    }
 };

void Engine::check()
 {
  for(TaskBase &obj : task_pool) obj.check();
  
  for(TaskList &obj : list_pool) obj.check();
 }

void Engine::print()
 {
  PrintFile out("test300.txt");
  
  Printf(out,"Deadlocks = #;\n\n",TaskList::GetDeadlockCount());
  
  for(TaskBase &obj : task_pool) obj.print(out);
  
  for(TaskList &obj : list_pool) obj.print(out);
  
  Printf(out,"Loops = #;\n\n",TaskBase::GetLoopCount());
  
  Printf(Con,"Deadlocks = #;\n\n",TaskList::GetDeadlockCount());
  Printf(Con,"Loops = #;\n\n",TaskBase::GetLoopCount());
 }

void Engine::step()
 {
  switch( random.select(4) )
    {
     case 0 : put(); break;
     case 1 : del(); break;
     case 2 : take(); break;
     case 3 : free(); break;
    }
  
  check();
 }

} // namespace Private_0300
 
using namespace Private_0300; 
 
/* Testit<300> */ 

template<>
const char *const Testit<300>::Name="Test300 TaskList";

template<>
bool Testit<300>::Main() 
 {
  Engine engine;
  
  engine.run(10000000);
  
  return true;
 }
 
} // namespace App
 
