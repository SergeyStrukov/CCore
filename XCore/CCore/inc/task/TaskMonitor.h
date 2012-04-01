/* TaskMonitor.h */ 
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

#ifndef CCore_inc_task_TaskMonitor_h
#define CCore_inc_task_TaskMonitor_h

#include <CCore/inc/task/TaskPriority.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/TextLabel.h>
#include <CCore/inc/Timer.h>
 
namespace CCore {

/* classes */ 

class TaskMonitor;

class TaskMonitor_CPU;

/* class TaskMonitor */ 

class TaskMonitor : NoCopy
 {
  public:
  
   class Record
    {
     private:
     
      friend class TaskMonitor;
      
      // IntLocked
     
      virtual void transit(Record *from,Record *to)=0; 
   
      void begin() { transit(0,this); }
   
      void end() { transit(this,0); }
      
     public:
  
      Record() {}
   
      ~Record() {}
    };
   
   class Link : NoCopy
    {
      TextLabel name;
      TaskPriority priority;
      
      DLink<Link> link;
      TaskMonitor *monitor;
      Record *record;
      
     private: 
     
      friend class TaskMonitor;
      
      void init();
      
      // IntLocked
   
      Record * get(TaskMonitor *monitor); 
      
     public:
  
      Link(TextLabel name,TaskPriority priority);
   
      ~Link();
      
      TextLabel getName() const { return name; }
      
      TaskPriority getPriority() const { return priority; }
    };
   
   class StartStop : NoCopy
    {
      TaskMonitor *obj;
   
     public: 
  
      explicit StartStop(TaskMonitor &obj_) : obj(&obj_) { obj->start(); }
      
      void stop() { if( obj ) Replace_null(obj)->stop(); }
   
      ~StartStop() { if( obj ) obj->stop(); }
    };
  
  private:
  
   static TaskMonitor * Active;
   
   DLink<Link>::LinearAlgo<&Link::link>::Top top;
  
  private:
  
   virtual void prepare()=0;
   
   virtual void complete()=0;
   
   void start();
   
   void stop();
   
   // IntLocked
   
   virtual Record * alloc(TextLabel name,TaskPriority priority)=0;
   
   virtual Record * getInt()=0;
   
   static Link * GetCurrent();
  
  protected:
  
   void guardStopped() const;
  
  public:
  
   TaskMonitor();
   
   ~TaskMonitor();
   
   struct Internal;
 };
 
/* struct TaskMonitor::Internal */  

struct TaskMonitor::Internal
 {
  // IntLocked
   
  static void Transit(Link *from,Link *to);
   
  static void BeginInt();
   
  static void EndInt();
 };
 
/* class TaskMonitor_CPU */ 

class TaskMonitor_CPU : public TaskMonitor
 {
  private:
  
   class Record_CPU : public NoCopyBase<Record>
    {
      TextLabel name;
      TaskPriority priority;
      
      enum Type
       {
        Type_None,
        Type_Task,
        Type_Int,
        Type_Other
       };
      
      Type type;
      
      ClockTimer::ValueType start_time;
      uint64 run_time;
      unsigned percent;
    
     private:
     
      void init();
      
      void start(ClockTimer::ValueType t);
      
      void stop(ClockTimer::ValueType t);
     
      virtual void transit(Record *from,Record *to);
      
     public:
     
      Record_CPU();
      
      void init(TextLabel name_,TaskPriority priority_);
      
      void init_int();
      
      void init_other();
      
      uint64 getRunTime() const { return run_time; }
      
      void setPercent(uint64 total) { percent=unsigned( (run_time*100)/total ); }
      
      template <class P>
      void print(P &out) const
       {
        switch( type )
         {
          case Type_Task :
           {
            Printf(out,"#20l; #8r; #20r; clk #3r; %",name,priority,run_time,percent);
           }
          break;
          
          case Type_Int :
           {
            Printf(out,"#20l; -------- #20r; clk #3r; %",name,run_time,percent);
           }
          break;
          
          case Type_Other :
           {
            Printf(out,"#20l; -------- #20r; clk #3r; %",name,run_time,percent);
           }
          break;
         }
       }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
    
   DynArray<Record_CPU> buf;
   ulen len;
 
  private:
   
   PtrLen<Record_CPU> getRange() { return Range(buf.getPtr(),len); }
  
   PtrLen<const Record_CPU> getRange() const { return Range(buf.getPtr(),len); }
   
   virtual void prepare();
   
   virtual void complete();
   
   virtual Record * alloc(TextLabel name,TaskPriority priority);
   
   virtual Record * getInt();
   
  public:
   
   static const ulen DefaultBufLen = 100 ;
  
   explicit TaskMonitor_CPU(ulen buf_len=DefaultBufLen);
   
   ~TaskMonitor_CPU();
   
   template <class P>
   void print(P &out) const
    {
     guardStopped();
     
     Printf(out,"\n#;\n\n",Title("CPU usage"));
     
     for(auto r=getRange(); +r ;++r) Printf(out,"#;\n",*r);
     
     Printf(out,"\n#;\n",TextDivider());
    }
 };
 
} // namespace CCore
 
#endif
 

