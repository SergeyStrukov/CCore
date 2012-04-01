/* Counters.h */ 
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

#ifndef CCore_inc_Counters_h
#define CCore_inc_Counters_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */ 

template <class Enum,Enum Lim> class Counters;

/* class Counters<Enum,Enum Lim> */ 

template <class Enum,Enum Lim>
class Counters : public PrintOptAdapter<Enum>
 {
   unsigned counter[Lim];
   
  private:
  
   static void DiffCnt(unsigned &cur,unsigned &next) { next=Diff(cur,next); }
   
  public:
  
   Counters() : counter() {}
   
   void reset() { (*this)=Counters(); }
   
   void count(Enum e) { counter[e]++; }
   
   void count(Enum e,unsigned cnt) { counter[e]+=cnt; }
   
   unsigned operator [] (Enum e) const { return counter[e]; }
   
   void diff(Counters<Enum,Lim> &next)
    // (*this) <- next
    //    next <- next-(*this)
    {
     for(ulen i=0; i<DimOf(counter) ;i++) DiffCnt(counter[i],next.counter[i]);
    }
    
   void operator -= (const Counters<Enum,Lim> &base) 
    {
     for(ulen i=0; i<DimOf(counter) ;i++) counter[i]-=base.counter[i];
    }
   
   // print object
 
   template <class P> 
   void print(P &out) const
    {
     for(ulen i=0; i<DimOf(counter) ;i++) 
       {
        if( unsigned cnt=counter[i] )
          {
           Printf(out,"#; = #;\n",Enum(i),cnt);
          }
       }
    }
    
   template <class P,class Opt> 
   void print(P &out,const Opt &opt) const
    {
     for(ulen i=0; i<DimOf(counter) ;i++) 
       {
        if( unsigned cnt=counter[i] )
          {
           Printf(out,"#; = #;\n",BindOpt(opt,Enum(i)),cnt);
          }
       }
    }
 };
 
} // namespace CCore
 
#endif



