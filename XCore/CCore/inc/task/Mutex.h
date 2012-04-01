/* Mutex.h */ 
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

#ifndef CCore_inc_task_Mutex_h
#define CCore_inc_task_Mutex_h

#include <CCore/inc/task/TaskList.h>
 
namespace CCore {

/* classes */ 

class Mutex;

/* class Mutex */ 

class Mutex : NoCopy
 {
   TextLabel name;
   unsigned count;
   TaskList list;
   
  private:
  
   static AutoTextNameType ObjName;
    
   template <class ... TT> 
   static void Log(const char *format,const TT & ... tt);
    
   void init(); 
   
  public: 
  
   Mutex();
   
   explicit Mutex(TextLabel name);
   
   ~Mutex();
   
   TextLabel getName() const { return name; }
   
   void lock();
  
   void unlock();
  
   typedef LockObject<Mutex> Lock;
 };
 
} // namespace CCore
 
#endif
 

