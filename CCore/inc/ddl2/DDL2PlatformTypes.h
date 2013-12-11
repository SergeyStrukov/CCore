/* DDL2PlatformTypes.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.07
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

#ifndef CCore_inc_ddl2_DDL2PlatformTypes_h
#define CCore_inc_ddl2_DDL2PlatformTypes_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {
namespace DDL2 {

/* types */

using sint_type = Meta::Select<( unsigned(-1)<=uint32(-1) ), sint32 , sint64 > ;

using uint_type = Meta::Select<( unsigned(-1)<=uint32(-1) ), uint32 , uint64 > ;

using ulen_type = Meta::Select<( ulen(-1)<=uint32(-1) && unsigned(-1)<=uint32(-1) ), uint32 , uint64 > ;

} // namespace DDL2
} // namespace CCore
 
#endif
 

