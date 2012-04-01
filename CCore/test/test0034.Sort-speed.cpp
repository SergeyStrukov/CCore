/* test0034.Sort-speed.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Counters.h>

#include <algorithm>

namespace App {

namespace Private_0034 {

/* consts */

const ulen Count = 1000 ;

/* struct StdSort<Ran,Ctx> */ 

template <class Ran,class Ctx> 
struct StdSort
 {
  template <class T>
  static void Sort(T *ptr,ulen len) { std::sort(ptr,ptr+len); }
 };

/* class Engine<Algo> */

template <template <class Ran,class Ctx> class Algo>
class Engine
 {
   typedef unsigned Type; 
 
   Random random;
   
  private:
  
   Type next() { return random.next_uint<unsigned>(); }
  
   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) *(ptr++)=next();
    }
 
   ClockTimer::ValueType sort(Type *ptr,ulen len)
    {
     ClockTimer timer;
     
     Algo<Type *,SortCtx<Type *> >::Sort(ptr,len);
     
     return timer.get();
    }
    
  public:
  
   Engine() {}
   
   ~Engine() {}
   
   void run(ulen len)
    {
     Printf(Con,"len = #8;  ",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();
     
     TimeStat<ClockTimer::ValueType> stat;
     
     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);
        
        ClockTimer::ValueType t=sort(ptr,len);
        
        stat.add(t);
       }
       
     stat.div(len);  
       
     Printf(Con,"#3;\n",stat);  
    }
 };
 
/* class Engine2<Algo> */

template <template <class Ran,class Ctx> class Algo>
class Engine2
 {
   class Fill
    {
      Random &gen;
      ulen len;
     
     public: 
      
      explicit Fill(Random &gen_) : gen(gen_),len(gen.select(5,25)) {}
      
      ulen getLen() const { return len; }
      
      PtrLen<char> operator () (Place<void> place)
       {
        PtrLen<char> ret(place,len);
        
        for(auto r=ret; +r ;++r) *r=gen.next8();
        
        return ret;
       }
    };
  
   class Type : public String
    {
     public:
      
      Type() {}
      
      explicit Type(Random &gen) : String(DoBuild,Fill(gen)) {}
      
      bool operator < (const Type &obj) const { return StrLess(Range(*this),Range(obj)); }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
 
   Random random;
   
  private:
  
   Type next() { return Type(random); }
  
   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) *(ptr++)=next();
    }
 
   ClockTimer::ValueType sort(Type *ptr,ulen len)
    {
     ClockTimer timer;
     
     Algo<Type *,SortCtx<Type *> >::Sort(ptr,len);
     
     return timer.get();
    }
    
  public:
  
   Engine2() {}
   
   ~Engine2() {}
   
   void run(ulen len)
    {
     Printf(Con,"len = #8;  ",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();
     
     TimeStat<ClockTimer::ValueType> stat;
     
     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);
        
        ClockTimer::ValueType t=sort(ptr,len);
        
        stat.add(t);
       }
       
     stat.div(len);  
       
     Printf(Con,"#3;\n",stat);  
    }
 };

/* class Engine3<Algo> */

enum Event
 {
  EventCmp,
  EventSwap,
  EventCopy,
  EventAssign,
  
  EventLim
 };

static const char * GetTextDesc(Event ev)
 {
  static const char *const Table[]=
   {
    "Cmp",
    "Swap",
    "Copy",
    "Assign",
     
    "" 
   };
  
  return Table[ev];
 }

typedef Counters<Event,EventLim> Stat;

template <template <class Ran,class Ctx> class Algo>
class Engine3
 {
   class Type
    {
      unsigned value;
      
      static Stat OpStat;
     
     public:
      
      Type() : value() {}
      
      void set(Random &gen) { value=gen.next_uint<unsigned>(); }
      
      Type(const Type &obj)
       : value(obj.value)
       {
        OpStat.count(EventCopy);
       }
      
      Type & operator = (const Type &obj)
       {
        value=obj.value;
        
        OpStat.count(EventAssign);
        
        return *this;
       }
      
      bool operator < (const Type &obj) const 
       {
        OpStat.count(EventCmp);
        
        return value<obj.value; 
       }
      
      void objSwap(Type &obj)
       {
        OpStat.count(EventSwap);
        
        Swap(value,obj.value);
       }
      
      static void ResetStat() { OpStat.reset(); }
      
      static const Stat & GetStat() { return OpStat; }
      
      // no-throw flags
      
      enum NoThrowFlagType
       {
        Default_no_throw = true,
        Copy_no_throw = true
       };
    };
 
   Random random;
   
  private:
  
   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) (ptr++)->set(random);
    }
 
   void sort(Type *ptr,ulen len)
    {
     Algo<Type *,SortCtx<Type *> >::Sort(ptr,len);
    }
    
  public:
  
   Engine3() {}
   
   ~Engine3() {}
   
   void run(ulen len)
    {
     Printf(Con,"len = #8;\n",len);
    
     SimpleArray<Type> a(len);
     
     Type *ptr=a.getPtr();
     
     Type::ResetStat();

     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);
        
        sort(ptr,len);
       }
       
     Printf(Con,"#10;\n\n",Type::GetStat());  
    }
 };

template <template <class Ran,class Ctx> class Algo>
Stat Engine3<Algo>::Type::OpStat;
      
} // namespace Private_0034
 
using namespace Private_0034; 
 
/* Testit<34> */ 

template<>
const char *const Testit<34>::Name="Test34 Sort speed";

template<>
bool Testit<34>::Main() 
 {
#if 1  
  
  Printf(Con,"#;\n\n",Title("ParaQuickSort"));
 
  {
   Job::Init job_init;
   
   Engine<ParaQuickSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
   engine.run(100000);
  } 
  
  Printf(Con,"\n#;\n\n",Title("ParaQuickSort -- 1 task"));
 
  {
   Engine<ParaQuickSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
   engine.run(100000);
  } 
  
  Printf(Con,"\n#;\n\n",Title("QuickSort"));
 
  {
   Engine<QuickSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
   engine.run(100000);
  } 
 
  Printf(Con,"\n#;\n\n",Title("HeapSort"));
 
  {
   Engine<HeapSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
   engine.run(100000);
  } 
 
  Printf(Con,"\n#;\n\n",Title("StdSort"));
 
  {
   Engine<StdSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
   engine.run(100000);
  }
  
#endif
  
#if 1  
 
  Printf(Con,"\n#;\n\n",Title("QuickSort string"));
 
  {
   Engine2<QuickSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
  }
  
  Printf(Con,"\n#;\n\n",Title("StdSort string"));
 
  {
   Engine2<StdSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
  }
  
#endif
  
#if 1  
  
  Printf(Con,"\n#;\n\n",Title("QuickSort count"));
 
  {
   Engine3<QuickSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
  }
  
  Printf(Con,"\n#;\n\n",Title("StdSort count"));
 
  {
   Engine3<StdSort> engine;
  
   engine.run(100);
   engine.run(1000);
   engine.run(10000);
  }

#endif  
  
  return true;
 }

} // namespace App
 
