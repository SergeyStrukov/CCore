/* Elf.cpp */ 
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
 
#include <CCore/inc/Elf.h>
 
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Elf {

/* functions */   

void GuardTakeFailed(uint32 off,ulen len,ulen lim)
 {
  Printf(Exception,"CCore::Elf::GuardTake(off=#;,len=#;,lim=#;) : out of range",off,len,lim);
 }
 
static void GuardScanNullFailed(uint32 off)
 {
  Printf(Exception,"CCore::Elf::ScanNull(,off=#;,...) : no terminating null",off);  
 }
 
ulen ScanNull(const uint8 *base,uint32 off,ulen lim)
 {
  if( off>=lim ) GuardScanNullFailed(off);
    
  base+=off;
  lim-=off;
  
  ulen len=lim;
  
  for(; *base ;base++,lim--) if( lim<=1 ) GuardScanNullFailed(off);
  
  return len-lim;
 }
 
void GuardLimFailed(const char *name,uint32 val)
 {
  Printf(Exception,"CCore::Elf::GuardLim(#;,#;) : value is out of range",name,val);
 }
 
} // namespace Elf
} // namespace CCore
 

