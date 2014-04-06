/* AM3359.I2C.gen.h */ 

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

 };
 
