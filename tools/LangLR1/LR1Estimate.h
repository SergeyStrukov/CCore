/* LR1Estimate.h */ 
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

#ifndef LangLR1_LR1Estimate_h
#define LangLR1_LR1Estimate_h

#include "Set.h"

namespace App {

/* classes */

template <class T,class R,R RNull> class LR1;

/* class LR1<T,R,R RNull> */ 

template <class T,class R,R RNull>
class LR1 : public CmpComparable<LR1<T,R,RNull> >
 {
  public:
 
   typedef Set<R,SimpleJoiner> AlphaSet;
   
   typedef IndexPair<T,AlphaSet> Rec;
    
   typedef Set<Rec,Joiner> BetaSet;
   
  private: 

   bool empty;
   bool null;
   AlphaSet alpha;
   BetaSet beta;
   
  private: 
   
   LR1(bool empty_,bool null_,const AlphaSet &alpha_,const BetaSet &beta_) : empty(empty_),null(null_),alpha(alpha_),beta(beta_) {}
    
   LR1(const LR1<T,R,RNull> &a,const LR1<T,R,RNull> &b); 
    
  public:
   
   // constructors

   explicit LR1(bool null_=false) 
    { 
     empty=!null_; 
     null=null_; 
    }

   explicit LR1(T a) 
    : beta(Rec(a,AlphaSet(RNull)))
    {
     empty=false;
     null=false;
    }
    
   explicit LR1(R r) 
    : alpha(r)
    {
     empty=false;
     null=false;
    }
   
   ~LR1() {}
   
   // methods
   
   bool getEmpty() const { return empty; }
   
   bool getNull() const { return null; }
   
   const AlphaSet & getAlpha() const { return alpha; }
    
   const BetaSet & getBeta() const { return beta; } 
    
   bool set(const LR1<T,R,RNull> &obj)
    {
     bool ret=false;
     
     if( SetCmp(empty,obj.empty) ) ret=true;
     if( SetCmp(null,obj.null) ) ret=true;
     if( SetCmp(alpha,obj.alpha) ) ret=true;
     if( SetCmp(beta,obj.beta) ) ret=true;
     
     return ret;
    }
    
   bool isStrong() const { return !empty && !null && alpha.isEmpty() ; }

   CmpResult objCmp(const LR1<T,R,RNull> &obj) const
    {
     return AlphaCmp(empty,obj.empty,null,obj.null,alpha,obj.alpha,beta,obj.beta);
    }
   
   // operators

   friend LR1<T,R,RNull> operator + (const LR1<T,R,RNull> &a,const LR1<T,R,RNull> &b)
    {
     return LR1<T,R,RNull>( a.empty && b.empty , a.null || b.null , a.alpha+b.alpha , a.beta+b.beta );   
    }

   friend LR1<T,R,RNull> operator * (const LR1<T,R,RNull> &a,const LR1<T,R,RNull> &b)
    {
     if( a.isStrong() )
       {
        if( b.empty ) return LR1<T,R,RNull>();
        
        return a;
       }
    
     return LR1<T,R,RNull>(a,b);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = NoThrowFlags<AlphaSet>::Default_no_throw && NoThrowFlags<BetaSet>::Default_no_throw ,
     Copy_no_throw = NoThrowFlags<AlphaSet>::Copy_no_throw && NoThrowFlags<BetaSet>::Copy_no_throw
    };
 };

template <class T,class R,R RNull>
LR1<T,R,RNull>::LR1(const LR1<T,R,RNull> &a,const LR1<T,R,RNull> &b)
 : empty( a.empty || b.empty ),
   null( a.null && b.null )
 {
  if( a.null ) alpha=b.alpha;
     
  if( b.null || b.alpha.nonEmpty() ) alpha=alpha+a.alpha;
     
  if( a.null ) beta=b.beta;
     
  if( !b.empty ) beta=beta+a.beta;
     
  if( a.alpha.nonEmpty() )
    {
     BetaSet cross(b.beta);
     
     for(auto p=cross.write(); +p ;++p) p->object=a.alpha;
        
     beta=beta+cross;
    }
 }
 
} // namespace App

#endif




