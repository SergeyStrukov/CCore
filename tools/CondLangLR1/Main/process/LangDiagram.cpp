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

LangDiagram::LangDiagram(const Lang &lang)
 : start(DoReserve,1024)
 {
  ulen N=lang.getSyntCount();
  
  // start/stop
  {
   stop=N;
    
   for(auto &synt : lang.getSynts() ) if( synt.is_lang ) start.append_fill(synt.index);
    
   start.shrink_extra();
  }
  
  // elements
  {
   auto *out=elements.extend_default(N).ptr;
   
   for(auto &synt : lang.getSynts() ) *(out++)=&synt;
  }

  // arrows
  {
   ExtraVertex extra(N);
   Collector<Arrow> collector;
   
   for(auto &rule : lang.getRules() )
     {
      ulen K=rule.ret->index;
      
      Element T(rule.ret);
      
      collector.append_fill(K,N,T);
      collector.append_fill(K,N,Range_const(elements.getPtr()+K,1));
      
      PtrLen<const Element> args=rule.args;
     
      if( args.len )
        {
         Vertex cur(K);
         
         Element E=*args;
         
         ++args;
         
         E.applyForSynt( [=,&collector] (Synt synt) { collector.append_fill(cur,synt.getIndex(),args); } );
         
         if( +args )
           for(;;)
             {
              collector.append_fill(cur,N,E,args);
              
              Element F=*args;
              
              ++args;
              
              F.applyForSynt( [=,&collector] (Synt synt) { collector.append_fill(cur,synt.getIndex(),E,args); } );
               
              if( !args ) break;
               
              Vertex v=extra.get();
               
              collector.append_fill(cur,v,E);
               
              cur=v;
              E=F;
             }
        }
     }
   
   collector.copyTo(arrows);
  }
 }

LangDiagram::~LangDiagram() 
 {
 }

} // namespace App


