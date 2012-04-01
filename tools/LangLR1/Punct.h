/* Punct.h */ 
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

#ifndef LangLR1_Punct_h
#define LangLR1_Punct_h

#include "Lang.h"

namespace App {

/* classes */

//enum AlphaIndex;

//enum VIndex;

class NTRIndex;

class Punct;

/* enum AlphaIndex */ 

enum AlphaIndex : ulen
 {
  AlphaIndexNull,  // "(Null)"
  AlphaIndexBegin, // "(Begin)"
  
  AlphaIndexFirst  // t(>=first) nt(>=first)
 };

typedef IndexRange<AlphaIndex> AlphaIndexRange;

/* enum VIndex */ 

enum VIndex : ulen
 {
  VIndexStart,  // "(Start)"
  VIndexFinish, // "(Finish)"
  
  VIndexFirst   // nt(>=first) white
 };

/* class NTRIndex */

class NTRIndex
 {
  public:
   
   enum Type
    {
     TypeN,
     TypeT,
     TypeR
    };
   
  private: 
  
   ulen index;
   Type type;
   
  public: 
   
   // constructors
  
   explicit NTRIndex(NIndex nt) : index(nt),type(TypeN) {}
  
   explicit NTRIndex(TIndex t=TIndexEnd) : index(t),type(TypeT) {}
  
   explicit NTRIndex(RIndex r) : index(r),type(TypeR) {}
   
   // methods
   
   Type getType() const { return type; }
  
   NIndex getNIndex() const { return NIndex(index); }
  
   TIndex getTIndex() const { return TIndex(index); }
  
   RIndex getRIndex() const { return RIndex(index); }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };

/* namespace PunctPrivate */

namespace PunctPrivate {

/* word DoWhite */

enum DoWhiteType { DoWhite };
  
/* classes */

//enum IndexClass;

class Index;

class Arrow;

class Diagram;

/* enum IndexClass */ 

enum IndexClass
 {
  IndexNull,        // 0
  
  IndexBegin,       // 0
  IndexEnd,         // 0
  
  IndexStart,       // 0
  IndexFinish,      // 0
  
  IndexShift,       // 0
  
  IndexTerminal,    // [0,...)
  IndexNonTerminal, // [0,...)
  IndexRule,        // [0,...)
  
  IndexWhite        // [0,...)
 };

/* class Index */  

class Index : public CmpComparable<Index>
 {
   ulen index;
   IndexClass cls;
   
   static ulen NextWhite;
   
  public:
   
   // constructors
  
   explicit Index(IndexClass cls_=IndexNull) : index(0),cls(cls_) {}
   
   explicit Index(DoWhiteType) : index(NextWhite++),cls(IndexWhite) {}
   
   explicit Index(NIndex nt) : index(nt),cls(IndexNonTerminal) {}
   
   explicit Index(TIndex t) : index(t),cls(IndexTerminal) {}
   
   explicit Index(RIndex r) : index(r),cls(IndexRule) {}
   
   explicit Index(NTIndex ntt)
    {
     if( ntt.isNIndex() )
       *this=Index(ntt.getNIndex());
     else
       *this=Index(ntt.getTIndex());
    }
   
   // methods
   
   IndexClass getClass() const { return cls; }
   
   ulen getIndex() const { return index; }
   
   bool hasClass(IndexClass cls_) const { return cls==cls_; }
   
   CmpResult objCmp(const Index &obj) const
    {
     return AlphaCmp(cls,obj.cls,index,obj.index);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* class Arrow */ 

class Arrow : public CmpComparable<Arrow>
 {
   Index src;
   Index dst;
   Index alpha;
   
   DynArray<Index> beta;
   
  private:
   
   void fill(PtrLen<const NTIndex> str,RIndex rule);
   
  public:
   
   // constructors
  
   explicit Arrow(ToMoveCtor<Arrow> obj)
    : src(obj->src),dst(obj->dst),alpha(obj->alpha),beta(ObjToMove(obj->beta))
    {
    }
   
   Arrow(Index src_,Index dst_,Index alpha_)
    : src(src_),dst(dst_),alpha(alpha_) 
    {
    }
    
   Arrow(Index src_,Index dst_,Index alpha_,Index beta1)
    : src(src_),dst(dst_),alpha(alpha_),beta{beta1} 
    {
    }
    
   Arrow(Index src_,Index dst_,Index alpha_,Index beta1,Index beta2)
    : src(src_),dst(dst_),alpha(alpha_),beta{beta1,beta2} 
    {
    }
    
   Arrow(Index src_,Index dst_,Index alpha_,PtrLen<const NTIndex> str,RIndex rule)
    : src(src_),dst(dst_),alpha(alpha_),beta(str.len+1) 
    { 
     fill(str,rule); 
    }
   
   ~Arrow() {}
   
   // methods
    
   Index getSrc() const { return src; } 
   
   Index getDst() const { return dst; }
   
   Index getAlpha() const { return alpha; }
   
   PtrLen<const Index> getBeta() const { return Range_const(beta); }
   
   CmpResult objCmp(const Arrow &obj) const
    {
     return AlphaCmp(alpha,obj.alpha,dst,obj.dst,src,obj.src);
    }
   
   // move objects
   
   Arrow * objMove(Place<void> place)
    {
     return CtorMove(this,place);
    }
   
   // no-throw flags
   
   enum NoThrowFlagType
    {
     Default_no_throw = true,
     Copy_no_throw = true
    };
 };
 
/* class Diagram */  

class Diagram : NoCopy
 {
   const Lang &lang;
  
   DynArray<Arrow> list;
   DynArray<const Arrow *> ptr_list;
   
  private: 
   
   void add(Index src,Index dst,Index alpha) 
    { 
     list.append_fill(src,dst,alpha); 
    }
    
   void add(Index src,Index dst,Index alpha,Index beta1) 
    { 
     list.append_fill(src,dst,alpha,beta1); 
    }
    
   void add(Index src,Index dst,Index alpha,Index beta1,Index beta2) 
    { 
     list.append_fill(src,dst,alpha,beta1,beta2); 
    }
    
   void add(Index src,Index dst,Index alpha,PtrLen<const NTIndex> str,RIndex rule) 
    { 
     list.append_fill(src,dst,alpha,str,rule); 
    }
   
   void add(Index vertex,PtrLen<const NTIndex> str,RIndex rule);
   
   void addStart(NIndex nt);
   
   void add(NIndex nt);
   
   void complete();
   
  public:
  
   explicit Diagram(const Lang &lang);
   
   ~Diagram() {}
   
   PtrLen<const Arrow *const> getList() const { return Range_const(ptr_list); }
 };
 
} // namespace PunctPrivate

/* class Punct */

class Punct : NoCopy
 {
  public:
  
   struct Rec
    {
     VIndex src;
     VIndex dst;
    
     DynArray<DynArray<NTRIndex> > expr;
    
     Rec(VIndex src_,VIndex dst_,ulen len) : src(src_),dst(dst_),expr(DoFill(1),len) {}
     
     explicit Rec(ToMoveCtor<Rec> obj)
      : src(obj->src),
        dst(obj->dst),
        expr(ObjToMove(obj->expr))
      {
      }
     
     // move objects
     
     Rec * objMove(Place<void> place)
      {
       return CtorMove(this,place);
      }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
  
  private:
  
   const Lang &lang;

   ulen alphaLim;
   
   DynArray<DynArray<Rec> > data;
   
  private:
   
   AlphaIndex toAlpha(PunctPrivate::Index ind) const;
   
   VIndex toVertex(PunctPrivate::Index ind) const;
   
   NTRIndex toNTR(PunctPrivate::Index ind) const;
   
   DynArray<Rec> * start(PunctPrivate::Index ind);
   
   void init(PtrLen<NTRIndex> out,const PunctPrivate::Index *beta);
   
   Rec * ext(DynArray<Rec> *cur,Rec *last,const PunctPrivate::Arrow *arrow); 
   
  public:
   
   explicit Punct(const Lang &lang);
   
   ~Punct();
   
   // methods
   
   const Lang & getLang() const { return lang; }
   
   ulen getAlphaIndexLim() const { return alphaLim ; }
   
   AlphaIndexRange getAlphaRange() const { return AlphaIndexRange(getAlphaIndexLim()); }
   
   AlphaIndexRange getAlphaRange(AlphaIndex first) const { return AlphaIndexRange(first,getAlphaIndexLim()); }
   
   PtrLen<const Rec> getData(AlphaIndex a) const { return Range(data[a]); }
   
   // from lang
   
   StrLen getTextDesc(NIndex nt) const { return lang.getTextDesc(nt); }
   
   StrLen getTextDesc(TIndex t) const { return lang.getTextDesc(t); }
   
   StrLen getTextDesc(RIndex r) const { return lang.getTextDesc(r); }
   
   // AlphaIndex names
   
   StrLen getTextDesc(AlphaIndex a) const;
   
   // VIndex names
   
   class PrintVIndex
    {
      StrLen name;
      ulen ind;
      
     public: 
     
      PrintVIndex(StrLen name_) : name(name_),ind(0) {}
     
      PrintVIndex(StrLen name_,ulen ind_) : name(name_),ind(ind_) {}
     
      template <class P>
      void print(P &out) const
       {
        Putobj(out,name);
       
        if( ind ) Putobj(out,ind);
       }
    };
   
   PrintVIndex getTextDesc(VIndex v) const;
   
   // print string
   
   template <class I>
   class PrintStr
    {
      const Punct &punct;
      PtrLen<I> str;
     
     public:
      
      PrintStr(const Punct &punct_,PtrLen<I> str_) : punct(punct_),str(str_) {}
     
      template <class P>
      void print(P &out) const
       {
        auto p=str;
       
        if( +p )
          {
           Putobj(out,"( ",punct.getTextDesc(*p));
          
           for(++p; +p ;++p) Putobj(out," , ",punct.getTextDesc(*p));
          
           Putobj(out," )");
          }
        else
          {
           Putobj(out,"( )");
          }
       }
    };

   template <class I>
   PrintStr<I> printStr(PtrLen<I> str) const { return PrintStr<I>(*this,str); } 
 };

} // namespace App

#endif


