/* SysWaitInternal.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysWaitInternal_h
#define CCore_inc_sys_SysWaitInternal_h

#include <CCore/inc/sys/SysWait.h>
#include <CCore/inc/sys/SysAbort.h>

#include <CCore/inc/Array.h>

#include <CCore/inc/win32/Win32.h>
 
namespace CCore {
namespace Sys {

/* functions */

void GuardError(ErrorType error=NonNullError());

inline void Guard(bool nok) { if( nok ) GuardError(); }

/* classes */

class WaitSem;

struct WaitFile;

struct WaitNet;

template <class AsyncState,class Wait> class WaitBase;

/* class WaitSem */

class WaitSem : NoCopy
 {
   Win32::handle_t h_sem;
  
  public:
   
   WaitSem();
   
   ~WaitSem();
   
   Win32::handle_t getHandle() { return h_sem; }
   
   void give();
 };

/* struct WaitFile */

struct WaitFile
 {
  static Win32::handle_t CreateEvent()
   {
    return Win32::CreateEventA(0,true,false,0);
   }
  
  static Win32::bool_t DestroyEvent(Win32::handle_t h_event)
   {
    return Win32::CloseHandle(h_event);
   }
  
  static WaitResult WaitSome(Win32::handle_t *hlist,ulen hcount,MSec timeout)
   {
    auto result=Win32::WaitForMultipleObjects(hcount,hlist,false,+timeout);
       
    switch( result )
      {
       case Win32::WaitFailed : return Wait_error; 
        
       case Win32::WaitTimeout : return Wait_timeout;
       
       default: 
        {
         ulen slot;
         
         if( result>=Win32::WaitObject_0 && (slot=ulen(result-Win32::WaitObject_0))<hcount )
           {
            return WaitResult(slot);
           }
         else
           {
            return Wait_error;
           }
        }
      }
   }
 };

/* struct WaitNet */

struct WaitNet
 {
  static Win32::handle_t CreateEvent()
   {
    return Win32::WSACreateEvent();
   }
  
  static Win32::bool_t DestroyEvent(Win32::handle_t h_event)
   {
    return Win32::WSACloseEvent(h_event);
   }
  
  static WaitResult WaitSome(Win32::handle_t *hlist,ulen hcount,MSec timeout)
   {
    auto result=Win32::WSAWaitForMultipleEvents(hcount,hlist,false,+timeout,false);
       
    switch( result )
      {
       case Win32::WSAWaitFailed : return Wait_error; 
        
       case Win32::WSAWaitTimeout : return Wait_timeout;
       
       default: 
        {
         ulen slot;
         
         if( result>=Win32::WSAWaitObject_0 && (slot=ulen(result-Win32::WSAWaitObject_0))<hcount )
           {
            return WaitResult(slot);
           }
         else
           {
            return Wait_error;
           }
        }
      }
   }
  
  static WaitResult WaitAll(Win32::handle_t *hlist,ulen hcount,MSec timeout)
   {
    auto result=Win32::WSAWaitForMultipleEvents(hcount,hlist,true,+timeout,false);
    
    switch( result )
      {
       case Win32::WSAWaitFailed : return Wait_error;
        
       case Win32::WSAWaitTimeout : return Wait_timeout;
       
       default: 
        {
         if( result>=Win32::WSAWaitObject_0 && ulen(result-Win32::WSAWaitObject_0)<hcount )
           {
            return WaitResult(0);
           }
         else
           {
            return Wait_error;
           }
        }
      }
   }
 };

/* class WaitBase<AsyncState,Wait> */

template <class AsyncState,class Wait>
class WaitBase : public MemBase_nocopy
 {
   class State : NoCopy
    {
      AsyncState state;
      
     public: 
      
      ulen slot;
      
      State();
      
      ~State();
      
      Win32::handle_t getHandle() { return state.olap.h_event; }
      
      AsyncState * getAsync() { return &state; }
      
      struct Flags
       {
        enum NoThrowFlagType
         {
          Default_no_throw = false,
          Copy_no_throw = true
         };
       };
    };
   
  private:
   
   SimpleArray<State,ArrayAlgo<State,typename State::Flags> > state_buf;
   SimpleArray<AsyncState *> async_buf;
   
   SimpleArray<Win32::handle_t> handle_buf;
   SimpleArray<ulen> index_buf;
   
   WaitSem sem;
   
   ulen count;
   bool sem_first;
   
  private:
   
   void rollWait(ulen slot,ulen index);
  
  public:
   
   explicit WaitBase(ulen async_count);
   
   ~WaitBase() {}
   
   AsyncState ** getAsyncs() { return async_buf.getPtr(); }
   
   bool addWait(ulen index);
   
   bool delWait(ulen index);
   
   WaitResult wait(MSec timeout);
   
   void interrupt() { sem.give(); }
   
   WaitResult waitAll(MSec timeout);
 };

template <class AsyncState,class Wait>
WaitBase<AsyncState,Wait>::State::State()
 : slot(0)
 {
  state.olap.h_event=Wait::CreateEvent();
   
  Guard( !state.olap.h_event );
 }

template <class AsyncState,class Wait>
WaitBase<AsyncState,Wait>::State::~State()
 {
  AbortIf( !Wait::DestroyEvent(state.olap.h_event) ,"CCore::Sys::WaitBase<AsyncState,Wait>::State::~State()");
 }

template <class AsyncState,class Wait>
void WaitBase<AsyncState,Wait>::rollWait(ulen slot,ulen index)
 {
  if( slot<count )
    {
     Swap(handle_buf[slot],handle_buf[count]);
     
     ulen i=Replace(index_buf[count],index);
     
     index_buf[slot]=i;
     
     state_buf[i].slot=slot;

     state_buf[index].slot=count;
    }
 }

template <class AsyncState,class Wait>
WaitBase<AsyncState,Wait>::WaitBase(ulen async_count)
 : state_buf(async_count),
   async_buf(async_count),
   handle_buf(async_count+2),
   index_buf(async_count+1),
   count(0),
   sem_first(true)
 {
  for(ulen i=0; i<async_count ;i++) async_buf[i]=state_buf[i].getAsync();
 }

template <class AsyncState,class Wait>
bool WaitBase<AsyncState,Wait>::addWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].slot!=0 ) return false;
  
  ulen slot=++count;
  
  state_buf[index].slot=slot;
  
  handle_buf[slot]=state_buf[index].getHandle();
  index_buf[slot]=index;
  
  return true;
 }

template <class AsyncState,class Wait>
bool WaitBase<AsyncState,Wait>::delWait(ulen index)
 {
  if( index>=state_buf.getLen() || state_buf[index].slot==0 ) return false;
  
  ulen slot=Replace_null(state_buf[index].slot);
  
  if( slot<count )
    {
     handle_buf[slot]=handle_buf[count];
     
     ulen i=index_buf[count];
     
     index_buf[slot]=i;
     
     state_buf[i].slot=slot;
    }
   
  count--;
   
  return true;
 }

template <class AsyncState,class Wait>
WaitResult WaitBase<AsyncState,Wait>::wait(MSec timeout) 
 {
  WaitResult slot;
  
  if( sem_first )
    {
     handle_buf[0]=sem.getHandle();
     
     slot=Wait::WaitSome(handle_buf.getPtr(),count+1,timeout);
     
     if( slot<0 ) return slot;
     
     if( slot==0 ) 
       {
        sem_first=false;
        
        return Wait_interrupt;
       }
    }
  else
    {
     handle_buf[count+1]=sem.getHandle();
     
     slot=Wait::WaitSome(handle_buf.getPtr()+1,count+1,timeout);
     
     if( slot<0 ) return slot;
     
     if( (ulen)slot==count ) return Wait_interrupt;
     
     slot=WaitResult(slot+1);
     
     sem_first=true;
    }
  
  ulen index=index_buf[slot];
  
  rollWait(slot,index);
  
  return WaitResult(index);
 }

template <class AsyncState,class Wait>
WaitResult WaitBase<AsyncState,Wait>::waitAll(MSec timeout) 
 {
  if( count==0 ) return WaitResult(0);
  
  return Wait::WaitAll(handle_buf.getPtr()+1,count,timeout);
 }

} // namespace Sys
} // namespace CCore
 
#endif
 

