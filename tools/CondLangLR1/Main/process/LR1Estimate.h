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

class LR1Context;

class LR1MapContext;

class LR1Estimate;

/* class LR1Context */

class LR1Context
 {
   ulen atom_count;
   
  public: 
  
   explicit LR1Context(const ExtLang &lang) : atom_count(lang.getOriginalAtomCount()) {}
  
   bool isRule(Atom atom) const
    {
     return atom.getIndex()>=atom_count;
    }
 };

/* class LR1MapContext */

class LR1MapContext
 {
   LangMap map;
   ulen atom_count;
   
  public: 
  
   explicit LR1MapContext(const ExtLang &lang) : map(lang),atom_count(lang.getOriginalAtomCount()) {}
   
   Atom operator () (Atom atom) const { return map(atom); }
  
   bool isRule(Atom atom) const
    {
     return atom.getIndex()>=atom_count;
    }
 };

/* class LR1Estimate */

class LR1Estimate : public CmpComparable<LR1Estimate> , public NoThrowFlagsBase
 {
  public:
  
   using RuleSet = Set<Atom,SimpleJoiner> ;
   
   static bool HasConflict(bool shift,const RuleSet &rules) { return rules.getLen()>1u-shift; }
   
   static RuleSet GetConflictSet(bool shift,const RuleSet &rules)
    {
     if( shift || rules.getLen()>1 ) return rules;
     
     return RuleSet(); 
    }
   
   struct ExtRuleSet : NoThrowFlagsBase
    {
     bool shift;
     RuleSet rules;
     
     // constructors
     
     ExtRuleSet() : shift(true) {}
     
     ExtRuleSet(const RuleSet &rules_) : shift(false),rules(rules_) {}
     
     ExtRuleSet(bool shift_,const RuleSet &rules_) : shift(shift_),rules(rules_) {}
     
     // properties

     bool hasConflict() const { return HasConflict(shift,rules); }
     
     RuleSet getConflictSet() const { return GetConflictSet(shift,rules); }
     
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
     
     struct PrintOptType
      {
       bool flag;
       
       void setDefault() { flag=false; }
       
       PrintOptType() { setDefault(); }
       
       PrintOptType(const char *ptr,const char *lim);
       
       //
       // [.s]
       //
      };
     
     template <class P>
     void print(P &out,PrintOptType opt) const
      {
       if( shift ) 
         {
          if( opt.flag )
            Putobj(out,"STOP");
          else
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
      
      CrossBuilder(const RecSet &beta_,const RuleSet &alpha_) : beta(Range(beta_)),alpha(alpha_) {}
      
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
   
   LR1Estimate(Atom atom,LR1Context ctx)
    {
     empty=false;
     null=false;
     
     if( ctx.isRule(atom) )
       {
        alpha=RuleSet(atom);
       }
     else
       {
        beta=RecSet( Rec(atom,ExtRuleSet()) );
       }
    }
   
   LR1Estimate(Atom atom,LR1MapContext ctx)
    {
     empty=false;
     null=false;
     
     atom=ctx(atom);
     
     if( ctx.isRule(atom) )
       {
        alpha=RuleSet(atom);
       }
     else
       {
        beta=RecSet( Rec(atom,ExtRuleSet()) );
       }
    }
   
   // methods
   
   bool operator + () const { return !empty; }
   
   bool operator ! () const { return empty; }
   
   bool setCmp(const LR1Estimate &obj) { return SetCmp(*this,obj); }
   
   // properties
   
   bool isStrong() const { return !null && alpha.isEmpty() ; }
   
   bool hasConflict() const
    {
     if( HasConflict(null,alpha) ) return true;
     
     for(auto &rec : Range(beta) ) if( rec.object.hasConflict() ) return true;
     
     return false;
    }
   
   bool isEmpty() const { return empty; }
   
   bool hasNull() const { return null; }
   
   RuleSet getAlpha() const { return alpha; }
   
   RecSet getBeta() const { return beta; }
   
   RuleSet getConflictSet() const
    {
     RuleSet::Accumulator acc;
     
     acc+=GetConflictSet(null,alpha);
     
     for(auto &rec : Range(beta) ) acc+=rec.object.getConflictSet();
     
     return acc;
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
   
   using PrintOptType = BlockPrintOpt ;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     if( empty )
       {
        Putobj(out,"EMPTY");
        
        if( opt.flag ) Putch(out,'\n');
       }
     else if( opt.flag )
       {
        if( hasConflict() ) Putobj(out,"CONFLICT");
        
        Putch(out,'\n');
        
        if( null || alpha.nonEmpty() )
          {
           ExtRuleSet object(null,alpha);
          
           if( object.hasConflict() )
             Printf(out,"\n  (End) : #.s;  CONFLICT\n",object);
           else
             Printf(out,"\n  (End) : #.s;\n",object);
          }
        
        for(auto &rec : Range(beta) )
          {
           if( rec.object.hasConflict() )
             Printf(out,"\n  #;  CONFLICT\n",rec);
           else
             Printf(out,"\n  #;\n",rec);
          }
       }
     else
       {
        if( hasConflict() ) Putobj(out,"CONFLICT ");
        
        if( null || alpha.nonEmpty() )
          {
           Printf(out," (End) : #.s;",ExtRuleSet(null,alpha));
           
           if( beta.nonEmpty() ) Printf(out," #;",beta);
          }
        else
          {
           Putobj(out,beta);
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

