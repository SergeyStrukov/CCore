/* Estimator.h */
//----------------------------------------------------------------------------------------
//
//  Project: LangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2004, 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef LangLR1_Estimator_h
#define LangLR1_Estimator_h

#include "Punct.h"

namespace App {

/* classes */

template <class T> class Estimator;

/* class Estimator<T> */

template <class T> 
class Estimator : NoCopy
 {
   const Lang &lang;
  
   DynArray<T> tableN;
   DynArray<T> tableT;
   DynArray<T> tableR;
   
  private: 
   
   T mul(RuleRecord rec) const;
   
   bool step(NIndex nt);
   
   bool step();
  
  public:
   
   explicit Estimator(const Lang &lang);

   ~Estimator() {}
   
   const T & get(NIndex nt) const { return tableN[nt]; }
   
   const T & get(TIndex t) const { return tableT[t]; }

   const T & get(RIndex r) const { return tableR[r]; }
   
   const T & get(NTIndex ntt) const { return ntt.isNIndex()?tableN[ntt.getNIndex()]:tableT[ntt.getTIndex()]; }
   
   const T & get(NTRIndex ntr) const
    {
     switch( ntr.getType() )
       {
        default: // unreachable
        
        case NTRIndex::TypeN : return get(ntr.getNIndex());
        
        case NTRIndex::TypeT : return get(ntr.getTIndex());
        
        case NTRIndex::TypeR : return get(ntr.getRIndex());
       }
    }
 };

template <class T> 
T Estimator<T>::mul(RuleRecord rec) const
 {
  auto p=rec.str;
  
  if( +p )
    {
     T result=get(*p);
     
     for(++p; +p ;++p) result=result*get(*p);
     
     return result*tableR[rec.rule];
    }
  else
    {
     return tableR[rec.rule];
    }
 }

template <class T> 
bool Estimator<T>::step(NIndex nt)
 {
  auto p=lang.getRules(nt);
  
  if( +p )
    {
     T result=mul(*p);
     
     for(++p; +p ;++p) result=result+mul(*p);

     return tableN[nt].set(result);
    }
  else
    {
     T result;
     
     return tableN[nt].set(result);
    }
 }

template <class T> 
bool Estimator<T>::step()
 {
  bool ret=false;

  for(auto p=lang.getNRange(); +p ;++p) if( step(*p) ) ret=true;
  
  return ret;
 }

template <class T> 
Estimator<T>::Estimator(const Lang &lang_)
 : lang(lang_),
   tableN(lang.getNIndexLim()),
   tableT(lang.getTIndexLim()),
   tableR(lang.getRIndexLim())
 {
  for(auto p=lang.getTRange(); +p ;++p) tableT[*p]=T(*p);

  for(auto p=lang.getRRange(RIndexFirst); +p ;++p) tableR[*p]=T(*p);

  while( step() );
 }

} // namespace App

#endif

