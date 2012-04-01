/* Punct.cpp */ 
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

#include "Punct.h"

namespace App {

/* namespace PunctPrivate */

namespace PunctPrivate {
  
/* class Index */

ulen Index::NextWhite=0;

/* class Arrow */

void Arrow::fill(PtrLen<const NTIndex> str,RIndex rule)
 {
  auto out=beta.getPtr();
  
  for(; +str ;++str,++out) *out=Index(*str); 
  
  *out=Index(rule);
 }

/* class Diagram */  

void Diagram::addStart(NIndex nt)
 {
  Index begin(IndexBegin);
  Index end(IndexEnd);
  Index start(IndexStart);
  Index finish(IndexFinish);
  
  Index white(DoWhite);
  Index a(nt);
     
  add(start,finish,begin,a,end);            // Start -> Finish : (Begin, (n,End) )
                                            //
                                            //
  add(start,a,begin,end);                   // Start -> V(n)   : (Begin, (End) )
  add(start,white,begin);                   // Start -> ?      : (Begin, () )
  add(white,finish,a,end);                  // ?     -> Finish : (n, (End) )
 }
   
void Diagram::add(Index vertex,PtrLen<const NTIndex> str,RIndex rule)
 {
  if( !str.len ) return;
  
  Index null(IndexNull);
  Index finish(IndexFinish);
  
                                            // vertex = V(n)
                                            // (str,rule) = (a1,a2,...,ak,r) , k>=1
                                            //
  Index a(*str);                            // a = a1
                                            //
  ++str;                                    // (str,rule) = (a2,...,ak,r)
                                            //
  if( a.hasClass(IndexNonTerminal) )        // a == n'
    add(vertex,a,null,str,rule);            // V(n) -> V(n') : (, (a2,...,ak,r) )
                                            //
  for(;;)                                   // i=1,...,k
    {                                       // vertex = ? or V(n) if( i==1 )
                                            // a = ai
                                            // (str,rule) = (a(i+1),...,ak,r)
                                            //
     add(vertex,finish,a,str,rule);         // vertex -> Finish : (ai, (a(i+1),...,ak,r) )
                                            //
     if( !str ) break;                      //
                                            // 
     Index b(*str);                         // b = a(i+1) , i<k
                                            //
     ++str;                                 // (str,rule) = (a(i+2),...,ak,r)
                                            //
     if( b.hasClass(IndexNonTerminal) )     // a(i+1) == n'
       add(vertex,b,a,str,rule);            // vertex -> V(n') : (ai, (a(i+2),...,ak,r) )
                                            //
     Index white(DoWhite);                  // next vertex = ?
                                            //
     add(vertex,white,a);                   // vertex -> next vertex : (ai, () )
                                            //
     a=b;                                   // a = a(i+1)
     vertex=white;                          // vertex=next vertex
    }
 }
 
void Diagram::add(NIndex nt)
 {
  Index vertex(nt);
 
  for(auto p=lang.getRules(nt); +p ;++p) add(vertex,p->str,p->rule);
 }

void Diagram::complete()
 {
  RecordPtrs(Range(list),ptr_list);

  IncrSort(Range(ptr_list), [] (const Arrow *a,const Arrow *b) -> bool { return (*a) < (*b) ; } );
 }
 
Diagram::Diagram(const Lang &lang_)
 : lang(lang_)
 {
  for(auto p=lang.getResult(); +p ;++p) addStart(*p);
  
  for(auto p=lang.getNRange(); +p ;++p) add(*p);
  
  complete();
 }  
    
} // namespace PunctPrivate

/* class Punct */

using namespace PunctPrivate;

AlphaIndex Punct::toAlpha(Index ind) const
 {
  switch( ind.getClass() )
    {
     default:
      {
       Printf(Exception,"Punct::toAlpha(Index) : illegal class");
      }
     
     case IndexNull : return AlphaIndexNull;
      
     case IndexBegin : return AlphaIndexBegin;
      
     case IndexTerminal : return AlphaIndex((ind.getIndex()-TIndexFirst)+AlphaIndexFirst);
      
     case IndexNonTerminal : return AlphaIndex((ind.getIndex()-NIndexFirst)+(lang.getTIndexLim()-TIndexFirst)+AlphaIndexFirst);
    }
 }

VIndex Punct::toVertex(Index ind) const
 {
  switch( ind.getClass() )
    {
     default:
      {
       Printf(Exception,"Punct::toVertex(Index) : illegal class");
      }
   
     case IndexStart : return VIndexStart;
      
     case IndexFinish : return VIndexFinish;
      
     case IndexNonTerminal : return VIndex((ind.getIndex()-NIndexFirst)+VIndexFirst);
     
     case IndexWhite : return VIndex(ind.getIndex()+(lang.getNIndexLim()-NIndexFirst)+VIndexFirst);
    }
 }

NTRIndex Punct::toNTR(Index ind) const
 {
  switch( ind.getClass() )
    {
     default:
      {
       Printf(Exception,"Punct::toNTR(Index) : illegal class");
      }
     
     case IndexEnd : return NTRIndex(TIndexEnd);
      
     case IndexNonTerminal : return NTRIndex(NIndex(ind.getIndex()));
     
     case IndexTerminal : return NTRIndex(TIndex(ind.getIndex()));
      
     case IndexRule : return NTRIndex(RIndex(ind.getIndex()));
    }
 }

DynArray<Punct::Rec> * Punct::start(Index ind)
 {
  return data.getPtr()+toAlpha(ind);
 }

void Punct::init(PtrLen<NTRIndex> out,const Index *beta)
 {
  for(; +out ;++out,++beta) *out=toNTR(*beta);
 }

Punct::Rec * Punct::ext(DynArray<Rec> *cur,Rec *last,const Arrow *arrow)
 {
  PtrLen<const Index> beta=arrow->getBeta();
  
  VIndex src=toVertex(arrow->getSrc());
  VIndex dst=toVertex(arrow->getDst());
  
  if( !last || src!=last->src || dst!=last->dst )
    {
     last=cur->append_fill(src,dst,beta.len);
     
     init(Range(last->expr[0]),beta.ptr);
    }
  else
    {
     DynArray<NTRIndex> *obj=last->expr.append_fill(beta.len);
     
     init(Range(*obj),beta.ptr);
    }
  
  return last;
 }

Punct::Punct(const Lang &lang_)
 : lang(lang_),
   alphaLim(AlphaIndexFirst+(lang.getNIndexLim()-NIndexFirst)+(lang.getTIndexLim()-TIndexFirst)),
   data(alphaLim)
 {
  Diagram diagram(lang);
  
  auto p=diagram.getList();
  
  if( +p )
    {
     Index alpha=(*p)->getAlpha();
     DynArray<Rec> *cur=start(alpha);
     Rec *last=ext(cur,0,(*p));
    
     for(++p; +p ;++p)
       {
        Index a=(*p)->getAlpha();
        
        if( a!=alpha )
          {
           alpha=a;

           cur=start(alpha);
           last=ext(cur,0,(*p));
          }
        else
          {
           last=ext(cur,last,(*p));
          }
       }
    }
 }
   
Punct::~Punct()
 {
 }
   
StrLen Punct::getTextDesc(AlphaIndex a) const
 {
  switch( a )
    {
     case AlphaIndexNull : return "(Null)";
      
     case AlphaIndexBegin : return "(Begin)";
      
     default:
      {
       ulen n=lang.getTIndexLim()-TIndexFirst+AlphaIndexFirst;
       
       if( a<n ) return lang.getTextDesc(TIndex(a-AlphaIndexFirst+TIndexFirst));
       
       return lang.getTextDesc(NIndex(a-n+NIndexFirst));
      }
    }
 }

auto Punct::getTextDesc(VIndex v) const -> PrintVIndex
 {
  switch( v )
    {
     case VIndexStart : return StrLen("(Start)");
     
     case VIndexFinish : return StrLen("(Finish)");
     
     default:
      {
       ulen n=lang.getNIndexLim()-NIndexFirst+VIndexFirst;
       
       if( v<n ) return lang.getTextDesc(NIndex(v-VIndexFirst+NIndexFirst));
       
       return PrintVIndex("W",v-n+1);
      }
    }
 }

} // namespace App

