/* LangEstimate.h */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CondLangLR1_process_LangEstimate_h
#define CondLangLR1_process_LangEstimate_h

#include "lang/Lang.h"

namespace App {

/* classes */

template <class Estimate,class Context=EmptyContext> class LangEstimate;

/* class LangEstimate<Estimate,Context> */

template <class Estimate,class Context> 
class LangEstimate : NoCopy
 {
   DynArray<Estimate> buf;
   
   Context ctx;
   
  private: 

   bool step(Synt synt);
   
   bool step(const Lang &lang);
   
  public:
  
   template <class ... TT>
   explicit LangEstimate(const Lang &lang,TT && ... tt);
   
   ~LangEstimate();
   
   const Estimate & operator [] (Synt synt) const { return buf[synt.getIndex()]; }
   
   Estimate operator () (PtrLen<const Element> str) const;
 };

template <class Estimate,class Context> 
bool LangEstimate<Estimate,Context>::step(Synt synt)
 {
  typename Estimate::Accumulator est;
  
  synt.apply( [&] (Rule rule) { est+=(*this)(rule.getArgs()); } );
  
  return buf[synt.getIndex()].setCmp(est);
 }

template <class Estimate,class Context> 
bool LangEstimate<Estimate,Context>::step(const Lang &lang)
 {
  bool ret=false;
  
  lang.applyForSynts( [&] (Synt synt) { ret|=this->step(synt); } );
  
  return ret;
 }

template <class Estimate,class Context>
template <class ... TT>
LangEstimate<Estimate,Context>::LangEstimate(const Lang &lang,TT && ... tt)
 : buf(DoFill(lang.getSyntCount()),ElementNull),
   ctx( std::forward<TT>(tt)... )
 {
  TrackStep track; 
  
  while( step(lang) ) track.step();
  
  track.finish();
 }

template <class Estimate,class Context> 
LangEstimate<Estimate,Context>::~LangEstimate()
 {
 }

template <class Estimate,class Context> 
Estimate LangEstimate<Estimate,Context>::operator () (PtrLen<const Element> str) const
 {
  Estimate ret(ElementOne);
  
  for(Element e : str )
    {
     e.apply( [&] (Atom atom) { ret=ret*Estimate(atom,ctx); } , 
              [&] (Synt synt) { ret=ret*buf[synt.getIndex()]; } );
    }
  
  return ret;
 }

} // namespace App

#endif

