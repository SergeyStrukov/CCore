/* LR1Estimate.h */
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

#ifndef CondLangLR1_process_LR1Estimate_h
#define CondLangLR1_process_LR1Estimate_h

#include "lang/Lang.h"
#include "Set.h"

namespace App {

/* classes */

class LR1Estimate;

/* class LR1Estimate */

class LR1Estimate : public CmpComparable<LR1Estimate> , public NoThrowFlagsBase
 {
  public:
  
   using RuleSet = Set<Atom,SimpleJoiner> ;
   
   struct ExtRuleSet : NoThrowFlagsBase
    {
     bool shift;
     RuleSet rules;
     
     // constructors
     
     ExtRuleSet() : shift(true) {}
     
     ExtRuleSet(const RuleSet &rules_) : shift(false),rules(rules_) {}
     
     ExtRuleSet(bool shift_,const RuleSet &rules_) : shift(shift_),rules(rules_) {}
     
     // properties

     bool hasConflict() const { return rules.getLen()>1u-shift; }
     
     // cmp objects
     
     CmpResult objCmp(const ExtRuleSet &obj) const
      {
       return AlphaCmp(shift,obj.shift,rules,obj.rules);
      }
     
     // operators
     
     friend ExtRuleSet operator + (const ExtRuleSet &a,const ExtRuleSet &b)
      {
       return ExtRuleSet( a.shift|b.shift , a.rules+b.rules );
      }

     // print object
     
     template <class P>
     void print(P &out) const
      {
       if( shift ) 
         {
          Putobj(out,"<-");
          
          if( rules.nonEmpty() ) Printf(out," #;",rules);
         }
       else
         {
          Putobj(out,rules);
         }
      }
    };
   
   using Rec = IndexPair<Atom,ExtRuleSet> ;
   
   using RecSet = Set<Rec,Joiner> ;
   
   class CrossBuilder
    {
      PtrLen<const Rec> beta;
      RuleSet alpha;
      
     public:
      
      CrossBuilder(const RecSet &beta_,const RuleSet &alpha_) : beta(beta_.read()),alpha(alpha_) {}
      
      ulen getLen() const { return beta.len; }
      
      PtrLen<Rec> operator () (Place<void> place)
       {
        typename ArrayAlgo<Rec>::CreateGuard_nothrow guard(place,getLen());
        
        for(auto p=beta; +p ;++p,++guard) new(guard.at()) Rec(p->index,alpha); 
        
        return guard.disarm();
       }
    };
  
  private:
  
   bool empty;
   bool null;
   RuleSet alpha;
   RecSet beta;
  
  private: 
   
   LR1Estimate(bool empty_,bool null_,const RuleSet &alpha_,const RecSet &beta_) 
    : empty(empty_),null(null_),alpha(alpha_),beta(beta_) {}
   
   LR1Estimate(const LR1Estimate &a,const LR1Estimate &b)
    : empty(false),
      null(a.null&b.null)
    {
     // alpha
     
     if( a.null ) alpha=b.alpha;
        
     if( b.null || b.alpha.nonEmpty() ) alpha=alpha+a.alpha;
     
     // beta
     
     if( a.null ) 
       {
        beta=a.beta+b.beta;
       }
     else
       {
        beta=a.beta;
       }
        
     if( a.alpha.nonEmpty() )
       {
        beta=beta+RecSet(DoBuild,CrossBuilder(b.beta,a.alpha));
       }
    }
   
  public:
   
   // constructors
  
   LR1Estimate()
    {
     empty=true;
     null=false;
    }
   
   LR1Estimate(ElementNullType) : LR1Estimate() {}
   
   LR1Estimate(ElementOneType)
    {
     empty=false;
     null=true;
    }
   
   using Context = ulen ;
   
   LR1Estimate(Atom atom,ulen atom_count)
    {
     empty=false;
     null=false;
     
     if( atom.getIndex()<atom_count )
       {
        beta=RecSet( Rec(atom,ExtRuleSet()) );
       }
     else
       {
        alpha=RuleSet(atom);
       }
    }
   
   // methods
   
   bool operator + () const { return !empty; }
   
   bool operator ! () const { return empty; }
   
   bool setCmp(const LR1Estimate &obj) { return SetCmp(*this,obj); }
   
   // properties
   
   bool isStrong() const { return !null && alpha.isEmpty() ; }
   
   bool hasEndConflict() const { return alpha.getLen()>1u-null; }
   
   bool hasConflict() const
    {
     if( hasEndConflict() ) return true;
     
     for(auto &rec : beta.read() ) if( rec.object.hasConflict() ) return true;
     
     return false;
    }
   
   // cmp objects
   
   CmpResult objCmp(const LR1Estimate &obj) const
    {
     return AlphaCmp(empty,obj.empty,null,obj.null,alpha,obj.alpha,beta,obj.beta);
    }
   
   // operations
   
   friend LR1Estimate operator + (const LR1Estimate &a,const LR1Estimate &b)
    {
     return LR1Estimate( a.empty&b.empty , a.null|b.null , a.alpha+b.alpha , a.beta+b.beta );   
    }
   
   friend LR1Estimate operator * (const LR1Estimate &a,const LR1Estimate &b)
    {
     if( a.empty || b.empty ) return LR1Estimate();
     
     if( a.isStrong() ) return a;
    
     return LR1Estimate(a,b);
    }

   class Accumulator;
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     if( empty )
       {
        Putobj(out,"EMPTY");
       }
     else
       {
        if( hasConflict() ) Putobj(out,"CONFLICT ");
        
        if( null ) 
          {
           if( alpha.nonEmpty() ) 
             Printf(out," (End) : STOP #;",alpha);
           else
             Putobj(out," (End) : STOP");
           
           if( beta.nonEmpty() ) Printf(out," #;",beta);
          }
        else
          {
           if( alpha.nonEmpty() ) 
             {
              Printf(out,"(End) : #;",alpha);
              
              if( beta.nonEmpty() ) Printf(out," #;",beta);
             }
           else
             {
              Putobj(out,beta);
             }
          }
       }
    }
   
   template <class P>
   void printBlock(P &out,ulen index) const
    {
     if( empty )
       {
        Printf(out,"#;) EMPTY\n",index);
       }
     else
       {
        Printf(out,"#;)",index);
        
        if( hasConflict() ) Putobj(out," CONFLICT");
        
        Putch(out,'\n');
        
        if( null ) 
          {
           if( alpha.nonEmpty() ) 
             Printf(out,"\n  (End) : STOP #;",alpha);
           else
             Putobj(out,"\n  (End) : STOP");
           
           if( hasEndConflict() )
             Putobj(out,"CONFLICT\n");
           else
             Putch(out,'\n');
          }
        else
          {
           if( alpha.nonEmpty() ) 
             {
              Printf(out,"\n  (End) : #;",alpha);
              
              if( hasEndConflict() )
                Putobj(out,"CONFLICT\n");
              else
                Putch(out,'\n');
             }
          }
        
        for(auto &rec : beta.read() )
          {
           if( rec.object.hasConflict() )
             Printf(out,"\n  #; : #;  CONFLICT\n",rec.index,rec.object);
           else
             Printf(out,"\n  #; : #;\n",rec.index,rec.object);
          }
       }
    }
 };

class LR1Estimate::Accumulator : NoCopy
 {
   bool empty;
   bool null;
   RuleSet::Accumulator alpha;
   RecSet::Accumulator beta;
   
  public:
 
   Accumulator() 
    {
     empty=true;
     null=false;
    }
   
   void operator += (LR1Estimate obj) 
    { 
     empty&=obj.empty;
     null|=obj.null;
     alpha+=obj.alpha;
     beta+=obj.beta;
    }

   operator LR1Estimate() { return LR1Estimate(empty,null,alpha,beta); } 
 };

} // namespace App

#endif

