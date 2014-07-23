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
#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/PrintTime.h>
#include <CCore/inc/Job.h>

namespace CCore {
namespace Math {
namespace APRTest {

/* functions */

QType MulGuarded(QType a,QType b)
 {
  UIntFunc<QType>::Mul mul(a,b);
  
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

ulen SmallPrimesSet::getSetNumber() const
 {
  auto r=Range(flags);
  
  for(ulen i=r.len; i-- ;) if( r[i] ) return i;
  
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
  return UIntModMul(a,b,mod);
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

QType QModEngine::mac(QType s,QType a,QType b) const
 {
  return UIntModMac(s,a,b,mod);
 }

QType QModEngine::add(QType a,QType b) const
 {
  QType c=mod-b;
  
  if( a>=c ) return a-c;
  
  return a+b;
 }

QType QModEngine::sub(QType a,QType b) const
 {
  if( a>=b ) return a-b;
  
  return mod-(b-a);
 }

QType QModEngine::inv(QType a) const
 {
  QType b=mod;
  QType y=0;
  QType x=1;
  
  while( a>1 )
    {
     QType c=b%a;
     QType z=sub(y,mul(x,b/a));
     
     b=a;
     y=x;
     
     a=c;
     x=z;
    }
  
  return x; 
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

/* class Jacobi::LogPow */

class Jacobi::LogPow : QModEngine
 {
   QType d;
  
   struct Rec : NoThrowFlagsBase
    {
     unsigned ind = 0 ;
     QType a = 0 ;
     
     Rec() {}
     
     void set(unsigned ind_,QType a_)
      {
       ind=ind_;
       a=a_; 
      }
     
     bool operator < (const Rec &obj) const { return a<obj.a; }
     
     bool operator >= (QType b) const { return a>=b; }
    };
   
   DynArray<Rec> table;
   
  public:
  
   LogPow(const Jacobi &jac,unsigned p);
   
   ~LogPow() {}
   
   unsigned operator () (QType x) const; // 0 < x < prime
 };

Jacobi::LogPow::LogPow(const Jacobi &jac,unsigned p)
 : QModEngine(jac),
   d((jac.prime-1)/p),
   table(p)
 {
  QType g=pow(jac.gen,d);
  QType a=1;
  
  for(unsigned i=0; i<p ;i++) 
    {
     table[i].set(i,a);
     
     a=mul(a,g);
    }
  
  Sort(Range(table));
 }
   
unsigned Jacobi::LogPow::operator () (QType x) const // 0 < x < prime
 {
  x=pow(x,d);
  
  auto r=Range(table);
  
  Algon::BinarySearch_greater_or_equal(r,x);
  
  if( +r && r->a==x ) return r->ind;
  
  Printf(Exception,"CCore::Math::APRTest::Jacobi::LogPow : internal");
  
  return 0;
 }

/* class Jacobi::AddLogReport */

class Jacobi::AddLogReport : NoCopy
 {
   SecTimer timer;
   
  public:
 
   AddLogReport(QType prime,unsigned p)
    {
     Printf(Con,"Jacobi #; #;\n",prime,p);
    }
   
   ~AddLogReport()
    {
     Printf(Con,"\ntime = #;\n",PrintTime(timer.get()));
    }
   
   void next(QType x,QType y)
    {
     if( (y-x)%1024==0 )  Printf(Con,"#; #;    \r",x,y);
    }
 };

/* class Jacobi::LogCountTable */

void Jacobi::GuardLog()
 {
  Printf(Exception,"CCore::Math::APRTest::Jacobi::GuardLog() : internal");
 }

template <class Func>
void Jacobi::addLog(unsigned p,Func func) const
 {
  AddLogReport report(prime,p);
  
  if( table.getLen() )
    {
#if 1
    
     QType x=2,y=prime-1;
     
     for(; x<y ;x++,y--) 
       {
        report.next(x,y);
        
        unsigned a=log_table(x,p);
        unsigned b=log_table(y,p);
        
        func(a,b);
        func(b,a);
       }
     
     {
      unsigned c=log_table(x,p);
      
      func(c,c);
     }
     
#else
     
     LogPow log(*this,p);
     
     QType x=gen;
     
     for(QType i=1,lim=prime-1; i<lim ;i++)
       {
        unsigned a=unsigned(i%p);
        QType y=prime+1-x;
        
        if( a!=log_table(x,p) ) GuardLog();
       
        if( x<y )
          {
           unsigned b=log(y);
           
           func(a,b);
           func(b,a);
          }
        else if( x==y )
          {
           func(a,a);
          }
         
        x=mul(x,gen);
       }
     
#endif        
    }
  else
    {
     LogPow log(*this,p);
     
     QType x=gen;
     
     for(QType i=1,lim=prime-1; i<lim ;i++)
       {
        report.next(i,lim);
       
        unsigned a=unsigned(i%p);
        QType y=prime+1-x;
       
        if( x<y )
          {
           unsigned b=log(y);
           
           func(a,b);
           func(b,a);
          }
        else if( x==y )
          {
           func(a,a);
          }
         
        x=mul(x,gen);
       }
    }
 }

class Jacobi::LogCountTable : NoCopy
 {
   unsigned p;
   DynArray<QType> table; // [p*p]

  private: 
   
   void add(unsigned a,unsigned b) { table[a*p+b]++; }
   
   QType count(unsigned a,unsigned b) const { return table[a*p+b]; }
   
   static void Normalize(QType result[ /* p */ ],unsigned p);
   
  public:
   
   LogCountTable(const Jacobi &jac,unsigned p);
   
   ~LogCountTable() {}
   
   void operator () (unsigned k,QType result[ /* p */ ]) const; // result is erased
 };
   
void Jacobi::LogCountTable::Normalize(QType result[ /* p */ ],unsigned p)
 {
  QType minval;
  
  // 1
  {
   auto r=Range(result,p);
   
   minval=*r;
   
   for(++r; +r ;++r) Replace_min(minval,*r);
  }
  
  // 2
  {
   for(auto r=Range(result,p); +r ;++r) (*r)-=minval;
  }
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
  
  Normalize(result,p);
 }

/* class Jacobi */

Jacobi::Jacobi(QType prime_,ulen set_number_,QType gen_)
 : QModEngine(prime_),
   prime(prime_),
   set_number(set_number_),
   gen(gen_)
 {
  if( prime_<100000000u && prime_<MaxULen )
    {
     table.extend_default( (ulen)prime_-1 );
     
     QType a=gen_;
    
     for(QType d=1,lim=prime_-1; d<lim ;d++)
       {
        table[ (ulen)a-1 ]=d; // a == gen^d
        
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

/* class AltJacobi::Table */

class AltJacobi::Table : QModEngine
 {
   unsigned p;
   QType m;
 
   DynArray<QType> tableG;
   DynArray<QType> tableC;
   
  private:
 
   QType G(unsigned a) const { return tableG[a]; }
   
   QType C(unsigned a,unsigned b,unsigned p) const { return tableC[a+b*p]; }
   
   QType coeff(unsigned k,unsigned i,unsigned p) const;
 
   static void Normalize(QType result[ /* p */ ],unsigned p);
   
  public:
 
   Table(QType q,QType gen,unsigned p);
   
   ~Table() {}
   
   void operator () (unsigned k,QType result[ /* p */ ]) const; // result is erased
 };

QType AltJacobi::Table::coeff(unsigned k,unsigned i,unsigned p) const
 {
  QType ret=2;
  
  if( i )
    {
     i=p-i;
     
     for(unsigned l=1; l<p ;l++)
       {
        unsigned s=((p-k)*l)%p;
        
        if( s<l ) 
          {
           ret=mac(ret,C(s,l,p),G( (l*i)%p ));
          }
       }
    }
  else
    {
     for(unsigned l=1; l<p ;l++)
       {
        unsigned s=((p-k)*l)%p;
        
        if( s<l ) ret=add(ret,C(s,l,p));
       }
    }
  
  return mul(ret,m);
 }

void AltJacobi::Table::Normalize(QType result[ /* p */ ],unsigned p)
 {
  QType minval;
  
  // 1
  {
   auto r=Range(result,p);
   
   minval=*r;
   
   for(++r; +r ;++r) Replace_min(minval,*r);
  }
  
  // 2
  {
   for(auto r=Range(result,p); +r ;++r) (*r)-=minval;
  }
 }

AltJacobi::Table::Table(QType q,QType gen,unsigned p_)
 : QModEngine(q),
   p(p_),
   m((q-1)/p_),
   tableG(p_),
   tableC(p_*p_)
 {
  // 1
  {
   QType g=pow(gen,m);
   QType cur=1;
   
   for(unsigned i=0; i<p_ ;i++) 
     {
      tableG[i]=cur;
      
      cur=mul(cur,g);
     }
  }

  // 2
  {
   DynArray<QType> A(p_);
   DynArray<QType> B(p_);
   
   {
    QType t=1;
    QType P=1;
     
    unsigned k=0;
    
    for(unsigned lim=(p_-1)/2; k<lim ;k++)
      {
       QType F=1;
       
       for(QType cnt=m; cnt ;cnt--,t++) F=mul(F,t);
       
       A[p_-1-k]=A[k]=F;
       B[p_-1-k]=B[k]=inv(F);
       
       P=mul(P,sq(F));
      }

    P=q-P;
    
    A[k]=inv(P);
    B[k]=P;
   }
   
   for(unsigned b=2; b<p_ ;b++)
     {
      QType C=1;
      
      unsigned a=1;
      
      for(unsigned end=b/2; a<=end ;a++)
        {
         C=mul(C,A[b-a]);
         C=mul(C,B[a-1]);
        
         tableC[a+b*p_]=C;
        }
      
      for(; a<b ;a++)
        {
         tableC[a+b*p_]=tableC[(b-a)+b*p_];
        }
     }
  }
 }

void AltJacobi::Table::operator () (unsigned k,QType result[ /* p */ ]) const
 {
  for(unsigned i=0,p=this->p; i<p ;i++) result[i]=coeff(k,i,p);
  
  Normalize(result,p);
 }

/* class AltJacobi */

AltJacobi::AltJacobi(QType prime_,ulen set_number_,QType gen_)
 : prime(prime_),
   set_number(set_number_),
   gen(gen_)
 {
 }
   
void AltJacobi::operator () (unsigned p,QType result[ /* (p-2)*p */ ]) const
 {
  Printf(Con,"Jacobi #; #;\n",prime,p);
  
  SecTimer timer;
  
  Table table(prime,gen,p);
  
  Printf(Con,"time = #;\n",PrintTime(timer.get()));
  
  for(unsigned k=1; k<p-1 ;k++,result+=p) table(k,result);
 }
   
/* class JacobiSumTable */

JacobiSumTable::JacobiSumTable(const AltJacobi &jac,unsigned prime_p_)
 : prime_q(jac.getPrime()),
   set_number(jac.getSetNumber()),
   prime_p(prime_p_)
 {
  if( prime_p_>2 )
    {
     jac(prime_p_,table.extend_default((prime_p_-2)*prime_p_).ptr);
     
#if 0
     
     Jacobi alt(jac.getPrime(),jac.getSetNumber(),jac.getGen());
     
     DynArray<QType> temp((prime_p_-2)*prime_p_);
     
     alt(prime_p_,temp.getPtr());
     
     if( Range(table).equal(Range(temp)) ) 
       Printf(Con,"Ok\n"); 
     else
       Printf(Exception,"Fail");
     
#endif     
    }
 }
  
/* struct PrimeP */

PrimeP::PrimeP(ulen ind_)
 : ind(ind_),
   prime(SmallPrimes[ind_]),
   jset(DoReserve,100)
 {
 }

bool PrimeP::testSet() const
 {
  if( ind==0 ) return jset.getLen()!=0 && jset[0].getSetNumber()<=0 ;
   
  return jset.getLen()!=0 && jset[0].getSetNumber()<=ind-1 ;
 }

/* class DataGen */

class DataGen::JobControl : public Funchor_nocopy
 {
   AltJacobi jac;
   PtrLen<PrimeP> pset;
   
   DynArray<ulen> list;
   
   Mutex mutex;
   
   PtrLen<const ulen> cur;

  private:
   
   void job()
    {
     for(ulen i;;)
       {
        {
         Mutex::Lock lock(mutex);
         
         if( !cur ) return;
         
         i=*cur;
         
         ++cur;
        }
        
        pset[i].append(jac);   
       }
    }
   
  public:
 
   JobControl(const PrimeQ &q,PtrLen<PrimeP> pset_)
    : jac(q),
      pset(pset_),
      list(DoReserve,pset.len)
    {
     for(ulen ind=0; ind<pset.len ;ind++)
       {
        if( q.hasP(ind) ) list.append_copy(ind);
       }
    
     cur=Range_const(list);
    }
   
   ~JobControl() {}
   
   Function<void (void)> function_job() { return FunctionOf(this,&JobControl::job); }
 };

DataGen::DataGen(ulen n)
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
  
  qset.shrink_extra();
  
  Sort(Range(qset));

  // make pset
  
  for(ulen ind=0; ind<=n ;ind++) pset.append_fill(ind);

  // make Jacobi
  
  {
   for(ulen j=0,len=qset.getLen(); j<len ;j++)
     {
      JobControl ctrl(qset[j],Range(pset));
      
      Job run_job(ctrl.function_job());
     }
  }
 }
   
DataGen::~DataGen()
 {
 }

bool DataGen::testSet() const
 {
  for(const PrimeP &p : pset ) if( !p.testSet() ) return false;
  
  return true;
 }

} // namespace APRTest
} // namespace Math
} // namespace CCore
 

