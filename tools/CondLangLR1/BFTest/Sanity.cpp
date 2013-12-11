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
  auto atoms=lang.atoms.getRange();
  auto elements=lang.elements.getRange();
  
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
     
     auto *element=atom.element.getPtr();
     
     if( !Checkin(element,elements) || element->index!=i || element->elem.getPtr().castPtr<TypeDef::Atom>()!=&atom )
       {
        Printf(Exception,"App::DataMap::sanity_atoms(...) : bad atom #; element",i);
       }
    }
 }

void DataMap::sanity_synts()
 {
  auto synts=lang.synts.getRange();
  auto elements=lang.elements.getRange();
  auto top_rules=lang.top_rules.getRange();
  auto rules=lang.rules.getRange();
  
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
     
     auto kinds=synt.kinds.getRange();
     
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
        
        if( kind.synt.getPtr()!=&synt )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; synt",i,j);
          }
        
        auto *element=kind.element.getPtr();
        
        if( !Checkin(element,elements) || element->index!=eindex || element->elem.getPtr().castPtr<TypeDef::Kind>()!=&kind )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; element",i,j);
          }
        
        if( !kind.rules.getRange() )
          {
           Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; , no rules",i,j);
          }
        
        for(auto rule : kind.rules.getRange() )
          if( !Checkin(rule.getPtr(),top_rules) || rule.getPtr()->result.getPtr()!=&kind )
            {
             Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , bad kind #; rules",i,j);
            }
       }
     
     if( !synt.rules.getRange() )
       {
        Printf(Exception,"App::DataMap::sanity_synts(...) : bad synt #; , no rules",i);
       }
     
     for(auto rule : synt.rules.getRange() )
       if( !Checkin(rule.getPtr(),rules) || !rule.getPtr()->result.getPtr() || rule.getPtr()->result.getPtr()->synt.getPtr()!=&synt )
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
  auto synts=lang.synts.getRange();
  
  if( !lang.lang.getRange() )
    {
     Printf(Exception,"App::DataMap::sanity_lang(...) : no lang synts");
    }
  
  for(auto synt : lang.lang.getRange() )
    if( !Checkin(synt.getPtr(),synts) )
      {
       Printf(Exception,"App::DataMap::sanity_lang(...) : bad lang synt");
      }
 }

void DataMap::sanity_rules()
 {
  auto rules=lang.rules.getRange();
  auto synts=lang.synts.getRange();
  auto atoms=lang.atoms.getRange();
  
  for(ulen i=0; i<rules.len ;i++)
    {
     auto &rule=rules[i];
     
     if( rule.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; index",i);
       }
     
     auto *result=rule.result.getPtr();
     
     if( !result || !Checkin(result->synt.getPtr(),synts) || !Checkin(result,result->synt.getPtr()->kinds.getRange()) )
       {
        Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; result",i);
       }
     
     for(auto arg : rule.args.getRange() )
       {
        struct Func
         {
          PtrLen<TypeDef::Atom> atoms;
          PtrLen<TypeDef::Synt> synts;
          ulen i;
          
          Func(PtrLen<TypeDef::Atom> atoms_,PtrLen<TypeDef::Synt> synts_,ulen i_) : atoms(atoms_),synts(synts_),i(i_) {}
          
          void operator () (TypeDef::Atom *atom)
           {
            if( !Checkin(atom,atoms) )
              {
               Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; args",i);
              }
           }
          
          void operator () (TypeDef::Synt *synt)
           {
            if( !Checkin(synt,synts) )
              {
               Printf(Exception,"App::DataMap::sanity_rules(...) : bad rule #; args",i);
              }
           }
         };
       
        arg.getPtr().apply(Func(atoms,synts,i));
       }
    }
 }

void DataMap::sanity_top_rules()
 {
  auto top_rules=lang.top_rules.getRange();
  auto rules=lang.rules.getRange();
  
  for(ulen i=0; i<top_rules.len ;i++)
    {
     auto &rule=top_rules[i];
     
     if( rule.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; index",i);
       }
     
     auto *bottom=rule.bottom.getPtr();
     
     if( !Checkin(bottom,rules) )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; bottom",i);
       }
      
     if( rule.result.getPtr()!=bottom->result.getPtr() )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; result",i);
       }
     
     auto args=rule.args.getRange();
     auto bottom_args=bottom->args.getRange();
     
     using Type = decltype(bottom_args) ;
     
     if( args.len!=bottom_args.len )
       {
        Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
       }
     
     for(ulen j=0; j<args.len ;j++)
       {
        struct Func
         {
          Type bottom_args;
          ulen i;
          ulen j;
          
          Func(Type bottom_args_,ulen i_,ulen j_) : bottom_args(bottom_args_),i(i_),j(j_) {}
          
          void operator () (TypeDef::Atom *atom)
           {
            if( bottom_args[j].getPtr().castPtr<TypeDef::Atom>()!=atom )
              {
               Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
              }
           }
          
          void operator () (TypeDef::Kind *kind)
           {
            auto *synt=bottom_args[j].getPtr().castPtr<TypeDef::Synt>();
            
            if( !synt || !Checkin(kind,synt->kinds.getRange()) )
              {
               Printf(Exception,"App::DataMap::sanity_top_rules(...) : bad top rule #; args",i);
              }
           }
         };
       
        args[j].getPtr().apply(Func(bottom_args,i,j));
       }
    }
 }

void DataMap::sanity_states()
 {
  auto states=lang.states.getRange();
  auto finals=lang.finals.getRange();
  auto elements=lang.elements.getRange();
  
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
     
     if( !Checkin(state.final.getPtr(),finals) )
       {
        Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; final",i);
       }
     
     for(auto p=state.transitions.getRange(); +p ;++p)
       {
        if( !Checkin(p->element.getPtr(),elements) || !Checkin(p->state.getPtr(),states) )
          {
           Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; transitions",i);
          }
       }
     
     for(auto p=state.transitions.getRange(); p.len>1 ;++p)
       if( p[0].element->index>=p[1].element->index )
         {
          Printf(Exception,"App::DataMap::sanity_states(...) : bad state #; transitions",i);
         }
    }
 }

void DataMap::sanity_finals()
 {
  auto finals=lang.finals.getRange();
  auto atoms=lang.atoms.getRange();
  auto rules=lang.rules.getRange();
  
  for(ulen i=0; i<finals.len ;i++)
    {
     auto &final=finals[i];
     
     if( final.index!=i )
       {
        Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; index",i);
       }
     
     for(auto action : final.actions.getRange() )
       {
        if( !Checkin_null(action.atom.getPtr(),atoms) || !Checkin_null(action.rule.getPtr(),rules) )
          {
           Printf(Exception,"App::DataMap::sanity_finals(...) : bad final #; actions",i);
          }
       }
     
     {
      auto actions=final.actions.getRange();
      
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
