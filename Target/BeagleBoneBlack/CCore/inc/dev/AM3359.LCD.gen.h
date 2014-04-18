/* AM3359.LCD.gen.h */ 

/* struct Type_ClockEnable */ 

enum Bits_ClockEnable : uint32
 {
  ClockEnable_Core = 0x00000001,
  ClockEnable_LIDD = 0x00000002,
  ClockEnable_DMA  = 0x00000004
 };
 
inline Bits_ClockEnable operator | (Bits_ClockEnable a,Bits_ClockEnable b)
 { return Bits_ClockEnable(uint32(a)|uint32(b)); }
 
struct Type_ClockEnable
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ClockEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClockEnable & setTo(Bar &bar) { bar.set_ClockEnable(*this); return *this; }
 

  template <class Bar>
  Type_ClockEnable & setTo(Bar &bar,uint32 ind) { bar.set_ClockEnable(ind,*this); return *this; }
 

  template <class T>
  Type_ClockEnable & set(T to) { to(*this); return *this; }
 

  Type_ClockEnable & setbit(Bits_ClockEnable bits) { value|=Type(bits); return *this; }
 
  Type_ClockEnable & setbitIf(bool cond,Bits_ClockEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ClockEnable & clearbit(Bits_ClockEnable bits) { value&=~Type(bits); return *this; }
 
  Type_ClockEnable & clearbitIf(bool cond,Bits_ClockEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ClockEnable bits) const { return value&bits; }
 
  bool testbit(Bits_ClockEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ClockEnable_Core )
      {
       if( first )
         {
          Putobj(out,"Core");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Core");
         }
      }

    if( value&ClockEnable_LIDD )
      {
       if( first )
         {
          Putobj(out,"LIDD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LIDD");
         }
      }

    if( value&ClockEnable_DMA )
      {
       if( first )
         {
          Putobj(out,"DMA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMA");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Reset */ 

enum Bits_Reset : uint32
 {
  Reset_Core = 0x00000001,
  Reset_LIDD = 0x00000002,
  Reset_DMA  = 0x00000004,
  Reset_Main = 0x00000008
 };
 
inline Bits_Reset operator | (Bits_Reset a,Bits_Reset b)
 { return Bits_Reset(uint32(a)|uint32(b)); }
 
struct Type_Reset
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Reset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Reset & setTo(Bar &bar) { bar.set_Reset(*this); return *this; }
 

  template <class Bar>
  Type_Reset & setTo(Bar &bar,uint32 ind) { bar.set_Reset(ind,*this); return *this; }
 

  template <class T>
  Type_Reset & set(T to) { to(*this); return *this; }
 

  Type_Reset & setbit(Bits_Reset bits) { value|=Type(bits); return *this; }
 
  Type_Reset & setbitIf(bool cond,Bits_Reset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Reset & clearbit(Bits_Reset bits) { value&=~Type(bits); return *this; }
 
  Type_Reset & clearbitIf(bool cond,Bits_Reset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Reset bits) const { return value&bits; }
 
  bool testbit(Bits_Reset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Reset_Core )
      {
       if( first )
         {
          Putobj(out,"Core");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Core");
         }
      }

    if( value&Reset_LIDD )
      {
       if( first )
         {
          Putobj(out,"LIDD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LIDD");
         }
      }

    if( value&Reset_DMA )
      {
       if( first )
         {
          Putobj(out,"DMA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMA");
         }
      }

    if( value&Reset_Main )
      {
       if( first )
         {
          Putobj(out,"Main");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Main");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SysConfig */ 

enum Field_SysConfig_IdleMode : uint32
 {
  SysConfig_IdleMode_ForceIdle = 0x00,
  SysConfig_IdleMode_NoIdle    = 0x01,
  SysConfig_IdleMode_SmartIdle = 0x02
 };
 
struct PrintField_SysConfig_IdleMode
 {
  Field_SysConfig_IdleMode field;

  explicit PrintField_SysConfig_IdleMode(Field_SysConfig_IdleMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"ForceIdle"); break;
       case 0x01 : Putobj(out,"NoIdle"); break;
       case 0x02 : Putobj(out,"SmartIdle"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_SysConfig_IdleMode GetTextDesc(Field_SysConfig_IdleMode field)
 {
  return PrintField_SysConfig_IdleMode(field);
 }
 
enum Field_SysConfig_StandbyMode : uint32
 {
  SysConfig_StandbyMode_ForceStandby = 0x00,
  SysConfig_StandbyMode_NoStandby    = 0x01,
  SysConfig_StandbyMode_SmartStandby = 0x02
 };
 
struct PrintField_SysConfig_StandbyMode
 {
  Field_SysConfig_StandbyMode field;

  explicit PrintField_SysConfig_StandbyMode(Field_SysConfig_StandbyMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"ForceStandby"); break;
       case 0x01 : Putobj(out,"NoStandby"); break;
       case 0x02 : Putobj(out,"SmartStandby"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_SysConfig_StandbyMode GetTextDesc(Field_SysConfig_StandbyMode field)
 {
  return PrintField_SysConfig_StandbyMode(field);
 }
 
struct Type_SysConfig
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SysConfig(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SysConfig & setTo(Bar &bar) { bar.set_SysConfig(*this); return *this; }
 

  template <class Bar>
  Type_SysConfig & setTo(Bar &bar,uint32 ind) { bar.set_SysConfig(ind,*this); return *this; }
 

  template <class T>
  Type_SysConfig & set(T to) { to(*this); return *this; }
 

  Field_SysConfig_IdleMode get_IdleMode() const
   {
    return Field_SysConfig_IdleMode((value>>2)&0x3);
   }
 
  Type_SysConfig & set_IdleMode(Field_SysConfig_IdleMode field)
   {
    value=((Type(field)&0x3)<<2)|(value&0xFFFFFFF3);

    return *this;
   }
 

  Field_SysConfig_StandbyMode get_StandbyMode() const
   {
    return Field_SysConfig_StandbyMode((value>>4)&0x3);
   }
 
  Type_SysConfig & set_StandbyMode(Field_SysConfig_StandbyMode field)
   {
    value=((Type(field)&0x3)<<4)|(value&0xFFFFFFCF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"IdleMode(#;)",get_IdleMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleMode(#;)",get_IdleMode());
      }

    if( first )
      {
       Printf(out,"StandbyMode(#;)",get_StandbyMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"StandbyMode(#;)",get_StandbyMode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Control */ 

enum Bits_Control : uint32
 {
  Control_Raster           = 0x00000001,
  Control_UnderflowRestart = 0x00000002
 };
 
inline Bits_Control operator | (Bits_Control a,Bits_Control b)
 { return Bits_Control(uint32(a)|uint32(b)); }
 
struct Type_Control
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Control & setTo(Bar &bar) { bar.set_Control(*this); return *this; }
 

  template <class Bar>
  Type_Control & setTo(Bar &bar,uint32 ind) { bar.set_Control(ind,*this); return *this; }
 

  template <class T>
  Type_Control & set(T to) { to(*this); return *this; }
 

  Type_Control & setbit(Bits_Control bits) { value|=Type(bits); return *this; }
 
  Type_Control & setbitIf(bool cond,Bits_Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Control & clearbit(Bits_Control bits) { value&=~Type(bits); return *this; }
 
  Type_Control & clearbitIf(bool cond,Bits_Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Control bits) const { return value&bits; }
 
  bool testbit(Bits_Control bits) const { return (value&bits)==Type(bits); }
 

  Type get_PCLKDiv() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_Control & set_PCLKDiv(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Control_Raster )
      {
       if( first )
         {
          Putobj(out,"Raster");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Raster");
         }
      }

    if( value&Control_UnderflowRestart )
      {
       if( first )
         {
          Putobj(out,"UnderflowRestart");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UnderflowRestart");
         }
      }

    if( first )
      {
       Printf(out,"PCLKDiv(#;)",get_PCLKDiv());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PCLKDiv(#;)",get_PCLKDiv());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_LCDDMAControl */ 

enum Bits_LCDDMAControl : uint32
 {
  LCDDMAControl_TwoFB = 0x00000001
 };
 
inline Bits_LCDDMAControl operator | (Bits_LCDDMAControl a,Bits_LCDDMAControl b)
 { return Bits_LCDDMAControl(uint32(a)|uint32(b)); }
 
struct Type_LCDDMAControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_LCDDMAControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_LCDDMAControl & setTo(Bar &bar) { bar.set_LCDDMAControl(*this); return *this; }
 

  template <class Bar>
  Type_LCDDMAControl & setTo(Bar &bar,uint32 ind) { bar.set_LCDDMAControl(ind,*this); return *this; }
 

  template <class T>
  Type_LCDDMAControl & set(T to) { to(*this); return *this; }
 

  Type_LCDDMAControl & setbit(Bits_LCDDMAControl bits) { value|=Type(bits); return *this; }
 
  Type_LCDDMAControl & setbitIf(bool cond,Bits_LCDDMAControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_LCDDMAControl & clearbit(Bits_LCDDMAControl bits) { value&=~Type(bits); return *this; }
 
  Type_LCDDMAControl & clearbitIf(bool cond,Bits_LCDDMAControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_LCDDMAControl bits) const { return value&bits; }
 
  bool testbit(Bits_LCDDMAControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_BurstSize() const
   {
    return (value>>4)&0x7;
   }
 
  Type_LCDDMAControl & set_BurstSize(Type field)
   {
    value=((field&0x7)<<4)|(value&0xFFFFFF8F);

    return *this;
   }
 

  Type get_FIFOReady() const
   {
    return (value>>8)&0x7;
   }
 
  Type_LCDDMAControl & set_FIFOReady(Type field)
   {
    value=((field&0x7)<<8)|(value&0xFFFFF8FF);

    return *this;
   }
 

  Type get_DMAPri() const
   {
    return (value>>16)&0x7;
   }
 
  Type_LCDDMAControl & set_DMAPri(Type field)
   {
    value=((field&0x7)<<16)|(value&0xFFF8FFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&LCDDMAControl_TwoFB )
      {
       if( first )
         {
          Putobj(out,"TwoFB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TwoFB");
         }
      }

    if( first )
      {
       Printf(out,"BurstSize(#;)",get_BurstSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BurstSize(#;)",get_BurstSize());
      }

    if( first )
      {
       Printf(out,"FIFOReady(#;)",get_FIFOReady());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"FIFOReady(#;)",get_FIFOReady());
      }

    if( first )
      {
       Printf(out,"DMAPri(#;)",get_DMAPri());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DMAPri(#;)",get_DMAPri());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_LCDDMAFB0Base */ 

typedef uint32 Type_LCDDMAFB0Base;

/* type Type_LCDDMAFB0Lim */ 

typedef uint32 Type_LCDDMAFB0Lim;

/* type Type_LCDDMAFB1Base */ 

typedef uint32 Type_LCDDMAFB1Base;

/* type Type_LCDDMAFB1Lim */ 

typedef uint32 Type_LCDDMAFB1Lim;

/* struct Type_SplitHLen */ 

enum Bits_SplitHLen : uint32
 {
  SplitHLen_msb = 0x00000400
 };
 
inline Bits_SplitHLen operator | (Bits_SplitHLen a,Bits_SplitHLen b)
 { return Bits_SplitHLen(uint32(a)|uint32(b)); }
 
struct Type_SplitHLen
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SplitHLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SplitHLen & setTo(Bar &bar) { bar.set_SplitHLen(*this); return *this; }
 

  template <class Bar>
  Type_SplitHLen & setTo(Bar &bar,uint32 ind) { bar.set_SplitHLen(ind,*this); return *this; }
 

  template <class T>
  Type_SplitHLen & set(T to) { to(*this); return *this; }
 

  Type_SplitHLen & setbit(Bits_SplitHLen bits) { value|=Type(bits); return *this; }
 
  Type_SplitHLen & setbitIf(bool cond,Bits_SplitHLen bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SplitHLen & clearbit(Bits_SplitHLen bits) { value&=~Type(bits); return *this; }
 
  Type_SplitHLen & clearbitIf(bool cond,Bits_SplitHLen bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SplitHLen bits) const { return value&bits; }
 
  bool testbit(Bits_SplitHLen bits) const { return (value&bits)==Type(bits); }
 

  Type get_lsb() const
   {
    return (value>>4)&0x3F;
   }
 
  Type_SplitHLen & set_lsb(Type field)
   {
    value=((field&0x3F)<<4)|(value&0xFFFFFC0F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SplitHLen_msb )
      {
       if( first )
         {
          Putobj(out,"msb");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"msb");
         }
      }

    if( first )
      {
       Printf(out,"lsb(#;)",get_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"lsb(#;)",get_lsb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SplitHSync */ 

struct Type_SplitHSync
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SplitHSync(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SplitHSync & setTo(Bar &bar) { bar.set_SplitHSync(*this); return *this; }
 

  template <class Bar>
  Type_SplitHSync & setTo(Bar &bar,uint32 ind) { bar.set_SplitHSync(ind,*this); return *this; }
 

  template <class T>
  Type_SplitHSync & set(T to) { to(*this); return *this; }
 

  Type get_lsb() const
   {
    return (value>>0)&0x3F;
   }
 
  Type_SplitHSync & set_lsb(Type field)
   {
    value=((field&0x3F)<<0)|(value&0xFFFFFFC0);

    return *this;
   }
 

  Type get_msb() const
   {
    return (value>>6)&0xF;
   }
 
  Type_SplitHSync & set_msb(Type field)
   {
    value=((field&0xF)<<6)|(value&0xFFFFFC3F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"lsb(#;)",get_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"lsb(#;)",get_lsb());
      }

    if( first )
      {
       Printf(out,"msb(#;)",get_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"msb(#;)",get_msb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SplitHFront */ 

struct Type_SplitHFront
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SplitHFront(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SplitHFront & setTo(Bar &bar) { bar.set_SplitHFront(*this); return *this; }
 

  template <class Bar>
  Type_SplitHFront & setTo(Bar &bar,uint32 ind) { bar.set_SplitHFront(ind,*this); return *this; }
 

  template <class T>
  Type_SplitHFront & set(T to) { to(*this); return *this; }
 

  Type get_lsb() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_SplitHFront & set_lsb(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_msb() const
   {
    return (value>>8)&0x3;
   }
 
  Type_SplitHFront & set_msb(Type field)
   {
    value=((field&0x3)<<8)|(value&0xFFFFFCFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"lsb(#;)",get_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"lsb(#;)",get_lsb());
      }

    if( first )
      {
       Printf(out,"msb(#;)",get_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"msb(#;)",get_msb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SplitHBack */ 

struct Type_SplitHBack
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SplitHBack(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SplitHBack & setTo(Bar &bar) { bar.set_SplitHBack(*this); return *this; }
 

  template <class Bar>
  Type_SplitHBack & setTo(Bar &bar,uint32 ind) { bar.set_SplitHBack(ind,*this); return *this; }
 

  template <class T>
  Type_SplitHBack & set(T to) { to(*this); return *this; }
 

  Type get_lsb() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_SplitHBack & set_lsb(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_msb() const
   {
    return (value>>8)&0x3;
   }
 
  Type_SplitHBack & set_msb(Type field)
   {
    value=((field&0x3)<<8)|(value&0xFFFFFCFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"lsb(#;)",get_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"lsb(#;)",get_lsb());
      }

    if( first )
      {
       Printf(out,"msb(#;)",get_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"msb(#;)",get_msb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SplitVLen */ 

enum Bits_SplitVLen : uint32
 {
  SplitVLen_msb = 0x00000400
 };
 
inline Bits_SplitVLen operator | (Bits_SplitVLen a,Bits_SplitVLen b)
 { return Bits_SplitVLen(uint32(a)|uint32(b)); }
 
struct Type_SplitVLen
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SplitVLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SplitVLen & setTo(Bar &bar) { bar.set_SplitVLen(*this); return *this; }
 

  template <class Bar>
  Type_SplitVLen & setTo(Bar &bar,uint32 ind) { bar.set_SplitVLen(ind,*this); return *this; }
 

  template <class T>
  Type_SplitVLen & set(T to) { to(*this); return *this; }
 

  Type_SplitVLen & setbit(Bits_SplitVLen bits) { value|=Type(bits); return *this; }
 
  Type_SplitVLen & setbitIf(bool cond,Bits_SplitVLen bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SplitVLen & clearbit(Bits_SplitVLen bits) { value&=~Type(bits); return *this; }
 
  Type_SplitVLen & clearbitIf(bool cond,Bits_SplitVLen bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SplitVLen bits) const { return value&bits; }
 
  bool testbit(Bits_SplitVLen bits) const { return (value&bits)==Type(bits); }
 

  Type get_lsb() const
   {
    return (value>>0)&0x3FF;
   }
 
  Type_SplitVLen & set_lsb(Type field)
   {
    value=((field&0x3FF)<<0)|(value&0xFFFFFC00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SplitVLen_msb )
      {
       if( first )
         {
          Putobj(out,"msb");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"msb");
         }
      }

    if( first )
      {
       Printf(out,"lsb(#;)",get_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"lsb(#;)",get_lsb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RasterTiming0 */ 

enum Bits_RasterTiming0 : uint32
 {
  RasterTiming0_HLen_msb = 0x00000008
 };
 
inline Bits_RasterTiming0 operator | (Bits_RasterTiming0 a,Bits_RasterTiming0 b)
 { return Bits_RasterTiming0(uint32(a)|uint32(b)); }
 
struct Type_RasterTiming0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RasterTiming0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RasterTiming0 & setTo(Bar &bar) { bar.set_RasterTiming0(*this); return *this; }
 

  template <class Bar>
  Type_RasterTiming0 & setTo(Bar &bar,uint32 ind) { bar.set_RasterTiming0(ind,*this); return *this; }
 

  template <class T>
  Type_RasterTiming0 & set(T to) { to(*this); return *this; }
 

  Type_RasterTiming0 & setbit(Bits_RasterTiming0 bits) { value|=Type(bits); return *this; }
 
  Type_RasterTiming0 & setbitIf(bool cond,Bits_RasterTiming0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RasterTiming0 & clearbit(Bits_RasterTiming0 bits) { value&=~Type(bits); return *this; }
 
  Type_RasterTiming0 & clearbitIf(bool cond,Bits_RasterTiming0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RasterTiming0 bits) const { return value&bits; }
 
  bool testbit(Bits_RasterTiming0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_HLen_lsb() const
   {
    return (value>>4)&0x3F;
   }
 
  Type_RasterTiming0 & set_HLen_lsb(Type field)
   {
    value=((field&0x3F)<<4)|(value&0xFFFFFC0F);

    return *this;
   }
 

  Type get_HSync_lsb() const
   {
    return (value>>10)&0x3F;
   }
 
  Type_RasterTiming0 & set_HSync_lsb(Type field)
   {
    value=((field&0x3F)<<10)|(value&0xFFFF03FF);

    return *this;
   }
 

  Type get_HFront_lsb() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_RasterTiming0 & set_HFront_lsb(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_HBack_lsb() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_RasterTiming0 & set_HBack_lsb(Type field)
   {
    value=((field&0xFF)<<24)|(value&0xFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RasterTiming0_HLen_msb )
      {
       if( first )
         {
          Putobj(out,"HLen_msb");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HLen_msb");
         }
      }

    if( first )
      {
       Printf(out,"HLen_lsb(#;)",get_HLen_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HLen_lsb(#;)",get_HLen_lsb());
      }

    if( first )
      {
       Printf(out,"HSync_lsb(#;)",get_HSync_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HSync_lsb(#;)",get_HSync_lsb());
      }

    if( first )
      {
       Printf(out,"HFront_lsb(#;)",get_HFront_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HFront_lsb(#;)",get_HFront_lsb());
      }

    if( first )
      {
       Printf(out,"HBack_lsb(#;)",get_HBack_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HBack_lsb(#;)",get_HBack_lsb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RasterTiming1 */ 

struct Type_RasterTiming1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RasterTiming1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RasterTiming1 & setTo(Bar &bar) { bar.set_RasterTiming1(*this); return *this; }
 

  template <class Bar>
  Type_RasterTiming1 & setTo(Bar &bar,uint32 ind) { bar.set_RasterTiming1(ind,*this); return *this; }
 

  template <class T>
  Type_RasterTiming1 & set(T to) { to(*this); return *this; }
 

  Type get_VLen_lsb() const
   {
    return (value>>0)&0x3FF;
   }
 
  Type_RasterTiming1 & set_VLen_lsb(Type field)
   {
    value=((field&0x3FF)<<0)|(value&0xFFFFFC00);

    return *this;
   }
 

  Type get_VSync() const
   {
    return (value>>10)&0x3F;
   }
 
  Type_RasterTiming1 & set_VSync(Type field)
   {
    value=((field&0x3F)<<10)|(value&0xFFFF03FF);

    return *this;
   }
 

  Type get_VFront() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_RasterTiming1 & set_VFront(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_VBack() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_RasterTiming1 & set_VBack(Type field)
   {
    value=((field&0xFF)<<24)|(value&0xFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"VLen_lsb(#;)",get_VLen_lsb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VLen_lsb(#;)",get_VLen_lsb());
      }

    if( first )
      {
       Printf(out,"VSync(#;)",get_VSync());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VSync(#;)",get_VSync());
      }

    if( first )
      {
       Printf(out,"VFront(#;)",get_VFront());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VFront(#;)",get_VFront());
      }

    if( first )
      {
       Printf(out,"VBack(#;)",get_VBack());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VBack(#;)",get_VBack());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RasterTiming2 */ 

enum Bits_RasterTiming2 : uint32
 {
  RasterTiming2_InvVSync = 0x00100000,
  RasterTiming2_InvHSync = 0x00200000,
  RasterTiming2_InvPCLK  = 0x00400000,
  RasterTiming2_InvOE    = 0x00800000,
  RasterTiming2_FallEdge = 0x01000000,
  RasterTiming2_SyncEdge = 0x02000000,
  RasterTiming2_VLen_msb = 0x04000000
 };
 
inline Bits_RasterTiming2 operator | (Bits_RasterTiming2 a,Bits_RasterTiming2 b)
 { return Bits_RasterTiming2(uint32(a)|uint32(b)); }
 
struct Type_RasterTiming2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RasterTiming2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RasterTiming2 & setTo(Bar &bar) { bar.set_RasterTiming2(*this); return *this; }
 

  template <class Bar>
  Type_RasterTiming2 & setTo(Bar &bar,uint32 ind) { bar.set_RasterTiming2(ind,*this); return *this; }
 

  template <class T>
  Type_RasterTiming2 & set(T to) { to(*this); return *this; }
 

  Type_RasterTiming2 & setbit(Bits_RasterTiming2 bits) { value|=Type(bits); return *this; }
 
  Type_RasterTiming2 & setbitIf(bool cond,Bits_RasterTiming2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RasterTiming2 & clearbit(Bits_RasterTiming2 bits) { value&=~Type(bits); return *this; }
 
  Type_RasterTiming2 & clearbitIf(bool cond,Bits_RasterTiming2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RasterTiming2 bits) const { return value&bits; }
 
  bool testbit(Bits_RasterTiming2 bits) const { return (value&bits)==Type(bits); }
 

  Type get_HFront_msb() const
   {
    return (value>>0)&0x3;
   }
 
  Type_RasterTiming2 & set_HFront_msb(Type field)
   {
    value=((field&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Type get_HBack_msb() const
   {
    return (value>>4)&0x3;
   }
 
  Type_RasterTiming2 & set_HBack_msb(Type field)
   {
    value=((field&0x3)<<4)|(value&0xFFFFFFCF);

    return *this;
   }
 

  Type get_HSync_msb() const
   {
    return (value>>27)&0xF;
   }
 
  Type_RasterTiming2 & set_HSync_msb(Type field)
   {
    value=((field&0xF)<<27)|(value&0x87FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RasterTiming2_InvVSync )
      {
       if( first )
         {
          Putobj(out,"InvVSync");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InvVSync");
         }
      }

    if( value&RasterTiming2_InvHSync )
      {
       if( first )
         {
          Putobj(out,"InvHSync");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InvHSync");
         }
      }

    if( value&RasterTiming2_InvPCLK )
      {
       if( first )
         {
          Putobj(out,"InvPCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InvPCLK");
         }
      }

    if( value&RasterTiming2_InvOE )
      {
       if( first )
         {
          Putobj(out,"InvOE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InvOE");
         }
      }

    if( value&RasterTiming2_FallEdge )
      {
       if( first )
         {
          Putobj(out,"FallEdge");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FallEdge");
         }
      }

    if( value&RasterTiming2_SyncEdge )
      {
       if( first )
         {
          Putobj(out,"SyncEdge");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SyncEdge");
         }
      }

    if( value&RasterTiming2_VLen_msb )
      {
       if( first )
         {
          Putobj(out,"VLen_msb");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLen_msb");
         }
      }

    if( first )
      {
       Printf(out,"HFront_msb(#;)",get_HFront_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HFront_msb(#;)",get_HFront_msb());
      }

    if( first )
      {
       Printf(out,"HBack_msb(#;)",get_HBack_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HBack_msb(#;)",get_HBack_msb());
      }

    if( first )
      {
       Printf(out,"HSync_msb(#;)",get_HSync_msb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HSync_msb(#;)",get_HSync_msb());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RasterControl */ 

enum Bits_RasterControl : uint32
 {
  RasterControl_LCDEn         = 0x00000001,
  RasterControl_LCDTFT        = 0x00000080,
  RasterControl_STN565        = 0x01000000,
  RasterControl_TFT24         = 0x02000000,
  RasterControl_TFT24Unpacked = 0x04000000
 };
 
inline Bits_RasterControl operator | (Bits_RasterControl a,Bits_RasterControl b)
 { return Bits_RasterControl(uint32(a)|uint32(b)); }
 
enum Field_RasterControl_PalMode : uint32
 {
  RasterControl_PalMode_Both = 0x00,
  RasterControl_PalMode_Pal  = 0x01,
  RasterControl_PalMode_Data = 0x02
 };
 
struct PrintField_RasterControl_PalMode
 {
  Field_RasterControl_PalMode field;

  explicit PrintField_RasterControl_PalMode(Field_RasterControl_PalMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Both"); break;
       case 0x01 : Putobj(out,"Pal"); break;
       case 0x02 : Putobj(out,"Data"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_RasterControl_PalMode GetTextDesc(Field_RasterControl_PalMode field)
 {
  return PrintField_RasterControl_PalMode(field);
 }
 
struct Type_RasterControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RasterControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RasterControl & setTo(Bar &bar) { bar.set_RasterControl(*this); return *this; }
 

  template <class Bar>
  Type_RasterControl & setTo(Bar &bar,uint32 ind) { bar.set_RasterControl(ind,*this); return *this; }
 

  template <class T>
  Type_RasterControl & set(T to) { to(*this); return *this; }
 

  Type_RasterControl & setbit(Bits_RasterControl bits) { value|=Type(bits); return *this; }
 
  Type_RasterControl & setbitIf(bool cond,Bits_RasterControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RasterControl & clearbit(Bits_RasterControl bits) { value&=~Type(bits); return *this; }
 
  Type_RasterControl & clearbitIf(bool cond,Bits_RasterControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RasterControl bits) const { return value&bits; }
 
  bool testbit(Bits_RasterControl bits) const { return (value&bits)==Type(bits); }
 

  Field_RasterControl_PalMode get_PalMode() const
   {
    return Field_RasterControl_PalMode((value>>20)&0x3);
   }
 
  Type_RasterControl & set_PalMode(Field_RasterControl_PalMode field)
   {
    value=((Type(field)&0x3)<<20)|(value&0xFFCFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RasterControl_LCDEn )
      {
       if( first )
         {
          Putobj(out,"LCDEn");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LCDEn");
         }
      }

    if( value&RasterControl_LCDTFT )
      {
       if( first )
         {
          Putobj(out,"LCDTFT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LCDTFT");
         }
      }

    if( value&RasterControl_STN565 )
      {
       if( first )
         {
          Putobj(out,"STN565");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"STN565");
         }
      }

    if( value&RasterControl_TFT24 )
      {
       if( first )
         {
          Putobj(out,"TFT24");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TFT24");
         }
      }

    if( value&RasterControl_TFT24Unpacked )
      {
       if( first )
         {
          Putobj(out,"TFT24Unpacked");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TFT24Unpacked");
         }
      }

    if( first )
      {
       Printf(out,"PalMode(#;)",get_PalMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PalMode(#;)",get_PalMode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct LCDBar<RW> */ 

template <class RW>
struct LCDBar
 {
  RW rw;

  template <class ... TT>
  LCDBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SysConfig

  Type_SysConfig get_SysConfig() { return Type_SysConfig(rw.template get<uint32>(0x54)); }
 
  void set_SysConfig(Type_SysConfig value) { rw.set(0x54,value.value); }
 
  Setter<Type_SysConfig> to_SysConfig() { return Setter<Type_SysConfig>(rw,0x54); }
 
  static Type_SysConfig null_SysConfig() { return Type_SysConfig(0); }
 
  static Type_SysConfig ones_SysConfig() { return Type_SysConfig(Type_SysConfig::Type(-1)); }
 
  //--- ClockEnable

  Type_ClockEnable get_ClockEnable() { return Type_ClockEnable(rw.template get<uint32>(0x6C)); }
 
  void set_ClockEnable(Type_ClockEnable value) { rw.set(0x6C,value.value); }
 
  Setter<Type_ClockEnable> to_ClockEnable() { return Setter<Type_ClockEnable>(rw,0x6C); }
 
  static Type_ClockEnable null_ClockEnable() { return Type_ClockEnable(0); }
 
  static Type_ClockEnable ones_ClockEnable() { return Type_ClockEnable(Type_ClockEnable::Type(-1)); }
 
  //--- Reset

  Type_Reset get_Reset() { return Type_Reset(rw.template get<uint32>(0x70)); }
 
  void set_Reset(Type_Reset value) { rw.set(0x70,value.value); }
 
  Setter<Type_Reset> to_Reset() { return Setter<Type_Reset>(rw,0x70); }
 
  static Type_Reset null_Reset() { return Type_Reset(0); }
 
  static Type_Reset ones_Reset() { return Type_Reset(Type_Reset::Type(-1)); }
 
  //--- Control

  Type_Control get_Control() { return Type_Control(rw.template get<uint32>(0x4)); }
 
  void set_Control(Type_Control value) { rw.set(0x4,value.value); }
 
  Setter<Type_Control> to_Control() { return Setter<Type_Control>(rw,0x4); }
 
  static Type_Control null_Control() { return Type_Control(0); }
 
  static Type_Control ones_Control() { return Type_Control(Type_Control::Type(-1)); }
 
  //--- LCDDMAControl

  Type_LCDDMAControl get_LCDDMAControl() { return Type_LCDDMAControl(rw.template get<uint32>(0x40)); }
 
  void set_LCDDMAControl(Type_LCDDMAControl value) { rw.set(0x40,value.value); }
 
  Setter<Type_LCDDMAControl> to_LCDDMAControl() { return Setter<Type_LCDDMAControl>(rw,0x40); }
 
  static Type_LCDDMAControl null_LCDDMAControl() { return Type_LCDDMAControl(0); }
 
  static Type_LCDDMAControl ones_LCDDMAControl() { return Type_LCDDMAControl(Type_LCDDMAControl::Type(-1)); }
 
  //--- LCDDMAFB0Base

  Type_LCDDMAFB0Base get_LCDDMAFB0Base() { return Type_LCDDMAFB0Base(rw.template get<uint32>(0x44)); }
 
  void set_LCDDMAFB0Base(Type_LCDDMAFB0Base value) { rw.set(0x44,value); }
 
  void set_LCDDMAFB0Base_null() { rw.set(0x44,Type_LCDDMAFB0Base(0)); }
 
  void set_LCDDMAFB0Base_ones() { rw.set(0x44,Type_LCDDMAFB0Base(-1)); }
 
  //--- LCDDMAFB0Lim

  Type_LCDDMAFB0Lim get_LCDDMAFB0Lim() { return Type_LCDDMAFB0Lim(rw.template get<uint32>(0x48)); }
 
  void set_LCDDMAFB0Lim(Type_LCDDMAFB0Lim value) { rw.set(0x48,value); }
 
  void set_LCDDMAFB0Lim_null() { rw.set(0x48,Type_LCDDMAFB0Lim(0)); }
 
  void set_LCDDMAFB0Lim_ones() { rw.set(0x48,Type_LCDDMAFB0Lim(-1)); }
 
  //--- LCDDMAFB1Base

  Type_LCDDMAFB1Base get_LCDDMAFB1Base() { return Type_LCDDMAFB1Base(rw.template get<uint32>(0x4C)); }
 
  void set_LCDDMAFB1Base(Type_LCDDMAFB1Base value) { rw.set(0x4C,value); }
 
  void set_LCDDMAFB1Base_null() { rw.set(0x4C,Type_LCDDMAFB1Base(0)); }
 
  void set_LCDDMAFB1Base_ones() { rw.set(0x4C,Type_LCDDMAFB1Base(-1)); }
 
  //--- LCDDMAFB1Lim

  Type_LCDDMAFB1Lim get_LCDDMAFB1Lim() { return Type_LCDDMAFB1Lim(rw.template get<uint32>(0x50)); }
 
  void set_LCDDMAFB1Lim(Type_LCDDMAFB1Lim value) { rw.set(0x50,value); }
 
  void set_LCDDMAFB1Lim_null() { rw.set(0x50,Type_LCDDMAFB1Lim(0)); }
 
  void set_LCDDMAFB1Lim_ones() { rw.set(0x50,Type_LCDDMAFB1Lim(-1)); }
 
  //--- RasterTiming0

  Type_RasterTiming0 get_RasterTiming0() { return Type_RasterTiming0(rw.template get<uint32>(0x2C)); }
 
  void set_RasterTiming0(Type_RasterTiming0 value) { rw.set(0x2C,value.value); }
 
  Setter<Type_RasterTiming0> to_RasterTiming0() { return Setter<Type_RasterTiming0>(rw,0x2C); }
 
  static Type_RasterTiming0 null_RasterTiming0() { return Type_RasterTiming0(0); }
 
  static Type_RasterTiming0 ones_RasterTiming0() { return Type_RasterTiming0(Type_RasterTiming0::Type(-1)); }
 
  //--- RasterTiming1

  Type_RasterTiming1 get_RasterTiming1() { return Type_RasterTiming1(rw.template get<uint32>(0x30)); }
 
  void set_RasterTiming1(Type_RasterTiming1 value) { rw.set(0x30,value.value); }
 
  Setter<Type_RasterTiming1> to_RasterTiming1() { return Setter<Type_RasterTiming1>(rw,0x30); }
 
  static Type_RasterTiming1 null_RasterTiming1() { return Type_RasterTiming1(0); }
 
  static Type_RasterTiming1 ones_RasterTiming1() { return Type_RasterTiming1(Type_RasterTiming1::Type(-1)); }
 
  //--- RasterTiming2

  Type_RasterTiming2 get_RasterTiming2() { return Type_RasterTiming2(rw.template get<uint32>(0x34)); }
 
  void set_RasterTiming2(Type_RasterTiming2 value) { rw.set(0x34,value.value); }
 
  Setter<Type_RasterTiming2> to_RasterTiming2() { return Setter<Type_RasterTiming2>(rw,0x34); }
 
  static Type_RasterTiming2 null_RasterTiming2() { return Type_RasterTiming2(0); }
 
  static Type_RasterTiming2 ones_RasterTiming2() { return Type_RasterTiming2(Type_RasterTiming2::Type(-1)); }
 
  //--- RasterControl

  Type_RasterControl get_RasterControl() { return Type_RasterControl(rw.template get<uint32>(0x28)); }
 
  void set_RasterControl(Type_RasterControl value) { rw.set(0x28,value.value); }
 
  Setter<Type_RasterControl> to_RasterControl() { return Setter<Type_RasterControl>(rw,0x28); }
 
  static Type_RasterControl null_RasterControl() { return Type_RasterControl(0); }
 
  static Type_RasterControl ones_RasterControl() { return Type_RasterControl(Type_RasterControl::Type(-1)); }
 
 };
 
