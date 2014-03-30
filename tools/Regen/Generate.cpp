/* Generate.cpp */ 
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

#include "Generate.h"

#include <CCore/inc/Path.h>

namespace App {

/* functions */ 

#if 0

void Generate(const Parser &parser,StrLen file_name)
 {
  PrintFile out(file_name);

  for(auto reg=parser.getRegs(); +reg ;++reg)
    {
     Printf(out,"reg #; : #;\n {",reg.getName(),reg.getBitLen());

     for(auto field=reg.getFields(); +field ;++field)
       {
        if( field.isBlank() ) continue;

        if( field.getBitLen()>1 )
          Printf(out,"\n  #; : #; + #;",field.getName(),field.getBit(),field.getBitLen());
        else
          Printf(out,"\n  #; : #;",field.getName(),field.getBit());

        auto fname=field.getFieldNames();

        if( +fname )
          {
           Printf(out,"\n   {");

           for(; +fname ;++fname)
             Printf(out,"\n    #; = #;",fname.getName(),fname.getValue());

           Printf(out,"\n   }");
          }
       }

     Printf(out,"\n }\n\n");
    }

  for(auto bar=parser.getBars(); +bar ;++bar)
    {
     Printf(out,"bar #;\n {",bar.getName());

     for(auto reg=bar.getRegs(); +reg ;++reg)
       {
        if( reg.isBlock() )
          {
           uint32 block=reg.getBlock();
           
           if( reg.getAs() )
             Printf(out,"\n  #; [#;] = #; #; as #;",reg.getName(),block,reg.getAddress(),reg.getMode(),reg.getProp().getName());
           else
             Printf(out,"\n  #; [#;] = #; #;",reg.getName(),block,reg.getAddress(),reg.getMode());
          }
        else
          {
           if( reg.getAs() )
             Printf(out,"\n  #; = #; #; as #;",reg.getName(),reg.getAddress(),reg.getMode(),reg.getProp().getName());
           else
             Printf(out,"\n  #; = #; #;",reg.getName(),reg.getAddress(),reg.getMode());
          }
       }

     Printf(out,"\n }\n\n");
    }
 }
 
#else

namespace Private_Generate {

struct IntValueOpt : IntPrintOpt
 {
  template <class T>
  explicit IntValueOpt(T bitlen)
   {
    base=16;
    align=IntAlignInternal;
    show_base=IntShowBasePrefix;

    switch( bitlen )
      {
       case 8  : width=4;  break;
       case 16 : width=6;  break;
       default : width=10; break;
      }
   }
 };

struct IntFieldOpt : IntPrintOpt
 {
  template <class T>
  explicit IntFieldOpt(T fbitlen)
   {
    base=16;
    align=IntAlignInternal;
    show_base=IntShowBasePrefix;

    if( fbitlen<=8 )
      width=4;
    else if( fbitlen<=12 )
      width=5;
    else if( fbitlen<=16 )
      width=6;
    else if( fbitlen<=20 )
      width=7;
    else if( fbitlen<=24 )
      width=8;
    else
      width=10;
   }
 };

template <class Reg,class Out>
void GenerateReg(Reg reg,Out &out)
 {
  auto name=reg.getName();
  auto bitlen=reg.getBitLen();

  if( !reg.getFields() )
    {
     Printf(out,"/* type Type_#; */ \n\n",name);

     Printf(out,"typedef uint#; Type_#;;\n\n",bitlen,name);

     return;
    }

  IntValueOpt value_opt(bitlen);
  
  ulen bit_count=0;
  ulen field_count=0;
  ulen nfield_count=0;

  ulen max_bitname_len=0;

  for(auto field=reg.getFields(); +field ;++field)
    {
     if( field.isBlank() ) continue;

     if( !field.getFieldNames() )
       {
        if( field.getBitLen()==1 ) 
          {
           bit_count++;

           Replace_max(max_bitname_len,field.getName().getLen());
          }
        else
          {
           field_count++;
          }
       }
     else
       {
        nfield_count++;
       }
    }

  Printf(out,"/* struct Type_#; */ \n\n",name);

  if( bit_count )
    {
     Printf(out,"enum Bits_#; : uint#;\n",name,bitlen);
     Printf(out," {\n");

     ulen i=bit_count;

     for(auto field=reg.getFields(); +field ;++field)
       {
        if( field.isBlank() ) continue;

        if( !field.getFieldNames() && field.getBitLen()==1 ) 
          {
           ulen extra=max_bitname_len-field.getName().getLen();

           Printf(out,"  #;_#;#; = #;",name,field.getName(),RepeatChar(extra,' '),BindOpt(value_opt,uint32(1)<<field.getBit()));

           if( --i )
             Printf(out,",\n");
           else
             Printf(out,"\n");
          }
       }

     Printf(out," };\n \n");

     Printf(out,"inline Bits_#; operator | (Bits_#; a,Bits_#; b)\n",name,name,name);
     Printf(out," { return Bits_#;(uint#;(a)|uint#;(b)); }\n \n",name,bitlen,bitlen);
    }

  if( nfield_count )
    {
     for(auto field=reg.getFields(); +field ;++field)
       {
        if( field.isBlank() ) continue;

        if( +field.getFieldNames() )
          {
           auto field_name=field.getName();
           auto fbitlen=field.getBitLen();

           IntFieldOpt field_opt(fbitlen);

           ulen i=0;
           ulen max_namelen=0;

           for(auto fname=field.getFieldNames(); +fname ;++fname)
             {
              i++;

              Replace_max(max_namelen,fname.getName().getLen());
             }

           Printf(out,"enum Field_#;_#; : uint#;\n",name,field_name,bitlen);
           Printf(out," {\n");

           for(auto fname=field.getFieldNames(); +fname ;++fname)
             {
              ulen extra=max_namelen-fname.getName().getLen();
              
              Printf(out,"  #;_#;_#;#; = #;",name,field_name,fname.getName(),RepeatChar(extra,' '),BindOpt(field_opt,fname.getValue()));

              if( --i )
                Printf(out,",\n");
              else
                Printf(out,"\n");
             }

           Printf(out," };\n \n");

           Printf(out,"struct PrintField_#;_#;\n",name,field_name);
           Printf(out," {\n");
           Printf(out,"  Field_#;_#; field;\n\n",name,field_name);

           Printf(out,"  explicit PrintField_#;_#;(Field_#;_#; field_) : field(field_) {}\n \n",name,field_name,name,field_name);

           Printf(out,"  template <class P>\n");
           Printf(out,"  void print(P &out) const\n");
           Printf(out,"   {\n");
           Printf(out,"    switch( field )\n");
           Printf(out,"      {\n");

           for(auto fname=field.getFieldNames(); +fname ;++fname)
             {
              Printf(out,"       case #; : Putobj(out,#.q;); break;\n",BindOpt(field_opt,fname.getValue()),fname.getName());
             }

           Printf(out,"\n       default: Putobj(out,uint#;(field));\n",bitlen);
           Printf(out,"      }\n");
           Printf(out,"   }\n");
           Printf(out," };\n \n");

           Printf(out,"inline PrintField_#;_#; GetTextDesc(Field_#;_#; field)\n",name,field_name,name,field_name);
           Printf(out," {\n");
           Printf(out,"  return PrintField_#;_#;(field);\n",name,field_name);
           Printf(out," }\n \n");
          }
       }
    }

  Printf(out,"struct Type_#;\n",name);
  Printf(out," {\n");
  Printf(out,"  typedef uint#; Type;\n\n",bitlen);

  Printf(out,"  Type value;\n\n\n");


  Printf(out,"  explicit Type_#;(Type value_=0) : value(value_) {}\n \n\n",name);


  Printf(out,"  operator Type() const { return value; }\n \n");

  Printf(out,"  void operator = (Type value_) { value=value_; }\n \n");

  Printf(out,"  template <class Bar>\n");
  Printf(out,"  Type_#; & setTo(Bar &bar) { bar.set_#;(*this); return *this; }\n \n\n",name,name);

  Printf(out,"  template <class Bar>\n");
  Printf(out,"  Type_#; & setTo(Bar &bar,uint32 ind) { bar.set_#;(ind,*this); return *this; }\n \n\n",name,name);
  
  Printf(out,"  template <class T>\n");
  Printf(out,"  Type_#; & set(T to) { to(*this); return *this; }\n \n\n",name);
  
  if( bit_count )
    {
     Printf(out,"  Type_#; & setbit(Bits_#; bits) { value|=Type(bits); return *this; }\n \n",name,name);

     Printf(out,"  Type_#; & setbitIf(bool cond,Bits_#; bits) { if( cond ) value|=Type(bits); return *this; }\n \n",name,name);

     Printf(out,"  Type_#; & clearbit(Bits_#; bits) { value&=~Type(bits); return *this; }\n \n",name,name);

     Printf(out,"  Type_#; & clearbitIf(bool cond,Bits_#; bits) { if( cond ) value&=~Type(bits); return *this; }\n \n",name,name);

     Printf(out,"  Type maskbit(Bits_#; bits) const { return value&bits; }\n \n",name);

     Printf(out,"  bool testbit(Bits_#; bits) const { return (value&bits)==Type(bits); }\n \n\n",name);
    }

  for(auto field=reg.getFields(); +field ;++field)
    {
     if( field.isBlank() ) continue;

     auto field_name=field.getName();

     auto bit=field.getBit();
     auto fbitlen=field.getBitLen();

     uint32 mask;
     
     if( fbitlen<32 )
       mask=(uint32(1)<<fbitlen)-1;
     else
       mask=uint32(-1);

     uint32 zmask=~(mask<<bit);

     if( !field.getFieldNames() )
       {
        if( field.getBitLen()==1 ) continue;

        Printf(out,"  Type get_#;() const\n",field_name);
        Printf(out,"   {\n");
        Printf(out,"    return (value>>#;)&#.x;;\n",bit,mask);
        Printf(out,"   }\n \n");

        Printf(out,"  Type_#; & set_#;(Type field)\n",name,field_name);
        Printf(out,"   {\n");
        Printf(out,"    value=((field&#.x;)<<#;)|(value&#.x;);\n\n",mask,bit,zmask);

        Printf(out,"    return *this;\n");
        Printf(out,"   }\n \n\n");
       }
     else
       {
        Printf(out,"  Field_#;_#; get_#;() const\n",name,field_name,field_name);
        Printf(out,"   {\n");
        Printf(out,"    return Field_#;_#;((value>>#;)&#.x;);\n",name,field_name,bit,mask);
        Printf(out,"   }\n \n");

        Printf(out,"  Type_#; & set_#;(Field_#;_#; field)\n",name,field_name,name,field_name);
        Printf(out,"   {\n");
        Printf(out,"    value=((Type(field)&#.x;)<<#;)|(value&#.x;);\n\n",mask,bit,zmask);

        Printf(out,"    return *this;\n");
        Printf(out,"   }\n \n\n");
       }
    }

  Printf(out,"  template <class P>\n");
  Printf(out,"  void print(P &out) const\n");
  Printf(out,"   {\n");
  Printf(out,"    bool first=true;\n\n");

  for(auto field=reg.getFields(); +field ;++field)
    {
     if( field.isBlank() ) continue;

     if( !field.getFieldNames() && field.getBitLen()==1 )
       {
        auto field_name=field.getName();

        Printf(out,"    if( value&#;_#; )\n",name,field_name);
        Printf(out,"      {\n");
        Printf(out,"       if( first )\n");
        Printf(out,"         {\n");
        Printf(out,"          Putobj(out,#.q;);\n\n",field_name);

        Printf(out,"          first=false;\n");
        Printf(out,"         }\n");
        Printf(out,"       else\n");
        Printf(out,"         {\n");
        Printf(out,"          out.put('|');\n\n");
        
        Printf(out,"          Putobj(out,#.q;);\n",field_name);
        Printf(out,"         }\n");
        Printf(out,"      }\n\n");
       }
    }

  for(auto field=reg.getFields(); +field ;++field)
    {
     if( field.isBlank() ) continue;

     if( +field.getFieldNames() || field.getBitLen()!=1 )
       {
        auto field_name=field.getName();

        Printf(out,"    if( first )\n");
        Printf(out,"      {\n");
        Printf(out,"       Printf(out,\"#;(##;)\",get_#;());\n\n",field_name,field_name);

        Printf(out,"       first=false;\n");
        Printf(out,"      }\n");
        Printf(out,"    else\n");
        Printf(out,"      {\n");
        Printf(out,"       out.put('|');\n\n");
        
        Printf(out,"       Printf(out,\"#;(##;)\",get_#;());\n",field_name,field_name);
        Printf(out,"      }\n\n");
       }
    }

  Printf(out,"    if( first ) out.put('0');\n");
  Printf(out,"   }\n");

  Printf(out," };\n \n");
 }
 
template <class Bar,class Out>
void GenerateBar(Bar bar,Out &out)
 {
  auto name=bar.getName();
  auto address_mode=bar.getAddressMode();

  Printf(out,"/* struct #;<RW> */ \n\n",name);

  Printf(out,"template <class RW>\n");
  Printf(out,"struct #;\n",name);
  Printf(out," {\n");
  Printf(out,"  RW rw;\n\n");

  Printf(out,"  template <class ... TT>\n");
  Printf(out,"  #;(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}\n \n",name);
  
  Printf(out,"  template <class T>\n");
  Printf(out,"  struct Setter\n");
  Printf(out,"   {\n");
  Printf(out,"    RW &rw;\n");
  Printf(out,"    uint32 address;\n\n");
  
  Printf(out,"    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}\n\n");
  
  Printf(out,"    void operator () (T value) { rw.set(address,value.value); }\n");
  Printf(out,"   };\n\n");

  for(auto reg=bar.getRegs(); +reg ;++reg)
    {
     auto name=reg.getName();
     auto address=reg.getAddress();
     auto mode=reg.getMode();
     auto regname=reg.getProp().getName();
     auto bitlen=reg.getProp().getBitLen();
     auto delta=reg.getProp().getDelta(address_mode);
     bool is_block=reg.isBlock();
     bool has_type=+reg.getProp().getFields();
     bool isReadable=IsReadable(mode);
     bool isWriteable=IsWriteable(mode);

     Printf(out,"  //--- #;\n\n",name);

     if( is_block )
       {
        if( isReadable )
          {
           Printf(out,"  Type_#; get_#;(uint32 ind) { return Type_#;(rw.template get<uint#;>(#.x; +ind*#;)); }\n \n",regname,name,regname,bitlen,address,delta);
          }

        if( isWriteable )
          {
           if( has_type )
             {
              Printf(out,"  void set_#;(uint32 ind,Type_#; value) { rw.set(#.x; +ind*#;,value.value); }\n \n",name,regname,address,delta);
              
              Printf(out,"  Setter<Type_#;> to_#;(uint32 ind) { return Setter<Type_#;>(rw,#.x; +ind*#;); }\n \n",regname,name,regname,address,delta);
             }
           else
             {
              Printf(out,"  void set_#;(uint32 ind,Type_#; value) { rw.set(#.x; +ind*#;,value); }\n \n",name,regname,address,delta);
             }
          }
       }
     else
       {
        if( isReadable )
          {
           Printf(out,"  Type_#; get_#;() { return Type_#;(rw.template get<uint#;>(#.x;)); }\n \n",regname,name,regname,bitlen,address);
          }

        if( isWriteable )
          {
           if( has_type )
             {
              Printf(out,"  void set_#;(Type_#; value) { rw.set(#.x;,value.value); }\n \n",name,regname,address);
              
              Printf(out,"  Setter<Type_#;> to_#;() { return Setter<Type_#;>(rw,#.x;); }\n \n",regname,name,regname,address);
             }
           else
             {
              Printf(out,"  void set_#;(Type_#; value) { rw.set(#.x;,value); }\n \n",name,regname,address);
             }
          }
       }
     
     if( has_type )
       {
        if( !reg.getAs() )
          {
           Printf(out,"  static Type_#; null_#;() { return Type_#;(0); }\n \n",regname,name,regname);

           Printf(out,"  static Type_#; ones_#;() { return Type_#;(Type_#;::Type(-1)); }\n \n",regname,name,regname,regname);
          }
       }
     else
       {
        if( isWriteable )
          {
           if( is_block )
             {
              Printf(out,"  void set_#;_null(uint32 ind) { rw.set(#.x; +ind*#;,Type_#;(0)); }\n \n",name,address,delta,regname);

              Printf(out,"  void set_#;_ones(uint32 ind) { rw.set(#.x; +ind*#;,Type_#;(-1)); }\n \n",name,address,delta,regname);
             }
           else
             {
              Printf(out,"  void set_#;_null() { rw.set(#.x;,Type_#;(0)); }\n \n",name,address,regname);

              Printf(out,"  void set_#;_ones() { rw.set(#.x;,Type_#;(-1)); }\n \n",name,address,regname);
             }
          }
       }
    }

  Printf(out," };\n \n");
 }
 
} // namespace Private_Generate
 
using namespace Private_Generate;
 
void Generate(const Parser &parser,StrLen file_name)
 {
  PrintFile out(file_name);
  
  SplitPath split_path(file_name);
  SplitName split_name(split_path.path);

  Printf(out,"/* #; */ \n\n",split_name.name);

  for(auto reg=parser.getRegs(); +reg ;++reg) GenerateReg(reg,out);

  for(auto bar=parser.getBars(); +bar ;++bar) GenerateBar(bar,out);
 }
 
#endif
 
} // namespace App
 
