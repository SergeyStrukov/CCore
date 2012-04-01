/* IXP465.PCI.gen.h */ 

/* type Type_Address */ 

typedef uint32 Type_Address;

/* struct Type_CBE */ 

struct Type_CBE
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CBE(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CBE & setTo(Bar &bar) { bar.set_CBE(*this); return *this; }
 

  template <class Bar>
  Type_CBE & setTo(Bar &bar,uint32 ind) { bar.set_CBE(*this,ind); return *this; }
 

  template <class T>
  Type_CBE & set(T to) { to(*this); return *this; }
 

  Type get_CMD() const
   {
    return (value>>0)&0xF;
   }
 
  Type_CBE & set_CMD(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_BE() const
   {
    return (value>>4)&0xF;
   }
 
  Type_CBE & set_BE(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"CMD(#;)",get_CMD());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CMD(#;)",get_CMD());
      }

    if( first )
      {
       Printf(out,"BE(#;)",get_BE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BE(#;)",get_BE());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_WData */ 

typedef uint32 Type_WData;

/* type Type_RData */ 

typedef uint32 Type_RData;

/* struct Type_CfgAddressCBE */ 

enum Field_CfgAddressCBE_CMD : uint32
 {
  CfgAddressCBE_CMD_Read  = 0x00,
  CfgAddressCBE_CMD_Write = 0x01
 };
 
struct PrintField_CfgAddressCBE_CMD
 {
  Field_CfgAddressCBE_CMD field;

  explicit PrintField_CfgAddressCBE_CMD(Field_CfgAddressCBE_CMD field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Read"); break;
       case 0x01 : Putobj(out,"Write"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CfgAddressCBE_CMD GetTextDesc(Field_CfgAddressCBE_CMD field)
 {
  return PrintField_CfgAddressCBE_CMD(field);
 }
 
struct Type_CfgAddressCBE
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CfgAddressCBE(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CfgAddressCBE & setTo(Bar &bar) { bar.set_CfgAddressCBE(*this); return *this; }
 

  template <class Bar>
  Type_CfgAddressCBE & setTo(Bar &bar,uint32 ind) { bar.set_CfgAddressCBE(*this,ind); return *this; }
 

  template <class T>
  Type_CfgAddressCBE & set(T to) { to(*this); return *this; }
 

  Type get_Address() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_CfgAddressCBE & set_Address(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Field_CfgAddressCBE_CMD get_CMD() const
   {
    return Field_CfgAddressCBE_CMD((value>>16)&0xF);
   }
 
  Type_CfgAddressCBE & set_CMD(Field_CfgAddressCBE_CMD field)
   {
    value=((Type(field)&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_BE() const
   {
    return (value>>20)&0xF;
   }
 
  Type_CfgAddressCBE & set_BE(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

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

    if( first )
      {
       Printf(out,"CMD(#;)",get_CMD());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CMD(#;)",get_CMD());
      }

    if( first )
      {
       Printf(out,"BE(#;)",get_BE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BE(#;)",get_BE());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_CfgWData */ 

typedef uint32 Type_CfgWData;

/* type Type_CfgRData */ 

typedef uint32 Type_CfgRData;

/* struct Type_ControlStatus */ 

enum Bits_ControlStatus : uint32
 {
  ControlStatus_Host         = 0x00000001,
  ControlStatus_Arbiter      = 0x00000002,
  ControlStatus_AHBswap      = 0x00000004,
  ControlStatus_PCIswap      = 0x00000008,
  ControlStatus_AHBbigendian = 0x00000010,
  ControlStatus_DoorbellTest = 0x00000020,
  ControlStatus_SystemError  = 0x00000100,
  ControlStatus_InitComplete = 0x00008000,
  ControlStatus_Reset        = 0x00010000
 };
 
inline Bits_ControlStatus operator | (Bits_ControlStatus a,Bits_ControlStatus b)
 { return Bits_ControlStatus(uint32(a)|uint32(b)); }
 
struct Type_ControlStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ControlStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ControlStatus & setTo(Bar &bar) { bar.set_ControlStatus(*this); return *this; }
 

  template <class Bar>
  Type_ControlStatus & setTo(Bar &bar,uint32 ind) { bar.set_ControlStatus(*this,ind); return *this; }
 

  template <class T>
  Type_ControlStatus & set(T to) { to(*this); return *this; }
 

  Type_ControlStatus & setbit(Bits_ControlStatus bits) { value|=Type(bits); return *this; }
 
  Type_ControlStatus & setbitIf(bool cond,Bits_ControlStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ControlStatus & clearbit(Bits_ControlStatus bits) { value&=~Type(bits); return *this; }
 
  Type_ControlStatus & clearbitIf(bool cond,Bits_ControlStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ControlStatus bits) const { return value&bits; }
 
  bool testbit(Bits_ControlStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ControlStatus_Host )
      {
       if( first )
         {
          Putobj(out,"Host");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Host");
         }
      }

    if( value&ControlStatus_Arbiter )
      {
       if( first )
         {
          Putobj(out,"Arbiter");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Arbiter");
         }
      }

    if( value&ControlStatus_AHBswap )
      {
       if( first )
         {
          Putobj(out,"AHBswap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBswap");
         }
      }

    if( value&ControlStatus_PCIswap )
      {
       if( first )
         {
          Putobj(out,"PCIswap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCIswap");
         }
      }

    if( value&ControlStatus_AHBbigendian )
      {
       if( first )
         {
          Putobj(out,"AHBbigendian");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBbigendian");
         }
      }

    if( value&ControlStatus_DoorbellTest )
      {
       if( first )
         {
          Putobj(out,"DoorbellTest");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DoorbellTest");
         }
      }

    if( value&ControlStatus_SystemError )
      {
       if( first )
         {
          Putobj(out,"SystemError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SystemError");
         }
      }

    if( value&ControlStatus_InitComplete )
      {
       if( first )
         {
          Putobj(out,"InitComplete");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InitComplete");
         }
      }

    if( value&ControlStatus_Reset )
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
 
/* struct Type_IntStatus */ 

enum Bits_IntStatus : uint32
 {
  IntStatus_SystemError = 0x00000001,
  IntStatus_FatalError  = 0x00000002,
  IntStatus_ParityError = 0x00000004,
  IntStatus_AHBError    = 0x00000008,
  IntStatus_DMAWrite    = 0x00000010,
  IntStatus_DMARead     = 0x00000020,
  IntStatus_AHBDoorbell = 0x00000040,
  IntStatus_PCIDoorbell = 0x00000080
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

    if( value&IntStatus_SystemError )
      {
       if( first )
         {
          Putobj(out,"SystemError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SystemError");
         }
      }

    if( value&IntStatus_FatalError )
      {
       if( first )
         {
          Putobj(out,"FatalError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FatalError");
         }
      }

    if( value&IntStatus_ParityError )
      {
       if( first )
         {
          Putobj(out,"ParityError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ParityError");
         }
      }

    if( value&IntStatus_AHBError )
      {
       if( first )
         {
          Putobj(out,"AHBError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBError");
         }
      }

    if( value&IntStatus_DMAWrite )
      {
       if( first )
         {
          Putobj(out,"DMAWrite");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMAWrite");
         }
      }

    if( value&IntStatus_DMARead )
      {
       if( first )
         {
          Putobj(out,"DMARead");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMARead");
         }
      }

    if( value&IntStatus_AHBDoorbell )
      {
       if( first )
         {
          Putobj(out,"AHBDoorbell");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBDoorbell");
         }
      }

    if( value&IntStatus_PCIDoorbell )
      {
       if( first )
         {
          Putobj(out,"PCIDoorbell");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCIDoorbell");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_IntEnable */ 

enum Bits_IntEnable : uint32
 {
  IntEnable_SystemError = 0x00000001,
  IntEnable_FatalError  = 0x00000002,
  IntEnable_ParityError = 0x00000004,
  IntEnable_AHBError    = 0x00000008,
  IntEnable_DMAWrite    = 0x00000010,
  IntEnable_DMARead     = 0x00000020,
  IntEnable_AHBDoorbell = 0x00000040,
  IntEnable_PCIDoorbell = 0x00000080
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
  Type_IntEnable & setTo(Bar &bar,uint32 ind) { bar.set_IntEnable(*this,ind); return *this; }
 

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

    if( value&IntEnable_SystemError )
      {
       if( first )
         {
          Putobj(out,"SystemError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SystemError");
         }
      }

    if( value&IntEnable_FatalError )
      {
       if( first )
         {
          Putobj(out,"FatalError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FatalError");
         }
      }

    if( value&IntEnable_ParityError )
      {
       if( first )
         {
          Putobj(out,"ParityError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ParityError");
         }
      }

    if( value&IntEnable_AHBError )
      {
       if( first )
         {
          Putobj(out,"AHBError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBError");
         }
      }

    if( value&IntEnable_DMAWrite )
      {
       if( first )
         {
          Putobj(out,"DMAWrite");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMAWrite");
         }
      }

    if( value&IntEnable_DMARead )
      {
       if( first )
         {
          Putobj(out,"DMARead");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DMARead");
         }
      }

    if( value&IntEnable_AHBDoorbell )
      {
       if( first )
         {
          Putobj(out,"AHBDoorbell");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AHBDoorbell");
         }
      }

    if( value&IntEnable_PCIDoorbell )
      {
       if( first )
         {
          Putobj(out,"PCIDoorbell");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCIDoorbell");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DMAControl */ 

enum Bits_DMAControl : uint32
 {
  DMAControl_WriteIntEnable = 0x00000001,
  DMAControl_WriteComplete0 = 0x00000010,
  DMAControl_WriteError0    = 0x00000020,
  DMAControl_WriteComplete1 = 0x00000040,
  DMAControl_WriteError1    = 0x00000080,
  DMAControl_ReadIntEnable  = 0x00000100,
  DMAControl_ReadComplete0  = 0x00001000,
  DMAControl_ReadError0     = 0x00002000,
  DMAControl_ReadComplete1  = 0x00004000,
  DMAControl_ReadError1     = 0x00008000
 };
 
inline Bits_DMAControl operator | (Bits_DMAControl a,Bits_DMAControl b)
 { return Bits_DMAControl(uint32(a)|uint32(b)); }
 
struct Type_DMAControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DMAControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAControl & setTo(Bar &bar) { bar.set_DMAControl(*this); return *this; }
 

  template <class Bar>
  Type_DMAControl & setTo(Bar &bar,uint32 ind) { bar.set_DMAControl(*this,ind); return *this; }
 

  template <class T>
  Type_DMAControl & set(T to) { to(*this); return *this; }
 

  Type_DMAControl & setbit(Bits_DMAControl bits) { value|=Type(bits); return *this; }
 
  Type_DMAControl & setbitIf(bool cond,Bits_DMAControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAControl & clearbit(Bits_DMAControl bits) { value&=~Type(bits); return *this; }
 
  Type_DMAControl & clearbitIf(bool cond,Bits_DMAControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAControl bits) const { return value&bits; }
 
  bool testbit(Bits_DMAControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAControl_WriteIntEnable )
      {
       if( first )
         {
          Putobj(out,"WriteIntEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WriteIntEnable");
         }
      }

    if( value&DMAControl_WriteComplete0 )
      {
       if( first )
         {
          Putobj(out,"WriteComplete0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WriteComplete0");
         }
      }

    if( value&DMAControl_WriteError0 )
      {
       if( first )
         {
          Putobj(out,"WriteError0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WriteError0");
         }
      }

    if( value&DMAControl_WriteComplete1 )
      {
       if( first )
         {
          Putobj(out,"WriteComplete1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WriteComplete1");
         }
      }

    if( value&DMAControl_WriteError1 )
      {
       if( first )
         {
          Putobj(out,"WriteError1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WriteError1");
         }
      }

    if( value&DMAControl_ReadIntEnable )
      {
       if( first )
         {
          Putobj(out,"ReadIntEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ReadIntEnable");
         }
      }

    if( value&DMAControl_ReadComplete0 )
      {
       if( first )
         {
          Putobj(out,"ReadComplete0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ReadComplete0");
         }
      }

    if( value&DMAControl_ReadError0 )
      {
       if( first )
         {
          Putobj(out,"ReadError0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ReadError0");
         }
      }

    if( value&DMAControl_ReadComplete1 )
      {
       if( first )
         {
          Putobj(out,"ReadComplete1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ReadComplete1");
         }
      }

    if( value&DMAControl_ReadError1 )
      {
       if( first )
         {
          Putobj(out,"ReadError1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ReadError1");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_AHBMemBase */ 

struct Type_AHBMemBase
 {
  typedef uint32 Type;

  Type value;


  explicit Type_AHBMemBase(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_AHBMemBase & setTo(Bar &bar) { bar.set_AHBMemBase(*this); return *this; }
 

  template <class Bar>
  Type_AHBMemBase & setTo(Bar &bar,uint32 ind) { bar.set_AHBMemBase(*this,ind); return *this; }
 

  template <class T>
  Type_AHBMemBase & set(T to) { to(*this); return *this; }
 

  Type get_Base3() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_AHBMemBase & set_Base3(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_Base2() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_AHBMemBase & set_Base2(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_Base1() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_AHBMemBase & set_Base1(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_Base0() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_AHBMemBase & set_Base0(Type field)
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
       Printf(out,"Base3(#;)",get_Base3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base3(#;)",get_Base3());
      }

    if( first )
      {
       Printf(out,"Base2(#;)",get_Base2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base2(#;)",get_Base2());
      }

    if( first )
      {
       Printf(out,"Base1(#;)",get_Base1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base1(#;)",get_Base1());
      }

    if( first )
      {
       Printf(out,"Base0(#;)",get_Base0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base0(#;)",get_Base0());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_AHBIOBase */ 

struct Type_AHBIOBase
 {
  typedef uint32 Type;

  Type value;


  explicit Type_AHBIOBase(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_AHBIOBase & setTo(Bar &bar) { bar.set_AHBIOBase(*this); return *this; }
 

  template <class Bar>
  Type_AHBIOBase & setTo(Bar &bar,uint32 ind) { bar.set_AHBIOBase(*this,ind); return *this; }
 

  template <class T>
  Type_AHBIOBase & set(T to) { to(*this); return *this; }
 

  Type get_Base() const
   {
    return (value>>0)&0xFFFFFF;
   }
 
  Type_AHBIOBase & set_Base(Type field)
   {
    value=((field&0xFFFFFF)<<0)|(value&0xFF000000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Base(#;)",get_Base());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base(#;)",get_Base());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PCIMemBase */ 

struct Type_PCIMemBase
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PCIMemBase(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PCIMemBase & setTo(Bar &bar) { bar.set_PCIMemBase(*this); return *this; }
 

  template <class Bar>
  Type_PCIMemBase & setTo(Bar &bar,uint32 ind) { bar.set_PCIMemBase(*this,ind); return *this; }
 

  template <class T>
  Type_PCIMemBase & set(T to) { to(*this); return *this; }
 

  Type get_Base3() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_PCIMemBase & set_Base3(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_Base2() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_PCIMemBase & set_Base2(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_Base1() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_PCIMemBase & set_Base1(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_Base0() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_PCIMemBase & set_Base0(Type field)
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
       Printf(out,"Base3(#;)",get_Base3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base3(#;)",get_Base3());
      }

    if( first )
      {
       Printf(out,"Base2(#;)",get_Base2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base2(#;)",get_Base2());
      }

    if( first )
      {
       Printf(out,"Base1(#;)",get_Base1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base1(#;)",get_Base1());
      }

    if( first )
      {
       Printf(out,"Base0(#;)",get_Base0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base0(#;)",get_Base0());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_AHBDoorbell */ 

typedef uint32 Type_AHBDoorbell;

/* type Type_PCIDoorbell */ 

typedef uint32 Type_PCIDoorbell;

/* type Type_DMAWriteAHBAddress0 */ 

typedef uint32 Type_DMAWriteAHBAddress0;

/* type Type_DMAWritePCIAddress0 */ 

typedef uint32 Type_DMAWritePCIAddress0;

/* struct Type_DMAWriteLen0 */ 

enum Bits_DMAWriteLen0 : uint32
 {
  DMAWriteLen0_DS = 0x10000000,
  DMAWriteLen0_EN = 0x80000000
 };
 
inline Bits_DMAWriteLen0 operator | (Bits_DMAWriteLen0 a,Bits_DMAWriteLen0 b)
 { return Bits_DMAWriteLen0(uint32(a)|uint32(b)); }
 
struct Type_DMAWriteLen0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DMAWriteLen0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAWriteLen0 & setTo(Bar &bar) { bar.set_DMAWriteLen0(*this); return *this; }
 

  template <class Bar>
  Type_DMAWriteLen0 & setTo(Bar &bar,uint32 ind) { bar.set_DMAWriteLen0(*this,ind); return *this; }
 

  template <class T>
  Type_DMAWriteLen0 & set(T to) { to(*this); return *this; }
 

  Type_DMAWriteLen0 & setbit(Bits_DMAWriteLen0 bits) { value|=Type(bits); return *this; }
 
  Type_DMAWriteLen0 & setbitIf(bool cond,Bits_DMAWriteLen0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAWriteLen0 & clearbit(Bits_DMAWriteLen0 bits) { value&=~Type(bits); return *this; }
 
  Type_DMAWriteLen0 & clearbitIf(bool cond,Bits_DMAWriteLen0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAWriteLen0 bits) const { return value&bits; }
 
  bool testbit(Bits_DMAWriteLen0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_WordLen() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_DMAWriteLen0 & set_WordLen(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAWriteLen0_DS )
      {
       if( first )
         {
          Putobj(out,"DS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS");
         }
      }

    if( value&DMAWriteLen0_EN )
      {
       if( first )
         {
          Putobj(out,"EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EN");
         }
      }

    if( first )
      {
       Printf(out,"WordLen(#;)",get_WordLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WordLen(#;)",get_WordLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DMAWriteAHBAddress1 */ 

typedef uint32 Type_DMAWriteAHBAddress1;

/* type Type_DMAWritePCIAddress1 */ 

typedef uint32 Type_DMAWritePCIAddress1;

/* struct Type_DMAWriteLen1 */ 

enum Bits_DMAWriteLen1 : uint32
 {
  DMAWriteLen1_DS = 0x10000000,
  DMAWriteLen1_EN = 0x80000000
 };
 
inline Bits_DMAWriteLen1 operator | (Bits_DMAWriteLen1 a,Bits_DMAWriteLen1 b)
 { return Bits_DMAWriteLen1(uint32(a)|uint32(b)); }
 
struct Type_DMAWriteLen1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DMAWriteLen1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAWriteLen1 & setTo(Bar &bar) { bar.set_DMAWriteLen1(*this); return *this; }
 

  template <class Bar>
  Type_DMAWriteLen1 & setTo(Bar &bar,uint32 ind) { bar.set_DMAWriteLen1(*this,ind); return *this; }
 

  template <class T>
  Type_DMAWriteLen1 & set(T to) { to(*this); return *this; }
 

  Type_DMAWriteLen1 & setbit(Bits_DMAWriteLen1 bits) { value|=Type(bits); return *this; }
 
  Type_DMAWriteLen1 & setbitIf(bool cond,Bits_DMAWriteLen1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAWriteLen1 & clearbit(Bits_DMAWriteLen1 bits) { value&=~Type(bits); return *this; }
 
  Type_DMAWriteLen1 & clearbitIf(bool cond,Bits_DMAWriteLen1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAWriteLen1 bits) const { return value&bits; }
 
  bool testbit(Bits_DMAWriteLen1 bits) const { return (value&bits)==Type(bits); }
 

  Type get_WordLen() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_DMAWriteLen1 & set_WordLen(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAWriteLen1_DS )
      {
       if( first )
         {
          Putobj(out,"DS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS");
         }
      }

    if( value&DMAWriteLen1_EN )
      {
       if( first )
         {
          Putobj(out,"EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EN");
         }
      }

    if( first )
      {
       Printf(out,"WordLen(#;)",get_WordLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WordLen(#;)",get_WordLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DMAReadAHBAddress0 */ 

typedef uint32 Type_DMAReadAHBAddress0;

/* type Type_DMAReadPCIAddress0 */ 

typedef uint32 Type_DMAReadPCIAddress0;

/* struct Type_DMAReadLen0 */ 

enum Bits_DMAReadLen0 : uint32
 {
  DMAReadLen0_DS = 0x10000000,
  DMAReadLen0_EN = 0x80000000
 };
 
inline Bits_DMAReadLen0 operator | (Bits_DMAReadLen0 a,Bits_DMAReadLen0 b)
 { return Bits_DMAReadLen0(uint32(a)|uint32(b)); }
 
struct Type_DMAReadLen0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DMAReadLen0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAReadLen0 & setTo(Bar &bar) { bar.set_DMAReadLen0(*this); return *this; }
 

  template <class Bar>
  Type_DMAReadLen0 & setTo(Bar &bar,uint32 ind) { bar.set_DMAReadLen0(*this,ind); return *this; }
 

  template <class T>
  Type_DMAReadLen0 & set(T to) { to(*this); return *this; }
 

  Type_DMAReadLen0 & setbit(Bits_DMAReadLen0 bits) { value|=Type(bits); return *this; }
 
  Type_DMAReadLen0 & setbitIf(bool cond,Bits_DMAReadLen0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAReadLen0 & clearbit(Bits_DMAReadLen0 bits) { value&=~Type(bits); return *this; }
 
  Type_DMAReadLen0 & clearbitIf(bool cond,Bits_DMAReadLen0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAReadLen0 bits) const { return value&bits; }
 
  bool testbit(Bits_DMAReadLen0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_WordLen() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_DMAReadLen0 & set_WordLen(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAReadLen0_DS )
      {
       if( first )
         {
          Putobj(out,"DS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS");
         }
      }

    if( value&DMAReadLen0_EN )
      {
       if( first )
         {
          Putobj(out,"EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EN");
         }
      }

    if( first )
      {
       Printf(out,"WordLen(#;)",get_WordLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WordLen(#;)",get_WordLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DMAReadAHBAddress1 */ 

typedef uint32 Type_DMAReadAHBAddress1;

/* type Type_DMAReadPCIAddress1 */ 

typedef uint32 Type_DMAReadPCIAddress1;

/* struct Type_DMAReadLen1 */ 

enum Bits_DMAReadLen1 : uint32
 {
  DMAReadLen1_DS = 0x10000000,
  DMAReadLen1_EN = 0x80000000
 };
 
inline Bits_DMAReadLen1 operator | (Bits_DMAReadLen1 a,Bits_DMAReadLen1 b)
 { return Bits_DMAReadLen1(uint32(a)|uint32(b)); }
 
struct Type_DMAReadLen1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DMAReadLen1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DMAReadLen1 & setTo(Bar &bar) { bar.set_DMAReadLen1(*this); return *this; }
 

  template <class Bar>
  Type_DMAReadLen1 & setTo(Bar &bar,uint32 ind) { bar.set_DMAReadLen1(*this,ind); return *this; }
 

  template <class T>
  Type_DMAReadLen1 & set(T to) { to(*this); return *this; }
 

  Type_DMAReadLen1 & setbit(Bits_DMAReadLen1 bits) { value|=Type(bits); return *this; }
 
  Type_DMAReadLen1 & setbitIf(bool cond,Bits_DMAReadLen1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DMAReadLen1 & clearbit(Bits_DMAReadLen1 bits) { value&=~Type(bits); return *this; }
 
  Type_DMAReadLen1 & clearbitIf(bool cond,Bits_DMAReadLen1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DMAReadLen1 bits) const { return value&bits; }
 
  bool testbit(Bits_DMAReadLen1 bits) const { return (value&bits)==Type(bits); }
 

  Type get_WordLen() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_DMAReadLen1 & set_WordLen(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DMAReadLen1_DS )
      {
       if( first )
         {
          Putobj(out,"DS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS");
         }
      }

    if( value&DMAReadLen1_EN )
      {
       if( first )
         {
          Putobj(out,"EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EN");
         }
      }

    if( first )
      {
       Printf(out,"WordLen(#;)",get_WordLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WordLen(#;)",get_WordLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct PCIBar<RW> */ 

template <class RW>
struct PCIBar
 {
  RW rw;

  template <class ... TT>
  PCIBar(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- Address

  Type_Address get_Address() { return Type_Address(rw.template get<uint32>(0x0)); }
 
  void set_Address(Type_Address value) { rw.set(0x0,value); }
 
  void set_Address_null() { rw.set(0x0,Type_Address(0)); }
 
  void set_Address_ones() { rw.set(0x0,Type_Address(-1)); }
 
  //--- CBE

  Type_CBE get_CBE() { return Type_CBE(rw.template get<uint32>(0x4)); }
 
  void set_CBE(Type_CBE value) { rw.set(0x4,value.value); }
 
  Setter<Type_CBE> to_CBE() { return Setter<Type_CBE>(rw,0x4); }
 
  static Type_CBE null_CBE() { return Type_CBE(0); }
 
  static Type_CBE ones_CBE() { return Type_CBE(Type_CBE::Type(-1)); }
 
  //--- WData

  Type_WData get_WData() { return Type_WData(rw.template get<uint32>(0x8)); }
 
  void set_WData(Type_WData value) { rw.set(0x8,value); }
 
  void set_WData_null() { rw.set(0x8,Type_WData(0)); }
 
  void set_WData_ones() { rw.set(0x8,Type_WData(-1)); }
 
  //--- RData

  Type_RData get_RData() { return Type_RData(rw.template get<uint32>(0xC)); }
 
  //--- CfgAddressCBE

  Type_CfgAddressCBE get_CfgAddressCBE() { return Type_CfgAddressCBE(rw.template get<uint32>(0x10)); }
 
  void set_CfgAddressCBE(Type_CfgAddressCBE value) { rw.set(0x10,value.value); }
 
  Setter<Type_CfgAddressCBE> to_CfgAddressCBE() { return Setter<Type_CfgAddressCBE>(rw,0x10); }
 
  static Type_CfgAddressCBE null_CfgAddressCBE() { return Type_CfgAddressCBE(0); }
 
  static Type_CfgAddressCBE ones_CfgAddressCBE() { return Type_CfgAddressCBE(Type_CfgAddressCBE::Type(-1)); }
 
  //--- CfgWData

  Type_CfgWData get_CfgWData() { return Type_CfgWData(rw.template get<uint32>(0x14)); }
 
  void set_CfgWData(Type_CfgWData value) { rw.set(0x14,value); }
 
  void set_CfgWData_null() { rw.set(0x14,Type_CfgWData(0)); }
 
  void set_CfgWData_ones() { rw.set(0x14,Type_CfgWData(-1)); }
 
  //--- CfgRData

  Type_CfgRData get_CfgRData() { return Type_CfgRData(rw.template get<uint32>(0x18)); }
 
  //--- ControlStatus

  Type_ControlStatus get_ControlStatus() { return Type_ControlStatus(rw.template get<uint32>(0x1C)); }
 
  void set_ControlStatus(Type_ControlStatus value) { rw.set(0x1C,value.value); }
 
  Setter<Type_ControlStatus> to_ControlStatus() { return Setter<Type_ControlStatus>(rw,0x1C); }
 
  static Type_ControlStatus null_ControlStatus() { return Type_ControlStatus(0); }
 
  static Type_ControlStatus ones_ControlStatus() { return Type_ControlStatus(Type_ControlStatus::Type(-1)); }
 
  //--- IntStatus

  Type_IntStatus get_IntStatus() { return Type_IntStatus(rw.template get<uint32>(0x20)); }
 
  void set_IntStatus(Type_IntStatus value) { rw.set(0x20,value.value); }
 
  Setter<Type_IntStatus> to_IntStatus() { return Setter<Type_IntStatus>(rw,0x20); }
 
  static Type_IntStatus null_IntStatus() { return Type_IntStatus(0); }
 
  static Type_IntStatus ones_IntStatus() { return Type_IntStatus(Type_IntStatus::Type(-1)); }
 
  //--- IntEnable

  Type_IntEnable get_IntEnable() { return Type_IntEnable(rw.template get<uint32>(0x24)); }
 
  void set_IntEnable(Type_IntEnable value) { rw.set(0x24,value.value); }
 
  Setter<Type_IntEnable> to_IntEnable() { return Setter<Type_IntEnable>(rw,0x24); }
 
  static Type_IntEnable null_IntEnable() { return Type_IntEnable(0); }
 
  static Type_IntEnable ones_IntEnable() { return Type_IntEnable(Type_IntEnable::Type(-1)); }
 
  //--- DMAControl

  Type_DMAControl get_DMAControl() { return Type_DMAControl(rw.template get<uint32>(0x28)); }
 
  void set_DMAControl(Type_DMAControl value) { rw.set(0x28,value.value); }
 
  Setter<Type_DMAControl> to_DMAControl() { return Setter<Type_DMAControl>(rw,0x28); }
 
  static Type_DMAControl null_DMAControl() { return Type_DMAControl(0); }
 
  static Type_DMAControl ones_DMAControl() { return Type_DMAControl(Type_DMAControl::Type(-1)); }
 
  //--- AHBMemBase

  Type_AHBMemBase get_AHBMemBase() { return Type_AHBMemBase(rw.template get<uint32>(0x2C)); }
 
  void set_AHBMemBase(Type_AHBMemBase value) { rw.set(0x2C,value.value); }
 
  Setter<Type_AHBMemBase> to_AHBMemBase() { return Setter<Type_AHBMemBase>(rw,0x2C); }
 
  static Type_AHBMemBase null_AHBMemBase() { return Type_AHBMemBase(0); }
 
  static Type_AHBMemBase ones_AHBMemBase() { return Type_AHBMemBase(Type_AHBMemBase::Type(-1)); }
 
  //--- AHBIOBase

  Type_AHBIOBase get_AHBIOBase() { return Type_AHBIOBase(rw.template get<uint32>(0x30)); }
 
  void set_AHBIOBase(Type_AHBIOBase value) { rw.set(0x30,value.value); }
 
  Setter<Type_AHBIOBase> to_AHBIOBase() { return Setter<Type_AHBIOBase>(rw,0x30); }
 
  static Type_AHBIOBase null_AHBIOBase() { return Type_AHBIOBase(0); }
 
  static Type_AHBIOBase ones_AHBIOBase() { return Type_AHBIOBase(Type_AHBIOBase::Type(-1)); }
 
  //--- PCIMemBase

  Type_PCIMemBase get_PCIMemBase() { return Type_PCIMemBase(rw.template get<uint32>(0x34)); }
 
  void set_PCIMemBase(Type_PCIMemBase value) { rw.set(0x34,value.value); }
 
  Setter<Type_PCIMemBase> to_PCIMemBase() { return Setter<Type_PCIMemBase>(rw,0x34); }
 
  static Type_PCIMemBase null_PCIMemBase() { return Type_PCIMemBase(0); }
 
  static Type_PCIMemBase ones_PCIMemBase() { return Type_PCIMemBase(Type_PCIMemBase::Type(-1)); }
 
  //--- AHBDoorbell

  Type_AHBDoorbell get_AHBDoorbell() { return Type_AHBDoorbell(rw.template get<uint32>(0x38)); }
 
  void set_AHBDoorbell(Type_AHBDoorbell value) { rw.set(0x38,value); }
 
  void set_AHBDoorbell_null() { rw.set(0x38,Type_AHBDoorbell(0)); }
 
  void set_AHBDoorbell_ones() { rw.set(0x38,Type_AHBDoorbell(-1)); }
 
  //--- PCIDoorbell

  Type_PCIDoorbell get_PCIDoorbell() { return Type_PCIDoorbell(rw.template get<uint32>(0x3C)); }
 
  void set_PCIDoorbell(Type_PCIDoorbell value) { rw.set(0x3C,value); }
 
  void set_PCIDoorbell_null() { rw.set(0x3C,Type_PCIDoorbell(0)); }
 
  void set_PCIDoorbell_ones() { rw.set(0x3C,Type_PCIDoorbell(-1)); }
 
  //--- DMAWriteAHBAddress0

  Type_DMAWriteAHBAddress0 get_DMAWriteAHBAddress0() { return Type_DMAWriteAHBAddress0(rw.template get<uint32>(0x40)); }
 
  void set_DMAWriteAHBAddress0(Type_DMAWriteAHBAddress0 value) { rw.set(0x40,value); }
 
  void set_DMAWriteAHBAddress0_null() { rw.set(0x40,Type_DMAWriteAHBAddress0(0)); }
 
  void set_DMAWriteAHBAddress0_ones() { rw.set(0x40,Type_DMAWriteAHBAddress0(-1)); }
 
  //--- DMAWritePCIAddress0

  Type_DMAWritePCIAddress0 get_DMAWritePCIAddress0() { return Type_DMAWritePCIAddress0(rw.template get<uint32>(0x44)); }
 
  void set_DMAWritePCIAddress0(Type_DMAWritePCIAddress0 value) { rw.set(0x44,value); }
 
  void set_DMAWritePCIAddress0_null() { rw.set(0x44,Type_DMAWritePCIAddress0(0)); }
 
  void set_DMAWritePCIAddress0_ones() { rw.set(0x44,Type_DMAWritePCIAddress0(-1)); }
 
  //--- DMAWriteLen0

  Type_DMAWriteLen0 get_DMAWriteLen0() { return Type_DMAWriteLen0(rw.template get<uint32>(0x48)); }
 
  void set_DMAWriteLen0(Type_DMAWriteLen0 value) { rw.set(0x48,value.value); }
 
  Setter<Type_DMAWriteLen0> to_DMAWriteLen0() { return Setter<Type_DMAWriteLen0>(rw,0x48); }
 
  static Type_DMAWriteLen0 null_DMAWriteLen0() { return Type_DMAWriteLen0(0); }
 
  static Type_DMAWriteLen0 ones_DMAWriteLen0() { return Type_DMAWriteLen0(Type_DMAWriteLen0::Type(-1)); }
 
  //--- DMAWriteAHBAddress1

  Type_DMAWriteAHBAddress1 get_DMAWriteAHBAddress1() { return Type_DMAWriteAHBAddress1(rw.template get<uint32>(0x4C)); }
 
  void set_DMAWriteAHBAddress1(Type_DMAWriteAHBAddress1 value) { rw.set(0x4C,value); }
 
  void set_DMAWriteAHBAddress1_null() { rw.set(0x4C,Type_DMAWriteAHBAddress1(0)); }
 
  void set_DMAWriteAHBAddress1_ones() { rw.set(0x4C,Type_DMAWriteAHBAddress1(-1)); }
 
  //--- DMAWritePCIAddress1

  Type_DMAWritePCIAddress1 get_DMAWritePCIAddress1() { return Type_DMAWritePCIAddress1(rw.template get<uint32>(0x50)); }
 
  void set_DMAWritePCIAddress1(Type_DMAWritePCIAddress1 value) { rw.set(0x50,value); }
 
  void set_DMAWritePCIAddress1_null() { rw.set(0x50,Type_DMAWritePCIAddress1(0)); }
 
  void set_DMAWritePCIAddress1_ones() { rw.set(0x50,Type_DMAWritePCIAddress1(-1)); }
 
  //--- DMAWriteLen1

  Type_DMAWriteLen1 get_DMAWriteLen1() { return Type_DMAWriteLen1(rw.template get<uint32>(0x54)); }
 
  void set_DMAWriteLen1(Type_DMAWriteLen1 value) { rw.set(0x54,value.value); }
 
  Setter<Type_DMAWriteLen1> to_DMAWriteLen1() { return Setter<Type_DMAWriteLen1>(rw,0x54); }
 
  static Type_DMAWriteLen1 null_DMAWriteLen1() { return Type_DMAWriteLen1(0); }
 
  static Type_DMAWriteLen1 ones_DMAWriteLen1() { return Type_DMAWriteLen1(Type_DMAWriteLen1::Type(-1)); }
 
  //--- DMAReadAHBAddress0

  Type_DMAReadAHBAddress0 get_DMAReadAHBAddress0() { return Type_DMAReadAHBAddress0(rw.template get<uint32>(0x58)); }
 
  void set_DMAReadAHBAddress0(Type_DMAReadAHBAddress0 value) { rw.set(0x58,value); }
 
  void set_DMAReadAHBAddress0_null() { rw.set(0x58,Type_DMAReadAHBAddress0(0)); }
 
  void set_DMAReadAHBAddress0_ones() { rw.set(0x58,Type_DMAReadAHBAddress0(-1)); }
 
  //--- DMAReadPCIAddress0

  Type_DMAReadPCIAddress0 get_DMAReadPCIAddress0() { return Type_DMAReadPCIAddress0(rw.template get<uint32>(0x5C)); }
 
  void set_DMAReadPCIAddress0(Type_DMAReadPCIAddress0 value) { rw.set(0x5C,value); }
 
  void set_DMAReadPCIAddress0_null() { rw.set(0x5C,Type_DMAReadPCIAddress0(0)); }
 
  void set_DMAReadPCIAddress0_ones() { rw.set(0x5C,Type_DMAReadPCIAddress0(-1)); }
 
  //--- DMAReadLen0

  Type_DMAReadLen0 get_DMAReadLen0() { return Type_DMAReadLen0(rw.template get<uint32>(0x60)); }
 
  void set_DMAReadLen0(Type_DMAReadLen0 value) { rw.set(0x60,value.value); }
 
  Setter<Type_DMAReadLen0> to_DMAReadLen0() { return Setter<Type_DMAReadLen0>(rw,0x60); }
 
  static Type_DMAReadLen0 null_DMAReadLen0() { return Type_DMAReadLen0(0); }
 
  static Type_DMAReadLen0 ones_DMAReadLen0() { return Type_DMAReadLen0(Type_DMAReadLen0::Type(-1)); }
 
  //--- DMAReadAHBAddress1

  Type_DMAReadAHBAddress1 get_DMAReadAHBAddress1() { return Type_DMAReadAHBAddress1(rw.template get<uint32>(0x64)); }
 
  void set_DMAReadAHBAddress1(Type_DMAReadAHBAddress1 value) { rw.set(0x64,value); }
 
  void set_DMAReadAHBAddress1_null() { rw.set(0x64,Type_DMAReadAHBAddress1(0)); }
 
  void set_DMAReadAHBAddress1_ones() { rw.set(0x64,Type_DMAReadAHBAddress1(-1)); }
 
  //--- DMAReadPCIAddress1

  Type_DMAReadPCIAddress1 get_DMAReadPCIAddress1() { return Type_DMAReadPCIAddress1(rw.template get<uint32>(0x68)); }
 
  void set_DMAReadPCIAddress1(Type_DMAReadPCIAddress1 value) { rw.set(0x68,value); }
 
  void set_DMAReadPCIAddress1_null() { rw.set(0x68,Type_DMAReadPCIAddress1(0)); }
 
  void set_DMAReadPCIAddress1_ones() { rw.set(0x68,Type_DMAReadPCIAddress1(-1)); }
 
  //--- DMAReadLen1

  Type_DMAReadLen1 get_DMAReadLen1() { return Type_DMAReadLen1(rw.template get<uint32>(0x6C)); }
 
  void set_DMAReadLen1(Type_DMAReadLen1 value) { rw.set(0x6C,value.value); }
 
  Setter<Type_DMAReadLen1> to_DMAReadLen1() { return Setter<Type_DMAReadLen1>(rw,0x6C); }
 
  static Type_DMAReadLen1 null_DMAReadLen1() { return Type_DMAReadLen1(0); }
 
  static Type_DMAReadLen1 ones_DMAReadLen1() { return Type_DMAReadLen1(Type_DMAReadLen1::Type(-1)); }
 
 };
 
