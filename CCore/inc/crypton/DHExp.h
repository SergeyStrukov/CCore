/* DHExp.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_DHExp_h
#define CCore_inc_crypton_DHExp_h

#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/inc/SaveLoad.h>

namespace CCore {
namespace Crypton {

/* classes */

struct DHModI;

struct DHModII;

template <class DHMod,class Algo> class DHExp;

/* struct DHModI */

struct DHModI
 {
  static const ulen GLen = 96 ;
  
  static const uint8 G[GLen];
  
  static const uint8 Mod[GLen];
 };

/* struct DHModII */

struct DHModII
 {
  static const ulen GLen = 128 ;
  
  static const uint8 G[GLen];
  
  static const uint8 Mod[GLen];
 };

/* class DHExp<DHMod,Algo> */

template <class DHMod,class Algo> 
class DHExp : NoCopy 
 {
  public: 
 
   static const ulen GLen = DHMod::GLen ;

  private:
   
   static const unsigned UnitBits = Algo::UnitBits ;
   
   static_assert( (UnitBits%8)==0 ,"CCore::Crypton::DHExp<...> : UnitBits is not multiple 8");
   
   static const unsigned UnitOctets = UnitBits/8 ;
   
   static const ulen IntLen = (8*GLen+UnitBits-1)/UnitBits ;
   
   using Unit = typename Algo::Unit ;
   
   Unit A[15*IntLen];
   Unit P[IntLen];
   
  private: 

   static Unit Load(const uint8 a[],ulen len);
   
   static void Save(Unit value,uint8 a[],ulen len);
 
   void load(const uint8 a[]);
   
   void prepare();
   
   void expand();
   
   void mul(const Unit A[],const Unit B[],Unit C[]);
   
   void sq(const Unit A[],Unit C[]);
   
   void pow(const uint8 x[]);
   
   void complete();
   
   void save(uint8 ax[]);
   
  public:
 
   DHExp() 
    {
    }
   
   ~DHExp()
    {
     Range(A).set_null();
     Range(P).set_null();
    }
   
   void pow(const uint8 a[],const uint8 x[],uint8 ax[]);
   
   void pow(const uint8 x[],uint8 gx[]);
 };

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::load(const uint8 a[])
 {
  Unit *out=A;
  auto r=Range(a,GLen); 
  
  for(; r.len>=UnitOctets ;r+=UnitOctets) *(out++)=Load(r.ptr,UnitOctets);
  
  if( r.len ) *out=Load(r.ptr,r.len);
 }
   
template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::prepare()
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::expand()
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::mul(const Unit A[],const Unit B[],Unit C[])
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::sq(const Unit A[],Unit C[])
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::pow(const uint8 x[])
 {
 }
   
template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::complete()
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::save(uint8 ax[])
 {
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::pow(const uint8 a[],const uint8 x[],uint8 ax[])
 {
  load(a);
  
  pow(x);
  
  save(ax);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::pow(const uint8 x[],uint8 gx[])
 {
  load(DHMod::G);
  
  pow(x);
    
  save(gx);
 }

} // namespace Crypton
} // namespace CCore
 
#endif
 

