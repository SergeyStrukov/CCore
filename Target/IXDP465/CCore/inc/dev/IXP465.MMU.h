/* IXP465.MMU.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_IXP465_MMU_h
#define CCore_inc_dev_IXP465_MMU_h

#include <CCore/inc/dev/IXP465.h>
 
namespace IXP465 {
namespace MMU {

//
// entire memory is divided on 4K sections, length of each is 1M
//
// TT translates VA to PA between these sections
//
//    VA    |  va_index  |                  offset |
//
//    PA    |  pa_index  |                  offset |
//
//               12 bit                     20 bit
//

/* consts */ 

const unsigned TTLen = 0x1000 ;

const unsigned TTAlign = 0x4000 ;

/* Section flags */ 

enum SectionFlags : unsigned
 {
  Section_Cache  = 0x001, // enable cache
  Section_Buff   = 0x002, // enable write buffering
  
  Section_AP_SR  = 0x000, // CP15 SR bits based
  Section_AP_UNO = 0x100, // no user mode access
  Section_AP_URO = 0x200, // RO user mode access
  Section_AP_ALL = 0x300, // RW user mode access
 };
 
/* classes */ 

struct TTEntry;

/* struct TTEntry */ 

struct TTEntry
 {
  unsigned descriptor;
  
  void disable() { descriptor=0; }
  
  void section(unsigned pa_index,unsigned domain,unsigned flags) 
   { 
    descriptor=(pa_index<<20)|(domain<<5)|(flags<<2)|2; 
   }
 };
 
} // namespace MMU
} // namespace IXP465
 
#endif
 

