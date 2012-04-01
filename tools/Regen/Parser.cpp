/* Parser.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: Regen 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "Parser.h"

#include <CCore/inc/Abort.h>

namespace App {

/* enum RegMode */ 

const char * GetTextDesc(RegMode mode)
 {
  switch( mode )
    {
     case RegMode_Hidden : return "hidden";
     
     case RegMode_RO : return "RO";
     case RegMode_WO : return "WO";
     case RegMode_RW : return "RW";

     default: return "???";
    }
 }
 
/* struct Atom */ 

AtomClass Atom::GetErrorClass(const Token &token)
 {
  Printf(Error,"Internal error: unexpected token #;\n",token);
  
  return Atom_other;
 }

AtomClass Atom::GetWordClass(StrLen str,const Token &token)
 {
  if( str.len==0 ) return GetErrorClass(token);
  
  switch( str[0] )
    {
     case 'r' : // reg
      {
       if( str.len==3 && str[1]=='e' && str[2]=='g' ) return Atom_reg;
      }
     break;

     case 'b' : // bar
      {
       if( str.len==3 && str[1]=='a' && str[2]=='r' ) return Atom_bar;
      }
     break;

     case 'i' : // index
      {
       if( str.len==5 && str[1]=='n' && str[2]=='d' && str[3]=='e' && str[4]=='x' ) return Atom_index;
      }
     break;

     case 'a' : // as address
      {
       if( str.len==2 && str[1]=='s' ) return Atom_as;
       
       if( str.len==7 && str[1]=='d' && str[2]=='d' && str[3]=='r' && str[4]=='e' && str[5]=='s' && str[6]=='s' ) return Atom_address;
      }
     break;

     case 'R' : // RO RW
      {
       if( str.len==2 ) 
         {
          if( str[1]=='O' ) return Atom_RO;
            
          if( str[1]=='W' ) return Atom_RW;
         }
      }
     break;

     case 'W' : // WO
      {
       if( str.len==2 && str[1]=='O' ) return Atom_WO;
      }
     break;
     
     case 'h' : // hidden
      {
       if( str.len==6 && str[1]=='i' && str[2]=='d' && str[3]=='d' && str[4]=='e' && str[5]=='n' ) return Atom_hidden;
      }
     break;
    }
  
  return Atom_name;
 }

AtomClass Atom::GetPunctClass(StrLen str,const Token &token)
 {
  if( str.len!=1 ) return GetErrorClass(token);
  
  switch( str[0] )
    {
     case '{' : return Atom_begin;
     case '}' : return Atom_end;
     case ':' : return Atom_is;
     case '.' : return Atom_next;
     case '*' : return Atom_blank;
     case '=' : return Atom_set;  
     case '+' : return Atom_plus; 
     case '-' : return Atom_to;   
     case '[' : return Atom_block;
     case ']' : return Atom_endblock;
     
     default: return GetErrorClass(token);
    }
 }

AtomClass Atom::GetClass(const Token &token)
 {
  switch( token.tc )
    {
     case Token_Number : return Atom_number;
     case Token_Word   : return GetWordClass(token.str,token);
     case Token_Punct  : return GetPunctClass(token.str,token);
     
     default: return Atom_other;
    }
 }

Atom Atom::NotUsed;

/* namespace Element */ 

namespace Element {

/* struct Field_Name */

bool Field_Name::setValue(uint32 bitlen)
 {
  bool ok=true;
  
  if( !value.getNumber(value_number) ) ok=false;

  if( bitlen<32 && (value_number>>bitlen) )
    {
     Printf(Error,"Error: bad field value #;\n",name.token);

     ok=false;
    }
  
  return ok;
 }

/* struct Reg_Field */

bool Reg_Field::setBit(uint32 length,uint32 &next_bit)
 {
  bool ok=true;
  
  switch( type )
    {
     case Type_number :
      {
       if( !number1.getNumber(bit) ) ok=false;

       bitlen=1;
      }
     break;

     case Type_next :
      {
       bit=next_bit;
       
       bitlen=1;
      }
     break;

     case Type_next_plus_number :
      {
       bit=next_bit;
       
       if( !number1.getNumber(bitlen) ) ok=false;
      }
     break;

     case Type_number_to_number :
      {
       uint32 last;

       if( !number1.getNumber(bit) ) ok=false;

       if( !number2.getNumber(last) ) ok=false;

       bitlen=last-bit+1;
      }
     break;
    }
  
  next_bit=bit+bitlen;
  
  if( bit>=length || bitlen>length-bit || bitlen==0 ) 
    {
     Printf(Error,"Error: bad bit number(s) #;\n",name.token);
     
     ok=false;
    }

  return ok;
 }

} // namespace Element
 
/* class Parser */ 

struct Parser::Match
 {
  Atom *atom;

  explicit Match(Atom *atom_) : atom(atom_) {}

  AtomClass probe(AtomClass ac)
   {
    if( atom->ac==ac )
      {
       atom=atom->next;

       return ac;
      }

    return AtomNull;
   }

  template <class ... AC>
  AtomClass probe(AtomClass ac,AC ... extra)
   {
    if( AtomClass ret=probe(ac) ) return ret;

    return probe(extra...);
   }

  bool step(AtomClass ac)
   {
    if( atom->ac==ac )
      {
       atom=atom->next;

       return true;
      }

    return false;
   }

  template <class ... AC>
  bool step(AtomClass ac,AC ... extra)
   {
    if( step(ac) ) return step(extra...);

    return false;
   }

  template <class ... AC>
  bool pass(AC ... ac)
   {
    Atom *a=atom;
    
    if( step(ac...) ) return true;
    
    atom=a;
    
    return false;
   }
  
  bool end()
   {
    ulen count=1;

    for(; AtomClass ac=atom->ac ;atom=atom->next)
      {
       if( ac==Atom_begin ) 
         {
          count++;
         }
       else if( ac==Atom_end )
         {
          count--;

          if( count==0 )
            {
             atom=Replace_null(atom->next);

             return true;
            }
         }
      }

    return false;
   }
 };
  
bool Parser::buildAtomList(StrLen text)
 {
  Tokenizer tok(text);

  Atom::Builder builder;
  Atom::Builder other_builder;

  while( +tok )
    {
     Token token=tok.next();
     TokenClass tc=token.tc;
     
     if( IsSignificantToken(tc) )
       {
        Atom *atom=pool.create<Atom>(token);

        if( atom->ac==Atom_other )
          other_builder.add(atom);
        else
          builder.add(atom);
       }
     else if( tc==Token_Other )
       {
        Atom *atom=pool.create<Atom>(token);
        
        other_builder.add(atom);
       }
    }

  builder.add(pool.create<Atom>());

  atom_list=builder.get();

  if( Atom *atom=other_builder.get() ) 
    {
     for(; atom ;atom=atom->next)
       {
        Printf(Error,"Error: invalid token #;\n",atom->token);
       }

     Printf(Error,"\n--- Tokenizing phase ---\n\n");

     nok=true;

     return false;
    }

  return true;
 }
 
bool Parser::buildRegBarList()
 {
  Atom *atom=Replace_null(atom_list);

  Element::Reg::Builder reg_builder;
  Element::Bar::Builder bar_builder;
  Atom::Builder error_builder;

  while( atom->ac!=AtomNull )
    {
     Match match(atom);

     switch( match.probe(Atom_reg,Atom_bar) )
       {
        case Atom_reg :
         {
          if( match.step(Atom_name,Atom_is,Atom_number,Atom_begin) && match.end() )
            {
             Atom *atom0=atom;        // reg 
             Atom *atom1=atom0->next; // name
             Atom *atom2=atom1->next; // :
             Atom *atom3=atom2->next; // number
             Atom *atom4=atom3->next; // {
             Atom *atom5=atom4->next; //  body

             reg_builder.add(pool.create<Element::Reg>(*atom0,*atom1,*atom3,atom5));

             atom=match.atom;

             continue;
            }
         }
        break;

        case Atom_bar :
         {
          if( match.step(Atom_name,Atom_is) && match.probe(Atom_index,Atom_address) && match.step(Atom_begin) && match.end() )
            {
             Atom *atom0=atom;        // bar
             Atom *atom1=atom0->next; // name
             Atom *atom2=atom1->next; // :
             Atom *atom3=atom2->next; // address or index 
             Atom *atom4=atom3->next; // {
             Atom *atom5=atom4->next; //  body

             bar_builder.add(pool.create<Element::Bar>(*atom0,*atom1,atom3->ac,atom5));

             atom=match.atom;
             
             continue;
            }
         }
        break;
       }

     atom=error_builder.add_dirty(atom);
    }

  reg_list=reg_builder.get();
  bar_list=bar_builder.get();

  if( Atom *atom=error_builder.get() )
    {
     for(; atom ;atom=atom->next)
       {
        Printf(Error,"Error: unrecognized declaration #;\n",atom->token);
       }

     Printf(Error,"\n--- Parsing reg-and-bar declaration phase ---\n\n");

     nok=true;

     return false;
    }

  return true;
 }
 
bool Parser::buildFieldBody(Element::Reg_Field *field)
 {
  Atom *atom=Replace_null(field->body);

  if( !atom )
    {
     field->name_list=0;

     return true;
    }

  Element::Field_Name::Builder builder;
  Atom::Builder error_builder;

  while( atom->ac!=Atom_end )
    {
     Match match(atom);
     
     if( match.step(Atom_name,Atom_set,Atom_number) )
       {
        Atom *atom0=atom;        // name
        Atom *atom1=atom->next;  // =
        Atom *atom2=atom1->next; // number 
        
        builder.add(pool.create<Element::Field_Name>(*atom0,*atom2));
        
        atom=match.atom;
        
        continue;
       }

     atom=error_builder.add_dirty(atom);
    }

  field->name_list=builder.get();

  if( Atom *atom=error_builder.get() )
    {
     for(; atom ;atom=atom->next)
       {
        Printf(Error,"Error: unrecognized field name declaration #;\n",atom->token);
       }

     Printf(Error,"\n--- Parsing field #; body phase ---\n\n",field->name.token);

     nok=true;

     return false;
    }

  return true;
 }
 
bool Parser::buildRegBody(Element::Reg *reg)
 {
  Atom *atom=Replace_null(reg->body);

  Element::Reg_Field::Builder builder;
  Atom::Builder error_builder;

  while( atom->ac!=Atom_end )
    {
     Match match(atom);
     
     if( match.probe(Atom_name,Atom_blank) && match.step(Atom_is) )
       {
        switch( match.probe(Atom_next,Atom_number) )
          {
           case Atom_next :
            {
             if( match.step(Atom_plus) )
               {
                if( match.step(Atom_number) )
                  {
                   Atom *atom0=atom;        // name or blank
                   Atom *atom1=atom0->next; // :
                   Atom *atom2=atom1->next; // .
                   Atom *atom3=atom2->next; // +
                   Atom *atom4=atom3->next; // number
                   Atom *body;

                   if( match.step(Atom_begin) )
                     {
                      body=match.atom;
                      
                      if( !match.end() ) Abort("App::Parser trap1");
                     }
                   else
                     {
                      body=0;
                     }

                   builder.add(pool.create<Element::Reg_Field>(*atom0,Element::Reg_Field::Type_next_plus_number,*atom4,body));

                   atom=match.atom;
                   
                   continue;
                  }
               }
             else
               {
                Atom *atom0=atom;        // name or blank
                //Atom *atom1=atom0->next; // :
                //Atom *atom2=atom1->next; // .
                Atom *body=0;

                builder.add(pool.create<Element::Reg_Field>(*atom0,Element::Reg_Field::Type_next,body));
                
                atom=match.atom;

                continue;
               }
            }
           break;
           
           case Atom_number :
            {
             if( match.step(Atom_to) )
               {
                if( match.step(Atom_number) )
                  {
                   Atom *atom0=atom;        // name or blank
                   Atom *atom1=atom0->next; // :
                   Atom *atom2=atom1->next; // number
                   Atom *atom3=atom2->next; // -
                   Atom *atom4=atom3->next; // number
                   Atom *body;

                   if( match.step(Atom_begin) )
                     {
                      body=match.atom;
                      
                      if( !match.end() ) Abort("App::Parser trap2");
                     }
                   else
                     {
                      body=0;
                     }
                   
                   builder.add(pool.create<Element::Reg_Field>(*atom0,Element::Reg_Field::Type_number_to_number,*atom2,*atom4,body));
                   
                   atom=match.atom;
                   
                   continue;
                  }
               }
             else
               {
                Atom *atom0=atom;        // name or blank
                Atom *atom1=atom0->next; // :
                Atom *atom2=atom1->next; // number
                Atom *body=0;
                
                builder.add(pool.create<Element::Reg_Field>(*atom0,Element::Reg_Field::Type_number,*atom2,body));

                atom=match.atom;
                
                continue;
               }
            }
           break;
          }
       }

     atom=error_builder.add_dirty(atom);
    }

  reg->field_list=builder.get();

  if( Atom *atom=error_builder.get() )
    {
     for(; atom ;atom=atom->next)
       {
        Printf(Error,"Error: unrecognized reg field declaration #;\n",atom->token);
       }

     Printf(Error,"\n--- Parsing reg #; body phase ---\n\n",reg->name.token);

     nok=true;

     return false;
    }

  return true;
 }
 
bool Parser::buildBarBody(Element::Bar *bar)
 {
  Atom *atom=Replace_null(bar->body);

  Element::Bar_Reg::Builder builder;
  Atom::Builder error_builder;

  while( atom->ac!=Atom_end )
    {
     Match match(atom);
     
     if( match.step(Atom_name) )
       {
        Atom *atom0=atom; // name
        Atom *atom_block;
        
        if( match.pass(Atom_block,Atom_number,Atom_endblock) )
          {
           Atom *atom1=atom0->next; // [
           Atom *atom2=atom1->next; // block
           
           atom_block=atom2;
          }
        else
          {
           atom_block=&Atom::NotUsed;
          }
        
        if( match.step(Atom_set) )
          {
           Atom *atom2=match.atom; // address 
           
           switch( match.probe(Atom_number,Atom_next,Atom_hidden) )
             {
              case Atom_number :
              case Atom_next :
               {
                RegMode mode;
                
                switch( match.probe(Atom_RO,Atom_WO,Atom_RW) )
                  {
                   case Atom_RO : mode=RegMode_RO; break;
                   case Atom_WO : mode=RegMode_WO; break;
                   case Atom_RW : mode=RegMode_RW; break;

                   default: mode=RegMode_RW; 
                  }
                
                Atom *atom3=match.atom;
                
                if( match.pass(Atom_as,Atom_name) )
                  {
                   Atom *atom4=atom3->next;
                   
                   builder.add(pool.create<Element::Bar_Reg>(*atom0,*atom2,*atom_block,mode,*atom4));
                   
                   atom=match.atom;
                   
                   continue;
                  }
                else
                  {
                   builder.add(pool.create<Element::Bar_Reg>(*atom0,*atom2,*atom_block,mode));
                   
                   atom=match.atom;
                   
                   continue;
                  }
               }
              break;
              
              case Atom_hidden :
               {
                builder.add(pool.create<Element::Bar_Reg>(*atom0,Atom::NotUsed,*atom_block,RegMode_Hidden));
                
                atom=match.atom;
                
                continue;
               }
              break;
             }
          }
       }

     atom=error_builder.add_dirty(atom);
    }

  bar->reg_list=builder.get();

  if( Atom *atom=error_builder.get() )
    {
     for(; atom ;atom=atom->next)
       {
        Printf(Error,"Error: unrecognized bar register declaration #;\n",atom->token);
       }

     Printf(Error,"\n--- Parsing bar #; body phase ---\n\n",bar->name.token);

     nok=true;

     return false;
    }

  return true;
 }
 
template <class Map,class Func,class Ptr>
bool Parser::buildMap(Map &map,Func func,Ptr list)
 {
  for(Ptr ptr=list; ptr ;ptr=ptr->next) map.add(ptr->name.token.str,ptr);
  
  if( !map.complete(func) )
    {
     nok=true;
     
     return false;
    }
  
  return true;
 }

bool Parser::buildMap()
 {
  bool ok=true;
  
  if( !buildMap(reg_map, [] (StrLen,Element::Reg *reg1,Element::Reg *reg2) 
                            {
                             Printf(Error,"Error: register name duplication\n   #;\n   #;\n",reg1->name.token,reg2->name.token);
                            }
  
                       ,reg_list) ) ok=false;

  if( !buildMap(bar_map, [] (StrLen,Element::Bar *bar1,Element::Bar *bar2)
                            {
                             Printf(Error,"Error: bar name duplication\n   #;\n   #;\n",bar1->name.token,bar2->name.token);
                            }
  
                       ,bar_list) ) ok=false;
  
  if( !ok ) 
    {
     Printf(Error,"\n--- Mapping phase ---\n\n");

     nok=true;
    }

  return ok;
 }
 
bool Parser::bind(Element::Reg *reg)
 {
  bool ok=true;

  if( !reg->setLength() ) ok=false;

  uint32 length=reg->length_number;

  if( length!=8 && length!=16 && length!=32 )
    {
     Printf(Error,"Error: invalid register bit length #;(#;)\n",reg->length.token,reg->length_number);

     ok=false;
    }

  uint32 next_bit=0;

  for(Element::Reg_Field *field=reg->field_list; field ;field=field->next)
    {
     if( !field->setBit(length,next_bit) ) ok=false;
     
     uint32 bitlen=field->bitlen;
     
     for(Element::Field_Name *fname=field->name_list; fname ;fname=fname->next)
       {
        if( !fname->setValue(bitlen) ) ok=false;
       }
    }

  return ok;
 }
 
bool Parser::bind(Element::Bar *bar)
 {
  bool ok=true;
  uint32 next_address=0;
  bool address_mode=bar->address_mode;

  for(Element::Bar_Reg *reg=bar->reg_list; reg ;reg=reg->next)
    {
     if( !reg->bind(reg_map,next_address,address_mode) )
       {
        ok=false;
       }
    }

  return ok;
 }
 
bool Parser::bind()
 {
  bool ok=true;

  for(Element::Reg *reg=reg_list; reg ;reg=reg->next)
    {
     if( !bind(reg) ) ok=false;
    }

  for(Element::Bar *bar=bar_list; bar ;bar=bar->next)
    {
     if( !bind(bar) ) ok=false;
    }

  if( !ok ) 
    {
     Printf(Error,"\n--- Bind phase ---\n\n");

     nok=true;
    }

  return ok;
 }
 
Parser::Parser(StrLen text)
 : atom_list(0),
   reg_list(0),
   bar_list(0),
   nok(false)
 {
  buildAtomList(text);

  buildRegBarList();

  for(Element::Reg *reg=reg_list; reg ;reg=reg->next)
    {
     buildRegBody(reg);

     for(Element::Reg_Field *field=reg->field_list; field ;field=field->next)
       {
        buildFieldBody(field);
       }
    }

  for(Element::Bar *bar=bar_list; bar ;bar=bar->next)
    {
     buildBarBody(bar);
    }

  buildMap();

  bind();
 }
 
Parser::~Parser()
 {
 }
 
} // namespace App
 
