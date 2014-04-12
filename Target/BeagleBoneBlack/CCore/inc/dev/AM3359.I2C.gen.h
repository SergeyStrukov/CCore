/* AM3359.I2C.gen.h */ 

/* struct Type_SysConfig */ 

enum Bits_SysConfig : uint32
 {
  SysConfig_SoftReset = 0x00000002
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
  Type_SysConfig & setTo(Bar &bar,uint32 ind) { bar.set_SysConfig(ind,*this); return *this; }
 

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

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Config */ 

enum Bits_Config : uint32
 {
  Config_Start  = 0x00000001,
  Config_Stop   = 0x00000002,
  Config_A10    = 0x00000100,
  Config_TXMode = 0x00000200,
  Config_Master = 0x00000400,
  Config_Enable = 0x00008000
 };
 
inline Bits_Config operator | (Bits_Config a,Bits_Config b)
 { return Bits_Config(uint32(a)|uint32(b)); }
 
struct Type_Config
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Config(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Config & setTo(Bar &bar) { bar.set_Config(*this); return *this; }
 

  template <class Bar>
  Type_Config & setTo(Bar &bar,uint32 ind) { bar.set_Config(ind,*this); return *this; }
 

  template <class T>
  Type_Config & set(T to) { to(*this); return *this; }
 

  Type_Config & setbit(Bits_Config bits) { value|=Type(bits); return *this; }
 
  Type_Config & setbitIf(bool cond,Bits_Config bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Config & clearbit(Bits_Config bits) { value&=~Type(bits); return *this; }
 
  Type_Config & clearbitIf(bool cond,Bits_Config bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Config bits) const { return value&bits; }
 
  bool testbit(Bits_Config bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Config_Start )
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

    if( value&Config_Stop )
      {
       if( first )
         {
          Putobj(out,"Stop");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Stop");
         }
      }

    if( value&Config_A10 )
      {
       if( first )
         {
          Putobj(out,"A10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"A10");
         }
      }

    if( value&Config_TXMode )
      {
       if( first )
         {
          Putobj(out,"TXMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXMode");
         }
      }

    if( value&Config_Master )
      {
       if( first )
         {
          Putobj(out,"Master");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Master");
         }
      }

    if( value&Config_Enable )
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
 
/* struct Type_Prescale */ 

struct Type_Prescale
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Prescale(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Prescale & setTo(Bar &bar) { bar.set_Prescale(*this); return *this; }
 

  template <class Bar>
  Type_Prescale & setTo(Bar &bar,uint32 ind) { bar.set_Prescale(ind,*this); return *this; }
 

  template <class T>
  Type_Prescale & set(T to) { to(*this); return *this; }
 

  Type get_Div() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Prescale & set_Div(Type field)
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
 
/* struct Type_SCLLoTime */ 

struct Type_SCLLoTime
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SCLLoTime(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SCLLoTime & setTo(Bar &bar) { bar.set_SCLLoTime(*this); return *this; }
 

  template <class Bar>
  Type_SCLLoTime & setTo(Bar &bar,uint32 ind) { bar.set_SCLLoTime(ind,*this); return *this; }
 

  template <class T>
  Type_SCLLoTime & set(T to) { to(*this); return *this; }
 

  Type get_Time() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_SCLLoTime & set_Time(Type field)
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
       Printf(out,"Time(#;)",get_Time());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Time(#;)",get_Time());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SCLHiTime */ 

struct Type_SCLHiTime
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SCLHiTime(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SCLHiTime & setTo(Bar &bar) { bar.set_SCLHiTime(*this); return *this; }
 

  template <class Bar>
  Type_SCLHiTime & setTo(Bar &bar,uint32 ind) { bar.set_SCLHiTime(ind,*this); return *this; }
 

  template <class T>
  Type_SCLHiTime & set(T to) { to(*this); return *this; }
 

  Type get_Time() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_SCLHiTime & set_Time(Type field)
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
       Printf(out,"Time(#;)",get_Time());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Time(#;)",get_Time());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_BufStatus */ 

struct Type_BufStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_BufStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_BufStatus & setTo(Bar &bar) { bar.set_BufStatus(*this); return *this; }
 

  template <class Bar>
  Type_BufStatus & setTo(Bar &bar,uint32 ind) { bar.set_BufStatus(ind,*this); return *this; }
 

  template <class T>
  Type_BufStatus & set(T to) { to(*this); return *this; }
 

  Type get_TXStat() const
   {
    return (value>>0)&0x3F;
   }
 
  Type_BufStatus & set_TXStat(Type field)
   {
    value=((field&0x3F)<<0)|(value&0xFFFFFFC0);

    return *this;
   }
 

  Type get_RXStat() const
   {
    return (value>>8)&0x3F;
   }
 
  Type_BufStatus & set_RXStat(Type field)
   {
    value=((field&0x3F)<<8)|(value&0xFFFFC0FF);

    return *this;
   }
 

  Type get_FIFODepth() const
   {
    return (value>>14)&0x3;
   }
 
  Type_BufStatus & set_FIFODepth(Type field)
   {
    value=((field&0x3)<<14)|(value&0xFFFF3FFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"TXStat(#;)",get_TXStat());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TXStat(#;)",get_TXStat());
      }

    if( first )
      {
       Printf(out,"RXStat(#;)",get_RXStat());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RXStat(#;)",get_RXStat());
      }

    if( first )
      {
       Printf(out,"FIFODepth(#;)",get_FIFODepth());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"FIFODepth(#;)",get_FIFODepth());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_BufControl */ 

enum Bits_BufControl : uint32
 {
  BufControl_TXFIFOClear = 0x00000040,
  BufControl_RXFIFOClear = 0x00004000
 };
 
inline Bits_BufControl operator | (Bits_BufControl a,Bits_BufControl b)
 { return Bits_BufControl(uint32(a)|uint32(b)); }
 
struct Type_BufControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_BufControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_BufControl & setTo(Bar &bar) { bar.set_BufControl(*this); return *this; }
 

  template <class Bar>
  Type_BufControl & setTo(Bar &bar,uint32 ind) { bar.set_BufControl(ind,*this); return *this; }
 

  template <class T>
  Type_BufControl & set(T to) { to(*this); return *this; }
 

  Type_BufControl & setbit(Bits_BufControl bits) { value|=Type(bits); return *this; }
 
  Type_BufControl & setbitIf(bool cond,Bits_BufControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_BufControl & clearbit(Bits_BufControl bits) { value&=~Type(bits); return *this; }
 
  Type_BufControl & clearbitIf(bool cond,Bits_BufControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_BufControl bits) const { return value&bits; }
 
  bool testbit(Bits_BufControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_TXFIFOThreshold() const
   {
    return (value>>0)&0x3F;
   }
 
  Type_BufControl & set_TXFIFOThreshold(Type field)
   {
    value=((field&0x3F)<<0)|(value&0xFFFFFFC0);

    return *this;
   }
 

  Type get_RXFIFOThreshold() const
   {
    return (value>>8)&0x3F;
   }
 
  Type_BufControl & set_RXFIFOThreshold(Type field)
   {
    value=((field&0x3F)<<8)|(value&0xFFFFC0FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&BufControl_TXFIFOClear )
      {
       if( first )
         {
          Putobj(out,"TXFIFOClear");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXFIFOClear");
         }
      }

    if( value&BufControl_RXFIFOClear )
      {
       if( first )
         {
          Putobj(out,"RXFIFOClear");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXFIFOClear");
         }
      }

    if( first )
      {
       Printf(out,"TXFIFOThreshold(#;)",get_TXFIFOThreshold());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TXFIFOThreshold(#;)",get_TXFIFOThreshold());
      }

    if( first )
      {
       Printf(out,"RXFIFOThreshold(#;)",get_RXFIFOThreshold());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RXFIFOThreshold(#;)",get_RXFIFOThreshold());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SlaveAddress */ 

struct Type_SlaveAddress
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SlaveAddress(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SlaveAddress & setTo(Bar &bar) { bar.set_SlaveAddress(*this); return *this; }
 

  template <class Bar>
  Type_SlaveAddress & setTo(Bar &bar,uint32 ind) { bar.set_SlaveAddress(ind,*this); return *this; }
 

  template <class T>
  Type_SlaveAddress & set(T to) { to(*this); return *this; }
 

  Type get_Address() const
   {
    return (value>>0)&0x3FF;
   }
 
  Type_SlaveAddress & set_Address(Type field)
   {
    value=((field&0x3FF)<<0)|(value&0xFFFFFC00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Address(#;)",get_Address());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Address(#;)",get_Address());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Counter */ 

struct Type_Counter
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Counter(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Counter & setTo(Bar &bar) { bar.set_Counter(*this); return *this; }
 

  template <class Bar>
  Type_Counter & setTo(Bar &bar,uint32 ind) { bar.set_Counter(ind,*this); return *this; }
 

  template <class T>
  Type_Counter & set(T to) { to(*this); return *this; }
 

  Type get_Count() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_Counter & set_Count(Type field)
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
       Printf(out,"Count(#;)",get_Count());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Count(#;)",get_Count());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Data */ 

struct Type_Data
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Data(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Data & setTo(Bar &bar) { bar.set_Data(*this); return *this; }
 

  template <class Bar>
  Type_Data & setTo(Bar &bar,uint32 ind) { bar.set_Data(ind,*this); return *this; }
 

  template <class T>
  Type_Data & set(T to) { to(*this); return *this; }
 

  Type get_Byte() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Data & set_Byte(Type field)
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
 
/* struct Type_IRQStatus */ 

enum Bits_IRQStatus : uint32
 {
  IRQStatus_BusLost      = 0x00000001,
  IRQStatus_NACK         = 0x00000002,
  IRQStatus_Complete     = 0x00000004,
  IRQStatus_RXReady      = 0x00000008,
  IRQStatus_TXReady      = 0x00000010,
  IRQStatus_BusFree      = 0x00000100,
  IRQStatus_TXUnderflow  = 0x00000400,
  IRQStatus_RXOverflow   = 0x00000800,
  IRQStatus_BusBusy      = 0x00001000,
  IRQStatus_RXReadyShort = 0x00002000,
  IRQStatus_TXReadyShort = 0x00004000
 };
 
inline Bits_IRQStatus operator | (Bits_IRQStatus a,Bits_IRQStatus b)
 { return Bits_IRQStatus(uint32(a)|uint32(b)); }
 
struct Type_IRQStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_IRQStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_IRQStatus & setTo(Bar &bar) { bar.set_IRQStatus(*this); return *this; }
 

  template <class Bar>
  Type_IRQStatus & setTo(Bar &bar,uint32 ind) { bar.set_IRQStatus(ind,*this); return *this; }
 

  template <class T>
  Type_IRQStatus & set(T to) { to(*this); return *this; }
 

  Type_IRQStatus & setbit(Bits_IRQStatus bits) { value|=Type(bits); return *this; }
 
  Type_IRQStatus & setbitIf(bool cond,Bits_IRQStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_IRQStatus & clearbit(Bits_IRQStatus bits) { value&=~Type(bits); return *this; }
 
  Type_IRQStatus & clearbitIf(bool cond,Bits_IRQStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_IRQStatus bits) const { return value&bits; }
 
  bool testbit(Bits_IRQStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&IRQStatus_BusLost )
      {
       if( first )
         {
          Putobj(out,"BusLost");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BusLost");
         }
      }

    if( value&IRQStatus_NACK )
      {
       if( first )
         {
          Putobj(out,"NACK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NACK");
         }
      }

    if( value&IRQStatus_Complete )
      {
       if( first )
         {
          Putobj(out,"Complete");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Complete");
         }
      }

    if( value&IRQStatus_RXReady )
      {
       if( first )
         {
          Putobj(out,"RXReady");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXReady");
         }
      }

    if( value&IRQStatus_TXReady )
      {
       if( first )
         {
          Putobj(out,"TXReady");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXReady");
         }
      }

    if( value&IRQStatus_BusFree )
      {
       if( first )
         {
          Putobj(out,"BusFree");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BusFree");
         }
      }

    if( value&IRQStatus_TXUnderflow )
      {
       if( first )
         {
          Putobj(out,"TXUnderflow");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXUnderflow");
         }
      }

    if( value&IRQStatus_RXOverflow )
      {
       if( first )
         {
          Putobj(out,"RXOverflow");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXOverflow");
         }
      }

    if( value&IRQStatus_BusBusy )
      {
       if( first )
         {
          Putobj(out,"BusBusy");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BusBusy");
         }
      }

    if( value&IRQStatus_RXReadyShort )
      {
       if( first )
         {
          Putobj(out,"RXReadyShort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXReadyShort");
         }
      }

    if( value&IRQStatus_TXReadyShort )
      {
       if( first )
         {
          Putobj(out,"TXReadyShort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXReadyShort");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct I2CBar<RW> */ 

template <class RW>
struct I2CBar
 {
  RW rw;

  template <class ... TT>
  I2CBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
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
 
  //--- Config

  Type_Config get_Config() { return Type_Config(rw.template get<uint32>(0xA4)); }
 
  void set_Config(Type_Config value) { rw.set(0xA4,value.value); }
 
  Setter<Type_Config> to_Config() { return Setter<Type_Config>(rw,0xA4); }
 
  static Type_Config null_Config() { return Type_Config(0); }
 
  static Type_Config ones_Config() { return Type_Config(Type_Config::Type(-1)); }
 
  //--- Prescale

  Type_Prescale get_Prescale() { return Type_Prescale(rw.template get<uint32>(0xB0)); }
 
  void set_Prescale(Type_Prescale value) { rw.set(0xB0,value.value); }
 
  Setter<Type_Prescale> to_Prescale() { return Setter<Type_Prescale>(rw,0xB0); }
 
  static Type_Prescale null_Prescale() { return Type_Prescale(0); }
 
  static Type_Prescale ones_Prescale() { return Type_Prescale(Type_Prescale::Type(-1)); }
 
  //--- SCLLoTime

  Type_SCLLoTime get_SCLLoTime() { return Type_SCLLoTime(rw.template get<uint32>(0xB4)); }
 
  void set_SCLLoTime(Type_SCLLoTime value) { rw.set(0xB4,value.value); }
 
  Setter<Type_SCLLoTime> to_SCLLoTime() { return Setter<Type_SCLLoTime>(rw,0xB4); }
 
  static Type_SCLLoTime null_SCLLoTime() { return Type_SCLLoTime(0); }
 
  static Type_SCLLoTime ones_SCLLoTime() { return Type_SCLLoTime(Type_SCLLoTime::Type(-1)); }
 
  //--- SCLHiTime

  Type_SCLHiTime get_SCLHiTime() { return Type_SCLHiTime(rw.template get<uint32>(0xB8)); }
 
  void set_SCLHiTime(Type_SCLHiTime value) { rw.set(0xB8,value.value); }
 
  Setter<Type_SCLHiTime> to_SCLHiTime() { return Setter<Type_SCLHiTime>(rw,0xB8); }
 
  static Type_SCLHiTime null_SCLHiTime() { return Type_SCLHiTime(0); }
 
  static Type_SCLHiTime ones_SCLHiTime() { return Type_SCLHiTime(Type_SCLHiTime::Type(-1)); }
 
  //--- BufStatus

  Type_BufStatus get_BufStatus() { return Type_BufStatus(rw.template get<uint32>(0xC0)); }
 
  void set_BufStatus(Type_BufStatus value) { rw.set(0xC0,value.value); }
 
  Setter<Type_BufStatus> to_BufStatus() { return Setter<Type_BufStatus>(rw,0xC0); }
 
  static Type_BufStatus null_BufStatus() { return Type_BufStatus(0); }
 
  static Type_BufStatus ones_BufStatus() { return Type_BufStatus(Type_BufStatus::Type(-1)); }
 
  //--- BufControl

  Type_BufControl get_BufControl() { return Type_BufControl(rw.template get<uint32>(0x94)); }
 
  void set_BufControl(Type_BufControl value) { rw.set(0x94,value.value); }
 
  Setter<Type_BufControl> to_BufControl() { return Setter<Type_BufControl>(rw,0x94); }
 
  static Type_BufControl null_BufControl() { return Type_BufControl(0); }
 
  static Type_BufControl ones_BufControl() { return Type_BufControl(Type_BufControl::Type(-1)); }
 
  //--- SlaveAddress

  Type_SlaveAddress get_SlaveAddress() { return Type_SlaveAddress(rw.template get<uint32>(0xAC)); }
 
  void set_SlaveAddress(Type_SlaveAddress value) { rw.set(0xAC,value.value); }
 
  Setter<Type_SlaveAddress> to_SlaveAddress() { return Setter<Type_SlaveAddress>(rw,0xAC); }
 
  static Type_SlaveAddress null_SlaveAddress() { return Type_SlaveAddress(0); }
 
  static Type_SlaveAddress ones_SlaveAddress() { return Type_SlaveAddress(Type_SlaveAddress::Type(-1)); }
 
  //--- Counter

  Type_Counter get_Counter() { return Type_Counter(rw.template get<uint32>(0x98)); }
 
  void set_Counter(Type_Counter value) { rw.set(0x98,value.value); }
 
  Setter<Type_Counter> to_Counter() { return Setter<Type_Counter>(rw,0x98); }
 
  static Type_Counter null_Counter() { return Type_Counter(0); }
 
  static Type_Counter ones_Counter() { return Type_Counter(Type_Counter::Type(-1)); }
 
  //--- Data

  Type_Data get_Data() { return Type_Data(rw.template get<uint32>(0x9C)); }
 
  void set_Data(Type_Data value) { rw.set(0x9C,value.value); }
 
  Setter<Type_Data> to_Data() { return Setter<Type_Data>(rw,0x9C); }
 
  static Type_Data null_Data() { return Type_Data(0); }
 
  static Type_Data ones_Data() { return Type_Data(Type_Data::Type(-1)); }
 
  //--- IRQStatus

  Type_IRQStatus get_IRQStatus() { return Type_IRQStatus(rw.template get<uint32>(0x28)); }
 
  void set_IRQStatus(Type_IRQStatus value) { rw.set(0x28,value.value); }
 
  Setter<Type_IRQStatus> to_IRQStatus() { return Setter<Type_IRQStatus>(rw,0x28); }
 
  static Type_IRQStatus null_IRQStatus() { return Type_IRQStatus(0); }
 
  static Type_IRQStatus ones_IRQStatus() { return Type_IRQStatus(Type_IRQStatus::Type(-1)); }
 
  //--- IRQStatusRaw

  Type_IRQStatus get_IRQStatusRaw() { return Type_IRQStatus(rw.template get<uint32>(0x24)); }
 
  void set_IRQStatusRaw(Type_IRQStatus value) { rw.set(0x24,value.value); }
 
  Setter<Type_IRQStatus> to_IRQStatusRaw() { return Setter<Type_IRQStatus>(rw,0x24); }
 
  //--- IRQEnableSet

  Type_IRQStatus get_IRQEnableSet() { return Type_IRQStatus(rw.template get<uint32>(0x2C)); }
 
  void set_IRQEnableSet(Type_IRQStatus value) { rw.set(0x2C,value.value); }
 
  Setter<Type_IRQStatus> to_IRQEnableSet() { return Setter<Type_IRQStatus>(rw,0x2C); }
 
  //--- IRQEnableClear

  Type_IRQStatus get_IRQEnableClear() { return Type_IRQStatus(rw.template get<uint32>(0x30)); }
 
  void set_IRQEnableClear(Type_IRQStatus value) { rw.set(0x30,value.value); }
 
  Setter<Type_IRQStatus> to_IRQEnableClear() { return Setter<Type_IRQStatus>(rw,0x30); }
 
 };
 
