/* StdioReadCon.h */ 
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

#ifndef CCore_inc_StdioReadCon_h
#define CCore_inc_StdioReadCon_h

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/PlanInit.h>
 
namespace CCore {

/* GetPlanInitNode_...() */ 

PlanInitNode * GetPlanInitNode_StdioReadCon();

/* classes */

class StdioReadCon;

/* class StdioReadCon */ 

class StdioReadCon : NoCopy
 {
   ReadCon con;
   AntiSem asem;
  
  public:
   
   StdioReadCon();
   
   ~StdioReadCon();
   
   class Register : NoCopy
    {
      Mutex mutex;
     
      StdioReadCon *host;  
    
     public:
     
      explicit Register(TextLabel name);
     
      ~Register();
     
      bool set(StdioReadCon *host);
      
      void clear();
     
      StdioReadCon * lock();
    };
   
   class Access : NoCopy
    {
      StdioReadCon *host;
      ReadCon *con;
     
     public:
      
      Access();
      
      ~Access();
      
      bool operator + () const { return con; }
      
      bool operator ! () const { return !con; }
      
      ReadCon * operator -> () const { return con; }
    };
 };
 
} // namespace CCore
 
#endif
 

