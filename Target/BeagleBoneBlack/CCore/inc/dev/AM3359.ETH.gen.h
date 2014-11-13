/* AM3359.ETH.gen.h */ 

/* struct Type_SwitchControl */ 

enum Bits_SwitchControl : uint32
 {
  SwitchControl_FIFOLoopback = 0x00000001,
  SwitchControl_VLANAware    = 0x00000002,
  SwitchControl_Port2VLAN    = 0x00000004,
  SwitchControl_DLREnable    = 0x00000008
 };
 
inline Bits_SwitchControl operator | (Bits_SwitchControl a,Bits_SwitchControl b)
 { return Bits_SwitchControl(uint32(a)|uint32(b)); }
 
struct Type_SwitchControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchControl & setTo(Bar &bar) { bar.set_SwitchControl(*this); return *this; }
 

  template <class Bar>
  Type_SwitchControl & setTo(Bar &bar,uint32 ind) { bar.set_SwitchControl(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchControl & set(T to) { to(*this); return *this; }
 

  Type_SwitchControl & setbit(Bits_SwitchControl bits) { value|=Type(bits); return *this; }
 
  Type_SwitchControl & setbitIf(bool cond,Bits_SwitchControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchControl & clearbit(Bits_SwitchControl bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchControl & clearbitIf(bool cond,Bits_SwitchControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchControl bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchControl_FIFOLoopback )
      {
       if( first )
         {
          Putobj(out,"FIFOLoopback");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FIFOLoopback");
         }
      }

    if( value&SwitchControl_VLANAware )
      {
       if( first )
         {
          Putobj(out,"VLANAware");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLANAware");
         }
      }

    if( value&SwitchControl_Port2VLAN )
      {
       if( first )
         {
          Putobj(out,"Port2VLAN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2VLAN");
         }
      }

    if( value&SwitchControl_DLREnable )
      {
       if( first )
         {
          Putobj(out,"DLREnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DLREnable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchSoftReset */ 

enum Bits_SwitchSoftReset : uint32
 {
  SwitchSoftReset_Reset = 0x00000001
 };
 
inline Bits_SwitchSoftReset operator | (Bits_SwitchSoftReset a,Bits_SwitchSoftReset b)
 { return Bits_SwitchSoftReset(uint32(a)|uint32(b)); }
 
struct Type_SwitchSoftReset
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchSoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchSoftReset & setTo(Bar &bar) { bar.set_SwitchSoftReset(*this); return *this; }
 

  template <class Bar>
  Type_SwitchSoftReset & setTo(Bar &bar,uint32 ind) { bar.set_SwitchSoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchSoftReset & set(T to) { to(*this); return *this; }
 

  Type_SwitchSoftReset & setbit(Bits_SwitchSoftReset bits) { value|=Type(bits); return *this; }
 
  Type_SwitchSoftReset & setbitIf(bool cond,Bits_SwitchSoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchSoftReset & clearbit(Bits_SwitchSoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchSoftReset & clearbitIf(bool cond,Bits_SwitchSoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchSoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchSoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchSoftReset_Reset )
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
 
/* struct Type_SwitchStatPort */ 

enum Bits_SwitchStatPort : uint32
 {
  SwitchStatPort_Port0Enable = 0x00000001,
  SwitchStatPort_Port1Enable = 0x00000002,
  SwitchStatPort_Port2Enable = 0x00000004
 };
 
inline Bits_SwitchStatPort operator | (Bits_SwitchStatPort a,Bits_SwitchStatPort b)
 { return Bits_SwitchStatPort(uint32(a)|uint32(b)); }
 
struct Type_SwitchStatPort
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchStatPort(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchStatPort & setTo(Bar &bar) { bar.set_SwitchStatPort(*this); return *this; }
 

  template <class Bar>
  Type_SwitchStatPort & setTo(Bar &bar,uint32 ind) { bar.set_SwitchStatPort(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchStatPort & set(T to) { to(*this); return *this; }
 

  Type_SwitchStatPort & setbit(Bits_SwitchStatPort bits) { value|=Type(bits); return *this; }
 
  Type_SwitchStatPort & setbitIf(bool cond,Bits_SwitchStatPort bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchStatPort & clearbit(Bits_SwitchStatPort bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchStatPort & clearbitIf(bool cond,Bits_SwitchStatPort bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchStatPort bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchStatPort bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchStatPort_Port0Enable )
      {
       if( first )
         {
          Putobj(out,"Port0Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Enable");
         }
      }

    if( value&SwitchStatPort_Port1Enable )
      {
       if( first )
         {
          Putobj(out,"Port1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Enable");
         }
      }

    if( value&SwitchStatPort_Port2Enable )
      {
       if( first )
         {
          Putobj(out,"Port2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxPriType */ 

enum Bits_SwitchTxPriType : uint32
 {
  SwitchTxPriType_Port0Escalate  = 0x00000100,
  SwitchTxPriType_Port1Escalate  = 0x00000200,
  SwitchTxPriType_Port2Escalate  = 0x00000400,
  SwitchTxPriType_Port1Pri1Shape = 0x00010000,
  SwitchTxPriType_Port1Pri2Shape = 0x00020000,
  SwitchTxPriType_Port1Pri3Shape = 0x00040000,
  SwitchTxPriType_Port2Pri1Shape = 0x00080000,
  SwitchTxPriType_Port2Pri2Shape = 0x00100000,
  SwitchTxPriType_Port2Pri3Shape = 0x00200000
 };
 
inline Bits_SwitchTxPriType operator | (Bits_SwitchTxPriType a,Bits_SwitchTxPriType b)
 { return Bits_SwitchTxPriType(uint32(a)|uint32(b)); }
 
struct Type_SwitchTxPriType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchTxPriType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxPriType & setTo(Bar &bar) { bar.set_SwitchTxPriType(*this); return *this; }
 

  template <class Bar>
  Type_SwitchTxPriType & setTo(Bar &bar,uint32 ind) { bar.set_SwitchTxPriType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxPriType & set(T to) { to(*this); return *this; }
 

  Type_SwitchTxPriType & setbit(Bits_SwitchTxPriType bits) { value|=Type(bits); return *this; }
 
  Type_SwitchTxPriType & setbitIf(bool cond,Bits_SwitchTxPriType bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchTxPriType & clearbit(Bits_SwitchTxPriType bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchTxPriType & clearbitIf(bool cond,Bits_SwitchTxPriType bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchTxPriType bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchTxPriType bits) const { return (value&bits)==Type(bits); }
 

  Type get_EscalateCount() const
   {
    return (value>>0)&0x1F;
   }
 
  Type_SwitchTxPriType & set_EscalateCount(Type field)
   {
    value=((field&0x1F)<<0)|(value&0xFFFFFFE0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchTxPriType_Port0Escalate )
      {
       if( first )
         {
          Putobj(out,"Port0Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Escalate");
         }
      }

    if( value&SwitchTxPriType_Port1Escalate )
      {
       if( first )
         {
          Putobj(out,"Port1Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Escalate");
         }
      }

    if( value&SwitchTxPriType_Port2Escalate )
      {
       if( first )
         {
          Putobj(out,"Port2Escalate");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Escalate");
         }
      }

    if( value&SwitchTxPriType_Port1Pri1Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri1Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri1Shape");
         }
      }

    if( value&SwitchTxPriType_Port1Pri2Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri2Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri2Shape");
         }
      }

    if( value&SwitchTxPriType_Port1Pri3Shape )
      {
       if( first )
         {
          Putobj(out,"Port1Pri3Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Pri3Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri1Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri1Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri1Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri2Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri2Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri2Shape");
         }
      }

    if( value&SwitchTxPriType_Port2Pri3Shape )
      {
       if( first )
         {
          Putobj(out,"Port2Pri3Shape");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Pri3Shape");
         }
      }

    if( first )
      {
       Printf(out,"EscalateCount(#;)",get_EscalateCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"EscalateCount(#;)",get_EscalateCount());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchCmdIdle */ 

enum Bits_SwitchCmdIdle : uint32
 {
  SwitchCmdIdle_CmdIdle = 0x00000001
 };
 
inline Bits_SwitchCmdIdle operator | (Bits_SwitchCmdIdle a,Bits_SwitchCmdIdle b)
 { return Bits_SwitchCmdIdle(uint32(a)|uint32(b)); }
 
struct Type_SwitchCmdIdle
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchCmdIdle(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchCmdIdle & setTo(Bar &bar) { bar.set_SwitchCmdIdle(*this); return *this; }
 

  template <class Bar>
  Type_SwitchCmdIdle & setTo(Bar &bar,uint32 ind) { bar.set_SwitchCmdIdle(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchCmdIdle & set(T to) { to(*this); return *this; }
 

  Type_SwitchCmdIdle & setbit(Bits_SwitchCmdIdle bits) { value|=Type(bits); return *this; }
 
  Type_SwitchCmdIdle & setbitIf(bool cond,Bits_SwitchCmdIdle bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchCmdIdle & clearbit(Bits_SwitchCmdIdle bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchCmdIdle & clearbitIf(bool cond,Bits_SwitchCmdIdle bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchCmdIdle bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchCmdIdle bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchCmdIdle_CmdIdle )
      {
       if( first )
         {
          Putobj(out,"CmdIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdIdle");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchRate */ 

struct Type_SwitchRate
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchRate(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchRate & setTo(Bar &bar) { bar.set_SwitchRate(*this); return *this; }
 

  template <class Bar>
  Type_SwitchRate & setTo(Bar &bar,uint32 ind) { bar.set_SwitchRate(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchRate & set(T to) { to(*this); return *this; }
 

  Type get_Host() const
   {
    return (value>>0)&0xF;
   }
 
  Type_SwitchRate & set_Host(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_Sliver() const
   {
    return (value>>12)&0xF;
   }
 
  Type_SwitchRate & set_Sliver(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Host(#;)",get_Host());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Host(#;)",get_Host());
      }

    if( first )
      {
       Printf(out,"Sliver(#;)",get_Sliver());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Sliver(#;)",get_Sliver());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxShortGap */ 

struct Type_SwitchTxShortGap
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchTxShortGap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxShortGap & setTo(Bar &bar) { bar.set_SwitchTxShortGap(*this); return *this; }
 

  template <class Bar>
  Type_SwitchTxShortGap & setTo(Bar &bar,uint32 ind) { bar.set_SwitchTxShortGap(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxShortGap & set(T to) { to(*this); return *this; }
 

  Type get_Thresh() const
   {
    return (value>>0)&0x1F;
   }
 
  Type_SwitchTxShortGap & set_Thresh(Type field)
   {
    value=((field&0x1F)<<0)|(value&0xFFFFFFE0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Thresh(#;)",get_Thresh());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Thresh(#;)",get_Thresh());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTxStart */ 

struct Type_SwitchTxStart
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchTxStart(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTxStart & setTo(Bar &bar) { bar.set_SwitchTxStart(*this); return *this; }
 

  template <class Bar>
  Type_SwitchTxStart & setTo(Bar &bar,uint32 ind) { bar.set_SwitchTxStart(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTxStart & set(T to) { to(*this); return *this; }
 

  Type get_Len() const
   {
    return (value>>0)&0x7FF;
   }
 
  Type_SwitchTxStart & set_Len(Type field)
   {
    value=((field&0x7FF)<<0)|(value&0xFFFFF800);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Len(#;)",get_Len());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Len(#;)",get_Len());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchRxFlowControl */ 

enum Bits_SwitchRxFlowControl : uint32
 {
  SwitchRxFlowControl_Port0Enable = 0x00000001,
  SwitchRxFlowControl_Port1Enable = 0x00000002,
  SwitchRxFlowControl_Port2Enable = 0x00000004
 };
 
inline Bits_SwitchRxFlowControl operator | (Bits_SwitchRxFlowControl a,Bits_SwitchRxFlowControl b)
 { return Bits_SwitchRxFlowControl(uint32(a)|uint32(b)); }
 
struct Type_SwitchRxFlowControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchRxFlowControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchRxFlowControl & setTo(Bar &bar) { bar.set_SwitchRxFlowControl(*this); return *this; }
 

  template <class Bar>
  Type_SwitchRxFlowControl & setTo(Bar &bar,uint32 ind) { bar.set_SwitchRxFlowControl(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchRxFlowControl & set(T to) { to(*this); return *this; }
 

  Type_SwitchRxFlowControl & setbit(Bits_SwitchRxFlowControl bits) { value|=Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & setbitIf(bool cond,Bits_SwitchRxFlowControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & clearbit(Bits_SwitchRxFlowControl bits) { value&=~Type(bits); return *this; }
 
  Type_SwitchRxFlowControl & clearbitIf(bool cond,Bits_SwitchRxFlowControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SwitchRxFlowControl bits) const { return value&bits; }
 
  bool testbit(Bits_SwitchRxFlowControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SwitchRxFlowControl_Port0Enable )
      {
       if( first )
         {
          Putobj(out,"Port0Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port0Enable");
         }
      }

    if( value&SwitchRxFlowControl_Port1Enable )
      {
       if( first )
         {
          Putobj(out,"Port1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1Enable");
         }
      }

    if( value&SwitchRxFlowControl_Port2Enable )
      {
       if( first )
         {
          Putobj(out,"Port2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2Enable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchVLANLType */ 

struct Type_SwitchVLANLType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchVLANLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchVLANLType & setTo(Bar &bar) { bar.set_SwitchVLANLType(*this); return *this; }
 

  template <class Bar>
  Type_SwitchVLANLType & setTo(Bar &bar,uint32 ind) { bar.set_SwitchVLANLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchVLANLType & set(T to) { to(*this); return *this; }
 

  Type get_LType1() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_SwitchVLANLType & set_LType1(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  Type get_LType2() const
   {
    return (value>>16)&0xFFFF;
   }
 
  Type_SwitchVLANLType & set_LType2(Type field)
   {
    value=((field&0xFFFF)<<16)|(value&0xFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"LType1(#;)",get_LType1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType1(#;)",get_LType1());
      }

    if( first )
      {
       Printf(out,"LType2(#;)",get_LType2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType2(#;)",get_LType2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchTSVLANLType */ 

struct Type_SwitchTSVLANLType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchTSVLANLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchTSVLANLType & setTo(Bar &bar) { bar.set_SwitchTSVLANLType(*this); return *this; }
 

  template <class Bar>
  Type_SwitchTSVLANLType & setTo(Bar &bar,uint32 ind) { bar.set_SwitchTSVLANLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchTSVLANLType & set(T to) { to(*this); return *this; }
 

  Type get_LType1() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_SwitchTSVLANLType & set_LType1(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  Type get_LType2() const
   {
    return (value>>16)&0x3F;
   }
 
  Type_SwitchTSVLANLType & set_LType2(Type field)
   {
    value=((field&0x3F)<<16)|(value&0xFFC0FFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"LType1(#;)",get_LType1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType1(#;)",get_LType1());
      }

    if( first )
      {
       Printf(out,"LType2(#;)",get_LType2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType2(#;)",get_LType2());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SwitchDLRLType */ 

struct Type_SwitchDLRLType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SwitchDLRLType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SwitchDLRLType & setTo(Bar &bar) { bar.set_SwitchDLRLType(*this); return *this; }
 

  template <class Bar>
  Type_SwitchDLRLType & setTo(Bar &bar,uint32 ind) { bar.set_SwitchDLRLType(ind,*this); return *this; }
 

  template <class T>
  Type_SwitchDLRLType & set(T to) { to(*this); return *this; }
 

  Type get_LType() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_SwitchDLRLType & set_LType(Type field)
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
       Printf(out,"LType(#;)",get_LType());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LType(#;)",get_LType());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortControl */ 

enum Bits_PortControl : uint32
 {
  PortControl_RxTimeSyncEnable     = 0x00000001,
  PortControl_TxTimeSyncEnable     = 0x00000002,
  PortControl_LType1TimeSyncEnable = 0x00000004,
  PortControl_LType2TimeSyncEnable = 0x00000008,
  PortControl_AnnexDTimeSyncEnable = 0x00000010,
  PortControl_TTLTimeSyncEnable    = 0x00000100,
  PortControl_UDP129TimeSyncEnable = 0x00000200,
  PortControl_UDP130TimeSyncEnable = 0x00000400,
  PortControl_UDP131TimeSyncEnable = 0x00000800,
  PortControl_UDP132TimeSyncEnable = 0x00001000,
  PortControl_UDP319TimeSyncEnable = 0x00002000,
  PortControl_UDP320TimeSyncEnable = 0x00004000,
  PortControl_IPv4PriEnable        = 0x00010000,
  PortControl_VLAN_LType1Enable    = 0x00100000,
  PortControl_VLAN_LType2Enable    = 0x00200000,
  PortControl_VLAN_PassPri         = 0x01000000
 };
 
inline Bits_PortControl operator | (Bits_PortControl a,Bits_PortControl b)
 { return Bits_PortControl(uint32(a)|uint32(b)); }
 
struct Type_PortControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PortControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortControl & setTo(Bar &bar) { bar.set_PortControl(*this); return *this; }
 

  template <class Bar>
  Type_PortControl & setTo(Bar &bar,uint32 ind) { bar.set_PortControl(ind,*this); return *this; }
 

  template <class T>
  Type_PortControl & set(T to) { to(*this); return *this; }
 

  Type_PortControl & setbit(Bits_PortControl bits) { value|=Type(bits); return *this; }
 
  Type_PortControl & setbitIf(bool cond,Bits_PortControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PortControl & clearbit(Bits_PortControl bits) { value&=~Type(bits); return *this; }
 
  Type_PortControl & clearbitIf(bool cond,Bits_PortControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PortControl bits) const { return value&bits; }
 
  bool testbit(Bits_PortControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_DLRChan() const
   {
    return (value>>28)&0x7;
   }
 
  Type_PortControl & set_DLRChan(Type field)
   {
    value=((field&0x7)<<28)|(value&0x8FFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PortControl_RxTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"RxTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxTimeSyncEnable");
         }
      }

    if( value&PortControl_TxTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"TxTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxTimeSyncEnable");
         }
      }

    if( value&PortControl_LType1TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"LType1TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LType1TimeSyncEnable");
         }
      }

    if( value&PortControl_LType2TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"LType2TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LType2TimeSyncEnable");
         }
      }

    if( value&PortControl_AnnexDTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"AnnexDTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AnnexDTimeSyncEnable");
         }
      }

    if( value&PortControl_TTLTimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"TTLTimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TTLTimeSyncEnable");
         }
      }

    if( value&PortControl_UDP129TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP129TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP129TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP130TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP130TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP130TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP131TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP131TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP131TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP132TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP132TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP132TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP319TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP319TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP319TimeSyncEnable");
         }
      }

    if( value&PortControl_UDP320TimeSyncEnable )
      {
       if( first )
         {
          Putobj(out,"UDP320TimeSyncEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDP320TimeSyncEnable");
         }
      }

    if( value&PortControl_IPv4PriEnable )
      {
       if( first )
         {
          Putobj(out,"IPv4PriEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IPv4PriEnable");
         }
      }

    if( value&PortControl_VLAN_LType1Enable )
      {
       if( first )
         {
          Putobj(out,"VLAN_LType1Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_LType1Enable");
         }
      }

    if( value&PortControl_VLAN_LType2Enable )
      {
       if( first )
         {
          Putobj(out,"VLAN_LType2Enable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_LType2Enable");
         }
      }

    if( value&PortControl_VLAN_PassPri )
      {
       if( first )
         {
          Putobj(out,"VLAN_PassPri");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VLAN_PassPri");
         }
      }

    if( first )
      {
       Printf(out,"DLRChan(#;)",get_DLRChan());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DLRChan(#;)",get_DLRChan());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortFIFOLen */ 

enum Field_PortFIFOLen_RxLen : uint32
 {
  PortFIFOLen_RxLen_Default0 = 0x04,
  PortFIFOLen_RxLen_Default  = 0x03
 };
 
struct PrintField_PortFIFOLen_RxLen
 {
  Field_PortFIFOLen_RxLen field;

  explicit PrintField_PortFIFOLen_RxLen(Field_PortFIFOLen_RxLen field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x04 : Putobj(out,"Default0"); break;
       case 0x03 : Putobj(out,"Default"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortFIFOLen_RxLen GetTextDesc(Field_PortFIFOLen_RxLen field)
 {
  return PrintField_PortFIFOLen_RxLen(field);
 }
 
enum Field_PortFIFOLen_TxLen : uint32
 {
  PortFIFOLen_TxLen_Default0 = 0x10,
  PortFIFOLen_TxLen_Default  = 0x11
 };
 
struct PrintField_PortFIFOLen_TxLen
 {
  Field_PortFIFOLen_TxLen field;

  explicit PrintField_PortFIFOLen_TxLen(Field_PortFIFOLen_TxLen field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x10 : Putobj(out,"Default0"); break;
       case 0x11 : Putobj(out,"Default"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortFIFOLen_TxLen GetTextDesc(Field_PortFIFOLen_TxLen field)
 {
  return PrintField_PortFIFOLen_TxLen(field);
 }
 
struct Type_PortFIFOLen
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PortFIFOLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortFIFOLen & setTo(Bar &bar) { bar.set_PortFIFOLen(*this); return *this; }
 

  template <class Bar>
  Type_PortFIFOLen & setTo(Bar &bar,uint32 ind) { bar.set_PortFIFOLen(ind,*this); return *this; }
 

  template <class T>
  Type_PortFIFOLen & set(T to) { to(*this); return *this; }
 

  Field_PortFIFOLen_RxLen get_RxLen() const
   {
    return Field_PortFIFOLen_RxLen((value>>0)&0xF);
   }
 
  Type_PortFIFOLen & set_RxLen(Field_PortFIFOLen_RxLen field)
   {
    value=((Type(field)&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Field_PortFIFOLen_TxLen get_TxLen() const
   {
    return Field_PortFIFOLen_TxLen((value>>4)&0x1F);
   }
 
  Type_PortFIFOLen & set_TxLen(Field_PortFIFOLen_TxLen field)
   {
    value=((Type(field)&0x1F)<<4)|(value&0xFFFFFE0F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"RxLen(#;)",get_RxLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxLen(#;)",get_RxLen());
      }

    if( first )
      {
       Printf(out,"TxLen(#;)",get_TxLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxLen(#;)",get_TxLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortFIFOUse */ 

struct Type_PortFIFOUse
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PortFIFOUse(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortFIFOUse & setTo(Bar &bar) { bar.set_PortFIFOUse(*this); return *this; }
 

  template <class Bar>
  Type_PortFIFOUse & setTo(Bar &bar,uint32 ind) { bar.set_PortFIFOUse(ind,*this); return *this; }
 

  template <class T>
  Type_PortFIFOUse & set(T to) { to(*this); return *this; }
 

  Type get_RxUse() const
   {
    return (value>>0)&0xF;
   }
 
  Type_PortFIFOUse & set_RxUse(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_TxUse() const
   {
    return (value>>4)&0x1F;
   }
 
  Type_PortFIFOUse & set_TxUse(Type field)
   {
    value=((field&0x1F)<<4)|(value&0xFFFFFE0F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"RxUse(#;)",get_RxUse());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RxUse(#;)",get_RxUse());
      }

    if( first )
      {
       Printf(out,"TxUse(#;)",get_TxUse());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TxUse(#;)",get_TxUse());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PortTxFIFOControl */ 

enum Field_PortTxFIFOControl_Mode : uint32
 {
  PortTxFIFOControl_Mode_Normal  = 0x00,
  PortTxFIFOControl_Mode_DualMAC = 0x01,
  PortTxFIFOControl_Mode_RateLim = 0x02
 };
 
struct PrintField_PortTxFIFOControl_Mode
 {
  Field_PortTxFIFOControl_Mode field;

  explicit PrintField_PortTxFIFOControl_Mode(Field_PortTxFIFOControl_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Normal"); break;
       case 0x01 : Putobj(out,"DualMAC"); break;
       case 0x02 : Putobj(out,"RateLim"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_PortTxFIFOControl_Mode GetTextDesc(Field_PortTxFIFOControl_Mode field)
 {
  return PrintField_PortTxFIFOControl_Mode(field);
 }
 
struct Type_PortTxFIFOControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PortTxFIFOControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PortTxFIFOControl & setTo(Bar &bar) { bar.set_PortTxFIFOControl(*this); return *this; }
 

  template <class Bar>
  Type_PortTxFIFOControl & setTo(Bar &bar,uint32 ind) { bar.set_PortTxFIFOControl(ind,*this); return *this; }
 

  template <class T>
  Type_PortTxFIFOControl & set(T to) { to(*this); return *this; }
 

  Type get_WordLen() const
   {
    return (value>>0)&0x3FF;
   }
 
  Type_PortTxFIFOControl & set_WordLen(Type field)
   {
    value=((field&0x3FF)<<0)|(value&0xFFFFFC00);

    return *this;
   }
 

  Type get_Rem() const
   {
    return (value>>12)&0xF;
   }
 
  Type_PortTxFIFOControl & set_Rem(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Field_PortTxFIFOControl_Mode get_Mode() const
   {
    return Field_PortTxFIFOControl_Mode((value>>16)&0x3);
   }
 
  Type_PortTxFIFOControl & set_Mode(Field_PortTxFIFOControl_Mode field)
   {
    value=((Type(field)&0x3)<<16)|(value&0xFFFCFFFF);

    return *this;
   }
 

  Type get_Rate() const
   {
    return (value>>20)&0xF;
   }
 
  Type_PortTxFIFOControl & set_Rate(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  Type get_HostRem() const
   {
    return (value>>24)&0xF;
   }
 
  Type_PortTxFIFOControl & set_HostRem(Type field)
   {
    value=((field&0xF)<<24)|(value&0xF0FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

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

    if( first )
      {
       Printf(out,"Rem(#;)",get_Rem());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Rem(#;)",get_Rem());
      }

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
       Printf(out,"Rate(#;)",get_Rate());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Rate(#;)",get_Rate());
      }

    if( first )
      {
       Printf(out,"HostRem(#;)",get_HostRem());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HostRem(#;)",get_HostRem());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DescPtr */ 

typedef uint32 Type_DescPtr;

/* struct Type_SliverControl */ 

enum Bits_SliverControl : uint32
 {
  SliverControl_FullDuplex          = 0x00000001,
  SliverControl_Loopback            = 0x00000002,
  SliverControl_MTest               = 0x00000004,
  SliverControl_RxFlowControlEnable = 0x00000008,
  SliverControl_TxFlowControlEnable = 0x00000010,
  SliverControl_GMIIEnable          = 0x00000020,
  SliverControl_TxPaceEnable        = 0x00000040,
  SliverControl_GigMode             = 0x00000080,
  SliverControl_TxShortGapEnable    = 0x00000400,
  SliverControl_CmdIdle             = 0x00000800,
  SliverControl_CtrlA               = 0x00008000,
  SliverControl_CtrlB               = 0x00010000,
  SliverControl_ForceGig            = 0x00020000,
  SliverControl_ExtEnable           = 0x00040000,
  SliverControl_LimitTxShortGap     = 0x00200000,
  SliverControl_RxErrorPassEnable   = 0x00400000,
  SliverControl_RxShortPassEnable   = 0x00800000,
  SliverControl_RxCtrlPassEnable    = 0x01000000
 };
 
inline Bits_SliverControl operator | (Bits_SliverControl a,Bits_SliverControl b)
 { return Bits_SliverControl(uint32(a)|uint32(b)); }
 
struct Type_SliverControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverControl & setTo(Bar &bar) { bar.set_SliverControl(*this); return *this; }
 

  template <class Bar>
  Type_SliverControl & setTo(Bar &bar,uint32 ind) { bar.set_SliverControl(ind,*this); return *this; }
 

  template <class T>
  Type_SliverControl & set(T to) { to(*this); return *this; }
 

  Type_SliverControl & setbit(Bits_SliverControl bits) { value|=Type(bits); return *this; }
 
  Type_SliverControl & setbitIf(bool cond,Bits_SliverControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverControl & clearbit(Bits_SliverControl bits) { value&=~Type(bits); return *this; }
 
  Type_SliverControl & clearbitIf(bool cond,Bits_SliverControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverControl bits) const { return value&bits; }
 
  bool testbit(Bits_SliverControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverControl_FullDuplex )
      {
       if( first )
         {
          Putobj(out,"FullDuplex");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FullDuplex");
         }
      }

    if( value&SliverControl_Loopback )
      {
       if( first )
         {
          Putobj(out,"Loopback");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Loopback");
         }
      }

    if( value&SliverControl_MTest )
      {
       if( first )
         {
          Putobj(out,"MTest");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MTest");
         }
      }

    if( value&SliverControl_RxFlowControlEnable )
      {
       if( first )
         {
          Putobj(out,"RxFlowControlEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxFlowControlEnable");
         }
      }

    if( value&SliverControl_TxFlowControlEnable )
      {
       if( first )
         {
          Putobj(out,"TxFlowControlEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxFlowControlEnable");
         }
      }

    if( value&SliverControl_GMIIEnable )
      {
       if( first )
         {
          Putobj(out,"GMIIEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GMIIEnable");
         }
      }

    if( value&SliverControl_TxPaceEnable )
      {
       if( first )
         {
          Putobj(out,"TxPaceEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxPaceEnable");
         }
      }

    if( value&SliverControl_GigMode )
      {
       if( first )
         {
          Putobj(out,"GigMode");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GigMode");
         }
      }

    if( value&SliverControl_TxShortGapEnable )
      {
       if( first )
         {
          Putobj(out,"TxShortGapEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxShortGapEnable");
         }
      }

    if( value&SliverControl_CmdIdle )
      {
       if( first )
         {
          Putobj(out,"CmdIdle");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CmdIdle");
         }
      }

    if( value&SliverControl_CtrlA )
      {
       if( first )
         {
          Putobj(out,"CtrlA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CtrlA");
         }
      }

    if( value&SliverControl_CtrlB )
      {
       if( first )
         {
          Putobj(out,"CtrlB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CtrlB");
         }
      }

    if( value&SliverControl_ForceGig )
      {
       if( first )
         {
          Putobj(out,"ForceGig");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ForceGig");
         }
      }

    if( value&SliverControl_ExtEnable )
      {
       if( first )
         {
          Putobj(out,"ExtEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtEnable");
         }
      }

    if( value&SliverControl_LimitTxShortGap )
      {
       if( first )
         {
          Putobj(out,"LimitTxShortGap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LimitTxShortGap");
         }
      }

    if( value&SliverControl_RxErrorPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxErrorPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxErrorPassEnable");
         }
      }

    if( value&SliverControl_RxShortPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxShortPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxShortPassEnable");
         }
      }

    if( value&SliverControl_RxCtrlPassEnable )
      {
       if( first )
         {
          Putobj(out,"RxCtrlPassEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxCtrlPassEnable");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverStatus */ 

enum Bits_SliverStatus : uint32
 {
  SliverStatus_TxFlowControlActive = 0x00000001,
  SliverStatus_RxFlowControlActive = 0x00000002,
  SliverStatus_ExtFullDuplex       = 0x00000008,
  SliverStatus_ExtGig              = 0x00000010,
  SliverStatus_Idle                = 0x80000000
 };
 
inline Bits_SliverStatus operator | (Bits_SliverStatus a,Bits_SliverStatus b)
 { return Bits_SliverStatus(uint32(a)|uint32(b)); }
 
struct Type_SliverStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverStatus & setTo(Bar &bar) { bar.set_SliverStatus(*this); return *this; }
 

  template <class Bar>
  Type_SliverStatus & setTo(Bar &bar,uint32 ind) { bar.set_SliverStatus(ind,*this); return *this; }
 

  template <class T>
  Type_SliverStatus & set(T to) { to(*this); return *this; }
 

  Type_SliverStatus & setbit(Bits_SliverStatus bits) { value|=Type(bits); return *this; }
 
  Type_SliverStatus & setbitIf(bool cond,Bits_SliverStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverStatus & clearbit(Bits_SliverStatus bits) { value&=~Type(bits); return *this; }
 
  Type_SliverStatus & clearbitIf(bool cond,Bits_SliverStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverStatus bits) const { return value&bits; }
 
  bool testbit(Bits_SliverStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverStatus_TxFlowControlActive )
      {
       if( first )
         {
          Putobj(out,"TxFlowControlActive");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TxFlowControlActive");
         }
      }

    if( value&SliverStatus_RxFlowControlActive )
      {
       if( first )
         {
          Putobj(out,"RxFlowControlActive");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RxFlowControlActive");
         }
      }

    if( value&SliverStatus_ExtFullDuplex )
      {
       if( first )
         {
          Putobj(out,"ExtFullDuplex");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtFullDuplex");
         }
      }

    if( value&SliverStatus_ExtGig )
      {
       if( first )
         {
          Putobj(out,"ExtGig");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ExtGig");
         }
      }

    if( value&SliverStatus_Idle )
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

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverSoftReset */ 

enum Bits_SliverSoftReset : uint32
 {
  SliverSoftReset_Reset = 0x00000001
 };
 
inline Bits_SliverSoftReset operator | (Bits_SliverSoftReset a,Bits_SliverSoftReset b)
 { return Bits_SliverSoftReset(uint32(a)|uint32(b)); }
 
struct Type_SliverSoftReset
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverSoftReset(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverSoftReset & setTo(Bar &bar) { bar.set_SliverSoftReset(*this); return *this; }
 

  template <class Bar>
  Type_SliverSoftReset & setTo(Bar &bar,uint32 ind) { bar.set_SliverSoftReset(ind,*this); return *this; }
 

  template <class T>
  Type_SliverSoftReset & set(T to) { to(*this); return *this; }
 

  Type_SliverSoftReset & setbit(Bits_SliverSoftReset bits) { value|=Type(bits); return *this; }
 
  Type_SliverSoftReset & setbitIf(bool cond,Bits_SliverSoftReset bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverSoftReset & clearbit(Bits_SliverSoftReset bits) { value&=~Type(bits); return *this; }
 
  Type_SliverSoftReset & clearbitIf(bool cond,Bits_SliverSoftReset bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverSoftReset bits) const { return value&bits; }
 
  bool testbit(Bits_SliverSoftReset bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverSoftReset_Reset )
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
 
/* struct Type_SliverRxMaxLen */ 

struct Type_SliverRxMaxLen
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverRxMaxLen(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxMaxLen & setTo(Bar &bar) { bar.set_SliverRxMaxLen(*this); return *this; }
 

  template <class Bar>
  Type_SliverRxMaxLen & setTo(Bar &bar,uint32 ind) { bar.set_SliverRxMaxLen(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxMaxLen & set(T to) { to(*this); return *this; }
 

  Type get_Len() const
   {
    return (value>>0)&0x3FFF;
   }
 
  Type_SliverRxMaxLen & set_Len(Type field)
   {
    value=((field&0x3FFF)<<0)|(value&0xFFFFC000);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Len(#;)",get_Len());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Len(#;)",get_Len());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverBOFFTest */ 

struct Type_SliverBOFFTest
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverBOFFTest(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverBOFFTest & setTo(Bar &bar) { bar.set_SliverBOFFTest(*this); return *this; }
 

  template <class Bar>
  Type_SliverBOFFTest & setTo(Bar &bar,uint32 ind) { bar.set_SliverBOFFTest(ind,*this); return *this; }
 

  template <class T>
  Type_SliverBOFFTest & set(T to) { to(*this); return *this; }
 

  Type get_Backoff() const
   {
    return (value>>0)&0x3FF;
   }
 
  Type_SliverBOFFTest & set_Backoff(Type field)
   {
    value=((field&0x3FF)<<0)|(value&0xFFFFFC00);

    return *this;
   }
 

  Type get_CollisionCount() const
   {
    return (value>>12)&0xF;
   }
 
  Type_SliverBOFFTest & set_CollisionCount(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Type get_Random() const
   {
    return (value>>16)&0x3FF;
   }
 
  Type_SliverBOFFTest & set_Random(Type field)
   {
    value=((field&0x3FF)<<16)|(value&0xFC00FFFF);

    return *this;
   }
 

  Type get_Pace() const
   {
    return (value>>26)&0x1F;
   }
 
  Type_SliverBOFFTest & set_Pace(Type field)
   {
    value=((field&0x1F)<<26)|(value&0x83FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Backoff(#;)",get_Backoff());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Backoff(#;)",get_Backoff());
      }

    if( first )
      {
       Printf(out,"CollisionCount(#;)",get_CollisionCount());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CollisionCount(#;)",get_CollisionCount());
      }

    if( first )
      {
       Printf(out,"Random(#;)",get_Random());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Random(#;)",get_Random());
      }

    if( first )
      {
       Printf(out,"Pace(#;)",get_Pace());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pace(#;)",get_Pace());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverRxPause */ 

struct Type_SliverRxPause
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverRxPause(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxPause & setTo(Bar &bar) { bar.set_SliverRxPause(*this); return *this; }
 

  template <class Bar>
  Type_SliverRxPause & setTo(Bar &bar,uint32 ind) { bar.set_SliverRxPause(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxPause & set(T to) { to(*this); return *this; }
 

  Type get_Timer() const
   {
    return (value>>16)&0xFFFF;
   }
 
  Type_SliverRxPause & set_Timer(Type field)
   {
    value=((field&0xFFFF)<<16)|(value&0xFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Timer(#;)",get_Timer());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Timer(#;)",get_Timer());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverTxPause */ 

struct Type_SliverTxPause
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverTxPause(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverTxPause & setTo(Bar &bar) { bar.set_SliverTxPause(*this); return *this; }
 

  template <class Bar>
  Type_SliverTxPause & setTo(Bar &bar,uint32 ind) { bar.set_SliverTxPause(ind,*this); return *this; }
 

  template <class T>
  Type_SliverTxPause & set(T to) { to(*this); return *this; }
 

  Type get_Timer() const
   {
    return (value>>16)&0xFFFF;
   }
 
  Type_SliverTxPause & set_Timer(Type field)
   {
    value=((field&0xFFFF)<<16)|(value&0xFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Timer(#;)",get_Timer());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Timer(#;)",get_Timer());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverEMControl */ 

enum Bits_SliverEMControl : uint32
 {
  SliverEMControl_Free = 0x00000001,
  SliverEMControl_Soft = 0x00000002
 };
 
inline Bits_SliverEMControl operator | (Bits_SliverEMControl a,Bits_SliverEMControl b)
 { return Bits_SliverEMControl(uint32(a)|uint32(b)); }
 
struct Type_SliverEMControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverEMControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverEMControl & setTo(Bar &bar) { bar.set_SliverEMControl(*this); return *this; }
 

  template <class Bar>
  Type_SliverEMControl & setTo(Bar &bar,uint32 ind) { bar.set_SliverEMControl(ind,*this); return *this; }
 

  template <class T>
  Type_SliverEMControl & set(T to) { to(*this); return *this; }
 

  Type_SliverEMControl & setbit(Bits_SliverEMControl bits) { value|=Type(bits); return *this; }
 
  Type_SliverEMControl & setbitIf(bool cond,Bits_SliverEMControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SliverEMControl & clearbit(Bits_SliverEMControl bits) { value&=~Type(bits); return *this; }
 
  Type_SliverEMControl & clearbitIf(bool cond,Bits_SliverEMControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SliverEMControl bits) const { return value&bits; }
 
  bool testbit(Bits_SliverEMControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SliverEMControl_Free )
      {
       if( first )
         {
          Putobj(out,"Free");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Free");
         }
      }

    if( value&SliverEMControl_Soft )
      {
       if( first )
         {
          Putobj(out,"Soft");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Soft");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverRxPriMap */ 

struct Type_SliverRxPriMap
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverRxPriMap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverRxPriMap & setTo(Bar &bar) { bar.set_SliverRxPriMap(*this); return *this; }
 

  template <class Bar>
  Type_SliverRxPriMap & setTo(Bar &bar,uint32 ind) { bar.set_SliverRxPriMap(ind,*this); return *this; }
 

  template <class T>
  Type_SliverRxPriMap & set(T to) { to(*this); return *this; }
 

  Type get_Pri0() const
   {
    return (value>>0)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri0(Type field)
   {
    value=((field&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Type get_Pri1() const
   {
    return (value>>4)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri1(Type field)
   {
    value=((field&0x7)<<4)|(value&0xFFFFFF8F);

    return *this;
   }
 

  Type get_Pri2() const
   {
    return (value>>8)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri2(Type field)
   {
    value=((field&0x7)<<8)|(value&0xFFFFF8FF);

    return *this;
   }
 

  Type get_Pri3() const
   {
    return (value>>12)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri3(Type field)
   {
    value=((field&0x7)<<12)|(value&0xFFFF8FFF);

    return *this;
   }
 

  Type get_Pri4() const
   {
    return (value>>16)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri4(Type field)
   {
    value=((field&0x7)<<16)|(value&0xFFF8FFFF);

    return *this;
   }
 

  Type get_Pri5() const
   {
    return (value>>20)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri5(Type field)
   {
    value=((field&0x7)<<20)|(value&0xFF8FFFFF);

    return *this;
   }
 

  Type get_Pri6() const
   {
    return (value>>24)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri6(Type field)
   {
    value=((field&0x7)<<24)|(value&0xF8FFFFFF);

    return *this;
   }
 

  Type get_Pri7() const
   {
    return (value>>28)&0x7;
   }
 
  Type_SliverRxPriMap & set_Pri7(Type field)
   {
    value=((field&0x7)<<28)|(value&0x8FFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Pri0(#;)",get_Pri0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri0(#;)",get_Pri0());
      }

    if( first )
      {
       Printf(out,"Pri1(#;)",get_Pri1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri1(#;)",get_Pri1());
      }

    if( first )
      {
       Printf(out,"Pri2(#;)",get_Pri2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri2(#;)",get_Pri2());
      }

    if( first )
      {
       Printf(out,"Pri3(#;)",get_Pri3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri3(#;)",get_Pri3());
      }

    if( first )
      {
       Printf(out,"Pri4(#;)",get_Pri4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri4(#;)",get_Pri4());
      }

    if( first )
      {
       Printf(out,"Pri5(#;)",get_Pri5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri5(#;)",get_Pri5());
      }

    if( first )
      {
       Printf(out,"Pri6(#;)",get_Pri6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri6(#;)",get_Pri6());
      }

    if( first )
      {
       Printf(out,"Pri7(#;)",get_Pri7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Pri7(#;)",get_Pri7());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SliverTxGap */ 

struct Type_SliverTxGap
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SliverTxGap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SliverTxGap & setTo(Bar &bar) { bar.set_SliverTxGap(*this); return *this; }
 

  template <class Bar>
  Type_SliverTxGap & setTo(Bar &bar,uint32 ind) { bar.set_SliverTxGap(ind,*this); return *this; }
 

  template <class T>
  Type_SliverTxGap & set(T to) { to(*this); return *this; }
 

  Type get_Gap() const
   {
    return (value>>0)&0x1FF;
   }
 
  Type_SliverTxGap & set_Gap(Type field)
   {
    value=((field&0x1FF)<<0)|(value&0xFFFFFE00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Gap(#;)",get_Gap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Gap(#;)",get_Gap());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct SwitchBar<RW> */ 

template <class RW>
struct SwitchBar
 {
  RW rw;

  template <class ... TT>
  SwitchBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SwitchControl

  Type_SwitchControl get_SwitchControl() { return Type_SwitchControl(rw.template get<uint32>(0x4)); }
 
  void set_SwitchControl(Type_SwitchControl value) { rw.set(0x4,value.value); }
 
  Setter<Type_SwitchControl> to_SwitchControl() { return Setter<Type_SwitchControl>(rw,0x4); }
 
  static Type_SwitchControl null_SwitchControl() { return Type_SwitchControl(0); }
 
  static Type_SwitchControl ones_SwitchControl() { return Type_SwitchControl(Type_SwitchControl::Type(-1)); }
 
  //--- SwitchSoftReset

  Type_SwitchSoftReset get_SwitchSoftReset() { return Type_SwitchSoftReset(rw.template get<uint32>(0x8)); }
 
  void set_SwitchSoftReset(Type_SwitchSoftReset value) { rw.set(0x8,value.value); }
 
  Setter<Type_SwitchSoftReset> to_SwitchSoftReset() { return Setter<Type_SwitchSoftReset>(rw,0x8); }
 
  static Type_SwitchSoftReset null_SwitchSoftReset() { return Type_SwitchSoftReset(0); }
 
  static Type_SwitchSoftReset ones_SwitchSoftReset() { return Type_SwitchSoftReset(Type_SwitchSoftReset::Type(-1)); }
 
  //--- SwitchStatPort

  Type_SwitchStatPort get_SwitchStatPort() { return Type_SwitchStatPort(rw.template get<uint32>(0xC)); }
 
  void set_SwitchStatPort(Type_SwitchStatPort value) { rw.set(0xC,value.value); }
 
  Setter<Type_SwitchStatPort> to_SwitchStatPort() { return Setter<Type_SwitchStatPort>(rw,0xC); }
 
  static Type_SwitchStatPort null_SwitchStatPort() { return Type_SwitchStatPort(0); }
 
  static Type_SwitchStatPort ones_SwitchStatPort() { return Type_SwitchStatPort(Type_SwitchStatPort::Type(-1)); }
 
  //--- SwitchTxPriType

  Type_SwitchTxPriType get_SwitchTxPriType() { return Type_SwitchTxPriType(rw.template get<uint32>(0x10)); }
 
  void set_SwitchTxPriType(Type_SwitchTxPriType value) { rw.set(0x10,value.value); }
 
  Setter<Type_SwitchTxPriType> to_SwitchTxPriType() { return Setter<Type_SwitchTxPriType>(rw,0x10); }
 
  static Type_SwitchTxPriType null_SwitchTxPriType() { return Type_SwitchTxPriType(0); }
 
  static Type_SwitchTxPriType ones_SwitchTxPriType() { return Type_SwitchTxPriType(Type_SwitchTxPriType::Type(-1)); }
 
  //--- SwitchCmdIdle

  Type_SwitchCmdIdle get_SwitchCmdIdle() { return Type_SwitchCmdIdle(rw.template get<uint32>(0x14)); }
 
  void set_SwitchCmdIdle(Type_SwitchCmdIdle value) { rw.set(0x14,value.value); }
 
  Setter<Type_SwitchCmdIdle> to_SwitchCmdIdle() { return Setter<Type_SwitchCmdIdle>(rw,0x14); }
 
  static Type_SwitchCmdIdle null_SwitchCmdIdle() { return Type_SwitchCmdIdle(0); }
 
  static Type_SwitchCmdIdle ones_SwitchCmdIdle() { return Type_SwitchCmdIdle(Type_SwitchCmdIdle::Type(-1)); }
 
  //--- SwitchRate

  Type_SwitchRate get_SwitchRate() { return Type_SwitchRate(rw.template get<uint32>(0x18)); }
 
  void set_SwitchRate(Type_SwitchRate value) { rw.set(0x18,value.value); }
 
  Setter<Type_SwitchRate> to_SwitchRate() { return Setter<Type_SwitchRate>(rw,0x18); }
 
  static Type_SwitchRate null_SwitchRate() { return Type_SwitchRate(0); }
 
  static Type_SwitchRate ones_SwitchRate() { return Type_SwitchRate(Type_SwitchRate::Type(-1)); }
 
  //--- SwitchTxShortGap

  Type_SwitchTxShortGap get_SwitchTxShortGap() { return Type_SwitchTxShortGap(rw.template get<uint32>(0x1C)); }
 
  void set_SwitchTxShortGap(Type_SwitchTxShortGap value) { rw.set(0x1C,value.value); }
 
  Setter<Type_SwitchTxShortGap> to_SwitchTxShortGap() { return Setter<Type_SwitchTxShortGap>(rw,0x1C); }
 
  static Type_SwitchTxShortGap null_SwitchTxShortGap() { return Type_SwitchTxShortGap(0); }
 
  static Type_SwitchTxShortGap ones_SwitchTxShortGap() { return Type_SwitchTxShortGap(Type_SwitchTxShortGap::Type(-1)); }
 
  //--- SwitchTxStart

  Type_SwitchTxStart get_SwitchTxStart() { return Type_SwitchTxStart(rw.template get<uint32>(0x20)); }
 
  void set_SwitchTxStart(Type_SwitchTxStart value) { rw.set(0x20,value.value); }
 
  Setter<Type_SwitchTxStart> to_SwitchTxStart() { return Setter<Type_SwitchTxStart>(rw,0x20); }
 
  static Type_SwitchTxStart null_SwitchTxStart() { return Type_SwitchTxStart(0); }
 
  static Type_SwitchTxStart ones_SwitchTxStart() { return Type_SwitchTxStart(Type_SwitchTxStart::Type(-1)); }
 
  //--- SwitchRxFlowControl

  Type_SwitchRxFlowControl get_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(rw.template get<uint32>(0x24)); }
 
  void set_SwitchRxFlowControl(Type_SwitchRxFlowControl value) { rw.set(0x24,value.value); }
 
  Setter<Type_SwitchRxFlowControl> to_SwitchRxFlowControl() { return Setter<Type_SwitchRxFlowControl>(rw,0x24); }
 
  static Type_SwitchRxFlowControl null_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(0); }
 
  static Type_SwitchRxFlowControl ones_SwitchRxFlowControl() { return Type_SwitchRxFlowControl(Type_SwitchRxFlowControl::Type(-1)); }
 
  //--- SwitchVLANLType

  Type_SwitchVLANLType get_SwitchVLANLType() { return Type_SwitchVLANLType(rw.template get<uint32>(0x28)); }
 
  void set_SwitchVLANLType(Type_SwitchVLANLType value) { rw.set(0x28,value.value); }
 
  Setter<Type_SwitchVLANLType> to_SwitchVLANLType() { return Setter<Type_SwitchVLANLType>(rw,0x28); }
 
  static Type_SwitchVLANLType null_SwitchVLANLType() { return Type_SwitchVLANLType(0); }
 
  static Type_SwitchVLANLType ones_SwitchVLANLType() { return Type_SwitchVLANLType(Type_SwitchVLANLType::Type(-1)); }
 
  //--- SwitchTSVLANLType

  Type_SwitchTSVLANLType get_SwitchTSVLANLType() { return Type_SwitchTSVLANLType(rw.template get<uint32>(0x2C)); }
 
  void set_SwitchTSVLANLType(Type_SwitchTSVLANLType value) { rw.set(0x2C,value.value); }
 
  Setter<Type_SwitchTSVLANLType> to_SwitchTSVLANLType() { return Setter<Type_SwitchTSVLANLType>(rw,0x2C); }
 
  static Type_SwitchTSVLANLType null_SwitchTSVLANLType() { return Type_SwitchTSVLANLType(0); }
 
  static Type_SwitchTSVLANLType ones_SwitchTSVLANLType() { return Type_SwitchTSVLANLType(Type_SwitchTSVLANLType::Type(-1)); }
 
  //--- SwitchDLRLType

  Type_SwitchDLRLType get_SwitchDLRLType() { return Type_SwitchDLRLType(rw.template get<uint32>(0x30)); }
 
  void set_SwitchDLRLType(Type_SwitchDLRLType value) { rw.set(0x30,value.value); }
 
  Setter<Type_SwitchDLRLType> to_SwitchDLRLType() { return Setter<Type_SwitchDLRLType>(rw,0x30); }
 
  static Type_SwitchDLRLType null_SwitchDLRLType() { return Type_SwitchDLRLType(0); }
 
  static Type_SwitchDLRLType ones_SwitchDLRLType() { return Type_SwitchDLRLType(Type_SwitchDLRLType::Type(-1)); }
 
 };
 
/* struct Port0Bar<RW> */ 

template <class RW>
struct Port0Bar
 {
  RW rw;

  template <class ... TT>
  Port0Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xC)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
 };
 
/* struct Port1Bar<RW> */ 

template <class RW>
struct Port1Bar
 {
  RW rw;

  template <class ... TT>
  Port1Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xC)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
 };
 
/* struct Port2Bar<RW> */ 

template <class RW>
struct Port2Bar
 {
  RW rw;

  template <class ... TT>
  Port2Bar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PortControl

  Type_PortControl get_PortControl() { return Type_PortControl(rw.template get<uint32>(0x0)); }
 
  void set_PortControl(Type_PortControl value) { rw.set(0x0,value.value); }
 
  Setter<Type_PortControl> to_PortControl() { return Setter<Type_PortControl>(rw,0x0); }
 
  static Type_PortControl null_PortControl() { return Type_PortControl(0); }
 
  static Type_PortControl ones_PortControl() { return Type_PortControl(Type_PortControl::Type(-1)); }
 
  //--- PortFIFOLen

  Type_PortFIFOLen get_PortFIFOLen() { return Type_PortFIFOLen(rw.template get<uint32>(0x8)); }
 
  void set_PortFIFOLen(Type_PortFIFOLen value) { rw.set(0x8,value.value); }
 
  Setter<Type_PortFIFOLen> to_PortFIFOLen() { return Setter<Type_PortFIFOLen>(rw,0x8); }
 
  static Type_PortFIFOLen null_PortFIFOLen() { return Type_PortFIFOLen(0); }
 
  static Type_PortFIFOLen ones_PortFIFOLen() { return Type_PortFIFOLen(Type_PortFIFOLen::Type(-1)); }
 
  //--- PortFIFOUse

  Type_PortFIFOUse get_PortFIFOUse() { return Type_PortFIFOUse(rw.template get<uint32>(0xC)); }
 
  static Type_PortFIFOUse null_PortFIFOUse() { return Type_PortFIFOUse(0); }
 
  static Type_PortFIFOUse ones_PortFIFOUse() { return Type_PortFIFOUse(Type_PortFIFOUse::Type(-1)); }
 
  //--- PortTxFIFOControl

  Type_PortTxFIFOControl get_PortTxFIFOControl() { return Type_PortTxFIFOControl(rw.template get<uint32>(0x10)); }
 
  void set_PortTxFIFOControl(Type_PortTxFIFOControl value) { rw.set(0x10,value.value); }
 
  Setter<Type_PortTxFIFOControl> to_PortTxFIFOControl() { return Setter<Type_PortTxFIFOControl>(rw,0x10); }
 
  static Type_PortTxFIFOControl null_PortTxFIFOControl() { return Type_PortTxFIFOControl(0); }
 
  static Type_PortTxFIFOControl ones_PortTxFIFOControl() { return Type_PortTxFIFOControl(Type_PortTxFIFOControl::Type(-1)); }
 
 };
 
/* struct DMABar<RW> */ 

template <class RW>
struct DMABar
 {
  RW rw;

  template <class ... TT>
  DMABar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
/* struct StatBar<RW> */ 

template <class RW>
struct StatBar
 {
  RW rw;

  template <class ... TT>
  StatBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
/* struct DescBar<RW> */ 

template <class RW>
struct DescBar
 {
  RW rw;

  template <class ... TT>
  DescBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- HeadTx

  Type_DescPtr get_HeadTx(uint32 ind) { return Type_DescPtr(rw.template get<uint32>(0x0 +ind*4)); }
 
  void set_HeadTx(uint32 ind,Type_DescPtr value) { rw.set(0x0 +ind*4,value); }
 
  void set_HeadTx_null(uint32 ind) { rw.set(0x0 +ind*4,Type_DescPtr(0)); }
 
  void set_HeadTx_ones(uint32 ind) { rw.set(0x0 +ind*4,Type_DescPtr(-1)); }
 
  //--- HeadRx

  Type_DescPtr get_HeadRx(uint32 ind) { return Type_DescPtr(rw.template get<uint32>(0x20 +ind*4)); }
 
  void set_HeadRx(uint32 ind,Type_DescPtr value) { rw.set(0x20 +ind*4,value); }
 
  void set_HeadRx_null(uint32 ind) { rw.set(0x20 +ind*4,Type_DescPtr(0)); }
 
  void set_HeadRx_ones(uint32 ind) { rw.set(0x20 +ind*4,Type_DescPtr(-1)); }
 
  //--- CompleteTx

  Type_DescPtr get_CompleteTx(uint32 ind) { return Type_DescPtr(rw.template get<uint32>(0x40 +ind*4)); }
 
  void set_CompleteTx(uint32 ind,Type_DescPtr value) { rw.set(0x40 +ind*4,value); }
 
  void set_CompleteTx_null(uint32 ind) { rw.set(0x40 +ind*4,Type_DescPtr(0)); }
 
  void set_CompleteTx_ones(uint32 ind) { rw.set(0x40 +ind*4,Type_DescPtr(-1)); }
 
  //--- CompleteRx

  Type_DescPtr get_CompleteRx(uint32 ind) { return Type_DescPtr(rw.template get<uint32>(0x60 +ind*4)); }
 
  void set_CompleteRx(uint32 ind,Type_DescPtr value) { rw.set(0x60 +ind*4,value); }
 
  void set_CompleteRx_null(uint32 ind) { rw.set(0x60 +ind*4,Type_DescPtr(0)); }
 
  void set_CompleteRx_ones(uint32 ind) { rw.set(0x60 +ind*4,Type_DescPtr(-1)); }
 
  //--- DescPtr

 };
 
/* struct TimeSyncBar<RW> */ 

template <class RW>
struct TimeSyncBar
 {
  RW rw;

  template <class ... TT>
  TimeSyncBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
/* struct ALEBar<RW> */ 

template <class RW>
struct ALEBar
 {
  RW rw;

  template <class ... TT>
  ALEBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
/* struct SliverBar<RW> */ 

template <class RW>
struct SliverBar
 {
  RW rw;

  template <class ... TT>
  SliverBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- SliverControl

  Type_SliverControl get_SliverControl() { return Type_SliverControl(rw.template get<uint32>(0x4)); }
 
  void set_SliverControl(Type_SliverControl value) { rw.set(0x4,value.value); }
 
  Setter<Type_SliverControl> to_SliverControl() { return Setter<Type_SliverControl>(rw,0x4); }
 
  static Type_SliverControl null_SliverControl() { return Type_SliverControl(0); }
 
  static Type_SliverControl ones_SliverControl() { return Type_SliverControl(Type_SliverControl::Type(-1)); }
 
  //--- SliverStatus

  Type_SliverStatus get_SliverStatus() { return Type_SliverStatus(rw.template get<uint32>(0x8)); }
 
  static Type_SliverStatus null_SliverStatus() { return Type_SliverStatus(0); }
 
  static Type_SliverStatus ones_SliverStatus() { return Type_SliverStatus(Type_SliverStatus::Type(-1)); }
 
  //--- SliverSoftReset

  Type_SliverSoftReset get_SliverSoftReset() { return Type_SliverSoftReset(rw.template get<uint32>(0xC)); }
 
  void set_SliverSoftReset(Type_SliverSoftReset value) { rw.set(0xC,value.value); }
 
  Setter<Type_SliverSoftReset> to_SliverSoftReset() { return Setter<Type_SliverSoftReset>(rw,0xC); }
 
  static Type_SliverSoftReset null_SliverSoftReset() { return Type_SliverSoftReset(0); }
 
  static Type_SliverSoftReset ones_SliverSoftReset() { return Type_SliverSoftReset(Type_SliverSoftReset::Type(-1)); }
 
  //--- SliverRxMaxLen

  Type_SliverRxMaxLen get_SliverRxMaxLen() { return Type_SliverRxMaxLen(rw.template get<uint32>(0x10)); }
 
  void set_SliverRxMaxLen(Type_SliverRxMaxLen value) { rw.set(0x10,value.value); }
 
  Setter<Type_SliverRxMaxLen> to_SliverRxMaxLen() { return Setter<Type_SliverRxMaxLen>(rw,0x10); }
 
  static Type_SliverRxMaxLen null_SliverRxMaxLen() { return Type_SliverRxMaxLen(0); }
 
  static Type_SliverRxMaxLen ones_SliverRxMaxLen() { return Type_SliverRxMaxLen(Type_SliverRxMaxLen::Type(-1)); }
 
  //--- SliverBOFFTest

  Type_SliverBOFFTest get_SliverBOFFTest() { return Type_SliverBOFFTest(rw.template get<uint32>(0x14)); }
 
  void set_SliverBOFFTest(Type_SliverBOFFTest value) { rw.set(0x14,value.value); }
 
  Setter<Type_SliverBOFFTest> to_SliverBOFFTest() { return Setter<Type_SliverBOFFTest>(rw,0x14); }
 
  static Type_SliverBOFFTest null_SliverBOFFTest() { return Type_SliverBOFFTest(0); }
 
  static Type_SliverBOFFTest ones_SliverBOFFTest() { return Type_SliverBOFFTest(Type_SliverBOFFTest::Type(-1)); }
 
  //--- SliverRxPause

  Type_SliverRxPause get_SliverRxPause() { return Type_SliverRxPause(rw.template get<uint32>(0x18)); }
 
  void set_SliverRxPause(Type_SliverRxPause value) { rw.set(0x18,value.value); }
 
  Setter<Type_SliverRxPause> to_SliverRxPause() { return Setter<Type_SliverRxPause>(rw,0x18); }
 
  static Type_SliverRxPause null_SliverRxPause() { return Type_SliverRxPause(0); }
 
  static Type_SliverRxPause ones_SliverRxPause() { return Type_SliverRxPause(Type_SliverRxPause::Type(-1)); }
 
  //--- SliverTxPause

  Type_SliverTxPause get_SliverTxPause() { return Type_SliverTxPause(rw.template get<uint32>(0x1C)); }
 
  void set_SliverTxPause(Type_SliverTxPause value) { rw.set(0x1C,value.value); }
 
  Setter<Type_SliverTxPause> to_SliverTxPause() { return Setter<Type_SliverTxPause>(rw,0x1C); }
 
  static Type_SliverTxPause null_SliverTxPause() { return Type_SliverTxPause(0); }
 
  static Type_SliverTxPause ones_SliverTxPause() { return Type_SliverTxPause(Type_SliverTxPause::Type(-1)); }
 
  //--- SliverEMControl

  Type_SliverEMControl get_SliverEMControl() { return Type_SliverEMControl(rw.template get<uint32>(0x20)); }
 
  void set_SliverEMControl(Type_SliverEMControl value) { rw.set(0x20,value.value); }
 
  Setter<Type_SliverEMControl> to_SliverEMControl() { return Setter<Type_SliverEMControl>(rw,0x20); }
 
  static Type_SliverEMControl null_SliverEMControl() { return Type_SliverEMControl(0); }
 
  static Type_SliverEMControl ones_SliverEMControl() { return Type_SliverEMControl(Type_SliverEMControl::Type(-1)); }
 
  //--- SliverRxPriMap

  Type_SliverRxPriMap get_SliverRxPriMap() { return Type_SliverRxPriMap(rw.template get<uint32>(0x24)); }
 
  void set_SliverRxPriMap(Type_SliverRxPriMap value) { rw.set(0x24,value.value); }
 
  Setter<Type_SliverRxPriMap> to_SliverRxPriMap() { return Setter<Type_SliverRxPriMap>(rw,0x24); }
 
  static Type_SliverRxPriMap null_SliverRxPriMap() { return Type_SliverRxPriMap(0); }
 
  static Type_SliverRxPriMap ones_SliverRxPriMap() { return Type_SliverRxPriMap(Type_SliverRxPriMap::Type(-1)); }
 
  //--- SliverTxGap

  Type_SliverTxGap get_SliverTxGap() { return Type_SliverTxGap(rw.template get<uint32>(0x28)); }
 
  void set_SliverTxGap(Type_SliverTxGap value) { rw.set(0x28,value.value); }
 
  Setter<Type_SliverTxGap> to_SliverTxGap() { return Setter<Type_SliverTxGap>(rw,0x28); }
 
  static Type_SliverTxGap null_SliverTxGap() { return Type_SliverTxGap(0); }
 
  static Type_SliverTxGap ones_SliverTxGap() { return Type_SliverTxGap(Type_SliverTxGap::Type(-1)); }
 
 };
 
/* struct WRBar<RW> */ 

template <class RW>
struct WRBar
 {
  RW rw;

  template <class ... TT>
  WRBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
/* struct MDIOBar<RW> */ 

template <class RW>
struct MDIOBar
 {
  RW rw;

  template <class ... TT>
  MDIOBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

 };
 
