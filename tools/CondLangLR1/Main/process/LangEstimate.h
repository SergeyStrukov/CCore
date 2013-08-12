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

template <class Estimate> class LangEstimate;

/* class LangEstimate<Estimate> */

template <class Estimate> 
class LangEstimate : NoCopy
 {
   DynArray<Estimate> buf;
   
   using Context = typename Estimate::Context ;
   
   Context ctx;
   
  private: 

   bool step(Synt synt);
   
   bool step(const Lang &lang);
   
  public:
  
   LangEstimate(const Lang &lang,const Context &ctx);
   
   ~LangEstimate();
   
   const Estimate & operator [] (Synt synt) const { return buf[synt.getIndex()]; }
   
   Estimate operator () (PtrLen<const Element> str) const;
 };

template <class Estimate> 
bool LangEstimate<Estimate>::step(Synt synt)
 {
  typename Estimate::Accumulator est;
  
  synt.apply( [&] (Rule rule) { est+=(*this)(rule.getArgs()); } );
  
  return buf[synt.getIndex()].setCmp(est);
 }

template <class Estimate> 
bool LangEstimate<Estimate>::step(const Lang &lang)
 {
  bool ret=false;
  
  lang.applyForSynts( [&] (Synt synt) { ret|=this->step(synt); } );
  
  return ret;
 }

template <class Estimate> 
LangEstimate<Estimate>::LangEstimate(const Lang &lang,const Context &ctx_)
 : buf(DoFill(lang.getSyntCount()),ElementNull),
   ctx(ctx_)
 {
  TrackStep track; 
  
  while( step(lang) ) track.step();
  
  track.finish();
 }

template <class Estimate> 
LangEstimate<Estimate>::~LangEstimate()
 {
 }

template <class Estimate> 
Estimate LangEstimate<Estimate>::operator () (PtrLen<const Element> str) const
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

