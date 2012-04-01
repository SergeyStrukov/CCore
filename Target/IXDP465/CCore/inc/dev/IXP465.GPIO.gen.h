/* IXP465.GPIO.gen.h */ 

/* struct Type_Out */ 

enum Bits_Out : uint32
 {
  Out_Pin0  = 0x00000001,
  Out_Pin1  = 0x00000002,
  Out_Pin2  = 0x00000004,
  Out_Pin3  = 0x00000008,
  Out_Pin4  = 0x00000010,
  Out_Pin5  = 0x00000020,
  Out_Pin6  = 0x00000040,
  Out_Pin7  = 0x00000080,
  Out_Pin8  = 0x00000100,
  Out_Pin9  = 0x00000200,
  Out_Pin10 = 0x00000400,
  Out_Pin11 = 0x00000800,
  Out_Pin12 = 0x00001000,
  Out_Pin13 = 0x00002000,
  Out_Pin14 = 0x00004000,
  Out_Pin15 = 0x00008000
 };
 
inline Bits_Out operator | (Bits_Out a,Bits_Out b)
 { return Bits_Out(uint32(a)|uint32(b)); }
 
struct Type_Out
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Out(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Out & setTo(Bar &bar) { bar.set_Out(*this); return *this; }
 

  template <class Bar>
  Type_Out & setTo(Bar &bar,uint32 ind) { bar.set_Out(*this,ind); return *this; }
 

  template <class T>
  Type_Out & set(T to) { to(*this); return *this; }
 

  Type_Out & setbit(Bits_Out bits) { value|=Type(bits); return *this; }
 
  Type_Out & setbitIf(bool cond,Bits_Out bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Out & clearbit(Bits_Out bits) { value&=~Type(bits); return *this; }
 
  Type_Out & clearbitIf(bool cond,Bits_Out bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Out bits) const { return value&bits; }
 
  bool testbit(Bits_Out bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Out_Pin0 )
      {
       if( first )
         {
          Putobj(out,"Pin0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin0");
         }
      }

    if( value&Out_Pin1 )
      {
       if( first )
         {
          Putobj(out,"Pin1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin1");
         }
      }

    if( value&Out_Pin2 )
      {
       if( first )
         {
          Putobj(out,"Pin2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin2");
         }
      }

    if( value&Out_Pin3 )
      {
       if( first )
         {
          Putobj(out,"Pin3");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin3");
         }
      }

    if( value&Out_Pin4 )
      {
       if( first )
         {
          Putobj(out,"Pin4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin4");
         }
      }

    if( value&Out_Pin5 )
      {
       if( first )
         {
          Putobj(out,"Pin5");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin5");
         }
      }

    if( value&Out_Pin6 )
      {
       if( first )
         {
          Putobj(out,"Pin6");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin6");
         }
      }

    if( value&Out_Pin7 )
      {
       if( first )
         {
          Putobj(out,"Pin7");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin7");
         }
      }

    if( value&Out_Pin8 )
      {
       if( first )
         {
          Putobj(out,"Pin8");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin8");
         }
      }

    if( value&Out_Pin9 )
      {
       if( first )
         {
          Putobj(out,"Pin9");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin9");
         }
      }

    if( value&Out_Pin10 )
      {
       if( first )
         {
          Putobj(out,"Pin10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin10");
         }
      }

    if( value&Out_Pin11 )
      {
       if( first )
         {
          Putobj(out,"Pin11");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin11");
         }
      }

    if( value&Out_Pin12 )
      {
       if( first )
         {
          Putobj(out,"Pin12");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin12");
         }
      }

    if( value&Out_Pin13 )
      {
       if( first )
         {
          Putobj(out,"Pin13");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin13");
         }
      }

    if( value&Out_Pin14 )
      {
       if( first )
         {
          Putobj(out,"Pin14");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin14");
         }
      }

    if( value&Out_Pin15 )
      {
       if( first )
         {
          Putobj(out,"Pin15");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin15");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Int */ 

enum Bits_Int : uint32
 {
  Int_Pin0  = 0x00000001,
  Int_Pin1  = 0x00000002,
  Int_Pin2  = 0x00000004,
  Int_Pin3  = 0x00000008,
  Int_Pin4  = 0x00000010,
  Int_Pin5  = 0x00000020,
  Int_Pin6  = 0x00000040,
  Int_Pin7  = 0x00000080,
  Int_Pin8  = 0x00000100,
  Int_Pin9  = 0x00000200,
  Int_Pin10 = 0x00000400,
  Int_Pin11 = 0x00000800,
  Int_Pin12 = 0x00001000
 };
 
inline Bits_Int operator | (Bits_Int a,Bits_Int b)
 { return Bits_Int(uint32(a)|uint32(b)); }
 
struct Type_Int
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Int(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Int & setTo(Bar &bar) { bar.set_Int(*this); return *this; }
 

  template <class Bar>
  Type_Int & setTo(Bar &bar,uint32 ind) { bar.set_Int(*this,ind); return *this; }
 

  template <class T>
  Type_Int & set(T to) { to(*this); return *this; }
 

  Type_Int & setbit(Bits_Int bits) { value|=Type(bits); return *this; }
 
  Type_Int & setbitIf(bool cond,Bits_Int bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Int & clearbit(Bits_Int bits) { value&=~Type(bits); return *this; }
 
  Type_Int & clearbitIf(bool cond,Bits_Int bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Int bits) const { return value&bits; }
 
  bool testbit(Bits_Int bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Int_Pin0 )
      {
       if( first )
         {
          Putobj(out,"Pin0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin0");
         }
      }

    if( value&Int_Pin1 )
      {
       if( first )
         {
          Putobj(out,"Pin1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin1");
         }
      }

    if( value&Int_Pin2 )
      {
       if( first )
         {
          Putobj(out,"Pin2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin2");
         }
      }

    if( value&Int_Pin3 )
      {
       if( first )
         {
          Putobj(out,"Pin3");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin3");
         }
      }

    if( value&Int_Pin4 )
      {
       if( first )
         {
          Putobj(out,"Pin4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin4");
         }
      }

    if( value&Int_Pin5 )
      {
       if( first )
         {
          Putobj(out,"Pin5");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin5");
         }
      }

    if( value&Int_Pin6 )
      {
       if( first )
         {
          Putobj(out,"Pin6");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin6");
         }
      }

    if( value&Int_Pin7 )
      {
       if( first )
         {
          Putobj(out,"Pin7");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin7");
         }
      }

    if( value&Int_Pin8 )
      {
       if( first )
         {
          Putobj(out,"Pin8");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin8");
         }
      }

    if( value&Int_Pin9 )
      {
       if( first )
         {
          Putobj(out,"Pin9");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin9");
         }
      }

    if( value&Int_Pin10 )
      {
       if( first )
         {
          Putobj(out,"Pin10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin10");
         }
      }

    if( value&Int_Pin11 )
      {
       if( first )
         {
          Putobj(out,"Pin11");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin11");
         }
      }

    if( value&Int_Pin12 )
      {
       if( first )
         {
          Putobj(out,"Pin12");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pin12");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntType1 */ 

enum Bits_IntType1 : uint32
 {
  IntType1_InToNPE0 = 0x01000000,
  IntType1_InToNPE1 = 0x02000000,
  IntType1_InToNPE2 = 0x04000000,
  IntType1_InToNPE3 = 0x08000000,
  IntType1_InToNPE4 = 0x10000000,
  IntType1_InToNPE5 = 0x20000000,
  IntType1_InToNPE6 = 0x40000000,
  IntType1_InToNPE7 = 0x80000000
 };
 
inline Bits_IntType1 operator | (Bits_IntType1 a,Bits_IntType1 b)
 { return Bits_IntType1(uint32(a)|uint32(b)); }
 
enum Field_IntType1_Pin0 : uint32
 {
  IntType1_Pin0_Hi         = 0x00,
  IntType1_Pin0_Lo         = 0x01,
  IntType1_Pin0_Rising     = 0x02,
  IntType1_Pin0_Falling    = 0x03,
  IntType1_Pin0_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin0
 {
  Field_IntType1_Pin0 field;

  explicit PrintField_IntType1_Pin0(Field_IntType1_Pin0 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin0 GetTextDesc(Field_IntType1_Pin0 field)
 {
  return PrintField_IntType1_Pin0(field);
 }
 
enum Field_IntType1_Pin1 : uint32
 {
  IntType1_Pin1_Hi         = 0x00,
  IntType1_Pin1_Lo         = 0x01,
  IntType1_Pin1_Rising     = 0x02,
  IntType1_Pin1_Falling    = 0x03,
  IntType1_Pin1_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin1
 {
  Field_IntType1_Pin1 field;

  explicit PrintField_IntType1_Pin1(Field_IntType1_Pin1 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin1 GetTextDesc(Field_IntType1_Pin1 field)
 {
  return PrintField_IntType1_Pin1(field);
 }
 
enum Field_IntType1_Pin2 : uint32
 {
  IntType1_Pin2_Hi         = 0x00,
  IntType1_Pin2_Lo         = 0x01,
  IntType1_Pin2_Rising     = 0x02,
  IntType1_Pin2_Falling    = 0x03,
  IntType1_Pin2_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin2
 {
  Field_IntType1_Pin2 field;

  explicit PrintField_IntType1_Pin2(Field_IntType1_Pin2 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin2 GetTextDesc(Field_IntType1_Pin2 field)
 {
  return PrintField_IntType1_Pin2(field);
 }
 
enum Field_IntType1_Pin3 : uint32
 {
  IntType1_Pin3_Hi         = 0x00,
  IntType1_Pin3_Lo         = 0x01,
  IntType1_Pin3_Rising     = 0x02,
  IntType1_Pin3_Falling    = 0x03,
  IntType1_Pin3_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin3
 {
  Field_IntType1_Pin3 field;

  explicit PrintField_IntType1_Pin3(Field_IntType1_Pin3 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin3 GetTextDesc(Field_IntType1_Pin3 field)
 {
  return PrintField_IntType1_Pin3(field);
 }
 
enum Field_IntType1_Pin4 : uint32
 {
  IntType1_Pin4_Hi         = 0x00,
  IntType1_Pin4_Lo         = 0x01,
  IntType1_Pin4_Rising     = 0x02,
  IntType1_Pin4_Falling    = 0x03,
  IntType1_Pin4_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin4
 {
  Field_IntType1_Pin4 field;

  explicit PrintField_IntType1_Pin4(Field_IntType1_Pin4 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin4 GetTextDesc(Field_IntType1_Pin4 field)
 {
  return PrintField_IntType1_Pin4(field);
 }
 
enum Field_IntType1_Pin5 : uint32
 {
  IntType1_Pin5_Hi         = 0x00,
  IntType1_Pin5_Lo         = 0x01,
  IntType1_Pin5_Rising     = 0x02,
  IntType1_Pin5_Falling    = 0x03,
  IntType1_Pin5_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin5
 {
  Field_IntType1_Pin5 field;

  explicit PrintField_IntType1_Pin5(Field_IntType1_Pin5 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin5 GetTextDesc(Field_IntType1_Pin5 field)
 {
  return PrintField_IntType1_Pin5(field);
 }
 
enum Field_IntType1_Pin6 : uint32
 {
  IntType1_Pin6_Hi         = 0x00,
  IntType1_Pin6_Lo         = 0x01,
  IntType1_Pin6_Rising     = 0x02,
  IntType1_Pin6_Falling    = 0x03,
  IntType1_Pin6_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin6
 {
  Field_IntType1_Pin6 field;

  explicit PrintField_IntType1_Pin6(Field_IntType1_Pin6 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin6 GetTextDesc(Field_IntType1_Pin6 field)
 {
  return PrintField_IntType1_Pin6(field);
 }
 
enum Field_IntType1_Pin7 : uint32
 {
  IntType1_Pin7_Hi         = 0x00,
  IntType1_Pin7_Lo         = 0x01,
  IntType1_Pin7_Rising     = 0x02,
  IntType1_Pin7_Falling    = 0x03,
  IntType1_Pin7_Transition = 0x04
 };
 
struct PrintField_IntType1_Pin7
 {
  Field_IntType1_Pin7 field;

  explicit PrintField_IntType1_Pin7(Field_IntType1_Pin7 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType1_Pin7 GetTextDesc(Field_IntType1_Pin7 field)
 {
  return PrintField_IntType1_Pin7(field);
 }
 
struct Type_IntType1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_IntType1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IntType1 & setTo(Bar &bar) { bar.set_IntType1(*this); return *this; }
 

  template <class Bar>
  Type_IntType1 & setTo(Bar &bar,uint32 ind) { bar.set_IntType1(*this,ind); return *this; }
 

  template <class T>
  Type_IntType1 & set(T to) { to(*this); return *this; }
 

  Type_IntType1 & setbit(Bits_IntType1 bits) { value|=Type(bits); return *this; }
 
  Type_IntType1 & setbitIf(bool cond,Bits_IntType1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IntType1 & clearbit(Bits_IntType1 bits) { value&=~Type(bits); return *this; }
 
  Type_IntType1 & clearbitIf(bool cond,Bits_IntType1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IntType1 bits) const { return value&bits; }
 
  bool testbit(Bits_IntType1 bits) const { return (value&bits)==Type(bits); }
 

  Field_IntType1_Pin0 get_Pin0() const
   {
    return Field_IntType1_Pin0((value>>0)&0x7);
   }
 
  Type_IntType1 & set_Pin0(Field_IntType1_Pin0 field)
   {
    value=((Type(field)&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Field_IntType1_Pin1 get_Pin1() const
   {
    return Field_IntType1_Pin1((value>>3)&0x7);
   }
 
  Type_IntType1 & set_Pin1(Field_IntType1_Pin1 field)
   {
    value=((Type(field)&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Field_IntType1_Pin2 get_Pin2() const
   {
    return Field_IntType1_Pin2((value>>6)&0x7);
   }
 
  Type_IntType1 & set_Pin2(Field_IntType1_Pin2 field)
   {
    value=((Type(field)&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  Field_IntType1_Pin3 get_Pin3() const
   {
    return Field_IntType1_Pin3((value>>9)&0x7);
   }
 
  Type_IntType1 & set_Pin3(Field_IntType1_Pin3 field)
   {
    value=((Type(field)&0x7)<<9)|(value&0xFFFFF1FF);

    return *this;
   }
 

  Field_IntType1_Pin4 get_Pin4() const
   {
    return Field_IntType1_Pin4((value>>12)&0x7);
   }
 
  Type_IntType1 & set_Pin4(Field_IntType1_Pin4 field)
   {
    value=((Type(field)&0x7)<<12)|(value&0xFFFF8FFF);

    return *this;
   }
 

  Field_IntType1_Pin5 get_Pin5() const
   {
    return Field_IntType1_Pin5((value>>15)&0x7);
   }
 
  Type_IntType1 & set_Pin5(Field_IntType1_Pin5 field)
   {
    value=((Type(field)&0x7)<<15)|(value&0xFFFC7FFF);

    return *this;
   }
 

  Field_IntType1_Pin6 get_Pin6() const
   {
    return Field_IntType1_Pin6((value>>18)&0x7);
   }
 
  Type_IntType1 & set_Pin6(Field_IntType1_Pin6 field)
   {
    value=((Type(field)&0x7)<<18)|(value&0xFFE3FFFF);

    return *this;
   }
 

  Field_IntType1_Pin7 get_Pin7() const
   {
    return Field_IntType1_Pin7((value>>21)&0x7);
   }
 
  Type_IntType1 & set_Pin7(Field_IntType1_Pin7 field)
   {
    value=((Type(field)&0x7)<<21)|(value&0xFF1FFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IntType1_InToNPE0 )
      {
       if( first )
         {
          Putobj(out,"InToNPE0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE0");
         }
      }

    if( value&IntType1_InToNPE1 )
      {
       if( first )
         {
          Putobj(out,"InToNPE1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE1");
         }
      }

    if( value&IntType1_InToNPE2 )
      {
       if( first )
         {
          Putobj(out,"InToNPE2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE2");
         }
      }

    if( value&IntType1_InToNPE3 )
      {
       if( first )
         {
          Putobj(out,"InToNPE3");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE3");
         }
      }

    if( value&IntType1_InToNPE4 )
      {
       if( first )
         {
          Putobj(out,"InToNPE4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE4");
         }
      }

    if( value&IntType1_InToNPE5 )
      {
       if( first )
         {
          Putobj(out,"InToNPE5");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE5");
         }
      }

    if( value&IntType1_InToNPE6 )
      {
       if( first )
         {
          Putobj(out,"InToNPE6");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE6");
         }
      }

    if( value&IntType1_InToNPE7 )
      {
       if( first )
         {
          Putobj(out,"InToNPE7");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InToNPE7");
         }
      }

    if( first )
      {
       Printf(out,"Pin0(#;)",get_Pin0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin0(#;)",get_Pin0());
      }

    if( first )
      {
       Printf(out,"Pin1(#;)",get_Pin1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin1(#;)",get_Pin1());
      }

    if( first )
      {
       Printf(out,"Pin2(#;)",get_Pin2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin2(#;)",get_Pin2());
      }

    if( first )
      {
       Printf(out,"Pin3(#;)",get_Pin3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin3(#;)",get_Pin3());
      }

    if( first )
      {
       Printf(out,"Pin4(#;)",get_Pin4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin4(#;)",get_Pin4());
      }

    if( first )
      {
       Printf(out,"Pin5(#;)",get_Pin5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin5(#;)",get_Pin5());
      }

    if( first )
      {
       Printf(out,"Pin6(#;)",get_Pin6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin6(#;)",get_Pin6());
      }

    if( first )
      {
       Printf(out,"Pin7(#;)",get_Pin7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin7(#;)",get_Pin7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntType2 */ 

enum Field_IntType2_Pin8 : uint32
 {
  IntType2_Pin8_Hi         = 0x00,
  IntType2_Pin8_Lo         = 0x01,
  IntType2_Pin8_Rising     = 0x02,
  IntType2_Pin8_Falling    = 0x03,
  IntType2_Pin8_Transition = 0x04
 };
 
struct PrintField_IntType2_Pin8
 {
  Field_IntType2_Pin8 field;

  explicit PrintField_IntType2_Pin8(Field_IntType2_Pin8 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType2_Pin8 GetTextDesc(Field_IntType2_Pin8 field)
 {
  return PrintField_IntType2_Pin8(field);
 }
 
enum Field_IntType2_Pin9 : uint32
 {
  IntType2_Pin9_Hi         = 0x00,
  IntType2_Pin9_Lo         = 0x01,
  IntType2_Pin9_Rising     = 0x02,
  IntType2_Pin9_Falling    = 0x03,
  IntType2_Pin9_Transition = 0x04
 };
 
struct PrintField_IntType2_Pin9
 {
  Field_IntType2_Pin9 field;

  explicit PrintField_IntType2_Pin9(Field_IntType2_Pin9 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType2_Pin9 GetTextDesc(Field_IntType2_Pin9 field)
 {
  return PrintField_IntType2_Pin9(field);
 }
 
enum Field_IntType2_Pin10 : uint32
 {
  IntType2_Pin10_Hi         = 0x00,
  IntType2_Pin10_Lo         = 0x01,
  IntType2_Pin10_Rising     = 0x02,
  IntType2_Pin10_Falling    = 0x03,
  IntType2_Pin10_Transition = 0x04
 };
 
struct PrintField_IntType2_Pin10
 {
  Field_IntType2_Pin10 field;

  explicit PrintField_IntType2_Pin10(Field_IntType2_Pin10 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType2_Pin10 GetTextDesc(Field_IntType2_Pin10 field)
 {
  return PrintField_IntType2_Pin10(field);
 }
 
enum Field_IntType2_Pin11 : uint32
 {
  IntType2_Pin11_Hi         = 0x00,
  IntType2_Pin11_Lo         = 0x01,
  IntType2_Pin11_Rising     = 0x02,
  IntType2_Pin11_Falling    = 0x03,
  IntType2_Pin11_Transition = 0x04
 };
 
struct PrintField_IntType2_Pin11
 {
  Field_IntType2_Pin11 field;

  explicit PrintField_IntType2_Pin11(Field_IntType2_Pin11 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType2_Pin11 GetTextDesc(Field_IntType2_Pin11 field)
 {
  return PrintField_IntType2_Pin11(field);
 }
 
enum Field_IntType2_Pin12 : uint32
 {
  IntType2_Pin12_Hi         = 0x00,
  IntType2_Pin12_Lo         = 0x01,
  IntType2_Pin12_Rising     = 0x02,
  IntType2_Pin12_Falling    = 0x03,
  IntType2_Pin12_Transition = 0x04
 };
 
struct PrintField_IntType2_Pin12
 {
  Field_IntType2_Pin12 field;

  explicit PrintField_IntType2_Pin12(Field_IntType2_Pin12 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Hi"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Rising"); break;
       case 0x03 : Putobj(out,"Falling"); break;
       case 0x04 : Putobj(out,"Transition"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntType2_Pin12 GetTextDesc(Field_IntType2_Pin12 field)
 {
  return PrintField_IntType2_Pin12(field);
 }
 
struct Type_IntType2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_IntType2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IntType2 & setTo(Bar &bar) { bar.set_IntType2(*this); return *this; }
 

  template <class Bar>
  Type_IntType2 & setTo(Bar &bar,uint32 ind) { bar.set_IntType2(*this,ind); return *this; }
 

  template <class T>
  Type_IntType2 & set(T to) { to(*this); return *this; }
 

  Field_IntType2_Pin8 get_Pin8() const
   {
    return Field_IntType2_Pin8((value>>0)&0x7);
   }
 
  Type_IntType2 & set_Pin8(Field_IntType2_Pin8 field)
   {
    value=((Type(field)&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Field_IntType2_Pin9 get_Pin9() const
   {
    return Field_IntType2_Pin9((value>>3)&0x7);
   }
 
  Type_IntType2 & set_Pin9(Field_IntType2_Pin9 field)
   {
    value=((Type(field)&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Field_IntType2_Pin10 get_Pin10() const
   {
    return Field_IntType2_Pin10((value>>6)&0x7);
   }
 
  Type_IntType2 & set_Pin10(Field_IntType2_Pin10 field)
   {
    value=((Type(field)&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  Field_IntType2_Pin11 get_Pin11() const
   {
    return Field_IntType2_Pin11((value>>9)&0x7);
   }
 
  Type_IntType2 & set_Pin11(Field_IntType2_Pin11 field)
   {
    value=((Type(field)&0x7)<<9)|(value&0xFFFFF1FF);

    return *this;
   }
 

  Field_IntType2_Pin12 get_Pin12() const
   {
    return Field_IntType2_Pin12((value>>12)&0x7);
   }
 
  Type_IntType2 & set_Pin12(Field_IntType2_Pin12 field)
   {
    value=((Type(field)&0x7)<<12)|(value&0xFFFF8FFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pin8(#;)",get_Pin8());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin8(#;)",get_Pin8());
      }

    if( first )
      {
       Printf(out,"Pin9(#;)",get_Pin9());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin9(#;)",get_Pin9());
      }

    if( first )
      {
       Printf(out,"Pin10(#;)",get_Pin10());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin10(#;)",get_Pin10());
      }

    if( first )
      {
       Printf(out,"Pin11(#;)",get_Pin11());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin11(#;)",get_Pin11());
      }

    if( first )
      {
       Printf(out,"Pin12(#;)",get_Pin12());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pin12(#;)",get_Pin12());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ClkType */ 

enum Bits_ClkType : uint32
 {
  ClkType_MUX14 = 0x00000100,
  ClkType_MUX15 = 0x01000000
 };
 
inline Bits_ClkType operator | (Bits_ClkType a,Bits_ClkType b)
 { return Bits_ClkType(uint32(a)|uint32(b)); }
 
struct Type_ClkType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ClkType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClkType & setTo(Bar &bar) { bar.set_ClkType(*this); return *this; }
 

  template <class Bar>
  Type_ClkType & setTo(Bar &bar,uint32 ind) { bar.set_ClkType(*this,ind); return *this; }
 

  template <class T>
  Type_ClkType & set(T to) { to(*this); return *this; }
 

  Type_ClkType & setbit(Bits_ClkType bits) { value|=Type(bits); return *this; }
 
  Type_ClkType & setbitIf(bool cond,Bits_ClkType bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ClkType & clearbit(Bits_ClkType bits) { value&=~Type(bits); return *this; }
 
  Type_ClkType & clearbitIf(bool cond,Bits_ClkType bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ClkType bits) const { return value&bits; }
 
  bool testbit(Bits_ClkType bits) const { return (value&bits)==Type(bits); }
 

  Type get_CLK0DC() const
   {
    return (value>>0)&0xF;
   }
 
  Type_ClkType & set_CLK0DC(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_CLK0TC() const
   {
    return (value>>4)&0xF;
   }
 
  Type_ClkType & set_CLK0TC(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_CLK1DC() const
   {
    return (value>>16)&0xF;
   }
 
  Type_ClkType & set_CLK1DC(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_CLK1TC() const
   {
    return (value>>20)&0xF;
   }
 
  Type_ClkType & set_CLK1TC(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ClkType_MUX14 )
      {
       if( first )
         {
          Putobj(out,"MUX14");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MUX14");
         }
      }

    if( value&ClkType_MUX15 )
      {
       if( first )
         {
          Putobj(out,"MUX15");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MUX15");
         }
      }

    if( first )
      {
       Printf(out,"CLK0DC(#;)",get_CLK0DC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CLK0DC(#;)",get_CLK0DC());
      }

    if( first )
      {
       Printf(out,"CLK0TC(#;)",get_CLK0TC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CLK0TC(#;)",get_CLK0TC());
      }

    if( first )
      {
       Printf(out,"CLK1DC(#;)",get_CLK1DC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CLK1DC(#;)",get_CLK1DC());
      }

    if( first )
      {
       Printf(out,"CLK1TC(#;)",get_CLK1TC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CLK1TC(#;)",get_CLK1TC());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct GPIOBar<RW> */ 

template <class RW>
struct GPIOBar
 {
  RW rw;

  template <class ... TT>
  GPIOBar(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- Out

  Type_Out get_Out() { return Type_Out(rw.template get<uint32>(0x0)); }
 
  void set_Out(Type_Out value) { rw.set(0x0,value.value); }
 
  Setter<Type_Out> to_Out() { return Setter<Type_Out>(rw,0x0); }
 
  static Type_Out null_Out() { return Type_Out(0); }
 
  static Type_Out ones_Out() { return Type_Out(Type_Out::Type(-1)); }
 
  //--- OutDisable

  Type_Out get_OutDisable() { return Type_Out(rw.template get<uint32>(0x4)); }
 
  void set_OutDisable(Type_Out value) { rw.set(0x4,value.value); }
 
  Setter<Type_Out> to_OutDisable() { return Setter<Type_Out>(rw,0x4); }
 
  //--- In

  Type_Out get_In() { return Type_Out(rw.template get<uint32>(0x8)); }
 
  //--- Int

  Type_Int get_Int() { return Type_Int(rw.template get<uint32>(0xC)); }
 
  void set_Int(Type_Int value) { rw.set(0xC,value.value); }
 
  Setter<Type_Int> to_Int() { return Setter<Type_Int>(rw,0xC); }
 
  static Type_Int null_Int() { return Type_Int(0); }
 
  static Type_Int ones_Int() { return Type_Int(Type_Int::Type(-1)); }
 
  //--- IntType1

  Type_IntType1 get_IntType1() { return Type_IntType1(rw.template get<uint32>(0x10)); }
 
  void set_IntType1(Type_IntType1 value) { rw.set(0x10,value.value); }
 
  Setter<Type_IntType1> to_IntType1() { return Setter<Type_IntType1>(rw,0x10); }
 
  static Type_IntType1 null_IntType1() { return Type_IntType1(0); }
 
  static Type_IntType1 ones_IntType1() { return Type_IntType1(Type_IntType1::Type(-1)); }
 
  //--- IntType2

  Type_IntType2 get_IntType2() { return Type_IntType2(rw.template get<uint32>(0x14)); }
 
  void set_IntType2(Type_IntType2 value) { rw.set(0x14,value.value); }
 
  Setter<Type_IntType2> to_IntType2() { return Setter<Type_IntType2>(rw,0x14); }
 
  static Type_IntType2 null_IntType2() { return Type_IntType2(0); }
 
  static Type_IntType2 ones_IntType2() { return Type_IntType2(Type_IntType2::Type(-1)); }
 
  //--- ClkType

  Type_ClkType get_ClkType() { return Type_ClkType(rw.template get<uint32>(0x18)); }
 
  void set_ClkType(Type_ClkType value) { rw.set(0x18,value.value); }
 
  Setter<Type_ClkType> to_ClkType() { return Setter<Type_ClkType>(rw,0x18); }
 
  static Type_ClkType null_ClkType() { return Type_ClkType(0); }
 
  static Type_ClkType ones_ClkType() { return Type_ClkType(Type_ClkType::Type(-1)); }
 
 };
 
