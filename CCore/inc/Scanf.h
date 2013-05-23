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

struct ProbeSet_ScanSwitch;

template <class T> struct ScanSwitch;

template <int Sw,class T> struct ScanOptAdapters;

template <int Sw,class T> struct ScanAdapters;

template <class T> struct ScanOptAdapter;

template <class T> struct ScanAdapter;

struct ScanDevBase;

template <class S> class ScanfDev;

template <class S> class ScanobjDev;

template <class OptType,class T> struct BindScanOptType;

/* struct ProbeSet_ScanSwitch */

struct ProbeSet_ScanSwitch
 {
  template <class T> struct Host;  
 
  template <class T>
  static constexpr int Probe(...) { return 0; }
     
  template <class T>
  static constexpr int Probe(Host<typename T::ProxyType> *,...) { return 1; }
     
  template <class T>
  static constexpr int Probe(Host<typename T::ProxyType> *,Host<typename T::OptType> *) { return 2; }
 };

/* struct ScanSwitch<T> */ 

template <class T> 
struct ScanSwitch 
 {
  enum RetType { Ret = ProbeSet_ScanSwitch::Probe<T>(0,0) };
 };
 
/* struct ScanOptAdapters<int Sw,T> */ 

template <class T> 
struct ScanOptAdapters<2,T>
 {
  typedef typename ScanProxy<T>::OptType ScanOptType;
 }; 
 
template <class T> 
struct ScanOptAdapters<1,T>
 {
 }; 
 
template <class T> 
struct ScanOptAdapters<0,T>
 {
 }; 
 
/* struct ScanAdapters<int Sw,T> */ 

template <class T> 
struct ScanAdapters<2,T>
 {
  typedef typename ScanProxy<T>::ProxyType ProxyType;
  
  typedef typename ScanProxy<T>::OptType OptType;
 
  template <class S>
  static void Scan(S &inp,const char *ptr,const char *lim,T &t)
   {
    OptType opt(ptr,lim);
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef(),opt);
   }
   
  template <class S>
  static void Scan(S &inp,const OptType &opt,T &t)
   {
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef(),opt);
   }
   
  template <class S>
  static void Scan(S &inp,T &t)
   {
    OptType opt;
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef(),opt);
   }
 };
 
template <class T> 
struct ScanAdapters<1,T>
 {
  typedef typename ScanProxy<T>::ProxyType ProxyType;
  
  template <class S>
  static void Scan(S &inp,const char *,const char *,T &t)
   {
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef());
   }
   
  template <class S,class OptType>
  static void Scan(S &inp,const OptType &,T &t)
   {
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef());
   }
   
  template <class S>
  static void Scan(S &inp,T &t)
   {
    ProxyType proxy(t);
    
    proxy.scan(inp.scanRef());
   }
 };
 
template <class T> 
struct ScanAdapters<0,T>
 {
 };
 
/* struct ScanOptAdapter<T> */ 

template <class T> 
struct ScanOptAdapter : ScanOptAdapters<ScanSwitch<ScanProxy<T> >::Ret,T> {};
 
/* struct ScanAdapter<T> */ 

template <class T> 
struct ScanAdapter : ScanAdapters<ScanSwitch<ScanProxy<T> >::Ret,T> {};

/* struct ScanDevBase */  

struct ScanDevBase : NoCopy
 {
  static const char OpenFormat  = '#' ;
  static const char CloseFormat = ';' ;
  
  static bool NotFound(char cur,char ch) { return cur && cur!=ch ;  }
  
  static const char * Find(const char *format,char ch);
  
  struct OptStr
   {
    const char *ptr;
    const char *lim;
    
    OptStr(NothingType) : ptr(0),lim(0) {}
    
    OptStr(const char *ptr_,const char *lim_) : ptr(ptr_),lim(lim_) {}
    
    template <class S,class T>
    void scan(S &inp,T &t) const
     {
      if( !ptr )
        {
         inp.fail();
        }
      else
        {
         ScanAdapter<T>::Scan(inp,ptr,lim,t);
        }
     }
    
    template <class S>
    void scan(S &inp) const
     {
      if( !ptr )
        {
         // do nothing
        }
      else
        {
         inp.fail();
        }
     }
   }; 
 };
 
/* class ScanfDev<S> */ 

template <class S> 
class ScanfDev : ScanDevBase
 {
   S inp;
   const char *format;
   
  private:
  
   void match(char ch);
   
   void match(const char *ptr,ulen len);
   
   OptStr find();
   
   // step_tuple
   
   void step_tuple(Tuple<> &) {}
 
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
     find().scan(inp,t);
    }
 
   template <class ... TT>
   void step(Tuple<TT...> &tuple)
    {
     step_tuple(tuple);
    }
   
   // print
 
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
   ScanfDev(T &&inp_,const char *format_) : inp(inp_),format(format_) {}
   
   ~ScanfDev() {}
   
   template <class ... TT>
   void operator () (TT & ... tt)
    {
     scan(tt...);
     
     if( *format ) find().scan(inp);
    }
 };

template <class S> 
void ScanfDev<S>::match(char ch)
 {
  if( ch==' ' )
    {
     SkipSpace(inp);
    }
  else
    {
     PassChars(inp,ch);
    }
 }

template <class S> 
void ScanfDev<S>::match(const char *ptr,ulen len)
 {
  for(char ch : Range(ptr,len) ) match(ch);
 }

template <class S> 
auto ScanfDev<S>::find() -> OptStr // ^aaaaaa##aaaaaaaaaaaa#opt;
 {
  for(;;)
    {
     const char *ptr=Find(format,OpenFormat);
        
     match(format,Dist(format,ptr));
        
     if( *ptr )                // ^##aaaaaaaaaaaa#opt;
       {
        ptr++;  
           
        if( *ptr==OpenFormat ) // ^#aaaaaaaaaaaa#opt;
          {
           match(OpenFormat);
              
           format=ptr+1;
              
           // continue;
          }
        else                   // ^opt;
          {
           const char *lim=Find(ptr,CloseFormat);
              
           if( *lim )
             {
              format=lim+1;
                 
              return OptStr(ptr,lim);
             }
           else // no ;
             {
              format=ptr;
                 
              return OptStr(ptr,ptr);
             }
          }
       }
     else // ^end-of-str
       {
        format=ptr;
           
        return Nothing;
       }
    }
 } 

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

/* struct BindScanOptType<OptType,T> */ 
 
template <class OptType,class T> 
struct BindScanOptType
 {
  const OptType &opt;
  T &t;
  
  BindScanOptType(const OptType &opt_,T &t_) : opt(opt_),t(t_) {}
  
  template <class S>
  void scan(S &inp)
   {
    ScanAdapter<T>::Scan(inp,opt,t);
   }
 };
 
/* BindScanOpt() */  

template <class OptType,class T> 
BindScanOptType<OptType,T> BindScanOpt(const OptType &opt,T &t) { return BindScanOptType<OptType,T>(opt,t); }
 
/* Scanf() */

template <class S,class ... TT>
void Scanf(S &&inp,const char *format,TT && ... tt) CCORE_NOINLINE ;

template <class S,class ... TT>
void Scanf(S &&inp,const char *format,TT && ... tt)
 {
  typedef typename ScanInpAdapter<typename std::remove_reference<S>::type>::ScanInpType SInp;
  
  ScanfDev<SInp> dev(inp,format);
  
  dev(tt...);
 }

/* Scanobj() */

template <class S,class ... TT>
void Scanobj(S &&inp,TT && ... tt) CCORE_NOINLINE ;

template <class S,class ... TT>
void Scanobj(S &&inp,TT && ... tt) 
 {
  typedef typename ScanInpAdapter<typename std::remove_reference<S>::type>::ScanInpType SInp;
  
  ScanobjDev<SInp> dev(inp);
  
  dev(tt...);
 }

} // namespace CCore
 
#endif
 

