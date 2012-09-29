/* test0104.ParaSort.cpp */ 
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
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Task.h>

namespace App {

namespace Private_0104 {

/* consts */

const ulen Count = 1000 ;

/* struct SortEvent */

struct SortEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint8 job_number;
  uint32 off;
  uint32 len;
  
  void init(EventTimeType time_,EventIdType id_,uint8 job_number_,uint32 off_,uint32 len_)
   {
    time=time_;
    id=id_;
    
    job_number=job_number_;
    off=off_;
    len=len_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<SortEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<SortEvent *>(ptr)->id); }
  
  static void * Offset_job(void *ptr) { return &(static_cast<SortEvent *>(ptr)->job_number); }
  
  static void * Offset_off(void *ptr) { return &(static_cast<SortEvent *>(ptr)->off); }
  
  static void * Offset_len(void *ptr) { return &(static_cast<SortEvent *>(ptr)->len); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id=info.addStruct("SortEvent")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .addField_uint8("job",Offset_job)
                .addField_uint32("off",Offset_off)
                .addField_uint32("len",Offset_len)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

/* struct SortStartEvent */

struct SortStartEvent
 {
  EventTimeType time;
  EventIdType id;
  
  uint32 len;
  
  void init(EventTimeType time_,EventIdType id_,uint32 len_)
   {
    time=time_;
    id=id_;
    
    len=len_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<SortStartEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<SortStartEvent *>(ptr)->id); }
  
  static void * Offset_len(void *ptr) { return &(static_cast<SortStartEvent *>(ptr)->len); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id=info.addStruct("SortStartEvent")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .addField_uint32("len",Offset_len)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

/* struct SortStopEvent */

struct SortStopEvent
 {
  EventTimeType time;
  EventIdType id;
  
  void init(EventTimeType time_,EventIdType id_)
   {
    time=time_;
    id=id_;
   }
  
  static void * Offset_time(void *ptr) { return &(static_cast<SortStopEvent *>(ptr)->time); }
  
  static void * Offset_id(void *ptr) { return &(static_cast<SortStopEvent *>(ptr)->id); }
  
  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
   {
    auto id=info.addStruct("SortStopEvent")
                .addField_uint32("time",Offset_time)
                .addField_uint16("id",Offset_id)
                .getId();
    
    desc.setStructId(info,id);
   }
 };

/* struct ParaSort<Ran,Ctx> */

template <class Ran,class Ctx=SortCtx<Ran> >
struct ParaSort
 {
  static const ulen MinLen      = 1000 ;
  static const ulen JobQueueLen =  100 ;
  static const ulen SplitLim    = 1000 ;
  static const ulen SpawnLim    =  500 ;
 
  template <class Len> class SortEngine;
 
  template <class Len>
  static void Sort(Ran a,Len len,Ctx ctx);
  
  template <class Len>
  static void Sort(Ran a,Len len) { Sort(a,len,Ctx()); }
 };
 
template <class Ran,class Ctx>
template <class Len>
class ParaSort<Ran,Ctx>::SortEngine : public Funchor_nocopy
 {
   struct Unit
    {
     Ran a;
     Len len;

     Unit() : a(),len() {}
       
     Unit(Ran a_,Len len_) : a(a_),len(len_) {}
    };
      
   FifoBuf<Unit,JobQueueLen> queue;
   
   Mutex mutex;
   Sem sem;
   Atomic active;
   
   Ctx ctx;
   
   Ran beg;
   Atomic number;
   
  private:
    
   bool put(Unit unit)
    {
     Mutex::Lock lock(mutex);
     
     return queue.put(unit);
    }
     
   bool get(Unit &unit)
    {
     Mutex::Lock lock(mutex);
     
     return queue.get(unit);
    }
    
   void spawn(Ran a,Len len);
     
   void sort(Ran a,Len len);
    
  public:
    
   SortEngine(Ctx ctx,Ran a,Len len);
     
   ~SortEngine() {}
     
   void job();
   
   Function<void (void)> function_job() { return FunctionOf(this,&SortEngine::job); }
 };
   
template <class Ran,class Ctx>
template <class Len>
void ParaSort<Ran,Ctx>::SortEngine<Len>::spawn(Ran a,Len len)
 {
  if( len<SpawnLim )
   {
    QuickSort<Ran,Ctx>::Sort(a,len,ctx);
    
    return;
   }
  
  if( put(Unit(a,len)) )
    {
     active++;
     
     sem.give();
    }
  else
    {
     sort(a,len);
    }
 }
     
template <class Ran,class Ctx>
template <class Len>
void ParaSort<Ran,Ctx>::SortEngine<Len>::sort(Ran a,Len len)
 {
  Len S=len;
  
  if( len<SplitLim )
    {
     QuickSort<Ran,Ctx>::Sort(a,len,ctx);
     
     return;
    }
 
  while( !ShortSort<Ran,Ctx>::Sort(a,len,ctx) )
    {
     Len D=len/16;
     
     if( D<S )
       {
        S-=D;
       }
     else
       {
        HeapSort<Ran,Ctx>::Sort(a,len,ctx);
        
        return;
       }
    
     Ran p=QuickSort<Ran,Ctx>::Partition(a,a+(len/2),a+(len-1),ctx);
     
     Len len1=Len(p-a);
     Len len2=Len(len-1-len1);
     
     if( len1<=len2 )
       {
        spawn(a,len1);
        
        a=p+1;
        len=len2;
       }
     else
       {
        spawn(p+1,len2);
        
        len=len1;
       }
    }
 }
 
template <class Ran,class Ctx>
template <class Len>
ParaSort<Ran,Ctx>::SortEngine<Len>::SortEngine(Ctx ctx_,Ran a,Len len)
 : mutex("ParaSort"),
   sem("ParaSort"),
   ctx(ctx_),
   beg(a)
 {
  number=1;
  
  spawn(a,len);
 }
     
template <class Ran,class Ctx>
template <class Len>
void ParaSort<Ran,Ctx>::SortEngine<Len>::job()
 {
  uint8 job_number=(uint8)(number++);
  
  for(;;)
    {
     sem.take();
     
     Unit unit;
     
     if( get(unit) )
       {
        TaskEventHost.add<SortEvent>(job_number,(uint32)(unit.a-beg),(uint32)unit.len);      
       
        sort(unit.a,unit.len);
        
        active--;
       }

     if( active==0 )
       {
        sem.give();
        
        break;
       }
    }
 }
     
template <class Ran,class Ctx>
template <class Len>
void ParaSort<Ran,Ctx>::Sort(Ran a,Len len,Ctx ctx)
 {
  TaskEventHost.add<SortStartEvent>((uint32)len);      
  
  if( len<MinLen )
    {
     QuickSort<Ran,Ctx>::Sort(a,len,ctx);
    }
  else
    {  
     SortEngine<Len> engine(ctx,a,len); 
     
     Job job(engine.function_job());
    }
  
  TaskEventHost.add<SortStopEvent>();      
 }

/* class Engine<Algo> */

template <template <class Ran,class Ctx> class Algo>
class Engine
 {
   typedef unsigned Type; 
 
   Random random;
   
  private:
  
   Type next() { return random.next_uint<unsigned>(); }
  
   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) *(ptr++)=next();
    }
 
   ClockTimer::ValueType sort(Type *ptr,ulen len)
    {
     ClockTimer timer;
     
     Algo<Type *,SortCtx<Type *> >::Sort(ptr,len);
     
     return timer.get();
    }
    
  public:
  
   Engine() {}
   
   ~Engine() {}
   
   void run_once(ulen len)
    {
     Printf(Con,"len = #8;  ",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();
     
     fill(ptr,len);
     
     ClockTimer::ValueType t=sort(ptr,len);
       
     Printf(Con,"time = #3;\n",t/len);  
    }
   
   void run(ulen len)
    {
     Printf(Con,"len = #8;  ",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();
     
     TimeStat<ClockTimer::ValueType> stat;
     
     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);
        
        ClockTimer::ValueType t=sort(ptr,len);
        
        stat.add(t);
       }
       
     stat.div(len);  
       
     Printf(Con,"#3;\n",stat);  
    }
 };

} // namespace Private_0104
 
using namespace Private_0104; 
 
/* Testit<104> */ 

template<>
const char *const Testit<104>::Name="Test104 ParaSort";

template<>
bool Testit<104>::Main() 
 {
#if 1
  
  Printf(Con,"\n#;\n\n",Title("ParaSort"));

  {
   TaskEventRecorder recorder(100_MByte);
  
   {
    TaskEventHostType::StartStop start_stop(TaskEventHost,&recorder); 
    
    Printf(Con,"extra task count = #;\n\n",Job::Init::DefaultTaskCount());

    Job::Init job_init;
  
    Engine<ParaSort> engine;
 
    engine.run(10000);
    engine.run(100000);
    engine.run(1000000);
   }
  
   PrintFile out("test104.txt");
  
   Putobj(out,recorder);
  } 
  
  Printf(Con,"\n#;\n\n",Title("QuickSort"));
  
  {
   Engine<QuickSort> engine;
  
   engine.run(10000);
   engine.run(100000);
   engine.run(1000000);
  }
  
#else
  
  TaskEventRecorder recorder(100_MByte);
 
  {
   TaskEventHostType::StartStop start_stop(TaskEventHost,&recorder); 
   
   Job::Init job_init;
 
   Engine<ParaSort> engine;

   engine.run_once(10000);
  }
 
  PrintFile out("test104.txt");
 
  Putobj(out,recorder);
  
#endif
  
  return true;
 }
 
} // namespace App
 
