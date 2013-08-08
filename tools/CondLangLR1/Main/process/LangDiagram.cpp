/* LangDiagram.cpp */
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

#include "LangDiagram.h"

#include <CCore/inc/Exception.h>

namespace App {

/* class LangDiagram */

class LangDiagram::ExtraVertex : NoCopy
 {
   ulen last;
   
  public:
 
   explicit ExtraVertex(ulen last_) : last(last_) {}
   
   Vertex get()
    {
     ulen ret=++last;
     
     if( !ret )
       {
        Printf(Exception,"App::LangDiagram::ExtraVertex::get() : overflow");
       }
     
     return ret;
    }
 };

class LangDiagram::ArrowBuilder : NoCopy
 {
   ulen N;
   ExtraVertex extra;
   Collector<Arrow> collector;
   
  public: 
   
   explicit ArrowBuilder(ulen N_) : N(N_),extra(N_) {}
   
   ~ArrowBuilder() {}
   
   void add(Synt synt,const Element *base)
    {
     Element T(synt);
     ulen K=synt.getIndex();
     
     collector.append_fill(K,N,T);
     collector.append_fill(K,N,Range(base+K,1));
    }
   
   void add(Rule rule)
    {
     ulen K=rule.getRet().getIndex();
     
     PtrLen<const Element> args=rule.getArgs();
    
     if( +args )
       {
        Vertex cur(K);
        
        Element E=*args;
        
        ++args;
        
        E.applyForSynt( [=] (Synt synt) { collector.append_fill(cur,synt.getIndex(),args); } );
        
        if( +args )
          for(;;)
            {
             collector.append_fill(cur,N,E,args);
             
             Element F=*args;
             
             ++args;
             
             F.applyForSynt( [=] (Synt synt) { collector.append_fill(cur,synt.getIndex(),E,args); } );
              
             if( !args ) break;
              
             Vertex v=extra.get();
              
             collector.append_fill(cur,v,E);
              
             cur=v;
             E=F;
            }
       }
    }
   
   void finish(DynArray<Arrow> &ret)
    {
     collector.copyTo(ret);
    }
 };

LangDiagram::LangDiagram(const Lang &lang)
 {
  ulen N=lang.getSyntCount();
  
  // start/stop
  {
   stop=N;
   
   start.reserve(N);
    
   lang.applyForSynts( [this] (Synt synt) { if( synt.isLang() ) start.append_fill(synt.getIndex()); } );
   
   start.shrink_extra();
  }
  
  // elements
  {
   elements.reserve(N);
   
   lang.applyForSynts( [this] (Synt synt) { elements.append_fill(synt); } );
  }

  // arrows
  {
   ArrowBuilder builder(N);
   const Element *base=elements.getPtr();
   
   lang.applyForSynts( [=,&builder] (Synt synt) { builder.add(synt,base); } );
   
   lang.applyForRules( [&builder] (Rule rule) { builder.add(rule); } );
   
   builder.finish(arrows);
  }
 }

LangDiagram::~LangDiagram() 
 {
 }

} // namespace App


