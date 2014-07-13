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

#include <CCore/inc/math/IntegerSlowAlgo.h>
#include <CCore/inc/math/IntegerFastAlgo.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Math {
namespace APRTest {

/* functions */

using Algo = Meta::Select<( QType(-1)==IntegerFastAlgo::Unit(-1) ),IntegerFastAlgo,IntegerSlowAlgo<QType> > ;

QType MulGuarded(QType a,QType b)
 {
  Algo::DoubleMul mul(a,b);
  
  if( mul.hi )
    {
     Printf(Exception,"CCore::Math::APRTest::MulGuarded(...) : overflow");
    }
  
  return mul.lo;
 }

QType AddGuarded(QType a,QType b)
 {
  UIntFunc<QType>::Add add(a,b);
  
  if( add.carry )
    {
     Printf(Exception,"CCore::Math::APRTest::AddGuarded(...) : overflow");
    }
  
  return add.result;
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

/* class SmallPrimesSet */

unsigned SmallPrimesSet::getSetNumber() const
 {
  auto r=Range(flags);
  
  for(ulen i=r.len; i-- ;) if( r[i] ) return unsigned(i);
  
  return 0;
 }

bool SmallPrimesSet::next()
 {
  PtrLen<bool> r=flags.modify();
  
  for(; +r ;++r)
    {
     if( *r )
       {
        *r=false;
       }
     else
       {
        *r=true;
        
        return true;
       }
    }
  
  return false;
 }

QType SmallPrimesSet::getPrimeQ() const
 {
  QType ret=2;
  
  forOddPrimes( [&ret] (unsigned p) { ret=MulGuarded(ret,p); } );

  ret=AddGuarded(ret,1);
  
  return ret;
 }

/* class QModEngine */

QType QModEngine::mul(QType a,QType b) const
 {
  Algo::DoubleMul mul(a,b);
  
  mul.hi%=mod;
  
  QType div=Algo::DoubleUDiv(mul.hi,mul.lo,mod);
  
  return mul.lo-QType(div*mod);
 }
   
QType QModEngine::pow(QType a,QType d) const
 {
  for(BitScanner<QType> scanner(d); +scanner ;++scanner)
    {
     if( *scanner )
       {
        QType ret=a;
        
        for(++scanner; +scanner ;++scanner)
          {
           ret=sq(ret);
           
           if( *scanner ) ret=mul(ret,a);
          }
        
        return ret;
       }
    }
  
  return 1u;
 }

/* struct PrimeQ */

PrimeQ::PrimeQ(const SmallPrimesSet &spset_)
 : spset(spset_),
   prime(spset_.getPrimeQ()),
   set_number(spset_.getSetNumber()),
   gen(0)
 {
 }

bool PrimeQ::test()
 {
  QModEngine engine(prime);
  
  QType d=prime>>1;
  
  DynArray<QType> elist(DoReserve,set_number+1);
  
  spset.forOddPrimes( [&elist,this] (unsigned p) { elist.append_copy( (prime-1)/p ); } );
  
  for(QType a=2; a<prime ;a++)
    {
     // 1
     {
      QType x=engine.pow(a,d);
      
      if( x==1 ) continue; 
       
      if( x!=prime-1 ) return false;
     }
     
     // 2
     {
      bool flag=true;
      
      for(QType e : elist )
        {
         if( engine.pow(a,e)==1 )
           {
            flag=false;
            
            break;
           }
        }
      
      if( flag ) 
        {
         gen=a;
         
         return true;
        }
     }
    }
  
  return false;
 }

/* class Jacobi */

void Jacobi::GuardLog()
 {
  Printf(Exception,"CCore::Math::APRTest::Jacobi::GuardLog() : internal");
 }

Jacobi::LogPow::LogPow(const Jacobi &jac,unsigned p)
 : engine(jac),
   d((jac.prime-1)/p),
   table(p)
 {
  QType g=engine.pow(jac.gen,d);
  QType a=1;
  
  for(unsigned i=0; i<p ;i++) 
    {
     table[i].set(i,a);
     
     a=engine.mul(a,g);
    }
  
  Sort(Range(table));
 }
   
unsigned Jacobi::LogPow::operator () (QType x) const // 0 < x < prime
 {
  x=engine.pow(x,d);
  
  auto r=Range(table);
  
  Algon::BinarySearch_greater_or_equal(r,x);
  
  if( +r && r->a==x ) return r->ind;
  
  Printf(Exception,"CCore::Math::APRTest::Jacobi::LogPow : internal");
  
  return 0;
 }

Jacobi::LogCountTable::LogCountTable(const Jacobi &jac,unsigned p_)
 : p(p_),
   table(p_*p_)
 {
  jac.addLog(p_, [=] (unsigned a,unsigned b) { add(a,b); } );
 }

void Jacobi::LogCountTable::operator () (unsigned k,QType result[ /* p */ ]) const
 {
  unsigned p=this->p;
  
  for(unsigned a=0; a<p ;a++)
    for(unsigned b=0; b<p ;b++)
      result[ (a+k*b)%p ] += count(a,b) ;
 }

Jacobi::Jacobi(QType prime_,unsigned set_number_,QType gen_)
 : QModEngine(prime_),
   prime(prime_),
   set_number(set_number_),
   gen(gen_)
 {
  if( prime_<100000000u && prime_<MaxULen )
    {
     table.extend_default( (ulen)prime_-1 );
     
     QType a=gen_;
    
     for(QType d=1; d<prime_-1 ;d++)
       {
        table[a-1]=d; // a == gen^d
        
        a=mul(a,gen_);
       }

     if( table[0] )
       {
        Printf(Exception,"CCore::Math::APRTest::Jacobi::Jacobi(prime=#;,...,gen=#;) : gen is not a generator",prime_,gen_);
       }
    }
 }

void Jacobi::operator () (unsigned p,QType result[]) const
 {
  LogCountTable table(*this,p);
  
  for(unsigned k=1; k<p-1 ;k++,result+=p) table(k,result);
 }

/* class JacobiSumTable */

JacobiSumTable::JacobiSumTable(const Jacobi &jac,unsigned prime_p_)
 : prime_q(jac.getPrime()),
   set_number(jac.getSetNumber()),
   prime_p(prime_p_)
 {
  if( prime_p_>2 )
    {
     jac(prime_p_,table.extend_default((prime_p_-2)*prime_p_).ptr);
    }
 }
  
/* struct PrimeP */

PrimeP::PrimeP(PtrLen<const PrimeQ> qset)
 : qlist(DoReserve,qset.len)
 {
  prime=2;

  for(ulen j=0; j<qset.len ;j++) qlist.append_copy(j);
  
  qlist.shrink_extra();
 }

PrimeP::PrimeP(PtrLen<const PrimeQ> qset,unsigned ind)
 : qlist(DoReserve,qset.len)
 {
  prime=SmallPrimes[ind+1];
  
  for(ulen j=0; j<qset.len ;j++) if( qset[j].hasP(ind) ) qlist.append_copy(j);
  
  qlist.shrink_extra();
 }

/* class DataGen */

DataGen::DataGen(unsigned n)
 : qset(DoReserve,1000)
 {
  // make qset
  
  SmallPrimesSet spset(n);
  
  do
    {
     PrimeQ q(spset);
    
     if( q.test() ) qset.append_copy(q); 
    }
  while( spset.next() );
  
  Sort(Range(qset));

  // make pset
  
  pset.append_fill(Range_const(qset));
  
  for(unsigned ind=0; ind<n ;ind++) pset.append_fill(Range_const(qset),ind);

  // make Jacobi
  
  {
   DynArray<DynArray<ulen> > table(qset.getLen());
   
   for(ulen i=0,len=pset.getLen(); i<len ;i++)
     {
      pset[i].forQInd( [&table,i] (ulen j) { table[j].append_copy(i); } );
     }
   
   for(ulen j=0,len=qset.getLen(); j<len ;j++)
     {
      Jacobi jac(qset[j]);
     
      for(ulen i : table[j] ) pset[i].update(jac);
     }
  }
 }
   
DataGen::~DataGen()
 {
 }

} // namespace APRTest
} // namespace Math
} // namespace CCore
 

