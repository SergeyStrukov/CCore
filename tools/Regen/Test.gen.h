/* Test.gen.h */ 

/* struct Type_ISR */ 

enum Bits_ISR : uint8
 {
  ISR_A = 0x01,
  ISR_B = 0x02,
  ISR_C = 0x04,
  ISR_D = 0x08
 };
 
inline Bits_ISR operator | (Bits_ISR a,Bits_ISR b)
 { return Bits_ISR(uint8(a)|uint8(b)); }
 
struct Type_ISR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_ISR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ISR & setTo(Bar &bar) { bar.set_ISR(*this); return *this; }
 

  template <class Bar>
  Type_ISR & setTo(Bar &bar,uint32 ind) { bar.set_ISR(*this,ind); return *this; }
 

  template <class T>
  Type_ISR & set(T to) { to(*this); return *this; }
 

  Type_ISR & setbit(Bits_ISR bits) { value|=Type(bits); return *this; }
 
  Type_ISR & setbitIf(bool cond,Bits_ISR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ISR & clearbit(Bits_ISR bits) { value&=~Type(bits); return *this; }
 
  Type_ISR & clearbitIf(bool cond,Bits_ISR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ISR bits) const { return value&bits; }
 
  bool testbit(Bits_ISR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ISR_A )
      {
       if( first )
         {
          Putobj(out,"A");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"A");
         }
      }

    if( value&ISR_B )
      {
       if( first )
         {
          Putobj(out,"B");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"B");
         }
      }

    if( value&ISR_C )
      {
       if( first )
         {
          Putobj(out,"C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C");
         }
      }

    if( value&ISR_D )
      {
       if( first )
         {
          Putobj(out,"D");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"D");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CTRL */ 

enum Bits_CTRL : uint32
 {
  CTRL_RUN  = 0x00000001,
  CTRL_STOP = 0x00000002
 };
 
inline Bits_CTRL operator | (Bits_CTRL a,Bits_CTRL b)
 { return Bits_CTRL(uint32(a)|uint32(b)); }
 
enum Field_CTRL_MODE : uint32
 {
  CTRL_MODE_SLOW = 0x00,
  CTRL_MODE_FAST = 0x01,
  CTRL_MODE_ACK  = 0x07
 };
 
struct PrintField_CTRL_MODE
 {
  Field_CTRL_MODE field;

  explicit PrintField_CTRL_MODE(Field_CTRL_MODE field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"SLOW"); break;
       case 0x01 : Putobj(out,"FAST"); break;
       case 0x07 : Putobj(out,"ACK"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CTRL_MODE GetTextDesc(Field_CTRL_MODE field)
 {
  return PrintField_CTRL_MODE(field);
 }
 
struct Type_CTRL
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CTRL(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CTRL & setTo(Bar &bar) { bar.set_CTRL(*this); return *this; }
 

  template <class Bar>
  Type_CTRL & setTo(Bar &bar,uint32 ind) { bar.set_CTRL(*this,ind); return *this; }
 

  template <class T>
  Type_CTRL & set(T to) { to(*this); return *this; }
 

  Type_CTRL & setbit(Bits_CTRL bits) { value|=Type(bits); return *this; }
 
  Type_CTRL & setbitIf(bool cond,Bits_CTRL bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CTRL & clearbit(Bits_CTRL bits) { value&=~Type(bits); return *this; }
 
  Type_CTRL & clearbitIf(bool cond,Bits_CTRL bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CTRL bits) const { return value&bits; }
 
  bool testbit(Bits_CTRL bits) const { return (value&bits)==Type(bits); }
 

  Type get_COUNT() const
   {
    return (value>>2)&0xF;
   }
 
  Type_CTRL & set_COUNT(Type field)
   {
    value=((field&0xF)<<2)|(value&0xFFFFFFC3);

    return *this;
   }
 

  Field_CTRL_MODE get_MODE() const
   {
    return Field_CTRL_MODE((value>>16)&0x7);
   }
 
  Type_CTRL & set_MODE(Field_CTRL_MODE field)
   {
    value=((Type(field)&0x7)<<16)|(value&0xFFF8FFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CTRL_RUN )
      {
       if( first )
         {
          Putobj(out,"RUN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RUN");
         }
      }

    if( value&CTRL_STOP )
      {
       if( first )
         {
          Putobj(out,"STOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"STOP");
         }
      }

    if( first )
      {
       Printf(out,"COUNT(#;)",get_COUNT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"COUNT(#;)",get_COUNT());
      }

    if( first )
      {
       Printf(out,"MODE(#;)",get_MODE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MODE(#;)",get_MODE());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_STAT */ 

enum Bits_STAT : uint16
 {
  STAT_RUN  = 0x0001,
  STAT_STOP = 0x0002
 };
 
inline Bits_STAT operator | (Bits_STAT a,Bits_STAT b)
 { return Bits_STAT(uint16(a)|uint16(b)); }
 
enum Field_STAT_MODE : uint16
 {
  STAT_MODE_SLOW = 0x00,
  STAT_MODE_FAST = 0x01,
  STAT_MODE_ACK  = 0x04
 };
 
struct PrintField_STAT_MODE
 {
  Field_STAT_MODE field;

  explicit PrintField_STAT_MODE(Field_STAT_MODE field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"SLOW"); break;
       case 0x01 : Putobj(out,"FAST"); break;
       case 0x04 : Putobj(out,"ACK"); break;

       default: Putobj(out,uint16(field));
      }
   }
 };
 
inline PrintField_STAT_MODE GetTextDesc(Field_STAT_MODE field)
 {
  return PrintField_STAT_MODE(field);
 }
 
struct Type_STAT
 {
  typedef uint16 Type;

  Type value;


  explicit Type_STAT(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_STAT & setTo(Bar &bar) { bar.set_STAT(*this); return *this; }
 

  template <class Bar>
  Type_STAT & setTo(Bar &bar,uint32 ind) { bar.set_STAT(*this,ind); return *this; }
 

  template <class T>
  Type_STAT & set(T to) { to(*this); return *this; }
 

  Type_STAT & setbit(Bits_STAT bits) { value|=Type(bits); return *this; }
 
  Type_STAT & setbitIf(bool cond,Bits_STAT bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_STAT & clearbit(Bits_STAT bits) { value&=~Type(bits); return *this; }
 
  Type_STAT & clearbitIf(bool cond,Bits_STAT bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_STAT bits) const { return value&bits; }
 
  bool testbit(Bits_STAT bits) const { return (value&bits)==Type(bits); }
 

  Type get_COUNT() const
   {
    return (value>>2)&0xF;
   }
 
  Type_STAT & set_COUNT(Type field)
   {
    value=((field&0xF)<<2)|(value&0xFFFFFFC3);

    return *this;
   }
 

  Field_STAT_MODE get_MODE() const
   {
    return Field_STAT_MODE((value>>6)&0x7);
   }
 
  Type_STAT & set_MODE(Field_STAT_MODE field)
   {
    value=((Type(field)&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&STAT_RUN )
      {
       if( first )
         {
          Putobj(out,"RUN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RUN");
         }
      }

    if( value&STAT_STOP )
      {
       if( first )
         {
          Putobj(out,"STOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"STOP");
         }
      }

    if( first )
      {
       Printf(out,"COUNT(#;)",get_COUNT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"COUNT(#;)",get_COUNT());
      }

    if( first )
      {
       Printf(out,"MODE(#;)",get_MODE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MODE(#;)",get_MODE());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_SCRAP */ 

typedef uint16 Type_SCRAP;

/* type Type_PTR */ 

typedef uint32 Type_PTR;

/* type Type_TEMP */ 

typedef uint32 Type_TEMP;

/* struct Test<RW> */ 

template <class RW>
struct Test
 {
  RW rw;

  template <class ... TT>
  Test(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ISR

  Type_ISR get_ISR() { return Type_ISR(rw.template get<uint8>(0xA)); }
 
  static Type_ISR null_ISR() { return Type_ISR(0); }
 
  static Type_ISR ones_ISR() { return Type_ISR(Type_ISR::Type(-1)); }
 
  //--- ICR

  void set_ICR(Type_ISR value) { rw.set(0x100,value.value); }
 
  Setter<Type_ISR> to_ICR() { return Setter<Type_ISR>(rw,0x100); }
 
  //--- IMR

  Type_ISR get_IMR() { return Type_ISR(rw.template get<uint8>(0x101)); }
 
  void set_IMR(Type_ISR value) { rw.set(0x101,value.value); }
 
  Setter<Type_ISR> to_IMR() { return Setter<Type_ISR>(rw,0x101); }
 
  //--- CTRL

  Type_CTRL get_CTRL(uint32 ind) { return Type_CTRL(rw.template get<uint32>(0x102 +ind*4)); }
 
  void set_CTRL(uint32 ind,Type_CTRL value) { rw.set(0x102 +ind*4,value.value); }
 
  Setter<Type_CTRL> to_CTRL(uint32 ind) { return Setter<Type_CTRL>(rw,0x102 +ind*4); }
 
  static Type_CTRL null_CTRL() { return Type_CTRL(0); }
 
  static Type_CTRL ones_CTRL() { return Type_CTRL(Type_CTRL::Type(-1)); }
 
  //--- STAT

  Type_STAT get_STAT() { return Type_STAT(rw.template get<uint16>(0x12A)); }
 
  static Type_STAT null_STAT() { return Type_STAT(0); }
 
  static Type_STAT ones_STAT() { return Type_STAT(Type_STAT::Type(-1)); }
 
  //--- SCRAP

  Type_SCRAP get_SCRAP() { return Type_SCRAP(rw.template get<uint16>(0x12C)); }
 
  void set_SCRAP(Type_SCRAP value) { rw.set(0x12C,value); }
 
  void set_SCRAP_null() { rw.set(0x12C,Type_SCRAP(0)); }
 
  void set_SCRAP_ones() { rw.set(0x12C,Type_SCRAP(-1)); }
 
  //--- BSCRAP

  Type_SCRAP get_BSCRAP(uint32 ind) { return Type_SCRAP(rw.template get<uint16>(0x12E +ind*2)); }
 
  void set_BSCRAP(uint32 ind,Type_SCRAP value) { rw.set(0x12E +ind*2,value); }
 
  void set_BSCRAP_null(uint32 ind) { rw.set(0x12E +ind*2,Type_SCRAP(0)); }
 
  void set_BSCRAP_ones(uint32 ind) { rw.set(0x12E +ind*2,Type_SCRAP(-1)); }
 
  //--- BIMP

  Type_ISR get_BIMP(uint32 ind) { return Type_ISR(rw.template get<uint8>(0x142 +ind*1)); }
 
  void set_BIMP(uint32 ind,Type_ISR value) { rw.set(0x142 +ind*1,value.value); }
 
  Setter<Type_ISR> to_BIMP(uint32 ind) { return Setter<Type_ISR>(rw,0x142 +ind*1); }
 
  //--- PTR

  Type_PTR get_PTR(uint32 ind) { return Type_PTR(rw.template get<uint32>(0x14C +ind*4)); }
 
  void set_PTR(uint32 ind,Type_PTR value) { rw.set(0x14C +ind*4,value); }
 
  void set_PTR_null(uint32 ind) { rw.set(0x14C +ind*4,Type_PTR(0)); }
 
  void set_PTR_ones(uint32 ind) { rw.set(0x14C +ind*4,Type_PTR(-1)); }
 
  //--- TEMP

 };
 
