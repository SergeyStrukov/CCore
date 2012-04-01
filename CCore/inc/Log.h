/* Log.h */ 
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

#ifndef CCore_inc_Log_h
#define CCore_inc_Log_h
 
#include <CCore/inc/Timer.h>
#include <CCore/inc/TextLabel.h>
#include <CCore/inc/PrintTime.h>
#include <CCore/inc/PrintTitle.h>
#include <CCore/inc/List.h>

#include <CCore/inc/task/NoMutex.h>

namespace CCore {

/* classes */ 

template <class Src,class Type> class LogCategory_enum;

template <class Src,class Type> class LogFilter_enum;

class LogStamp;

class LogCounter;

class LogMem;

template <class Cat,class Stamp> class LogMsgBase;

template <class Cat,class Stamp> class LogStorage;

template <class Cat,class Stamp,class ... TT> class LogMsg;

template <class Cat,class Stamp,class Filter,class Mutex=NoMutex> class UserLog;

/* class LogCategory_enum<Src,Type> */ 

template <class Src,class Type> // Src and Type are uint5 enums
class LogCategory_enum
 {
   unsigned value;
   
  public:
   
   // constructors
  
   LogCategory_enum() : value(0) {}
  
   LogCategory_enum(Src src_,Type type_)
    {
     unsigned src=src_;
     unsigned type=type_;
    
     value=((src&31)<<5)|(type&31);
    }
   
   // methods
   
   Src getSource() const { return Src((value>>5)&31); }
  
   Type getType() const { return Type(value&31); }
   
   // print object
 
   template <class P> 
   void print(P &out) const
    {
     Printf(out,"#;:#;",getSource(),getType());
    }
 };
 
/* class LogFilter_enum<Src,Type> */ 
 
template <class Src,class Type> // Src and Type are uint5 enums
class LogFilter_enum
 {
   // disable masks
  
   uint32 src_mask;
   uint32 type_mask;
   
  private:
  
   static uint32 Bit(unsigned i) { return uint32(1)<<i; }
 
  public:
   
   // constructors
  
   LogFilter_enum() : src_mask(0),type_mask(0) {} // enable all
   
   LogFilter_enum(LogCategory_enum<Src,Type> cat) // filter all other cats
    {
     src_mask = ~Bit(cat.getSource()) ;
     type_mask = ~Bit(cat.getType()) ;
    }
   
   // enable/disable
   
   void enable(Src src) { BitClear(src_mask,Bit(src)); }
    
   void enable(Type type) { BitClear(type_mask,Bit(type)); }
    
   void disable(Src src) { BitSet(src_mask,Bit(src)); }
    
   void disable(Type type) { BitSet(type_mask,Bit(type)); }
   
   // filter all cats with disabled src OR disabled type
   
   bool operator () (LogCategory_enum<Src,Type> cat) const
    {
     return ( src_mask&Bit(cat.getSource()) ) || ( type_mask&Bit(cat.getType()) ) ;
    }
 };
 
/* class LogStamp */ 
 
class LogStamp
 {
   ulen num;
   SecTimer::ValueType time_sec;
   ClockDiffTimer::ValueType time_clock;
   
  public: 
  
   // constructors
   
   LogStamp() : num(0),time_sec(0),time_clock(0) {}
   
   // print object
   
   template <class P> 
   void print(P &out) const
    {
     Printf(out,"#;) [#;,#6r;]",num,PrintTime(time_sec),time_clock);
    }
   
   // Host
    
   class Host : NoCopy
    {
      ulen num;
      SecTimer sec_timer;
      ClockDiffTimer clock_timer;
      
     public:
     
      Host() : num(0) {}
      
      void operator () (LogStamp &stamp)
       {
        stamp.num=num++;
        stamp.time_sec=sec_timer.get();
        stamp.time_clock=clock_timer.get();
       }
    };
 };
 
/* class LogCounter */ 

class LogCounter
 {
   ulen total;
   ulen committed;
 
  public:
  
   // constructors
   
   LogCounter()
    {
     total=0;
     committed=0;
    }
   
   // count
   
   void alloc() { total++; }
   
   void commit() { committed++; }
   
   // print object
   
   template <class P> 
   void print(P &out) const
    {
     Printf(out,"total = #;",total);
     
     if( ulen skipped=total-committed ) Printf(out," skipped = #;",skipped);
    }
 };
 
/* class LogMem */  
 
class LogMem : NoCopy
 {
   byte *mem;
   byte *mem_lim;
   
   byte *ptr;
   byte *lim;
   byte *cut;
   
   bool free_mem;
   
  private: 
   
   void init(void *mem,ulen mem_len,bool free_mem);
   
  public:
  
   // constructors
   
   explicit LogMem(ulen mem_len); 
   
   explicit LogMem(Space space); // space.mem aligned
   
   ~LogMem();
   
   // methods
   
   void clear();
   
   void * alloc(ulen len);
   
   void free(void *ret);
   
   void del(void *beg);
 };
 
/* class LogMsgBase<Cat,Stamp> */ 
 
template <class Cat,class Stamp> 
class LogMsgBase : NoCopy
 {
   Cat cat;
   Stamp stamp;
   void *mem;
   SLink<LogMsgBase<Cat,Stamp> > link;
   
  private: 
   
   friend class LogStorage<Cat,Stamp>;
   
   virtual void printBody(PrintBase &) const {}
   
  public:
  
   // constructors
   
   explicit LogMsgBase(Cat cat_) : cat(cat_) {}
   
   virtual ~LogMsgBase() {}
   
   // methods
   
   Cat getCategory() const { return cat; }
   
   // print object
   
   void print(PrintBase &out) const
    {
     Printf(out,"#; #;> ",stamp,cat);
 
     printBody(out);
  
     Printf(out,"\n#;\n",TextDivider());
    }
 };
 
/* class LogStorage<Cat,Stamp> */ 
 
template <class Cat,class Stamp> 
class LogStorage : NoCopy
 {
   typedef typename SLink<LogMsgBase<Cat,Stamp> >::template LinearAlgo<&LogMsgBase<Cat,Stamp>::link> Algo;
   
  private: 
  
   LogCounter counter;
   LogMem logmem;
   typename Stamp::Host stamp_host;
   
   typename Algo::FirstLast list;
   typename Algo::Cur cur;
   
   ulen count;
   bool overrun;
   
  private:
  
   bool delOne();
   
  public:
  
   // constructors
   
   explicit LogStorage(ulen mem_len,bool overrun=true);
   
   explicit LogStorage(Space space,bool overrun=true); // space.mem aligned
   
   ~LogStorage();
   
   // methods
   
   ulen getCount() const { return count; }
   
   void getCounter(LogCounter &ret) const { ret=counter; }
   
   void setOverrun(bool overrun_) { overrun=overrun_; }
   
   void delAll();
   
   // message
   
   void * alloc(ulen msg_len);
   
   void free(void *mem);
   
   void commit(void *mem,LogMsgBase<Cat,Stamp> *msg);
   
   // cursor
   
   const LogMsgBase<Cat,Stamp> * startCursor(); 
   
   const LogMsgBase<Cat,Stamp> * nextCursor(); 
    
   void stopCursor();
 };
 
template <class Cat,class Stamp> 
bool LogStorage<Cat,Stamp>::delOne()
 {
  if( LogMsgBase<Cat,Stamp> *todel=list.first )
    {
     if( todel==cur.ptr ) return false;
     
     list.del_first();
    
     todel->~LogMsgBase();
        
     if( list.first )
       {
        logmem.del(list.first->mem);
       }
     else
       {
        logmem.clear();
       }
       
     count--;  
    
     return true;
    }
    
  return false;  
 }
 
 // constructors

template <class Cat,class Stamp> 
LogStorage<Cat,Stamp>::LogStorage(ulen mem_len,bool overrun_)
 : logmem(mem_len),cur(0)
 {
  count=0;
  overrun=overrun_;
 }
   
template <class Cat,class Stamp> 
LogStorage<Cat,Stamp>::LogStorage(Space space,bool overrun_)
 : logmem(space),cur(0)
 {
  count=0;
  overrun=overrun_;
 }
   
template <class Cat,class Stamp> 
LogStorage<Cat,Stamp>::~LogStorage()
 {
  delAll();
 }
   
 // methods

template <class Cat,class Stamp> 
void LogStorage<Cat,Stamp>::delAll()
 {
  while( delOne() );
 }
   
 // message

template <class Cat,class Stamp> 
void * LogStorage<Cat,Stamp>::alloc(ulen msg_len)
 {
  counter.alloc();
 
  if( !overrun ) return logmem.alloc(msg_len);
 
  do
    {
     if( void *ret=logmem.alloc(msg_len) ) return ret;
    }
  while( delOne() );   
    
  return 0;  
 }
   
template <class Cat,class Stamp> 
void LogStorage<Cat,Stamp>::free(void *mem)
 {
  logmem.free(mem);
 }
   
template <class Cat,class Stamp> 
void LogStorage<Cat,Stamp>::commit(void *mem,LogMsgBase<Cat,Stamp> *msg)
 {
  counter.commit();
 
  stamp_host(msg->stamp);
  
  msg->mem=mem;
  
  list.ins_last(msg);
  
  count++;
 }
 
 // cursor

template <class Cat,class Stamp> 
const LogMsgBase<Cat,Stamp> * LogStorage<Cat,Stamp>::startCursor() 
 { 
  if( +cur ) return 0; 
  
  cur=list.start();
  
  return cur.ptr; 
 }

template <class Cat,class Stamp> 
const LogMsgBase<Cat,Stamp> * LogStorage<Cat,Stamp>::nextCursor() 
 { 
  if( !cur ) return 0; 
  
  ++cur;
  
  return cur.ptr;
 }
 
template <class Cat,class Stamp> 
void LogStorage<Cat,Stamp>::stopCursor() 
 { 
  cur=typename Algo::Cur(0); 
 }

/* class LogMsg<Cat,Stamp,TT> */ 

template <class Cat,class Stamp>
class LogMsg<Cat,Stamp> : public LogMsgBase<Cat,Stamp>
 {
   const char *format;
   
  private: 
   
   virtual void printBody(PrintBase &out) const
    {
     Printf(out,format);
    }
   
  public: 
  
   LogMsg(Cat cat,const char *format_)
    : LogMsgBase<Cat,Stamp>(cat),format(format_) {}
 };
 
template <class Cat,class Stamp,class T,class ... TT>
class LogMsg<Cat,Stamp,T,TT...> : public LogMsgBase<Cat,Stamp>
 {
   const char *format;
   Tuple<T,TT...> data;
   
  private: 
   
   virtual void printBody(PrintBase &out) const
    {
     Printf(out,format,data);
    }
   
  public: 
  
   LogMsg(Cat cat,const char *format_,const T &t,const TT & ... tt)
    : LogMsgBase<Cat,Stamp>(cat),format(format_),data(t,tt...) {}
 };
 
/* class UserLog<Cat,Stamp,Filter,Mutex> */ 
 
template <class Cat,class Stamp,class Filter,class Mutex> 
class UserLog : NoCopy
 {
   LogStorage<Cat,Stamp> storage;
   Filter filter;
   TextLabel name;
   mutable Mutex mutex;
   
  private: 
 
   typedef typename Mutex::Lock Lock;
 
  public:
   
   // constructors
  
   UserLog(TextLabel name_,ulen mem_len,bool overrun=true)
    : storage(mem_len,overrun),
      name(name_),
      mutex(name_)
    {
    }
   
   UserLog(TextLabel name_,Space space,bool overrun=true) // space.mem aligned
    : storage(space,overrun),
      name(name_),
      mutex(name_)
    {
    }
   
   ~UserLog() {}
   
   // methods
   
   TextLabel getName() const { return name; }
   
   void getCounter(LogCounter &ret) const 
    {
     Lock lock(mutex);
    
     storage.getCounter(ret);
    }
   
   void setOverrun(bool overrun) 
    {
     Lock lock(mutex);
    
     storage.setOverrun(overrun);
    }
    
   void setFilter(Filter filter_)
    {
     Lock lock(mutex);
     
     filter=filter_;
    }
   
   void getFilter(Filter &ret) const
    {
     Lock lock(mutex);
     
     ret=filter;
    }
   
   // message
   
   class Access; 
    
   template <class ... TT> 
   void operator () (Cat cat,const char *format,const TT & ... tt);
   
   // cursor
    
   class Cursor;
   
   // print
   
   class PrintFunc;
   
   PrintFunc getPrint(ulen count,Filter filter=Filter());
 };
 
 // message

template <class Cat,class Stamp,class Filter,class Mutex> 
class UserLog<Cat,Stamp,Filter,Mutex>::Access : NoCopy
 {
   UserLog<Cat,Stamp,Filter,Mutex> &log;
   Lock lock;
   void *mem;
 
  public:
  
   explicit Access(UserLog<Cat,Stamp,Filter,Mutex> &log_,Cat cat,ulen msg_len)
    : log(log_),
      lock(log.mutex)
    {
     if( log.filter(cat) )
       mem=0;
     else
       mem=log.storage.alloc(msg_len);  
    }
   
   ~Access()
    {
     if( mem ) log.storage.free(mem);
    }
   
   operator void * () const { return mem; }
   
   void commit(LogMsgBase<Cat,Stamp> *msg)
    {
     log.storage.commit(Replace_null(mem),msg);
    }
 };
 
template <class Cat,class Stamp,class Filter,class Mutex> 
template <class ... TT> 
void UserLog<Cat,Stamp,Filter,Mutex>::operator () (Cat cat,const char *format,const TT & ... tt)
 {
  typedef LogMsg<Cat,Stamp,TT...> MsgType;
  
  Access access(*this,cat,sizeof (MsgType));
 
  if( access )
    {
     MsgType *msg=new(PlaceAt(access)) MsgType(cat,format,tt...);
     
     access.commit(msg);
    } 
 }
    
 // cursor

template <class Cat,class Stamp,class Filter,class Mutex> 
class UserLog<Cat,Stamp,Filter,Mutex>::Cursor
 {
   UserLog<Cat,Stamp,Filter,Mutex> &log;
   ulen count;
   const LogMsgBase<Cat,Stamp> *cur;
   
  public:
   
   // constructors
  
   Cursor(UserLog<Cat,Stamp,Filter,Mutex> &log_,ulen count_)
    : log(log_),
      count(count_)
    {
     if( count )
       {
        count--;
        
        Lock lock(log.mutex);
     
        cur=log.storage.startCursor();
       }
     else
       {
        cur=0;
       }  
    }
   
   ~Cursor()
    {
     if( !cur ) return;

     Lock lock(log.mutex);
     
     log.storage.stopCursor();
    }
   
   // object ptr
    
   bool operator + () const { return cur!=0; }
   
   bool operator ! () const { return cur==0; }
   
   const LogMsgBase<Cat,Stamp> * getPtr() const { return cur; }
   
   const LogMsgBase<Cat,Stamp> & operator * () const { return *cur; }
    
   const LogMsgBase<Cat,Stamp> * operator -> () const { return cur; }
   
   // cursor
   
   void operator ++ ()
    {
     if( !cur ) return;
 
     if( count )
       {
        count--;
     
        Lock lock(log.mutex);
     
        cur=log.storage.nextCursor();
       }
     else
       {
        cur=0;
     
        Lock lock(log.mutex);
     
        log.storage.stopCursor();
       }  
    }
 };
    
 // print

template <class Cat,class Stamp,class Filter,class Mutex> 
class UserLog<Cat,Stamp,Filter,Mutex>::PrintFunc
 {
   UserLog<Cat,Stamp,Filter,Mutex> &log;
   ulen count;
   Filter filter;
   
  public: 
  
   PrintFunc(UserLog<Cat,Stamp,Filter,Mutex> &log_,ulen count_,Filter filter_)
    : log(log_),
      count(count_),
      filter(filter_) 
    {
    }
    
   template <class P>
   void print(P &out) const
    {
     LogCounter cnt;
     
     log.getCounter(cnt);
  
     Printf(out,"#;\n#;\n#;\n",PrintTitle(log.getName()),cnt,TextDivider());
  
     for(Cursor cur(log,count); +cur ;++cur) 
       if( !filter(cur->getCategory())  )
         Putobj(out,*cur);
    }
 };
 
template <class Cat,class Stamp,class Filter,class Mutex> 
auto UserLog<Cat,Stamp,Filter,Mutex>::getPrint(ulen count,Filter filter) -> PrintFunc
 {
  return PrintFunc(*this,count,filter);
 }
 
/* PrintLog() */  

template <class Cat,class Stamp,class Filter,class Mutex> 
auto PrintLog(UserLog<Cat,Stamp,Filter,Mutex> &log,ulen count,Filter filter) -> typename UserLog<Cat,Stamp,Filter,Mutex>::PrintFunc
 {
  return log.getPrint(count,filter);
 }
 
template <class Cat,class Stamp,class Filter,class Mutex> 
auto PrintLog(UserLog<Cat,Stamp,Filter,Mutex> &log,ulen count) -> typename UserLog<Cat,Stamp,Filter,Mutex>::PrintFunc
 {
  return log.getPrint(count);
 }
 
} // namespace CCore
 
#endif
 

