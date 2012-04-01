/* Crc.h */ 
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

#ifndef CCore_inc_Crc_h
#define CCore_inc_Crc_h

#include <CCore/inc/Printf.h>
 
namespace CCore {

/* classes */ 

template <class ResultType,ResultType Mask,ResultType Polynom> class CrcTable;

struct AlgoCrc16;

struct AlgoCrc24;

struct AlgoCrc32;

template <class Algo> class CrcAccumulator;

/* class CrcTable<ResultType,ResultType Mask,ResultType Polynom> */ 

template <class ResultType,ResultType Mask,ResultType Polynom>
class CrcTable : NoCopy
 {
   static_assert( Meta::IsUInt<ResultType>::Ret ,"CCore::CrcTable<ResultType,...> : ResultType must be an unsigned integral type");
  
   static_assert( (Polynom&Mask)==Polynom ,"CCore::CrcTable<,Mask,Polynom> : Polynom must be in Mask");
   
   static_assert( ((Mask+1)&Mask)==0 ,"CCore::CrcTable<,Mask,...> : invalid Mask");
   
  private: 
   
   ResultType bits[8];
   
  private: 
   
   static const ResultType MSBit = Mask^(Mask>>1) ;
   
   static ResultType Mul2(ResultType p)
    {
     if( p&MSBit )
       return ResultType( ((p<<1)&Mask)^Polynom );
     else
       return ResultType( (p<<1)&Mask );
    }
   
  public:
  
   CrcTable()
    {
     ResultType p=Polynom;
     
     bits[0]=p;
     
     for(unsigned i=1; i<8 ;i++)
       {
        p=Mul2(p);
       
        bits[i]=p;
       }
    }
    
   ResultType operator [] (unsigned index) const
    {
     ResultType ret=0;
     
     for(unsigned i=0; i<8 ;i++) if( index&(1u<<i) ) ret^=bits[i];
     
     return ret;
    }
    
   void gen(ResultType table[256]) const
    {
     for(unsigned i=0; i<256 ;i++) table[i]=(*this)[i];
    }
    
   bool check(const ResultType table[256]) const
    {
     for(unsigned i=0; i<256 ;i++) if( table[i]!=(*this)[i] ) return false;
     
     return true;
    }
   
   // print object
    
   template <class P> 
   void print(P &out) const
    {
     ResultType table[256];
     
     gen(table);
     
     Printf(out,"#.8;",PrintDump(Range(table)));
    }
 };
 
/* struct AlgoCrc16 */ 

struct AlgoCrc16
 {
  typedef uint16 ResultType;
  
  typedef uint8 DataType;
  
  static ResultType Add(ResultType crc,DataType data)
   {
    return ResultType( (crc<<8)^data^Table[crc>>8] );
   }
   
  static ResultType Mask(ResultType crc) { return crc; }
   
  static const uint16 Table[256];
 };
 
/* struct AlgoCrc24 */ 

struct AlgoCrc24 
 {
  typedef uint32 ResultType;
  
  typedef uint8 DataType;
  
  static ResultType Add(ResultType crc,DataType data)
   {
    crc<<=8;
    
    return ResultType( crc^data^Table[crc>>24] );
   }
   
  static ResultType Mask(ResultType crc) { return crc&0xFFFFFF; }
   
  static const uint32 Table[256];
 };
 
/* struct AlgoCrc32 */ 

struct AlgoCrc32
 {
  typedef uint32 ResultType;
  
  typedef uint8 DataType;
  
  static ResultType Add(ResultType crc,DataType data)
   {
    return ResultType( (crc<<8)^data^Table[crc>>24] );
   }
   
  static ResultType Mask(ResultType crc) { return crc; }
  
  static const uint32 Table[256];
 };
 
/* class CrcAccumulator<Algo> */ 
 
template <class Algo> 
class CrcAccumulator
 {
  public:
  
   typedef typename Algo::ResultType ResultType;
   
   typedef typename Algo::DataType DataType;
   
  private:
  
   ResultType crc;
   
  public:
  
   explicit CrcAccumulator(ResultType crc_=1) : crc(Algo::Mask(crc_)) {}
   
   operator ResultType() const { return crc; }
   
   void add(DataType data) { crc=Algo::Mask(Algo::Add(crc,data)); }
   
   template <class R>
   void addRange(R r) 
    {
     ResultType temp=crc;
     
     for(; +r ;++r) temp=Algo::Add(temp,DataType(*r));
     
     crc=Algo::Mask(temp);
    }
 };
 
/* types */  

typedef CrcAccumulator<AlgoCrc16> Crc16;
 
typedef CrcAccumulator<AlgoCrc24> Crc24;

typedef CrcAccumulator<AlgoCrc32> Crc32;

} // namespace CCore
 
#endif
 

