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

#include <CCore/inc/FunctorType.h>
#include <CCore/inc/math/IntegerOctetBuilder.h>

namespace CCore {
namespace Math {
namespace APRTest {

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
     
     Printf(out,"static const uint8 P#;[]=#;;\n\n",number,PrintIntegerOctets<Integer>(this->P));
     
     Printf(out,"static const uint8 Q#;[]=#;;\n\n",number,PrintIntegerOctets<Integer>(Q));
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
     P=Integer(DoBuild,IntegerOctetBuilder<Integer>(octP));
     Q=Integer(DoBuild,IntegerOctetBuilder<Integer>(octQ));
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

} // namespace APRTest
} // namespace Math
} // namespace CCore
 
#endif
 

