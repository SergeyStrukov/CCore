/* APRTest.cpp */ 
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
 
#include <CCore/inc/math/APRTest.h>

#include <CCore/inc/Sort.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Math {
namespace APRTest {

/* functions */

void GuardBadData()
 {
  Printf(Exception,"Bad test data");
 }

UType CastGuarded(DType a)
 {
  UType ret=(UType)a;
  
  if( ret!=a )
    {
     Printf(Exception,"CCore::Math::APRTest : too large prime");
    }
  
  return ret;
 }

/* enum TestResult */

const char * GetTextDesc(TestResult res)
 {
  switch( res )
    {
     case IsPrime    : return "Prime";
     case NoPrime    : return "NoPrime";
     case HasDivisor : return "Has divisor";
     case HardCase   : return "Hard case";
     case TooLarge   : return "Too large";
     
     default: return "???"; 
    }
 }

/* class ShortModEngine */

UType ShortModEngine::pow(UType gen,UType d) const
 {
  UType ret=1;
  
  for(BitScanner<UType> scanner(d); +scanner ;++scanner)
    {
     ret=sq(ret);
     
     if( *scanner ) ret=mul(ret,gen);
    }
  
  return ret;
 }
  
/* class GenTest */

GenTest::GenTest(UType prime,const SmallPrimesSet &spset)
 : ShortModEngine(prime) 
 {
  spset.forPrimes_with2( [=] (unsigned p) { dlist.append_copy( (prime-1)/p ); } );
 }

GenTest::~GenTest()
 {
 }

bool GenTest::operator () (UType gen) const
 {
  for(UType d : dlist ) if( pow(gen,d)==1 ) return false;
  
  return true;
 }

/* class Jacobi */
   
Jacobi::Jacobi(UType prime_,UType gen_)
 : ShortModEngine(prime_),
   prime(prime_),
   gen(gen_),
   table(prime_-1) 
 {
  UType a=gen_;
 
  for(UType d=1; d<prime_-1 ;d++)
    {
     table[a-1]=d; // a == gen^d
     
     a=mul(a,gen);
    }

  if( table[0] )
    {
     Printf(Exception,"CCore::Math::APRTest::Jacobi::Jacobi(prime=#;,gen=#;) : gen is not a generator",prime_,gen_);
    }
 }

Jacobi::~Jacobi()
 {
 }
   
void Jacobi::operator () (unsigned p,unsigned k,UType result[]) const
 {
  for(UType x=2,y=prime-1,lim=prime; x<lim ;x++,y--)
    {
     unsigned d=unsigned( (log(x)+k*log(y))%p );
     
     result[d]++;
    }
 }

/* struct PrimeQ */

void PrimeQ::make_gen()
 {
  GenTest test(prime,spset);
  
  for(UType a=2; a<prime ;a++)
    if( test(a) )
      {
       gen=a;
       
       break;
      }
 }

PrimeQ::PrimeQ(const SmallPrimesSet &spset_)
 : spset(spset_),
   prime(2),
   gen(0)
 {
  spset.forPrimes( [=] (unsigned p) { prime=MulGuarded(prime,p); } );

  prime=AddGuarded(prime,1);
 }

PrimeQ::~PrimeQ()
 {
 }

bool PrimeQ::test() const
 {
  for(unsigned d : SmallPrimes )
    {
     if( prime<=d ) return true;
     
     if( prime%d == 0 ) return false;

     if( prime/d < d ) return true;
    }

  Printf(Exception,"CCore::Math::APRTest : too large prime");
  
  return false;
 }

void PrimeQ::complete()
 {
  make_gen();
 }

/* class JacobiSum */

JacobiSum::JacobiSum(const Jacobi &jac,unsigned p,unsigned k)
 : coeff(p)
 {
  jac(p,k,coeff.modify().ptr);
 }

JacobiSum::~JacobiSum()
 {
 }

/* class JacobiSumTable */

JacobiSumTable::JacobiSumTable(const Jacobi &jac,unsigned p)
 : prime(jac.getPrime())
 {
  for(unsigned k=1; k<p-1 ;k++) table.append_fill(jac,p,k);
 }
  
JacobiSumTable::~JacobiSumTable() 
 {
 }

/* struct PrimeP */

PrimeP::PrimeP(PtrLen<const PrimeQ> qset)
 {
  prime=2;

  for(ulen j=0; j<qset.len ;j++) qlist.append_copy(j);
 }

PrimeP::PrimeP(PtrLen<const PrimeQ> qset,ulen i)
 {
  prime=SmallPrimes[i+1];
  
  for(ulen j=0; j<qset.len ;j++) if( qset[j].hasP(i) ) qlist.append_copy(j);
 }

PrimeP::~PrimeP()
 {
 }

/* class DataGenBase */

DataGenBase::DataGenBase(ulen n)
 : number(n)
 {
  // make qset
  
  SmallPrimesSet spset(n);
  
  do
    {
     PrimeQ q(spset);
    
     if( q.test() ) 
       {
        q.complete();
       
        qset.append_copy(q);
       }
    }
  while( spset.next() );
  
  IncrSort(Range(qset), [] (const PrimeQ &a,const PrimeQ &b) { return a.getPrime()<b.getPrime(); } );
  
  // make pset
  
  {
   PrimeP p(Range_const(qset));
    
   if( +p ) pset.append_copy(p);
  }
  
  for(ulen i=0; i<n ;i++)
    {
     PrimeP p(Range_const(qset),i);
     
     if( +p ) pset.append_copy(p);
    }
  
  // make Jacobi
  
  {
   DynArray<DynArray<ulen> > table(qset.getLen());
   
   for(ulen i=0,len=pset.getLen(); i<len ;i++)
     {
      for(ulen j : pset[i].getQList() ) table[j].append_copy(i);
     }
   
   for(ulen j=0,len=qset.getLen(); j<len ;j++)
     {
      Jacobi jac(qset[j]);
     
      for(ulen i : table[j] ) pset[i].update(jac);
     }
  }
 }
   
DataGenBase::~DataGenBase()
 {
 }

} // namespace APRTest
} // namespace Math
} // namespace CCore
 

