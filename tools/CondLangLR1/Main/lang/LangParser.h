/* LangParser.h */
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

#ifndef CondLangLR1_LangParser_h
#define CondLangLR1_LangParser_h

#include "Tools.h"

#include <CCore/inc/TextTools.h>

namespace App {
namespace LangParser {

/* classes */

//enum CharClass;

//enum TokenClass;

struct Token;

class Tokenizer;

//enum CondAtom;

struct CondPaserBase;

template <class Action> class CondParser; 

template <class Action> class Parser;

/* enum CharClass */ 

enum CharClass
 {
  Char_Digit,
  Char_Letter,
  Char_Punct,
  Char_Comment,
  Char_Space,

  Char_Other
 };
 
inline bool IsLetterDigit(CharClass cc) { return cc<=Char_Letter; }
 
/* class CharProp */ 

class CharProp : public CharPropTable<CharClass,Char_Other>
 {
  public:

   CharProp();
 
   static const CharProp Object;
 };

/* char functions */ 
 
inline CharClass GetCharClass(char ch) { return CharProp::Object[ch]; }

inline bool CharIsLetterDigit(char ch) { return IsLetterDigit(GetCharClass(ch)); }

//---------------------------------
//                                 
// From CharProp.h and TextTools.h
//
//---------------------------------
//
// bool CharIsEOL(char ch);
//
// bool CharIsSpace(char ch);
//
// bool CharIsVisible(char ch);
//
//---------------------------------

/* enum TokenClass */

enum TokenClass
 {
  Token_Punct,
  Token_Name,
  Token_Visible,
  
  Token_Space,
 
  Token_ShortComment,
  Token_LongComment,
  
  Token_END,
  
  Token_Other
 };

const char * GetTextDesc(TokenClass tc);

/* struct Token */

struct Token
 {
  TokenClass tc;
  TextPos pos;
  StrLen str;

  Token() : tc(Token_Other) {}
 
  Token(TokenClass tc_,TextPos pos_,StrLen str_) : tc(tc_),pos(pos_),str(str_) {}
  
  explicit Token(TextPos pos_) : tc(Token_END),pos(pos_) {}
  
  bool is(char ch) const { return str.len==1 && str[0]==ch ; }
  
  bool is(char ch1,char ch2) const { return str.len==2 && str[0]==ch1 && str[1]==ch2 ; }
 };

/* class Tokenizer */

class Tokenizer : NoCopy
 {
   TextPos pos;
   StrLen text;
   
  private:
   
   struct Scan;
   struct BadScan;
   
   static ulen ScanShortComment(StrLen text); // >=2
   static Scan ScanLongComment(StrLen text); // >=2
   
   static ulen ScanLetterDigit(StrLen text); // >=1
   static ulen ScanSpace(StrLen text); // >=1
   
   static ulen ScanVisible(StrLen text); // >=1
   
  private: 
   
   Token cut(TokenClass tc,ulen len);
   Token cut_pos(TokenClass tc,ulen len);
   
   Token next_short_comment();
   Token next_long_comment();
   
   Token next_word();
   Token next_punct();
   Token next_comment();
   Token next_space();
   Token next_visible();
   Token next_other();
   
  public:
  
   explicit Tokenizer(StrLen text_) : text(text_) {}
   
   ulen operator + () const { return text.len; }
   
   bool operator ! () const { return !text.len; }
 
   Token next();
   
   Token next_relaxed();
   
   TextPos getPos() const { return pos; }
 };

/* enum CondAtom */

enum CondAtom
 {
  CondAtomEnd,
  
  CondAtom_NOT,  // !
  CondAtom_NE,   // !=
  CondAtom_AND,  // &
  CondAtom_OBR,  // (
  CondAtom_CBR,  // )
  CondAtom_LT,   // <
  CondAtom_LE,   // <=
  CondAtom_EQ,   // ==
  CondAtom_GT,   // >
  CondAtom_GE,   // >=
  CondAtom_Name, // NAME
  CondAtom_OR,   // |
  
  CondAtomLim
 };

/* struct CondPaserBase */

struct CondPaserBase : NoCopy
 {
  enum Rule
   {
    Rule_Shift,
    
    Rule_CastMUL,
    Rule_OpOR,
    Rule_CastUN,
    Rule_OpAND,
    Rule_CastPRIM,
    Rule_OpNOT,
    Rule_OpEQ,
    Rule_OpNE,
    Rule_OpLT,
    Rule_OpLE,
    Rule_OpGT,
    Rule_OpGE,
    Rule_Brackets,
    
    RuleError
   };
  
  enum Synt
   {
    Synt_COND,
    Synt_COND_MUL,
    Synt_COND_UN,
    Synt_COND_PRIM,
    
    SyntLim
   };
  
  struct State
   {
    Rule actions[CondAtomLim];
    
    const State * atom_transitions[CondAtomLim];
    const State * synt_transitions[SyntLim];
   };
  
  static const State StateTable[];
 };

/* class CondParser<Action> */

template <class Action> 
class CondParser : CondPaserBase
 {
   Action &action;
   
   using BuildCond = typename Action::BuildCond ;
   
   struct Node
    {
     const State *state;
     BuildCond cond;
     StrLen name;
    };
   
   static const ulen Len = 100 ;
   
   Node buf[Len];
   ulen len;
   
  private: 
   
   Node * top(ulen ind=1) { return buf+(len-ind); }
   
   void pop(ulen delta) { len-=delta; }
   
   void push(Synt synt,BuildCond cond)
    {
     const State *state=top()->state->synt_transitions[synt];
     
     buf[len++]={state,cond};
    }
   
   void cast(Synt synt)
    {
     top()->state=top(2)->state->synt_transitions[synt];
    }
   
   bool putAtom(CondAtom atom,TextPos pos);
   
  public:
 
   explicit CondParser(Action &action_) : action(action_) {}
   
   ~CondParser() {}
   
   void reset();

   void put(CondAtom atom,TextPos pos);
   
   void putName(StrLen name,TextPos pos);
   
   void putEnd(TextPos pos);
 };

template <class Action> 
bool CondParser<Action>::putAtom(CondAtom atom,TextPos pos)
 {
  switch( top()->state->actions[atom] )
    {
     case Rule_Shift : return false; 
   
     case Rule_CastMUL :
      {
       cast(Synt_COND);
      }
     break; 
      
     case Rule_OpOR :
      {
       BuildCond cond=action.condOR(top(3)->cond,top(1)->cond);
       
       pop(3);
       push(Synt_COND,cond);
      }
     break;
     
     case Rule_CastUN :
      {
       cast(Synt_COND_MUL);
      }
     break;
     
     case Rule_OpAND :
      {
       BuildCond cond=action.condAND(top(3)->cond,top(1)->cond);
       
       pop(3);
       push(Synt_COND_MUL,cond);
      }
     break;
     
     case Rule_CastPRIM :
      {
       cast(Synt_COND_UN);
      }
     break;
     
     case Rule_OpNOT :
      {
       BuildCond cond=action.condNOT(top(1)->cond);
       
       pop(2);
       push(Synt_COND_UN,cond);
      }
     break;
     
     case Rule_OpEQ :
      {
       BuildCond cond=action.condEQ(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_OpNE :
      {
       BuildCond cond=action.condNE(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_OpLT :
      {
       BuildCond cond=action.condLT(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_OpLE :
      {
       BuildCond cond=action.condLE(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_OpGT :
      {
       BuildCond cond=action.condGT(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_OpGE :
      {
       BuildCond cond=action.condGE(top(3)->name,top(1)->name);
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break;
     
     case Rule_Brackets :
      {
       BuildCond cond=top(2)->cond;
       
       pop(3);
       push(Synt_COND_PRIM,cond);
      }
     break; 
   
     default: // case RuleError
      {
       action.error("Parser #; : unexpected atom",pos);
      }
     return false; 
    }
  
  return true;
 }

template <class Action> 
void CondParser<Action>::reset()
 {
  buf[0]={StateTable};
  len=1;
 }

template <class Action> 
void CondParser<Action>::put(CondAtom atom,TextPos pos)
 {
  while( putAtom(atom,pos) );
  
  if( len<Len )
    {
     const State *state=top()->state->atom_transitions[atom];
     
     buf[len++]={state};
    }
  else
    {
     action.error("Parser #; : stack overflow",pos);
    }
 }

template <class Action> 
void CondParser<Action>::putName(StrLen name,TextPos pos)
 {
  while( putAtom(CondAtom_Name,pos) );
  
  if( len<Len )
    {
     const State *state=top()->state->atom_transitions[CondAtom_Name];
     
     buf[len++]={state,{},name};
    }
  else
    {
     action.error("Parser #; : stack overflow",pos);
    }
 }

template <class Action> 
void CondParser<Action>::putEnd(TextPos pos)
 {
  while( putAtom(CondAtomEnd,pos) );
  
  action.rule(top()->cond);
 }

/* class Parser<Action> */

template <class Action> 
class Parser : NoCopy
 {
   Action action;
   
   enum State
    {
     State_Beg,        // ...        Name { 
     State_Name,       // !          Name
     State_Kinds,      // Name       ...
     State_NextKind,   // Name :     ...
     State_EndKind,    // Name : A   ...
     State_Rules,      // Name {     ...
     
     State_RuleEnd,    // Name { ... :
     State_RuleIf,     // Name { ... : if
     State_RuleCond,   // Name { ... : if (
     State_RuleName,   // ...        Name
     
     State_Result,     // ...        = Name
     State_ResultName  // ... =      Name
    };
   
   State state = State_Beg ;
   bool has_kinds;
   
   CondParser<Action> cond_parser;
   ulen cond_count;
   
  private: 
   
   bool isNextRelaxed() const { return state==State_Rules; }
   
   void put_Beg(Token token);
   void put_Name(Token token);
   void put_Kinds(Token token);
   void put_NextKind(Token token);
   void put_EndKind(Token token);
   void put_Rules(Token token);
   void put_RuleEnd(Token token);
   void put_RuleIf(Token token);
   void put_RuleCond(Token token);
   void put_RuleName(Token token);
   void put_Result(Token token);
   void put_ResultName(Token token);
   
   void put(Token token);
   
  public:
 
   template <class ... SS>
   explicit Parser(SS && ... ss) : action( std::forward<SS>(ss)... ),cond_parser(action) {}
   
   ~Parser() {}
   
   void run(StrLen text);
 };

template <class Action> 
void Parser<Action>::put_Beg(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is('!') ) 
         {
          state=State_Name;
          
          return;
         }
      }
     break;
      
     case Token_Name :
      {
       action.startSynt(token.str,false);
       
       has_kinds=false;
       
       state=State_Kinds;
       
       return;
      }
     break;
     
     case Token_END :
      {
       action.endLang();
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME or '!' are expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_Name(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       action.startSynt(token.str,true);
       
       has_kinds=false;
       
       state=State_Kinds;
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_Kinds(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is(':') ) 
         {
          state=State_NextKind;
          
          return;
         }
       
       if( token.is('{') )
         {
          state=State_Rules;
          
          return;
         }
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, ':' or '{' are expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_NextKind(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       action.addKind(token.str);
       
       state=State_EndKind;
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_EndKind(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is(',') )
         {
          state=State_NextKind;
          
          return;
         }
       
       if( token.is('{') )
         {
          action.endKinds();
          
          has_kinds=true;
         
          state=State_Rules;
          
          return;
         }
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, ',' or '{' are expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_Rules(Token token)
 {
  switch( token.tc )
    {
     case Token_Visible :
      {
       if( token.is('}') )
         {
          action.endSynt();
         
          state=State_Beg;
          
          return;
         }
       
       if( token.is(':') )
         {
          action.endElements();
          
          state=State_RuleEnd;
          
          return;
         }
       
       action.addElement(token.str);
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token",token.pos);
 }

template <class Action> 
void Parser<Action>::put_RuleEnd(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       if( token.is('i','f') )
         {
          state=State_RuleIf;
          
          return;
         }
       
       action.rule(token.str);
          
       state=has_kinds?State_Result:State_Rules;
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME or 'if' are expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_RuleIf(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is('(') )
         {
          cond_parser.reset();
          cond_count=0;
         
          state=State_RuleCond;
          
          return;
         }
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, '(' is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_RuleCond(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       switch( token.str.len )
         {
          case 1 :
           {
            switch( token.str[0] )
              {
               case '!' : cond_parser.put(CondAtom_NOT,token.pos); return;
               case '&' : cond_parser.put(CondAtom_AND,token.pos); return;
               
               case '(' : cond_parser.put(CondAtom_OBR,token.pos); cond_count++; return;
               
               case ')' :
                {
                 if( cond_count ) 
                   { 
                    cond_parser.put(CondAtom_CBR,token.pos);
                    
                    cond_count--; 
                   }
                 else
                   {
                    cond_parser.putEnd(token.pos);
                    
                    state=State_RuleName;
                   }
                }
               return; 
                
               case '<' : cond_parser.put(CondAtom_LT,token.pos); return;
               case '>' : cond_parser.put(CondAtom_GT,token.pos); return;
               case '|' : cond_parser.put(CondAtom_OR,token.pos); return;
              }
           }
          break;
          
          case 2 :
           {
            if( token.str[1]=='=' )
              {
               switch( token.str[0] )
                 {
                  case '!' : cond_parser.put(CondAtom_NE,token.pos); return;
                  case '<' : cond_parser.put(CondAtom_LE,token.pos); return;
                  case '>' : cond_parser.put(CondAtom_GE,token.pos); return;
                  case '=' : cond_parser.put(CondAtom_EQ,token.pos); return;
                 }
              }
           }
          break; 
         }
      }
     break;
     
     case Token_Name :
      {
       cond_parser.putName(token.str,token.pos);
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token",token.pos);
 }

template <class Action> 
void Parser<Action>::put_RuleName(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       action.rule(token.str);
       
       state=has_kinds?State_Result:State_Rules;
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_Result(Token token)
 {
  switch( token.tc )
    {
     case Token_Punct :
      {
       if( token.is('=') )
         {
          state=State_ResultName;
          
          return;
         }
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, '=' is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put_ResultName(Token token)
 {
  switch( token.tc )
    {
     case Token_Name :
      {
       action.result(token.str);
       
       state=State_Rules;
       
       return;
      }
     break;
    }
  
  action.error("Parser #; : unexpected token, NAME is expected",token.pos);
 }

template <class Action> 
void Parser<Action>::put(Token token)
 {
  switch( token.tc )
    {
     case Token_Space :
     case Token_ShortComment :
     case Token_LongComment :
      {
       // do nothing
      }
     return;
    }
  
  switch( state )
    {
     case State_Beg        : put_Beg(token); break;
     case State_Name       : put_Name(token); break;
     case State_Kinds      : put_Kinds(token); break;
     case State_NextKind   : put_NextKind(token); break;
     case State_EndKind    : put_EndKind(token); break;
     case State_Rules      : put_Rules(token); break;
     case State_RuleEnd    : put_RuleEnd(token); break;
     case State_RuleIf     : put_RuleIf(token); break;
     case State_RuleCond   : put_RuleCond(token); break;
     case State_RuleName   : put_RuleName(token); break;
     case State_Result     : put_Result(token); break;
     case State_ResultName : put_ResultName(token); break;
    }
 }

template <class Action> 
void Parser<Action>::run(StrLen text)
 {
  Tokenizer tok(text);

  while( +tok )
    {
     if( isNextRelaxed() )
       put(tok.next_relaxed());
     else
       put(tok.next());
    }
  
  put(Token(tok.getPos()));
 }

} // namespace LangParser
} // namespace App

#endif
