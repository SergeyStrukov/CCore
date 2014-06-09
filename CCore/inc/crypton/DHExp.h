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

#include <CCore/inc/crypton/Forget.h>

namespace CCore {
namespace Crypton {

/* classes */

struct DHModI;

struct DHModII;

struct DefaultDHAlgo;

template <class DHMod,class Algo=DefaultDHAlgo> class DHExp;

/* struct DHModI */

struct DHModI
 {
  static const ulen GLen = 96 ;
  
  static const uint8 G[GLen];
  
  static const uint8 Mod[GLen];
  
  static const uint8 InvMod[GLen];
  
  static const uint8 Lift[GLen];
 };

/* struct DHModII */

struct DHModII
 {
  static const ulen GLen = 128 ;
  
  static const uint8 G[GLen];
  
  static const uint8 Mod[GLen];
  
  static const uint8 InvMod[GLen];
  
  static const uint8 Lift[GLen];
 };

/* struct Algo */

#if 0

struct Algo
 {
  using Unit = ??? ;
  
  static const unsigned UnitBits = ??? ;
  
  template <ulen Len>
  class MulOp : NoCopy
   {
    public:
    
     MulOp();
     
     ~MulOp();
     
     void mul(const Unit A[Len],const Unit B[Len],Unit C[2*Len]); // no overlapp
     
     void mulHi(const Unit A[Len],const Unit B[Len],Unit C[Len]); // no overlapp
     
     void mulLo(const Unit A[Len],const Unit B[Len],Unit C[Len]); // no overlapp
     
     void sq(const Unit A[Len],Unit B[2*Len]); // no overlapp
   };

  template <ulen Len>
  class AddOp : NoCopy
   {
    public:
   
     AddOp();
     
     ~AddOp();
     
     bool /* borrow */ sub(const Unit A[Len],const Unit B[Len],Unit C[Len]); // no overlapp
     
     bool /* carry */ add(const Unit A[Len],Unit B[Len]); // no overlap
     
     bool /* carry */ neg(Unit A[Len]);
   };
 };

#endif

/* struct DefaultDHAlgo */

struct DefaultDHAlgo
 {
  using Algo = Math::IntegerFastAlgo;
  
  using Unit = Algo::Unit ;
  
  static const unsigned UnitBits = Algo::UnitBits ;
  
  template <ulen Len>
  class MulOp : NoCopy
   {
     Unit temp[2*Len];
     
    public:
    
     MulOp()
      {
      }
     
     ~MulOp()
      {
       Forget(temp);
      }
     
     void mul(const Unit A[Len],const Unit B[Len],Unit C[2*Len])
      {
       Algo::UMul(C,A,Len,B,Len);
      }
     
     void mulHi(const Unit A[Len],const Unit B[Len],Unit C[Len])
      {
       Algo::UMul(temp,A,Len,B,Len);
       
       Range(temp+Len,Len).copyTo(C);
      }
     
     void mulLo(const Unit A[Len],const Unit B[Len],Unit C[Len])
      {
       Algo::UMulLo(C,Len,A,Len,B,Len);
      }
     
     void sq(const Unit A[Len],Unit B[2*Len])
      {
       Algo::USq(B,A,Len);
      }
   };

  template <ulen Len>
  class AddOp : NoCopy
   {
    public:
   
     AddOp()
      {
      }
     
     ~AddOp()
      {
      }
     
     bool /* borrow */ sub(const Unit A[Len],const Unit B[Len],Unit C[Len])
      {
       Range(A,Len).copyTo(C);
       
       return Algo::USub(C,B,Len);
      }
     
     bool /* carry */ add(const Unit A[Len],Unit B[Len])
      {
       return Algo::UAdd(B,A,Len);
      }
     
     bool /* carry */ neg(Unit A[Len])
      {
       return Algo::UNeg(A,Len);
      }
   };
 };

/* class DHExp<DHMod,Algo> */

template <class DHMod,class Algo> 
class DHExp : NoCopy 
 {
  public: 
 
   static const ulen GLen = DHMod::GLen ;

  public:
   
   static const unsigned UnitBits = Algo::UnitBits ;
   
   static_assert( (UnitBits%8)==0 ,"CCore::Crypton::DHExp<...> : UnitBits is not multiple 8");
   
   static const unsigned UnitOctets = UnitBits/8 ;
   
   static_assert( (GLen%UnitOctets)==0 ,"CCore::Crypton::DHExp<...> : GLen is not multiple UnitOctets");
   
   static const ulen IntLen = GLen/UnitOctets ;
   
   using Unit = typename Algo::Unit ;
   
  public:
   
   class Core : NoCopy
    {
      typename Algo::template MulOp<IntLen> mulop;
      typename Algo::template AddOp<IntLen> addop;
      
      Unit M[IntLen];
      Unit K[IntLen];
      Unit L[IntLen];
      
      Unit P[2*IntLen];
      Unit Q[IntLen];
      
     private: 
    
      void reduce(Unit R[IntLen]);
      
     public:
    
      Core();
      
      ~Core();
      
      void direct(const Unit A[IntLen],Unit B[IntLen]); // may overlapp , result fit to module
      
      void inverse(const Unit A[IntLen],Unit B[IntLen]); // may overlapp
      
      void mul(const Unit A[IntLen],const Unit B[IntLen],Unit C[IntLen]); // may overlapp
      
      void sq(const Unit A[IntLen],Unit B[IntLen]); // may overlapp
    };
   
  private: 
   
   Core core;
   
   Unit G[15*IntLen];
   Unit A[15*IntLen];
   Unit P[IntLen];
   
  private: 

   static Unit Load(const uint8 a[UnitOctets]);
   
   static void Save(Unit A,uint8 a[UnitOctets]);
   
   static void Load(const uint8 a[GLen],Unit A[IntLen]);
   
   static void Save(const Unit A[IntLen],uint8 a[GLen]);
   
   static bool IsNull(const Unit A[IntLen]);
   
   static void SetNull(Unit A[IntLen]);
   
   static void SetOne(Unit A[IntLen]);
   
   static bool LSBit(const Unit A[IntLen]) { return A[0]&Unit(1); }
   
  private: 
 
   void load(const uint8 a[GLen]);
   
   void prepare();
   
   void expand();
   
   bool powstep(unsigned bits,bool one);
   
   bool pow(const uint8 x[GLen]);
   
   void complete(bool one);
   
   void save(uint8 ax[GLen]);
   
  public:
 
   DHExp();
   
   ~DHExp();
   
   void pow(const uint8 a[GLen],const uint8 x[GLen],uint8 ax[GLen]);
   
   void pow(const uint8 x[GLen],uint8 gx[GLen]);
 };

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Core::reduce(Unit R[IntLen])
 {
  mulop.mulLo(P,K,Q);
  mulop.mulHi(Q,M,P);
  
  if( addop.sub(P+IntLen,P,R) )
    {
     if( !addop.add(M,R) ) addop.add(M,R);
    }
 }

template <class DHMod,class Algo> 
DHExp<DHMod,Algo>::Core::Core()
 {
  Load(DHMod::Mod,M);
  Load(DHMod::InvMod,K);
  Load(DHMod::Lift,L);
 }

template <class DHMod,class Algo> 
DHExp<DHMod,Algo>::Core::~Core()
 {
  Forget(P);
  Forget(Q);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Core::direct(const Unit A[IntLen],Unit B[IntLen])
 {
  mulop.mulLo(A,K,Q);
  mulop.mulHi(Q,M,P);
  
  if( IsNull(P) )
    {
     SetNull(B);
    }
  else
    {
     if( addop.sub(M,P,B) ) addop.add(M,B);
    }
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Core::inverse(const Unit A[IntLen],Unit B[IntLen])
 {
  mulop.mulHi(A,L,Q);
  
  unsigned bitC=addop.add(A,Q);
  
  mulop.mul(Q,M,P);
  
  unsigned bitA=LSBit(A);
  unsigned bitP=LSBit(P+IntLen);
  
  unsigned bitN=addop.neg(P);
  
  unsigned bit=bitA^bitC^bitP^bitN;
  
  if( bit )
    {
     addop.sub(P,M,B);
    }
  else
    {
     Range(P,IntLen).copyTo(B);
    }
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Core::mul(const Unit A[IntLen],const Unit B[IntLen],Unit C[IntLen])
 {
  mulop.mul(A,B,P);
  
  reduce(C);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Core::sq(const Unit A[IntLen],Unit B[IntLen])
 {
  mulop.sq(A,P);
  
  reduce(B);
 }

template <class DHMod,class Algo> 
auto DHExp<DHMod,Algo>::Load(const uint8 a[UnitOctets]) -> Unit
 {
  Unit A=0;
  
  for(unsigned cnt=UnitOctets,off=0; cnt ;cnt--,a++,off+=8) A|=(Unit(*a)<<off);
  
  return A;
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Save(Unit A,uint8 a[UnitOctets])
 {
  for(unsigned cnt=UnitOctets,off=0; cnt ;cnt--,a++,off+=8) *a=uint8(A>>off);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Load(const uint8 a[GLen],Unit A[IntLen])
 {
  for(ulen cnt=IntLen; cnt ;cnt--,A++,a+=UnitOctets) *A=Load(a);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::Save(const Unit A[IntLen],uint8 a[GLen])
 {
  for(ulen cnt=IntLen; cnt ;cnt--,A++,a+=UnitOctets) Save(*A,a);
 }

template <class DHMod,class Algo> 
bool DHExp<DHMod,Algo>::IsNull(const Unit A[IntLen])
 {
  for(ulen cnt=IntLen; cnt ;cnt--,A++) if( *A ) return false;
  
  return true;
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::SetNull(Unit A[IntLen])
 {
  for(ulen cnt=IntLen; cnt ;cnt--,A++) *A=0;
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::SetOne(Unit A[IntLen])
 {
  *(A++)=1;
  
  for(ulen cnt=IntLen-1; cnt ;cnt--,A++) *A=0;
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::load(const uint8 a[GLen])
 {
  Load(a,A);
 }
   
template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::prepare()
 {
  core.inverse(A,A);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::expand()
 {
  core.sq(A,A+IntLen);
  
  ulen off=IntLen;
  
  for(unsigned cnt=13; cnt ;cnt--,off+=IntLen) core.mul(A,A+off,A+off+IntLen);
 }

template <class DHMod,class Algo> 
bool DHExp<DHMod,Algo>::powstep(unsigned bits,bool one)
 {
  if( one )
    {
     if( bits )
       {
        Range(P).copy(A+(bits-1)*IntLen);
       
        return false;
       }
     else
       {
        return true;
       }
    }
  else
    {
     core.sq(P,P);
     core.sq(P,P);
     core.sq(P,P);
     core.sq(P,P);
     
     if( bits ) core.mul(A+(bits-1)*IntLen,P,P);
     
     return false;
    }
 }

template <class DHMod,class Algo> 
bool DHExp<DHMod,Algo>::pow(const uint8 x[GLen])
 {
  bool one=true;
  
  for(uint8 d : RangeReverse(x,GLen) )
    {
     one=powstep(d>>4,one);
     one=powstep(d&15,one);
    }
  
  return one;
 }
   
template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::complete(bool one)
 {
  if( one )
    {
     SetOne(P);
    }
  else
    {
     core.direct(P,P);
    }
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::save(uint8 ax[GLen])
 {
  Save(P,ax);
 }

template <class DHMod,class Algo> 
DHExp<DHMod,Algo>::DHExp()
 {
  load(DHMod::G);
  
  prepare();
  
  expand();
  
  Range(G).copy(A);
 }

template <class DHMod,class Algo> 
DHExp<DHMod,Algo>::~DHExp()
 {
  Forget(A);
  Forget(P);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::pow(const uint8 a[GLen],const uint8 x[GLen],uint8 ax[GLen])
 {
  load(a);
  
  prepare();
  
  expand();
  
  bool one=pow(x);
  
  complete(one);
  
  save(ax);
 }

template <class DHMod,class Algo> 
void DHExp<DHMod,Algo>::pow(const uint8 x[GLen],uint8 gx[GLen])
 {
  Range(A).copy(G);
  
  bool one=pow(x);
  
  complete(one);
  
  save(gx);
 }

} // namespace Crypton
} // namespace CCore
 
#endif
 

