/* LangDiagram.h */
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

#ifndef CondLangLR1_process_LangDiagram_h
#define CondLangLR1_process_LangDiagram_h

#include "lang/Lang.h"

namespace App {

/* classes */

struct Vertex;

struct Arrow;

class LangDiagram;

/* struct Vertex */

struct Vertex : CmpComparable<Vertex> , NoThrowFlagsBase 
 {
  ulen index = MaxULen ;
  
  Vertex() {}
  
  Vertex(ulen index_) : index(index_) {}
  
  // cmp objects
  
  CmpResult objCmp(Vertex obj) const { return LessCmp(index,obj.index); }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"V(#;)",index);
   }
 };

/* struct Arrow */

struct Arrow : NoThrowFlagsBase
 {
  Vertex src;
  Vertex dst;
  Element alpha; // may be null
  PtrLen<const Element> beta;
  
  Arrow(Vertex src_,Vertex dst_,Element alpha_,PtrLen<const Element> beta_) 
   : src(src_),dst(dst_),alpha(alpha_),beta(beta_) {}
  
  Arrow(Vertex src_,Vertex dst_,Element alpha_) 
   : src(src_),dst(dst_),alpha(alpha_) {}
  
  Arrow(Vertex src_,Vertex dst_,PtrLen<const Element> beta_) 
   : src(src_),dst(dst_),beta(beta_) {}
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#; -> #; ( #; ;",src,dst,alpha);
    
    for(Element e : beta ) Printf(out," #;",e);
    
    Putobj(out," )");
   }
 };

/* class LangDiagram */

class LangDiagram : NoCopy
 {
   DynArray<Vertex> start;
   Vertex stop;
   DynArray<Arrow> arrows;
   
   DynArray<Element> elements;
   
  private:
   
   class ExtraVertex;
   
   class ArrowBuilder;
   
  public:
  
   explicit LangDiagram(const Lang &lang);
   
   ~LangDiagram();
   
   // description
   
   PtrLen<const Arrow> getArrows() const { return Range(arrows); }
   
   PtrLen<const Vertex> getStart() const { return Range(start); } // strictly ordered
   
   Vertex getStop() const { return stop; }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"#;\n\n",Title("Start"));
     
     for(Vertex v : start ) Printf(out,"#;\n",v);
     
     Printf(out,"\n#;\n\n",Title("Stop"));
     
     Printf(out,"#;\n",stop);
     
     Printf(out,"\n#;\n\n",Title("Arrows"));
     
     for(const Arrow &a : arrows ) Printf(out,"#;\n",a);
     
     Printf(out,"\n#;\n",TextDivider());
    }
 };

} // namespace App

#endif
