/* ARMBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ARMGo_inc_ARMBase_h
#define ARMGo_inc_ARMBase_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/base/Quick.h>

namespace ARMCore {

/* using */ 

using namespace CCore;

/* types */ 

typedef uint64 DWord;

typedef uint32 Word;

typedef uint16 Half;

typedef uint8  Byte;

typedef sint64 SDWord;

typedef sint32 SWord;

typedef sint16 SHalf;

typedef sint8  SByte;

/* consts */ 

const Word StopAddress = 0xFFFFFFF0 ;

/* functions */

inline Word BitAt(bool bit,unsigned num) { return Word(bit)<<num; }

inline constexpr Word Bit(unsigned num) { return Word(1)<<num; }

inline constexpr Word Bits() { return 0; }

template <class T,class ... TT>
constexpr Word Bits(T num,TT ... tt) { return Bit(num)|Bits(tt...); }

inline constexpr Word Field(unsigned len) { return (Word(1)<<len)-1; }

inline constexpr Word Field(unsigned len,unsigned off) { return Field(len)<<off; }

/* functions */

inline SWord SHExt(Word a) { return SHalf(a); }

inline SWord SBExt(Word a) { return SByte(a); }

inline DWord MakeDWord(Word hi,Word lo) { return (DWord(hi)<<32)|lo; }
 
template <class UInt,class T1,class T2>
UInt Combine(UInt mask,T1 a,T2 b) { return (mask&UInt(a))|(~mask&UInt(b)); }

inline Word RotR(Word val,unsigned shift) { return (val>>shift)|(val<<(32-shift)); }

inline Word RotRBit(Word val,bool bit) { return (val>>1)|BitAt(bit,31); }

inline bool SOverflow(Word a,Word b,Word c) // c == a+b OR c == a+b+1
 {
  Word sa=a&Bit(31);
  Word sb=b&Bit(31);
  Word sc=c&Bit(31);
  
  return sa==sb && sa!=sc ;
 }

inline Half GetHalf(Word value,Word address) // BE, address  0,2
 {
  switch( address )
    {
     case 0 : return Half(value>>16);
     case 2 : return Half(value    );
    }
  
  return 0;
 }

inline Byte GetByte(Word value,Word address) // BE, address  0,1,2,3
 {
  switch( address )
    {
     case 0 : return Byte(value>>24);
     case 1 : return Byte(value>>16);
     case 2 : return Byte(value>> 8);
     case 3 : return Byte(value    );
    }
  
  return 0;
 }

inline void PutHalf(Word &var,Word address,Half value) // BE, address  0,2 
 {
  switch( address )
    {
     case 0 : var=(var&0x0000FFFF)|(Word(value)<<16); break;
     case 2 : var=(var&0xFFFF0000)|(     value     ); break;
    }
 }

inline void PutByte(Word &var,Word address,Byte value) // BE, address  0,1,2,3
 {
  switch( address )
    {
     case 0 : var=(var&0x00FFFFFF)|(Word(value)<<24); break;
     case 1 : var=(var&0xFF00FFFF)|(Word(value)<<16); break;
     case 2 : var=(var&0xFFFF00FF)|(Word(value)<< 8); break;
     case 3 : var=(var&0xFFFFFF00)|(     value     ); break;
    }
 }

/* classes */ 

//enum MemTag;

struct NegMemTag;

struct MemUnit;

struct ExtWord;

/* enum MemTag */

enum MemTag : uint8
 {
  MemTag_Ok,
  
  MemTag_Void,       // not exist
  MemTag_NoVal,      // not initialized memory
  MemTag_NoW,        // not writable
  MemTag_NoX,        // not executable
  MemTag_NotAligned  // not aligned
 };

const char * GetTextDesc(MemTag tag);

/* struct NegMemTag */

struct NegMemTag
 {
  MemTag tag;
  
  NegMemTag() : tag(MemTag_Void) {}

  NegMemTag(MemTag tag_) : tag(tag_) {}

  MemTag operator ! () const { return tag; }
 };

/* struct MemUnit */ 

struct MemUnit : NegMemTag
 {
  Word value;
  
  MemUnit() : value(0) {}

  MemUnit(Word value_) : NegMemTag(MemTag_Ok),value(value_) {}
  
  MemUnit(MemTag tag) : NegMemTag(tag),value(0) {}
 };
 
/* struct ExtWord */

struct ExtWord
 {
  Word value;
  bool bitC;
  
  ExtWord(NothingType) : value(0),bitC(false) {}
  
  ExtWord(Word value_,bool bitC_) : value(value_),bitC(bitC_) {}
  
  operator Word() const { return value; }
 };

} // namespace ARMCore
 
#endif

