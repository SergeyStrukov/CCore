/* IntScan.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_scanf_IntScan_h
#define CCore_inc_scanf_IntScan_h
 
#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

struct IntScanOpt;

template <class UInt> class UIntScan;

template <class SInt> class SIntScan;

/* struct IntScanOpt */

struct IntScanOpt
 {
  // TODO
  
  IntScanOpt() {}
  
  IntScanOpt(const char *ptr,const char *lim) { Used(ptr); Used(lim); }
 };

/* class UIntScan<UInt> */

template <class UInt> 
class UIntScan : NoCopy
 {
   UInt &var;
   
  public:
  
   explicit UIntScan(UInt &var_) : var(var_) {}
   
   template <class S>
   void scan(S &inp,IntScanOpt opt)
    {
     // TODO
    }
 };

/* class SIntScan<SInt> */

template <class SInt> 
class SIntScan : NoCopy
 {
   SInt &var;
   
  public:
  
   explicit SIntScan(SInt &var_) : var(var_) {}
   
   template <class S>
   void scan(S &inp,IntScanOpt opt)
    {
     // TODO
    }
 };

} // namespace CCore
 
#endif
 

