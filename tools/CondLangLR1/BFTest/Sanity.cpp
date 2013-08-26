/* Sanity.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1-BFTest 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "DataMap.h"

#include <CCore/inc/Exception.h>

namespace App {

/* class DataMap */

void DataMap::sanity_atoms()
 {
  auto atoms=lang.atoms;
  auto elements=lang.elements;
  
  if( !atoms )
    {
     Printf(Exception,"App::DataMap::sanity_atoms(...) : no atoms");
    }
  
  for(ulen i=0; i<atoms.len ;i++)
    {
     auto &atom=atoms[i];
    
     if( atom.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_atoms(...) : bad atom #; index",i);
       }
     
     auto *element=atom.element;
     
     if( !Checkin(element,elements) || element->index!=i || element->atom!=&atom || element->kind )
       {
        Printf(Exception,"App::DataMap::sanity_atoms(...) : bad atom #; element",i);
       }
    }
 }

void DataMap::sanity_synts()
 {
  auto synts=lang.synts;
  auto elements=lang.elements;
  auto top_rules=lang.top_rules;
  auto rules=lang.rules;
  
  ulen eindex=lang.atoms.len;
  ulen kindex=0;
  
  if( !synts )
    {
     Printf(Exception,"App::DataMap::sanity_synts(...) : no synts");
    }
  
  for(ulen i=0; i<synts.len ;i++)
    {
     auto &synt=synts[i];
     
     if( synt.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; index",i);
       }
     
     auto kinds=synt.kinds;
     
     if( !kinds )
       {
        Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , no kinds",i);
       }
     
     for(ulen j=0; j<kinds.len ;j++,eindex++)
       {
        auto &kind=kinds[j];
        
        if( kind.kindex!=kindex )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; kindex",i,j);
          }
        
        kindex++;
        
        if( kind.index!=j )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; index",i,j);
          }
        
        if( kind.synt!=&synt )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; synt",i,j);
          }
        
        auto *element=kind.element;
        
        if( !Checkin(element,elements) || element->index!=eindex || element->kind!=&kind || element->atom )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; element",i,j);
          }
        
        if( !kind.rules )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; , no rules",i,j);
          }
        
        for(auto *rule : kind.rules )
          if( !Checkin(rule,top_rules) || rule->result!=&kind )
            {
             Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; rules",i,j);
            }
       }
     
     if( !synt.rules )
       {
        Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , no rules",i);
       }
     
     for(auto *rule : synt.rules )
       if( !Checkin(rule,rules) || !rule->result || rule->result->synt!=&synt )
         {
          Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad rules",i);
         }
    }
  
  if( eindex!=elements.len )
    {
     Printf(Exception,"App::DataMap::sanity_synts(...) : extra elements");
    }
 }

void DataMap::sanity_lang()
 {
  auto synts=lang.synts;
  
  if( !lang.lang )
    {
     Printf(Exception,"App::DataMap::sanity_lang(...) : no lang synts");
    }
  
  for(auto *synt : lang.lang )
    if( !Checkin(synt,synts) )
      {
       Printf(Exception,"App::DataMap::sanity_lang(...) : bad lang synt");
      }
 }

void DataMap::sanity_rules()
 {
  auto rules=lang.rules;
  auto synts=lang.synts;
  auto atoms=lang.atoms;
  
  for(ulen i=0; i<rules.len ;i++)
    {
     auto &rule=rules[i];
     
     if( rule.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; index",i);
       }
     
     auto *result=rule.result;
     
     if( !result || !Checkin(result->synt,synts) || !Checkin(result,result->synt->kinds) )
       {
        Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; result",i);
       }
     
     for(auto arg : rule.args )
       if( arg.atom )
         {
          if( arg.synt || !Checkin(arg.atom,atoms) )
            {
             Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; args",i);
            }
         }
       else
         {
          if( !Checkin(arg.synt,synts) )
            {
             Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; args",i);
            }
         }
    }
 }

void DataMap::sanity_top_rules()
 {
  auto top_rules=lang.top_rules;
  auto rules=lang.rules;
  
  for(ulen i=0; i<top_rules.len ;i++)
    {
     auto &rule=top_rules[i];
     
     if( rule.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; index",i);
       }
     
     auto *bottom=rule.bottom;
     
     if( !Checkin(bottom,rules) )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; bottom",i);
       }
      
     if( rule.result!=bottom->result )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; result",i);
       }
     
     auto args=rule.args;
     auto bottom_args=bottom->args;
     
     if( args.len!=bottom_args.len )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
       }
     
     for(ulen j=0; j<args.len ;j++)
       {
        if( auto *atom=args[j].atom )
          {
           if( args[j].kind || bottom_args[j].atom!=atom )
             {
              Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
             }
          }
        else
          {
           auto *kind=args[j].kind;
           auto *synt=bottom_args[j].synt;
           
           if( !Checkin(kind,synt->kinds) )
             {
              Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
             }
          }
       }
    }
 }

void DataMap::sanity_states()
 {
  auto states=lang.states;
  auto finals=lang.finals;
  auto elements=lang.elements;
  
  if( !states )
    {
     Printf(Exception,"App::DataMap::sanity_states(...) : no states");
    }
  
  for(ulen i=0; i<states.len ;i++)
    {
     auto &state=states[i];
     
     if( state.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; index",i);
       }
     
     if( !Checkin(state.final,finals) )
       {
        Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; final",i);
       }
     
     for(auto p=state.transitions; +p ;++p)
       {
        if( !Checkin(p->element,elements) || !Checkin(p->state,states) )
          {
           Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; transitions",i);
          }
       }
     
     for(auto p=state.transitions; p.len>1 ;++p)
       if( p[0].element->index>=p[1].element->index )
         {
          Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; transitions",i);
         }
    }
 }

void DataMap::sanity_finals()
 {
  auto finals=lang.finals;
  auto atoms=lang.atoms;
  auto rules=lang.rules;
  
  for(ulen i=0; i<finals.len ;i++)
    {
     auto &final=finals[i];
     
     if( final.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; index",i);
       }
     
     for(auto action : final.actions )
       {
        if( !Checkin_null(action.atom,atoms) || !Checkin_null(action.rule,rules) )
          {
           Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
       }
     
     {
      auto actions=final.actions;
      
      if( +actions && !actions->atom ) ++actions;
      
      for(auto p=actions; +p ;++p)
        if( !p->atom )
          {
           Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
      
      for(auto p=actions; p.len>1 ;++p)
        if( p[0].atom->index>=p[1].atom->index )
          {
           Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
     }
    }
 }

void DataMap::sanity()
 {
  sanity_atoms();
  sanity_synts();
  sanity_lang();
  sanity_rules();
  sanity_top_rules();
  sanity_states();
  sanity_finals();
 }

} // namespace App
