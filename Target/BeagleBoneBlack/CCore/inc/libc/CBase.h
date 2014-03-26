/* CBase.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_libc_CBase_h
#define CCore_inc_libc_CBase_h
 
namespace LibC_Internal {

/* types */ 

typedef unsigned PtrValue;

        // to represent void *


typedef unsigned Size;

        // size_t : unsigned , unsigned long


typedef          long long Format_sj_t;
typedef unsigned long long Format_uj_t;

        // intmax_t


typedef      int Format_sz_t;
typedef unsigned Format_uz_t;

        // size_t


typedef      int Format_st_t;
typedef unsigned Format_ut_t;

        // ptrdiff_t


/* consts */ 

const Size NumberBufSize = 64 ;

      // sufficient to hold the octal representation of any unsigned long long

      
const Size PtrValueHexSize = 8 ;      

      // number of hex digit to represent PtrValue


/* types */ 

typedef unsigned long long FilePos;

/* consts */ 

const Size FileBufSize = 4*(1<<10) ;

/* functions */ 

void Abort(const char *zstr);

/* char prop functions */

inline bool IsSpace(char ch) // 0 is not a space 
 { 
  return ch==' ' || ch=='\n' || ch=='\r' || ch=='\t' || ch=='\v' || ch=='\f' ; 
 }

/* signed int functions */

template <class SInt,class UInt>
void SetPosInt(SInt *out,UInt value) { *out=(SInt)value; }

template <class SInt,class UInt>
void SetNegInt(SInt *out,UInt value) { *out=(SInt)(UInt)-value; }

} // namespace LibC_Internal
 
#endif
 

