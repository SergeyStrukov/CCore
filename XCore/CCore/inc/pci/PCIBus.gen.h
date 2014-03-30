/* PCIBus.gen.h */ 

/* struct Type_ID */ 

struct Type_ID
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ID(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ID & setTo(Bar &bar) { bar.set_ID(*this); return *this; }
 

  template <class Bar>
  Type_ID & setTo(Bar &bar,uint32 ind) { bar.set_ID(ind,*this); return *this; }
 

  template <class T>
  Type_ID & set(T to) { to(*this); return *this; }
 

  Type get_VendorID() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_ID & set_VendorID(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  Type get_DeviceID() const
   {
    return (value>>16)&0xFFFF;
   }
 
  Type_ID & set_DeviceID(Type field)
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
       Printf(out,"VendorID(#;)",get_VendorID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VendorID(#;)",get_VendorID());
      }

    if( first )
      {
       Printf(out,"DeviceID(#;)",get_DeviceID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DeviceID(#;)",get_DeviceID());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_StatusCommand */ 

enum Bits_StatusCommand : uint32
 {
  StatusCommand_IOEnable          = 0x00000001,
  StatusCommand_MemEnable         = 0x00000002,
  StatusCommand_BusMasterEnable   = 0x00000004,
  StatusCommand_SpecEnable        = 0x00000008,
  StatusCommand_InvWriteEnable    = 0x00000010,
  StatusCommand_VGASnoopEnable    = 0x00000020,
  StatusCommand_ParityErrorEnable = 0x00000040,
  StatusCommand_SteppingEnable    = 0x00000080,
  StatusCommand_SysErrorEnable    = 0x00000100,
  StatusCommand_BacktoBackEnable  = 0x00000200,
  StatusCommand_CapsList          = 0x00100000,
  StatusCommand_Cap66MHz          = 0x00200000,
  StatusCommand_CapBacktoBack     = 0x00800000,
  StatusCommand_MasterParityError = 0x01000000,
  StatusCommand_SigTargetAbort    = 0x08000000,
  StatusCommand_TargetAbort       = 0x10000000,
  StatusCommand_MasterAbort       = 0x20000000,
  StatusCommand_SysError          = 0x40000000,
  StatusCommand_ParityError       = 0x80000000
 };
 
inline Bits_StatusCommand operator | (Bits_StatusCommand a,Bits_StatusCommand b)
 { return Bits_StatusCommand(uint32(a)|uint32(b)); }
 
enum Field_StatusCommand_DevSel : uint32
 {
  StatusCommand_DevSel_Fast   = 0x00,
  StatusCommand_DevSel_Medium = 0x01,
  StatusCommand_DevSel_Slow   = 0x02
 };
 
struct PrintField_StatusCommand_DevSel
 {
  Field_StatusCommand_DevSel field;

  explicit PrintField_StatusCommand_DevSel(Field_StatusCommand_DevSel field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Fast"); break;
       case 0x01 : Putobj(out,"Medium"); break;
       case 0x02 : Putobj(out,"Slow"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_StatusCommand_DevSel GetTextDesc(Field_StatusCommand_DevSel field)
 {
  return PrintField_StatusCommand_DevSel(field);
 }
 
struct Type_StatusCommand
 {
  typedef uint32 Type;

  Type value;


  explicit Type_StatusCommand(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_StatusCommand & setTo(Bar &bar) { bar.set_StatusCommand(*this); return *this; }
 

  template <class Bar>
  Type_StatusCommand & setTo(Bar &bar,uint32 ind) { bar.set_StatusCommand(ind,*this); return *this; }
 

  template <class T>
  Type_StatusCommand & set(T to) { to(*this); return *this; }
 

  Type_StatusCommand & setbit(Bits_StatusCommand bits) { value|=Type(bits); return *this; }
 
  Type_StatusCommand & setbitIf(bool cond,Bits_StatusCommand bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_StatusCommand & clearbit(Bits_StatusCommand bits) { value&=~Type(bits); return *this; }
 
  Type_StatusCommand & clearbitIf(bool cond,Bits_StatusCommand bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_StatusCommand bits) const { return value&bits; }
 
  bool testbit(Bits_StatusCommand bits) const { return (value&bits)==Type(bits); }
 

  Field_StatusCommand_DevSel get_DevSel() const
   {
    return Field_StatusCommand_DevSel((value>>25)&0x3);
   }
 
  Type_StatusCommand & set_DevSel(Field_StatusCommand_DevSel field)
   {
    value=((Type(field)&0x3)<<25)|(value&0xF9FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&StatusCommand_IOEnable )
      {
       if( first )
         {
          Putobj(out,"IOEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IOEnable");
         }
      }

    if( value&StatusCommand_MemEnable )
      {
       if( first )
         {
          Putobj(out,"MemEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MemEnable");
         }
      }

    if( value&StatusCommand_BusMasterEnable )
      {
       if( first )
         {
          Putobj(out,"BusMasterEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BusMasterEnable");
         }
      }

    if( value&StatusCommand_SpecEnable )
      {
       if( first )
         {
          Putobj(out,"SpecEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SpecEnable");
         }
      }

    if( value&StatusCommand_InvWriteEnable )
      {
       if( first )
         {
          Putobj(out,"InvWriteEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InvWriteEnable");
         }
      }

    if( value&StatusCommand_VGASnoopEnable )
      {
       if( first )
         {
          Putobj(out,"VGASnoopEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"VGASnoopEnable");
         }
      }

    if( value&StatusCommand_ParityErrorEnable )
      {
       if( first )
         {
          Putobj(out,"ParityErrorEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ParityErrorEnable");
         }
      }

    if( value&StatusCommand_SteppingEnable )
      {
       if( first )
         {
          Putobj(out,"SteppingEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SteppingEnable");
         }
      }

    if( value&StatusCommand_SysErrorEnable )
      {
       if( first )
         {
          Putobj(out,"SysErrorEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SysErrorEnable");
         }
      }

    if( value&StatusCommand_BacktoBackEnable )
      {
       if( first )
         {
          Putobj(out,"BacktoBackEnable");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BacktoBackEnable");
         }
      }

    if( value&StatusCommand_CapsList )
      {
       if( first )
         {
          Putobj(out,"CapsList");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CapsList");
         }
      }

    if( value&StatusCommand_Cap66MHz )
      {
       if( first )
         {
          Putobj(out,"Cap66MHz");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Cap66MHz");
         }
      }

    if( value&StatusCommand_CapBacktoBack )
      {
       if( first )
         {
          Putobj(out,"CapBacktoBack");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CapBacktoBack");
         }
      }

    if( value&StatusCommand_MasterParityError )
      {
       if( first )
         {
          Putobj(out,"MasterParityError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MasterParityError");
         }
      }

    if( value&StatusCommand_SigTargetAbort )
      {
       if( first )
         {
          Putobj(out,"SigTargetAbort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SigTargetAbort");
         }
      }

    if( value&StatusCommand_TargetAbort )
      {
       if( first )
         {
          Putobj(out,"TargetAbort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TargetAbort");
         }
      }

    if( value&StatusCommand_MasterAbort )
      {
       if( first )
         {
          Putobj(out,"MasterAbort");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MasterAbort");
         }
      }

    if( value&StatusCommand_SysError )
      {
       if( first )
         {
          Putobj(out,"SysError");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SysError");
         }
      }

    if( value&StatusCommand_ParityError )
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

    if( first )
      {
       Printf(out,"DevSel(#;)",get_DevSel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DevSel(#;)",get_DevSel());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ClassRevision */ 

struct Type_ClassRevision
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ClassRevision(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ClassRevision & setTo(Bar &bar) { bar.set_ClassRevision(*this); return *this; }
 

  template <class Bar>
  Type_ClassRevision & setTo(Bar &bar,uint32 ind) { bar.set_ClassRevision(ind,*this); return *this; }
 

  template <class T>
  Type_ClassRevision & set(T to) { to(*this); return *this; }
 

  Type get_RevisionID() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_ClassRevision & set_RevisionID(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_IfClass() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_ClassRevision & set_IfClass(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_SubClass() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_ClassRevision & set_SubClass(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_BaseClass() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_ClassRevision & set_BaseClass(Type field)
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
       Printf(out,"RevisionID(#;)",get_RevisionID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RevisionID(#;)",get_RevisionID());
      }

    if( first )
      {
       Printf(out,"IfClass(#;)",get_IfClass());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IfClass(#;)",get_IfClass());
      }

    if( first )
      {
       Printf(out,"SubClass(#;)",get_SubClass());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SubClass(#;)",get_SubClass());
      }

    if( first )
      {
       Printf(out,"BaseClass(#;)",get_BaseClass());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BaseClass(#;)",get_BaseClass());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Prop */ 

enum Bits_Prop : uint32
 {
  Prop_MultiFunc = 0x00800000,
  Prop_BISTStart = 0x40000000,
  Prop_BISTCap   = 0x80000000
 };
 
inline Bits_Prop operator | (Bits_Prop a,Bits_Prop b)
 { return Bits_Prop(uint32(a)|uint32(b)); }
 
enum Field_Prop_Type : uint32
 {
  Prop_Type_Type0  = 0x00,
  Prop_Type_Bridge = 0x01,
  Prop_Type_Card   = 0x02
 };
 
struct PrintField_Prop_Type
 {
  Field_Prop_Type field;

  explicit PrintField_Prop_Type(Field_Prop_Type field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"Type0"); break;
       case 0x01 : Putobj(out,"Bridge"); break;
       case 0x02 : Putobj(out,"Card"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_Prop_Type GetTextDesc(Field_Prop_Type field)
 {
  return PrintField_Prop_Type(field);
 }
 
struct Type_Prop
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Prop(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Prop & setTo(Bar &bar) { bar.set_Prop(*this); return *this; }
 

  template <class Bar>
  Type_Prop & setTo(Bar &bar,uint32 ind) { bar.set_Prop(ind,*this); return *this; }
 

  template <class T>
  Type_Prop & set(T to) { to(*this); return *this; }
 

  Type_Prop & setbit(Bits_Prop bits) { value|=Type(bits); return *this; }
 
  Type_Prop & setbitIf(bool cond,Bits_Prop bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Prop & clearbit(Bits_Prop bits) { value&=~Type(bits); return *this; }
 
  Type_Prop & clearbitIf(bool cond,Bits_Prop bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Prop bits) const { return value&bits; }
 
  bool testbit(Bits_Prop bits) const { return (value&bits)==Type(bits); }
 

  Type get_CacheLineSize() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Prop & set_CacheLineSize(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_Latency() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_Prop & set_Latency(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Field_Prop_Type get_Type() const
   {
    return Field_Prop_Type((value>>16)&0x7F);
   }
 
  Type_Prop & set_Type(Field_Prop_Type field)
   {
    value=((Type(field)&0x7F)<<16)|(value&0xFF80FFFF);

    return *this;
   }
 

  Type get_BISTCode() const
   {
    return (value>>24)&0xF;
   }
 
  Type_Prop & set_BISTCode(Type field)
   {
    value=((field&0xF)<<24)|(value&0xF0FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Prop_MultiFunc )
      {
       if( first )
         {
          Putobj(out,"MultiFunc");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MultiFunc");
         }
      }

    if( value&Prop_BISTStart )
      {
       if( first )
         {
          Putobj(out,"BISTStart");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BISTStart");
         }
      }

    if( value&Prop_BISTCap )
      {
       if( first )
         {
          Putobj(out,"BISTCap");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"BISTCap");
         }
      }

    if( first )
      {
       Printf(out,"CacheLineSize(#;)",get_CacheLineSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CacheLineSize(#;)",get_CacheLineSize());
      }

    if( first )
      {
       Printf(out,"Latency(#;)",get_Latency());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Latency(#;)",get_Latency());
      }

    if( first )
      {
       Printf(out,"Type(#;)",get_Type());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Type(#;)",get_Type());
      }

    if( first )
      {
       Printf(out,"BISTCode(#;)",get_BISTCode());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BISTCode(#;)",get_BISTCode());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_Bar */ 

typedef uint32 Type_Bar;

/* struct Type_SubID */ 

struct Type_SubID
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SubID(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SubID & setTo(Bar &bar) { bar.set_SubID(*this); return *this; }
 

  template <class Bar>
  Type_SubID & setTo(Bar &bar,uint32 ind) { bar.set_SubID(ind,*this); return *this; }
 

  template <class T>
  Type_SubID & set(T to) { to(*this); return *this; }
 

  Type get_SubVendorID() const
   {
    return (value>>0)&0xFFFF;
   }
 
  Type_SubID & set_SubVendorID(Type field)
   {
    value=((field&0xFFFF)<<0)|(value&0xFFFF0000);

    return *this;
   }
 

  Type get_SubID() const
   {
    return (value>>16)&0xFFFF;
   }
 
  Type_SubID & set_SubID(Type field)
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
       Printf(out,"SubVendorID(#;)",get_SubVendorID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SubVendorID(#;)",get_SubVendorID());
      }

    if( first )
      {
       Printf(out,"SubID(#;)",get_SubID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SubID(#;)",get_SubID());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Caps */ 

struct Type_Caps
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Caps(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Caps & setTo(Bar &bar) { bar.set_Caps(*this); return *this; }
 

  template <class Bar>
  Type_Caps & setTo(Bar &bar,uint32 ind) { bar.set_Caps(ind,*this); return *this; }
 

  template <class T>
  Type_Caps & set(T to) { to(*this); return *this; }
 

  Type get_Offset() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Caps & set_Offset(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"Offset(#;)",get_Offset());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Offset(#;)",get_Offset());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Prop2 */ 

struct Type_Prop2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Prop2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Prop2 & setTo(Bar &bar) { bar.set_Prop2(*this); return *this; }
 

  template <class Bar>
  Type_Prop2 & setTo(Bar &bar,uint32 ind) { bar.set_Prop2(ind,*this); return *this; }
 

  template <class T>
  Type_Prop2 & set(T to) { to(*this); return *this; }
 

  Type get_IntLine() const
   {
    return (value>>0)&0xFF;
   }
 
  Type_Prop2 & set_IntLine(Type field)
   {
    value=((field&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_IntPin() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_Prop2 & set_IntPin(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_MinGnt() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_Prop2 & set_MinGnt(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Type get_MaxLatency() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_Prop2 & set_MaxLatency(Type field)
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
       Printf(out,"IntLine(#;)",get_IntLine());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IntLine(#;)",get_IntLine());
      }

    if( first )
      {
       Printf(out,"IntPin(#;)",get_IntPin());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IntPin(#;)",get_IntPin());
      }

    if( first )
      {
       Printf(out,"MinGnt(#;)",get_MinGnt());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MinGnt(#;)",get_MinGnt());
      }

    if( first )
      {
       Printf(out,"MaxLatency(#;)",get_MaxLatency());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MaxLatency(#;)",get_MaxLatency());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Cap */ 

enum Bits_Cap : uint32
 {
  Cap_MsiEn  = 0x00010000,
  Cap_MsiA64 = 0x00800000
 };
 
inline Bits_Cap operator | (Bits_Cap a,Bits_Cap b)
 { return Bits_Cap(uint32(a)|uint32(b)); }
 
enum Field_Cap_ID : uint32
 {
  Cap_ID_MSI = 0x05
 };
 
struct PrintField_Cap_ID
 {
  Field_Cap_ID field;

  explicit PrintField_Cap_ID(Field_Cap_ID field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x05 : Putobj(out,"MSI"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_Cap_ID GetTextDesc(Field_Cap_ID field)
 {
  return PrintField_Cap_ID(field);
 }
 
struct Type_Cap
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Cap(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Cap & setTo(Bar &bar) { bar.set_Cap(*this); return *this; }
 

  template <class Bar>
  Type_Cap & setTo(Bar &bar,uint32 ind) { bar.set_Cap(ind,*this); return *this; }
 

  template <class T>
  Type_Cap & set(T to) { to(*this); return *this; }
 

  Type_Cap & setbit(Bits_Cap bits) { value|=Type(bits); return *this; }
 
  Type_Cap & setbitIf(bool cond,Bits_Cap bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Cap & clearbit(Bits_Cap bits) { value&=~Type(bits); return *this; }
 
  Type_Cap & clearbitIf(bool cond,Bits_Cap bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Cap bits) const { return value&bits; }
 
  bool testbit(Bits_Cap bits) const { return (value&bits)==Type(bits); }
 

  Field_Cap_ID get_ID() const
   {
    return Field_Cap_ID((value>>0)&0xFF);
   }
 
  Type_Cap & set_ID(Field_Cap_ID field)
   {
    value=((Type(field)&0xFF)<<0)|(value&0xFFFFFF00);

    return *this;
   }
 

  Type get_Next() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_Cap & set_Next(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_MsiMultiCap() const
   {
    return (value>>17)&0x7;
   }
 
  Type_Cap & set_MsiMultiCap(Type field)
   {
    value=((field&0x7)<<17)|(value&0xFFF1FFFF);

    return *this;
   }
 

  Type get_MsiMultiEn() const
   {
    return (value>>20)&0x7;
   }
 
  Type_Cap & set_MsiMultiEn(Type field)
   {
    value=((field&0x7)<<20)|(value&0xFF8FFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Cap_MsiEn )
      {
       if( first )
         {
          Putobj(out,"MsiEn");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MsiEn");
         }
      }

    if( value&Cap_MsiA64 )
      {
       if( first )
         {
          Putobj(out,"MsiA64");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"MsiA64");
         }
      }

    if( first )
      {
       Printf(out,"ID(#;)",get_ID());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ID(#;)",get_ID());
      }

    if( first )
      {
       Printf(out,"Next(#;)",get_Next());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Next(#;)",get_Next());
      }

    if( first )
      {
       Printf(out,"MsiMultiCap(#;)",get_MsiMultiCap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MsiMultiCap(#;)",get_MsiMultiCap());
      }

    if( first )
      {
       Printf(out,"MsiMultiEn(#;)",get_MsiMultiEn());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MsiMultiEn(#;)",get_MsiMultiEn());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct CfgBar<RW> */ 

template <class RW>
struct CfgBar
 {
  RW rw;

  template <class ... TT>
  CfgBar(TT && ... tt) : rw( std::forward<TT>(tt)... ) {}
 
  template <class T>
  struct Setter
   {
    RW &rw;
    uint32 address;

    Setter(RW &rw_,uint32 address_) : rw(rw_),address(address_) {}

    void operator () (T value) { rw.set(address,value.value); }
   };

  //--- ID

  Type_ID get_ID() { return Type_ID(rw.template get<uint32>(0x0)); }
 
  void set_ID(Type_ID value) { rw.set(0x0,value.value); }
 
  Setter<Type_ID> to_ID() { return Setter<Type_ID>(rw,0x0); }
 
  static Type_ID null_ID() { return Type_ID(0); }
 
  static Type_ID ones_ID() { return Type_ID(Type_ID::Type(-1)); }
 
  //--- StatusCommand

  Type_StatusCommand get_StatusCommand() { return Type_StatusCommand(rw.template get<uint32>(0x4)); }
 
  void set_StatusCommand(Type_StatusCommand value) { rw.set(0x4,value.value); }
 
  Setter<Type_StatusCommand> to_StatusCommand() { return Setter<Type_StatusCommand>(rw,0x4); }
 
  static Type_StatusCommand null_StatusCommand() { return Type_StatusCommand(0); }
 
  static Type_StatusCommand ones_StatusCommand() { return Type_StatusCommand(Type_StatusCommand::Type(-1)); }
 
  //--- ClassRevision

  Type_ClassRevision get_ClassRevision() { return Type_ClassRevision(rw.template get<uint32>(0x8)); }
 
  void set_ClassRevision(Type_ClassRevision value) { rw.set(0x8,value.value); }
 
  Setter<Type_ClassRevision> to_ClassRevision() { return Setter<Type_ClassRevision>(rw,0x8); }
 
  static Type_ClassRevision null_ClassRevision() { return Type_ClassRevision(0); }
 
  static Type_ClassRevision ones_ClassRevision() { return Type_ClassRevision(Type_ClassRevision::Type(-1)); }
 
  //--- Prop

  Type_Prop get_Prop() { return Type_Prop(rw.template get<uint32>(0xC)); }
 
  void set_Prop(Type_Prop value) { rw.set(0xC,value.value); }
 
  Setter<Type_Prop> to_Prop() { return Setter<Type_Prop>(rw,0xC); }
 
  static Type_Prop null_Prop() { return Type_Prop(0); }
 
  static Type_Prop ones_Prop() { return Type_Prop(Type_Prop::Type(-1)); }
 
  //--- Bar

  Type_Bar get_Bar(uint32 ind) { return Type_Bar(rw.template get<uint32>(0x10 +ind*4)); }
 
  void set_Bar(uint32 ind,Type_Bar value) { rw.set(0x10 +ind*4,value); }
 
  void set_Bar_null(uint32 ind) { rw.set(0x10 +ind*4,Type_Bar(0)); }
 
  void set_Bar_ones(uint32 ind) { rw.set(0x10 +ind*4,Type_Bar(-1)); }
 
  //--- SubID

  Type_SubID get_SubID() { return Type_SubID(rw.template get<uint32>(0x28)); }
 
  void set_SubID(Type_SubID value) { rw.set(0x28,value.value); }
 
  Setter<Type_SubID> to_SubID() { return Setter<Type_SubID>(rw,0x28); }
 
  static Type_SubID null_SubID() { return Type_SubID(0); }
 
  static Type_SubID ones_SubID() { return Type_SubID(Type_SubID::Type(-1)); }
 
  //--- Caps

  Type_Caps get_Caps() { return Type_Caps(rw.template get<uint32>(0x34)); }
 
  void set_Caps(Type_Caps value) { rw.set(0x34,value.value); }
 
  Setter<Type_Caps> to_Caps() { return Setter<Type_Caps>(rw,0x34); }
 
  static Type_Caps null_Caps() { return Type_Caps(0); }
 
  static Type_Caps ones_Caps() { return Type_Caps(Type_Caps::Type(-1)); }
 
  //--- Prop2

  Type_Prop2 get_Prop2() { return Type_Prop2(rw.template get<uint32>(0x3C)); }
 
  void set_Prop2(Type_Prop2 value) { rw.set(0x3C,value.value); }
 
  Setter<Type_Prop2> to_Prop2() { return Setter<Type_Prop2>(rw,0x3C); }
 
  static Type_Prop2 null_Prop2() { return Type_Prop2(0); }
 
  static Type_Prop2 ones_Prop2() { return Type_Prop2(Type_Prop2::Type(-1)); }
 
 };
 
