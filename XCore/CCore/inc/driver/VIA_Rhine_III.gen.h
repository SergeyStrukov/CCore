/* VIA_Rhine_III.gen.h */ 

/* struct Type_PCIMode2 */ 

enum Bits_PCIMode2 : uint8
 {
  PCIMode2_T10     = 0x02,
  PCIMode2_MRDPL   = 0x08,
  PCIMode2_DISABT  = 0x40,
  PCIMode2_PCEROPT = 0x80
 };
 
inline Bits_PCIMode2 operator | (Bits_PCIMode2 a,Bits_PCIMode2 b)
 { return Bits_PCIMode2(uint8(a)|uint8(b)); }
 
struct Type_PCIMode2
 {
  typedef uint8 Type;

  Type value;


  explicit Type_PCIMode2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PCIMode2 & setTo(Bar &bar) { bar.set_PCIMode2(*this); return *this; }
 

  template <class Bar>
  Type_PCIMode2 & setTo(Bar &bar,uint32 ind) { bar.set_PCIMode2(ind,*this); return *this; }
 

  template <class T>
  Type_PCIMode2 & set(T to) { to(*this); return *this; }
 

  Type_PCIMode2 & setbit(Bits_PCIMode2 bits) { value|=Type(bits); return *this; }
 
  Type_PCIMode2 & setbitIf(bool cond,Bits_PCIMode2 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PCIMode2 & clearbit(Bits_PCIMode2 bits) { value&=~Type(bits); return *this; }
 
  Type_PCIMode2 & clearbitIf(bool cond,Bits_PCIMode2 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PCIMode2 bits) const { return value&bits; }
 
  bool testbit(Bits_PCIMode2 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PCIMode2_T10 )
      {
       if( first )
         {
          Putobj(out,"T10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T10");
         }
      }

    if( value&PCIMode2_MRDPL )
      {
       if( first )
         {
          Putobj(out,"MRDPL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MRDPL");
         }
      }

    if( value&PCIMode2_DISABT )
      {
       if( first )
         {
          Putobj(out,"DISABT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DISABT");
         }
      }

    if( value&PCIMode2_PCEROPT )
      {
       if( first )
         {
          Putobj(out,"PCEROPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PCEROPT");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_PCIMode3 */ 

enum Bits_PCIMode3 : uint8
 {
  PCIMode3_MIION   = 0x04,
  PCIMode3_MIIDMY  = 0x08,
  PCIMode3_DLTSEL  = 0x10,
  PCIMode3_BACKOPT = 0x20,
  PCIMode3_TRACEN  = 0x40,
  PCIMode3_XONOPT  = 0x80
 };
 
inline Bits_PCIMode3 operator | (Bits_PCIMode3 a,Bits_PCIMode3 b)
 { return Bits_PCIMode3(uint8(a)|uint8(b)); }
 
struct Type_PCIMode3
 {
  typedef uint8 Type;

  Type value;


  explicit Type_PCIMode3(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PCIMode3 & setTo(Bar &bar) { bar.set_PCIMode3(*this); return *this; }
 

  template <class Bar>
  Type_PCIMode3 & setTo(Bar &bar,uint32 ind) { bar.set_PCIMode3(ind,*this); return *this; }
 

  template <class T>
  Type_PCIMode3 & set(T to) { to(*this); return *this; }
 

  Type_PCIMode3 & setbit(Bits_PCIMode3 bits) { value|=Type(bits); return *this; }
 
  Type_PCIMode3 & setbitIf(bool cond,Bits_PCIMode3 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PCIMode3 & clearbit(Bits_PCIMode3 bits) { value&=~Type(bits); return *this; }
 
  Type_PCIMode3 & clearbitIf(bool cond,Bits_PCIMode3 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PCIMode3 bits) const { return value&bits; }
 
  bool testbit(Bits_PCIMode3 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PCIMode3_MIION )
      {
       if( first )
         {
          Putobj(out,"MIION");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MIION");
         }
      }

    if( value&PCIMode3_MIIDMY )
      {
       if( first )
         {
          Putobj(out,"MIIDMY");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MIIDMY");
         }
      }

    if( value&PCIMode3_DLTSEL )
      {
       if( first )
         {
          Putobj(out,"DLTSEL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DLTSEL");
         }
      }

    if( value&PCIMode3_BACKOPT )
      {
       if( first )
         {
          Putobj(out,"BACKOPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BACKOPT");
         }
      }

    if( value&PCIMode3_TRACEN )
      {
       if( first )
         {
          Putobj(out,"TRACEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TRACEN");
         }
      }

    if( value&PCIMode3_XONOPT )
      {
       if( first )
         {
          Putobj(out,"XONOPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XONOPT");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIIBMCR */ 

enum Bits_MIIBMCR : uint16
 {
  MIIBMCR_FDX    = 0x0100,
  MIIBMCR_REAUTO = 0x0200,
  MIIBMCR_ISO    = 0x0400,
  MIIBMCR_PD     = 0x0800,
  MIIBMCR_AUTO   = 0x1000,
  MIIBMCR_SPEED  = 0x2000,
  MIIBMCR_LBK    = 0x4000,
  MIIBMCR_RESET  = 0x8000
 };
 
inline Bits_MIIBMCR operator | (Bits_MIIBMCR a,Bits_MIIBMCR b)
 { return Bits_MIIBMCR(uint16(a)|uint16(b)); }
 
struct Type_MIIBMCR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MIIBMCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIBMCR & setTo(Bar &bar) { bar.set_MIIBMCR(*this); return *this; }
 

  template <class Bar>
  Type_MIIBMCR & setTo(Bar &bar,uint32 ind) { bar.set_MIIBMCR(ind,*this); return *this; }
 

  template <class T>
  Type_MIIBMCR & set(T to) { to(*this); return *this; }
 

  Type_MIIBMCR & setbit(Bits_MIIBMCR bits) { value|=Type(bits); return *this; }
 
  Type_MIIBMCR & setbitIf(bool cond,Bits_MIIBMCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIBMCR & clearbit(Bits_MIIBMCR bits) { value&=~Type(bits); return *this; }
 
  Type_MIIBMCR & clearbitIf(bool cond,Bits_MIIBMCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIBMCR bits) const { return value&bits; }
 
  bool testbit(Bits_MIIBMCR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIBMCR_FDX )
      {
       if( first )
         {
          Putobj(out,"FDX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDX");
         }
      }

    if( value&MIIBMCR_REAUTO )
      {
       if( first )
         {
          Putobj(out,"REAUTO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"REAUTO");
         }
      }

    if( value&MIIBMCR_ISO )
      {
       if( first )
         {
          Putobj(out,"ISO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ISO");
         }
      }

    if( value&MIIBMCR_PD )
      {
       if( first )
         {
          Putobj(out,"PD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PD");
         }
      }

    if( value&MIIBMCR_AUTO )
      {
       if( first )
         {
          Putobj(out,"AUTO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AUTO");
         }
      }

    if( value&MIIBMCR_SPEED )
      {
       if( first )
         {
          Putobj(out,"SPEED");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SPEED");
         }
      }

    if( value&MIIBMCR_LBK )
      {
       if( first )
         {
          Putobj(out,"LBK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LBK");
         }
      }

    if( value&MIIBMCR_RESET )
      {
       if( first )
         {
          Putobj(out,"RESET");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RESET");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIIBMSR */ 

enum Bits_MIIBMSR : uint16
 {
  MIIBMSR_LNK    = 0x0004,
  MIIBMSR_AUTOCM = 0x0020
 };
 
inline Bits_MIIBMSR operator | (Bits_MIIBMSR a,Bits_MIIBMSR b)
 { return Bits_MIIBMSR(uint16(a)|uint16(b)); }
 
struct Type_MIIBMSR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MIIBMSR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIBMSR & setTo(Bar &bar) { bar.set_MIIBMSR(*this); return *this; }
 

  template <class Bar>
  Type_MIIBMSR & setTo(Bar &bar,uint32 ind) { bar.set_MIIBMSR(ind,*this); return *this; }
 

  template <class T>
  Type_MIIBMSR & set(T to) { to(*this); return *this; }
 

  Type_MIIBMSR & setbit(Bits_MIIBMSR bits) { value|=Type(bits); return *this; }
 
  Type_MIIBMSR & setbitIf(bool cond,Bits_MIIBMSR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIBMSR & clearbit(Bits_MIIBMSR bits) { value&=~Type(bits); return *this; }
 
  Type_MIIBMSR & clearbitIf(bool cond,Bits_MIIBMSR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIBMSR bits) const { return value&bits; }
 
  bool testbit(Bits_MIIBMSR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIBMSR_LNK )
      {
       if( first )
         {
          Putobj(out,"LNK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LNK");
         }
      }

    if( value&MIIBMSR_AUTOCM )
      {
       if( first )
         {
          Putobj(out,"AUTOCM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AUTOCM");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIIANAR */ 

enum Bits_MIIANAR : uint16
 {
  MIIANAR_T10    = 0x0020,
  MIIANAR_T10FD  = 0x0040,
  MIIANAR_TX     = 0x0080,
  MIIANAR_TXFD   = 0x0100,
  MIIANAR_T4     = 0x0200,
  MIIANAR_PAUSE  = 0x0400,
  MIIANAR_ASMDIR = 0x0800
 };
 
inline Bits_MIIANAR operator | (Bits_MIIANAR a,Bits_MIIANAR b)
 { return Bits_MIIANAR(uint16(a)|uint16(b)); }
 
struct Type_MIIANAR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MIIANAR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIANAR & setTo(Bar &bar) { bar.set_MIIANAR(*this); return *this; }
 

  template <class Bar>
  Type_MIIANAR & setTo(Bar &bar,uint32 ind) { bar.set_MIIANAR(ind,*this); return *this; }
 

  template <class T>
  Type_MIIANAR & set(T to) { to(*this); return *this; }
 

  Type_MIIANAR & setbit(Bits_MIIANAR bits) { value|=Type(bits); return *this; }
 
  Type_MIIANAR & setbitIf(bool cond,Bits_MIIANAR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIANAR & clearbit(Bits_MIIANAR bits) { value&=~Type(bits); return *this; }
 
  Type_MIIANAR & clearbitIf(bool cond,Bits_MIIANAR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIANAR bits) const { return value&bits; }
 
  bool testbit(Bits_MIIANAR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIANAR_T10 )
      {
       if( first )
         {
          Putobj(out,"T10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T10");
         }
      }

    if( value&MIIANAR_T10FD )
      {
       if( first )
         {
          Putobj(out,"T10FD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T10FD");
         }
      }

    if( value&MIIANAR_TX )
      {
       if( first )
         {
          Putobj(out,"TX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TX");
         }
      }

    if( value&MIIANAR_TXFD )
      {
       if( first )
         {
          Putobj(out,"TXFD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXFD");
         }
      }

    if( value&MIIANAR_T4 )
      {
       if( first )
         {
          Putobj(out,"T4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T4");
         }
      }

    if( value&MIIANAR_PAUSE )
      {
       if( first )
         {
          Putobj(out,"PAUSE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PAUSE");
         }
      }

    if( value&MIIANAR_ASMDIR )
      {
       if( first )
         {
          Putobj(out,"ASMDIR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ASMDIR");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MIIPhyID1 */ 

typedef uint16 Type_MIIPhyID1;

/* type Type_MIIPhyID2 */ 

typedef uint16 Type_MIIPhyID2;

/* struct Type_MIIANLPAR */ 

enum Bits_MIIANLPAR : uint16
 {
  MIIANLPAR_T10    = 0x0020,
  MIIANLPAR_T10FD  = 0x0040,
  MIIANLPAR_TX     = 0x0080,
  MIIANLPAR_TXFD   = 0x0100,
  MIIANLPAR_T4     = 0x0200,
  MIIANLPAR_PAUSE  = 0x0400,
  MIIANLPAR_ASMDIR = 0x0800
 };
 
inline Bits_MIIANLPAR operator | (Bits_MIIANLPAR a,Bits_MIIANLPAR b)
 { return Bits_MIIANLPAR(uint16(a)|uint16(b)); }
 
struct Type_MIIANLPAR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MIIANLPAR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIANLPAR & setTo(Bar &bar) { bar.set_MIIANLPAR(*this); return *this; }
 

  template <class Bar>
  Type_MIIANLPAR & setTo(Bar &bar,uint32 ind) { bar.set_MIIANLPAR(ind,*this); return *this; }
 

  template <class T>
  Type_MIIANLPAR & set(T to) { to(*this); return *this; }
 

  Type_MIIANLPAR & setbit(Bits_MIIANLPAR bits) { value|=Type(bits); return *this; }
 
  Type_MIIANLPAR & setbitIf(bool cond,Bits_MIIANLPAR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIANLPAR & clearbit(Bits_MIIANLPAR bits) { value&=~Type(bits); return *this; }
 
  Type_MIIANLPAR & clearbitIf(bool cond,Bits_MIIANLPAR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIANLPAR bits) const { return value&bits; }
 
  bool testbit(Bits_MIIANLPAR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIANLPAR_T10 )
      {
       if( first )
         {
          Putobj(out,"T10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T10");
         }
      }

    if( value&MIIANLPAR_T10FD )
      {
       if( first )
         {
          Putobj(out,"T10FD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T10FD");
         }
      }

    if( value&MIIANLPAR_TX )
      {
       if( first )
         {
          Putobj(out,"TX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TX");
         }
      }

    if( value&MIIANLPAR_TXFD )
      {
       if( first )
         {
          Putobj(out,"TXFD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXFD");
         }
      }

    if( value&MIIANLPAR_T4 )
      {
       if( first )
         {
          Putobj(out,"T4");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T4");
         }
      }

    if( value&MIIANLPAR_PAUSE )
      {
       if( first )
         {
          Putobj(out,"PAUSE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PAUSE");
         }
      }

    if( value&MIIANLPAR_ASMDIR )
      {
       if( first )
         {
          Putobj(out,"ASMDIR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ASMDIR");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIIModCfg */ 

enum Bits_MIIModCfg : uint16
 {
  MIIModCfg_Bit0 = 0x0001
 };
 
inline Bits_MIIModCfg operator | (Bits_MIIModCfg a,Bits_MIIModCfg b)
 { return Bits_MIIModCfg(uint16(a)|uint16(b)); }
 
struct Type_MIIModCfg
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MIIModCfg(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIModCfg & setTo(Bar &bar) { bar.set_MIIModCfg(*this); return *this; }
 

  template <class Bar>
  Type_MIIModCfg & setTo(Bar &bar,uint32 ind) { bar.set_MIIModCfg(ind,*this); return *this; }
 

  template <class T>
  Type_MIIModCfg & set(T to) { to(*this); return *this; }
 

  Type_MIIModCfg & setbit(Bits_MIIModCfg bits) { value|=Type(bits); return *this; }
 
  Type_MIIModCfg & setbitIf(bool cond,Bits_MIIModCfg bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIModCfg & clearbit(Bits_MIIModCfg bits) { value&=~Type(bits); return *this; }
 
  Type_MIIModCfg & clearbitIf(bool cond,Bits_MIIModCfg bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIModCfg bits) const { return value&bits; }
 
  bool testbit(Bits_MIIModCfg bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIModCfg_Bit0 )
      {
       if( first )
         {
          Putobj(out,"Bit0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Bit0");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MAC */ 

typedef uint8 Type_MAC;

/* type Type_MAR */ 

typedef uint32 Type_MAR;

/* struct Type_RCR */ 

enum Bits_RCR : uint8
 {
  RCR_SEP  = 0x01,
  RCR_AR   = 0x02,
  RCR_AM   = 0x04,
  RCR_AB   = 0x08,
  RCR_PROM = 0x10
 };
 
inline Bits_RCR operator | (Bits_RCR a,Bits_RCR b)
 { return Bits_RCR(uint8(a)|uint8(b)); }
 
enum Field_RCR_RRFT : uint8
 {
  RCR_RRFT_Thresh32              = 0x00,
  RCR_RRFT_Thresh64              = 0x01,
  RCR_RRFT_Thresh128             = 0x02,
  RCR_RRFT_Thresh256             = 0x03,
  RCR_RRFT_Thresh512             = 0x04,
  RCR_RRFT_Thresh768             = 0x05,
  RCR_RRFT_Thresh1024            = 0x06,
  RCR_RRFT_ThreshStoreAndForward = 0x07
 };
 
struct PrintField_RCR_RRFT
 {
  Field_RCR_RRFT field;

  explicit PrintField_RCR_RRFT(Field_RCR_RRFT field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Thresh32"); break;
       case 0x01 : Putobj(out,"Thresh64"); break;
       case 0x02 : Putobj(out,"Thresh128"); break;
       case 0x03 : Putobj(out,"Thresh256"); break;
       case 0x04 : Putobj(out,"Thresh512"); break;
       case 0x05 : Putobj(out,"Thresh768"); break;
       case 0x06 : Putobj(out,"Thresh1024"); break;
       case 0x07 : Putobj(out,"ThreshStoreAndForward"); break;

       default: Putobj(out,uint8(field));
      }
   }
 };
 
inline PrintField_RCR_RRFT GetTextDesc(Field_RCR_RRFT field)
 {
  return PrintField_RCR_RRFT(field);
 }
 
struct Type_RCR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_RCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RCR & setTo(Bar &bar) { bar.set_RCR(*this); return *this; }
 

  template <class Bar>
  Type_RCR & setTo(Bar &bar,uint32 ind) { bar.set_RCR(ind,*this); return *this; }
 

  template <class T>
  Type_RCR & set(T to) { to(*this); return *this; }
 

  Type_RCR & setbit(Bits_RCR bits) { value|=Type(bits); return *this; }
 
  Type_RCR & setbitIf(bool cond,Bits_RCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RCR & clearbit(Bits_RCR bits) { value&=~Type(bits); return *this; }
 
  Type_RCR & clearbitIf(bool cond,Bits_RCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RCR bits) const { return value&bits; }
 
  bool testbit(Bits_RCR bits) const { return (value&bits)==Type(bits); }
 

  Field_RCR_RRFT get_RRFT() const
   {
    return Field_RCR_RRFT((value>>5)&0x7);
   }
 
  Type_RCR & set_RRFT(Field_RCR_RRFT field)
   {
    value=((Type(field)&0x7)<<5)|(value&0xFFFFFF1F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RCR_SEP )
      {
       if( first )
         {
          Putobj(out,"SEP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SEP");
         }
      }

    if( value&RCR_AR )
      {
       if( first )
         {
          Putobj(out,"AR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AR");
         }
      }

    if( value&RCR_AM )
      {
       if( first )
         {
          Putobj(out,"AM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AM");
         }
      }

    if( value&RCR_AB )
      {
       if( first )
         {
          Putobj(out,"AB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AB");
         }
      }

    if( value&RCR_PROM )
      {
       if( first )
         {
          Putobj(out,"PROM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PROM");
         }
      }

    if( first )
      {
       Printf(out,"RRFT(#;)",get_RRFT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RRFT(#;)",get_RRFT());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TCR */ 

enum Bits_TCR : uint8
 {
  TCR_PQEN   = 0x01,
  TCR_OFSET  = 0x08,
  TCR_RTGOPT = 0x10
 };
 
inline Bits_TCR operator | (Bits_TCR a,Bits_TCR b)
 { return Bits_TCR(uint8(a)|uint8(b)); }
 
enum Field_TCR_LB : uint8
 {
  TCR_LB_NONE     = 0x00,
  TCR_LB_INTERNAL = 0x01,
  TCR_LB_PHY      = 0x02
 };
 
struct PrintField_TCR_LB
 {
  Field_TCR_LB field;

  explicit PrintField_TCR_LB(Field_TCR_LB field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NONE"); break;
       case 0x01 : Putobj(out,"INTERNAL"); break;
       case 0x02 : Putobj(out,"PHY"); break;

       default: Putobj(out,uint8(field));
      }
   }
 };
 
inline PrintField_TCR_LB GetTextDesc(Field_TCR_LB field)
 {
  return PrintField_TCR_LB(field);
 }
 
enum Field_TCR_RTFT : uint8
 {
  TCR_RTFT_Thresh128             = 0x00,
  TCR_RTFT_Thresh256             = 0x01,
  TCR_RTFT_Thresh512             = 0x02,
  TCR_RTFT_Thresh1024            = 0x03,
  TCR_RTFT_ThreshStoreAndForward = 0x04
 };
 
struct PrintField_TCR_RTFT
 {
  Field_TCR_RTFT field;

  explicit PrintField_TCR_RTFT(Field_TCR_RTFT field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Thresh128"); break;
       case 0x01 : Putobj(out,"Thresh256"); break;
       case 0x02 : Putobj(out,"Thresh512"); break;
       case 0x03 : Putobj(out,"Thresh1024"); break;
       case 0x04 : Putobj(out,"ThreshStoreAndForward"); break;

       default: Putobj(out,uint8(field));
      }
   }
 };
 
inline PrintField_TCR_RTFT GetTextDesc(Field_TCR_RTFT field)
 {
  return PrintField_TCR_RTFT(field);
 }
 
struct Type_TCR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_TCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TCR & setTo(Bar &bar) { bar.set_TCR(*this); return *this; }
 

  template <class Bar>
  Type_TCR & setTo(Bar &bar,uint32 ind) { bar.set_TCR(ind,*this); return *this; }
 

  template <class T>
  Type_TCR & set(T to) { to(*this); return *this; }
 

  Type_TCR & setbit(Bits_TCR bits) { value|=Type(bits); return *this; }
 
  Type_TCR & setbitIf(bool cond,Bits_TCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TCR & clearbit(Bits_TCR bits) { value&=~Type(bits); return *this; }
 
  Type_TCR & clearbitIf(bool cond,Bits_TCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TCR bits) const { return value&bits; }
 
  bool testbit(Bits_TCR bits) const { return (value&bits)==Type(bits); }
 

  Field_TCR_LB get_LB() const
   {
    return Field_TCR_LB((value>>1)&0x3);
   }
 
  Type_TCR & set_LB(Field_TCR_LB field)
   {
    value=((Type(field)&0x3)<<1)|(value&0xFFFFFFF9);

    return *this;
   }
 

  Field_TCR_RTFT get_RTFT() const
   {
    return Field_TCR_RTFT((value>>5)&0x7);
   }
 
  Type_TCR & set_RTFT(Field_TCR_RTFT field)
   {
    value=((Type(field)&0x7)<<5)|(value&0xFFFFFF1F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TCR_PQEN )
      {
       if( first )
         {
          Putobj(out,"PQEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PQEN");
         }
      }

    if( value&TCR_OFSET )
      {
       if( first )
         {
          Putobj(out,"OFSET");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OFSET");
         }
      }

    if( value&TCR_RTGOPT )
      {
       if( first )
         {
          Putobj(out,"RTGOPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RTGOPT");
         }
      }

    if( first )
      {
       Printf(out,"LB(#;)",get_LB());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LB(#;)",get_LB());
      }

    if( first )
      {
       Printf(out,"RTFT(#;)",get_RTFT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RTFT(#;)",get_RTFT());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CR */ 

enum Bits_CR : uint16
 {
  CR_INIT   = 0x0001,
  CR_START  = 0x0002,
  CR_STOP   = 0x0004,
  CR_RXON   = 0x0008,
  CR_TXON   = 0x0010,
  CR_TDMD   = 0x0020,
  CR_RDMD   = 0x0040,
  CR_EREN   = 0x0100,
  CR_ETEN   = 0x0200,
  CR_FDX    = 0x0400,
  CR_DPOLL  = 0x0800,
  CR_REAUTO = 0x1000,
  CR_TDMD1  = 0x2000,
  CR_RDMD1  = 0x4000,
  CR_RESET  = 0x8000
 };
 
inline Bits_CR operator | (Bits_CR a,Bits_CR b)
 { return Bits_CR(uint16(a)|uint16(b)); }
 
struct Type_CR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_CR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CR & setTo(Bar &bar) { bar.set_CR(*this); return *this; }
 

  template <class Bar>
  Type_CR & setTo(Bar &bar,uint32 ind) { bar.set_CR(ind,*this); return *this; }
 

  template <class T>
  Type_CR & set(T to) { to(*this); return *this; }
 

  Type_CR & setbit(Bits_CR bits) { value|=Type(bits); return *this; }
 
  Type_CR & setbitIf(bool cond,Bits_CR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CR & clearbit(Bits_CR bits) { value&=~Type(bits); return *this; }
 
  Type_CR & clearbitIf(bool cond,Bits_CR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CR bits) const { return value&bits; }
 
  bool testbit(Bits_CR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CR_INIT )
      {
       if( first )
         {
          Putobj(out,"INIT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"INIT");
         }
      }

    if( value&CR_START )
      {
       if( first )
         {
          Putobj(out,"START");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"START");
         }
      }

    if( value&CR_STOP )
      {
       if( first )
         {
          Putobj(out,"STOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"STOP");
         }
      }

    if( value&CR_RXON )
      {
       if( first )
         {
          Putobj(out,"RXON");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXON");
         }
      }

    if( value&CR_TXON )
      {
       if( first )
         {
          Putobj(out,"TXON");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXON");
         }
      }

    if( value&CR_TDMD )
      {
       if( first )
         {
          Putobj(out,"TDMD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TDMD");
         }
      }

    if( value&CR_RDMD )
      {
       if( first )
         {
          Putobj(out,"RDMD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RDMD");
         }
      }

    if( value&CR_EREN )
      {
       if( first )
         {
          Putobj(out,"EREN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EREN");
         }
      }

    if( value&CR_ETEN )
      {
       if( first )
         {
          Putobj(out,"ETEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ETEN");
         }
      }

    if( value&CR_FDX )
      {
       if( first )
         {
          Putobj(out,"FDX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDX");
         }
      }

    if( value&CR_DPOLL )
      {
       if( first )
         {
          Putobj(out,"DPOLL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DPOLL");
         }
      }

    if( value&CR_REAUTO )
      {
       if( first )
         {
          Putobj(out,"REAUTO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"REAUTO");
         }
      }

    if( value&CR_TDMD1 )
      {
       if( first )
         {
          Putobj(out,"TDMD1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TDMD1");
         }
      }

    if( value&CR_RDMD1 )
      {
       if( first )
         {
          Putobj(out,"RDMD1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RDMD1");
         }
      }

    if( value&CR_RESET )
      {
       if( first )
         {
          Putobj(out,"RESET");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RESET");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_BCR */ 

enum Bits_BCR : uint16
 {
  BCR_LED100  = 0x0040,
  BCR_MED2    = 0x0080,
  BCR_TXQNOBK = 0x4000,
  BCR_VIDFR   = 0x8000
 };
 
inline Bits_BCR operator | (Bits_BCR a,Bits_BCR b)
 { return Bits_BCR(uint16(a)|uint16(b)); }
 
enum Field_BCR_DMAL : uint16
 {
  BCR_DMAL_DMAL8   = 0x00,
  BCR_DMAL_DMAL16  = 0x01,
  BCR_DMAL_DMAL32  = 0x02,
  BCR_DMAL_DMAL64  = 0x03,
  BCR_DMAL_DMAL128 = 0x04,
  BCR_DMAL_DMAL256 = 0x05,
  BCR_DMAL_DMALSF  = 0x06
 };
 
struct PrintField_BCR_DMAL
 {
  Field_BCR_DMAL field;

  explicit PrintField_BCR_DMAL(Field_BCR_DMAL field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"DMAL8"); break;
       case 0x01 : Putobj(out,"DMAL16"); break;
       case 0x02 : Putobj(out,"DMAL32"); break;
       case 0x03 : Putobj(out,"DMAL64"); break;
       case 0x04 : Putobj(out,"DMAL128"); break;
       case 0x05 : Putobj(out,"DMAL256"); break;
       case 0x06 : Putobj(out,"DMALSF"); break;

       default: Putobj(out,uint16(field));
      }
   }
 };
 
inline PrintField_BCR_DMAL GetTextDesc(Field_BCR_DMAL field)
 {
  return PrintField_BCR_DMAL(field);
 }
 
struct Type_BCR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_BCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_BCR & setTo(Bar &bar) { bar.set_BCR(*this); return *this; }
 

  template <class Bar>
  Type_BCR & setTo(Bar &bar,uint32 ind) { bar.set_BCR(ind,*this); return *this; }
 

  template <class T>
  Type_BCR & set(T to) { to(*this); return *this; }
 

  Type_BCR & setbit(Bits_BCR bits) { value|=Type(bits); return *this; }
 
  Type_BCR & setbitIf(bool cond,Bits_BCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_BCR & clearbit(Bits_BCR bits) { value&=~Type(bits); return *this; }
 
  Type_BCR & clearbitIf(bool cond,Bits_BCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_BCR bits) const { return value&bits; }
 
  bool testbit(Bits_BCR bits) const { return (value&bits)==Type(bits); }
 

  Field_BCR_DMAL get_DMAL() const
   {
    return Field_BCR_DMAL((value>>0)&0x7);
   }
 
  Type_BCR & set_DMAL(Field_BCR_DMAL field)
   {
    value=((Type(field)&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Type get_CRFT() const
   {
    return (value>>3)&0x7;
   }
 
  Type_BCR & set_CRFT(Type field)
   {
    value=((field&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Type get_POT() const
   {
    return (value>>8)&0x7;
   }
 
  Type_BCR & set_POT(Type field)
   {
    value=((field&0x7)<<8)|(value&0xFFFFF8FF);

    return *this;
   }
 

  Type get_CTFT() const
   {
    return (value>>11)&0x7;
   }
 
  Type_BCR & set_CTFT(Type field)
   {
    value=((field&0x7)<<11)|(value&0xFFFFC7FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&BCR_LED100 )
      {
       if( first )
         {
          Putobj(out,"LED100");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LED100");
         }
      }

    if( value&BCR_MED2 )
      {
       if( first )
         {
          Putobj(out,"MED2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MED2");
         }
      }

    if( value&BCR_TXQNOBK )
      {
       if( first )
         {
          Putobj(out,"TXQNOBK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXQNOBK");
         }
      }

    if( value&BCR_VIDFR )
      {
       if( first )
         {
          Putobj(out,"VIDFR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VIDFR");
         }
      }

    if( first )
      {
       Printf(out,"DMAL(#;)",get_DMAL());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DMAL(#;)",get_DMAL());
      }

    if( first )
      {
       Printf(out,"CRFT(#;)",get_CRFT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CRFT(#;)",get_CRFT());
      }

    if( first )
      {
       Printf(out,"POT(#;)",get_POT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"POT(#;)",get_POT());
      }

    if( first )
      {
       Printf(out,"CTFT(#;)",get_CTFT());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CTFT(#;)",get_CTFT());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_EECSR */ 

enum Bits_EECSR : uint8
 {
  EECSR_D0     = 0x01,
  EECSR_DI     = 0x02,
  EECSR_SK     = 0x04,
  EECSR_CS     = 0x08,
  EECSR_DPM    = 0x10,
  EECSR_AUTOLD = 0x20,
  EECSR_EMBP   = 0x40,
  EECSR_EEPR   = 0x80
 };
 
inline Bits_EECSR operator | (Bits_EECSR a,Bits_EECSR b)
 { return Bits_EECSR(uint8(a)|uint8(b)); }
 
struct Type_EECSR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_EECSR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_EECSR & setTo(Bar &bar) { bar.set_EECSR(*this); return *this; }
 

  template <class Bar>
  Type_EECSR & setTo(Bar &bar,uint32 ind) { bar.set_EECSR(ind,*this); return *this; }
 

  template <class T>
  Type_EECSR & set(T to) { to(*this); return *this; }
 

  Type_EECSR & setbit(Bits_EECSR bits) { value|=Type(bits); return *this; }
 
  Type_EECSR & setbitIf(bool cond,Bits_EECSR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_EECSR & clearbit(Bits_EECSR bits) { value&=~Type(bits); return *this; }
 
  Type_EECSR & clearbitIf(bool cond,Bits_EECSR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_EECSR bits) const { return value&bits; }
 
  bool testbit(Bits_EECSR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&EECSR_D0 )
      {
       if( first )
         {
          Putobj(out,"D0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"D0");
         }
      }

    if( value&EECSR_DI )
      {
       if( first )
         {
          Putobj(out,"DI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DI");
         }
      }

    if( value&EECSR_SK )
      {
       if( first )
         {
          Putobj(out,"SK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SK");
         }
      }

    if( value&EECSR_CS )
      {
       if( first )
         {
          Putobj(out,"CS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CS");
         }
      }

    if( value&EECSR_DPM )
      {
       if( first )
         {
          Putobj(out,"DPM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DPM");
         }
      }

    if( value&EECSR_AUTOLD )
      {
       if( first )
         {
          Putobj(out,"AUTOLD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AUTOLD");
         }
      }

    if( value&EECSR_EMBP )
      {
       if( first )
         {
          Putobj(out,"EMBP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EMBP");
         }
      }

    if( value&EECSR_EEPR )
      {
       if( first )
         {
          Putobj(out,"EEPR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EEPR");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CFG */ 

enum Bits_CFG : uint32
 {
  CFG_LED0S0  = 0x00000001,
  CFG_EELOAD  = 0x00000080,
  CFG_MRLDIS  = 0x00002000,
  CFG_QPKTDIS = 0x00008000,
  CFG_BPS0    = 0x00010000,
  CFG_BPS1    = 0x00020000,
  CFG_BPS2    = 0x00040000,
  CFG_BTSEL   = 0x00080000,
  CFG_DTSEL   = 0x00100000,
  CFG_DLYEN   = 0x00200000,
  CFG_BROPT   = 0x00400000,
  CFG_MEDEN   = 0x00800000,
  CFG_BAKOPT  = 0x01000000,
  CFG_MBA     = 0x02000000,
  CFG_CAP     = 0x04000000,
  CFG_CRADOM  = 0x08000000,
  CFG_MAGIC   = 0x10000000,
  CFG_DIAL    = 0x40000000,
  CFG_GPIOEN  = 0x80000000
 };
 
inline Bits_CFG operator | (Bits_CFG a,Bits_CFG b)
 { return Bits_CFG(uint32(a)|uint32(b)); }
 
struct Type_CFG
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CFG(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CFG & setTo(Bar &bar) { bar.set_CFG(*this); return *this; }
 

  template <class Bar>
  Type_CFG & setTo(Bar &bar,uint32 ind) { bar.set_CFG(ind,*this); return *this; }
 

  template <class T>
  Type_CFG & set(T to) { to(*this); return *this; }
 

  Type_CFG & setbit(Bits_CFG bits) { value|=Type(bits); return *this; }
 
  Type_CFG & setbitIf(bool cond,Bits_CFG bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CFG & clearbit(Bits_CFG bits) { value&=~Type(bits); return *this; }
 
  Type_CFG & clearbitIf(bool cond,Bits_CFG bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CFG bits) const { return value&bits; }
 
  bool testbit(Bits_CFG bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CFG_LED0S0 )
      {
       if( first )
         {
          Putobj(out,"LED0S0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LED0S0");
         }
      }

    if( value&CFG_EELOAD )
      {
       if( first )
         {
          Putobj(out,"EELOAD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EELOAD");
         }
      }

    if( value&CFG_MRLDIS )
      {
       if( first )
         {
          Putobj(out,"MRLDIS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MRLDIS");
         }
      }

    if( value&CFG_QPKTDIS )
      {
       if( first )
         {
          Putobj(out,"QPKTDIS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"QPKTDIS");
         }
      }

    if( value&CFG_BPS0 )
      {
       if( first )
         {
          Putobj(out,"BPS0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BPS0");
         }
      }

    if( value&CFG_BPS1 )
      {
       if( first )
         {
          Putobj(out,"BPS1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BPS1");
         }
      }

    if( value&CFG_BPS2 )
      {
       if( first )
         {
          Putobj(out,"BPS2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BPS2");
         }
      }

    if( value&CFG_BTSEL )
      {
       if( first )
         {
          Putobj(out,"BTSEL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BTSEL");
         }
      }

    if( value&CFG_DTSEL )
      {
       if( first )
         {
          Putobj(out,"DTSEL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DTSEL");
         }
      }

    if( value&CFG_DLYEN )
      {
       if( first )
         {
          Putobj(out,"DLYEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DLYEN");
         }
      }

    if( value&CFG_BROPT )
      {
       if( first )
         {
          Putobj(out,"BROPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BROPT");
         }
      }

    if( value&CFG_MEDEN )
      {
       if( first )
         {
          Putobj(out,"MEDEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MEDEN");
         }
      }

    if( value&CFG_BAKOPT )
      {
       if( first )
         {
          Putobj(out,"BAKOPT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BAKOPT");
         }
      }

    if( value&CFG_MBA )
      {
       if( first )
         {
          Putobj(out,"MBA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MBA");
         }
      }

    if( value&CFG_CAP )
      {
       if( first )
         {
          Putobj(out,"CAP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CAP");
         }
      }

    if( value&CFG_CRADOM )
      {
       if( first )
         {
          Putobj(out,"CRADOM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CRADOM");
         }
      }

    if( value&CFG_MAGIC )
      {
       if( first )
         {
          Putobj(out,"MAGIC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAGIC");
         }
      }

    if( value&CFG_DIAL )
      {
       if( first )
         {
          Putobj(out,"DIAL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DIAL");
         }
      }

    if( value&CFG_GPIOEN )
      {
       if( first )
         {
          Putobj(out,"GPIOEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GPIOEN");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MiscCR */ 

enum Bits_MiscCR : uint16
 {
  MiscCR_T0EN      = 0x0001,
  MiscCR_T0SUSPEND = 0x0002,
  MiscCR_HDXFEN    = 0x0004,
  MiscCR_FDXRFEN   = 0x0008,
  MiscCR_FDXTFEN   = 0x0010,
  MiscCR_T0US      = 0x0020,
  MiscCR_T1EN      = 0x0100,
  MiscCR_PHYINTEN  = 0x0200,
  MiscCR_VAUXJMP   = 0x2000,
  MiscCR_FORSRST   = 0x4000
 };
 
inline Bits_MiscCR operator | (Bits_MiscCR a,Bits_MiscCR b)
 { return Bits_MiscCR(uint16(a)|uint16(b)); }
 
struct Type_MiscCR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_MiscCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MiscCR & setTo(Bar &bar) { bar.set_MiscCR(*this); return *this; }
 

  template <class Bar>
  Type_MiscCR & setTo(Bar &bar,uint32 ind) { bar.set_MiscCR(ind,*this); return *this; }
 

  template <class T>
  Type_MiscCR & set(T to) { to(*this); return *this; }
 

  Type_MiscCR & setbit(Bits_MiscCR bits) { value|=Type(bits); return *this; }
 
  Type_MiscCR & setbitIf(bool cond,Bits_MiscCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MiscCR & clearbit(Bits_MiscCR bits) { value&=~Type(bits); return *this; }
 
  Type_MiscCR & clearbitIf(bool cond,Bits_MiscCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MiscCR bits) const { return value&bits; }
 
  bool testbit(Bits_MiscCR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MiscCR_T0EN )
      {
       if( first )
         {
          Putobj(out,"T0EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T0EN");
         }
      }

    if( value&MiscCR_T0SUSPEND )
      {
       if( first )
         {
          Putobj(out,"T0SUSPEND");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T0SUSPEND");
         }
      }

    if( value&MiscCR_HDXFEN )
      {
       if( first )
         {
          Putobj(out,"HDXFEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HDXFEN");
         }
      }

    if( value&MiscCR_FDXRFEN )
      {
       if( first )
         {
          Putobj(out,"FDXRFEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDXRFEN");
         }
      }

    if( value&MiscCR_FDXTFEN )
      {
       if( first )
         {
          Putobj(out,"FDXTFEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDXTFEN");
         }
      }

    if( value&MiscCR_T0US )
      {
       if( first )
         {
          Putobj(out,"T0US");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T0US");
         }
      }

    if( value&MiscCR_T1EN )
      {
       if( first )
         {
          Putobj(out,"T1EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T1EN");
         }
      }

    if( value&MiscCR_PHYINTEN )
      {
       if( first )
         {
          Putobj(out,"PHYINTEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PHYINTEN");
         }
      }

    if( value&MiscCR_VAUXJMP )
      {
       if( first )
         {
          Putobj(out,"VAUXJMP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VAUXJMP");
         }
      }

    if( value&MiscCR_FORSRST )
      {
       if( first )
         {
          Putobj(out,"FORSRST");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FORSRST");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_StickHW */ 

enum Bits_StickHW : uint8
 {
  StickHW_DS0_SHADOW = 0x01,
  StickHW_DS1_SHADOW = 0x02
 };
 
inline Bits_StickHW operator | (Bits_StickHW a,Bits_StickHW b)
 { return Bits_StickHW(uint8(a)|uint8(b)); }
 
struct Type_StickHW
 {
  typedef uint8 Type;

  Type value;


  explicit Type_StickHW(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_StickHW & setTo(Bar &bar) { bar.set_StickHW(*this); return *this; }
 

  template <class Bar>
  Type_StickHW & setTo(Bar &bar,uint32 ind) { bar.set_StickHW(ind,*this); return *this; }
 

  template <class T>
  Type_StickHW & set(T to) { to(*this); return *this; }
 

  Type_StickHW & setbit(Bits_StickHW bits) { value|=Type(bits); return *this; }
 
  Type_StickHW & setbitIf(bool cond,Bits_StickHW bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_StickHW & clearbit(Bits_StickHW bits) { value&=~Type(bits); return *this; }
 
  Type_StickHW & clearbitIf(bool cond,Bits_StickHW bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_StickHW bits) const { return value&bits; }
 
  bool testbit(Bits_StickHW bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&StickHW_DS0_SHADOW )
      {
       if( first )
         {
          Putobj(out,"DS0_SHADOW");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS0_SHADOW");
         }
      }

    if( value&StickHW_DS1_SHADOW )
      {
       if( first )
         {
          Putobj(out,"DS1_SHADOW");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DS1_SHADOW");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_FLOWCR0 */ 

typedef uint8 Type_FLOWCR0;

/* struct Type_FLOWCR1 */ 

enum Bits_FLOWCR1 : uint8
 {
  FLOWCR1_HDXFCEN  = 0x01,
  FLOWCR1_FDXRFCEN = 0x02,
  FLOWCR1_FDXTFCEN = 0x04,
  FLOWCR1_XONEN    = 0x08,
  FLOWCR1_XLTH0    = 0x10,
  FLOWCR1_XLTH1    = 0x20,
  FLOWCR1_XHITH0   = 0x40,
  FLOWCR1_XHITH1   = 0x80
 };
 
inline Bits_FLOWCR1 operator | (Bits_FLOWCR1 a,Bits_FLOWCR1 b)
 { return Bits_FLOWCR1(uint8(a)|uint8(b)); }
 
struct Type_FLOWCR1
 {
  typedef uint8 Type;

  Type value;


  explicit Type_FLOWCR1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_FLOWCR1 & setTo(Bar &bar) { bar.set_FLOWCR1(*this); return *this; }
 

  template <class Bar>
  Type_FLOWCR1 & setTo(Bar &bar,uint32 ind) { bar.set_FLOWCR1(ind,*this); return *this; }
 

  template <class T>
  Type_FLOWCR1 & set(T to) { to(*this); return *this; }
 

  Type_FLOWCR1 & setbit(Bits_FLOWCR1 bits) { value|=Type(bits); return *this; }
 
  Type_FLOWCR1 & setbitIf(bool cond,Bits_FLOWCR1 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_FLOWCR1 & clearbit(Bits_FLOWCR1 bits) { value&=~Type(bits); return *this; }
 
  Type_FLOWCR1 & clearbitIf(bool cond,Bits_FLOWCR1 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_FLOWCR1 bits) const { return value&bits; }
 
  bool testbit(Bits_FLOWCR1 bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&FLOWCR1_HDXFCEN )
      {
       if( first )
         {
          Putobj(out,"HDXFCEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"HDXFCEN");
         }
      }

    if( value&FLOWCR1_FDXRFCEN )
      {
       if( first )
         {
          Putobj(out,"FDXRFCEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDXRFCEN");
         }
      }

    if( value&FLOWCR1_FDXTFCEN )
      {
       if( first )
         {
          Putobj(out,"FDXTFCEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDXTFCEN");
         }
      }

    if( value&FLOWCR1_XONEN )
      {
       if( first )
         {
          Putobj(out,"XONEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XONEN");
         }
      }

    if( value&FLOWCR1_XLTH0 )
      {
       if( first )
         {
          Putobj(out,"XLTH0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XLTH0");
         }
      }

    if( value&FLOWCR1_XLTH1 )
      {
       if( first )
         {
          Putobj(out,"XLTH1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XLTH1");
         }
      }

    if( value&FLOWCR1_XHITH0 )
      {
       if( first )
         {
          Putobj(out,"XHITH0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XHITH0");
         }
      }

    if( value&FLOWCR1_XHITH1 )
      {
       if( first )
         {
          Putobj(out,"XHITH1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XHITH1");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WOLCFG */ 

enum Bits_WOLCFG : uint8
 {
  WOLCFG_SAB     = 0x10,
  WOLCFG_SAM     = 0x20,
  WOLCFG_SFDX    = 0x40,
  WOLCFG_PME_OVR = 0x80
 };
 
inline Bits_WOLCFG operator | (Bits_WOLCFG a,Bits_WOLCFG b)
 { return Bits_WOLCFG(uint8(a)|uint8(b)); }
 
struct Type_WOLCFG
 {
  typedef uint8 Type;

  Type value;


  explicit Type_WOLCFG(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WOLCFG & setTo(Bar &bar) { bar.set_WOLCFG(*this); return *this; }
 

  template <class Bar>
  Type_WOLCFG & setTo(Bar &bar,uint32 ind) { bar.set_WOLCFG(ind,*this); return *this; }
 

  template <class T>
  Type_WOLCFG & set(T to) { to(*this); return *this; }
 

  Type_WOLCFG & setbit(Bits_WOLCFG bits) { value|=Type(bits); return *this; }
 
  Type_WOLCFG & setbitIf(bool cond,Bits_WOLCFG bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WOLCFG & clearbit(Bits_WOLCFG bits) { value&=~Type(bits); return *this; }
 
  Type_WOLCFG & clearbitIf(bool cond,Bits_WOLCFG bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WOLCFG bits) const { return value&bits; }
 
  bool testbit(Bits_WOLCFG bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WOLCFG_SAB )
      {
       if( first )
         {
          Putobj(out,"SAB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SAB");
         }
      }

    if( value&WOLCFG_SAM )
      {
       if( first )
         {
          Putobj(out,"SAM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SAM");
         }
      }

    if( value&WOLCFG_SFDX )
      {
       if( first )
         {
          Putobj(out,"SFDX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SFDX");
         }
      }

    if( value&WOLCFG_PME_OVR )
      {
       if( first )
         {
          Putobj(out,"PME_OVR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PME_OVR");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_WOLCR */ 

enum Bits_WOLCR : uint8
 {
  WOLCR_ARP       = 0x01,
  WOLCR_MAGPKTPSW = 0x02,
  WOLCR_MSWOLEN2  = 0x04,
  WOLCR_PATMATCH  = 0x08,
  WOLCR_UNICAST   = 0x10,
  WOLCR_MAGPKT    = 0x20,
  WOLCR_LINKON    = 0x40,
  WOLCR_LINKOFF   = 0x80
 };
 
inline Bits_WOLCR operator | (Bits_WOLCR a,Bits_WOLCR b)
 { return Bits_WOLCR(uint8(a)|uint8(b)); }
 
struct Type_WOLCR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_WOLCR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_WOLCR & setTo(Bar &bar) { bar.set_WOLCR(*this); return *this; }
 

  template <class Bar>
  Type_WOLCR & setTo(Bar &bar,uint32 ind) { bar.set_WOLCR(ind,*this); return *this; }
 

  template <class T>
  Type_WOLCR & set(T to) { to(*this); return *this; }
 

  Type_WOLCR & setbit(Bits_WOLCR bits) { value|=Type(bits); return *this; }
 
  Type_WOLCR & setbitIf(bool cond,Bits_WOLCR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_WOLCR & clearbit(Bits_WOLCR bits) { value&=~Type(bits); return *this; }
 
  Type_WOLCR & clearbitIf(bool cond,Bits_WOLCR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_WOLCR bits) const { return value&bits; }
 
  bool testbit(Bits_WOLCR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&WOLCR_ARP )
      {
       if( first )
         {
          Putobj(out,"ARP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ARP");
         }
      }

    if( value&WOLCR_MAGPKTPSW )
      {
       if( first )
         {
          Putobj(out,"MAGPKTPSW");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAGPKTPSW");
         }
      }

    if( value&WOLCR_MSWOLEN2 )
      {
       if( first )
         {
          Putobj(out,"MSWOLEN2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MSWOLEN2");
         }
      }

    if( value&WOLCR_PATMATCH )
      {
       if( first )
         {
          Putobj(out,"PATMATCH");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PATMATCH");
         }
      }

    if( value&WOLCR_UNICAST )
      {
       if( first )
         {
          Putobj(out,"UNICAST");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UNICAST");
         }
      }

    if( value&WOLCR_MAGPKT )
      {
       if( first )
         {
          Putobj(out,"MAGPKT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAGPKT");
         }
      }

    if( value&WOLCR_LINKON )
      {
       if( first )
         {
          Putobj(out,"LINKON");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LINKON");
         }
      }

    if( value&WOLCR_LINKOFF )
      {
       if( first )
         {
          Putobj(out,"LINKOFF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LINKOFF");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TEST */ 

enum Bits_TEST : uint8
 {
  TEST_SNORMAL   = 0x01,
  TEST_SMACTEST  = 0x02,
  TEST_SMCSNOOP  = 0x04,
  TEST_SGENWATCH = 0x08
 };
 
inline Bits_TEST operator | (Bits_TEST a,Bits_TEST b)
 { return Bits_TEST(uint8(a)|uint8(b)); }
 
struct Type_TEST
 {
  typedef uint8 Type;

  Type value;


  explicit Type_TEST(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TEST & setTo(Bar &bar) { bar.set_TEST(*this); return *this; }
 

  template <class Bar>
  Type_TEST & setTo(Bar &bar,uint32 ind) { bar.set_TEST(ind,*this); return *this; }
 

  template <class T>
  Type_TEST & set(T to) { to(*this); return *this; }
 

  Type_TEST & setbit(Bits_TEST bits) { value|=Type(bits); return *this; }
 
  Type_TEST & setbitIf(bool cond,Bits_TEST bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TEST & clearbit(Bits_TEST bits) { value&=~Type(bits); return *this; }
 
  Type_TEST & clearbitIf(bool cond,Bits_TEST bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TEST bits) const { return value&bits; }
 
  bool testbit(Bits_TEST bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TEST_SNORMAL )
      {
       if( first )
         {
          Putobj(out,"SNORMAL");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SNORMAL");
         }
      }

    if( value&TEST_SMACTEST )
      {
       if( first )
         {
          Putobj(out,"SMACTEST");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SMACTEST");
         }
      }

    if( value&TEST_SMCSNOOP )
      {
       if( first )
         {
          Putobj(out,"SMCSNOOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SMCSNOOP");
         }
      }

    if( value&TEST_SGENWATCH )
      {
       if( first )
         {
          Putobj(out,"SGENWATCH");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SGENWATCH");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_PWRCSR */ 

typedef uint16 Type_PWRCSR;

/* struct Type_ISR */ 

enum Bits_ISR : uint16
 {
  ISR_PRX   = 0x0001,
  ISR_PTX   = 0x0002,
  ISR_RXE   = 0x0004,
  ISR_TXE   = 0x0008,
  ISR_TU    = 0x0010,
  ISR_RU    = 0x0020,
  ISR_BE    = 0x0040,
  ISR_CNT   = 0x0080,
  ISR_ER    = 0x0100,
  ISR_UDF   = 0x0200,
  ISR_OVF   = 0x0400,
  ISR_PKTRA = 0x0800,
  ISR_NORBF = 0x1000,
  ISR_ABT   = 0x2000,
  ISR_SRC   = 0x4000,
  ISR_GEN   = 0x8000
 };
 
inline Bits_ISR operator | (Bits_ISR a,Bits_ISR b)
 { return Bits_ISR(uint16(a)|uint16(b)); }
 
struct Type_ISR
 {
  typedef uint16 Type;

  Type value;


  explicit Type_ISR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ISR & setTo(Bar &bar) { bar.set_ISR(*this); return *this; }
 

  template <class Bar>
  Type_ISR & setTo(Bar &bar,uint32 ind) { bar.set_ISR(ind,*this); return *this; }
 

  template <class T>
  Type_ISR & set(T to) { to(*this); return *this; }
 

  Type_ISR & setbit(Bits_ISR bits) { value|=Type(bits); return *this; }
 
  Type_ISR & setbitIf(bool cond,Bits_ISR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_ISR & clearbit(Bits_ISR bits) { value&=~Type(bits); return *this; }
 
  Type_ISR & clearbitIf(bool cond,Bits_ISR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_ISR bits) const { return value&bits; }
 
  bool testbit(Bits_ISR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&ISR_PRX )
      {
       if( first )
         {
          Putobj(out,"PRX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PRX");
         }
      }

    if( value&ISR_PTX )
      {
       if( first )
         {
          Putobj(out,"PTX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PTX");
         }
      }

    if( value&ISR_RXE )
      {
       if( first )
         {
          Putobj(out,"RXE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXE");
         }
      }

    if( value&ISR_TXE )
      {
       if( first )
         {
          Putobj(out,"TXE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TXE");
         }
      }

    if( value&ISR_TU )
      {
       if( first )
         {
          Putobj(out,"TU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TU");
         }
      }

    if( value&ISR_RU )
      {
       if( first )
         {
          Putobj(out,"RU");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RU");
         }
      }

    if( value&ISR_BE )
      {
       if( first )
         {
          Putobj(out,"BE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BE");
         }
      }

    if( value&ISR_CNT )
      {
       if( first )
         {
          Putobj(out,"CNT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CNT");
         }
      }

    if( value&ISR_ER )
      {
       if( first )
         {
          Putobj(out,"ER");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ER");
         }
      }

    if( value&ISR_UDF )
      {
       if( first )
         {
          Putobj(out,"UDF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDF");
         }
      }

    if( value&ISR_OVF )
      {
       if( first )
         {
          Putobj(out,"OVF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OVF");
         }
      }

    if( value&ISR_PKTRA )
      {
       if( first )
         {
          Putobj(out,"PKTRA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PKTRA");
         }
      }

    if( value&ISR_NORBF )
      {
       if( first )
         {
          Putobj(out,"NORBF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NORBF");
         }
      }

    if( value&ISR_ABT )
      {
       if( first )
         {
          Putobj(out,"ABT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ABT");
         }
      }

    if( value&ISR_SRC )
      {
       if( first )
         {
          Putobj(out,"SRC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SRC");
         }
      }

    if( value&ISR_GEN )
      {
       if( first )
         {
          Putobj(out,"GEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"GEN");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MISR */ 

enum Bits_MISR : uint8
 {
  MISR_TM0    = 0x01,
  MISR_TM1    = 0x02,
  MISR_PHY    = 0x04,
  MISR_SSRC   = 0x10,
  MISR_UDPSET = 0x20,
  MISR_UDPCLR = 0x40,
  MISR_PWE    = 0x80
 };
 
inline Bits_MISR operator | (Bits_MISR a,Bits_MISR b)
 { return Bits_MISR(uint8(a)|uint8(b)); }
 
struct Type_MISR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_MISR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MISR & setTo(Bar &bar) { bar.set_MISR(*this); return *this; }
 

  template <class Bar>
  Type_MISR & setTo(Bar &bar,uint32 ind) { bar.set_MISR(ind,*this); return *this; }
 

  template <class T>
  Type_MISR & set(T to) { to(*this); return *this; }
 

  Type_MISR & setbit(Bits_MISR bits) { value|=Type(bits); return *this; }
 
  Type_MISR & setbitIf(bool cond,Bits_MISR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MISR & clearbit(Bits_MISR bits) { value&=~Type(bits); return *this; }
 
  Type_MISR & clearbitIf(bool cond,Bits_MISR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MISR bits) const { return value&bits; }
 
  bool testbit(Bits_MISR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MISR_TM0 )
      {
       if( first )
         {
          Putobj(out,"TM0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TM0");
         }
      }

    if( value&MISR_TM1 )
      {
       if( first )
         {
          Putobj(out,"TM1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TM1");
         }
      }

    if( value&MISR_PHY )
      {
       if( first )
         {
          Putobj(out,"PHY");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PHY");
         }
      }

    if( value&MISR_SSRC )
      {
       if( first )
         {
          Putobj(out,"SSRC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SSRC");
         }
      }

    if( value&MISR_UDPSET )
      {
       if( first )
         {
          Putobj(out,"UDPSET");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDPSET");
         }
      }

    if( value&MISR_UDPCLR )
      {
       if( first )
         {
          Putobj(out,"UDPCLR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDPCLR");
         }
      }

    if( value&MISR_PWE )
      {
       if( first )
         {
          Putobj(out,"PWE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PWE");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIMR */ 

enum Bits_MIMR : uint8
 {
  MIMR_TM0 = 0x01,
  MIMR_TM1 = 0x02
 };
 
inline Bits_MIMR operator | (Bits_MIMR a,Bits_MIMR b)
 { return Bits_MIMR(uint8(a)|uint8(b)); }
 
struct Type_MIMR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_MIMR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIMR & setTo(Bar &bar) { bar.set_MIMR(*this); return *this; }
 

  template <class Bar>
  Type_MIMR & setTo(Bar &bar,uint32 ind) { bar.set_MIMR(ind,*this); return *this; }
 

  template <class T>
  Type_MIMR & set(T to) { to(*this); return *this; }
 

  Type_MIMR & setbit(Bits_MIMR bits) { value|=Type(bits); return *this; }
 
  Type_MIMR & setbitIf(bool cond,Bits_MIMR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIMR & clearbit(Bits_MIMR bits) { value&=~Type(bits); return *this; }
 
  Type_MIMR & clearbitIf(bool cond,Bits_MIMR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIMR bits) const { return value&bits; }
 
  bool testbit(Bits_MIMR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIMR_TM0 )
      {
       if( first )
         {
          Putobj(out,"TM0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TM0");
         }
      }

    if( value&MIMR_TM1 )
      {
       if( first )
         {
          Putobj(out,"TM1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TM1");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_CurRD */ 

typedef uint32 Type_CurRD;

/* type Type_CurTD */ 

typedef uint32 Type_CurTD;

/* type Type_PauseTimer */ 

typedef uint16 Type_PauseTimer;

/* type Type_SoftT0 */ 

typedef uint16 Type_SoftT0;

/* type Type_SoftT1 */ 

typedef uint16 Type_SoftT1;

/* struct Type_MIISR */ 

enum Bits_MIISR : uint8
 {
  MIISR_SPEED10 = 0x01,
  MIISR_NOLINK  = 0x02,
  MIISR_FDX     = 0x04
 };
 
inline Bits_MIISR operator | (Bits_MIISR a,Bits_MIISR b)
 { return Bits_MIISR(uint8(a)|uint8(b)); }
 
struct Type_MIISR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_MIISR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIISR & setTo(Bar &bar) { bar.set_MIISR(*this); return *this; }
 

  template <class Bar>
  Type_MIISR & setTo(Bar &bar,uint32 ind) { bar.set_MIISR(ind,*this); return *this; }
 

  template <class T>
  Type_MIISR & set(T to) { to(*this); return *this; }
 

  Type_MIISR & setbit(Bits_MIISR bits) { value|=Type(bits); return *this; }
 
  Type_MIISR & setbitIf(bool cond,Bits_MIISR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIISR & clearbit(Bits_MIISR bits) { value&=~Type(bits); return *this; }
 
  Type_MIISR & clearbitIf(bool cond,Bits_MIISR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIISR bits) const { return value&bits; }
 
  bool testbit(Bits_MIISR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIISR_SPEED10 )
      {
       if( first )
         {
          Putobj(out,"SPEED10");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SPEED10");
         }
      }

    if( value&MIISR_NOLINK )
      {
       if( first )
         {
          Putobj(out,"NOLINK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NOLINK");
         }
      }

    if( value&MIISR_FDX )
      {
       if( first )
         {
          Putobj(out,"FDX");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FDX");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIICR */ 

enum Bits_MIICR : uint8
 {
  MIICR_MDC   = 0x01,
  MIICR_MDI   = 0x02,
  MIICR_MDO   = 0x04,
  MIICR_MOUT  = 0x08,
  MIICR_MDPM  = 0x10,
  MIICR_WCMD  = 0x20,
  MIICR_RCMD  = 0x40,
  MIICR_MAUTO = 0x80
 };
 
inline Bits_MIICR operator | (Bits_MIICR a,Bits_MIICR b)
 { return Bits_MIICR(uint8(a)|uint8(b)); }
 
struct Type_MIICR
 {
  typedef uint8 Type;

  Type value;


  explicit Type_MIICR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIICR & setTo(Bar &bar) { bar.set_MIICR(*this); return *this; }
 

  template <class Bar>
  Type_MIICR & setTo(Bar &bar,uint32 ind) { bar.set_MIICR(ind,*this); return *this; }
 

  template <class T>
  Type_MIICR & set(T to) { to(*this); return *this; }
 

  Type_MIICR & setbit(Bits_MIICR bits) { value|=Type(bits); return *this; }
 
  Type_MIICR & setbitIf(bool cond,Bits_MIICR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIICR & clearbit(Bits_MIICR bits) { value&=~Type(bits); return *this; }
 
  Type_MIICR & clearbitIf(bool cond,Bits_MIICR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIICR bits) const { return value&bits; }
 
  bool testbit(Bits_MIICR bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIICR_MDC )
      {
       if( first )
         {
          Putobj(out,"MDC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MDC");
         }
      }

    if( value&MIICR_MDI )
      {
       if( first )
         {
          Putobj(out,"MDI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MDI");
         }
      }

    if( value&MIICR_MDO )
      {
       if( first )
         {
          Putobj(out,"MDO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MDO");
         }
      }

    if( value&MIICR_MOUT )
      {
       if( first )
         {
          Putobj(out,"MOUT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MOUT");
         }
      }

    if( value&MIICR_MDPM )
      {
       if( first )
         {
          Putobj(out,"MDPM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MDPM");
         }
      }

    if( value&MIICR_WCMD )
      {
       if( first )
         {
          Putobj(out,"WCMD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WCMD");
         }
      }

    if( value&MIICR_RCMD )
      {
       if( first )
         {
          Putobj(out,"RCMD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RCMD");
         }
      }

    if( value&MIICR_MAUTO )
      {
       if( first )
         {
          Putobj(out,"MAUTO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAUTO");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MIIAD */ 

enum Bits_MIIAD : uint8
 {
  MIIAD_MAD0   = 0x01,
  MIIAD_MDONE  = 0x20,
  MIIAD_MSRCEN = 0x40,
  MIIAD_MIDLE  = 0x80
 };
 
inline Bits_MIIAD operator | (Bits_MIIAD a,Bits_MIIAD b)
 { return Bits_MIIAD(uint8(a)|uint8(b)); }
 
struct Type_MIIAD
 {
  typedef uint8 Type;

  Type value;


  explicit Type_MIIAD(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MIIAD & setTo(Bar &bar) { bar.set_MIIAD(*this); return *this; }
 

  template <class Bar>
  Type_MIIAD & setTo(Bar &bar,uint32 ind) { bar.set_MIIAD(ind,*this); return *this; }
 

  template <class T>
  Type_MIIAD & set(T to) { to(*this); return *this; }
 

  Type_MIIAD & setbit(Bits_MIIAD bits) { value|=Type(bits); return *this; }
 
  Type_MIIAD & setbitIf(bool cond,Bits_MIIAD bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_MIIAD & clearbit(Bits_MIIAD bits) { value&=~Type(bits); return *this; }
 
  Type_MIIAD & clearbitIf(bool cond,Bits_MIIAD bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_MIIAD bits) const { return value&bits; }
 
  bool testbit(Bits_MIIAD bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&MIIAD_MAD0 )
      {
       if( first )
         {
          Putobj(out,"MAD0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAD0");
         }
      }

    if( value&MIIAD_MDONE )
      {
       if( first )
         {
          Putobj(out,"MDONE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MDONE");
         }
      }

    if( value&MIIAD_MSRCEN )
      {
       if( first )
         {
          Putobj(out,"MSRCEN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MSRCEN");
         }
      }

    if( value&MIIAD_MIDLE )
      {
       if( first )
         {
          Putobj(out,"MIDLE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MIDLE");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MIIDATA */ 

typedef uint16 Type_MIIDATA;

/* struct Type_RxDescStatus */ 

enum Bits_RxDescStatus : uint32
 {
  RxDescStatus_ERROR = 0x00000001,
  RxDescStatus_CRC   = 0x00000002,
  RxDescStatus_FAE   = 0x00000004,
  RxDescStatus_FOV   = 0x00000008,
  RxDescStatus_LONG  = 0x00000010,
  RxDescStatus_RUNT  = 0x00000020,
  RxDescStatus_SERR  = 0x00000040,
  RxDescStatus_BUFF  = 0x00000080,
  RxDescStatus_EOP   = 0x00000100,
  RxDescStatus_SOP   = 0x00000200,
  RxDescStatus_CHAIN = 0x00000400,
  RxDescStatus_PHY   = 0x00000800,
  RxDescStatus_BAR   = 0x00001000,
  RxDescStatus_MAR   = 0x00002000,
  RxDescStatus_OK    = 0x00008000,
  RxDescStatus_Own   = 0x80000000
 };
 
inline Bits_RxDescStatus operator | (Bits_RxDescStatus a,Bits_RxDescStatus b)
 { return Bits_RxDescStatus(uint32(a)|uint32(b)); }
 
struct Type_RxDescStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RxDescStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RxDescStatus & setTo(Bar &bar) { bar.set_RxDescStatus(*this); return *this; }
 

  template <class Bar>
  Type_RxDescStatus & setTo(Bar &bar,uint32 ind) { bar.set_RxDescStatus(ind,*this); return *this; }
 

  template <class T>
  Type_RxDescStatus & set(T to) { to(*this); return *this; }
 

  Type_RxDescStatus & setbit(Bits_RxDescStatus bits) { value|=Type(bits); return *this; }
 
  Type_RxDescStatus & setbitIf(bool cond,Bits_RxDescStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RxDescStatus & clearbit(Bits_RxDescStatus bits) { value&=~Type(bits); return *this; }
 
  Type_RxDescStatus & clearbitIf(bool cond,Bits_RxDescStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RxDescStatus bits) const { return value&bits; }
 
  bool testbit(Bits_RxDescStatus bits) const { return (value&bits)==Type(bits); }
 

  Type get_Len() const
   {
    return (value>>16)&0x7FF;
   }
 
  Type_RxDescStatus & set_Len(Type field)
   {
    value=((field&0x7FF)<<16)|(value&0xF800FFFF);

    return *this;
   }
 

  Type get_ExtLen() const
   {
    return (value>>27)&0xF;
   }
 
  Type_RxDescStatus & set_ExtLen(Type field)
   {
    value=((field&0xF)<<27)|(value&0x87FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RxDescStatus_ERROR )
      {
       if( first )
         {
          Putobj(out,"ERROR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ERROR");
         }
      }

    if( value&RxDescStatus_CRC )
      {
       if( first )
         {
          Putobj(out,"CRC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CRC");
         }
      }

    if( value&RxDescStatus_FAE )
      {
       if( first )
         {
          Putobj(out,"FAE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FAE");
         }
      }

    if( value&RxDescStatus_FOV )
      {
       if( first )
         {
          Putobj(out,"FOV");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FOV");
         }
      }

    if( value&RxDescStatus_LONG )
      {
       if( first )
         {
          Putobj(out,"LONG");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"LONG");
         }
      }

    if( value&RxDescStatus_RUNT )
      {
       if( first )
         {
          Putobj(out,"RUNT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RUNT");
         }
      }

    if( value&RxDescStatus_SERR )
      {
       if( first )
         {
          Putobj(out,"SERR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SERR");
         }
      }

    if( value&RxDescStatus_BUFF )
      {
       if( first )
         {
          Putobj(out,"BUFF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BUFF");
         }
      }

    if( value&RxDescStatus_EOP )
      {
       if( first )
         {
          Putobj(out,"EOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EOP");
         }
      }

    if( value&RxDescStatus_SOP )
      {
       if( first )
         {
          Putobj(out,"SOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SOP");
         }
      }

    if( value&RxDescStatus_CHAIN )
      {
       if( first )
         {
          Putobj(out,"CHAIN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CHAIN");
         }
      }

    if( value&RxDescStatus_PHY )
      {
       if( first )
         {
          Putobj(out,"PHY");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PHY");
         }
      }

    if( value&RxDescStatus_BAR )
      {
       if( first )
         {
          Putobj(out,"BAR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BAR");
         }
      }

    if( value&RxDescStatus_MAR )
      {
       if( first )
         {
          Putobj(out,"MAR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MAR");
         }
      }

    if( value&RxDescStatus_OK )
      {
       if( first )
         {
          Putobj(out,"OK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OK");
         }
      }

    if( value&RxDescStatus_Own )
      {
       if( first )
         {
          Putobj(out,"Own");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Own");
         }
      }

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

    if( first )
      {
       Printf(out,"ExtLen(#;)",get_ExtLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ExtLen(#;)",get_ExtLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_RxDescControl */ 

enum Bits_RxDescControl : uint32
 {
  RxDescControl_CHAIN = 0x00008000
 };
 
inline Bits_RxDescControl operator | (Bits_RxDescControl a,Bits_RxDescControl b)
 { return Bits_RxDescControl(uint32(a)|uint32(b)); }
 
struct Type_RxDescControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_RxDescControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_RxDescControl & setTo(Bar &bar) { bar.set_RxDescControl(*this); return *this; }
 

  template <class Bar>
  Type_RxDescControl & setTo(Bar &bar,uint32 ind) { bar.set_RxDescControl(ind,*this); return *this; }
 

  template <class T>
  Type_RxDescControl & set(T to) { to(*this); return *this; }
 

  Type_RxDescControl & setbit(Bits_RxDescControl bits) { value|=Type(bits); return *this; }
 
  Type_RxDescControl & setbitIf(bool cond,Bits_RxDescControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_RxDescControl & clearbit(Bits_RxDescControl bits) { value&=~Type(bits); return *this; }
 
  Type_RxDescControl & clearbitIf(bool cond,Bits_RxDescControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_RxDescControl bits) const { return value&bits; }
 
  bool testbit(Bits_RxDescControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Len() const
   {
    return (value>>0)&0x7FF;
   }
 
  Type_RxDescControl & set_Len(Type field)
   {
    value=((field&0x7FF)<<0)|(value&0xFFFFF800);

    return *this;
   }
 

  Type get_ExtLen() const
   {
    return (value>>11)&0xF;
   }
 
  Type_RxDescControl & set_ExtLen(Type field)
   {
    value=((field&0xF)<<11)|(value&0xFFFF87FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&RxDescControl_CHAIN )
      {
       if( first )
         {
          Putobj(out,"CHAIN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CHAIN");
         }
      }

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

    if( first )
      {
       Printf(out,"ExtLen(#;)",get_ExtLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ExtLen(#;)",get_ExtLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_RxDescBuf */ 

typedef uint32 Type_RxDescBuf;

/* type Type_RxDescNext */ 

typedef uint32 Type_RxDescNext;

/* type Type_RxDescRes1 */ 

typedef uint32 Type_RxDescRes1;

/* type Type_RxDescRes2 */ 

typedef uint32 Type_RxDescRes2;

/* type Type_RxDescRes3 */ 

typedef uint32 Type_RxDescRes3;

/* type Type_RxDescRes4 */ 

typedef uint32 Type_RxDescRes4;

/* struct Type_TxDescStatus */ 

enum Bits_TxDescStatus : uint32
 {
  TxDescStatus_ABT   = 0x00000100,
  TxDescStatus_OWC   = 0x00000200,
  TxDescStatus_CRS   = 0x00000400,
  TxDescStatus_UDF   = 0x00000800,
  TxDescStatus_BUFF  = 0x00001000,
  TxDescStatus_SERR  = 0x00002000,
  TxDescStatus_JUB   = 0x00004000,
  TxDescStatus_ERROR = 0x00008000,
  TxDescStatus_Own   = 0x80000000
 };
 
inline Bits_TxDescStatus operator | (Bits_TxDescStatus a,Bits_TxDescStatus b)
 { return Bits_TxDescStatus(uint32(a)|uint32(b)); }
 
struct Type_TxDescStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TxDescStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TxDescStatus & setTo(Bar &bar) { bar.set_TxDescStatus(*this); return *this; }
 

  template <class Bar>
  Type_TxDescStatus & setTo(Bar &bar,uint32 ind) { bar.set_TxDescStatus(ind,*this); return *this; }
 

  template <class T>
  Type_TxDescStatus & set(T to) { to(*this); return *this; }
 

  Type_TxDescStatus & setbit(Bits_TxDescStatus bits) { value|=Type(bits); return *this; }
 
  Type_TxDescStatus & setbitIf(bool cond,Bits_TxDescStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TxDescStatus & clearbit(Bits_TxDescStatus bits) { value&=~Type(bits); return *this; }
 
  Type_TxDescStatus & clearbitIf(bool cond,Bits_TxDescStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TxDescStatus bits) const { return value&bits; }
 
  bool testbit(Bits_TxDescStatus bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TxDescStatus_ABT )
      {
       if( first )
         {
          Putobj(out,"ABT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ABT");
         }
      }

    if( value&TxDescStatus_OWC )
      {
       if( first )
         {
          Putobj(out,"OWC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"OWC");
         }
      }

    if( value&TxDescStatus_CRS )
      {
       if( first )
         {
          Putobj(out,"CRS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CRS");
         }
      }

    if( value&TxDescStatus_UDF )
      {
       if( first )
         {
          Putobj(out,"UDF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"UDF");
         }
      }

    if( value&TxDescStatus_BUFF )
      {
       if( first )
         {
          Putobj(out,"BUFF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BUFF");
         }
      }

    if( value&TxDescStatus_SERR )
      {
       if( first )
         {
          Putobj(out,"SERR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SERR");
         }
      }

    if( value&TxDescStatus_JUB )
      {
       if( first )
         {
          Putobj(out,"JUB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"JUB");
         }
      }

    if( value&TxDescStatus_ERROR )
      {
       if( first )
         {
          Putobj(out,"ERROR");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ERROR");
         }
      }

    if( value&TxDescStatus_Own )
      {
       if( first )
         {
          Putobj(out,"Own");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Own");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TxDescControl */ 

enum Bits_TxDescControl : uint32
 {
  TxDescControl_CHAIN = 0x00008000,
  TxDescControl_SOP   = 0x00200000,
  TxDescControl_EOP   = 0x00400000,
  TxDescControl_IC    = 0x00800000
 };
 
inline Bits_TxDescControl operator | (Bits_TxDescControl a,Bits_TxDescControl b)
 { return Bits_TxDescControl(uint32(a)|uint32(b)); }
 
struct Type_TxDescControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TxDescControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TxDescControl & setTo(Bar &bar) { bar.set_TxDescControl(*this); return *this; }
 

  template <class Bar>
  Type_TxDescControl & setTo(Bar &bar,uint32 ind) { bar.set_TxDescControl(ind,*this); return *this; }
 

  template <class T>
  Type_TxDescControl & set(T to) { to(*this); return *this; }
 

  Type_TxDescControl & setbit(Bits_TxDescControl bits) { value|=Type(bits); return *this; }
 
  Type_TxDescControl & setbitIf(bool cond,Bits_TxDescControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TxDescControl & clearbit(Bits_TxDescControl bits) { value&=~Type(bits); return *this; }
 
  Type_TxDescControl & clearbitIf(bool cond,Bits_TxDescControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TxDescControl bits) const { return value&bits; }
 
  bool testbit(Bits_TxDescControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_Len() const
   {
    return (value>>0)&0x7FF;
   }
 
  Type_TxDescControl & set_Len(Type field)
   {
    value=((field&0x7FF)<<0)|(value&0xFFFFF800);

    return *this;
   }
 

  Type get_ExtLen() const
   {
    return (value>>11)&0xF;
   }
 
  Type_TxDescControl & set_ExtLen(Type field)
   {
    value=((field&0xF)<<11)|(value&0xFFFF87FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TxDescControl_CHAIN )
      {
       if( first )
         {
          Putobj(out,"CHAIN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CHAIN");
         }
      }

    if( value&TxDescControl_SOP )
      {
       if( first )
         {
          Putobj(out,"SOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SOP");
         }
      }

    if( value&TxDescControl_EOP )
      {
       if( first )
         {
          Putobj(out,"EOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EOP");
         }
      }

    if( value&TxDescControl_IC )
      {
       if( first )
         {
          Putobj(out,"IC");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IC");
         }
      }

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

    if( first )
      {
       Printf(out,"ExtLen(#;)",get_ExtLen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ExtLen(#;)",get_ExtLen());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TxDescBuf */ 

typedef uint32 Type_TxDescBuf;

/* type Type_TxDescNext */ 

typedef uint32 Type_TxDescNext;

/* type Type_TxDescRes1 */ 

typedef uint32 Type_TxDescRes1;

/* type Type_TxDescRes2 */ 

typedef uint32 Type_TxDescRes2;

/* type Type_TxDescRes3 */ 

typedef uint32 Type_TxDescRes3;

/* type Type_TxDescRes4 */ 

typedef uint32 Type_TxDescRes4;

/* struct PCIRegBar<RW> */ 

template <class RW>
struct PCIRegBar
 {
  RW rw;

  template <class ... TT>
  PCIRegBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- PCIMode2

  Type_PCIMode2 get_PCIMode2() { return Type_PCIMode2(rw.template get<uint8>(0x52)); }
 
  void set_PCIMode2(Type_PCIMode2 value) { rw.set(0x52,value.value); }
 
  Setter<Type_PCIMode2> to_PCIMode2() { return Setter<Type_PCIMode2>(rw,0x52); }
 
  static Type_PCIMode2 null_PCIMode2() { return Type_PCIMode2(0); }
 
  static Type_PCIMode2 ones_PCIMode2() { return Type_PCIMode2(Type_PCIMode2::Type(-1)); }
 
  //--- PCIMode3

  Type_PCIMode3 get_PCIMode3() { return Type_PCIMode3(rw.template get<uint8>(0x53)); }
 
  void set_PCIMode3(Type_PCIMode3 value) { rw.set(0x53,value.value); }
 
  Setter<Type_PCIMode3> to_PCIMode3() { return Setter<Type_PCIMode3>(rw,0x53); }
 
  static Type_PCIMode3 null_PCIMode3() { return Type_PCIMode3(0); }
 
  static Type_PCIMode3 ones_PCIMode3() { return Type_PCIMode3(Type_PCIMode3::Type(-1)); }
 
 };
 
/* struct MIIRegBar<RW> */ 

template <class RW>
struct MIIRegBar
 {
  RW rw;

  template <class ... TT>
  MIIRegBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- MIIBMCR

  Type_MIIBMCR get_MIIBMCR() { return Type_MIIBMCR(rw.template get<uint16>(0x0)); }
 
  void set_MIIBMCR(Type_MIIBMCR value) { rw.set(0x0,value.value); }
 
  Setter<Type_MIIBMCR> to_MIIBMCR() { return Setter<Type_MIIBMCR>(rw,0x0); }
 
  static Type_MIIBMCR null_MIIBMCR() { return Type_MIIBMCR(0); }
 
  static Type_MIIBMCR ones_MIIBMCR() { return Type_MIIBMCR(Type_MIIBMCR::Type(-1)); }
 
  //--- MIIBMSR

  Type_MIIBMSR get_MIIBMSR() { return Type_MIIBMSR(rw.template get<uint16>(0x1)); }
 
  void set_MIIBMSR(Type_MIIBMSR value) { rw.set(0x1,value.value); }
 
  Setter<Type_MIIBMSR> to_MIIBMSR() { return Setter<Type_MIIBMSR>(rw,0x1); }
 
  static Type_MIIBMSR null_MIIBMSR() { return Type_MIIBMSR(0); }
 
  static Type_MIIBMSR ones_MIIBMSR() { return Type_MIIBMSR(Type_MIIBMSR::Type(-1)); }
 
  //--- MIIPhyID1

  Type_MIIPhyID1 get_MIIPhyID1() { return Type_MIIPhyID1(rw.template get<uint16>(0x2)); }
 
  void set_MIIPhyID1(Type_MIIPhyID1 value) { rw.set(0x2,value); }
 
  void set_MIIPhyID1_null() { rw.set(0x2,Type_MIIPhyID1(0)); }
 
  void set_MIIPhyID1_ones() { rw.set(0x2,Type_MIIPhyID1(-1)); }
 
  //--- MIIPhyID2

  Type_MIIPhyID2 get_MIIPhyID2() { return Type_MIIPhyID2(rw.template get<uint16>(0x3)); }
 
  void set_MIIPhyID2(Type_MIIPhyID2 value) { rw.set(0x3,value); }
 
  void set_MIIPhyID2_null() { rw.set(0x3,Type_MIIPhyID2(0)); }
 
  void set_MIIPhyID2_ones() { rw.set(0x3,Type_MIIPhyID2(-1)); }
 
  //--- MIIANAR

  Type_MIIANAR get_MIIANAR() { return Type_MIIANAR(rw.template get<uint16>(0x4)); }
 
  void set_MIIANAR(Type_MIIANAR value) { rw.set(0x4,value.value); }
 
  Setter<Type_MIIANAR> to_MIIANAR() { return Setter<Type_MIIANAR>(rw,0x4); }
 
  static Type_MIIANAR null_MIIANAR() { return Type_MIIANAR(0); }
 
  static Type_MIIANAR ones_MIIANAR() { return Type_MIIANAR(Type_MIIANAR::Type(-1)); }
 
  //--- MIIANLPAR

  Type_MIIANLPAR get_MIIANLPAR() { return Type_MIIANLPAR(rw.template get<uint16>(0x5)); }
 
  void set_MIIANLPAR(Type_MIIANLPAR value) { rw.set(0x5,value.value); }
 
  Setter<Type_MIIANLPAR> to_MIIANLPAR() { return Setter<Type_MIIANLPAR>(rw,0x5); }
 
  static Type_MIIANLPAR null_MIIANLPAR() { return Type_MIIANLPAR(0); }
 
  static Type_MIIANLPAR ones_MIIANLPAR() { return Type_MIIANLPAR(Type_MIIANLPAR::Type(-1)); }
 
  //--- MIIModCfg

  Type_MIIModCfg get_MIIModCfg() { return Type_MIIModCfg(rw.template get<uint16>(0x10)); }
 
  void set_MIIModCfg(Type_MIIModCfg value) { rw.set(0x10,value.value); }
 
  Setter<Type_MIIModCfg> to_MIIModCfg() { return Setter<Type_MIIModCfg>(rw,0x10); }
 
  static Type_MIIModCfg null_MIIModCfg() { return Type_MIIModCfg(0); }
 
  static Type_MIIModCfg ones_MIIModCfg() { return Type_MIIModCfg(Type_MIIModCfg::Type(-1)); }
 
 };
 
/* struct DevRegBar<RW> */ 

template <class RW>
struct DevRegBar
 {
  RW rw;

  template <class ... TT>
  DevRegBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- MAC

  Type_MAC get_MAC(uint32 ind) { return Type_MAC(rw.template get<uint8>(0x0 +ind*1)); }
 
  void set_MAC(uint32 ind,Type_MAC value) { rw.set(0x0 +ind*1,value); }
 
  void set_MAC_null(uint32 ind) { rw.set(0x0 +ind*1,Type_MAC(0)); }
 
  void set_MAC_ones(uint32 ind) { rw.set(0x0 +ind*1,Type_MAC(-1)); }
 
  //--- RCR

  Type_RCR get_RCR() { return Type_RCR(rw.template get<uint8>(0x6)); }
 
  void set_RCR(Type_RCR value) { rw.set(0x6,value.value); }
 
  Setter<Type_RCR> to_RCR() { return Setter<Type_RCR>(rw,0x6); }
 
  static Type_RCR null_RCR() { return Type_RCR(0); }
 
  static Type_RCR ones_RCR() { return Type_RCR(Type_RCR::Type(-1)); }
 
  //--- TCR

  Type_TCR get_TCR() { return Type_TCR(rw.template get<uint8>(0x7)); }
 
  void set_TCR(Type_TCR value) { rw.set(0x7,value.value); }
 
  Setter<Type_TCR> to_TCR() { return Setter<Type_TCR>(rw,0x7); }
 
  static Type_TCR null_TCR() { return Type_TCR(0); }
 
  static Type_TCR ones_TCR() { return Type_TCR(Type_TCR::Type(-1)); }
 
  //--- CR

  Type_CR get_CR() { return Type_CR(rw.template get<uint16>(0x8)); }
 
  void set_CR(Type_CR value) { rw.set(0x8,value.value); }
 
  Setter<Type_CR> to_CR() { return Setter<Type_CR>(rw,0x8); }
 
  static Type_CR null_CR() { return Type_CR(0); }
 
  static Type_CR ones_CR() { return Type_CR(Type_CR::Type(-1)); }
 
  //--- ISR

  Type_ISR get_ISR() { return Type_ISR(rw.template get<uint16>(0xC)); }
 
  void set_ISR(Type_ISR value) { rw.set(0xC,value.value); }
 
  Setter<Type_ISR> to_ISR() { return Setter<Type_ISR>(rw,0xC); }
 
  static Type_ISR null_ISR() { return Type_ISR(0); }
 
  static Type_ISR ones_ISR() { return Type_ISR(Type_ISR::Type(-1)); }
 
  //--- IMR

  Type_ISR get_IMR() { return Type_ISR(rw.template get<uint16>(0xE)); }
 
  void set_IMR(Type_ISR value) { rw.set(0xE,value.value); }
 
  Setter<Type_ISR> to_IMR() { return Setter<Type_ISR>(rw,0xE); }
 
  //--- MAR

  Type_MAR get_MAR(uint32 ind) { return Type_MAR(rw.template get<uint32>(0x10 +ind*4)); }
 
  void set_MAR(uint32 ind,Type_MAR value) { rw.set(0x10 +ind*4,value); }
 
  void set_MAR_null(uint32 ind) { rw.set(0x10 +ind*4,Type_MAR(0)); }
 
  void set_MAR_ones(uint32 ind) { rw.set(0x10 +ind*4,Type_MAR(-1)); }
 
  //--- CurRD

  Type_CurRD get_CurRD() { return Type_CurRD(rw.template get<uint32>(0x18)); }
 
  void set_CurRD(Type_CurRD value) { rw.set(0x18,value); }
 
  void set_CurRD_null() { rw.set(0x18,Type_CurRD(0)); }
 
  void set_CurRD_ones() { rw.set(0x18,Type_CurRD(-1)); }
 
  //--- CurTD

  Type_CurTD get_CurTD(uint32 ind) { return Type_CurTD(rw.template get<uint32>(0x1C +ind*4)); }
 
  void set_CurTD(uint32 ind,Type_CurTD value) { rw.set(0x1C +ind*4,value); }
 
  void set_CurTD_null(uint32 ind) { rw.set(0x1C +ind*4,Type_CurTD(0)); }
 
  void set_CurTD_ones(uint32 ind) { rw.set(0x1C +ind*4,Type_CurTD(-1)); }
 
  //--- MIISR

  Type_MIISR get_MIISR() { return Type_MIISR(rw.template get<uint8>(0x6D)); }
 
  void set_MIISR(Type_MIISR value) { rw.set(0x6D,value.value); }
 
  Setter<Type_MIISR> to_MIISR() { return Setter<Type_MIISR>(rw,0x6D); }
 
  static Type_MIISR null_MIISR() { return Type_MIISR(0); }
 
  static Type_MIISR ones_MIISR() { return Type_MIISR(Type_MIISR::Type(-1)); }
 
  //--- BCR

  Type_BCR get_BCR() { return Type_BCR(rw.template get<uint16>(0x6E)); }
 
  void set_BCR(Type_BCR value) { rw.set(0x6E,value.value); }
 
  Setter<Type_BCR> to_BCR() { return Setter<Type_BCR>(rw,0x6E); }
 
  static Type_BCR null_BCR() { return Type_BCR(0); }
 
  static Type_BCR ones_BCR() { return Type_BCR(Type_BCR::Type(-1)); }
 
  //--- MIICR

  Type_MIICR get_MIICR() { return Type_MIICR(rw.template get<uint8>(0x70)); }
 
  void set_MIICR(Type_MIICR value) { rw.set(0x70,value.value); }
 
  Setter<Type_MIICR> to_MIICR() { return Setter<Type_MIICR>(rw,0x70); }
 
  static Type_MIICR null_MIICR() { return Type_MIICR(0); }
 
  static Type_MIICR ones_MIICR() { return Type_MIICR(Type_MIICR::Type(-1)); }
 
  //--- MIIAD

  Type_MIIAD get_MIIAD() { return Type_MIIAD(rw.template get<uint8>(0x71)); }
 
  void set_MIIAD(Type_MIIAD value) { rw.set(0x71,value.value); }
 
  Setter<Type_MIIAD> to_MIIAD() { return Setter<Type_MIIAD>(rw,0x71); }
 
  static Type_MIIAD null_MIIAD() { return Type_MIIAD(0); }
 
  static Type_MIIAD ones_MIIAD() { return Type_MIIAD(Type_MIIAD::Type(-1)); }
 
  //--- MIIDATA

  Type_MIIDATA get_MIIDATA() { return Type_MIIDATA(rw.template get<uint16>(0x72)); }
 
  void set_MIIDATA(Type_MIIDATA value) { rw.set(0x72,value); }
 
  void set_MIIDATA_null() { rw.set(0x72,Type_MIIDATA(0)); }
 
  void set_MIIDATA_ones() { rw.set(0x72,Type_MIIDATA(-1)); }
 
  //--- EECSR

  Type_EECSR get_EECSR() { return Type_EECSR(rw.template get<uint8>(0x74)); }
 
  void set_EECSR(Type_EECSR value) { rw.set(0x74,value.value); }
 
  Setter<Type_EECSR> to_EECSR() { return Setter<Type_EECSR>(rw,0x74); }
 
  static Type_EECSR null_EECSR() { return Type_EECSR(0); }
 
  static Type_EECSR ones_EECSR() { return Type_EECSR(Type_EECSR::Type(-1)); }
 
  //--- CFG

  Type_CFG get_CFG() { return Type_CFG(rw.template get<uint32>(0x78)); }
 
  void set_CFG(Type_CFG value) { rw.set(0x78,value.value); }
 
  Setter<Type_CFG> to_CFG() { return Setter<Type_CFG>(rw,0x78); }
 
  static Type_CFG null_CFG() { return Type_CFG(0); }
 
  static Type_CFG ones_CFG() { return Type_CFG(Type_CFG::Type(-1)); }
 
  //--- MiscCR

  Type_MiscCR get_MiscCR() { return Type_MiscCR(rw.template get<uint16>(0x80)); }
 
  void set_MiscCR(Type_MiscCR value) { rw.set(0x80,value.value); }
 
  Setter<Type_MiscCR> to_MiscCR() { return Setter<Type_MiscCR>(rw,0x80); }
 
  static Type_MiscCR null_MiscCR() { return Type_MiscCR(0); }
 
  static Type_MiscCR ones_MiscCR() { return Type_MiscCR(Type_MiscCR::Type(-1)); }
 
  //--- StickHW

  Type_StickHW get_StickHW() { return Type_StickHW(rw.template get<uint8>(0x83)); }
 
  void set_StickHW(Type_StickHW value) { rw.set(0x83,value.value); }
 
  Setter<Type_StickHW> to_StickHW() { return Setter<Type_StickHW>(rw,0x83); }
 
  static Type_StickHW null_StickHW() { return Type_StickHW(0); }
 
  static Type_StickHW ones_StickHW() { return Type_StickHW(Type_StickHW::Type(-1)); }
 
  //--- MISR

  Type_MISR get_MISR() { return Type_MISR(rw.template get<uint8>(0x84)); }
 
  void set_MISR(Type_MISR value) { rw.set(0x84,value.value); }
 
  Setter<Type_MISR> to_MISR() { return Setter<Type_MISR>(rw,0x84); }
 
  static Type_MISR null_MISR() { return Type_MISR(0); }
 
  static Type_MISR ones_MISR() { return Type_MISR(Type_MISR::Type(-1)); }
 
  //--- MIMR

  Type_MIMR get_MIMR() { return Type_MIMR(rw.template get<uint8>(0x86)); }
 
  void set_MIMR(Type_MIMR value) { rw.set(0x86,value.value); }
 
  Setter<Type_MIMR> to_MIMR() { return Setter<Type_MIMR>(rw,0x86); }
 
  static Type_MIMR null_MIMR() { return Type_MIMR(0); }
 
  static Type_MIMR ones_MIMR() { return Type_MIMR(Type_MIMR::Type(-1)); }
 
  //--- FLOWCR0

  Type_FLOWCR0 get_FLOWCR0() { return Type_FLOWCR0(rw.template get<uint8>(0x98)); }
 
  void set_FLOWCR0(Type_FLOWCR0 value) { rw.set(0x98,value); }
 
  void set_FLOWCR0_null() { rw.set(0x98,Type_FLOWCR0(0)); }
 
  void set_FLOWCR0_ones() { rw.set(0x98,Type_FLOWCR0(-1)); }
 
  //--- FLOWCR1

  Type_FLOWCR1 get_FLOWCR1() { return Type_FLOWCR1(rw.template get<uint8>(0x99)); }
 
  void set_FLOWCR1(Type_FLOWCR1 value) { rw.set(0x99,value.value); }
 
  Setter<Type_FLOWCR1> to_FLOWCR1() { return Setter<Type_FLOWCR1>(rw,0x99); }
 
  static Type_FLOWCR1 null_FLOWCR1() { return Type_FLOWCR1(0); }
 
  static Type_FLOWCR1 ones_FLOWCR1() { return Type_FLOWCR1(Type_FLOWCR1::Type(-1)); }
 
  //--- WOLCFG

  static Type_WOLCFG null_WOLCFG() { return Type_WOLCFG(0); }
 
  static Type_WOLCFG ones_WOLCFG() { return Type_WOLCFG(Type_WOLCFG::Type(-1)); }
 
  //--- WOLCFG_SET

  Type_WOLCFG get_WOLCFG_SET() { return Type_WOLCFG(rw.template get<uint8>(0xA3)); }
 
  void set_WOLCFG_SET(Type_WOLCFG value) { rw.set(0xA3,value.value); }
 
  Setter<Type_WOLCFG> to_WOLCFG_SET() { return Setter<Type_WOLCFG>(rw,0xA3); }
 
  //--- WOLCFG_CLR

  Type_WOLCFG get_WOLCFG_CLR() { return Type_WOLCFG(rw.template get<uint8>(0xA7)); }
 
  void set_WOLCFG_CLR(Type_WOLCFG value) { rw.set(0xA7,value.value); }
 
  Setter<Type_WOLCFG> to_WOLCFG_CLR() { return Setter<Type_WOLCFG>(rw,0xA7); }
 
  //--- PauseTimer

  Type_PauseTimer get_PauseTimer() { return Type_PauseTimer(rw.template get<uint16>(0x9A)); }
 
  void set_PauseTimer(Type_PauseTimer value) { rw.set(0x9A,value); }
 
  void set_PauseTimer_null() { rw.set(0x9A,Type_PauseTimer(0)); }
 
  void set_PauseTimer_ones() { rw.set(0x9A,Type_PauseTimer(-1)); }
 
  //--- SoftT0

  Type_SoftT0 get_SoftT0() { return Type_SoftT0(rw.template get<uint16>(0x9C)); }
 
  void set_SoftT0(Type_SoftT0 value) { rw.set(0x9C,value); }
 
  void set_SoftT0_null() { rw.set(0x9C,Type_SoftT0(0)); }
 
  void set_SoftT0_ones() { rw.set(0x9C,Type_SoftT0(-1)); }
 
  //--- SoftT1

  Type_SoftT1 get_SoftT1() { return Type_SoftT1(rw.template get<uint16>(0x9E)); }
 
  void set_SoftT1(Type_SoftT1 value) { rw.set(0x9E,value); }
 
  void set_SoftT1_null() { rw.set(0x9E,Type_SoftT1(0)); }
 
  void set_SoftT1_ones() { rw.set(0x9E,Type_SoftT1(-1)); }
 
  //--- WOLCR

  static Type_WOLCR null_WOLCR() { return Type_WOLCR(0); }
 
  static Type_WOLCR ones_WOLCR() { return Type_WOLCR(Type_WOLCR::Type(-1)); }
 
  //--- WOLCR_SET

  Type_WOLCR get_WOLCR_SET() { return Type_WOLCR(rw.template get<uint8>(0xA0)); }
 
  void set_WOLCR_SET(Type_WOLCR value) { rw.set(0xA0,value.value); }
 
  Setter<Type_WOLCR> to_WOLCR_SET() { return Setter<Type_WOLCR>(rw,0xA0); }
 
  //--- WOLCR_CLR

  Type_WOLCR get_WOLCR_CLR() { return Type_WOLCR(rw.template get<uint8>(0xA4)); }
 
  void set_WOLCR_CLR(Type_WOLCR value) { rw.set(0xA4,value.value); }
 
  Setter<Type_WOLCR> to_WOLCR_CLR() { return Setter<Type_WOLCR>(rw,0xA4); }
 
  //--- TEST

  static Type_TEST null_TEST() { return Type_TEST(0); }
 
  static Type_TEST ones_TEST() { return Type_TEST(Type_TEST::Type(-1)); }
 
  //--- TEST_SET

  Type_TEST get_TEST_SET() { return Type_TEST(rw.template get<uint8>(0xA2)); }
 
  void set_TEST_SET(Type_TEST value) { rw.set(0xA2,value.value); }
 
  Setter<Type_TEST> to_TEST_SET() { return Setter<Type_TEST>(rw,0xA2); }
 
  //--- TEST_CLR

  Type_TEST get_TEST_CLR() { return Type_TEST(rw.template get<uint8>(0xA6)); }
 
  void set_TEST_CLR(Type_TEST value) { rw.set(0xA6,value.value); }
 
  Setter<Type_TEST> to_TEST_CLR() { return Setter<Type_TEST>(rw,0xA6); }
 
  //--- PWRCSR

  //--- PWRCSR_SET

  Type_PWRCSR get_PWRCSR_SET() { return Type_PWRCSR(rw.template get<uint16>(0xA8)); }
 
  void set_PWRCSR_SET(Type_PWRCSR value) { rw.set(0xA8,value); }
 
  void set_PWRCSR_SET_null() { rw.set(0xA8,Type_PWRCSR(0)); }
 
  void set_PWRCSR_SET_ones() { rw.set(0xA8,Type_PWRCSR(-1)); }
 
  //--- PWRCSR_CLR

  Type_PWRCSR get_PWRCSR_CLR() { return Type_PWRCSR(rw.template get<uint16>(0xAC)); }
 
  void set_PWRCSR_CLR(Type_PWRCSR value) { rw.set(0xAC,value); }
 
  void set_PWRCSR_CLR_null() { rw.set(0xAC,Type_PWRCSR(0)); }
 
  void set_PWRCSR_CLR_ones() { rw.set(0xAC,Type_PWRCSR(-1)); }
 
 };
 
/* struct RxDescBar<RW> */ 

template <class RW>
struct RxDescBar
 {
  RW rw;

  template <class ... TT>
  RxDescBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- RxDescStatus

  Type_RxDescStatus get_RxDescStatus() { return Type_RxDescStatus(rw.template get<uint32>(0x0)); }
 
  void set_RxDescStatus(Type_RxDescStatus value) { rw.set(0x0,value.value); }
 
  Setter<Type_RxDescStatus> to_RxDescStatus() { return Setter<Type_RxDescStatus>(rw,0x0); }
 
  static Type_RxDescStatus null_RxDescStatus() { return Type_RxDescStatus(0); }
 
  static Type_RxDescStatus ones_RxDescStatus() { return Type_RxDescStatus(Type_RxDescStatus::Type(-1)); }
 
  //--- RxDescControl

  Type_RxDescControl get_RxDescControl() { return Type_RxDescControl(rw.template get<uint32>(0x4)); }
 
  void set_RxDescControl(Type_RxDescControl value) { rw.set(0x4,value.value); }
 
  Setter<Type_RxDescControl> to_RxDescControl() { return Setter<Type_RxDescControl>(rw,0x4); }
 
  static Type_RxDescControl null_RxDescControl() { return Type_RxDescControl(0); }
 
  static Type_RxDescControl ones_RxDescControl() { return Type_RxDescControl(Type_RxDescControl::Type(-1)); }
 
  //--- RxDescBuf

  Type_RxDescBuf get_RxDescBuf() { return Type_RxDescBuf(rw.template get<uint32>(0x8)); }
 
  void set_RxDescBuf(Type_RxDescBuf value) { rw.set(0x8,value); }
 
  void set_RxDescBuf_null() { rw.set(0x8,Type_RxDescBuf(0)); }
 
  void set_RxDescBuf_ones() { rw.set(0x8,Type_RxDescBuf(-1)); }
 
  //--- RxDescNext

  Type_RxDescNext get_RxDescNext() { return Type_RxDescNext(rw.template get<uint32>(0xC)); }
 
  void set_RxDescNext(Type_RxDescNext value) { rw.set(0xC,value); }
 
  void set_RxDescNext_null() { rw.set(0xC,Type_RxDescNext(0)); }
 
  void set_RxDescNext_ones() { rw.set(0xC,Type_RxDescNext(-1)); }
 
  //--- RxDescRes1

  Type_RxDescRes1 get_RxDescRes1() { return Type_RxDescRes1(rw.template get<uint32>(0x10)); }
 
  void set_RxDescRes1(Type_RxDescRes1 value) { rw.set(0x10,value); }
 
  void set_RxDescRes1_null() { rw.set(0x10,Type_RxDescRes1(0)); }
 
  void set_RxDescRes1_ones() { rw.set(0x10,Type_RxDescRes1(-1)); }
 
  //--- RxDescRes2

  Type_RxDescRes2 get_RxDescRes2() { return Type_RxDescRes2(rw.template get<uint32>(0x14)); }
 
  void set_RxDescRes2(Type_RxDescRes2 value) { rw.set(0x14,value); }
 
  void set_RxDescRes2_null() { rw.set(0x14,Type_RxDescRes2(0)); }
 
  void set_RxDescRes2_ones() { rw.set(0x14,Type_RxDescRes2(-1)); }
 
  //--- RxDescRes3

  Type_RxDescRes3 get_RxDescRes3() { return Type_RxDescRes3(rw.template get<uint32>(0x18)); }
 
  void set_RxDescRes3(Type_RxDescRes3 value) { rw.set(0x18,value); }
 
  void set_RxDescRes3_null() { rw.set(0x18,Type_RxDescRes3(0)); }
 
  void set_RxDescRes3_ones() { rw.set(0x18,Type_RxDescRes3(-1)); }
 
  //--- RxDescRes4

  Type_RxDescRes4 get_RxDescRes4() { return Type_RxDescRes4(rw.template get<uint32>(0x1C)); }
 
  void set_RxDescRes4(Type_RxDescRes4 value) { rw.set(0x1C,value); }
 
  void set_RxDescRes4_null() { rw.set(0x1C,Type_RxDescRes4(0)); }
 
  void set_RxDescRes4_ones() { rw.set(0x1C,Type_RxDescRes4(-1)); }
 
 };
 
/* struct TxDescBar<RW> */ 

template <class RW>
struct TxDescBar
 {
  RW rw;

  template <class ... TT>
  TxDescBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- TxDescStatus

  Type_TxDescStatus get_TxDescStatus() { return Type_TxDescStatus(rw.template get<uint32>(0x0)); }
 
  void set_TxDescStatus(Type_TxDescStatus value) { rw.set(0x0,value.value); }
 
  Setter<Type_TxDescStatus> to_TxDescStatus() { return Setter<Type_TxDescStatus>(rw,0x0); }
 
  static Type_TxDescStatus null_TxDescStatus() { return Type_TxDescStatus(0); }
 
  static Type_TxDescStatus ones_TxDescStatus() { return Type_TxDescStatus(Type_TxDescStatus::Type(-1)); }
 
  //--- TxDescControl

  Type_TxDescControl get_TxDescControl() { return Type_TxDescControl(rw.template get<uint32>(0x4)); }
 
  void set_TxDescControl(Type_TxDescControl value) { rw.set(0x4,value.value); }
 
  Setter<Type_TxDescControl> to_TxDescControl() { return Setter<Type_TxDescControl>(rw,0x4); }
 
  static Type_TxDescControl null_TxDescControl() { return Type_TxDescControl(0); }
 
  static Type_TxDescControl ones_TxDescControl() { return Type_TxDescControl(Type_TxDescControl::Type(-1)); }
 
  //--- TxDescBuf

  Type_TxDescBuf get_TxDescBuf() { return Type_TxDescBuf(rw.template get<uint32>(0x8)); }
 
  void set_TxDescBuf(Type_TxDescBuf value) { rw.set(0x8,value); }
 
  void set_TxDescBuf_null() { rw.set(0x8,Type_TxDescBuf(0)); }
 
  void set_TxDescBuf_ones() { rw.set(0x8,Type_TxDescBuf(-1)); }
 
  //--- TxDescNext

  Type_TxDescNext get_TxDescNext() { return Type_TxDescNext(rw.template get<uint32>(0xC)); }
 
  void set_TxDescNext(Type_TxDescNext value) { rw.set(0xC,value); }
 
  void set_TxDescNext_null() { rw.set(0xC,Type_TxDescNext(0)); }
 
  void set_TxDescNext_ones() { rw.set(0xC,Type_TxDescNext(-1)); }
 
  //--- TxDescRes1

  Type_TxDescRes1 get_TxDescRes1() { return Type_TxDescRes1(rw.template get<uint32>(0x10)); }
 
  void set_TxDescRes1(Type_TxDescRes1 value) { rw.set(0x10,value); }
 
  void set_TxDescRes1_null() { rw.set(0x10,Type_TxDescRes1(0)); }
 
  void set_TxDescRes1_ones() { rw.set(0x10,Type_TxDescRes1(-1)); }
 
  //--- TxDescRes2

  Type_TxDescRes2 get_TxDescRes2() { return Type_TxDescRes2(rw.template get<uint32>(0x14)); }
 
  void set_TxDescRes2(Type_TxDescRes2 value) { rw.set(0x14,value); }
 
  void set_TxDescRes2_null() { rw.set(0x14,Type_TxDescRes2(0)); }
 
  void set_TxDescRes2_ones() { rw.set(0x14,Type_TxDescRes2(-1)); }
 
  //--- TxDescRes3

  Type_TxDescRes3 get_TxDescRes3() { return Type_TxDescRes3(rw.template get<uint32>(0x18)); }
 
  void set_TxDescRes3(Type_TxDescRes3 value) { rw.set(0x18,value); }
 
  void set_TxDescRes3_null() { rw.set(0x18,Type_TxDescRes3(0)); }
 
  void set_TxDescRes3_ones() { rw.set(0x18,Type_TxDescRes3(-1)); }
 
  //--- TxDescRes4

  Type_TxDescRes4 get_TxDescRes4() { return Type_TxDescRes4(rw.template get<uint32>(0x1C)); }
 
  void set_TxDescRes4(Type_TxDescRes4 value) { rw.set(0x1C,value); }
 
  void set_TxDescRes4_null() { rw.set(0x1C,Type_TxDescRes4(0)); }
 
  void set_TxDescRes4_ones() { rw.set(0x1C,Type_TxDescRes4(-1)); }
 
 };
 
