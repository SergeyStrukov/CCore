/* DDLTypes.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLTypes_h
#define CCore_inc_ddl_DDLTypes_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace DDL {

/* int types */

typedef sint8  imp_sint8;
typedef uint8  imp_uint8;
typedef sint16 imp_sint16;
typedef uint16 imp_uint16;
typedef sint32 imp_sint32;
typedef uint32 imp_uint32;
typedef sint64 imp_sint64;
typedef uint64 imp_uint64;

typedef Meta::Select<( unsigned(-1)<=uint32(-1) ), sint32 , sint64 > imp_sint;
typedef Meta::Select<( unsigned(-1)<=uint32(-1) ), uint32 , uint64 > imp_uint;

typedef Meta::Select<( ulen(-1)<=uint32(-1) && unsigned(-1)<=uint32(-1) ), uint32 , uint64 > imp_ulen;

typedef imp_sint imp_int;

} // namespace DDL
} // namespace CCore

#endif


