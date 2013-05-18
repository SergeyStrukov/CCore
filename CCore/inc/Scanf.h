/* Scanf.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Scanf_h
#define CCore_inc_Scanf_h

#include <CCore/inc/scanf/ScanBase.h>
#include <CCore/inc/scanf/ScanProxy.h>
#include <CCore/inc/Tuple.h>
 
namespace CCore {

/* classes */

template <class S> class ScanobjDev;

/* class ScanobjDev<S> */ 

template <class S> 
class ScanobjDev : NoCopy
 {
   S inp;
   
  private:
   
   // step_tuple
  
   void step_tuple(const Tuple<> &) {}
 
   template <class T>
   void step_tuple(Tuple<T> &tuple) { step(tuple.first); }
 
   template <class T1,class T2,class ... TT>
   void step_tuple(Tuple<T1,T2,TT...> &tuple)
    {
     step(tuple.first);
     step_tuple(tuple.rest);
    }
   
   // step
    
   template <class T>
   void step(T &t)
    {
     ScanAdapter<T>::Scan(inp,t);
    }
  
   template <class ... TT>
   void step(Tuple<TT...> &tuple)
    {
     step_tuple(tuple);
    }
   
   // scan
    
   void scan() {}
 
   template <class T1,class ... TT>
   void scan(T1 &t1,TT & ... tt)
    {
     step(t1);

     scan(tt...);
    }
 
   template <class T1,class T2,class ... TT>
   void scan(T1 &t1,T2 &t2,TT & ... tt)
    {
     step(t1);
     step(t2);

     scan(tt...);
    }
 
   template <class T1,class T2,class T3,class ... TT>
   void scan(T1 &t1,T2 &t2,T3 &t3,TT & ... tt)
    {
     step(t1);
     step(t2);
     step(t3);

     scan(tt...);
    }
 
  public:
  
   template <class T>
   explicit ScanobjDev(T &&inp_) : inp(inp_) {}
   
   ~ScanobjDev() {}
   
   template <class ... TT>
   void operator () (TT & ... tt)
    {
     scan(tt...);
    }
 };

/* Scanf() */

template <class S,class ... TT>
void Scanf(S &&inp,const char *format,TT & ... tt) CCORE_NOINLINE ;

/* Scanobj() */

template <class S,class ... TT>
void Scanobj(S &&inp,TT & ... tt) CCORE_NOINLINE ;

template <class S,class ... TT>
void Scanobj(S &&inp,TT & ... tt) 
 {
  typedef typename ScanInpAdapter<typename std::remove_reference<S>::type>::ScanInpType SInp;
  
  ScanobjDev<SInp> dev(inp);
  
  dev(tt...);
 }

} // namespace CCore
 
#endif
 

