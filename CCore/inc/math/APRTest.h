/* APRTest.h */ 
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

#ifndef CCore_inc_math_APRTest_h
#define CCore_inc_math_APRTest_h

#include <CCore/inc/math/ModEngine.h>
#include <CCore/inc/math/SmallPrimes.h>

#include <CCore/inc/Cmp.h>
#include <CCore/inc/FunctorType.h>
#include <CCore/inc/PrintSet.h>

namespace CCore {
namespace Math {
namespace APRTest {

#if 0

/* types */

using UType = uint32 ;
using DType = uint64 ;

/* functions */

void GuardBadData();

UType CastGuarded(DType a);

inline UType MulGuarded(UType a,UType b) { return CastGuarded( DType(a)*b ); }

inline UType AddGuarded(UType a,UType b) { return CastGuarded( DType(a)+b ); }

/* classes */

//enum TestResult;

class SmallPrimesSet;

class ShortModEngine;

class GenTest;

class PrimeQ;

class Jacobi;

class JacobiSum;

class JacobiSumTable;

class PrimeP;

class DataGenBase;

template <class Integer> class DataGen;

struct TestSet;

class TestData;

template <class Integer> class TestEngine;

/* enum TestResult */

enum TestResult
 {
  IsPrime = 0,
  
  NoPrime,
  HasDivisor,
  HardCase,
  TooLarge
 };

const char * GetTextDesc(TestResult res);

/* class SmallPrimesSet */

class SmallPrimesSet // odd subsequent SmallPrimes 3, 5, 7, ... 
 {
   RefArray<bool> flags;
   
  public:
   
   explicit SmallPrimesSet(ulen n) : flags(n) {}

   ~SmallPrimesSet() {}
   
   bool operator [] (ulen ind) const { return flags[ind]; }
   
   bool next()
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
 
   template <class FuncInit>
   void forPrimes(FuncInit func_init) const
    {
     FunctorTypeOf<FuncInit> func(func_init);
     
     for(ulen i=0,len=flags.getLen(); i<len ;i++) if( flags[i] ) func( SmallPrimes[i+1] );
    }
   
   template <class FuncInit>
   void forPrimes_with2(FuncInit func_init) const
    {
     FunctorTypeOf<FuncInit> func(func_init);
     
     func(2);
     
     for(ulen i=0,len=flags.getLen(); i<len ;i++) if( flags[i] ) func( SmallPrimes[i+1] );
    }
 };

/* class ShortModEngine */

class ShortModEngine : NoCopy
 {
   UType prime;
   
  public:
   
   explicit ShortModEngine(UType prime_) : prime(prime_) {}
   
   UType mul(UType a,UType b) const { return UType( (DType(a)*b)%prime ); }
   
   UType sq(UType a) const { return mul(a,a); }
   
   UType pow(UType gen,UType d) const;
 };

/* class GenTest */

class GenTest : ShortModEngine
 {
   DynArray<UType> dlist;
  
  public:
  
   GenTest(UType prime,const SmallPrimesSet &spset);
  
   ~GenTest();
   
   bool operator () (UType gen) const;
 };

/* class PrimeQ */

class PrimeQ : public NoThrowFlagsBase 
 {
   SmallPrimesSet spset;

   UType prime; // 1+2*(all p from spset)
   UType gen;
  
  private:
   
   void make_gen();
  
  public:
  
   explicit PrimeQ(const SmallPrimesSet &spset);

   ~PrimeQ();
   
   // props
  
   bool hasP(ulen i) const { return spset[i]; }
   
   UType getPrime() const { return prime; }
   
   UType getGen() const { return gen; }
  
   // methods
   
   bool test() const;
  
   void complete();
  
   // print object
  
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;u /* gen = #; */",prime,gen);
    }
 };

/* class Jacobi */

class Jacobi : ShortModEngine
 {
   UType prime;
   UType gen;
   
   DynArray<UType> table;

  private:
   
   DType log(UType x) const { return table[x-1]; } // 0 < x < prime
   
  public:
   
   Jacobi(UType prime,UType gen);
   
   Jacobi(const PrimeQ &q) : Jacobi(q.getPrime(),q.getGen()) {}
   
   ~Jacobi();
   
   UType getPrime() const { return prime; }
   
   void operator () (unsigned p,unsigned k,UType result[ /* p */ ]) const;
 };

/* class JacobiSum */

class JacobiSum : public NoThrowFlagsBase
 {
   RefArray<UType> coeff;
  
  public:
  
   JacobiSum(const Jacobi &jac,unsigned p,unsigned k);
   
   ~JacobiSum();
   
   // print object
   
   template <class P>
   void printJSum(P &out,ulen number,unsigned prime,ulen k,ulen l) const
    {
     Printf(out,"static const UType JSum_#;_#;_#;_#;[]=\n {",number,prime,k,l);
     
     {
      auto r=Range(coeff);
      
      if( +r )
        {
         Printf(out,"\n  #;u",*r);
        
         for(++r; +r ;++r) Printf(out,",\n  #;u",*r);
        }
     }
     
     Printf(out,"\n };\n\n");
    }
 };

/* class JacobiSumTable */

class JacobiSumTable : public NoThrowFlagsBase
 {
   UType prime;
   
   RefArray<JacobiSum> table;
   
  public:
  
   JacobiSumTable(const Jacobi &jac,unsigned p);
  
   ~JacobiSumTable();
   
   // print object
   
   template <class P>
   void printJTable(P &out,ulen number,unsigned prime,ulen k) const
    {
     if( table.getLen()==0 ) return;
     
     {
      auto r=Range(table);
      ulen l=1;
      
      for(; +r ;++r) r->printJSum(out,number,prime,k,l++);
     }
     
     Printf(out,"static const PtrLen<const UType> JTable_#;_#;_#;[]=\n {",number,prime,k);
     
     {
      ulen count=table.getLen(); 
      
      if( count )
        {
         ulen l=1;
         
         Printf(out,"\n  Range(JSum_#;_#;_#;_#;)",number,prime,k,l++);
         
         for(count--; count ;count--) Printf(out,",\n  Range(JSum_#;_#;_#;_#;)",number,prime,k,l++);
        }
     }
     
     Printf(out,"\n };\n\n");
    }
   
   template <class P>
   void printItem(P &out,ulen number,unsigned prime,ulen k) const
    {
     if( table.getLen()==0 )
       {
        Printf(out,"{ #;u , Empty }",this->prime);
       }
     else
       {
        Printf(out,"{ #;u , Range(JTable_#;_#;_#;) }",this->prime,number,prime,k);
       }
    }
 };

/* class PrimeP */

class PrimeP : public NoThrowFlagsBase
 {
   RefArray<ulen> qlist;
  
   unsigned prime;
   
   RefArray<JacobiSumTable> jset;

  public:
  
   explicit PrimeP(PtrLen<const PrimeQ> qset);
  
   PrimeP(PtrLen<const PrimeQ> qset,ulen i);
  
   ~PrimeP();
   
   // props
   
   bool operator + () const { return qlist.getLen(); }
   
   bool operator ! () const { return !qlist.getLen(); }
  
   unsigned getPrime() const { return prime; }
   
   PtrLen<const ulen> getQList() const { return Range(qlist); }
   
   // methods
   
   void update(const Jacobi &jac) { jset.append_fill(jac,prime); }
   
   // print object
  
   template <class P>
   void printJSet(P &out,ulen number) const
    {
     {
      auto r=Range(jset);
      ulen k=1;
      
      for(; +r ;++r) r->printJTable(out,number,prime,k++);
     }
     
     Printf(out,"static const TestSet::JTable JSet_#;_#;[]=\n {",number,prime);
     
     {
      auto r=Range(jset);
      
      if( +r )
        {
         ulen k=1;
         
         Printf(out,"\n  ");
         
         r->printItem(out,number,prime,k++);
         
         for(++r; +r ;++r) 
           {
            Printf(out,",\n  ");
            
            r->printItem(out,number,prime,k++);
           }
        }
     }
     
     Printf(out,"\n };\n\n");
    }
   
   template <class P>
   void printItem(P &out,ulen number) const
    {
     Printf(out,"{ #;u , Range(JSet_#;_#;) }",prime,number,prime);
    }
 };

/* class DataGenBase */

class DataGenBase : NoCopy
 {
  protected:
  
   ulen number;  
  
   DynArray<PrimeP> pset;
   DynArray<PrimeQ> qset; // odd
   
  public: 
   
   explicit DataGenBase(ulen n);
   
   ~DataGenBase();
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"/* Data #; */\n\n",number);

     // jset
     {
      auto r=Range(pset);
       
      for(; +r ;++r) r->printJSet(out,number);
     }
     
     // pset
     {
      Printf(out,"static const TestSet PSet#;[]=\n {",number);
      
      auto r=Range(pset);
      
      if( +r )
        {
         Printf(out,"\n  ");
        
         r->printItem(out,number);
        
         for(++r; +r ;++r) 
           {
            Printf(out,",\n  ");
            
            r->printItem(out,number);
           }
        }
      
      Printf(out,"\n };\n\n");
     }
     
     // qset
     {
      Printf(out,"static const UType QSet#;[]=\n {",number);
      
      auto r=Range(qset);
      
      if( +r )
        {
         Printf(out,"\n  #;",*r);
        
         for(++r; +r ;++r) Printf(out,",\n  #;",*r);
        }
      
      Printf(out,"\n };\n\n");
     }
    }
 };

/* class DataGen<Integer> */

template <class Integer> 
class DataGen : DataGenBase 
 {
   Integer P;
   Integer Q;
   
  public: 
  
   explicit DataGen(ulen n)
    : DataGenBase(n),
      P(1),
      Q(2)
    {
     for(const PrimeP &p : pset ) P*=p.getPrime();
     
     for(const PrimeQ &q : qset ) Q*=q.getPrime();
    }
   
   ~DataGen()
    {
    }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     DataGenBase::print(out);
     
     Printf(out,"static const uint8 P#;[]=#;;\n\n",number,PrintIntegerOctets(this->P));
     
     Printf(out,"static const uint8 Q#;[]=#;;\n\n",number,PrintIntegerOctets(Q));
    }
 };

/* PrepareData() */

template <class Integer,class P,class Func>
void PrepareData(P &out,ulen MaxN,Func func)
 {
  Putobj(out,"/* APRTestData.gen.cpp */\n\n");
  
  Putobj(out,"#include <CCore/inc/math/APRTest.h>\n\n");
  
  Putobj(out,"#include <CCore/inc/Exception.h>\n\n");
  
  Putobj(out,"namespace CCore {\n");
  Putobj(out,"namespace Math {\n");
  Putobj(out,"namespace APRTest {\n\n");
  
  for(ulen n=1; n<=MaxN ;n++)
    {
     func(n);
    
     DataGen<Integer> data(n);

     Putobj(out,data);
    }
  
  Putobj(out,"/* class TestData */\n\n");
  
  Putobj(out,"TestData::TestData(ulen n)\n {\n");
  
  Putobj(out,"  switch( n )\n");
  Putobj(out,"    {\n");
  
  for(ulen n=1; n<=MaxN ;n++)
    {
     Printf(out,"     case #; : pset=Range(PSet#;); qset=Range(QSet#;); octP=Range(P#;); octQ=Range(Q#;); break;\n",n,n,n,n,n);
    }
  
  Putobj(out,"\n     default:\n");
  Putobj(out,"      {\n");
  Putobj(out,"       Printf(Exception,\"CCore::Math::APRTest::TestData::TestData(#;) : bad data index\",n);\n");
  Putobj(out,"      }\n");
  
  Putobj(out,"    }\n");
  
  Putobj(out," }\n\n");
  
  Putobj(out,"} // namespace APRTest\n");
  Putobj(out,"} // namespace Math\n");
  Putobj(out,"} // namespace CCore\n\n");
 }

/* struct TestSet */

struct TestSet
 {
  unsigned prime;
  
  struct JTable
   {
    UType prime_q;
    
    const PtrLen<const PtrLen<const UType> > table; // prime-2
   };
  
  PtrLen<const JTable> jset;
 };

/* class TestData */

class TestData : NoCopy
 {
  protected:
  
   PtrLen<const TestSet> pset;
   PtrLen<const UType> qset;
   
   PtrLen<const uint8> octP; 
   PtrLen<const uint8> octQ; 
  
  public:

   static const ulen MaxN = 8 ;
   
   explicit TestData(ulen n);
 };

/* class TestEngine<Integer> */

template <class Integer> 
class TestEngine : TestData
 {
   Integer P;
   Integer Q;
   
  private:
   
   using Ring = RefArray<Integer> ;
   
   class Engine : NoCopy
    {
      ModEngine<Integer> engine;
      
      Integer N1;
      
     private:
      
      class BitScanner : NoCopy
       {
         using Unit = typename Integer::Unit ;
       
         Integer d;
         
         PtrLenReverse<const Unit> body;
         Unit mask;
         
        public:
       
         explicit BitScanner(const Integer &d_)
          : d(d_) 
          {
           body=RangeReverse(d.getBody());
           
           if( +body )
             mask=UIntFunc<Unit>::MSBit;
           else
             mask=0;
          }
         
         ~BitScanner() {}
         
         Unit operator + () const { return mask; }
         
         Unit operator * () const { return (*body)&mask; }
         
         void operator ++ ()
          {
           mask>>=1;
           
           if( !mask ) 
             {
              ++body;
              
              if( +body ) mask=UIntFunc<Unit>::MSBit;
             }
          }
       };
      
      Ring prepare(PtrLen<const UType> jsum) const
       {
        Ring ret=Ring(jsum.len);

        auto r=ret.modify();
        
        for(; +r ;++r,++jsum) *r=engine.prepare(*jsum); 
        
        return ret;
       }
      
      Ring mul(Ring a,Ring b) const
       {
        auto ra=Range(a);
        auto rb=Range(b);
        
        ulen len=ra.len;
        
        if( rb.len!=len ) GuardBadData();
        
        Ring ret(len);
        
        auto res=ret.modify();
        
        for(ulen i=0; i<len ;i++)
          for(ulen j=0; j<len ;j++)
            {
             ulen k=i+j;
             
             if( k>=len ) k-=len;
             
             res[k]=engine.mac(res[k],ra[i],rb[j]);
            }
        
        return ret;
       }
      
      Ring mul(Ring a,UType b) const
       {
        auto r=a.modify();
        auto b_=engine.prepare(b);
        
        for(; +r ;++r) *r=engine.mul(*r,b_);
        
        return a;
       }

      Ring one(ulen len) const
       {
        Ring ret=Ring(len);
        
        ret.modify()[0]=1;
        
        return ret;
       }
      
      Ring pow(Ring a,Integer d) const
       {
        for(BitScanner scanner(d); +scanner ;++scanner)
          if( *scanner ) 
            {
             Ring ret=a;
             
             for(++scanner; +scanner ;++scanner)
               {
                ret=mul(ret,ret);
                
                if( *scanner ) ret=mul(ret,a);
               }
             
             return ret;
            }

        return one(a.getLen());
       }
      
      Integer pow(Integer a,Integer d) const
       {
        for(BitScanner scanner(d); +scanner ;++scanner)
          if( *scanner ) 
            {
             Integer ret=a;
             
             for(++scanner; +scanner ;++scanner)
               {
                ret=engine.sq(ret);
                
                if( *scanner ) ret=engine.mul(ret,a);
               }
             
             return ret;
            }

        return 1;
       }
      
      int test(Integer a,Integer b) const // 0, 1, 2 : a-b mod N
       {
        switch( Cmp(a,b) )
          {
           case CmpLess :
            {
             if( !a && b==N1 ) return 1;
             
             return 2;
            }
           break;
         
           case CmpGreater :
            {
             if( (a-b).cmp(1)==0 ) return 1;
             
             return 2;
            }
           break;
         
           default: return 0;
          }
       }
      
      TestResult test(Ring cappa) const
       {
        auto r=Range(cappa);
        
        if( r.len<2 ) GuardBadData();
        
        Integer a=r[0];
        Integer b=r[1];
   
        if( test(a,b)==1 )
          {
           for(r+=2; +r ;++r) if( *r!=b ) return NoPrime;
           
           return HardCase;
          }
        else
          {
           bool flag=true;
           
           for(++r; +r ;++r)
             {
              if( flag )
                {
                 switch( test(*r,a) )
                   {
                    case 0 : break;
                     
                    case 1 : flag=false; break;
                     
                    case 2 : return NoPrime;
                   }
                }
              else
                {
                 if( *r!=a ) return NoPrime;
                }
             }
           
           return flag?NoPrime:IsPrime;
          }
       }
      
      TestResult test(Integer cappa,int sign) const
       {
        if( cappa.cmp(sign) ) return HardCase;
         
        if( cappa.cmp(-sign) ) return IsPrime;
        
        return NoPrime;
       }
      
     public:
      
      explicit Engine(Integer N) : engine(N),N1(N-1) {}
      
      ~Engine() {}
      
      TestResult test(unsigned prime,const TestSet::JTable &jtable) const
       {
        if( jtable.table.len!=prime-2 ) GuardBadData();
        
        if( prime>2 )
          {
           DynArray<Ring> theta(prime-2);
           
           theta[0]=prepare(jtable.table[0]);
           
           for(ulen k=1; k<prime-2 ;k++) theta[k]=mul(theta[k-1],prepare(jtable.table[k]));
           
           Ring omega=mul(theta[prime-3],jtable.prime_q);
           
           auto res=engine.getModule().divmod(prime);
           
           unsigned mod=res.mod.template cast<unsigned>();
           
           if( mod==0 ) GuardBadData();
           
           Ring cappa=pow(omega,res.div);
           
           if( mod>1 ) cappa=mul(cappa,theta[mod-2]);
           
           return test(cappa);
          }
        else
          {
           Integer omega=engine.prepare(jtable.prime_q);
           Integer d=engine.getModule()/2u;
           
           Integer cappa=pow(omega,d);
           
           if( d.isEven() )
             {
              return test(cappa,1);
             }
           else
             {
              return test(cappa,-1);
             }
          }
       }
    };
   
  private:
   
   template <class Func>
   TestResult sanity(Integer N,Func &func) const
    {
     if( N.cmp(1)<=0 ) 
       {
        func("N <= 1\nNoPrime\n");
       
        return NoPrime;
       }
     
     if( N>=Q.sq() ) 
       {
        func("N >= Q*Q\nTooLarge\n");       
       
        return TooLarge;
       }
     
     Integer D=GCDiv(N,P*Q);
     
     if( D.cmp(1)!=0 )
       {
        for(auto &p : pset ) 
          if( N.cmp(p.prime)==0 ) 
            {
             func("Prime\n");
             
             return IsPrime;
            }
        
        for(auto q : qset ) 
          if( N.cmp(q)==0 ) 
            {
             func("Prime\n");
             
             return IsPrime;
            }
       
        func("HasDivisor from P or Q\n");
        
        return HasDivisor;
       }
     
     return HardCase;
    }
   
   template <class Func>
   TestResult test(Integer N,const TestSet &p,Func &func) const
    {
     Engine engine(N);
     TestResult ret=HardCase;
     
     func("test p = #;\n",p.prime);
     
     for(ulen k=0; k<p.jset.len ;k++)
       {
        func("  #; q = #;\n",p.jset.len-k,p.jset[k].prime_q);
        
        switch( engine.test(p.prime,p.jset[k]) )
          {
           case IsPrime : ret=IsPrime; break;
           
           case NoPrime : func("NoPrime\n"); return NoPrime;
          }
       }
     
     return ret;
    }
   
   bool testOrder(unsigned p,Integer N) const
    {
     Integer M=p;
     
     ModEngine<Integer> engine(M.sq());
     
     N=engine.prepare(N);

     return engine.template exp<unsigned>(N,p-1).cmp(1)!=0;
    }
   
   template <class Func>
   TestResult finish(Integer N,Func &func) const
    {
     ModEngine<Integer> engine(Q);
     
     Integer D1=engine.prepare(N);
     Integer D=D1;
     
     for(Integer cnt=P-1; cnt.sign() ;cnt-=1,D=engine.mul(D,D1))
       {
        func("D #;\n",cnt);
        
        if( D.cmp(1)>0 && D<N && (N%D)==0 )
          {
           func("Divisor #;\n",D);
          
           return HasDivisor;
          }
       }
     
     func("Prime\n");
     
     return IsPrime;
    }
   
  public:
 
   explicit TestEngine(ulen n)
    : TestData(n) 
    {
     P=OctetInteger<Integer>(octP);
     Q=OctetInteger<Integer>(octQ);
    }
   
   Integer getCap() const { return Q*Q; }
   
   template <class Func>
   TestResult operator () (Integer N,Func &func) const
    {
     func("N = #;\n",N);
     
     TestResult ret;
     
     if( (ret=sanity(N,func))!=HardCase ) return ret;
     
     DynArray<bool> flags(pset.len);

     for(ulen i=0; i<pset.len ;i++)
       {
        ret=test(N,pset[i],func);
        
        if( ret==NoPrime ) return NoPrime;
        
        if( ret==IsPrime ) flags[i]=true;
       }
     
     for(ulen i=0; i<pset.len ;i++)
       {
        if( !flags[i] )
          {
           if( !testOrder(pset[i].prime,N) ) 
             {
              func("HardCase\n");
              
              return HardCase;
             }
          }
       }
     
     return finish(N,func);
    }
 };

#endif

/* types */

using QType = uint64 ;

/* functions */

QType MulGuarded(QType a,QType b);

QType AddGuarded(QType a,QType b);

/* classes */

//enum TestResult;

class SmallPrimesSet;

class QModEngine;

class PrimeQ;

class Jacobi;

class JacobiSumTable;

class PrimeP;

class DataGen;

struct TestSet;

class TestData;

class NoReport;

template <class Integer> class TestEngine;

/* enum TestResult */

enum TestResult
 {
  IsPrime = 0,
  
  NoPrime,
  HasDivisor,
  HardCase,
  TooLarge
 };

const char * GetTextDesc(TestResult res);

/* class SmallPrimesSet */

class SmallPrimesSet // odd subsequent SmallPrimes 3, 5, 7, ... 
 {
   RefArray<bool> flags;
   
  private:
   
   template <class Func>
   void forPrimes(Func &func) const
    {
     auto r=Range(flags);
     
     for(ulen i=0,len=r.len; i<len ;i++) if( r[i] ) func( SmallPrimes[i+1] );
    }
   
  public:
   
   explicit SmallPrimesSet(unsigned n) : flags(n) {}

   ~SmallPrimesSet() {}
   
   bool operator [] (unsigned ind) const { return flags[ind]; }
   
   unsigned getSetNumber() const;
   
   bool next();
 
   template <class FuncInit>
   void forOddPrimes(FuncInit func_init) const
    {
     FunctorTypeOf<FuncInit> func(func_init);
     
     forPrimes(func);
    }
   
   template <class FuncInit>
   void forAllPrimes(FuncInit func_init) const
    {
     FunctorTypeOf<FuncInit> func(func_init);
     
     func(2);
     
     forPrimes(func);
    }
 
   QType getPrimeQ() const;
 };

/* class QModEngine */

class QModEngine : NoCopy
 {
   QType mod;
   
  public:
   
   explicit QModEngine(QType mod_) : mod(mod_) {}
   
   QType mul(QType a,QType b) const;
   
   QType sq(QType a) const { return mul(a,a); }
   
   QType pow(QType a,QType d) const;
 };

/* class PrimeQ */

class PrimeQ : public NoThrowFlagsBase , public CmpComparable<PrimeQ>
 {
   SmallPrimesSet spset;

   QType prime; // 1+2*(odd p from spset)
   unsigned set_number;
   QType gen;
  
  public:
  
   explicit PrimeQ(const SmallPrimesSet &spset);

   ~PrimeQ() {}
   
   // props
  
   bool hasP(unsigned ind) const { return spset[ind]; }
   
   QType getPrime() const { return prime; }
   
   unsigned getSetNumber() const { return set_number; }
   
   QType getGen() const { return gen; }
   
   // cmp objects
  
   CmpResult objCmp(const PrimeQ &obj) const
    {
     return AlphaCmp(set_number,obj.set_number,prime,obj.prime);
    }
   
   // methods
   
   bool test();
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"prime = #; : 1 + 2",prime);
     
     spset.forOddPrimes( [&] (unsigned p) { Printf(out," * #;",p); } );
     
     Printf(out,"\nset_number = #;\ngen = #;\n",set_number,gen);
    }
 };

/* class Jacobi */

class Jacobi : QModEngine
 {
   QType prime;
   unsigned set_number;
   QType gen;
   
   DynArray<ulen> table;

  private:
   
   unsigned log_table(QType x,unsigned p) const // 0 < x < prime
    {
     return unsigned( table[ (ulen)x-1 ]%p ); 
    }
   
   class LogPow : NoCopy
    {
      const QModEngine &engine;
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
   
   static void GuardLog();
   
   template <class Func>
   void addLog(unsigned p,Func func) const
    {
     if( table.getLen() )
       {
#if 1
       
        QType x=2,y=prime-1;
        
        for(; x<y ;x++,y--) 
          {
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
        
        QType x=2,y=prime-1;
        
        for(; x<y ;x++,y--) 
          {
           unsigned a=log(x);
           unsigned b=log(y);
           
           if( a!=log_table(x,p) || b!=log_table(y,p) ) GuardLog();
           
           func(a,b);
           func(b,a);
          }
        
        {
         unsigned c=log(x);
         
         if( c!=log_table(x,p) ) GuardLog();
         
         func(c,c);
        }
        
#endif        
       }
     else
       {
        LogPow log(*this,p);
        
        QType x=2,y=prime-1;
        
        for(; x<y ;x++,y--) 
          {
           unsigned a=log(x);
           unsigned b=log(y);
           
           func(a,b);
           func(b,a);
          }
        
        {
         unsigned c=log(x);
         
         func(c,c);
        }
       }
    }
   
   class LogCountTable : NoCopy
    {
      unsigned p;
      DynArray<QType> table; // [p*p]

     private: 
      
      void add(unsigned a,unsigned b) { table[a*p+b]++; }
      
      QType count(unsigned a,unsigned b) const { return table[a*p+b]; }
      
     public:
      
      LogCountTable(const Jacobi &jac,unsigned p);
      
      ~LogCountTable() {}
      
      void operator () (unsigned k,QType result[ /* p */ ]) const; // result is erased
    };
   
  public:
   
   Jacobi(QType prime,unsigned set_number,QType gen);
   
   Jacobi(const PrimeQ &q) : Jacobi(q.getPrime(),q.getSetNumber(),q.getGen()) {}
   
   ~Jacobi() {}
   
   QType getPrime() const { return prime; }
   
   unsigned getSetNumber() const { return set_number; }
   
   void operator () (unsigned p,QType result[ /* (p-2)*p */ ]) const; // p > 2
 };

/* class JacobiSumTable */

class JacobiSumTable : public NoThrowFlagsBase
 {
   QType prime_q;
   unsigned set_number;
   
   unsigned prime_p;
   RefArray<QType> table;
   
  public:
  
   JacobiSumTable(const Jacobi &jac,unsigned prime_p);
  
   ~JacobiSumTable() {}
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"  q = #;\n  set_number = #;\n",prime_q,set_number);
     
     if( prime_p>2 )
       {
        auto r=Range(table);
        
        while( +r )
          {
           auto j=(r+=prime_p);
           
           Printf(out,"  #;\n",PrintSet(j));
          }
       }
    }
 };

/* class PrimeP */

class PrimeP : public NoThrowFlagsBase
 {
   unsigned prime;
  
   RefArray<ulen> qlist;
  
   RefArray<JacobiSumTable> jset;

  public:
  
   explicit PrimeP(PtrLen<const PrimeQ> qset);
  
   PrimeP(PtrLen<const PrimeQ> qset,unsigned ind);
  
   ~PrimeP() {}
   
   // props
   
   unsigned getPrime() const { return prime; }
   
   // methods
   
   template <class FuncInit>
   void forQInd(FuncInit func_init) const
    {
     qlist.apply(func_init);
    }
   
   void update(const Jacobi &jac) { jset.append_fill(jac,prime); }
 
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"p = #;\n\n",prime);
     
     for(const JacobiSumTable &jtable : jset ) Printf(out,"#;\n-----\n\n",jtable);
    }
 };

/* class DataGen */

class DataGen : NoCopy
 {
   DynArray<PrimeQ> qset; // odd
   DynArray<PrimeP> pset;
   
  public: 
   
   explicit DataGen(unsigned n);
   
   ~DataGen();
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     for(const PrimeQ &q : qset ) Printf(out,"#;\n------------\n\n",q);
     
     for(const PrimeP &p : pset ) Printf(out,"#;\n------------\n\n",p);
    }
 };

/* struct TestSet */

struct TestSet
 {
  unsigned prime_p;
  
  struct PrimeQ
   {
    QType prime_q;
    unsigned set_number;
   };
  
  struct JTable : PrimeQ
   {
    const QType *table; // [ (prime_p-2)*prime_p ]
   };
  
  PtrLen<const JTable> jset;
 };

/* class TestData */

class TestData : NoCopy
 {
  protected:
  
   const TestSet *pset;                // MaxN+1
   PtrLen<const TestSet::PrimeQ> qset; // odd
   
  public:

   static const unsigned MaxN = 8 ;
   
   TestData() : pset(0) {}
 };

/* class NoReport */

class NoReport
 {
  public:
   
   NoReport() {}
  
   template <class Integer>
   void start(Integer N) { Used(N); }
   
   void sanity(const char *msg) { Used(msg); }
   
   void test(unsigned prime_p) { Used(prime_p); }
   
   void startProbe() {}
   
   template <class Integer>
   void probe(Integer D) { Used(D); }
   
   template <class Integer>
   void div(Integer D) { Used(D); }
   
   void hard() {}
   
   void isPrime() {}
   
   void noPrime() {}
 };

/* class TestEngine<Integer> */

template <class Integer> 
class TestEngine : TestData
 {
   Integer P[MaxN];
   Integer Q[MaxN];
   Integer Q2[MaxN];
 
  private:
   
   using Ring = RefArray<Integer> ;
   
   class Engine : NoCopy
    {
      ModEngine<Integer> engine;
      
      Integer Nminus1;
      
     private:
      
      Ring prepare(const QType *table,unsigned prime,unsigned k) const
       {
        table+=k*prime;
       
        Ring ret=Ring(prime);

        auto r=ret.modify();
        
        for(; +r ;++r,++table) *r=engine.prepare(*table); 
        
        return ret;
       }
      
      Ring mul(Ring a,Ring b) const
       {
        auto ra=Range(a);
        auto rb=Range(b);
        
        ulen len=ra.len;
        Ring ret(len);
        
        auto res=ret.modify();
        
        for(ulen i=0; i<len ;i++)
          for(ulen j=0; j<len ;j++)
            {
             ulen k=i+j;
             
             if( k>=len ) k-=len;
             
             res[k]=engine.mac(res[k],ra[i],rb[j]);
            }
        
        return ret;
       }
      
      Ring mul(Ring a,QType b) const
       {
        auto r=a.modify();
        auto b_=engine.prepare(b);
        
        for(; +r ;++r) *r=engine.mul(*r,b_);
        
        return a;
       }

      Ring one(ulen len) const
       {
        Ring ret=Ring(len);
        
        ret.modify()[0]=1;
        
        return ret;
       }
      
      Ring pow(Ring a,Integer d) const
       {
        for(IntegerBitScanner<Integer> scanner(d); +scanner ;++scanner)
          if( *scanner ) 
            {
             Ring ret=a;
             
             for(++scanner; +scanner ;++scanner)
               {
                ret=mul(ret,ret);
                
                if( *scanner ) ret=mul(ret,a);
               }
             
             return ret;
            }

        return one(a.getLen());
       }
      
      int test(Integer a,Integer b) const // 0, 1, other=2 : a-b mod N
       {
        switch( Cmp(a,b) )
          {
           case CmpLess :
            {
             if( !a && b==Nminus1 ) return 1;
             
             return 2;
            }
           break;
         
           case CmpGreater :
            {
             if( a-b==1 ) return 1;
             
             return 2;
            }
           break;
         
           default: return 0;
          }
       }
      
      TestResult test(Ring cappa) const
       {
        auto r=Range(cappa);
        
        Integer a=r[0];
        Integer b=r[1];
   
        if( test(a,b)==1 )
          {
           for(r+=2; +r ;++r) if( *r!=b ) return NoPrime;
           
           return HardCase;
          }
        else
          {
           bool flag=true;
           
           for(++r; +r ;++r)
             {
              if( flag )
                {
                 switch( test(*r,a) )
                   {
                    case 0 : break;
                     
                    case 1 : flag=false; break;
                     
                    case 2 : return NoPrime;
                   }
                }
              else
                {
                 if( *r!=a ) return NoPrime;
                }
             }
           
           return flag?NoPrime:IsPrime;
          }
       }
      
      static TestResult Test(int cappa,int sign)
       {
        if( cappa==sign ) return HardCase;
        
        if( cappa==-sign ) return IsPrime;
        
        return NoPrime;
       }
      
      TestResult test(Integer cappa,int sign) const
       {
        if( cappa==1 ) return Test(1,sign);
        
        if( cappa==Nminus1 ) return Test(-1,sign);
        
        return NoPrime;
       }
      
     public:
      
      explicit Engine(Integer N) : engine(N),Nminus1(N-1) {}
      
      ~Engine() {}
      
      TestResult test(unsigned prime,const TestSet::JTable &jtable) const
       {
        if( prime>2 )
          {
           DynArray<Ring> theta(prime-2);
           
           theta[0]=prepare(jtable.table,prime,0);
           
           for(unsigned k=1; k<prime-2 ;k++) theta[k]=mul(theta[k-1],prepare(jtable.table,prime,k));
           
           Ring omega=mul(theta[prime-3],jtable.prime_q);
           
           auto res=engine.getModule().divmod(prime);
           
           unsigned mod=res.mod.template cast<unsigned>();
           
           Ring cappa=pow(omega,res.div);
           
           if( mod>1 ) cappa=mul(cappa,theta[mod-2]);
           
           return test(cappa);
          }
        else
          {
           Integer omega=engine.prepare(jtable.prime_q);
           Integer d=Nminus1>>1;
           
           Integer cappa=engine.pow(omega,d);
           
           if( d.isEven() )
             {
              return test(cappa,1);
             }
           else
             {
              return test(cappa,-1);
             }
          }
       }
    };
   
  private:
   
   template <class Report>
   TestResult sanity(Integer N,unsigned &set_number,Report &report) const
    {
     if( N<=1 ) 
       {
        report.sanity("N <= 1 NoPrime");
       
        return NoPrime;
       }
     
     unsigned n=MaxN-1;
     
     if( N>=Q2[n] ) 
       {
        report.sanity("N >= Q*Q TooLarge");       
       
        return TooLarge;
       }
     
     while( n>0 && N<Q2[n-1] ) n--;
     
     set_number=n;
     
     Integer D=GCDiv(N,P[n]*Q[n]);
     
     if( D>1 )
       {
        for(unsigned i=0; i<n+2 ;i++)
          {
           if( N==pset[i].prime_p )
             {
              report.isPrime();
             
              return IsPrime;
             } 
          }
        
        for(auto r=qset; +r && r->set_number<=n ;++r)
          {
           if( N==r->prime_q ) 
             {
              report.isPrime();
              
              return IsPrime;
             }
          }
       
        report.sanity("HasDivisor from P or Q");
        
        return HasDivisor;
       }
     
     return HardCase;
    }
   
   template <class Report>
   TestResult test(Integer N,unsigned set_number,const TestSet &tset,Report &report) const
    {
     if( tset.jset.len==0 || tset.jset[0].set_number>set_number ) return IsPrime;
     
     Engine engine(N);
     TestResult ret=HardCase;
     
     report.test(tset.prime_p);
     
     for(ulen k=0; k<tset.jset.len && tset.jset[k].set_number<=set_number ;k++)
       {
        switch( engine.test(tset.prime_p,tset.jset[k]) )
          {
           case IsPrime : ret=IsPrime; break;
           
           case NoPrime : report.noPrime(); return NoPrime;
          }
       }
     
     return ret;
    }
   
   static bool TestOrder(unsigned p,Integer N)
    {
     Integer M=p;
     
     ModEngine<Integer> engine(M.sq());
     
     N=engine.prepare(N);

     return engine.template pow<unsigned>(N,p-1)!=1;
    }
   
   template <class Report>
   TestResult finish(Integer N,unsigned set_number,Report &report) const
    {
     report.startProbe();
     
     ModEngine<Integer> engine(Q[set_number]);
     
     Integer D1=engine.prepare(N);
     Integer D=D1;
     
     for(Integer cnt=P[set_number]-1; cnt>0 ;cnt-=1,D=engine.mul(D,D1))
       {
        report.probe(cnt);
        
        if( D>1 && D<N && !(N%D) )
          {
           report.div(D);
          
           return HasDivisor;
          }
       }
     
     report.isPrime();
     
     return IsPrime;
    }
   
  public:
 
   TestEngine()
    {
     // 1
     {
      Integer prod=pset[0].prime_p;
      
      for(unsigned n=0; n<MaxN ;n++) 
        {
         prod*=pset[n+1].prime_p;
         
         P[n]=prod;
        }
     }
     
     // 2
     {
      Integer prod=2;
      auto r=qset;
      
      for(unsigned n=0; n<MaxN ;n++)
        {
         while( +r && r->set_number<=n ) prod*=r->prime_q; 
        
         Q[n]=prod;
         Q2[n]=prod.sq();
        }
     }
    }
   
   ~TestEngine() {}
   
   template <class Report>
   TestResult operator () (Integer N,Report &report) const
    {
     report.start(N);
     
     TestResult ret;
     unsigned set_number;
     
     if( (ret=sanity(N,set_number,report))!=HardCase ) return ret;
     
     DynArray<bool> flags(set_number+2);

     for(unsigned i=0; i<set_number+2 ;i++)
       {
        ret=test(N,set_number,pset[i],report);
        
        if( ret==NoPrime ) return NoPrime;
        
        if( ret==IsPrime ) flags[i]=true;
       }
     
     for(unsigned i=0; i<set_number+2 ;i++)
       {
        if( !flags[i] )
          {
           if( !TestOrder(pset[i].prime_p,N) ) 
             {
              report.hard();
              
              return HardCase;
             }
          }
       }
     
     return finish(N,set_number,report);
    }
 };

} // namespace APRTest
} // namespace Math
} // namespace CCore
 
#endif
 

