/* testArray.h */
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

#ifndef CCore_test_testArray_h
#define CCore_test_testArray_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* using */

using namespace CCore;

namespace Private_testArray {

/* struct X */

struct X
 {
  int val;
  
  X() 
   : val(NextVal++) 
   { 
    Printf(Con,"X::X(#;)\n",val); 
    
    if( val>10 ) Printf(Exception,"XTrap"); 
   }
  
  ~X() 
   { 
    Printf(Con,"X::~X(#;)\n",val); 
   }
  
  typedef int PrintProxyType;
  
  operator int() const { return val; }
  
  struct Flags
   {
    enum NoThrowFlagType
     {
      Default_no_throw = false,
      Copy_no_throw = true
     };
   };
  
  static int NextVal;
 };
 
/* functions */

template <class T>
void show(const T &a)
 {
  Printf(Con,"#; maxlen = #;\n",PrintSet(Range(a)),a.getMaxLen());
 }
 
} // namespace Private_testArray

using namespace Private_testArray; 

} // namespace App

#endif


