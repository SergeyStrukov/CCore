/* AM3359.INTC.gen.h */ 

/* struct Type_SysConfig */ 

enum Bits_SysConfig : uint32
 {
  SysConfig_Idle  = 0x00000001,
  SysConfig_Reset = 0x00000002
 };
 
inline Bits_SysConfig operator | (Bits_SysConfig a,Bits_SysConfig b)
 { return Bits_SysConfig(uint32(a)|uint32(b)); }
 
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
  Type_SysConfig & setTo(Bar &bar,uint32 ind) { bar.set_SysConfig(*this,ind); return *this; }
 

  template <class T>
  Type_SysConfig & set(T to) { to(*this); return *this; }
 

  Type_SysConfig & setbit(Bits_SysConfig bits) { value|=Type(bits); return *this; }
 
  Type_SysConfig & setbitIf(bool cond,Bits_SysConfig bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SysConfig & clearbit(Bits_SysConfig bits) { value&=~Type(bits); return *this; }
 
  Type_SysConfig & clearbitIf(bool cond,Bits_SysConfig bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SysConfig bits) const { return value&bits; }
 
  bool testbit(Bits_SysConfig bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SysConfig_Idle )
      {
       if( first )
         {
          Putobj(out,"Idle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Idle");
         }
      }

    if( value&SysConfig_Reset )
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
  Type_SysStatus & setTo(Bar &bar,uint32 ind) { bar.set_SysStatus(*this,ind); return *this; }
 

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
 
/* struct Type_Protection */ 

enum Bits_Protection : uint32
 {
  Protection_Enable = 0x00000001
 };
 
inline Bits_Protection operator | (Bits_Protection a,Bits_Protection b)
 { return Bits_Protection(uint32(a)|uint32(b)); }
 
struct Type_Protection
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Protection(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Protection & setTo(Bar &bar) { bar.set_Protection(*this); return *this; }
 

  template <class Bar>
  Type_Protection & setTo(Bar &bar,uint32 ind) { bar.set_Protection(*this,ind); return *this; }
 

  template <class T>
  Type_Protection & set(T to) { to(*this); return *this; }
 

  Type_Protection & setbit(Bits_Protection bits) { value|=Type(bits); return *this; }
 
  Type_Protection & setbitIf(bool cond,Bits_Protection bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Protection & clearbit(Bits_Protection bits) { value&=~Type(bits); return *this; }
 
  Type_Protection & clearbitIf(bool cond,Bits_Protection bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Protection bits) const { return value&bits; }
 
  bool testbit(Bits_Protection bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Protection_Enable )
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
 
/* struct Type_Idle */ 

enum Bits_Idle : uint32
 {
  Idle_Func  = 0x00000001,
  Idle_Turbo = 0x00000002
 };
 
inline Bits_Idle operator | (Bits_Idle a,Bits_Idle b)
 { return Bits_Idle(uint32(a)|uint32(b)); }
 
struct Type_Idle
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Idle(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Idle & setTo(Bar &bar) { bar.set_Idle(*this); return *this; }
 

  template <class Bar>
  Type_Idle & setTo(Bar &bar,uint32 ind) { bar.set_Idle(*this,ind); return *this; }
 

  template <class T>
  Type_Idle & set(T to) { to(*this); return *this; }
 

  Type_Idle & setbit(Bits_Idle bits) { value|=Type(bits); return *this; }
 
  Type_Idle & setbitIf(bool cond,Bits_Idle bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Idle & clearbit(Bits_Idle bits) { value&=~Type(bits); return *this; }
 
  Type_Idle & clearbitIf(bool cond,Bits_Idle bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Idle bits) const { return value&bits; }
 
  bool testbit(Bits_Idle bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Idle_Func )
      {
       if( first )
         {
          Putobj(out,"Func");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Func");
         }
      }

    if( value&Idle_Turbo )
      {
       if( first )
         {
          Putobj(out,"Turbo");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Turbo");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PriorityMask */ 

struct Type_PriorityMask
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PriorityMask(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PriorityMask & setTo(Bar &bar) { bar.set_PriorityMask(*this); return *this; }
 

  template <class Bar>
  Type_PriorityMask & setTo(Bar &bar,uint32 ind) { bar.set_PriorityMask(*this,ind); return *this; }
 

  template <class T>
  Type_PriorityMask & set(T to) { to(*this); return *this; }
 

  Type get_Threshold() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_PriorityMask & set_Threshold(Type field)
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
       Printf(out,"Threshold(#;)",get_Threshold());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Threshold(#;)",get_Threshold());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TypePriorityCfg */ 

enum Bits_TypePriorityCfg : uint32
 {
  TypePriorityCfg_AsFIQ = 0x00000001
 };
 
inline Bits_TypePriorityCfg operator | (Bits_TypePriorityCfg a,Bits_TypePriorityCfg b)
 { return Bits_TypePriorityCfg(uint32(a)|uint32(b)); }
 
struct Type_TypePriorityCfg
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TypePriorityCfg(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TypePriorityCfg & setTo(Bar &bar) { bar.set_TypePriorityCfg(*this); return *this; }
 

  template <class Bar>
  Type_TypePriorityCfg & setTo(Bar &bar,uint32 ind) { bar.set_TypePriorityCfg(*this,ind); return *this; }
 

  template <class T>
  Type_TypePriorityCfg & set(T to) { to(*this); return *this; }
 

  Type_TypePriorityCfg & setbit(Bits_TypePriorityCfg bits) { value|=Type(bits); return *this; }
 
  Type_TypePriorityCfg & setbitIf(bool cond,Bits_TypePriorityCfg bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TypePriorityCfg & clearbit(Bits_TypePriorityCfg bits) { value&=~Type(bits); return *this; }
 
  Type_TypePriorityCfg & clearbitIf(bool cond,Bits_TypePriorityCfg bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TypePriorityCfg bits) const { return value&bits; }
 
  bool testbit(Bits_TypePriorityCfg bits) const { return (value&bits)==Type(bits); }
 

  Type get_Priority() const
   {
    return (value>>2)&0x3F;
   }
 
  Type_TypePriorityCfg & set_Priority(Type field)
   {
    value=((field&0x3F)<<2)|(value&0xFFFFFF03);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TypePriorityCfg_AsFIQ )
      {
       if( first )
         {
          Putobj(out,"AsFIQ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AsFIQ");
         }
      }

    if( first )
      {
       Printf(out,"Priority(#;)",get_Priority());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Priority(#;)",get_Priority());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ActiveIRQ */ 

struct Type_ActiveIRQ
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ActiveIRQ(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ActiveIRQ & setTo(Bar &bar) { bar.set_ActiveIRQ(*this); return *this; }
 

  template <class Bar>
  Type_ActiveIRQ & setTo(Bar &bar,uint32 ind) { bar.set_ActiveIRQ(*this,ind); return *this; }
 

  template <class T>
  Type_ActiveIRQ & set(T to) { to(*this); return *this; }
 

  Type get_Number() const
   {
    return (value>>0)&0x7F;
   }
 
  Type_ActiveIRQ & set_Number(Type field)
   {
    value=((field&0x7F)<<0)|(value&0xFFFFFF80);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Number(#;)",get_Number());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Number(#;)",get_Number());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_NextActive */ 

enum Bits_NextActive : uint32
 {
  NextActive_IRQ = 0x00000001,
  NextActive_FIQ = 0x00000002
 };
 
inline Bits_NextActive operator | (Bits_NextActive a,Bits_NextActive b)
 { return Bits_NextActive(uint32(a)|uint32(b)); }
 
struct Type_NextActive
 {
  typedef uint32 Type;

  Type value;


  explicit Type_NextActive(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_NextActive & setTo(Bar &bar) { bar.set_NextActive(*this); return *this; }
 

  template <class Bar>
  Type_NextActive & setTo(Bar &bar,uint32 ind) { bar.set_NextActive(*this,ind); return *this; }
 

  template <class T>
  Type_NextActive & set(T to) { to(*this); return *this; }
 

  Type_NextActive & setbit(Bits_NextActive bits) { value|=Type(bits); return *this; }
 
  Type_NextActive & setbitIf(bool cond,Bits_NextActive bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_NextActive & clearbit(Bits_NextActive bits) { value&=~Type(bits); return *this; }
 
  Type_NextActive & clearbitIf(bool cond,Bits_NextActive bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_NextActive bits) const { return value&bits; }
 
  bool testbit(Bits_NextActive bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&NextActive_IRQ )
      {
       if( first )
         {
          Putobj(out,"IRQ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IRQ");
         }
      }

    if( value&NextActive_FIQ )
      {
       if( first )
         {
          Putobj(out,"FIQ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FIQ");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_Mask */ 

typedef uint32 Type_Mask;

/* struct INTCBar<RW> */ 

template <class RW>
struct INTCBar
 {
  RW rw;

  template <class ... TT>
  INTCBar(TT && ... tt) : rw(tt...) {}
 
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

  Type_SysStatus get_SysStatus() { return Type_SysStatus(rw.template get<uint32>(0x14)); }
 
  void set_SysStatus(Type_SysStatus value) { rw.set(0x14,value.value); }
 
  Setter<Type_SysStatus> to_SysStatus() { return Setter<Type_SysStatus>(rw,0x14); }
 
  static Type_SysStatus null_SysStatus() { return Type_SysStatus(0); }
 
  static Type_SysStatus ones_SysStatus() { return Type_SysStatus(Type_SysStatus::Type(-1)); }
 
  //--- Protection

  Type_Protection get_Protection() { return Type_Protection(rw.template get<uint32>(0x4C)); }
 
  void set_Protection(Type_Protection value) { rw.set(0x4C,value.value); }
 
  Setter<Type_Protection> to_Protection() { return Setter<Type_Protection>(rw,0x4C); }
 
  static Type_Protection null_Protection() { return Type_Protection(0); }
 
  static Type_Protection ones_Protection() { return Type_Protection(Type_Protection::Type(-1)); }
 
  //--- Idle

  Type_Idle get_Idle() { return Type_Idle(rw.template get<uint32>(0x50)); }
 
  void set_Idle(Type_Idle value) { rw.set(0x50,value.value); }
 
  Setter<Type_Idle> to_Idle() { return Setter<Type_Idle>(rw,0x50); }
 
  static Type_Idle null_Idle() { return Type_Idle(0); }
 
  static Type_Idle ones_Idle() { return Type_Idle(Type_Idle::Type(-1)); }
 
  //--- PriorityMask

  Type_PriorityMask get_PriorityMask() { return Type_PriorityMask(rw.template get<uint32>(0x68)); }
 
  void set_PriorityMask(Type_PriorityMask value) { rw.set(0x68,value.value); }
 
  Setter<Type_PriorityMask> to_PriorityMask() { return Setter<Type_PriorityMask>(rw,0x68); }
 
  static Type_PriorityMask null_PriorityMask() { return Type_PriorityMask(0); }
 
  static Type_PriorityMask ones_PriorityMask() { return Type_PriorityMask(Type_PriorityMask::Type(-1)); }
 
  //--- TypePriorityCfg

  Type_TypePriorityCfg get_TypePriorityCfg(uint32 ind) { return Type_TypePriorityCfg(rw.template get<uint32>(0x100 +ind*4)); }
 
  void set_TypePriorityCfg(uint32 ind,Type_TypePriorityCfg value) { rw.set(0x100 +ind*4,value.value); }
 
  Setter<Type_TypePriorityCfg> to_TypePriorityCfg(uint32 ind) { return Setter<Type_TypePriorityCfg>(rw,0x100 +ind*4); }
 
  static Type_TypePriorityCfg null_TypePriorityCfg() { return Type_TypePriorityCfg(0); }
 
  static Type_TypePriorityCfg ones_TypePriorityCfg() { return Type_TypePriorityCfg(Type_TypePriorityCfg::Type(-1)); }
 
  //--- ActiveIRQ

  Type_ActiveIRQ get_ActiveIRQ() { return Type_ActiveIRQ(rw.template get<uint32>(0x40)); }
 
  void set_ActiveIRQ(Type_ActiveIRQ value) { rw.set(0x40,value.value); }
 
  Setter<Type_ActiveIRQ> to_ActiveIRQ() { return Setter<Type_ActiveIRQ>(rw,0x40); }
 
  static Type_ActiveIRQ null_ActiveIRQ() { return Type_ActiveIRQ(0); }
 
  static Type_ActiveIRQ ones_ActiveIRQ() { return Type_ActiveIRQ(Type_ActiveIRQ::Type(-1)); }
 
  //--- NextActive

  Type_NextActive get_NextActive() { return Type_NextActive(rw.template get<uint32>(0x48)); }
 
  void set_NextActive(Type_NextActive value) { rw.set(0x48,value.value); }
 
  Setter<Type_NextActive> to_NextActive() { return Setter<Type_NextActive>(rw,0x48); }
 
  static Type_NextActive null_NextActive() { return Type_NextActive(0); }
 
  static Type_NextActive ones_NextActive() { return Type_NextActive(Type_NextActive::Type(-1)); }
 
  //--- SetMask0

  Type_Mask get_SetMask0() { return Type_Mask(rw.template get<uint32>(0x8C)); }
 
  void set_SetMask0(Type_Mask value) { rw.set(0x8C,value); }
 
  void set_SetMask0_null() { rw.set(0x8C,Type_Mask(0)); }
 
  void set_SetMask0_ones() { rw.set(0x8C,Type_Mask(-1)); }
 
  //--- SetMask1

  Type_Mask get_SetMask1() { return Type_Mask(rw.template get<uint32>(0xAC)); }
 
  void set_SetMask1(Type_Mask value) { rw.set(0xAC,value); }
 
  void set_SetMask1_null() { rw.set(0xAC,Type_Mask(0)); }
 
  void set_SetMask1_ones() { rw.set(0xAC,Type_Mask(-1)); }
 
  //--- SetMask2

  Type_Mask get_SetMask2() { return Type_Mask(rw.template get<uint32>(0xCC)); }
 
  void set_SetMask2(Type_Mask value) { rw.set(0xCC,value); }
 
  void set_SetMask2_null() { rw.set(0xCC,Type_Mask(0)); }
 
  void set_SetMask2_ones() { rw.set(0xCC,Type_Mask(-1)); }
 
  //--- SetMask3

  Type_Mask get_SetMask3() { return Type_Mask(rw.template get<uint32>(0xEC)); }
 
  void set_SetMask3(Type_Mask value) { rw.set(0xEC,value); }
 
  void set_SetMask3_null() { rw.set(0xEC,Type_Mask(0)); }
 
  void set_SetMask3_ones() { rw.set(0xEC,Type_Mask(-1)); }
 
  //--- ClearMask0

  Type_Mask get_ClearMask0() { return Type_Mask(rw.template get<uint32>(0x88)); }
 
  void set_ClearMask0(Type_Mask value) { rw.set(0x88,value); }
 
  void set_ClearMask0_null() { rw.set(0x88,Type_Mask(0)); }
 
  void set_ClearMask0_ones() { rw.set(0x88,Type_Mask(-1)); }
 
  //--- ClearMask1

  Type_Mask get_ClearMask1() { return Type_Mask(rw.template get<uint32>(0xA8)); }
 
  void set_ClearMask1(Type_Mask value) { rw.set(0xA8,value); }
 
  void set_ClearMask1_null() { rw.set(0xA8,Type_Mask(0)); }
 
  void set_ClearMask1_ones() { rw.set(0xA8,Type_Mask(-1)); }
 
  //--- ClearMask2

  Type_Mask get_ClearMask2() { return Type_Mask(rw.template get<uint32>(0xC8)); }
 
  void set_ClearMask2(Type_Mask value) { rw.set(0xC8,value); }
 
  void set_ClearMask2_null() { rw.set(0xC8,Type_Mask(0)); }
 
  void set_ClearMask2_ones() { rw.set(0xC8,Type_Mask(-1)); }
 
  //--- ClearMask3

  Type_Mask get_ClearMask3() { return Type_Mask(rw.template get<uint32>(0xE8)); }
 
  void set_ClearMask3(Type_Mask value) { rw.set(0xE8,value); }
 
  void set_ClearMask3_null() { rw.set(0xE8,Type_Mask(0)); }
 
  void set_ClearMask3_ones() { rw.set(0xE8,Type_Mask(-1)); }
 
 };
 
