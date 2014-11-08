/* AM3359.CONTROL.gen.h */ 

/* struct Type_PadMux */ 

enum Bits_PadMux : uint32
 {
  PadMux_NoPullUpDown = 0x00000008,
  PadMux_PullUp       = 0x00000010,
  PadMux_RXEn         = 0x00000020,
  PadMux_SlowSlew     = 0x00000040
 };
 
inline Bits_PadMux operator | (Bits_PadMux a,Bits_PadMux b)
 { return Bits_PadMux(uint32(a)|uint32(b)); }
 
struct Type_PadMux
 {
  typedef uint32 Type;

  Type value;


  explicit Type_PadMux(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_PadMux & setTo(Bar &bar) { bar.set_PadMux(*this); return *this; }
 

  template <class Bar>
  Type_PadMux & setTo(Bar &bar,uint32 ind) { bar.set_PadMux(ind,*this); return *this; }
 

  template <class T>
  Type_PadMux & set(T to) { to(*this); return *this; }
 

  Type_PadMux & setbit(Bits_PadMux bits) { value|=Type(bits); return *this; }
 
  Type_PadMux & setbitIf(bool cond,Bits_PadMux bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_PadMux & clearbit(Bits_PadMux bits) { value&=~Type(bits); return *this; }
 
  Type_PadMux & clearbitIf(bool cond,Bits_PadMux bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_PadMux bits) const { return value&bits; }
 
  bool testbit(Bits_PadMux bits) const { return (value&bits)==Type(bits); }
 

  Type get_MuxMode() const
   {
    return (value>>0)&0x7;
   }
 
  Type_PadMux & set_MuxMode(Type field)
   {
    value=((field&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&PadMux_NoPullUpDown )
      {
       if( first )
         {
          Putobj(out,"NoPullUpDown");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NoPullUpDown");
         }
      }

    if( value&PadMux_PullUp )
      {
       if( first )
         {
          Putobj(out,"PullUp");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PullUp");
         }
      }

    if( value&PadMux_RXEn )
      {
       if( first )
         {
          Putobj(out,"RXEn");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RXEn");
         }
      }

    if( value&PadMux_SlowSlew )
      {
       if( first )
         {
          Putobj(out,"SlowSlew");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SlowSlew");
         }
      }

    if( first )
      {
       Printf(out,"MuxMode(#;)",get_MuxMode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MuxMode(#;)",get_MuxMode());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_EthResetIsolation */ 

enum Bits_EthResetIsolation : uint32
 {
  EthResetIsolation_Enable = 0x00000001
 };
 
inline Bits_EthResetIsolation operator | (Bits_EthResetIsolation a,Bits_EthResetIsolation b)
 { return Bits_EthResetIsolation(uint32(a)|uint32(b)); }
 
struct Type_EthResetIsolation
 {
  typedef uint32 Type;

  Type value;


  explicit Type_EthResetIsolation(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_EthResetIsolation & setTo(Bar &bar) { bar.set_EthResetIsolation(*this); return *this; }
 

  template <class Bar>
  Type_EthResetIsolation & setTo(Bar &bar,uint32 ind) { bar.set_EthResetIsolation(ind,*this); return *this; }
 

  template <class T>
  Type_EthResetIsolation & set(T to) { to(*this); return *this; }
 

  Type_EthResetIsolation & setbit(Bits_EthResetIsolation bits) { value|=Type(bits); return *this; }
 
  Type_EthResetIsolation & setbitIf(bool cond,Bits_EthResetIsolation bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_EthResetIsolation & clearbit(Bits_EthResetIsolation bits) { value&=~Type(bits); return *this; }
 
  Type_EthResetIsolation & clearbitIf(bool cond,Bits_EthResetIsolation bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_EthResetIsolation bits) const { return value&bits; }
 
  bool testbit(Bits_EthResetIsolation bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&EthResetIsolation_Enable )
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
 
/* struct Type_GMIISelect */ 

enum Bits_GMIISelect : uint32
 {
  GMIISelect_Port1RMIIClockInput = 0x00000040,
  GMIISelect_Port2RMIIClockInput = 0x00000080
 };
 
inline Bits_GMIISelect operator | (Bits_GMIISelect a,Bits_GMIISelect b)
 { return Bits_GMIISelect(uint32(a)|uint32(b)); }
 
enum Field_GMIISelect_Port1 : uint32
 {
  GMIISelect_Port1_GMII  = 0x00,
  GMIISelect_Port1_RMII  = 0x01,
  GMIISelect_Port1_RGMII = 0x02
 };
 
struct PrintField_GMIISelect_Port1
 {
  Field_GMIISelect_Port1 field;

  explicit PrintField_GMIISelect_Port1(Field_GMIISelect_Port1 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"GMII"); break;
       case 0x01 : Putobj(out,"RMII"); break;
       case 0x02 : Putobj(out,"RGMII"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_GMIISelect_Port1 GetTextDesc(Field_GMIISelect_Port1 field)
 {
  return PrintField_GMIISelect_Port1(field);
 }
 
enum Field_GMIISelect_Port2 : uint32
 {
  GMIISelect_Port2_GMII  = 0x00,
  GMIISelect_Port2_RMII  = 0x01,
  GMIISelect_Port2_RGMII = 0x02
 };
 
struct PrintField_GMIISelect_Port2
 {
  Field_GMIISelect_Port2 field;

  explicit PrintField_GMIISelect_Port2(Field_GMIISelect_Port2 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"GMII"); break;
       case 0x01 : Putobj(out,"RMII"); break;
       case 0x02 : Putobj(out,"RGMII"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_GMIISelect_Port2 GetTextDesc(Field_GMIISelect_Port2 field)
 {
  return PrintField_GMIISelect_Port2(field);
 }
 
struct Type_GMIISelect
 {
  typedef uint32 Type;

  Type value;


  explicit Type_GMIISelect(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_GMIISelect & setTo(Bar &bar) { bar.set_GMIISelect(*this); return *this; }
 

  template <class Bar>
  Type_GMIISelect & setTo(Bar &bar,uint32 ind) { bar.set_GMIISelect(ind,*this); return *this; }
 

  template <class T>
  Type_GMIISelect & set(T to) { to(*this); return *this; }
 

  Type_GMIISelect & setbit(Bits_GMIISelect bits) { value|=Type(bits); return *this; }
 
  Type_GMIISelect & setbitIf(bool cond,Bits_GMIISelect bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_GMIISelect & clearbit(Bits_GMIISelect bits) { value&=~Type(bits); return *this; }
 
  Type_GMIISelect & clearbitIf(bool cond,Bits_GMIISelect bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_GMIISelect bits) const { return value&bits; }
 
  bool testbit(Bits_GMIISelect bits) const { return (value&bits)==Type(bits); }
 

  Field_GMIISelect_Port1 get_Port1() const
   {
    return Field_GMIISelect_Port1((value>>0)&0x3);
   }
 
  Type_GMIISelect & set_Port1(Field_GMIISelect_Port1 field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Field_GMIISelect_Port2 get_Port2() const
   {
    return Field_GMIISelect_Port2((value>>2)&0x3);
   }
 
  Type_GMIISelect & set_Port2(Field_GMIISelect_Port2 field)
   {
    value=((Type(field)&0x3)<<2)|(value&0xFFFFFFF3);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&GMIISelect_Port1RMIIClockInput )
      {
       if( first )
         {
          Putobj(out,"Port1RMIIClockInput");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port1RMIIClockInput");
         }
      }

    if( value&GMIISelect_Port2RMIIClockInput )
      {
       if( first )
         {
          Putobj(out,"Port2RMIIClockInput");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Port2RMIIClockInput");
         }
      }

    if( first )
      {
       Printf(out,"Port1(#;)",get_Port1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port1(#;)",get_Port1());
      }

    if( first )
      {
       Printf(out,"Port2(#;)",get_Port2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Port2(#;)",get_Port2());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MAC0Hi */ 

typedef uint32 Type_MAC0Hi;

/* type Type_MAC0Lo */ 

typedef uint32 Type_MAC0Lo;

/* type Type_MAC1Hi */ 

typedef uint32 Type_MAC1Hi;

/* type Type_MAC1Lo */ 

typedef uint32 Type_MAC1Lo;

/* struct CONTROLBar<RW> */ 

template <class RW>
struct CONTROLBar
 {
  RW rw;

  template <class ... TT>
  CONTROLBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- EthResetIsolation

  Type_EthResetIsolation get_EthResetIsolation() { return Type_EthResetIsolation(rw.template get<uint32>(0x1000)); }
 
  void set_EthResetIsolation(Type_EthResetIsolation value) { rw.set(0x1000,value.value); }
 
  Setter<Type_EthResetIsolation> to_EthResetIsolation() { return Setter<Type_EthResetIsolation>(rw,0x1000); }
 
  static Type_EthResetIsolation null_EthResetIsolation() { return Type_EthResetIsolation(0); }
 
  static Type_EthResetIsolation ones_EthResetIsolation() { return Type_EthResetIsolation(Type_EthResetIsolation::Type(-1)); }
 
  //--- GMIISelect

  Type_GMIISelect get_GMIISelect() { return Type_GMIISelect(rw.template get<uint32>(0x650)); }
 
  void set_GMIISelect(Type_GMIISelect value) { rw.set(0x650,value.value); }
 
  Setter<Type_GMIISelect> to_GMIISelect() { return Setter<Type_GMIISelect>(rw,0x650); }
 
  static Type_GMIISelect null_GMIISelect() { return Type_GMIISelect(0); }
 
  static Type_GMIISelect ones_GMIISelect() { return Type_GMIISelect(Type_GMIISelect::Type(-1)); }
 
  //--- MAC0Hi

  Type_MAC0Hi get_MAC0Hi() { return Type_MAC0Hi(rw.template get<uint32>(0x630)); }
 
  //--- MAC0Lo

  Type_MAC0Lo get_MAC0Lo() { return Type_MAC0Lo(rw.template get<uint32>(0x634)); }
 
  //--- MAC1Hi

  Type_MAC1Hi get_MAC1Hi() { return Type_MAC1Hi(rw.template get<uint32>(0x638)); }
 
  //--- MAC1Lo

  Type_MAC1Lo get_MAC1Lo() { return Type_MAC1Lo(rw.template get<uint32>(0x63C)); }
 
  //--- PadMux

  static Type_PadMux null_PadMux() { return Type_PadMux(0); }
 
  static Type_PadMux ones_PadMux() { return Type_PadMux(Type_PadMux::Type(-1)); }
 
  //--- Conf_I2C0_SDA

  Type_PadMux get_Conf_I2C0_SDA() { return Type_PadMux(rw.template get<uint32>(0x988)); }
 
  void set_Conf_I2C0_SDA(Type_PadMux value) { rw.set(0x988,value.value); }
 
  Setter<Type_PadMux> to_Conf_I2C0_SDA() { return Setter<Type_PadMux>(rw,0x988); }
 
  //--- Conf_I2C0_SCL

  Type_PadMux get_Conf_I2C0_SCL() { return Type_PadMux(rw.template get<uint32>(0x98C)); }
 
  void set_Conf_I2C0_SCL(Type_PadMux value) { rw.set(0x98C,value.value); }
 
  Setter<Type_PadMux> to_Conf_I2C0_SCL() { return Setter<Type_PadMux>(rw,0x98C); }
 
  //--- Conf_LCD_DATA0

  Type_PadMux get_Conf_LCD_DATA0() { return Type_PadMux(rw.template get<uint32>(0x8A0)); }
 
  void set_Conf_LCD_DATA0(Type_PadMux value) { rw.set(0x8A0,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA0() { return Setter<Type_PadMux>(rw,0x8A0); }
 
  //--- Conf_LCD_DATA1

  Type_PadMux get_Conf_LCD_DATA1() { return Type_PadMux(rw.template get<uint32>(0x8A4)); }
 
  void set_Conf_LCD_DATA1(Type_PadMux value) { rw.set(0x8A4,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA1() { return Setter<Type_PadMux>(rw,0x8A4); }
 
  //--- Conf_LCD_DATA2

  Type_PadMux get_Conf_LCD_DATA2() { return Type_PadMux(rw.template get<uint32>(0x8A8)); }
 
  void set_Conf_LCD_DATA2(Type_PadMux value) { rw.set(0x8A8,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA2() { return Setter<Type_PadMux>(rw,0x8A8); }
 
  //--- Conf_LCD_DATA3

  Type_PadMux get_Conf_LCD_DATA3() { return Type_PadMux(rw.template get<uint32>(0x8AC)); }
 
  void set_Conf_LCD_DATA3(Type_PadMux value) { rw.set(0x8AC,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA3() { return Setter<Type_PadMux>(rw,0x8AC); }
 
  //--- Conf_LCD_DATA4

  Type_PadMux get_Conf_LCD_DATA4() { return Type_PadMux(rw.template get<uint32>(0x8B0)); }
 
  void set_Conf_LCD_DATA4(Type_PadMux value) { rw.set(0x8B0,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA4() { return Setter<Type_PadMux>(rw,0x8B0); }
 
  //--- Conf_LCD_DATA5

  Type_PadMux get_Conf_LCD_DATA5() { return Type_PadMux(rw.template get<uint32>(0x8B4)); }
 
  void set_Conf_LCD_DATA5(Type_PadMux value) { rw.set(0x8B4,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA5() { return Setter<Type_PadMux>(rw,0x8B4); }
 
  //--- Conf_LCD_DATA6

  Type_PadMux get_Conf_LCD_DATA6() { return Type_PadMux(rw.template get<uint32>(0x8B8)); }
 
  void set_Conf_LCD_DATA6(Type_PadMux value) { rw.set(0x8B8,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA6() { return Setter<Type_PadMux>(rw,0x8B8); }
 
  //--- Conf_LCD_DATA7

  Type_PadMux get_Conf_LCD_DATA7() { return Type_PadMux(rw.template get<uint32>(0x8BC)); }
 
  void set_Conf_LCD_DATA7(Type_PadMux value) { rw.set(0x8BC,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA7() { return Setter<Type_PadMux>(rw,0x8BC); }
 
  //--- Conf_LCD_DATA8

  Type_PadMux get_Conf_LCD_DATA8() { return Type_PadMux(rw.template get<uint32>(0x8C0)); }
 
  void set_Conf_LCD_DATA8(Type_PadMux value) { rw.set(0x8C0,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA8() { return Setter<Type_PadMux>(rw,0x8C0); }
 
  //--- Conf_LCD_DATA9

  Type_PadMux get_Conf_LCD_DATA9() { return Type_PadMux(rw.template get<uint32>(0x8C4)); }
 
  void set_Conf_LCD_DATA9(Type_PadMux value) { rw.set(0x8C4,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA9() { return Setter<Type_PadMux>(rw,0x8C4); }
 
  //--- Conf_LCD_DATA10

  Type_PadMux get_Conf_LCD_DATA10() { return Type_PadMux(rw.template get<uint32>(0x8C8)); }
 
  void set_Conf_LCD_DATA10(Type_PadMux value) { rw.set(0x8C8,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA10() { return Setter<Type_PadMux>(rw,0x8C8); }
 
  //--- Conf_LCD_DATA11

  Type_PadMux get_Conf_LCD_DATA11() { return Type_PadMux(rw.template get<uint32>(0x8CC)); }
 
  void set_Conf_LCD_DATA11(Type_PadMux value) { rw.set(0x8CC,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA11() { return Setter<Type_PadMux>(rw,0x8CC); }
 
  //--- Conf_LCD_DATA12

  Type_PadMux get_Conf_LCD_DATA12() { return Type_PadMux(rw.template get<uint32>(0x8D0)); }
 
  void set_Conf_LCD_DATA12(Type_PadMux value) { rw.set(0x8D0,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA12() { return Setter<Type_PadMux>(rw,0x8D0); }
 
  //--- Conf_LCD_DATA13

  Type_PadMux get_Conf_LCD_DATA13() { return Type_PadMux(rw.template get<uint32>(0x8D4)); }
 
  void set_Conf_LCD_DATA13(Type_PadMux value) { rw.set(0x8D4,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA13() { return Setter<Type_PadMux>(rw,0x8D4); }
 
  //--- Conf_LCD_DATA14

  Type_PadMux get_Conf_LCD_DATA14() { return Type_PadMux(rw.template get<uint32>(0x8D8)); }
 
  void set_Conf_LCD_DATA14(Type_PadMux value) { rw.set(0x8D8,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA14() { return Setter<Type_PadMux>(rw,0x8D8); }
 
  //--- Conf_LCD_DATA15

  Type_PadMux get_Conf_LCD_DATA15() { return Type_PadMux(rw.template get<uint32>(0x8DC)); }
 
  void set_Conf_LCD_DATA15(Type_PadMux value) { rw.set(0x8DC,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_DATA15() { return Setter<Type_PadMux>(rw,0x8DC); }
 
  //--- Conf_LCD_VSYNC

  Type_PadMux get_Conf_LCD_VSYNC() { return Type_PadMux(rw.template get<uint32>(0x8E0)); }
 
  void set_Conf_LCD_VSYNC(Type_PadMux value) { rw.set(0x8E0,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_VSYNC() { return Setter<Type_PadMux>(rw,0x8E0); }
 
  //--- Conf_LCD_HSYNC

  Type_PadMux get_Conf_LCD_HSYNC() { return Type_PadMux(rw.template get<uint32>(0x8E4)); }
 
  void set_Conf_LCD_HSYNC(Type_PadMux value) { rw.set(0x8E4,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_HSYNC() { return Setter<Type_PadMux>(rw,0x8E4); }
 
  //--- Conf_LCD_PCLK

  Type_PadMux get_Conf_LCD_PCLK() { return Type_PadMux(rw.template get<uint32>(0x8E8)); }
 
  void set_Conf_LCD_PCLK(Type_PadMux value) { rw.set(0x8E8,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_PCLK() { return Setter<Type_PadMux>(rw,0x8E8); }
 
  //--- Conf_LCD_AC_BIAS_EN

  Type_PadMux get_Conf_LCD_AC_BIAS_EN() { return Type_PadMux(rw.template get<uint32>(0x8EC)); }
 
  void set_Conf_LCD_AC_BIAS_EN(Type_PadMux value) { rw.set(0x8EC,value.value); }
 
  Setter<Type_PadMux> to_Conf_LCD_AC_BIAS_EN() { return Setter<Type_PadMux>(rw,0x8EC); }
 
  //--- Conf_GPMC_A9

  Type_PadMux get_Conf_GPMC_A9() { return Type_PadMux(rw.template get<uint32>(0x864)); }
 
  void set_Conf_GPMC_A9(Type_PadMux value) { rw.set(0x864,value.value); }
 
  Setter<Type_PadMux> to_Conf_GPMC_A9() { return Setter<Type_PadMux>(rw,0x864); }
 
  //--- Conf_MII1_COL

  Type_PadMux get_Conf_MII1_COL() { return Type_PadMux(rw.template get<uint32>(0x908)); }
 
  void set_Conf_MII1_COL(Type_PadMux value) { rw.set(0x908,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_COL() { return Setter<Type_PadMux>(rw,0x908); }
 
  //--- Conf_MII1_CRS

  Type_PadMux get_Conf_MII1_CRS() { return Type_PadMux(rw.template get<uint32>(0x90C)); }
 
  void set_Conf_MII1_CRS(Type_PadMux value) { rw.set(0x90C,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_CRS() { return Setter<Type_PadMux>(rw,0x90C); }
 
  //--- Conf_MII1_RX_ER

  Type_PadMux get_Conf_MII1_RX_ER() { return Type_PadMux(rw.template get<uint32>(0x910)); }
 
  void set_Conf_MII1_RX_ER(Type_PadMux value) { rw.set(0x910,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_ER() { return Setter<Type_PadMux>(rw,0x910); }
 
  //--- Conf_MII1_TX_EN

  Type_PadMux get_Conf_MII1_TX_EN() { return Type_PadMux(rw.template get<uint32>(0x914)); }
 
  void set_Conf_MII1_TX_EN(Type_PadMux value) { rw.set(0x914,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TX_EN() { return Setter<Type_PadMux>(rw,0x914); }
 
  //--- Conf_MII1_RX_DV

  Type_PadMux get_Conf_MII1_RX_DV() { return Type_PadMux(rw.template get<uint32>(0x918)); }
 
  void set_Conf_MII1_RX_DV(Type_PadMux value) { rw.set(0x918,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_DV() { return Setter<Type_PadMux>(rw,0x918); }
 
  //--- Conf_MII1_TXD3

  Type_PadMux get_Conf_MII1_TXD3() { return Type_PadMux(rw.template get<uint32>(0x91C)); }
 
  void set_Conf_MII1_TXD3(Type_PadMux value) { rw.set(0x91C,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD3() { return Setter<Type_PadMux>(rw,0x91C); }
 
  //--- Conf_MII1_TXD2

  Type_PadMux get_Conf_MII1_TXD2() { return Type_PadMux(rw.template get<uint32>(0x920)); }
 
  void set_Conf_MII1_TXD2(Type_PadMux value) { rw.set(0x920,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD2() { return Setter<Type_PadMux>(rw,0x920); }
 
  //--- Conf_MII1_TXD1

  Type_PadMux get_Conf_MII1_TXD1() { return Type_PadMux(rw.template get<uint32>(0x924)); }
 
  void set_Conf_MII1_TXD1(Type_PadMux value) { rw.set(0x924,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD1() { return Setter<Type_PadMux>(rw,0x924); }
 
  //--- Conf_MII1_TXD0

  Type_PadMux get_Conf_MII1_TXD0() { return Type_PadMux(rw.template get<uint32>(0x928)); }
 
  void set_Conf_MII1_TXD0(Type_PadMux value) { rw.set(0x928,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TXD0() { return Setter<Type_PadMux>(rw,0x928); }
 
  //--- Conf_MII1_TX_CLK

  Type_PadMux get_Conf_MII1_TX_CLK() { return Type_PadMux(rw.template get<uint32>(0x92C)); }
 
  void set_Conf_MII1_TX_CLK(Type_PadMux value) { rw.set(0x92C,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_TX_CLK() { return Setter<Type_PadMux>(rw,0x92C); }
 
  //--- Conf_MII1_RX_CLK

  Type_PadMux get_Conf_MII1_RX_CLK() { return Type_PadMux(rw.template get<uint32>(0x930)); }
 
  void set_Conf_MII1_RX_CLK(Type_PadMux value) { rw.set(0x930,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RX_CLK() { return Setter<Type_PadMux>(rw,0x930); }
 
  //--- Conf_MII1_RXD3

  Type_PadMux get_Conf_MII1_RXD3() { return Type_PadMux(rw.template get<uint32>(0x934)); }
 
  void set_Conf_MII1_RXD3(Type_PadMux value) { rw.set(0x934,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD3() { return Setter<Type_PadMux>(rw,0x934); }
 
  //--- Conf_MII1_RXD2

  Type_PadMux get_Conf_MII1_RXD2() { return Type_PadMux(rw.template get<uint32>(0x938)); }
 
  void set_Conf_MII1_RXD2(Type_PadMux value) { rw.set(0x938,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD2() { return Setter<Type_PadMux>(rw,0x938); }
 
  //--- Conf_MII1_RXD1

  Type_PadMux get_Conf_MII1_RXD1() { return Type_PadMux(rw.template get<uint32>(0x93C)); }
 
  void set_Conf_MII1_RXD1(Type_PadMux value) { rw.set(0x93C,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD1() { return Setter<Type_PadMux>(rw,0x93C); }
 
  //--- Conf_MII1_RXD0

  Type_PadMux get_Conf_MII1_RXD0() { return Type_PadMux(rw.template get<uint32>(0x940)); }
 
  void set_Conf_MII1_RXD0(Type_PadMux value) { rw.set(0x940,value.value); }
 
  Setter<Type_PadMux> to_Conf_MII1_RXD0() { return Setter<Type_PadMux>(rw,0x940); }
 
  //--- Conf_RMII1_REF_CLK

  Type_PadMux get_Conf_RMII1_REF_CLK() { return Type_PadMux(rw.template get<uint32>(0x944)); }
 
  void set_Conf_RMII1_REF_CLK(Type_PadMux value) { rw.set(0x944,value.value); }
 
  Setter<Type_PadMux> to_Conf_RMII1_REF_CLK() { return Setter<Type_PadMux>(rw,0x944); }
 
  //--- Conf_MDIO

  Type_PadMux get_Conf_MDIO() { return Type_PadMux(rw.template get<uint32>(0x948)); }
 
  void set_Conf_MDIO(Type_PadMux value) { rw.set(0x948,value.value); }
 
  Setter<Type_PadMux> to_Conf_MDIO() { return Setter<Type_PadMux>(rw,0x948); }
 
  //--- Conf_MDC

  Type_PadMux get_Conf_MDC() { return Type_PadMux(rw.template get<uint32>(0x94C)); }
 
  void set_Conf_MDC(Type_PadMux value) { rw.set(0x94C,value.value); }
 
  Setter<Type_PadMux> to_Conf_MDC() { return Setter<Type_PadMux>(rw,0x94C); }
 
 };
 
