/* ScanProxy.h */ 
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

#ifndef CCore_inc_ScanProxy_h
#define CCore_inc_ScanProxy_h

#include <CCore/inc/scanf/IntScan.h>
#include <CCore/inc/scanf/StringScan.h>
 
namespace CCore {

/* classes */

template <class UInt> struct UIntScanProxy;

template <class SInt> struct SIntScanProxy;

template <class T> struct ScanProxy_other;

template <bool is_UInt,bool is_SInt,class T> struct ScanProxies_noclass;

template <class T> struct ScanProxy_noclass;

struct ProbeSet_ScanOptType;

template <class T> struct Has_ScanOptType;

struct ProbeSet_ScanProxyType;

template <class T> struct Has_ScanProxyType;

template <bool has_ScanOptType,class T> struct ScanProxies_class_noproxy;

template <bool has_ScanProxyType,class T> struct ScanProxies_class;

template <bool is_class,class T> struct ScanProxies;

template <class T> struct ScanProxy;

template <class T,class ProxySet> struct ScanProxySet;

/* struct UIntScanProxy<UInt> */  

template <class UInt>
struct UIntScanProxy
 {
  typedef IntScanOpt OptType;
  typedef UIntScan<UInt> ProxyType;
 };
 
/* struct SIntScanProxy<SInt> */  
 
template <class SInt>
struct SIntScanProxy
 {
  typedef IntScanOpt OptType;
  typedef SIntScan<SInt> ProxyType;
 };

/* struct ScanProxy_other<T> */

template <class T> 
struct ScanProxy_other
 {
 };

/* struct ScanProxies_noclass<bool is_UInt,bool is_SInt,T> */

template <class T> 
struct ScanProxies_noclass<true,false,T> : UIntScanProxy<T> {};

template <class T> 
struct ScanProxies_noclass<false,true,T> : SIntScanProxy<T> {};

template <class T>
struct ScanProxies_noclass<false,false,T> : ScanProxy_other<T> {};

/* struct ScanProxy_noclass<T> */ 

template <class T> 
struct ScanProxy_noclass : ScanProxies_noclass<Meta::IsUInt<T>::Ret,Meta::IsSInt<T>::Ret,T> {}; 
 
/* struct ProbeSet_ScanOptType */

struct ProbeSet_ScanOptType
 {
  template <class T> struct Host;
  
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<typename T::ScanOptType> *) { return true; }
 };

/* struct Has_ScanOptType<T> */ 

template <class T> 
struct Has_ScanOptType : Meta::Has<T,ProbeSet_ScanOptType> {};

/* struct ProbeSet_ScanProxyType */

struct ProbeSet_ScanProxyType
 {
  template <class T> struct Host;
  
  template <class T>
  static constexpr bool Probe(...) { return false; }
  
  template <class T>
  static constexpr bool Probe(Host<typename T::ScanProxyType> *) { return true; }
 };

/* struct Has_ScanProxyType<T> */ 

template <class T> 
struct Has_ScanProxyType : Meta::Has<T,ProbeSet_ScanProxyType> {};
 
/* struct ScanProxies_class_noproxy<bool has_ScanOptType,T> */ 

template <class T> 
struct ScanProxies_class_noproxy<true,T>
 {
  typedef typename T::ScanOptType OptType;
  
  typedef T & ProxyType;
 };
 
template <class T> 
struct ScanProxies_class_noproxy<false,T>
 {
  typedef T & ProxyType;
 };
 
/* struct ScanProxies_class<bool has_ScanProxyType,T> */ 

template <class T> 
struct ScanProxies_class<true,T> : ScanProxy<typename T::ScanProxyType> {};
 
template <class T> 
struct ScanProxies_class<false,T> : ScanProxies_class_noproxy<Has_ScanOptType<T>::Ret,T> {};
 
/* struct ScanProxies<bool is_class,T> */ 

template <class T> 
struct ScanProxies<true,T> : ScanProxies_class<Has_ScanProxyType<T>::Ret,T> {};
 
template <class T> 
struct ScanProxies<false,T> : ScanProxy_noclass<T> {};
 
/* struct ScanProxy<T> */ 

template <class T> 
struct ScanProxy : ScanProxies<std::is_class<T>::value,T> {};

template <>
struct ScanProxy<String>
 {
  typedef StringScanOpt OptType;
  typedef StringScan ProxyType;
 };

/* struct ScanProxySet<T,ProxySet> */

template <class T,class ProxySet>
struct ScanProxySet
 {
  struct ProxyType
   {
    T &ret;
    
    explicit ProxyType(T &ret_) : ret(ret_) {}
    
    template <class S>
    void scan(S &inp)
     {
      ProxySet set;
      
      Scanobj(inp,set);
      
      set.map(ret);
     }
   };
 };

} // namespace CCore
 
#endif
 

