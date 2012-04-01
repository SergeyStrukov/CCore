/* Parser.h */ 
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

#ifndef Regen_Parser_h
#define Regen_Parser_h

#include <CCore/inc/ElementPool.h>

#include "HashMap.h"
#include "Token.h"

namespace App {

/* classes */ 

//enum RegMode;

template <class T> struct ListBase;

//enum AtomClass;

struct Atom;

class Parser;

/* enum RegMode */ 

enum RegMode
 {
  RegMode_Hidden = 0,
  
  RegMode_RO = 1,
  RegMode_WO = 2,
  RegMode_RW = 3 // RegMode_RO|RegMode_WO 
 };
 
const char * GetTextDesc(RegMode mode);

inline bool IsReadable(RegMode mode) { return mode&RegMode_RO; }

inline bool IsWriteable(RegMode mode) { return mode&RegMode_WO; }

/* struct ListBase<T> */ 

template <class T> 
struct ListBase : NoCopy
 {
  T *next;

  ListBase() : next(0) {}
 
  class Builder;
 };
 
template <class T> 
class ListBase<T>::Builder : NoCopy
 {
   ListBase<T> list;
   ListBase<T> *last;

  public:

   Builder() { last=&list; }
 
   T * get() const { return list.next; }
 
   void add(T *obj) // obj->next==0
    {
     last->next=obj;
     last=obj;
    }
 
   T * add_dirty(T *obj)
    {
     T *ret=Replace_null(obj->next);

     add(obj);

     return ret;
    }
 };
 
/* enum AtomClass */ 

enum AtomClass
 {
  AtomNull = 0,
  
  // keywords

  Atom_reg,
  Atom_bar,
  Atom_index,
  Atom_address,

  Atom_RO,
  Atom_RW,
  Atom_WO,
  Atom_hidden,
  
  Atom_as,

  // punct

  Atom_begin,    // {
  Atom_end,      // }
  Atom_is,       // :
  Atom_next,     // .
  Atom_blank,    // *
  Atom_set,      // =
  Atom_plus,     // +
  Atom_to,       // -
  Atom_block,    // [
  Atom_endblock, // ]

  // common

  Atom_name,
  Atom_number,

  Atom_other
 };
 
/* struct Atom */ 

struct Atom : ListBase<Atom>
 {
  Token token;
  AtomClass ac;
  
  static AtomClass GetErrorClass(const Token &token);
  
  static AtomClass GetWordClass(StrLen str,const Token &token);
  
  static AtomClass GetPunctClass(StrLen str,const Token &token);
  
  static AtomClass GetClass(const Token &token);

  Atom() : ac(AtomNull) {}
 
  explicit Atom(const Token &token_) : token(token_),ac(GetClass(token_)) {}
 
  bool getNumber(uint32 &ret) const
   {
    TokenNumber number;

    bool ok=number.set(token);

    ret=number;

    return ok;
   }
 
  bool getNumber(uint32 &ret,uint32 next) const
   {
    if( ac==Atom_next )
      {
       ret=next;

       return true;
      }

    return getNumber(ret);
   }
 
  template <class T,class Map>
  bool bind(T * &ret,Map &map) const
   {
    auto result=map.find(token.str);

    if( result.found ) 
      {
       ret=result.obj;

       return true;
      }

    ret=0;

    Printf(Error,"Undefine name #;\n",token);

    return false;
   }
 
  static Atom NotUsed;
 };
 
/* namespace Element */ 

namespace Element {

/* classes */

struct Field_Name;

struct Reg_Field;

struct Reg;

struct Bar_Reg;

struct Bar;

/* struct Field_Name */

struct Field_Name : ListBase<Field_Name>
 {
  //
  // name = value
  //
  
  const Atom &name;
  const Atom &value;

  uint32 value_number;

  Field_Name(const Atom &name_,const Atom &value_)
   : name(name_),
     value(value_),
     value_number(0) 
   {
   }
  
  bool setValue(uint32 bitlen);
 };

/* struct Reg_Field */
 
struct Reg_Field : ListBase<Reg_Field>
 {
  //
  // name : bit             
  //
  // name : .              
  //
  // name : bit1 - bit2    [ { *<Field_Name> } ]
  //
  // name : . + len        [ { *<Field_Name> } ]
  //
  
  const Atom &name; // name or blank

  enum Type
   {
    Type_number,
    Type_next,
    Type_number_to_number,
    Type_next_plus_number
   };
 
  Type type;

  const Atom &number1;
  const Atom &number2;

  Atom *body;
  Field_Name *name_list; 

  uint32 bit;
  uint32 bitlen;
  
  void clear()
   {
    name_list=0;
    bit=0;
    bitlen=0;
   }

  Reg_Field(const Atom &name_,Type type_,Atom *body_) // Type_next
   : name(name_),
     type(type_),
     number1(Atom::NotUsed),
     number2(Atom::NotUsed),
     body(body_) 
   { 
    clear(); 
   }
 
  Reg_Field(const Atom &name_,Type type_,const Atom &number1_,Atom *body_) // Type_number , Type_next_plus_number
   : name(name_),
     type(type_),
     number1(number1_),
     number2(Atom::NotUsed),
     body(body_) 
   { 
    clear(); 
   }
 
  Reg_Field(const Atom &name_,Type type_,const Atom &number1_,const Atom &number2_,Atom *body_) // Type_number_to_number
   : name(name_),
     type(type_),
     number1(number1_),
     number2(number2_),
     body(body_) 
   { 
    clear(); 
   }
  
  bool setBit(uint32 length,uint32 &next_bit);
 };

/* struct Reg */

struct Reg : ListBase<Reg>
 {
  //
  // reg name : length { *<Reg_Field> }
  //
  
  const Atom &reg;
  const Atom &name;
  const Atom &length;

  Atom *body;
  Reg_Field *field_list;

  uint32 length_number;

  Reg(const Atom &reg_,const Atom &name_,const Atom &length_,Atom *body_)
   : reg(reg_),
     name(name_),
     length(length_),
     body(body_),
     field_list(0),
     length_number(0) 
   {
   }
 
  uint32 getDelta(bool address_mode) const { return address_mode?length_number/8:1; }
  
  bool setLength() { return length.getNumber(length_number); }
 };

/* struct Bar_Reg */

struct Bar_Reg : ListBase<Bar_Reg>
 {
  //
  // name [[block]] = address [mode] [as name] 
  //
  // name [[block]] = hidden
  //
  
  const Atom &name;
  const Atom &address; // number or next or NotUsed
  const Atom &block;   // number or NotUsed
  RegMode mode;
  const Atom &as_name; // name or NotUsed

  uint32 block_number;
  uint32 address_number;
  Reg *reg;

  Bar_Reg(const Atom &name_,const Atom &address_,const Atom &block_,RegMode mode_,const Atom &as_name_=Atom::NotUsed) 
   : name(name_),
     address(address_),
     block(block_),
     mode(mode_),
     as_name(as_name_),
     block_number(0),
     address_number(0),
     reg(0) 
   {
   }
  
  const Atom & getRegName() const { return as_name.ac?as_name:name; }
  
  template <class Map>
  bool bind(Map &map,uint32 &next_address,bool address_mode)
   {
    bool ok=true;
    
    if( block.ac )
      {
       if( !block.getNumber(block_number) ) ok=false;
      }
    else
      {
       block_number=1;
      }
    
    uint32 delta;
    
    if( getRegName().bind(reg,map) )
      {
       delta=reg->getDelta(address_mode);
      }
    else
      {
       delta=0;
       
       ok=false;
      }
    
    if( mode!=RegMode_Hidden )
      {
       if( !address.getNumber(address_number,next_address) ) ok=false;

       next_address=address_number+delta*block_number;
      }
    
    return ok;
   }
 };
 
/* struct Bar */

struct Bar : ListBase<Bar>
 {
  //
  // bar name : address { *<Bar_Reg> }
  //
  // bar name : index { *<Bar_Reg> }
  //
  
  const Atom &bar;
  const Atom &name;
  bool address_mode;

  Atom *body;
  Bar_Reg *reg_list;
  
  Bar(const Atom &bar_,const Atom &name_,AtomClass ac,Atom *body_)
   : bar(bar_),
     name(name_),
     address_mode( ac==Atom_address ),
     body(body_),
     reg_list(0) 
   {
   }
 };
 
} // namespace Element
 
/* class Parser */ 

class Parser : NoCopy
 {
   ElementPool pool;

   Atom *atom_list;
   Element::Reg *reg_list;
   Element::Bar *bar_list;

   HashMap<Element::Reg *> reg_map;
   HashMap<Element::Bar *> bar_map;

   bool nok;

  private:

   struct Match;
 
   bool buildAtomList(StrLen text);

   bool buildRegBarList();

   bool buildFieldBody(Element::Reg_Field *field);

   bool buildRegBody(Element::Reg *reg);

   bool buildBarBody(Element::Bar *bar);
   
   template <class Map,class Func,class Ptr>
   bool buildMap(Map &map,Func func,Ptr list);

   bool buildMap();

   bool bind(Element::Reg *reg);

   bool bind(Element::Bar *bar);

   bool bind();

  public:

   explicit Parser(StrLen text);

   ~Parser();

   bool operator + () const { return !nok; }
 
   bool operator ! () const { return nok; }
 
   // result

   class Name
    {
      StrLen str;

     public:

      Name(const Atom &atom) : str(atom.token.str) {}
 
      ulen getLen() const { return str.len; }
      
      typedef StrPrintOpt PrintOptType;
 
      template <class P>
      void print(P &out,PrintOptType opt) const
       {
        Putobj(out,BindOpt(opt,str));
       }
    };
 
   template <class T>
   class Cursor : public T
    {
      using T::ptr;

     public:

      template <class S>
      Cursor(S ptr_) : T(ptr_) {}
 
      bool operator + () const { return ptr; }
 
      bool operator ! () const { return !ptr; }
 
      void operator ++ () { ptr=ptr->next; }
    };
 
   class RegFieldNameProp
    {
     protected:

      Element::Field_Name *ptr;

     public:

      RegFieldNameProp(Element::Field_Name *ptr_) : ptr(ptr_) {}
 
      // props

      Name getName() const { return ptr->name; }
 
      uint32 getValue() const { return ptr->value_number; }
    };
 
   typedef Cursor<RegFieldNameProp> RegFieldNameCursor;

   class RegFieldProp
    {
     protected:

      Element::Reg_Field *ptr;

     public:

      RegFieldProp(Element::Reg_Field *ptr_) : ptr(ptr_) {}
 
      // props

      bool isBlank() const { return ptr->name.ac==Atom_blank; }
 
      Name getName() const { return ptr->name; }
 
      uint32 getBit() const { return ptr->bit; }
 
      uint32 getBitLen() const { return ptr->bitlen; }
 
      RegFieldNameCursor getFieldNames() const { return ptr->name_list; }
    };
 
   typedef Cursor<RegFieldProp> RegFieldCursor;

   class RegProp
    {
     protected:

      Element::Reg *ptr;

     public:

      RegProp(Element::Reg *ptr_) : ptr(ptr_) {}
 
      // props

      Name getName() const { return ptr->name; }
 
      uint32 getBitLen() const { return ptr->length_number; }
      
      uint32 getDelta(bool address_mode) const { return ptr->getDelta(address_mode); }
 
      RegFieldCursor getFields() const { return ptr->field_list; }
    };
 
   typedef Cursor<RegProp> RegCursor;

   RegCursor getRegs() const { return reg_list; }
 
   class BarRegProp
    {
     protected:

      Element::Bar_Reg *ptr;

     public:

      BarRegProp(Element::Bar_Reg *ptr_) : ptr(ptr_) {}
 
      // props

      Name getName() const { return ptr->name; }
      
      bool isBlock() const { return ptr->block.ac; }
      
      uint32 getBlock() const { return ptr->block_number; }
 
      uint32 getAddress() const { return ptr->address_number; }
 
      RegMode getMode() const { return ptr->mode; }
      
      bool getAs() const { return ptr->as_name.ac; }
 
      RegProp getProp() const { return ptr->reg; }
    };
 
   typedef Cursor<BarRegProp> BarRegCursor;

   class BarProp
    {
     protected:

      Element::Bar *ptr;

     public:

      BarProp(Element::Bar *ptr_) : ptr(ptr_) {}
 
      // props

      Name getName() const { return ptr->name; }
      
      bool getAddressMode() const { return ptr->address_mode; }
 
      BarRegCursor getRegs() const { return ptr->reg_list; }
    };
 
   typedef Cursor<BarProp> BarCursor;

   BarCursor getBars() const { return bar_list; }
 };
 
} // namespace App
 
#endif

