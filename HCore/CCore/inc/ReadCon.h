/* ReadCon.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ReadCon_h
#define CCore_inc_ReadCon_h

#include <CCore/inc/TimeScope.h>
 
#include <CCore/inc/sys/SysCon.h>

namespace CCore {

/* classes */ 

class ReadCon;

/* class ReadCon */ 

class ReadCon : NoCopy
 {
   static const ulen Len = 32 ;
 
   Sys::ConRead con;
 
   char buf[Len];
   char *cur;
   char *lim;
   
  public:

   ReadCon();
   
   ~ReadCon();
   
   // get
   
   char get();
   
   bool get(MSec timeout,char &ret);
   
   bool get(TimeScope time_scope,char &ret)
    {
     auto timeout=time_scope.get();
     
     if( !timeout ) return false;
     
     return get(timeout,ret);
    }
   
   // put
   
   void put(char ch) { put(&ch,1); }
   
   void put(const char *str,ulen len) { put(Range(str,len)); }
   
   void put(StrLen str) { Sys::ConWrite(str); }
 };
 
} // namespace CCore
 
#endif
 

