/* StaticInit.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_rawin_StaticInit_h
#define CCore_inc_rawin_StaticInit_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Rawin {

/* functions */ 

void TouchPtr(void *ptr);

void StaticInitAbort();

template <class T>
void Touch(T &obj) { TouchPtr(&obj); }
 
/* classes */ 

struct InitBeforeMain;

template <class POD> struct StaticInit;

/* struct InitBeforeMain */ 

struct InitBeforeMain
 {
  template <class T>
  explicit InitBeforeMain(T &obj) { obj.init(); }
 };
 
/* struct StaticInit<POD> */ 

template <class POD> 
struct StaticInit
 {
  static_assert( std::is_pod<POD>::value ,"CCore::Rawin::StaticInit<POD> : POD must be POD");
  
  POD pod;
  int state;
  
  enum State
   {
    InitRequired = 0,
    InitInProgress,
    InitDone
   };
   
  POD & init()
   {
    if( state==InitInProgress ) 
      {
       Touch(ObjInit);
       
       StaticInitAbort();
      }
    
    if( state==InitRequired )
      {
       state=InitInProgress;
       
       pod.init();
       
       state=InitDone;
      }
   
    return pod;
   }
  
  static StaticInit<POD> Obj;
  
  static InitBeforeMain ObjInit;
 };
 
template <class POD> 
StaticInit<POD> StaticInit<POD>::Obj;
  
template <class POD> 
InitBeforeMain StaticInit<POD>::ObjInit(Obj);

/* StaticInitObj() */ 

template <class POD>
POD & StaticInitObj() { return StaticInit<POD>::Obj.init(); }
 
} // namespace Rawin
} // namespace CCore
 
#endif
 

