/* LangBuilder.cpp */
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

#include "LangBuilder.h"

namespace App {
namespace LangInput {

/* class Builder */

void Builder::parse()
 {
  while( +tokenizer )
    {
     Atom atom(tokenizer.next());
     
     if( !atom )
       {
        if( atom.token.tc==Token_Other ) 
          {
           Printf(Exception,"Tokenizer error");
          }
       }
     else
       {
        parser.do_next(atom);
       }
    }
  
  parser.do_complete(tokenizer.getPos());
  
  parser.getBody()->extract(result);
 }

bool Builder::link(PtrLen<MixDescPtr> range,NTDesc *nt)
 {
  // 1
  {
   bool ret=true;
   
   for(auto p=range; +p && p->isNT ;++p)
     {
      Printf(Con,"Name link #; #; : the same non-terminal names\n",nt->name,p->getToken());
      
      ret=false;
     }
   
   if( !ret ) return false;
  }
  
  // 2
  {
   for(auto p=range; +p ;++p) p->getNTTDesc()->set(nt);
  }
  
  return true;
 }

void Builder::link(PtrLen<MixDescPtr> range)
 {
  TDesc *t=terminals.append_fill(range->getToken());
  
  for(auto p=range; +p ;++p) p->getNTTDesc()->set(t);
 }

bool Builder::link()
 {
  bool ret=true;
  
  // 1
  {
   DynArray<DescPtr> buf;
   
   for(auto p=Range(result); +p ;++p)
     for(auto q=Range(p->rules); +q ;++q)
       {
        buf.append_fill(q.ptr);
        
        if( q->name.tc!=Token_CWord )
          {
           Printf(Con,"Name link #; : rule name is not a C-name\n",q->name);
           
           ret=false;
          }
       }
   
   Sort(Range(buf));
   
   for(auto p=Range(buf); p.len>1 ;++p)
     if( !( p[0]<p[1] ) )
       {
        Printf(Con,"Name link #; #; : the same rule names\n",p[0].getToken(),p[1].getToken());
        
        ret=false;
       }
  }

  // 2
  {
   DynArray<MixDescPtr> buf;
   
   for(auto p=Range(result); +p ;++p)
     {
      buf.append_fill(p.ptr);
      
      if( p->name.tc!=Token_CWord )
        {
         Printf(Con,"Name link #; : non-terminal name is not a C-name\n",p->name);
         
         ret=false;
        }
      
      for(auto q=Range(p->rules); +q ;++q)
        for(auto r=Range(q->str); +r ;++r)
          {
           buf.append_fill(r.ptr);
          }
     }
   
   Sort(Range(buf));
   
   {
    auto p=Range(buf);
    
    while( +p )
      {
       MixDescPtr first=*p;
       
       if( first.isNT )
         {
          ++p;
          
          auto q=p;
          
          for(; +q && !first.weakLess(*q) ;++q);
          
          if( !link(p.prefix(q),first.getNTDesc()) ) ret=false;

          p=q;
         }
       else
         {
          auto q=p;
          
          for(++q; +q && !first.weakLess(*q) ;++q);
          
          link(p.prefix(q));

          p=q;
         }
      }
   }
  }
  
  return ret;
 }

Builder::Builder(StrLen file_name)
 : map(file_name),
   tokenizer(Mutate<const char>(Range(map)))
 {
  parse();
  
  if( !link() )
    {
     Printf(Exception,"Name link error");
    } 
 }

Builder::~Builder() {}

void Builder::extract(Lang::Builder &builder)
 {
  for(auto p=Range(terminals); +p ;++p) p->addTo(builder);
  
  bool has_result=false;
  
  for(auto p=Range(result); +p ;++p) if( p->addTo(builder) ) has_result=true;
  
  if( !has_result )
    {
     Printf(Exception,"The lang result is empty");
    }
  
  for(auto p=Range(result); +p ;++p) p->addRules();
 }

} // namespace LangInput
} // namespace App

 
 

