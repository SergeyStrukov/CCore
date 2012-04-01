/* NegBool.h */ 
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

#ifndef CCore_inc_gadget_NegBool_h
#define CCore_inc_gadget_NegBool_h
 
namespace CCore {

/* classes */ 

class NegBool;

/* class NegBool */ 

class NegBool
 {
   bool nok;

  public:

   NegBool(bool nok_=false) : nok(nok_) {}
 
   bool operator ! () const { return nok; }
 };
 
} // namespace CCore
 
#endif
 
