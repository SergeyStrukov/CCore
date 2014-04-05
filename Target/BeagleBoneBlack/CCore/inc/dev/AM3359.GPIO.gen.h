/* AM3359.GPIO.gen.h */ 

/* type Type_OutEnable */ 

typedef uint32 Type_OutEnable;

/* type Type_Out */ 

typedef uint32 Type_Out;

/* type Type_ClearOut */ 

typedef uint32 Type_ClearOut;

/* type Type_SetOut */ 

typedef uint32 Type_SetOut;

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
 
 };
 
