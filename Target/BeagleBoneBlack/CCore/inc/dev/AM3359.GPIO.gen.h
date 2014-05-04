/* AM3359.GPIO.gen.h */ 

/* struct Type_SysConfig */ 

enum Bits_SysConfig : uint32
 {
  SysConfig_AutoIdle  = 0x00000001,
  SysConfig_SoftReset = 0x00000002,
  SysConfig_EnWakeup  = 0x00000004
 };
 
inline Bits_SysConfig operator | (Bits_SysConfig a,Bits_SysConfig b)
 { return Bits_SysConfig(uint32(a)|uint32(b)); }
 
enum Field_SysConfig_IdleMode : uint32
 {
  SysConfig_IdleMode_ForceIdle       = 0x00,
  SysConfig_IdleMode_NoIdle          = 0x01,
  SysConfig_IdleMode_SmartIdle       = 0x02,
  SysConfig_IdleMode_SmartIdleWakeup = 0x03
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
       case 0x03 : Putobj(out,"SmartIdleWakeup"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_SysConfig_IdleMode GetTextDesc(Field_SysConfig_IdleMode field)
 {
  return PrintField_SysConfig_IdleMode(field);
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
 

  Type_SysConfig & setbit(Bits_SysConfig bits) { value|=Type(bits); return *this; }
 
  Type_SysConfig & setbitIf(bool cond,Bits_SysConfig bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SysConfig & clearbit(Bits_SysConfig bits) { value&=~Type(bits); return *this; }
 
  Type_SysConfig & clearbitIf(bool cond,Bits_SysConfig bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SysConfig bits) const { return value&bits; }
 
  bool testbit(Bits_SysConfig bits) const { return (value&bits)==Type(bits); }
 

  Field_SysConfig_IdleMode get_IdleMode() const
   {
    return Field_SysConfig_IdleMode((value>>3)&0x3);
   }
 
  Type_SysConfig & set_IdleMode(Field_SysConfig_IdleMode field)
   {
    value=((Type(field)&0x3)<<3)|(value&0xFFFFFFE7);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SysConfig_AutoIdle )
      {
       if( first )
         {
          Putobj(out,"AutoIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AutoIdle");
         }
      }

    if( value&SysConfig_SoftReset )
      {
       if( first )
         {
          Putobj(out,"SoftReset");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SoftReset");
         }
      }

    if( value&SysConfig_EnWakeup )
      {
       if( first )
         {
          Putobj(out,"EnWakeup");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EnWakeup");
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
 
/* struct Type_SysStatus */ 

enum Bits_SysStatus : uint32
 {
  SysStatus_ResetDone = 0x00000001
 };
 
inline Bits_SysStatus operator | (Bits_SysStatus a,Bits_SysStatus b)
 { return Bits_SysStatus(uint32(a)|uint32(b)); }
 
struct Type_SysStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SysStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SysStatus & setTo(Bar &bar) { bar.set_SysStatus(*this); return *this; }
 

  template <class Bar>
  Type_SysStatus & setTo(Bar &bar,uint32 ind) { bar.set_SysStatus(ind,*this); return *this; }
 

  template <class T>
  Type_SysStatus & set(T to) { to(*this); return *this; }
 

  Type_SysStatus & setbit(Bits_SysStatus bits) { value|=Type(bits); return *this; }
 
  Type_SysStatus & setbitIf(bool cond,Bits_SysStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SysStatus & clearbit(Bits_SysStatus bits) { value&=~Type(bits); return *this; }
 
  Type_SysStatus & clearbitIf(bool cond,Bits_SysStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SysStatus bits) const { return value&bits; }
 
  bool testbit(Bits_SysStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SysStatus_ResetDone )
      {
       if( first )
         {
          Putobj(out,"ResetDone");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ResetDone");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Control */ 

enum Bits_Control : uint32
 {
  Control_Disable = 0x00000001
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
 

  Type get_GatingRatio() const
   {
    return (value>>1)&0x3;
   }
 
  Type_Control & set_GatingRatio(Type field)
   {
    value=((field&0x3)<<1)|(value&0xFFFFFFF9);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Control_Disable )
      {
       if( first )
         {
          Putobj(out,"Disable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Disable");
         }
      }

    if( first )
      {
       Printf(out,"GatingRatio(#;)",get_GatingRatio());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"GatingRatio(#;)",get_GatingRatio());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DataIn */ 

typedef uint32 Type_DataIn;

/* type Type_Level0Detect */ 

typedef uint32 Type_Level0Detect;

/* type Type_Level1Detect */ 

typedef uint32 Type_Level1Detect;

/* type Type_RaisingDetect */ 

typedef uint32 Type_RaisingDetect;

/* type Type_FallingDetect */ 

typedef uint32 Type_FallingDetect;

/* type Type_OutEnable */ 

typedef uint32 Type_OutEnable;

/* type Type_Out */ 

typedef uint32 Type_Out;

/* type Type_ClearOut */ 

typedef uint32 Type_ClearOut;

/* type Type_SetOut */ 

typedef uint32 Type_SetOut;

/* type Type_IRQ0StatusRaw */ 

typedef uint32 Type_IRQ0StatusRaw;

/* type Type_IRQ0Status */ 

typedef uint32 Type_IRQ0Status;

/* type Type_IRQ0EnableSet */ 

typedef uint32 Type_IRQ0EnableSet;

/* type Type_IRQ0EnableClear */ 

typedef uint32 Type_IRQ0EnableClear;

/* type Type_IRQ1StatusRaw */ 

typedef uint32 Type_IRQ1StatusRaw;

/* type Type_IRQ1Status */ 

typedef uint32 Type_IRQ1Status;

/* type Type_IRQ1EnableSet */ 

typedef uint32 Type_IRQ1EnableSet;

/* type Type_IRQ1EnableClear */ 

typedef uint32 Type_IRQ1EnableClear;

/* struct GPIOBar<RW> */ 

template <class RW>
struct GPIOBar
 {
  RW rw;

  template <class ... TT>
  GPIOBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SysConfig

  Type_SysConfig get_SysConfig() { return Type_SysConfig(rw.template get<uint32>(0x10)); }
 
  void set_SysConfig(Type_SysConfig value) { rw.set(0x10,value.value); }
 
  Setter<Type_SysConfig> to_SysConfig() { return Setter<Type_SysConfig>(rw,0x10); }
 
  static Type_SysConfig null_SysConfig() { return Type_SysConfig(0); }
 
  static Type_SysConfig ones_SysConfig() { return Type_SysConfig(Type_SysConfig::Type(-1)); }
 
  //--- SysStatus

  Type_SysStatus get_SysStatus() { return Type_SysStatus(rw.template get<uint32>(0x114)); }
 
  void set_SysStatus(Type_SysStatus value) { rw.set(0x114,value.value); }
 
  Setter<Type_SysStatus> to_SysStatus() { return Setter<Type_SysStatus>(rw,0x114); }
 
  static Type_SysStatus null_SysStatus() { return Type_SysStatus(0); }
 
  static Type_SysStatus ones_SysStatus() { return Type_SysStatus(Type_SysStatus::Type(-1)); }
 
  //--- Control

  Type_Control get_Control() { return Type_Control(rw.template get<uint32>(0x130)); }
 
  void set_Control(Type_Control value) { rw.set(0x130,value.value); }
 
  Setter<Type_Control> to_Control() { return Setter<Type_Control>(rw,0x130); }
 
  static Type_Control null_Control() { return Type_Control(0); }
 
  static Type_Control ones_Control() { return Type_Control(Type_Control::Type(-1)); }
 
  //--- DataIn

  Type_DataIn get_DataIn() { return Type_DataIn(rw.template get<uint32>(0x138)); }
 
  void set_DataIn(Type_DataIn value) { rw.set(0x138,value); }
 
  void set_DataIn_null() { rw.set(0x138,Type_DataIn(0)); }
 
  void set_DataIn_ones() { rw.set(0x138,Type_DataIn(-1)); }
 
  //--- Level0Detect

  Type_Level0Detect get_Level0Detect() { return Type_Level0Detect(rw.template get<uint32>(0x140)); }
 
  void set_Level0Detect(Type_Level0Detect value) { rw.set(0x140,value); }
 
  void set_Level0Detect_null() { rw.set(0x140,Type_Level0Detect(0)); }
 
  void set_Level0Detect_ones() { rw.set(0x140,Type_Level0Detect(-1)); }
 
  //--- Level1Detect

  Type_Level1Detect get_Level1Detect() { return Type_Level1Detect(rw.template get<uint32>(0x144)); }
 
  void set_Level1Detect(Type_Level1Detect value) { rw.set(0x144,value); }
 
  void set_Level1Detect_null() { rw.set(0x144,Type_Level1Detect(0)); }
 
  void set_Level1Detect_ones() { rw.set(0x144,Type_Level1Detect(-1)); }
 
  //--- RaisingDetect

  Type_RaisingDetect get_RaisingDetect() { return Type_RaisingDetect(rw.template get<uint32>(0x148)); }
 
  void set_RaisingDetect(Type_RaisingDetect value) { rw.set(0x148,value); }
 
  void set_RaisingDetect_null() { rw.set(0x148,Type_RaisingDetect(0)); }
 
  void set_RaisingDetect_ones() { rw.set(0x148,Type_RaisingDetect(-1)); }
 
  //--- FallingDetect

  Type_FallingDetect get_FallingDetect() { return Type_FallingDetect(rw.template get<uint32>(0x14C)); }
 
  void set_FallingDetect(Type_FallingDetect value) { rw.set(0x14C,value); }
 
  void set_FallingDetect_null() { rw.set(0x14C,Type_FallingDetect(0)); }
 
  void set_FallingDetect_ones() { rw.set(0x14C,Type_FallingDetect(-1)); }
 
  //--- OutEnable

  Type_OutEnable get_OutEnable() { return Type_OutEnable(rw.template get<uint32>(0x134)); }
 
  void set_OutEnable(Type_OutEnable value) { rw.set(0x134,value); }
 
  void set_OutEnable_null() { rw.set(0x134,Type_OutEnable(0)); }
 
  void set_OutEnable_ones() { rw.set(0x134,Type_OutEnable(-1)); }
 
  //--- Out

  Type_Out get_Out() { return Type_Out(rw.template get<uint32>(0x13C)); }
 
  void set_Out(Type_Out value) { rw.set(0x13C,value); }
 
  void set_Out_null() { rw.set(0x13C,Type_Out(0)); }
 
  void set_Out_ones() { rw.set(0x13C,Type_Out(-1)); }
 
  //--- ClearOut

  Type_ClearOut get_ClearOut() { return Type_ClearOut(rw.template get<uint32>(0x190)); }
 
  void set_ClearOut(Type_ClearOut value) { rw.set(0x190,value); }
 
  void set_ClearOut_null() { rw.set(0x190,Type_ClearOut(0)); }
 
  void set_ClearOut_ones() { rw.set(0x190,Type_ClearOut(-1)); }
 
  //--- SetOut

  Type_SetOut get_SetOut() { return Type_SetOut(rw.template get<uint32>(0x194)); }
 
  void set_SetOut(Type_SetOut value) { rw.set(0x194,value); }
 
  void set_SetOut_null() { rw.set(0x194,Type_SetOut(0)); }
 
  void set_SetOut_ones() { rw.set(0x194,Type_SetOut(-1)); }
 
  //--- IRQ0StatusRaw

  Type_IRQ0StatusRaw get_IRQ0StatusRaw() { return Type_IRQ0StatusRaw(rw.template get<uint32>(0x24)); }
 
  void set_IRQ0StatusRaw(Type_IRQ0StatusRaw value) { rw.set(0x24,value); }
 
  void set_IRQ0StatusRaw_null() { rw.set(0x24,Type_IRQ0StatusRaw(0)); }
 
  void set_IRQ0StatusRaw_ones() { rw.set(0x24,Type_IRQ0StatusRaw(-1)); }
 
  //--- IRQ0Status

  Type_IRQ0Status get_IRQ0Status() { return Type_IRQ0Status(rw.template get<uint32>(0x2C)); }
 
  void set_IRQ0Status(Type_IRQ0Status value) { rw.set(0x2C,value); }
 
  void set_IRQ0Status_null() { rw.set(0x2C,Type_IRQ0Status(0)); }
 
  void set_IRQ0Status_ones() { rw.set(0x2C,Type_IRQ0Status(-1)); }
 
  //--- IRQ0EnableSet

  Type_IRQ0EnableSet get_IRQ0EnableSet() { return Type_IRQ0EnableSet(rw.template get<uint32>(0x34)); }
 
  void set_IRQ0EnableSet(Type_IRQ0EnableSet value) { rw.set(0x34,value); }
 
  void set_IRQ0EnableSet_null() { rw.set(0x34,Type_IRQ0EnableSet(0)); }
 
  void set_IRQ0EnableSet_ones() { rw.set(0x34,Type_IRQ0EnableSet(-1)); }
 
  //--- IRQ0EnableClear

  Type_IRQ0EnableClear get_IRQ0EnableClear() { return Type_IRQ0EnableClear(rw.template get<uint32>(0x3C)); }
 
  void set_IRQ0EnableClear(Type_IRQ0EnableClear value) { rw.set(0x3C,value); }
 
  void set_IRQ0EnableClear_null() { rw.set(0x3C,Type_IRQ0EnableClear(0)); }
 
  void set_IRQ0EnableClear_ones() { rw.set(0x3C,Type_IRQ0EnableClear(-1)); }
 
  //--- IRQ1StatusRaw

  Type_IRQ1StatusRaw get_IRQ1StatusRaw() { return Type_IRQ1StatusRaw(rw.template get<uint32>(0x28)); }
 
  void set_IRQ1StatusRaw(Type_IRQ1StatusRaw value) { rw.set(0x28,value); }
 
  void set_IRQ1StatusRaw_null() { rw.set(0x28,Type_IRQ1StatusRaw(0)); }
 
  void set_IRQ1StatusRaw_ones() { rw.set(0x28,Type_IRQ1StatusRaw(-1)); }
 
  //--- IRQ1Status

  Type_IRQ1Status get_IRQ1Status() { return Type_IRQ1Status(rw.template get<uint32>(0x30)); }
 
  void set_IRQ1Status(Type_IRQ1Status value) { rw.set(0x30,value); }
 
  void set_IRQ1Status_null() { rw.set(0x30,Type_IRQ1Status(0)); }
 
  void set_IRQ1Status_ones() { rw.set(0x30,Type_IRQ1Status(-1)); }
 
  //--- IRQ1EnableSet

  Type_IRQ1EnableSet get_IRQ1EnableSet() { return Type_IRQ1EnableSet(rw.template get<uint32>(0x38)); }
 
  void set_IRQ1EnableSet(Type_IRQ1EnableSet value) { rw.set(0x38,value); }
 
  void set_IRQ1EnableSet_null() { rw.set(0x38,Type_IRQ1EnableSet(0)); }
 
  void set_IRQ1EnableSet_ones() { rw.set(0x38,Type_IRQ1EnableSet(-1)); }
 
  //--- IRQ1EnableClear

  Type_IRQ1EnableClear get_IRQ1EnableClear() { return Type_IRQ1EnableClear(rw.template get<uint32>(0x40)); }
 
  void set_IRQ1EnableClear(Type_IRQ1EnableClear value) { rw.set(0x40,value); }
 
  void set_IRQ1EnableClear_null() { rw.set(0x40,Type_IRQ1EnableClear(0)); }
 
  void set_IRQ1EnableClear_ones() { rw.set(0x40,Type_IRQ1EnableClear(-1)); }
 
 };
 
