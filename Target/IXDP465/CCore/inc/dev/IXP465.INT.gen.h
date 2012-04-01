/* IXP465.INT.gen.h */ 

/* struct Type_Status */ 

enum Bits_Status : uint32
 {
  Status_NPE_A    = 0x00000001,
  Status_NPE_B    = 0x00000002,
  Status_NPE_C    = 0x00000004,
  Status_QMLO     = 0x00000008,
  Status_QMHI     = 0x00000010,
  Status_T0       = 0x00000020,
  Status_GPIO0    = 0x00000040,
  Status_GPIO1    = 0x00000080,
  Status_PCI      = 0x00000100,
  Status_PCI_DMA1 = 0x00000200,
  Status_PCI_DMA2 = 0x00000400,
  Status_T1       = 0x00000800,
  Status_USBDev   = 0x00001000,
  Status_UART1    = 0x00002000,
  Status_TS       = 0x00004000,
  Status_UART0    = 0x00008000,
  Status_WD       = 0x00010000,
  Status_APB_PMU  = 0x00020000,
  Status_CPU_PMU  = 0x00040000,
  Status_GPIO2    = 0x00080000,
  Status_GPIO3    = 0x00100000,
  Status_GPIO4    = 0x00200000,
  Status_GPIO5    = 0x00400000,
  Status_GPIO6    = 0x00800000,
  Status_GPIO7    = 0x01000000,
  Status_GPIO8    = 0x02000000,
  Status_GPIO9    = 0x04000000,
  Status_GPIO10   = 0x08000000,
  Status_GPIO11   = 0x10000000,
  Status_GPIO12   = 0x20000000,
  Status_SWI0     = 0x40000000,
  Status_SWI1     = 0x80000000
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

    if( value&Status_NPE_A )
      {
       if( first )
         {
          Putobj(out,"NPE_A");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NPE_A");
         }
      }

    if( value&Status_NPE_B )
      {
       if( first )
         {
          Putobj(out,"NPE_B");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NPE_B");
         }
      }

    if( value&Status_NPE_C )
      {
       if( first )
         {
          Putobj(out,"NPE_C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NPE_C");
         }
      }

    if( value&Status_QMLO )
      {
       if( first )
         {
          Putobj(out,"QMLO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"QMLO");
         }
      }

    if( value&Status_QMHI )
      {
       if( first )
         {
          Putobj(out,"QMHI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"QMHI");
         }
      }

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

    if( value&Status_GPIO0 )
      {
       if( first )
         {
          Putobj(out,"GPIO0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO0");
         }
      }

    if( value&Status_GPIO1 )
      {
       if( first )
         {
          Putobj(out,"GPIO1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO1");
         }
      }

    if( value&Status_PCI )
      {
       if( first )
         {
          Putobj(out,"PCI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCI");
         }
      }

    if( value&Status_PCI_DMA1 )
      {
       if( first )
         {
          Putobj(out,"PCI_DMA1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCI_DMA1");
         }
      }

    if( value&Status_PCI_DMA2 )
      {
       if( first )
         {
          Putobj(out,"PCI_DMA2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCI_DMA2");
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

    if( value&Status_USBDev )
      {
       if( first )
         {
          Putobj(out,"USBDev");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"USBDev");
         }
      }

    if( value&Status_UART1 )
      {
       if( first )
         {
          Putobj(out,"UART1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UART1");
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

    if( value&Status_UART0 )
      {
       if( first )
         {
          Putobj(out,"UART0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UART0");
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

    if( value&Status_APB_PMU )
      {
       if( first )
         {
          Putobj(out,"APB_PMU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"APB_PMU");
         }
      }

    if( value&Status_CPU_PMU )
      {
       if( first )
         {
          Putobj(out,"CPU_PMU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CPU_PMU");
         }
      }

    if( value&Status_GPIO2 )
      {
       if( first )
         {
          Putobj(out,"GPIO2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO2");
         }
      }

    if( value&Status_GPIO3 )
      {
       if( first )
         {
          Putobj(out,"GPIO3");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO3");
         }
      }

    if( value&Status_GPIO4 )
      {
       if( first )
         {
          Putobj(out,"GPIO4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO4");
         }
      }

    if( value&Status_GPIO5 )
      {
       if( first )
         {
          Putobj(out,"GPIO5");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO5");
         }
      }

    if( value&Status_GPIO6 )
      {
       if( first )
         {
          Putobj(out,"GPIO6");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO6");
         }
      }

    if( value&Status_GPIO7 )
      {
       if( first )
         {
          Putobj(out,"GPIO7");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO7");
         }
      }

    if( value&Status_GPIO8 )
      {
       if( first )
         {
          Putobj(out,"GPIO8");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO8");
         }
      }

    if( value&Status_GPIO9 )
      {
       if( first )
         {
          Putobj(out,"GPIO9");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO9");
         }
      }

    if( value&Status_GPIO10 )
      {
       if( first )
         {
          Putobj(out,"GPIO10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO10");
         }
      }

    if( value&Status_GPIO11 )
      {
       if( first )
         {
          Putobj(out,"GPIO11");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO11");
         }
      }

    if( value&Status_GPIO12 )
      {
       if( first )
         {
          Putobj(out,"GPIO12");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIO12");
         }
      }

    if( value&Status_SWI0 )
      {
       if( first )
         {
          Putobj(out,"SWI0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SWI0");
         }
      }

    if( value&Status_SWI1 )
      {
       if( first )
         {
          Putobj(out,"SWI1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SWI1");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_IRQHiPriority */ 

typedef uint32 Type_IRQHiPriority;

/* type Type_FIQHiPriority */ 

typedef uint32 Type_FIQHiPriority;

/* struct Type_Status2 */ 

enum Bits_Status2 : uint32
 {
  Status2_USBHost = 0x00000001,
  Status2_I2C     = 0x00000002,
  Status2_SSP     = 0x00000004,
  Status2_TSYNC   = 0x00000008,
  Status2_EAU     = 0x00000010,
  Status2_SHA     = 0x00000020,
  Status2_SWCP    = 0x04000000,
  Status2_QMERR   = 0x10000000,
  Status2_MCU     = 0x20000000,
  Status2_EXP     = 0x40000000
 };
 
inline Bits_Status2 operator | (Bits_Status2 a,Bits_Status2 b)
 { return Bits_Status2(uint32(a)|uint32(b)); }
 
struct Type_Status2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Status2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Status2 & setTo(Bar &bar) { bar.set_Status2(*this); return *this; }
 

  template <class Bar>
  Type_Status2 & setTo(Bar &bar,uint32 ind) { bar.set_Status2(*this,ind); return *this; }
 

  template <class T>
  Type_Status2 & set(T to) { to(*this); return *this; }
 

  Type_Status2 & setbit(Bits_Status2 bits) { value|=Type(bits); return *this; }
 
  Type_Status2 & setbitIf(bool cond,Bits_Status2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Status2 & clearbit(Bits_Status2 bits) { value&=~Type(bits); return *this; }
 
  Type_Status2 & clearbitIf(bool cond,Bits_Status2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Status2 bits) const { return value&bits; }
 
  bool testbit(Bits_Status2 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Status2_USBHost )
      {
       if( first )
         {
          Putobj(out,"USBHost");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"USBHost");
         }
      }

    if( value&Status2_I2C )
      {
       if( first )
         {
          Putobj(out,"I2C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"I2C");
         }
      }

    if( value&Status2_SSP )
      {
       if( first )
         {
          Putobj(out,"SSP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSP");
         }
      }

    if( value&Status2_TSYNC )
      {
       if( first )
         {
          Putobj(out,"TSYNC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TSYNC");
         }
      }

    if( value&Status2_EAU )
      {
       if( first )
         {
          Putobj(out,"EAU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EAU");
         }
      }

    if( value&Status2_SHA )
      {
       if( first )
         {
          Putobj(out,"SHA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SHA");
         }
      }

    if( value&Status2_SWCP )
      {
       if( first )
         {
          Putobj(out,"SWCP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SWCP");
         }
      }

    if( value&Status2_QMERR )
      {
       if( first )
         {
          Putobj(out,"QMERR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"QMERR");
         }
      }

    if( value&Status2_MCU )
      {
       if( first )
         {
          Putobj(out,"MCU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MCU");
         }
      }

    if( value&Status2_EXP )
      {
       if( first )
         {
          Putobj(out,"EXP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EXP");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Priority */ 

struct Type_Priority
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Priority(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Priority & setTo(Bar &bar) { bar.set_Priority(*this); return *this; }
 

  template <class Bar>
  Type_Priority & setTo(Bar &bar,uint32 ind) { bar.set_Priority(*this,ind); return *this; }
 

  template <class T>
  Type_Priority & set(T to) { to(*this); return *this; }
 

  Type get_Pri_NPE_A() const
   {
    return (value>>0)&0x7;
   }
 
  Type_Priority & set_Pri_NPE_A(Type field)
   {
    value=((field&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Type get_Pri_NPE_B() const
   {
    return (value>>3)&0x7;
   }
 
  Type_Priority & set_Pri_NPE_B(Type field)
   {
    value=((field&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Type get_Pri_NPE_C() const
   {
    return (value>>6)&0x7;
   }
 
  Type_Priority & set_Pri_NPE_C(Type field)
   {
    value=((field&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  Type get_Pri_QMLO() const
   {
    return (value>>9)&0x7;
   }
 
  Type_Priority & set_Pri_QMLO(Type field)
   {
    value=((field&0x7)<<9)|(value&0xFFFFF1FF);

    return *this;
   }
 

  Type get_Pri_QMHI() const
   {
    return (value>>12)&0x7;
   }
 
  Type_Priority & set_Pri_QMHI(Type field)
   {
    value=((field&0x7)<<12)|(value&0xFFFF8FFF);

    return *this;
   }
 

  Type get_Pri_T0() const
   {
    return (value>>15)&0x7;
   }
 
  Type_Priority & set_Pri_T0(Type field)
   {
    value=((field&0x7)<<15)|(value&0xFFFC7FFF);

    return *this;
   }
 

  Type get_Pri_GPIO0() const
   {
    return (value>>18)&0x7;
   }
 
  Type_Priority & set_Pri_GPIO0(Type field)
   {
    value=((field&0x7)<<18)|(value&0xFFE3FFFF);

    return *this;
   }
 

  Type get_Pri_GPIO1() const
   {
    return (value>>21)&0x7;
   }
 
  Type_Priority & set_Pri_GPIO1(Type field)
   {
    value=((field&0x7)<<21)|(value&0xFF1FFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri_NPE_A(#;)",get_Pri_NPE_A());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_NPE_A(#;)",get_Pri_NPE_A());
      }

    if( first )
      {
       Printf(out,"Pri_NPE_B(#;)",get_Pri_NPE_B());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_NPE_B(#;)",get_Pri_NPE_B());
      }

    if( first )
      {
       Printf(out,"Pri_NPE_C(#;)",get_Pri_NPE_C());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_NPE_C(#;)",get_Pri_NPE_C());
      }

    if( first )
      {
       Printf(out,"Pri_QMLO(#;)",get_Pri_QMLO());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_QMLO(#;)",get_Pri_QMLO());
      }

    if( first )
      {
       Printf(out,"Pri_QMHI(#;)",get_Pri_QMHI());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_QMHI(#;)",get_Pri_QMHI());
      }

    if( first )
      {
       Printf(out,"Pri_T0(#;)",get_Pri_T0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_T0(#;)",get_Pri_T0());
      }

    if( first )
      {
       Printf(out,"Pri_GPIO0(#;)",get_Pri_GPIO0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_GPIO0(#;)",get_Pri_GPIO0());
      }

    if( first )
      {
       Printf(out,"Pri_GPIO1(#;)",get_Pri_GPIO1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri_GPIO1(#;)",get_Pri_GPIO1());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_HiPriorityEnable */ 

enum Bits_HiPriorityEnable : uint32
 {
  HiPriorityEnable_USBHost = 0x00000001,
  HiPriorityEnable_I2C     = 0x00000002,
  HiPriorityEnable_SSP     = 0x00000004,
  HiPriorityEnable_TSYNC   = 0x00000008,
  HiPriorityEnable_EAU     = 0x00000010,
  HiPriorityEnable_SHA     = 0x00000020,
  HiPriorityEnable_SWCP    = 0x04000000,
  HiPriorityEnable_QMERR   = 0x10000000,
  HiPriorityEnable_MCU     = 0x20000000,
  HiPriorityEnable_EXP     = 0x40000000
 };
 
inline Bits_HiPriorityEnable operator | (Bits_HiPriorityEnable a,Bits_HiPriorityEnable b)
 { return Bits_HiPriorityEnable(uint32(a)|uint32(b)); }
 
struct Type_HiPriorityEnable
 {
  typedef uint32 Type;

  Type value;


  explicit Type_HiPriorityEnable(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_HiPriorityEnable & setTo(Bar &bar) { bar.set_HiPriorityEnable(*this); return *this; }
 

  template <class Bar>
  Type_HiPriorityEnable & setTo(Bar &bar,uint32 ind) { bar.set_HiPriorityEnable(*this,ind); return *this; }
 

  template <class T>
  Type_HiPriorityEnable & set(T to) { to(*this); return *this; }
 

  Type_HiPriorityEnable & setbit(Bits_HiPriorityEnable bits) { value|=Type(bits); return *this; }
 
  Type_HiPriorityEnable & setbitIf(bool cond,Bits_HiPriorityEnable bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_HiPriorityEnable & clearbit(Bits_HiPriorityEnable bits) { value&=~Type(bits); return *this; }
 
  Type_HiPriorityEnable & clearbitIf(bool cond,Bits_HiPriorityEnable bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_HiPriorityEnable bits) const { return value&bits; }
 
  bool testbit(Bits_HiPriorityEnable bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&HiPriorityEnable_USBHost )
      {
       if( first )
         {
          Putobj(out,"USBHost");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"USBHost");
         }
      }

    if( value&HiPriorityEnable_I2C )
      {
       if( first )
         {
          Putobj(out,"I2C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"I2C");
         }
      }

    if( value&HiPriorityEnable_SSP )
      {
       if( first )
         {
          Putobj(out,"SSP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSP");
         }
      }

    if( value&HiPriorityEnable_TSYNC )
      {
       if( first )
         {
          Putobj(out,"TSYNC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TSYNC");
         }
      }

    if( value&HiPriorityEnable_EAU )
      {
       if( first )
         {
          Putobj(out,"EAU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EAU");
         }
      }

    if( value&HiPriorityEnable_SHA )
      {
       if( first )
         {
          Putobj(out,"SHA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SHA");
         }
      }

    if( value&HiPriorityEnable_SWCP )
      {
       if( first )
         {
          Putobj(out,"SWCP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SWCP");
         }
      }

    if( value&HiPriorityEnable_QMERR )
      {
       if( first )
         {
          Putobj(out,"QMERR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"QMERR");
         }
      }

    if( value&HiPriorityEnable_MCU )
      {
       if( first )
         {
          Putobj(out,"MCU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MCU");
         }
      }

    if( value&HiPriorityEnable_EXP )
      {
       if( first )
         {
          Putobj(out,"EXP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EXP");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct INTBar<RW> */ 

template <class RW>
struct INTBar
 {
  RW rw;

  template <class ... TT>
  INTBar(TT && ... tt) : rw(tt...) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- Status

  Type_Status get_Status() { return Type_Status(rw.template get<uint32>(0x0)); }
 
  static Type_Status null_Status() { return Type_Status(0); }
 
  static Type_Status ones_Status() { return Type_Status(Type_Status::Type(-1)); }
 
  //--- Enable

  Type_Status get_Enable() { return Type_Status(rw.template get<uint32>(0x4)); }
 
  void set_Enable(Type_Status value) { rw.set(0x4,value.value); }
 
  Setter<Type_Status> to_Enable() { return Setter<Type_Status>(rw,0x4); }
 
  //--- Select

  Type_Status get_Select() { return Type_Status(rw.template get<uint32>(0x8)); }
 
  void set_Select(Type_Status value) { rw.set(0x8,value.value); }
 
  Setter<Type_Status> to_Select() { return Setter<Type_Status>(rw,0x8); }
 
  //--- IRQStatus

  Type_Status get_IRQStatus() { return Type_Status(rw.template get<uint32>(0xC)); }
 
  //--- FIQStatus

  Type_Status get_FIQStatus() { return Type_Status(rw.template get<uint32>(0x10)); }
 
  //--- Priority

  Type_Priority get_Priority() { return Type_Priority(rw.template get<uint32>(0x14)); }
 
  void set_Priority(Type_Priority value) { rw.set(0x14,value.value); }
 
  Setter<Type_Priority> to_Priority() { return Setter<Type_Priority>(rw,0x14); }
 
  static Type_Priority null_Priority() { return Type_Priority(0); }
 
  static Type_Priority ones_Priority() { return Type_Priority(Type_Priority::Type(-1)); }
 
  //--- IRQHiPriority

  Type_IRQHiPriority get_IRQHiPriority() { return Type_IRQHiPriority(rw.template get<uint32>(0x18)); }
 
  //--- FIQHiPriority

  Type_FIQHiPriority get_FIQHiPriority() { return Type_FIQHiPriority(rw.template get<uint32>(0x1C)); }
 
  //--- Status2

  Type_Status2 get_Status2() { return Type_Status2(rw.template get<uint32>(0x20)); }
 
  static Type_Status2 null_Status2() { return Type_Status2(0); }
 
  static Type_Status2 ones_Status2() { return Type_Status2(Type_Status2::Type(-1)); }
 
  //--- Enable2

  Type_Status2 get_Enable2() { return Type_Status2(rw.template get<uint32>(0x24)); }
 
  void set_Enable2(Type_Status2 value) { rw.set(0x24,value.value); }
 
  Setter<Type_Status2> to_Enable2() { return Setter<Type_Status2>(rw,0x24); }
 
  //--- Select2

  Type_Status2 get_Select2() { return Type_Status2(rw.template get<uint32>(0x28)); }
 
  void set_Select2(Type_Status2 value) { rw.set(0x28,value.value); }
 
  Setter<Type_Status2> to_Select2() { return Setter<Type_Status2>(rw,0x28); }
 
  //--- IRQStatus2

  Type_Status2 get_IRQStatus2() { return Type_Status2(rw.template get<uint32>(0x2C)); }
 
  //--- FIQStatus2

  Type_Status2 get_FIQStatus2() { return Type_Status2(rw.template get<uint32>(0x30)); }
 
  //--- HiPriorityEnable

  Type_HiPriorityEnable get_HiPriorityEnable() { return Type_HiPriorityEnable(rw.template get<uint32>(0x34)); }
 
  void set_HiPriorityEnable(Type_HiPriorityEnable value) { rw.set(0x34,value.value); }
 
  Setter<Type_HiPriorityEnable> to_HiPriorityEnable() { return Setter<Type_HiPriorityEnable>(rw,0x34); }
 
  static Type_HiPriorityEnable null_HiPriorityEnable() { return Type_HiPriorityEnable(0); }
 
  static Type_HiPriorityEnable ones_HiPriorityEnable() { return Type_HiPriorityEnable(Type_HiPriorityEnable::Type(-1)); }
 
 };
 
