/* IXP465.UART.gen.h */ 

/* struct Type_Rx */ 

struct Type_Rx
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Rx(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Rx & setTo(Bar &bar) { bar.set_Rx(*this); return *this; }
 

  template <class Bar>
  Type_Rx & setTo(Bar &bar,uint32 ind) { bar.set_Rx(ind,*this); return *this; }
 

  template <class T>
  Type_Rx & set(T to) { to(*this); return *this; }
 

  Type get_Byte() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Rx & set_Byte(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Byte(#;)",get_Byte());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte(#;)",get_Byte());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Tx */ 

struct Type_Tx
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Tx(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Tx & setTo(Bar &bar) { bar.set_Tx(*this); return *this; }
 

  template <class Bar>
  Type_Tx & setTo(Bar &bar,uint32 ind) { bar.set_Tx(ind,*this); return *this; }
 

  template <class T>
  Type_Tx & set(T to) { to(*this); return *this; }
 

  Type get_Byte() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Tx & set_Byte(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Byte(#;)",get_Byte());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte(#;)",get_Byte());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntEnable */ 

enum Bits_IntEnable : uint32
 {
  IntEnable_Rx          = 0x00000001,
  IntEnable_Tx          = 0x00000002,
  IntEnable_RxError     = 0x00000004,
  IntEnable_ModemStatus = 0x00000008,
  IntEnable_RxTO        = 0x00000010,
  IntEnable_Unit        = 0x00000040
 };
 
inline Bits_IntEnable operator | (Bits_IntEnable a,Bits_IntEnable b)
 { return Bits_IntEnable(uint32(a)|uint32(b)); }
 
struct Type_IntEnable
 {
  typedef uint32 Type;

  Type value;


  explicit Type_IntEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IntEnable & setTo(Bar &bar) { bar.set_IntEnable(*this); return *this; }
 

  template <class Bar>
  Type_IntEnable & setTo(Bar &bar,uint32 ind) { bar.set_IntEnable(ind,*this); return *this; }
 

  template <class T>
  Type_IntEnable & set(T to) { to(*this); return *this; }
 

  Type_IntEnable & setbit(Bits_IntEnable bits) { value|=Type(bits); return *this; }
 
  Type_IntEnable & setbitIf(bool cond,Bits_IntEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IntEnable & clearbit(Bits_IntEnable bits) { value&=~Type(bits); return *this; }
 
  Type_IntEnable & clearbitIf(bool cond,Bits_IntEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IntEnable bits) const { return value&bits; }
 
  bool testbit(Bits_IntEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IntEnable_Rx )
      {
       if( first )
         {
          Putobj(out,"Rx");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Rx");
         }
      }

    if( value&IntEnable_Tx )
      {
       if( first )
         {
          Putobj(out,"Tx");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Tx");
         }
      }

    if( value&IntEnable_RxError )
      {
       if( first )
         {
          Putobj(out,"RxError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxError");
         }
      }

    if( value&IntEnable_ModemStatus )
      {
       if( first )
         {
          Putobj(out,"ModemStatus");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ModemStatus");
         }
      }

    if( value&IntEnable_RxTO )
      {
       if( first )
         {
          Putobj(out,"RxTO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxTO");
         }
      }

    if( value&IntEnable_Unit )
      {
       if( first )
         {
          Putobj(out,"Unit");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Unit");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DivLo */ 

struct Type_DivLo
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DivLo(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DivLo & setTo(Bar &bar) { bar.set_DivLo(*this); return *this; }
 

  template <class Bar>
  Type_DivLo & setTo(Bar &bar,uint32 ind) { bar.set_DivLo(ind,*this); return *this; }
 

  template <class T>
  Type_DivLo & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_DivLo & set_Div(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Div(#;)",get_Div());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Div(#;)",get_Div());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DivHi */ 

struct Type_DivHi
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DivHi(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DivHi & setTo(Bar &bar) { bar.set_DivHi(*this); return *this; }
 

  template <class Bar>
  Type_DivHi & setTo(Bar &bar,uint32 ind) { bar.set_DivHi(ind,*this); return *this; }
 

  template <class T>
  Type_DivHi & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_DivHi & set_Div(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Div(#;)",get_Div());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Div(#;)",get_Div());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntStatus */ 

enum Bits_IntStatus : uint32
 {
  IntStatus_NoInt = 0x00000001
 };
 
inline Bits_IntStatus operator | (Bits_IntStatus a,Bits_IntStatus b)
 { return Bits_IntStatus(uint32(a)|uint32(b)); }
 
enum Field_IntStatus_Src : uint32
 {
  IntStatus_Src_ModemStatus = 0x00,
  IntStatus_Src_Tx          = 0x01,
  IntStatus_Src_Rx          = 0x02,
  IntStatus_Src_RxError     = 0x03,
  IntStatus_Src_TO          = 0x04
 };
 
struct PrintField_IntStatus_Src
 {
  Field_IntStatus_Src field;

  explicit PrintField_IntStatus_Src(Field_IntStatus_Src field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"ModemStatus"); break;
       case 0x01 : Putobj(out,"Tx"); break;
       case 0x02 : Putobj(out,"Rx"); break;
       case 0x03 : Putobj(out,"RxError"); break;
       case 0x04 : Putobj(out,"TO"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntStatus_Src GetTextDesc(Field_IntStatus_Src field)
 {
  return PrintField_IntStatus_Src(field);
 }
 
enum Field_IntStatus_FIFOStatus : uint32
 {
  IntStatus_FIFOStatus_NoFIFO = 0x00,
  IntStatus_FIFOStatus_FIFO   = 0x03
 };
 
struct PrintField_IntStatus_FIFOStatus
 {
  Field_IntStatus_FIFOStatus field;

  explicit PrintField_IntStatus_FIFOStatus(Field_IntStatus_FIFOStatus field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoFIFO"); break;
       case 0x03 : Putobj(out,"FIFO"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_IntStatus_FIFOStatus GetTextDesc(Field_IntStatus_FIFOStatus field)
 {
  return PrintField_IntStatus_FIFOStatus(field);
 }
 
struct Type_IntStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_IntStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IntStatus & setTo(Bar &bar) { bar.set_IntStatus(*this); return *this; }
 

  template <class Bar>
  Type_IntStatus & setTo(Bar &bar,uint32 ind) { bar.set_IntStatus(ind,*this); return *this; }
 

  template <class T>
  Type_IntStatus & set(T to) { to(*this); return *this; }
 

  Type_IntStatus & setbit(Bits_IntStatus bits) { value|=Type(bits); return *this; }
 
  Type_IntStatus & setbitIf(bool cond,Bits_IntStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IntStatus & clearbit(Bits_IntStatus bits) { value&=~Type(bits); return *this; }
 
  Type_IntStatus & clearbitIf(bool cond,Bits_IntStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IntStatus bits) const { return value&bits; }
 
  bool testbit(Bits_IntStatus bits) const { return (value&bits)==Type(bits); }
 

  Field_IntStatus_Src get_Src() const
   {
    return Field_IntStatus_Src((value>>1)&0x7);
   }
 
  Type_IntStatus & set_Src(Field_IntStatus_Src field)
   {
    value=((Type(field)&0x7)<<1)|(value&0xFFFFFFF1);

    return *this;
   }
 

  Field_IntStatus_FIFOStatus get_FIFOStatus() const
   {
    return Field_IntStatus_FIFOStatus((value>>6)&0x3);
   }
 
  Type_IntStatus & set_FIFOStatus(Field_IntStatus_FIFOStatus field)
   {
    value=((Type(field)&0x3)<<6)|(value&0xFFFFFF3F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IntStatus_NoInt )
      {
       if( first )
         {
          Putobj(out,"NoInt");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoInt");
         }
      }

    if( first )
      {
       Printf(out,"Src(#;)",get_Src());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Src(#;)",get_Src());
      }

    if( first )
      {
       Printf(out,"FIFOStatus(#;)",get_FIFOStatus());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"FIFOStatus(#;)",get_FIFOStatus());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_FIFOControl */ 

enum Bits_FIFOControl : uint32
 {
  FIFOControl_Enable      = 0x00000001,
  FIFOControl_ResetRxFIFO = 0x00000002,
  FIFOControl_ResetTxFIFO = 0x00000004
 };
 
inline Bits_FIFOControl operator | (Bits_FIFOControl a,Bits_FIFOControl b)
 { return Bits_FIFOControl(uint32(a)|uint32(b)); }
 
enum Field_FIFOControl_RxLevel : uint32
 {
  FIFOControl_RxLevel_Level1  = 0x00,
  FIFOControl_RxLevel_Level8  = 0x01,
  FIFOControl_RxLevel_Level16 = 0x02,
  FIFOControl_RxLevel_Level32 = 0x03
 };
 
struct PrintField_FIFOControl_RxLevel
 {
  Field_FIFOControl_RxLevel field;

  explicit PrintField_FIFOControl_RxLevel(Field_FIFOControl_RxLevel field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Level1"); break;
       case 0x01 : Putobj(out,"Level8"); break;
       case 0x02 : Putobj(out,"Level16"); break;
       case 0x03 : Putobj(out,"Level32"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_FIFOControl_RxLevel GetTextDesc(Field_FIFOControl_RxLevel field)
 {
  return PrintField_FIFOControl_RxLevel(field);
 }
 
struct Type_FIFOControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_FIFOControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_FIFOControl & setTo(Bar &bar) { bar.set_FIFOControl(*this); return *this; }
 

  template <class Bar>
  Type_FIFOControl & setTo(Bar &bar,uint32 ind) { bar.set_FIFOControl(ind,*this); return *this; }
 

  template <class T>
  Type_FIFOControl & set(T to) { to(*this); return *this; }
 

  Type_FIFOControl & setbit(Bits_FIFOControl bits) { value|=Type(bits); return *this; }
 
  Type_FIFOControl & setbitIf(bool cond,Bits_FIFOControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_FIFOControl & clearbit(Bits_FIFOControl bits) { value&=~Type(bits); return *this; }
 
  Type_FIFOControl & clearbitIf(bool cond,Bits_FIFOControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_FIFOControl bits) const { return value&bits; }
 
  bool testbit(Bits_FIFOControl bits) const { return (value&bits)==Type(bits); }
 

  Field_FIFOControl_RxLevel get_RxLevel() const
   {
    return Field_FIFOControl_RxLevel((value>>6)&0x3);
   }
 
  Type_FIFOControl & set_RxLevel(Field_FIFOControl_RxLevel field)
   {
    value=((Type(field)&0x3)<<6)|(value&0xFFFFFF3F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&FIFOControl_Enable )
      {
       if( first )
         {
          Putobj(out,"Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Enable");
         }
      }

    if( value&FIFOControl_ResetRxFIFO )
      {
       if( first )
         {
          Putobj(out,"ResetRxFIFO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetRxFIFO");
         }
      }

    if( value&FIFOControl_ResetTxFIFO )
      {
       if( first )
         {
          Putobj(out,"ResetTxFIFO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetTxFIFO");
         }
      }

    if( first )
      {
       Printf(out,"RxLevel(#;)",get_RxLevel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxLevel(#;)",get_RxLevel());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_LineControl */ 

enum Bits_LineControl : uint32
 {
  LineControl_StickyParity = 0x00000020,
  LineControl_Break        = 0x00000040,
  LineControl_DivAccess    = 0x00000080
 };
 
inline Bits_LineControl operator | (Bits_LineControl a,Bits_LineControl b)
 { return Bits_LineControl(uint32(a)|uint32(b)); }
 
enum Field_LineControl_Bits : uint32
 {
  LineControl_Bits_Bit5 = 0x00,
  LineControl_Bits_Bit6 = 0x01,
  LineControl_Bits_Bit7 = 0x02,
  LineControl_Bits_Bit8 = 0x03
 };
 
struct PrintField_LineControl_Bits
 {
  Field_LineControl_Bits field;

  explicit PrintField_LineControl_Bits(Field_LineControl_Bits field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Bit5"); break;
       case 0x01 : Putobj(out,"Bit6"); break;
       case 0x02 : Putobj(out,"Bit7"); break;
       case 0x03 : Putobj(out,"Bit8"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_LineControl_Bits GetTextDesc(Field_LineControl_Bits field)
 {
  return PrintField_LineControl_Bits(field);
 }
 
enum Field_LineControl_StopBits : uint32
 {
  LineControl_StopBits_Bit1 = 0x00,
  LineControl_StopBits_Bit2 = 0x01
 };
 
struct PrintField_LineControl_StopBits
 {
  Field_LineControl_StopBits field;

  explicit PrintField_LineControl_StopBits(Field_LineControl_StopBits field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Bit1"); break;
       case 0x01 : Putobj(out,"Bit2"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_LineControl_StopBits GetTextDesc(Field_LineControl_StopBits field)
 {
  return PrintField_LineControl_StopBits(field);
 }
 
enum Field_LineControl_ParityBits : uint32
 {
  LineControl_ParityBits_Bit0 = 0x00,
  LineControl_ParityBits_Bit1 = 0x01
 };
 
struct PrintField_LineControl_ParityBits
 {
  Field_LineControl_ParityBits field;

  explicit PrintField_LineControl_ParityBits(Field_LineControl_ParityBits field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Bit0"); break;
       case 0x01 : Putobj(out,"Bit1"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_LineControl_ParityBits GetTextDesc(Field_LineControl_ParityBits field)
 {
  return PrintField_LineControl_ParityBits(field);
 }
 
enum Field_LineControl_ParityType : uint32
 {
  LineControl_ParityType_Odd  = 0x00,
  LineControl_ParityType_Even = 0x01
 };
 
struct PrintField_LineControl_ParityType
 {
  Field_LineControl_ParityType field;

  explicit PrintField_LineControl_ParityType(Field_LineControl_ParityType field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Odd"); break;
       case 0x01 : Putobj(out,"Even"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_LineControl_ParityType GetTextDesc(Field_LineControl_ParityType field)
 {
  return PrintField_LineControl_ParityType(field);
 }
 
struct Type_LineControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_LineControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_LineControl & setTo(Bar &bar) { bar.set_LineControl(*this); return *this; }
 

  template <class Bar>
  Type_LineControl & setTo(Bar &bar,uint32 ind) { bar.set_LineControl(ind,*this); return *this; }
 

  template <class T>
  Type_LineControl & set(T to) { to(*this); return *this; }
 

  Type_LineControl & setbit(Bits_LineControl bits) { value|=Type(bits); return *this; }
 
  Type_LineControl & setbitIf(bool cond,Bits_LineControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_LineControl & clearbit(Bits_LineControl bits) { value&=~Type(bits); return *this; }
 
  Type_LineControl & clearbitIf(bool cond,Bits_LineControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_LineControl bits) const { return value&bits; }
 
  bool testbit(Bits_LineControl bits) const { return (value&bits)==Type(bits); }
 

  Field_LineControl_Bits get_Bits() const
   {
    return Field_LineControl_Bits((value>>0)&0x3);
   }
 
  Type_LineControl & set_Bits(Field_LineControl_Bits field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Field_LineControl_StopBits get_StopBits() const
   {
    return Field_LineControl_StopBits((value>>2)&0x1);
   }
 
  Type_LineControl & set_StopBits(Field_LineControl_StopBits field)
   {
    value=((Type(field)&0x1)<<2)|(value&0xFFFFFFFB);

    return *this;
   }
 

  Field_LineControl_ParityBits get_ParityBits() const
   {
    return Field_LineControl_ParityBits((value>>3)&0x1);
   }
 
  Type_LineControl & set_ParityBits(Field_LineControl_ParityBits field)
   {
    value=((Type(field)&0x1)<<3)|(value&0xFFFFFFF7);

    return *this;
   }
 

  Field_LineControl_ParityType get_ParityType() const
   {
    return Field_LineControl_ParityType((value>>4)&0x1);
   }
 
  Type_LineControl & set_ParityType(Field_LineControl_ParityType field)
   {
    value=((Type(field)&0x1)<<4)|(value&0xFFFFFFEF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&LineControl_StickyParity )
      {
       if( first )
         {
          Putobj(out,"StickyParity");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"StickyParity");
         }
      }

    if( value&LineControl_Break )
      {
       if( first )
         {
          Putobj(out,"Break");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Break");
         }
      }

    if( value&LineControl_DivAccess )
      {
       if( first )
         {
          Putobj(out,"DivAccess");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DivAccess");
         }
      }

    if( first )
      {
       Printf(out,"Bits(#;)",get_Bits());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Bits(#;)",get_Bits());
      }

    if( first )
      {
       Printf(out,"StopBits(#;)",get_StopBits());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"StopBits(#;)",get_StopBits());
      }

    if( first )
      {
       Printf(out,"ParityBits(#;)",get_ParityBits());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ParityBits(#;)",get_ParityBits());
      }

    if( first )
      {
       Printf(out,"ParityType(#;)",get_ParityType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ParityType(#;)",get_ParityType());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ModemControl */ 

enum Bits_ModemControl : uint32
 {
  ModemControl_DTR  = 0x00000001,
  ModemControl_RTS  = 0x00000002,
  ModemControl_OUT1 = 0x00000004,
  ModemControl_OUT2 = 0x00000008,
  ModemControl_LOOP = 0x00000010
 };
 
inline Bits_ModemControl operator | (Bits_ModemControl a,Bits_ModemControl b)
 { return Bits_ModemControl(uint32(a)|uint32(b)); }
 
struct Type_ModemControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ModemControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ModemControl & setTo(Bar &bar) { bar.set_ModemControl(*this); return *this; }
 

  template <class Bar>
  Type_ModemControl & setTo(Bar &bar,uint32 ind) { bar.set_ModemControl(ind,*this); return *this; }
 

  template <class T>
  Type_ModemControl & set(T to) { to(*this); return *this; }
 

  Type_ModemControl & setbit(Bits_ModemControl bits) { value|=Type(bits); return *this; }
 
  Type_ModemControl & setbitIf(bool cond,Bits_ModemControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ModemControl & clearbit(Bits_ModemControl bits) { value&=~Type(bits); return *this; }
 
  Type_ModemControl & clearbitIf(bool cond,Bits_ModemControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ModemControl bits) const { return value&bits; }
 
  bool testbit(Bits_ModemControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ModemControl_DTR )
      {
       if( first )
         {
          Putobj(out,"DTR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DTR");
         }
      }

    if( value&ModemControl_RTS )
      {
       if( first )
         {
          Putobj(out,"RTS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RTS");
         }
      }

    if( value&ModemControl_OUT1 )
      {
       if( first )
         {
          Putobj(out,"OUT1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OUT1");
         }
      }

    if( value&ModemControl_OUT2 )
      {
       if( first )
         {
          Putobj(out,"OUT2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OUT2");
         }
      }

    if( value&ModemControl_LOOP )
      {
       if( first )
         {
          Putobj(out,"LOOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LOOP");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_LineStatus */ 

enum Bits_LineStatus : uint32
 {
  LineStatus_RxReady    = 0x00000001,
  LineStatus_RxOverflow = 0x00000002,
  LineStatus_RxParity   = 0x00000004,
  LineStatus_RxFrame    = 0x00000008,
  LineStatus_RxBreak    = 0x00000010,
  LineStatus_TxReady    = 0x00000020,
  LineStatus_TxEmpty    = 0x00000040,
  LineStatus_FIFOError  = 0x00000080
 };
 
inline Bits_LineStatus operator | (Bits_LineStatus a,Bits_LineStatus b)
 { return Bits_LineStatus(uint32(a)|uint32(b)); }
 
struct Type_LineStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_LineStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_LineStatus & setTo(Bar &bar) { bar.set_LineStatus(*this); return *this; }
 

  template <class Bar>
  Type_LineStatus & setTo(Bar &bar,uint32 ind) { bar.set_LineStatus(ind,*this); return *this; }
 

  template <class T>
  Type_LineStatus & set(T to) { to(*this); return *this; }
 

  Type_LineStatus & setbit(Bits_LineStatus bits) { value|=Type(bits); return *this; }
 
  Type_LineStatus & setbitIf(bool cond,Bits_LineStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_LineStatus & clearbit(Bits_LineStatus bits) { value&=~Type(bits); return *this; }
 
  Type_LineStatus & clearbitIf(bool cond,Bits_LineStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_LineStatus bits) const { return value&bits; }
 
  bool testbit(Bits_LineStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&LineStatus_RxReady )
      {
       if( first )
         {
          Putobj(out,"RxReady");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxReady");
         }
      }

    if( value&LineStatus_RxOverflow )
      {
       if( first )
         {
          Putobj(out,"RxOverflow");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxOverflow");
         }
      }

    if( value&LineStatus_RxParity )
      {
       if( first )
         {
          Putobj(out,"RxParity");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxParity");
         }
      }

    if( value&LineStatus_RxFrame )
      {
       if( first )
         {
          Putobj(out,"RxFrame");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxFrame");
         }
      }

    if( value&LineStatus_RxBreak )
      {
       if( first )
         {
          Putobj(out,"RxBreak");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxBreak");
         }
      }

    if( value&LineStatus_TxReady )
      {
       if( first )
         {
          Putobj(out,"TxReady");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxReady");
         }
      }

    if( value&LineStatus_TxEmpty )
      {
       if( first )
         {
          Putobj(out,"TxEmpty");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxEmpty");
         }
      }

    if( value&LineStatus_FIFOError )
      {
       if( first )
         {
          Putobj(out,"FIFOError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FIFOError");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ModemStatus */ 

enum Bits_ModemStatus : uint32
 {
  ModemStatus_DeltaCTS = 0x00000001,
  ModemStatus_DeltaDSR = 0x00000002,
  ModemStatus_DeltaRI  = 0x00000004,
  ModemStatus_DeltaDCD = 0x00000008,
  ModemStatus_CTS      = 0x00000010,
  ModemStatus_DSR      = 0x00000020,
  ModemStatus_RI       = 0x00000040,
  ModemStatus_DCD      = 0x00000080
 };
 
inline Bits_ModemStatus operator | (Bits_ModemStatus a,Bits_ModemStatus b)
 { return Bits_ModemStatus(uint32(a)|uint32(b)); }
 
struct Type_ModemStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ModemStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ModemStatus & setTo(Bar &bar) { bar.set_ModemStatus(*this); return *this; }
 

  template <class Bar>
  Type_ModemStatus & setTo(Bar &bar,uint32 ind) { bar.set_ModemStatus(ind,*this); return *this; }
 

  template <class T>
  Type_ModemStatus & set(T to) { to(*this); return *this; }
 

  Type_ModemStatus & setbit(Bits_ModemStatus bits) { value|=Type(bits); return *this; }
 
  Type_ModemStatus & setbitIf(bool cond,Bits_ModemStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ModemStatus & clearbit(Bits_ModemStatus bits) { value&=~Type(bits); return *this; }
 
  Type_ModemStatus & clearbitIf(bool cond,Bits_ModemStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ModemStatus bits) const { return value&bits; }
 
  bool testbit(Bits_ModemStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ModemStatus_DeltaCTS )
      {
       if( first )
         {
          Putobj(out,"DeltaCTS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DeltaCTS");
         }
      }

    if( value&ModemStatus_DeltaDSR )
      {
       if( first )
         {
          Putobj(out,"DeltaDSR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DeltaDSR");
         }
      }

    if( value&ModemStatus_DeltaRI )
      {
       if( first )
         {
          Putobj(out,"DeltaRI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DeltaRI");
         }
      }

    if( value&ModemStatus_DeltaDCD )
      {
       if( first )
         {
          Putobj(out,"DeltaDCD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DeltaDCD");
         }
      }

    if( value&ModemStatus_CTS )
      {
       if( first )
         {
          Putobj(out,"CTS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CTS");
         }
      }

    if( value&ModemStatus_DSR )
      {
       if( first )
         {
          Putobj(out,"DSR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DSR");
         }
      }

    if( value&ModemStatus_RI )
      {
       if( first )
         {
          Putobj(out,"RI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RI");
         }
      }

    if( value&ModemStatus_DCD )
      {
       if( first )
         {
          Putobj(out,"DCD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DCD");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Scratch */ 

struct Type_Scratch
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Scratch(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Scratch & setTo(Bar &bar) { bar.set_Scratch(*this); return *this; }
 

  template <class Bar>
  Type_Scratch & setTo(Bar &bar,uint32 ind) { bar.set_Scratch(ind,*this); return *this; }
 

  template <class T>
  Type_Scratch & set(T to) { to(*this); return *this; }
 

  Type get_Byte() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Scratch & set_Byte(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Byte(#;)",get_Byte());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Byte(#;)",get_Byte());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct UARTBar<RW> */ 

template <class RW>
struct UARTBar
 {
  RW rw;

  template <class ... TT>
  UARTBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- Rx

  Type_Rx get_Rx() { return Type_Rx(rw.template get<uint32>(0x0)); }
 
  static Type_Rx null_Rx() { return Type_Rx(0); }
 
  static Type_Rx ones_Rx() { return Type_Rx(Type_Rx::Type(-1)); }
 
  //--- Tx

  void set_Tx(Type_Tx value) { rw.set(0x0,value.value); }
 
  Setter<Type_Tx> to_Tx() { return Setter<Type_Tx>(rw,0x0); }
 
  static Type_Tx null_Tx() { return Type_Tx(0); }
 
  static Type_Tx ones_Tx() { return Type_Tx(Type_Tx::Type(-1)); }
 
  //--- IntEnable

  Type_IntEnable get_IntEnable() { return Type_IntEnable(rw.template get<uint32>(0x4)); }
 
  void set_IntEnable(Type_IntEnable value) { rw.set(0x4,value.value); }
 
  Setter<Type_IntEnable> to_IntEnable() { return Setter<Type_IntEnable>(rw,0x4); }
 
  static Type_IntEnable null_IntEnable() { return Type_IntEnable(0); }
 
  static Type_IntEnable ones_IntEnable() { return Type_IntEnable(Type_IntEnable::Type(-1)); }
 
  //--- DivLo

  Type_DivLo get_DivLo() { return Type_DivLo(rw.template get<uint32>(0x0)); }
 
  void set_DivLo(Type_DivLo value) { rw.set(0x0,value.value); }
 
  Setter<Type_DivLo> to_DivLo() { return Setter<Type_DivLo>(rw,0x0); }
 
  static Type_DivLo null_DivLo() { return Type_DivLo(0); }
 
  static Type_DivLo ones_DivLo() { return Type_DivLo(Type_DivLo::Type(-1)); }
 
  //--- DivHi

  Type_DivHi get_DivHi() { return Type_DivHi(rw.template get<uint32>(0x4)); }
 
  void set_DivHi(Type_DivHi value) { rw.set(0x4,value.value); }
 
  Setter<Type_DivHi> to_DivHi() { return Setter<Type_DivHi>(rw,0x4); }
 
  static Type_DivHi null_DivHi() { return Type_DivHi(0); }
 
  static Type_DivHi ones_DivHi() { return Type_DivHi(Type_DivHi::Type(-1)); }
 
  //--- IntStatus

  Type_IntStatus get_IntStatus() { return Type_IntStatus(rw.template get<uint32>(0x8)); }
 
  static Type_IntStatus null_IntStatus() { return Type_IntStatus(0); }
 
  static Type_IntStatus ones_IntStatus() { return Type_IntStatus(Type_IntStatus::Type(-1)); }
 
  //--- FIFOControl

  void set_FIFOControl(Type_FIFOControl value) { rw.set(0x8,value.value); }
 
  Setter<Type_FIFOControl> to_FIFOControl() { return Setter<Type_FIFOControl>(rw,0x8); }
 
  static Type_FIFOControl null_FIFOControl() { return Type_FIFOControl(0); }
 
  static Type_FIFOControl ones_FIFOControl() { return Type_FIFOControl(Type_FIFOControl::Type(-1)); }
 
  //--- LineControl

  Type_LineControl get_LineControl() { return Type_LineControl(rw.template get<uint32>(0xC)); }
 
  void set_LineControl(Type_LineControl value) { rw.set(0xC,value.value); }
 
  Setter<Type_LineControl> to_LineControl() { return Setter<Type_LineControl>(rw,0xC); }
 
  static Type_LineControl null_LineControl() { return Type_LineControl(0); }
 
  static Type_LineControl ones_LineControl() { return Type_LineControl(Type_LineControl::Type(-1)); }
 
  //--- ModemControl

  Type_ModemControl get_ModemControl() { return Type_ModemControl(rw.template get<uint32>(0x10)); }
 
  void set_ModemControl(Type_ModemControl value) { rw.set(0x10,value.value); }
 
  Setter<Type_ModemControl> to_ModemControl() { return Setter<Type_ModemControl>(rw,0x10); }
 
  static Type_ModemControl null_ModemControl() { return Type_ModemControl(0); }
 
  static Type_ModemControl ones_ModemControl() { return Type_ModemControl(Type_ModemControl::Type(-1)); }
 
  //--- LineStatus

  Type_LineStatus get_LineStatus() { return Type_LineStatus(rw.template get<uint32>(0x14)); }
 
  static Type_LineStatus null_LineStatus() { return Type_LineStatus(0); }
 
  static Type_LineStatus ones_LineStatus() { return Type_LineStatus(Type_LineStatus::Type(-1)); }
 
  //--- ModemStatus

  Type_ModemStatus get_ModemStatus() { return Type_ModemStatus(rw.template get<uint32>(0x18)); }
 
  static Type_ModemStatus null_ModemStatus() { return Type_ModemStatus(0); }
 
  static Type_ModemStatus ones_ModemStatus() { return Type_ModemStatus(Type_ModemStatus::Type(-1)); }
 
  //--- Scratch

  Type_Scratch get_Scratch() { return Type_Scratch(rw.template get<uint32>(0x1C)); }
 
  void set_Scratch(Type_Scratch value) { rw.set(0x1C,value.value); }
 
  Setter<Type_Scratch> to_Scratch() { return Setter<Type_Scratch>(rw,0x1C); }
 
  static Type_Scratch null_Scratch() { return Type_Scratch(0); }
 
  static Type_Scratch ones_Scratch() { return Type_Scratch(Type_Scratch::Type(-1)); }
 
 };
 
