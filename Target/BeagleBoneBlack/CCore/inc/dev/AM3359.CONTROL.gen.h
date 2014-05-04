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
 
 };
 
