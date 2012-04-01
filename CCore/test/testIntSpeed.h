/* testIntSpeed.h */
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_testIntSpeed_h
#define CCore_test_testIntSpeed_h

#include <CCore/test/test.h>

#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/String.h>

namespace App {

/* classes */

template <class Algo> class TestIntegerSpeed;

/* class TestIntegerSpeed<Algo> */

template <class Algo>
class TestIntegerSpeed
 {
   typedef typename Algo::Unit Unit;
  
   static const ulen Len = 100 ;
   static const unsigned Rep = 100 ;
   static const unsigned Rep2 = 10 ;
  
   typedef TimeStat<ClockTimer::ValueType> Stat;
   
  private: 
  
   Random gen;
  
   Unit a[Len];
   Unit b[Len];
   Unit c[2*Len];
  
   Stat table[Len+1];
  
   Unit trash;
   
  private: 
  
   TestIntegerSpeed() : trash() {}
  
   void fill(PtrLen<Unit> r) { gen.fill(r); }
   
   unsigned select(unsigned a,unsigned b) { return gen.select(a,b); }
  
  private: 
  
   Stat testNull(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::Null(a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUAdd(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::UAdd(b,a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUSub(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::USub(b,a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testURevSub(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::URevSub(b,a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testMoveUp(ulen n,ulen delta)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(c,n+delta));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::MoveUp(c,n,delta);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testMoveDown(ulen n,ulen delta)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(c,n+delta));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::MoveDown(c,n,delta);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
  
   Stat testULShift(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        unsigned shift=select(1,Algo::UnitBits-1);
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::ULShift(a,n,shift);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testLShift(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        unsigned shift=select(1,Algo::UnitBits-1);
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::LShift(b,a,n,shift);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testRShift(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        unsigned shift=select(1,Algo::UnitBits-1);
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::RShift(b,a,n,shift);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testShiftDown(ulen n,ulen delta)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(c,n+delta));
        
        unsigned shift=select(1,Algo::UnitBits-1);
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::ShiftDown(c,n,delta,shift);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testShiftUp(ulen n,ulen delta)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(c,n+delta));
        
        unsigned shift=select(1,Algo::UnitBits-1);
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) trash+=Algo::ShiftUp(c,n,delta,shift);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUMul(ulen n,ulen m)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,m));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::UMul(c,a,n,b,m);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUMulLo(ulen n,ulen m,ulen nc)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,m));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::UMulLo(c,nc,a,n,b,m);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUSq(ulen n)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::USq(c,a,n);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
   Stat testUMac(ulen n,ulen m)
    {
     Stat stat;
     
     for(unsigned cnt=Rep; cnt ;cnt--)
       {
        fill(Range(a,n));
        fill(Range(b,m));
        fill(Range(c,m+n));
        
        ClockTimer timer;
        
        for(unsigned cnt=Rep2; cnt ;cnt--) Algo::UMac(c,a,n,b,m);
        
        stat.add(timer.get());
       }
 
     return stat;
    }
   
  private:
   
   template <class P>
   void showStat(P &&out)
    {
     for(ulen n=1; n<=Len ;n++) 
       {
        Stat stat=table[n];
        
        stat.div(Rep2);
        
        Printf(out,"n = #; #;\n",n,stat);
       }
    }
   
   template <class P>
   void show(P &&out,StrLen title)
    {
     Printf(out,"#;\n",Title(title));
     
     unsigned a=UIntMax();
 
     for(ulen n=Len/2; n<=Len ;n++)
       {
        auto val=table[n].getMin();
 
        Replace_min<unsigned>(a,val/n);
       }
     
     for(ulen n=1; n+9<=Len ;n+=10)
       {
        unsigned b=0;
        
        for(ulen k=n; k<=n+9 ;k++)
          {
           auto val=PosSub(table[k].getMin(),a*k);
           
           Replace_max<unsigned>(b,val);
          }
        
        Printf(out,"time[#3;-#3;] (#;*n+#;)/#;\n",n,n+9,a,b,+Rep2);
       }
     
     //showStat(out);
    }
  
   template <class P>
   void show2(P &&out,StrLen title)
    {
     Printf(out,"#;\n",Title(title));
     
     unsigned a=UIntMax();
 
     for(ulen n=Len/2; n<=Len ;n++)
       {
        auto val=table[n].getMin();
 
        Replace_min<unsigned>(a,val/n/n);
       }
     
     for(ulen n=1; n+9<=Len ;n+=10)
       {
        unsigned b=0;
        
        for(ulen k=n; k<=n+9 ;k++)
          {
           auto val=PosSub(table[k].getMin(),a*k*k);
           
           Replace_max<unsigned>(b,val);
          }
        
        Printf(out,"time[#3;-#3;] (#;*n*n+#;)/#;\n",n,n+9,a,b,+Rep2);
       }
     
     //showStat(out);
    }
  
   template <class P>
   void run(P &&out,StrLen title)
    {
     Printf(out,"#;\n\n",Title(title));
     
     for(ulen n=1; n<=Len ;n++) table[n]=testNull(n);
     
     show(out,"Null");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testUAdd(n);
     
     show(out,"UAdd");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testUSub(n);
     
     show(out,"USub");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testURevSub(n);
     
     show(out,"URevSub");
 
     for(ulen n=1; n<=Len ;n++) table[n]=testMoveUp(n,10);
     
     show(out,"MoveUp 10");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testMoveUp(n,2);
     
     show(out,"MoveUp 2");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testMoveDown(n,10);
     
     show(out,"MoveDown 10");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testMoveDown(n,2);
     
     show(out,"MoveDown 2");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testULShift(n);
 
     show(out,"ULShift");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testLShift(n);
 
     show(out,"LShift");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testRShift(n);
     
     show(out,"RShift");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testShiftDown(n,10);
     
     show(out,"ShiftDown 10");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testShiftDown(n,2);
     
     show(out,"ShiftDown 2");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testShiftUp(n,10);
     
     show(out,"ShiftUp 10");
     
     for(ulen n=1; n<=Len ;n++) table[n]=testShiftUp(n,2);
     
     show(out,"ShiftUp 2");
     
     for(ulen m=10; m<=Len ;m+=10)
       {
        for(ulen n=1; n<=Len ;n++) table[n]=testUMul(n,m);
       
        String str=Stringf("UMul #;",m);
       
        show(out,Range(str));
       }
    
     for(ulen m=10; m<=Len ;m+=10)
       {
        for(ulen n=1; n<=Len ;n++) table[n]=testUMac(n,m);
       
        String str=Stringf("UMac #;",m);
       
        show(out,Range(str));
       }
    
     for(ulen m=10; m<=Len ;m+=10)
       {
        for(ulen n=1; n<=Len ;n++) table[n]=testUMulLo(n,m,(n+m)/2);
     
        String str=Stringf("UMulLo #;",m);
        
        show(out,Range(str));
       }
     
     for(ulen n=1; n<=Len ;n++) table[n]=testUSq(n);
     
     show2(out,"USq");
     
     Printf(out,"\n#;\n\n",TextDivider());
    }
   
  public:
  
   template <class P>
   static void Run(P &&out,StrLen title)
    {
     TestIntegerSpeed<Algo> obj;
     
     obj.run(out,title);
    }
 };

} // namespace App
 
#endif
 
