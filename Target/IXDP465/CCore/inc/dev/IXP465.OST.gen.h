/* IXP465.OST.gen.h */ 

/* struct Type_Status */ 

enum Bits_Status : uint32
 {
  Status_T0        = 0x00000001,
  Status_T1        = 0x00000002,
  Status_TS        = 0x00000004,
  Status_WD        = 0x00000008,
  Status_WarmReset = 0x00000010
 };
 
inline Bits_Status operator | (Bits_Status a,Bits_Status b)
 { return Bits_Status(uint32(a)|uint32(b)); }
 
struct Type_Status
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Status(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Status & setTo(Bar &bar) { bar.set_Status(*this); return *this; }
 

  template <class Bar>
  Type_Status & setTo(Bar &bar,uint32 ind) { bar.set_Status(*this,ind); return *this; }
 

  template <class T>
  Type_Status & set(T to) { to(*this); return *this; }
 

  Type_Status & setbit(Bits_Status bits) { value|=Type(bits); return *this; }
 
  Type_Status & setbitIf(bool cond,Bits_Status bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Status & clearbit(Bits_Status bits) { value&=~Type(bits); return *this; }
 
  Type_Status & clearbitIf(bool cond,Bits_Status bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Status bits) const { return value&bits; }
 
  bool testbit(Bits_Status bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Status_T0 )
      {
       if( first )
         {
          Putobj(out,"T0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T0");
         }
      }

    if( value&Status_T1 )
      {
       if( first )
         {
          Putobj(out,"T1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T1");
         }
      }

    if( value&Status_TS )
      {
       if( first )
         {
          Putobj(out,"TS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TS");
         }
      }

    if( value&Status_WD )
      {
       if( first )
         {
          Putobj(out,"WD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WD");
         }
      }

    if( value&Status_WarmReset )
      {
       if( first )
         {
          Putobj(out,"WarmReset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WarmReset");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TS */ 

typedef uint32 Type_TS;

/* type Type_TSCmp */ 

typedef uint32 Type_TSCmp;

/* struct Type_TSCfg */ 

enum Bits_TSCfg : uint32
 {
  TSCfg_MHz50 = 0x00000001,
  TSCfg_Pause = 0x00000002
 };
 
inline Bits_TSCfg operator | (Bits_TSCfg a,Bits_TSCfg b)
 { return Bits_TSCfg(uint32(a)|uint32(b)); }
 
struct Type_TSCfg
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TSCfg(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TSCfg & setTo(Bar &bar) { bar.set_TSCfg(*this); return *this; }
 

  template <class Bar>
  Type_TSCfg & setTo(Bar &bar,uint32 ind) { bar.set_TSCfg(*this,ind); return *this; }
 

  template <class T>
  Type_TSCfg & set(T to) { to(*this); return *this; }
 

  Type_TSCfg & setbit(Bits_TSCfg bits) { value|=Type(bits); return *this; }
 
  Type_TSCfg & setbitIf(bool cond,Bits_TSCfg bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TSCfg & clearbit(Bits_TSCfg bits) { value&=~Type(bits); return *this; }
 
  Type_TSCfg & clearbitIf(bool cond,Bits_TSCfg bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TSCfg bits) const { return value&bits; }
 
  bool testbit(Bits_TSCfg bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TSCfg_MHz50 )
      {
       if( first )
         {
          Putobj(out,"MHz50");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MHz50");
         }
      }

    if( value&TSCfg_Pause )
      {
       if( first )
         {
          Putobj(out,"Pause");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pause");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TSPrescale */ 

struct Type_TSPrescale
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TSPrescale(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TSPrescale & setTo(Bar &bar) { bar.set_TSPrescale(*this); return *this; }
 

  template <class Bar>
  Type_TSPrescale & setTo(Bar &bar,uint32 ind) { bar.set_TSPrescale(*this,ind); return *this; }
 

  template <class T>
  Type_TSPrescale & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_TSPrescale & set_Div(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

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
 
/* type Type_T0 */ 

typedef uint32 Type_T0;

/* struct Type_T0Reload */ 

enum Bits_T0Reload : uint32
 {
  T0Reload_Enable   = 0x00000001,
  T0Reload_OneShort = 0x00000002
 };
 
inline Bits_T0Reload operator | (Bits_T0Reload a,Bits_T0Reload b)
 { return Bits_T0Reload(uint32(a)|uint32(b)); }
 
struct Type_T0Reload
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T0Reload(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T0Reload & setTo(Bar &bar) { bar.set_T0Reload(*this); return *this; }
 

  template <class Bar>
  Type_T0Reload & setTo(Bar &bar,uint32 ind) { bar.set_T0Reload(*this,ind); return *this; }
 

  template <class T>
  Type_T0Reload & set(T to) { to(*this); return *this; }
 

  Type_T0Reload & setbit(Bits_T0Reload bits) { value|=Type(bits); return *this; }
 
  Type_T0Reload & setbitIf(bool cond,Bits_T0Reload bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_T0Reload & clearbit(Bits_T0Reload bits) { value&=~Type(bits); return *this; }
 
  Type_T0Reload & clearbitIf(bool cond,Bits_T0Reload bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_T0Reload bits) const { return value&bits; }
 
  bool testbit(Bits_T0Reload bits) const { return (value&bits)==Type(bits); }
 

  Type get_Reload() const
   {
    return (value>>2)&0x3FFFFFFF;
   }
 
  Type_T0Reload & set_Reload(Type field)
   {
    value=((field&0x3FFFFFFF)<<2)|(value&0x3);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&T0Reload_Enable )
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

    if( value&T0Reload_OneShort )
      {
       if( first )
         {
          Putobj(out,"OneShort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OneShort");
         }
      }

    if( first )
      {
       Printf(out,"Reload(#;)",get_Reload());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Reload(#;)",get_Reload());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_T0Cfg */ 

enum Bits_T0Cfg : uint32
 {
  T0Cfg_MHz50 = 0x00000004,
  T0Cfg_Pause = 0x00000008
 };
 
inline Bits_T0Cfg operator | (Bits_T0Cfg a,Bits_T0Cfg b)
 { return Bits_T0Cfg(uint32(a)|uint32(b)); }
 
struct Type_T0Cfg
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T0Cfg(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T0Cfg & setTo(Bar &bar) { bar.set_T0Cfg(*this); return *this; }
 

  template <class Bar>
  Type_T0Cfg & setTo(Bar &bar,uint32 ind) { bar.set_T0Cfg(*this,ind); return *this; }
 

  template <class T>
  Type_T0Cfg & set(T to) { to(*this); return *this; }
 

  Type_T0Cfg & setbit(Bits_T0Cfg bits) { value|=Type(bits); return *this; }
 
  Type_T0Cfg & setbitIf(bool cond,Bits_T0Cfg bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_T0Cfg & clearbit(Bits_T0Cfg bits) { value&=~Type(bits); return *this; }
 
  Type_T0Cfg & clearbitIf(bool cond,Bits_T0Cfg bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_T0Cfg bits) const { return value&bits; }
 
  bool testbit(Bits_T0Cfg bits) const { return (value&bits)==Type(bits); }
 

  Type get_Reload() const
   {
    return (value>>0)&0x3;
   }
 
  Type_T0Cfg & set_Reload(Type field)
   {
    value=((field&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&T0Cfg_MHz50 )
      {
       if( first )
         {
          Putobj(out,"MHz50");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MHz50");
         }
      }

    if( value&T0Cfg_Pause )
      {
       if( first )
         {
          Putobj(out,"Pause");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pause");
         }
      }

    if( first )
      {
       Printf(out,"Reload(#;)",get_Reload());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Reload(#;)",get_Reload());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_T0Prescale */ 

struct Type_T0Prescale
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T0Prescale(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T0Prescale & setTo(Bar &bar) { bar.set_T0Prescale(*this); return *this; }
 

  template <class Bar>
  Type_T0Prescale & setTo(Bar &bar,uint32 ind) { bar.set_T0Prescale(*this,ind); return *this; }
 

  template <class T>
  Type_T0Prescale & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_T0Prescale & set_Div(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

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
 
/* type Type_T1 */ 

typedef uint32 Type_T1;

/* struct Type_T1Reload */ 

enum Bits_T1Reload : uint32
 {
  T1Reload_Enable   = 0x00000001,
  T1Reload_OneShort = 0x00000002
 };
 
inline Bits_T1Reload operator | (Bits_T1Reload a,Bits_T1Reload b)
 { return Bits_T1Reload(uint32(a)|uint32(b)); }
 
struct Type_T1Reload
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T1Reload(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T1Reload & setTo(Bar &bar) { bar.set_T1Reload(*this); return *this; }
 

  template <class Bar>
  Type_T1Reload & setTo(Bar &bar,uint32 ind) { bar.set_T1Reload(*this,ind); return *this; }
 

  template <class T>
  Type_T1Reload & set(T to) { to(*this); return *this; }
 

  Type_T1Reload & setbit(Bits_T1Reload bits) { value|=Type(bits); return *this; }
 
  Type_T1Reload & setbitIf(bool cond,Bits_T1Reload bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_T1Reload & clearbit(Bits_T1Reload bits) { value&=~Type(bits); return *this; }
 
  Type_T1Reload & clearbitIf(bool cond,Bits_T1Reload bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_T1Reload bits) const { return value&bits; }
 
  bool testbit(Bits_T1Reload bits) const { return (value&bits)==Type(bits); }
 

  Type get_Reload() const
   {
    return (value>>2)&0x3FFFFFFF;
   }
 
  Type_T1Reload & set_Reload(Type field)
   {
    value=((field&0x3FFFFFFF)<<2)|(value&0x3);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&T1Reload_Enable )
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

    if( value&T1Reload_OneShort )
      {
       if( first )
         {
          Putobj(out,"OneShort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OneShort");
         }
      }

    if( first )
      {
       Printf(out,"Reload(#;)",get_Reload());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Reload(#;)",get_Reload());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_T1Cfg */ 

enum Bits_T1Cfg : uint32
 {
  T1Cfg_MHz50 = 0x00000004,
  T1Cfg_Pause = 0x00000008
 };
 
inline Bits_T1Cfg operator | (Bits_T1Cfg a,Bits_T1Cfg b)
 { return Bits_T1Cfg(uint32(a)|uint32(b)); }
 
struct Type_T1Cfg
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T1Cfg(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T1Cfg & setTo(Bar &bar) { bar.set_T1Cfg(*this); return *this; }
 

  template <class Bar>
  Type_T1Cfg & setTo(Bar &bar,uint32 ind) { bar.set_T1Cfg(*this,ind); return *this; }
 

  template <class T>
  Type_T1Cfg & set(T to) { to(*this); return *this; }
 

  Type_T1Cfg & setbit(Bits_T1Cfg bits) { value|=Type(bits); return *this; }
 
  Type_T1Cfg & setbitIf(bool cond,Bits_T1Cfg bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_T1Cfg & clearbit(Bits_T1Cfg bits) { value&=~Type(bits); return *this; }
 
  Type_T1Cfg & clearbitIf(bool cond,Bits_T1Cfg bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_T1Cfg bits) const { return value&bits; }
 
  bool testbit(Bits_T1Cfg bits) const { return (value&bits)==Type(bits); }
 

  Type get_Reload() const
   {
    return (value>>0)&0x3;
   }
 
  Type_T1Cfg & set_Reload(Type field)
   {
    value=((field&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&T1Cfg_MHz50 )
      {
       if( first )
         {
          Putobj(out,"MHz50");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MHz50");
         }
      }

    if( value&T1Cfg_Pause )
      {
       if( first )
         {
          Putobj(out,"Pause");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Pause");
         }
      }

    if( first )
      {
       Printf(out,"Reload(#;)",get_Reload());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Reload(#;)",get_Reload());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_T1Prescale */ 

struct Type_T1Prescale
 {
  typedef uint32 Type;

  Type value;


  explicit Type_T1Prescale(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_T1Prescale & setTo(Bar &bar) { bar.set_T1Prescale(*this); return *this; }
 

  template <class Bar>
  Type_T1Prescale & setTo(Bar &bar,uint32 ind) { bar.set_T1Prescale(*this,ind); return *this; }
 

  template <class T>
  Type_T1Prescale & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_T1Prescale & set_Div(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

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
 
/* type Type_WD */ 

typedef uint32 Type_WD;

/* struct Type_WDKey */ 

enum Field_WDKey_Key : uint32
 {
  WDKey_Key_Open  = 0x482E,
  WDKey_Key_Close = 0x0000
 };
 
struct PrintField_WDKey_Key
 {
  Field_WDKey_Key field;

  explicit PrintField_WDKey_Key(Field_WDKey_Key field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x482E : Putobj(out,"Open"); break;
       case 0x0000 : Putobj(out,"Close"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_WDKey_Key GetTextDesc(Field_WDKey_Key field)
 {
  return PrintField_WDKey_Key(field);
 }
 
struct Type_WDKey
 {
  typedef uint32 Type;

  Type value;


  explicit Type_WDKey(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WDKey & setTo(Bar &bar) { bar.set_WDKey(*this); return *this; }
 

  template <class Bar>
  Type_WDKey & setTo(Bar &bar,uint32 ind) { bar.set_WDKey(*this,ind); return *this; }
 

  template <class T>
  Type_WDKey & set(T to) { to(*this); return *this; }
 

  Field_WDKey_Key get_Key() const
   {
    return Field_WDKey_Key((value>>0)&0xFFFF);
   }
 
  Type_WDKey & set_Key(Field_WDKey_Key field)
   {
    value=((Type(field)&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Key(#;)",get_Key());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Key(#;)",get_Key());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WDControl */ 

enum Bits_WDControl : uint32
 {
  WDControl_Reset  = 0x00000001,
  WDControl_Int    = 0x00000002,
  WDControl_Enable = 0x00000004
 };
 
inline Bits_WDControl operator | (Bits_WDControl a,Bits_WDControl b)
 { return Bits_WDControl(uint32(a)|uint32(b)); }
 
struct Type_WDControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_WDControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WDControl & setTo(Bar &bar) { bar.set_WDControl(*this); return *this; }
 

  template <class Bar>
  Type_WDControl & setTo(Bar &bar,uint32 ind) { bar.set_WDControl(*this,ind); return *this; }
 

  template <class T>
  Type_WDControl & set(T to) { to(*this); return *this; }
 

  Type_WDControl & setbit(Bits_WDControl bits) { value|=Type(bits); return *this; }
 
  Type_WDControl & setbitIf(bool cond,Bits_WDControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WDControl & clearbit(Bits_WDControl bits) { value&=~Type(bits); return *this; }
 
  Type_WDControl & clearbitIf(bool cond,Bits_WDControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WDControl bits) const { return value&bits; }
 
  bool testbit(Bits_WDControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WDControl_Reset )
      {
       if( first )
         {
          Putobj(out,"Reset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Reset");
         }
      }

    if( value&WDControl_Int )
      {
       if( first )
         {
          Putobj(out,"Int");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Int");
         }
      }

    if( value&WDControl_Enable )
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

    if( first ) out.put('0');
   }
 };
 
/* struct OSTBar<RW> */ 

template <class RW>
struct OSTBar
 {
  RW rw;

  template <class ... TT>
  OSTBar(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- TS

  Type_TS get_TS() { return Type_TS(rw.template get<uint32>(0x0)); }
 
  void set_TS(Type_TS value) { rw.set(0x0,value); }
 
  void set_TS_null() { rw.set(0x0,Type_TS(0)); }
 
  void set_TS_ones() { rw.set(0x0,Type_TS(-1)); }
 
  //--- T0

  Type_T0 get_T0() { return Type_T0(rw.template get<uint32>(0x4)); }
 
  //--- T0Reload

  Type_T0Reload get_T0Reload() { return Type_T0Reload(rw.template get<uint32>(0x8)); }
 
  void set_T0Reload(Type_T0Reload value) { rw.set(0x8,value.value); }
 
  Setter<Type_T0Reload> to_T0Reload() { return Setter<Type_T0Reload>(rw,0x8); }
 
  static Type_T0Reload null_T0Reload() { return Type_T0Reload(0); }
 
  static Type_T0Reload ones_T0Reload() { return Type_T0Reload(Type_T0Reload::Type(-1)); }
 
  //--- T1

  Type_T1 get_T1() { return Type_T1(rw.template get<uint32>(0xC)); }
 
  //--- T1Reload

  Type_T1Reload get_T1Reload() { return Type_T1Reload(rw.template get<uint32>(0x10)); }
 
  void set_T1Reload(Type_T1Reload value) { rw.set(0x10,value.value); }
 
  Setter<Type_T1Reload> to_T1Reload() { return Setter<Type_T1Reload>(rw,0x10); }
 
  static Type_T1Reload null_T1Reload() { return Type_T1Reload(0); }
 
  static Type_T1Reload ones_T1Reload() { return Type_T1Reload(Type_T1Reload::Type(-1)); }
 
  //--- WD

  Type_WD get_WD() { return Type_WD(rw.template get<uint32>(0x14)); }
 
  void set_WD(Type_WD value) { rw.set(0x14,value); }
 
  void set_WD_null() { rw.set(0x14,Type_WD(0)); }
 
  void set_WD_ones() { rw.set(0x14,Type_WD(-1)); }
 
  //--- WDControl

  Type_WDControl get_WDControl() { return Type_WDControl(rw.template get<uint32>(0x18)); }
 
  void set_WDControl(Type_WDControl value) { rw.set(0x18,value.value); }
 
  Setter<Type_WDControl> to_WDControl() { return Setter<Type_WDControl>(rw,0x18); }
 
  static Type_WDControl null_WDControl() { return Type_WDControl(0); }
 
  static Type_WDControl ones_WDControl() { return Type_WDControl(Type_WDControl::Type(-1)); }
 
  //--- WDKey

  Type_WDKey get_WDKey() { return Type_WDKey(rw.template get<uint32>(0x1C)); }
 
  void set_WDKey(Type_WDKey value) { rw.set(0x1C,value.value); }
 
  Setter<Type_WDKey> to_WDKey() { return Setter<Type_WDKey>(rw,0x1C); }
 
  static Type_WDKey null_WDKey() { return Type_WDKey(0); }
 
  static Type_WDKey ones_WDKey() { return Type_WDKey(Type_WDKey::Type(-1)); }
 
  //--- Status

  Type_Status get_Status() { return Type_Status(rw.template get<uint32>(0x20)); }
 
  void set_Status(Type_Status value) { rw.set(0x20,value.value); }
 
  Setter<Type_Status> to_Status() { return Setter<Type_Status>(rw,0x20); }
 
  static Type_Status null_Status() { return Type_Status(0); }
 
  static Type_Status ones_Status() { return Type_Status(Type_Status::Type(-1)); }
 
  //--- TSCmp

  Type_TSCmp get_TSCmp() { return Type_TSCmp(rw.template get<uint32>(0x24)); }
 
  void set_TSCmp(Type_TSCmp value) { rw.set(0x24,value); }
 
  void set_TSCmp_null() { rw.set(0x24,Type_TSCmp(0)); }
 
  void set_TSCmp_ones() { rw.set(0x24,Type_TSCmp(-1)); }
 
  //--- TSCfg

  Type_TSCfg get_TSCfg() { return Type_TSCfg(rw.template get<uint32>(0x28)); }
 
  void set_TSCfg(Type_TSCfg value) { rw.set(0x28,value.value); }
 
  Setter<Type_TSCfg> to_TSCfg() { return Setter<Type_TSCfg>(rw,0x28); }
 
  static Type_TSCfg null_TSCfg() { return Type_TSCfg(0); }
 
  static Type_TSCfg ones_TSCfg() { return Type_TSCfg(Type_TSCfg::Type(-1)); }
 
  //--- TSPrescale

  Type_TSPrescale get_TSPrescale() { return Type_TSPrescale(rw.template get<uint32>(0x2C)); }
 
  void set_TSPrescale(Type_TSPrescale value) { rw.set(0x2C,value.value); }
 
  Setter<Type_TSPrescale> to_TSPrescale() { return Setter<Type_TSPrescale>(rw,0x2C); }
 
  static Type_TSPrescale null_TSPrescale() { return Type_TSPrescale(0); }
 
  static Type_TSPrescale ones_TSPrescale() { return Type_TSPrescale(Type_TSPrescale::Type(-1)); }
 
  //--- T0Cfg

  Type_T0Cfg get_T0Cfg() { return Type_T0Cfg(rw.template get<uint32>(0x30)); }
 
  void set_T0Cfg(Type_T0Cfg value) { rw.set(0x30,value.value); }
 
  Setter<Type_T0Cfg> to_T0Cfg() { return Setter<Type_T0Cfg>(rw,0x30); }
 
  static Type_T0Cfg null_T0Cfg() { return Type_T0Cfg(0); }
 
  static Type_T0Cfg ones_T0Cfg() { return Type_T0Cfg(Type_T0Cfg::Type(-1)); }
 
  //--- T0Prescale

  Type_T0Prescale get_T0Prescale() { return Type_T0Prescale(rw.template get<uint32>(0x34)); }
 
  void set_T0Prescale(Type_T0Prescale value) { rw.set(0x34,value.value); }
 
  Setter<Type_T0Prescale> to_T0Prescale() { return Setter<Type_T0Prescale>(rw,0x34); }
 
  static Type_T0Prescale null_T0Prescale() { return Type_T0Prescale(0); }
 
  static Type_T0Prescale ones_T0Prescale() { return Type_T0Prescale(Type_T0Prescale::Type(-1)); }
 
  //--- T1Cfg

  Type_T1Cfg get_T1Cfg() { return Type_T1Cfg(rw.template get<uint32>(0x38)); }
 
  void set_T1Cfg(Type_T1Cfg value) { rw.set(0x38,value.value); }
 
  Setter<Type_T1Cfg> to_T1Cfg() { return Setter<Type_T1Cfg>(rw,0x38); }
 
  static Type_T1Cfg null_T1Cfg() { return Type_T1Cfg(0); }
 
  static Type_T1Cfg ones_T1Cfg() { return Type_T1Cfg(Type_T1Cfg::Type(-1)); }
 
  //--- T1Prescale

  Type_T1Prescale get_T1Prescale() { return Type_T1Prescale(rw.template get<uint32>(0x3C)); }
 
  void set_T1Prescale(Type_T1Prescale value) { rw.set(0x3C,value.value); }
 
  Setter<Type_T1Prescale> to_T1Prescale() { return Setter<Type_T1Prescale>(rw,0x3C); }
 
  static Type_T1Prescale null_T1Prescale() { return Type_T1Prescale(0); }
 
  static Type_T1Prescale ones_T1Prescale() { return Type_T1Prescale(Type_T1Prescale::Type(-1)); }
 
 };
 
