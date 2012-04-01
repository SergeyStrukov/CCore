/* Flash.h */ 
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

#ifndef CCore_inc_Flash_h
#define CCore_inc_Flash_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace Flash {

/* consts */ 

const ulen Base       = 0x50000000 ;

const ulen Size       = 0x2000000 ;
const ulen BlockSize  =   0x20000 ;
const ulen BlockCount =     0x100 ;

/* functions */ 

inline void * GetBaseAddress() { return (void *)Base; }
 
bool Erase(ulen block_index);

bool Write16(ulen off,uint16 data);

bool Write32(ulen off,uint32 data);

bool Write(ulen off,PtrLen<const uint32> data);
 
void ReadMode();

} // namespace Flash
} // namespace CCore
 
#endif
 

