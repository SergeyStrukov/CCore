/* AM3359.TIMER.gen.h */ 

/* struct Type_OCPConfig */ 

enum Bits_OCPConfig : uint32
 {
  OCPConfig_Reset   = 0x00000001,
  OCPConfig_EMUFree = 0x00000002
 };
 
inline Bits_OCPConfig operator | (Bits_OCPConfig a,Bits_OCPConfig b)
 { return Bits_OCPConfig(uint32(a)|uint32(b)); }
 
enum Field_OCPConfig_IdleMode : uint32
 {
  OCPConfig_IdleMode_ForceIdle       = 0x00,
  OCPConfig_IdleMode_NoIdle          = 0x01,
  OCPConfig_IdleMode_SmartIdle       = 0x02,
  OCPConfig_IdleMode_SmartIdleWakeup = 0x03
 };
 
struct PrintField_OCPConfig_IdleMode
 {
  Field_OCPConfig_IdleMode field;

  explicit PrintField_OCPConfig_IdleMode(Field_OCPConfig_IdleMode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"ForceIdle"); break;
       case 0x01 : Putobj(out,"NoIdle"); break;
       case 0x02 : Putobj(out,"SmartIdle"); break;
       case 0x03 : Putobj(out,"SmartIdleWakeup"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_OCPConfig_IdleMode GetTextDesc(Field_OCPConfig_IdleMode field)
 {
  return PrintField_OCPConfig_IdleMode(field);
 }
 
struct Type_OCPConfig
 {
  typedef uint32 Type;

  Type value;


  explicit Type_OCPConfig(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_OCPConfig & setTo(Bar &bar) { bar.set_OCPConfig(*this); return *this; }
 

  template <class Bar>
  Type_OCPConfig & setTo(Bar &bar,uint32 ind) { bar.set_OCPConfig(*this,ind); return *this; }
 

  template <class T>
  Type_OCPConfig & set(T to) { to(*this); return *this; }
 

  Type_OCPConfig & setbit(Bits_OCPConfig bits) { value|=Type(bits); return *this; }
 
  Type_OCPConfig & setbitIf(bool cond,Bits_OCPConfig bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_OCPConfig & clearbit(Bits_OCPConfig bits) { value&=~Type(bits); return *this; }
 
  Type_OCPConfig & clearbitIf(bool cond,Bits_OCPConfig bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_OCPConfig bits) const { return value&bits; }
 
  bool testbit(Bits_OCPConfig bits) const { return (value&bits)==Type(bits); }
 

  Field_OCPConfig_IdleMode get_IdleMode() const
   {
    return Field_OCPConfig_IdleMode((value>>2)&0x3);
   }
 
  Type_OCPConfig & set_IdleMode(Field_OCPConfig_IdleMode field)
   {
    value=((Type(field)&0x3)<<2)|(value&0xFFFFFFF3);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&OCPConfig_Reset )
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

    if( value&OCPConfig_EMUFree )
      {
       if( first )
         {
          Putobj(out,"EMUFree");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EMUFree");
         }
      }

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

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RegMode */ 

enum Bits_RegMode : uint32
 {
  RegMode_NoReset  = 0x00000002,
  RegMode_PostMode = 0x00000004
 };
 
inline Bits_RegMode operator | (Bits_RegMode a,Bits_RegMode b)
 { return Bits_RegMode(uint32(a)|uint32(b)); }
 
struct Type_RegMode
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RegMode(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RegMode & setTo(Bar &bar) { bar.set_RegMode(*this); return *this; }
 

  template <class Bar>
  Type_RegMode & setTo(Bar &bar,uint32 ind) { bar.set_RegMode(*this,ind); return *this; }
 

  template <class T>
  Type_RegMode & set(T to) { to(*this); return *this; }
 

  Type_RegMode & setbit(Bits_RegMode bits) { value|=Type(bits); return *this; }
 
  Type_RegMode & setbitIf(bool cond,Bits_RegMode bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RegMode & clearbit(Bits_RegMode bits) { value&=~Type(bits); return *this; }
 
  Type_RegMode & clearbitIf(bool cond,Bits_RegMode bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RegMode bits) const { return value&bits; }
 
  bool testbit(Bits_RegMode bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RegMode_NoReset )
      {
       if( first )
         {
          Putobj(out,"NoReset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoReset");
         }
      }

    if( value&RegMode_PostMode )
      {
       if( first )
         {
          Putobj(out,"PostMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PostMode");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_Counter */ 

typedef uint32 Type_Counter;

/* type Type_Reload */ 

typedef uint32 Type_Reload;

/* struct Type_Control */ 

enum Bits_Control : uint32
 {
  Control_Start      = 0x00000001,
  Control_AutoReload = 0x00000002
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
  Type_Control & setTo(Bar &bar,uint32 ind) { bar.set_Control(*this,ind); return *this; }
 

  template <class T>
  Type_Control & set(T to) { to(*this); return *this; }
 

  Type_Control & setbit(Bits_Control bits) { value|=Type(bits); return *this; }
 
  Type_Control & setbitIf(bool cond,Bits_Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Control & clearbit(Bits_Control bits) { value&=~Type(bits); return *this; }
 
  Type_Control & clearbitIf(bool cond,Bits_Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Control bits) const { return value&bits; }
 
  bool testbit(Bits_Control bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Control_Start )
      {
       if( first )
         {
          Putobj(out,"Start");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Start");
         }
      }

    if( value&Control_AutoReload )
      {
       if( first )
         {
          Putobj(out,"AutoReload");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AutoReload");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RegPost */ 

enum Bits_RegPost : uint32
 {
  RegPost_PendingControl = 0x00000001,
  RegPost_PendingCounter = 0x00000002,
  RegPost_PendingReload  = 0x00000004
 };
 
inline Bits_RegPost operator | (Bits_RegPost a,Bits_RegPost b)
 { return Bits_RegPost(uint32(a)|uint32(b)); }
 
struct Type_RegPost
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RegPost(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RegPost & setTo(Bar &bar) { bar.set_RegPost(*this); return *this; }
 

  template <class Bar>
  Type_RegPost & setTo(Bar &bar,uint32 ind) { bar.set_RegPost(*this,ind); return *this; }
 

  template <class T>
  Type_RegPost & set(T to) { to(*this); return *this; }
 

  Type_RegPost & setbit(Bits_RegPost bits) { value|=Type(bits); return *this; }
 
  Type_RegPost & setbitIf(bool cond,Bits_RegPost bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RegPost & clearbit(Bits_RegPost bits) { value&=~Type(bits); return *this; }
 
  Type_RegPost & clearbitIf(bool cond,Bits_RegPost bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RegPost bits) const { return value&bits; }
 
  bool testbit(Bits_RegPost bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RegPost_PendingControl )
      {
       if( first )
         {
          Putobj(out,"PendingControl");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PendingControl");
         }
      }

    if( value&RegPost_PendingCounter )
      {
       if( first )
         {
          Putobj(out,"PendingCounter");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PendingCounter");
         }
      }

    if( value&RegPost_PendingReload )
      {
       if( first )
         {
          Putobj(out,"PendingReload");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PendingReload");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntStatus */ 

enum Bits_IntStatus : uint32
 {
  IntStatus_Match    = 0x00000001,
  IntStatus_Overflow = 0x00000002,
  IntStatus_Capture  = 0x00000004
 };
 
inline Bits_IntStatus operator | (Bits_IntStatus a,Bits_IntStatus b)
 { return Bits_IntStatus(uint32(a)|uint32(b)); }
 
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
  Type_IntStatus & setTo(Bar &bar,uint32 ind) { bar.set_IntStatus(*this,ind); return *this; }
 

  template <class T>
  Type_IntStatus & set(T to) { to(*this); return *this; }
 

  Type_IntStatus & setbit(Bits_IntStatus bits) { value|=Type(bits); return *this; }
 
  Type_IntStatus & setbitIf(bool cond,Bits_IntStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IntStatus & clearbit(Bits_IntStatus bits) { value&=~Type(bits); return *this; }
 
  Type_IntStatus & clearbitIf(bool cond,Bits_IntStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IntStatus bits) const { return value&bits; }
 
  bool testbit(Bits_IntStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IntStatus_Match )
      {
       if( first )
         {
          Putobj(out,"Match");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Match");
         }
      }

    if( value&IntStatus_Overflow )
      {
       if( first )
         {
          Putobj(out,"Overflow");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Overflow");
         }
      }

    if( value&IntStatus_Capture )
      {
       if( first )
         {
          Putobj(out,"Capture");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Capture");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct DMBar<RW> */ 

template <class RW>
struct DMBar
 {
  RW rw;

  template <class ... TT>
  DMBar(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- OCPConfig

  Type_OCPConfig get_OCPConfig() { return Type_OCPConfig(rw.template get<uint32>(0x10)); }
 
  void set_OCPConfig(Type_OCPConfig value) { rw.set(0x10,value.value); }
 
  Setter<Type_OCPConfig> to_OCPConfig() { return Setter<Type_OCPConfig>(rw,0x10); }
 
  static Type_OCPConfig null_OCPConfig() { return Type_OCPConfig(0); }
 
  static Type_OCPConfig ones_OCPConfig() { return Type_OCPConfig(Type_OCPConfig::Type(-1)); }
 
  //--- RegMode

  Type_RegMode get_RegMode() { return Type_RegMode(rw.template get<uint32>(0x54)); }
 
  void set_RegMode(Type_RegMode value) { rw.set(0x54,value.value); }
 
  Setter<Type_RegMode> to_RegMode() { return Setter<Type_RegMode>(rw,0x54); }
 
  static Type_RegMode null_RegMode() { return Type_RegMode(0); }
 
  static Type_RegMode ones_RegMode() { return Type_RegMode(Type_RegMode::Type(-1)); }
 
  //--- Counter

  Type_Counter get_Counter() { return Type_Counter(rw.template get<uint32>(0x3C)); }
 
  void set_Counter(Type_Counter value) { rw.set(0x3C,value); }
 
  void set_Counter_null() { rw.set(0x3C,Type_Counter(0)); }
 
  void set_Counter_ones() { rw.set(0x3C,Type_Counter(-1)); }
 
  //--- Reload

  Type_Reload get_Reload() { return Type_Reload(rw.template get<uint32>(0x40)); }
 
  void set_Reload(Type_Reload value) { rw.set(0x40,value); }
 
  void set_Reload_null() { rw.set(0x40,Type_Reload(0)); }
 
  void set_Reload_ones() { rw.set(0x40,Type_Reload(-1)); }
 
  //--- Control

  Type_Control get_Control() { return Type_Control(rw.template get<uint32>(0x38)); }
 
  void set_Control(Type_Control value) { rw.set(0x38,value.value); }
 
  Setter<Type_Control> to_Control() { return Setter<Type_Control>(rw,0x38); }
 
  static Type_Control null_Control() { return Type_Control(0); }
 
  static Type_Control ones_Control() { return Type_Control(Type_Control::Type(-1)); }
 
  //--- RegPost

  Type_RegPost get_RegPost() { return Type_RegPost(rw.template get<uint32>(0x48)); }
 
  void set_RegPost(Type_RegPost value) { rw.set(0x48,value.value); }
 
  Setter<Type_RegPost> to_RegPost() { return Setter<Type_RegPost>(rw,0x48); }
 
  static Type_RegPost null_RegPost() { return Type_RegPost(0); }
 
  static Type_RegPost ones_RegPost() { return Type_RegPost(Type_RegPost::Type(-1)); }
 
  //--- IntStatusRaw

  Type_IntStatus get_IntStatusRaw() { return Type_IntStatus(rw.template get<uint32>(0x24)); }
 
  void set_IntStatusRaw(Type_IntStatus value) { rw.set(0x24,value.value); }
 
  Setter<Type_IntStatus> to_IntStatusRaw() { return Setter<Type_IntStatus>(rw,0x24); }
 
  //--- IntStatus

  Type_IntStatus get_IntStatus() { return Type_IntStatus(rw.template get<uint32>(0x28)); }
 
  void set_IntStatus(Type_IntStatus value) { rw.set(0x28,value.value); }
 
  Setter<Type_IntStatus> to_IntStatus() { return Setter<Type_IntStatus>(rw,0x28); }
 
  static Type_IntStatus null_IntStatus() { return Type_IntStatus(0); }
 
  static Type_IntStatus ones_IntStatus() { return Type_IntStatus(Type_IntStatus::Type(-1)); }
 
  //--- IntEnableSet

  Type_IntStatus get_IntEnableSet() { return Type_IntStatus(rw.template get<uint32>(0x2C)); }
 
  void set_IntEnableSet(Type_IntStatus value) { rw.set(0x2C,value.value); }
 
  Setter<Type_IntStatus> to_IntEnableSet() { return Setter<Type_IntStatus>(rw,0x2C); }
 
  //--- IntEnableClear

  Type_IntStatus get_IntEnableClear() { return Type_IntStatus(rw.template get<uint32>(0x30)); }
 
  void set_IntEnableClear(Type_IntStatus value) { rw.set(0x30,value.value); }
 
  Setter<Type_IntStatus> to_IntEnableClear() { return Setter<Type_IntStatus>(rw,0x30); }
 
 };
 
