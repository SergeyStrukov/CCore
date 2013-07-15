/* Lang.cpp */
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

#include "Lang.h"
#include "LangParser.h"

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Exception.h>

namespace App {

using namespace LangParser;

/* class Lang::Builder */

class Lang::Builder : NoCopy
 {
   Lang &lang;
   
   enum State
    {
     Beg,      // 
     Name,     // !
     Kinds,    // Name
     NextKind, // Name :
     EndKind,  // Name : A
     Rules,    // Name {
     RuleEnd,  // Name { ... :
     RuleIf,   // Name { ... : if
     RuleCond, // Name { ... : if (
    };
   
   State state = Beg ;
   bool has_kinds;
   
  private:
   
   void startSynt(StrLen name,bool is_lang);
   
   void addKind(StrLen name);
   
   void addElement(StrLen elem);
   
   void endElements();
   
   void endSynt();
   
  private:
 
   void put_Beg(Token token);
   void put_Name(Token token);
   void put_Kinds(Token token);
   void put_NextKind(Token token);
   void put_EndKind(Token token);
   void put_Rules(Token token);
   void put_RuleEnd(Token token);
 
  public:
 
   explicit Builder(Lang &lang);
   
   ~Builder();
   
   bool isNextRelaxed() const { return state==Rules; }
   
   void put(Token token);
 };

void Lang::Builder::startSynt(StrLen name,bool is_lang)
 {
  Printf(Con,"startSynt(#.q;,#;)\n",name,is_lang);
  
  has_kinds=false;
 }

void Lang::Builder::addKind(StrLen name)
 {
  Printf(Con,"addKind(#.q;)\n",name);
  
  has_kinds=true;
 }

void Lang::Builder::addElement(StrLen elem)
 {
  Printf(Con,"addElement( #; )\n",elem);
 }

void Lang::Builder::endElements()
 {
  Printf(Con,"endElements()\n");
 }

void Lang::Builder::endSynt()
 {
  Printf(Con,"endSynt()\n");
 }


void Lang::Builder::put_Beg(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is('!') ) 
         {
          state=Name;
         }
      }
     return;
      
     case Token_Name :
      {
       startSynt(token.str,false);
       
       state=Kinds;
      }
     return;
     
     case Token_END :
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token, NAME or '!' are expected",token.pos);
 }

void Lang::Builder::put_Name(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       startSynt(token.str,true);
       
       state=Kinds;
      }
     return;
     
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token, NAME is expected",token.pos);
 }

void Lang::Builder::put_Kinds(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is(':') ) 
         {
          state=NextKind;
         }
       else if( token.is('{') )
         {
          state=Rules;
         }
      }
     return;
    
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token, ':' or '{' are expected",token.pos);
 }

void Lang::Builder::put_NextKind(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       addKind(token.str);
       
       state=EndKind;
      }
     return;
    
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token, NAME is expected",token.pos);
 }

void Lang::Builder::put_EndKind(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is(',') )
         {
          state=NextKind;
         }
       else if( token.is('{') )
         {
          state=Rules;
         }
      }
     return;
     
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token, ',' or '{' are expected",token.pos);
 }

void Lang::Builder::put_Rules(Token token)
 {
  switch( token.tc )
    {
     case Token_Visible :
      {
       if( token.is('}') )
         {
          endSynt();
         
          state=Beg;
         }
       else if( token.is(':') )
         {
          endElements();
          
          state=RuleEnd;
         }
       else
         {
          addElement(token.str);
         }
      }
     return;
     
     case Token_Space :
      {
       // do nothing
      }
     return;
    }
  
  Printf(Exception,"Parser #; : unexpected token",token.pos);
 }

void Lang::Builder::put_RuleEnd(Token token)
 {
 }

Lang::Builder::Builder(Lang &lang_) 
 : lang(lang_)
 {
 }

Lang::Builder::~Builder()
 {
 }

void Lang::Builder::put(Token token)
 {
  switch( state )
    {
     case Beg : put_Beg(token); break;
     case Name : put_Name(token); break;
     case Kinds : put_Kinds(token); break;
     case NextKind : put_NextKind(token); break;
     case EndKind : put_EndKind(token); break;
     case Rules : put_Rules(token); break;
     case RuleEnd : put_RuleEnd(token); break;
    }
 }

/* class Lang */

Lang::Lang(StrLen file_name)
 {
  FileToMem file(file_name);
  Tokenizer tok(Mutate<const char>(Range(file)));
  Builder builder(*this);

  while( +tok )
    {
     if( builder.isNextRelaxed() )
       builder.put(tok.next_relaxed());
     else
       builder.put(tok.next());
    }
  
  builder.put(Token(tok.getPos()));
 }

Lang::~Lang()
 {
 }

} // namespace App

