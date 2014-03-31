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
 
