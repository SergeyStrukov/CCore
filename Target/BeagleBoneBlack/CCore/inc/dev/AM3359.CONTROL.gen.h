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
 
 };
 
