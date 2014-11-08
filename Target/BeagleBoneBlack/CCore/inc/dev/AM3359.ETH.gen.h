/* AM3359.ETH.gen.h */ 

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

 };
 
/* struct PortBar<RW> */ 

template <class RW>
struct PortBar
 {
  RW rw;

  template <class ... TT>
  PortBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

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
 
/* struct RAMStateBar<RW> */ 

template <class RW>
struct RAMStateBar
 {
  RW rw;

  template <class ... TT>
  RAMStateBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

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
 
