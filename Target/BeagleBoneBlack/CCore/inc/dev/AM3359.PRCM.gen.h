/* AM3359.PRCM.gen.h */ 

/* struct Type_ClockControl */ 

enum Field_ClockControl_Mode : uint32
 {
  ClockControl_Mode_Disable = 0x00,
  ClockControl_Mode_Enable  = 0x02
 };
 
struct PrintField_ClockControl_Mode
 {
  Field_ClockControl_Mode field;

  explicit PrintField_ClockControl_Mode(Field_ClockControl_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Disable"); break;
       case 0x02 : Putobj(out,"Enable"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockControl_Mode GetTextDesc(Field_ClockControl_Mode field)
 {
  return PrintField_ClockControl_Mode(field);
 }
 
enum Field_ClockControl_IdleStatus : uint32
 {
  ClockControl_IdleStatus_Running    = 0x00,
  ClockControl_IdleStatus_Transition = 0x01,
  ClockControl_IdleStatus_Idle       = 0x02,
  ClockControl_IdleStatus_Disabled   = 0x03
 };
 
struct PrintField_ClockControl_IdleStatus
 {
  Field_ClockControl_IdleStatus field;

  explicit PrintField_ClockControl_IdleStatus(Field_ClockControl_IdleStatus field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Running"); break;
       case 0x01 : Putobj(out,"Transition"); break;
       case 0x02 : Putobj(out,"Idle"); break;
       case 0x03 : Putobj(out,"Disabled"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ClockControl_IdleStatus GetTextDesc(Field_ClockControl_IdleStatus field)
 {
  return PrintField_ClockControl_IdleStatus(field);
 }
 
struct Type_ClockControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ClockControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClockControl & setTo(Bar &bar) { bar.set_ClockControl(*this); return *this; }
 

  template <class Bar>
  Type_ClockControl & setTo(Bar &bar,uint32 ind) { bar.set_ClockControl(ind,*this); return *this; }
 

  template <class T>
  Type_ClockControl & set(T to) { to(*this); return *this; }
 

  Field_ClockControl_Mode get_Mode() const
   {
    return Field_ClockControl_Mode((value>>0)&0x3);
   }
 
  Type_ClockControl & set_Mode(Field_ClockControl_Mode field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Field_ClockControl_IdleStatus get_IdleStatus() const
   {
    return Field_ClockControl_IdleStatus((value>>16)&0x3);
   }
 
  Type_ClockControl & set_IdleStatus(Field_ClockControl_IdleStatus field)
   {
    value=((Type(field)&0x3)<<16)|(value&0xFFFCFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Mode(#;)",get_Mode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Mode(#;)",get_Mode());
      }

    if( first )
      {
       Printf(out,"IdleStatus(#;)",get_IdleStatus());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IdleStatus(#;)",get_IdleStatus());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TimerClockSelect */ 

enum Field_TimerClockSelect_Source : uint32
 {
  TimerClockSelect_Source_TCLKIN    = 0x00,
  TimerClockSelect_Source_CLK_M_OSC = 0x01,
  TimerClockSelect_Source_CLK_32KHZ = 0x02
 };
 
struct PrintField_TimerClockSelect_Source
 {
  Field_TimerClockSelect_Source field;

  explicit PrintField_TimerClockSelect_Source(Field_TimerClockSelect_Source field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"TCLKIN"); break;
       case 0x01 : Putobj(out,"CLK_M_OSC"); break;
       case 0x02 : Putobj(out,"CLK_32KHZ"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_TimerClockSelect_Source GetTextDesc(Field_TimerClockSelect_Source field)
 {
  return PrintField_TimerClockSelect_Source(field);
 }
 
struct Type_TimerClockSelect
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TimerClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TimerClockSelect & setTo(Bar &bar) { bar.set_TimerClockSelect(*this); return *this; }
 

  template <class Bar>
  Type_TimerClockSelect & setTo(Bar &bar,uint32 ind) { bar.set_TimerClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_TimerClockSelect & set(T to) { to(*this); return *this; }
 

  Field_TimerClockSelect_Source get_Source() const
   {
    return Field_TimerClockSelect_Source((value>>0)&0x3);
   }
 
  Type_TimerClockSelect & set_Source(Field_TimerClockSelect_Source field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Source(#;)",get_Source());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Source(#;)",get_Source());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MPUIdleStatus */ 

enum Bits_MPUIdleStatus : uint32
 {
  MPUIdleStatus_Locked = 0x00000001,
  MPUIdleStatus_Bypass = 0x00000100
 };
 
inline Bits_MPUIdleStatus operator | (Bits_MPUIdleStatus a,Bits_MPUIdleStatus b)
 { return Bits_MPUIdleStatus(uint32(a)|uint32(b)); }
 
struct Type_MPUIdleStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MPUIdleStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MPUIdleStatus & setTo(Bar &bar) { bar.set_MPUIdleStatus(*this); return *this; }
 

  template <class Bar>
  Type_MPUIdleStatus & setTo(Bar &bar,uint32 ind) { bar.set_MPUIdleStatus(ind,*this); return *this; }
 

  template <class T>
  Type_MPUIdleStatus & set(T to) { to(*this); return *this; }
 

  Type_MPUIdleStatus & setbit(Bits_MPUIdleStatus bits) { value|=Type(bits); return *this; }
 
  Type_MPUIdleStatus & setbitIf(bool cond,Bits_MPUIdleStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MPUIdleStatus & clearbit(Bits_MPUIdleStatus bits) { value&=~Type(bits); return *this; }
 
  Type_MPUIdleStatus & clearbitIf(bool cond,Bits_MPUIdleStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MPUIdleStatus bits) const { return value&bits; }
 
  bool testbit(Bits_MPUIdleStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MPUIdleStatus_Locked )
      {
       if( first )
         {
          Putobj(out,"Locked");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Locked");
         }
      }

    if( value&MPUIdleStatus_Bypass )
      {
       if( first )
         {
          Putobj(out,"Bypass");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Bypass");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MPUClockSelect */ 

enum Bits_MPUClockSelect : uint32
 {
  MPUClockSelect_BypassSelect = 0x00800000
 };
 
inline Bits_MPUClockSelect operator | (Bits_MPUClockSelect a,Bits_MPUClockSelect b)
 { return Bits_MPUClockSelect(uint32(a)|uint32(b)); }
 
struct Type_MPUClockSelect
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MPUClockSelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MPUClockSelect & setTo(Bar &bar) { bar.set_MPUClockSelect(*this); return *this; }
 

  template <class Bar>
  Type_MPUClockSelect & setTo(Bar &bar,uint32 ind) { bar.set_MPUClockSelect(ind,*this); return *this; }
 

  template <class T>
  Type_MPUClockSelect & set(T to) { to(*this); return *this; }
 

  Type_MPUClockSelect & setbit(Bits_MPUClockSelect bits) { value|=Type(bits); return *this; }
 
  Type_MPUClockSelect & setbitIf(bool cond,Bits_MPUClockSelect bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MPUClockSelect & clearbit(Bits_MPUClockSelect bits) { value&=~Type(bits); return *this; }
 
  Type_MPUClockSelect & clearbitIf(bool cond,Bits_MPUClockSelect bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MPUClockSelect bits) const { return value&bits; }
 
  bool testbit(Bits_MPUClockSelect bits) const { return (value&bits)==Type(bits); }
 

  Type get_Div() const
   {
    return (value>>0)&0x7F;
   }
 
  Type_MPUClockSelect & set_Div(Type field)
   {
    value=((field&0x7F)<<0)|(value&0xFFFFFF80);

    return *this;
   }
 

  Type get_Mul() const
   {
    return (value>>8)&0x7FF;
   }
 
  Type_MPUClockSelect & set_Mul(Type field)
   {
    value=((field&0x7FF)<<8)|(value&0xFFF800FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MPUClockSelect_BypassSelect )
      {
       if( first )
         {
          Putobj(out,"BypassSelect");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BypassSelect");
         }
      }

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

    if( first )
      {
       Printf(out,"Mul(#;)",get_Mul());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Mul(#;)",get_Mul());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MPUDivM2 */ 

enum Bits_MPUDivM2 : uint32
 {
  MPUDivM2_M2Ack      = 0x00000020,
  MPUDivM2_NoAutoGate = 0x00000100,
  MPUDivM2_Running    = 0x00000200
 };
 
inline Bits_MPUDivM2 operator | (Bits_MPUDivM2 a,Bits_MPUDivM2 b)
 { return Bits_MPUDivM2(uint32(a)|uint32(b)); }
 
struct Type_MPUDivM2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MPUDivM2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MPUDivM2 & setTo(Bar &bar) { bar.set_MPUDivM2(*this); return *this; }
 

  template <class Bar>
  Type_MPUDivM2 & setTo(Bar &bar,uint32 ind) { bar.set_MPUDivM2(ind,*this); return *this; }
 

  template <class T>
  Type_MPUDivM2 & set(T to) { to(*this); return *this; }
 

  Type_MPUDivM2 & setbit(Bits_MPUDivM2 bits) { value|=Type(bits); return *this; }
 
  Type_MPUDivM2 & setbitIf(bool cond,Bits_MPUDivM2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MPUDivM2 & clearbit(Bits_MPUDivM2 bits) { value&=~Type(bits); return *this; }
 
  Type_MPUDivM2 & clearbitIf(bool cond,Bits_MPUDivM2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MPUDivM2 bits) const { return value&bits; }
 
  bool testbit(Bits_MPUDivM2 bits) const { return (value&bits)==Type(bits); }
 

  Type get_M2() const
   {
    return (value>>0)&0x1F;
   }
 
  Type_MPUDivM2 & set_M2(Type field)
   {
    value=((field&0x1F)<<0)|(value&0xFFFFFFE0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MPUDivM2_M2Ack )
      {
       if( first )
         {
          Putobj(out,"M2Ack");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"M2Ack");
         }
      }

    if( value&MPUDivM2_NoAutoGate )
      {
       if( first )
         {
          Putobj(out,"NoAutoGate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoAutoGate");
         }
      }

    if( value&MPUDivM2_Running )
      {
       if( first )
         {
          Putobj(out,"Running");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Running");
         }
      }

    if( first )
      {
       Printf(out,"M2(#;)",get_M2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"M2(#;)",get_M2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MPUClockMode */ 

enum Bits_MPUClockMode : uint32
 {
  MPUClockMode_DriftGuard   = 0x00000100,
  MPUClockMode_RelockRamp   = 0x00000200,
  MPUClockMode_LPMode       = 0x00000400,
  MPUClockMode_REGM4X       = 0x00000800,
  MPUClockMode_SSC          = 0x00001000,
  MPUClockMode_SSCAck       = 0x00002000,
  MPUClockMode_SSCLowSpread = 0x00004000,
  MPUClockMode_SSCType      = 0x00008000
 };
 
inline Bits_MPUClockMode operator | (Bits_MPUClockMode a,Bits_MPUClockMode b)
 { return Bits_MPUClockMode(uint32(a)|uint32(b)); }
 
enum Field_MPUClockMode_En : uint32
 {
  MPUClockMode_En_MNBypass = 0x04,
  MPUClockMode_En_LPBypass = 0x05,
  MPUClockMode_En_FRBypass = 0x06,
  MPUClockMode_En_Lock     = 0x07
 };
 
struct PrintField_MPUClockMode_En
 {
  Field_MPUClockMode_En field;

  explicit PrintField_MPUClockMode_En(Field_MPUClockMode_En field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x04 : Putobj(out,"MNBypass"); break;
       case 0x05 : Putobj(out,"LPBypass"); break;
       case 0x06 : Putobj(out,"FRBypass"); break;
       case 0x07 : Putobj(out,"Lock"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_MPUClockMode_En GetTextDesc(Field_MPUClockMode_En field)
 {
  return PrintField_MPUClockMode_En(field);
 }
 
enum Field_MPUClockMode_RampLevel : uint32
 {
  MPUClockMode_RampLevel_No = 0x00,
  MPUClockMode_RampLevel_Lo = 0x01,
  MPUClockMode_RampLevel_Hi = 0x02
 };
 
struct PrintField_MPUClockMode_RampLevel
 {
  Field_MPUClockMode_RampLevel field;

  explicit PrintField_MPUClockMode_RampLevel(Field_MPUClockMode_RampLevel field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"No"); break;
       case 0x01 : Putobj(out,"Lo"); break;
       case 0x02 : Putobj(out,"Hi"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_MPUClockMode_RampLevel GetTextDesc(Field_MPUClockMode_RampLevel field)
 {
  return PrintField_MPUClockMode_RampLevel(field);
 }
 
struct Type_MPUClockMode
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MPUClockMode(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MPUClockMode & setTo(Bar &bar) { bar.set_MPUClockMode(*this); return *this; }
 

  template <class Bar>
  Type_MPUClockMode & setTo(Bar &bar,uint32 ind) { bar.set_MPUClockMode(ind,*this); return *this; }
 

  template <class T>
  Type_MPUClockMode & set(T to) { to(*this); return *this; }
 

  Type_MPUClockMode & setbit(Bits_MPUClockMode bits) { value|=Type(bits); return *this; }
 
  Type_MPUClockMode & setbitIf(bool cond,Bits_MPUClockMode bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MPUClockMode & clearbit(Bits_MPUClockMode bits) { value&=~Type(bits); return *this; }
 
  Type_MPUClockMode & clearbitIf(bool cond,Bits_MPUClockMode bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MPUClockMode bits) const { return value&bits; }
 
  bool testbit(Bits_MPUClockMode bits) const { return (value&bits)==Type(bits); }
 

  Field_MPUClockMode_En get_En() const
   {
    return Field_MPUClockMode_En((value>>0)&0x7);
   }
 
  Type_MPUClockMode & set_En(Field_MPUClockMode_En field)
   {
    value=((Type(field)&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Field_MPUClockMode_RampLevel get_RampLevel() const
   {
    return Field_MPUClockMode_RampLevel((value>>3)&0x3);
   }
 
  Type_MPUClockMode & set_RampLevel(Field_MPUClockMode_RampLevel field)
   {
    value=((Type(field)&0x3)<<3)|(value&0xFFFFFFE7);

    return *this;
   }
 

  Type get_RampRate() const
   {
    return (value>>5)&0x7;
   }
 
  Type_MPUClockMode & set_RampRate(Type field)
   {
    value=((field&0x7)<<5)|(value&0xFFFFFF1F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MPUClockMode_DriftGuard )
      {
       if( first )
         {
          Putobj(out,"DriftGuard");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DriftGuard");
         }
      }

    if( value&MPUClockMode_RelockRamp )
      {
       if( first )
         {
          Putobj(out,"RelockRamp");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RelockRamp");
         }
      }

    if( value&MPUClockMode_LPMode )
      {
       if( first )
         {
          Putobj(out,"LPMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LPMode");
         }
      }

    if( value&MPUClockMode_REGM4X )
      {
       if( first )
         {
          Putobj(out,"REGM4X");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"REGM4X");
         }
      }

    if( value&MPUClockMode_SSC )
      {
       if( first )
         {
          Putobj(out,"SSC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSC");
         }
      }

    if( value&MPUClockMode_SSCAck )
      {
       if( first )
         {
          Putobj(out,"SSCAck");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCAck");
         }
      }

    if( value&MPUClockMode_SSCLowSpread )
      {
       if( first )
         {
          Putobj(out,"SSCLowSpread");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCLowSpread");
         }
      }

    if( value&MPUClockMode_SSCType )
      {
       if( first )
         {
          Putobj(out,"SSCType");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSCType");
         }
      }

    if( first )
      {
       Printf(out,"En(#;)",get_En());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"En(#;)",get_En());
      }

    if( first )
      {
       Printf(out,"RampLevel(#;)",get_RampLevel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RampLevel(#;)",get_RampLevel());
      }

    if( first )
      {
       Printf(out,"RampRate(#;)",get_RampRate());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RampRate(#;)",get_RampRate());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct CM_PERBar<RW> */ 

template <class RW>
struct CM_PERBar
 {
  RW rw;

  template <class ... TT>
  CM_PERBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ClockControl

  static Type_ClockControl null_ClockControl() { return Type_ClockControl(0); }
 
  static Type_ClockControl ones_ClockControl() { return Type_ClockControl(Type_ClockControl::Type(-1)); }
 
  //--- Timer2

  Type_ClockControl get_Timer2() { return Type_ClockControl(rw.template get<uint32>(0x80)); }
 
  void set_Timer2(Type_ClockControl value) { rw.set(0x80,value.value); }
 
  Setter<Type_ClockControl> to_Timer2() { return Setter<Type_ClockControl>(rw,0x80); }
 
  //--- Timer4

  Type_ClockControl get_Timer4() { return Type_ClockControl(rw.template get<uint32>(0x88)); }
 
  void set_Timer4(Type_ClockControl value) { rw.set(0x88,value.value); }
 
  Setter<Type_ClockControl> to_Timer4() { return Setter<Type_ClockControl>(rw,0x88); }
 
 };
 
/* struct CM_DPLLBar<RW> */ 

template <class RW>
struct CM_DPLLBar
 {
  RW rw;

  template <class ... TT>
  CM_DPLLBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- TimerClockSelect

  static Type_TimerClockSelect null_TimerClockSelect() { return Type_TimerClockSelect(0); }
 
  static Type_TimerClockSelect ones_TimerClockSelect() { return Type_TimerClockSelect(Type_TimerClockSelect::Type(-1)); }
 
  //--- Timer2

  Type_TimerClockSelect get_Timer2() { return Type_TimerClockSelect(rw.template get<uint32>(0x8)); }
 
  void set_Timer2(Type_TimerClockSelect value) { rw.set(0x8,value.value); }
 
  Setter<Type_TimerClockSelect> to_Timer2() { return Setter<Type_TimerClockSelect>(rw,0x8); }
 
  //--- Timer4

  Type_TimerClockSelect get_Timer4() { return Type_TimerClockSelect(rw.template get<uint32>(0x10)); }
 
  void set_Timer4(Type_TimerClockSelect value) { rw.set(0x10,value.value); }
 
  Setter<Type_TimerClockSelect> to_Timer4() { return Setter<Type_TimerClockSelect>(rw,0x10); }
 
 };
 
/* struct CM_WKUPBar<RW> */ 

template <class RW>
struct CM_WKUPBar
 {
  RW rw;

  template <class ... TT>
  CM_WKUPBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- MPUIdleStatus

  Type_MPUIdleStatus get_MPUIdleStatus() { return Type_MPUIdleStatus(rw.template get<uint32>(0x20)); }
 
  static Type_MPUIdleStatus null_MPUIdleStatus() { return Type_MPUIdleStatus(0); }
 
  static Type_MPUIdleStatus ones_MPUIdleStatus() { return Type_MPUIdleStatus(Type_MPUIdleStatus::Type(-1)); }
 
  //--- MPUClockSelect

  Type_MPUClockSelect get_MPUClockSelect() { return Type_MPUClockSelect(rw.template get<uint32>(0x2C)); }
 
  void set_MPUClockSelect(Type_MPUClockSelect value) { rw.set(0x2C,value.value); }
 
  Setter<Type_MPUClockSelect> to_MPUClockSelect() { return Setter<Type_MPUClockSelect>(rw,0x2C); }
 
  static Type_MPUClockSelect null_MPUClockSelect() { return Type_MPUClockSelect(0); }
 
  static Type_MPUClockSelect ones_MPUClockSelect() { return Type_MPUClockSelect(Type_MPUClockSelect::Type(-1)); }
 
  //--- MPUDivM2

  Type_MPUDivM2 get_MPUDivM2() { return Type_MPUDivM2(rw.template get<uint32>(0xA8)); }
 
  void set_MPUDivM2(Type_MPUDivM2 value) { rw.set(0xA8,value.value); }
 
  Setter<Type_MPUDivM2> to_MPUDivM2() { return Setter<Type_MPUDivM2>(rw,0xA8); }
 
  static Type_MPUDivM2 null_MPUDivM2() { return Type_MPUDivM2(0); }
 
  static Type_MPUDivM2 ones_MPUDivM2() { return Type_MPUDivM2(Type_MPUDivM2::Type(-1)); }
 
  //--- MPUClockMode

  Type_MPUClockMode get_MPUClockMode() { return Type_MPUClockMode(rw.template get<uint32>(0x88)); }
 
  void set_MPUClockMode(Type_MPUClockMode value) { rw.set(0x88,value.value); }
 
  Setter<Type_MPUClockMode> to_MPUClockMode() { return Setter<Type_MPUClockMode>(rw,0x88); }
 
  static Type_MPUClockMode null_MPUClockMode() { return Type_MPUClockMode(0); }
 
  static Type_MPUClockMode ones_MPUClockMode() { return Type_MPUClockMode(Type_MPUClockMode::Type(-1)); }
 
 };
 
