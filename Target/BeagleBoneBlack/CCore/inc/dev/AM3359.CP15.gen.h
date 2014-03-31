/* AM3359.CP15.gen.h */ 

/* struct Type_CPSR */ 

enum Bits_CPSR : uint32
 {
  CPSR_T = 0x00000020,
  CPSR_F = 0x00000040,
  CPSR_I = 0x00000080,
  CPSR_A = 0x00000100,
  CPSR_E = 0x00000200,
  CPSR_J = 0x01000000,
  CPSR_Q = 0x08000000,
  CPSR_V = 0x10000000,
  CPSR_C = 0x20000000,
  CPSR_N = 0x40000000,
  CPSR_Z = 0x80000000
 };
 
inline Bits_CPSR operator | (Bits_CPSR a,Bits_CPSR b)
 { return Bits_CPSR(uint32(a)|uint32(b)); }
 
enum Field_CPSR_Mode : uint32
 {
  CPSR_Mode_User       = 0x10,
  CPSR_Mode_FIQ        = 0x11,
  CPSR_Mode_IRQ        = 0x12,
  CPSR_Mode_Supervisor = 0x13,
  CPSR_Mode_Monitor    = 0x16,
  CPSR_Mode_Abort      = 0x17,
  CPSR_Mode_Hypervisor = 0x1A,
  CPSR_Mode_Undefine   = 0x1B,
  CPSR_Mode_System     = 0x1F
 };
 
struct PrintField_CPSR_Mode
 {
  Field_CPSR_Mode field;

  explicit PrintField_CPSR_Mode(Field_CPSR_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x10 : Putobj(out,"User"); break;
       case 0x11 : Putobj(out,"FIQ"); break;
       case 0x12 : Putobj(out,"IRQ"); break;
       case 0x13 : Putobj(out,"Supervisor"); break;
       case 0x16 : Putobj(out,"Monitor"); break;
       case 0x17 : Putobj(out,"Abort"); break;
       case 0x1A : Putobj(out,"Hypervisor"); break;
       case 0x1B : Putobj(out,"Undefine"); break;
       case 0x1F : Putobj(out,"System"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CPSR_Mode GetTextDesc(Field_CPSR_Mode field)
 {
  return PrintField_CPSR_Mode(field);
 }
 
struct Type_CPSR
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CPSR(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CPSR & setTo(Bar &bar) { bar.set_CPSR(*this); return *this; }
 

  template <class Bar>
  Type_CPSR & setTo(Bar &bar,uint32 ind) { bar.set_CPSR(ind,*this); return *this; }
 

  template <class T>
  Type_CPSR & set(T to) { to(*this); return *this; }
 

  Type_CPSR & setbit(Bits_CPSR bits) { value|=Type(bits); return *this; }
 
  Type_CPSR & setbitIf(bool cond,Bits_CPSR bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CPSR & clearbit(Bits_CPSR bits) { value&=~Type(bits); return *this; }
 
  Type_CPSR & clearbitIf(bool cond,Bits_CPSR bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CPSR bits) const { return value&bits; }
 
  bool testbit(Bits_CPSR bits) const { return (value&bits)==Type(bits); }
 

  Field_CPSR_Mode get_Mode() const
   {
    return Field_CPSR_Mode((value>>0)&0x1F);
   }
 
  Type_CPSR & set_Mode(Field_CPSR_Mode field)
   {
    value=((Type(field)&0x1F)<<0)|(value&0xFFFFFFE0);

    return *this;
   }
 

  Type get_IThi() const
   {
    return (value>>10)&0x3F;
   }
 
  Type_CPSR & set_IThi(Type field)
   {
    value=((field&0x3F)<<10)|(value&0xFFFF03FF);

    return *this;
   }
 

  Type get_GE() const
   {
    return (value>>16)&0xF;
   }
 
  Type_CPSR & set_GE(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_ITlo() const
   {
    return (value>>25)&0x3;
   }
 
  Type_CPSR & set_ITlo(Type field)
   {
    value=((field&0x3)<<25)|(value&0xF9FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CPSR_T )
      {
       if( first )
         {
          Putobj(out,"T");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"T");
         }
      }

    if( value&CPSR_F )
      {
       if( first )
         {
          Putobj(out,"F");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"F");
         }
      }

    if( value&CPSR_I )
      {
       if( first )
         {
          Putobj(out,"I");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"I");
         }
      }

    if( value&CPSR_A )
      {
       if( first )
         {
          Putobj(out,"A");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"A");
         }
      }

    if( value&CPSR_E )
      {
       if( first )
         {
          Putobj(out,"E");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"E");
         }
      }

    if( value&CPSR_J )
      {
       if( first )
         {
          Putobj(out,"J");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"J");
         }
      }

    if( value&CPSR_Q )
      {
       if( first )
         {
          Putobj(out,"Q");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Q");
         }
      }

    if( value&CPSR_V )
      {
       if( first )
         {
          Putobj(out,"V");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"V");
         }
      }

    if( value&CPSR_C )
      {
       if( first )
         {
          Putobj(out,"C");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"C");
         }
      }

    if( value&CPSR_N )
      {
       if( first )
         {
          Putobj(out,"N");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"N");
         }
      }

    if( value&CPSR_Z )
      {
       if( first )
         {
          Putobj(out,"Z");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Z");
         }
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
       Printf(out,"IThi(#;)",get_IThi());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IThi(#;)",get_IThi());
      }

    if( first )
      {
       Printf(out,"GE(#;)",get_GE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"GE(#;)",get_GE());
      }

    if( first )
      {
       Printf(out,"ITlo(#;)",get_ITlo());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ITlo(#;)",get_ITlo());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MainID */ 

struct Type_MainID
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MainID(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MainID & setTo(Bar &bar) { bar.set_MainID(*this); return *this; }
 

  template <class Bar>
  Type_MainID & setTo(Bar &bar,uint32 ind) { bar.set_MainID(ind,*this); return *this; }
 

  template <class T>
  Type_MainID & set(T to) { to(*this); return *this; }
 

  Type get_Revision() const
   {
    return (value>>0)&0xF;
   }
 
  Type_MainID & set_Revision(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_PartNumber() const
   {
    return (value>>4)&0xFFF;
   }
 
  Type_MainID & set_PartNumber(Type field)
   {
    value=((field&0xFFF)<<4)|(value&0xFFFF000F);

    return *this;
   }
 

  Type get_Arch() const
   {
    return (value>>16)&0xF;
   }
 
  Type_MainID & set_Arch(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_Variant() const
   {
    return (value>>20)&0xF;
   }
 
  Type_MainID & set_Variant(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  Type get_Implementor() const
   {
    return (value>>24)&0xFF;
   }
 
  Type_MainID & set_Implementor(Type field)
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
       Printf(out,"Revision(#;)",get_Revision());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Revision(#;)",get_Revision());
      }

    if( first )
      {
       Printf(out,"PartNumber(#;)",get_PartNumber());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PartNumber(#;)",get_PartNumber());
      }

    if( first )
      {
       Printf(out,"Arch(#;)",get_Arch());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Arch(#;)",get_Arch());
      }

    if( first )
      {
       Printf(out,"Variant(#;)",get_Variant());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Variant(#;)",get_Variant());
      }

    if( first )
      {
       Printf(out,"Implementor(#;)",get_Implementor());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Implementor(#;)",get_Implementor());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CacheType */ 

struct Type_CacheType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CacheType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CacheType & setTo(Bar &bar) { bar.set_CacheType(*this); return *this; }
 

  template <class Bar>
  Type_CacheType & setTo(Bar &bar,uint32 ind) { bar.set_CacheType(ind,*this); return *this; }
 

  template <class T>
  Type_CacheType & set(T to) { to(*this); return *this; }
 

  Type get_IMinLine() const
   {
    return (value>>0)&0xF;
   }
 
  Type_CacheType & set_IMinLine(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_L1IPolicy() const
   {
    return (value>>14)&0x3;
   }
 
  Type_CacheType & set_L1IPolicy(Type field)
   {
    value=((field&0x3)<<14)|(value&0xFFFF3FFF);

    return *this;
   }
 

  Type get_DMinLine() const
   {
    return (value>>16)&0xF;
   }
 
  Type_CacheType & set_DMinLine(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_WBGranule() const
   {
    return (value>>24)&0xF;
   }
 
  Type_CacheType & set_WBGranule(Type field)
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
       Printf(out,"IMinLine(#;)",get_IMinLine());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IMinLine(#;)",get_IMinLine());
      }

    if( first )
      {
       Printf(out,"L1IPolicy(#;)",get_L1IPolicy());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1IPolicy(#;)",get_L1IPolicy());
      }

    if( first )
      {
       Printf(out,"DMinLine(#;)",get_DMinLine());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DMinLine(#;)",get_DMinLine());
      }

    if( first )
      {
       Printf(out,"WBGranule(#;)",get_WBGranule());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WBGranule(#;)",get_WBGranule());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TCMType */ 

typedef uint32 Type_TCMType;

/* struct Type_TLBType */ 

enum Bits_TLBType : uint32
 {
  TLBType_U = 0x00000001
 };
 
inline Bits_TLBType operator | (Bits_TLBType a,Bits_TLBType b)
 { return Bits_TLBType(uint32(a)|uint32(b)); }
 
struct Type_TLBType
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TLBType(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TLBType & setTo(Bar &bar) { bar.set_TLBType(*this); return *this; }
 

  template <class Bar>
  Type_TLBType & setTo(Bar &bar,uint32 ind) { bar.set_TLBType(ind,*this); return *this; }
 

  template <class T>
  Type_TLBType & set(T to) { to(*this); return *this; }
 

  Type_TLBType & setbit(Bits_TLBType bits) { value|=Type(bits); return *this; }
 
  Type_TLBType & setbitIf(bool cond,Bits_TLBType bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TLBType & clearbit(Bits_TLBType bits) { value&=~Type(bits); return *this; }
 
  Type_TLBType & clearbitIf(bool cond,Bits_TLBType bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TLBType bits) const { return value&bits; }
 
  bool testbit(Bits_TLBType bits) const { return (value&bits)==Type(bits); }
 

  Type get_DLSize() const
   {
    return (value>>8)&0xFF;
   }
 
  Type_TLBType & set_DLSize(Type field)
   {
    value=((field&0xFF)<<8)|(value&0xFFFF00FF);

    return *this;
   }
 

  Type get_ILSize() const
   {
    return (value>>16)&0xFF;
   }
 
  Type_TLBType & set_ILSize(Type field)
   {
    value=((field&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TLBType_U )
      {
       if( first )
         {
          Putobj(out,"U");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"U");
         }
      }

    if( first )
      {
       Printf(out,"DLSize(#;)",get_DLSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DLSize(#;)",get_DLSize());
      }

    if( first )
      {
       Printf(out,"ILSize(#;)",get_ILSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ILSize(#;)",get_ILSize());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_MultiprocessorID */ 

typedef uint32 Type_MultiprocessorID;

/* struct Type_ProcessorFeature0 */ 

struct Type_ProcessorFeature0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ProcessorFeature0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ProcessorFeature0 & setTo(Bar &bar) { bar.set_ProcessorFeature0(*this); return *this; }
 

  template <class Bar>
  Type_ProcessorFeature0 & setTo(Bar &bar,uint32 ind) { bar.set_ProcessorFeature0(ind,*this); return *this; }
 

  template <class T>
  Type_ProcessorFeature0 & set(T to) { to(*this); return *this; }
 

  Type get_ARM() const
   {
    return (value>>0)&0xF;
   }
 
  Type_ProcessorFeature0 & set_ARM(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_Thumb() const
   {
    return (value>>4)&0xF;
   }
 
  Type_ProcessorFeature0 & set_Thumb(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_Jazelle() const
   {
    return (value>>8)&0xF;
   }
 
  Type_ProcessorFeature0 & set_Jazelle(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_ThumbEE() const
   {
    return (value>>12)&0xF;
   }
 
  Type_ProcessorFeature0 & set_ThumbEE(Type field)
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
       Printf(out,"ARM(#;)",get_ARM());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ARM(#;)",get_ARM());
      }

    if( first )
      {
       Printf(out,"Thumb(#;)",get_Thumb());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Thumb(#;)",get_Thumb());
      }

    if( first )
      {
       Printf(out,"Jazelle(#;)",get_Jazelle());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Jazelle(#;)",get_Jazelle());
      }

    if( first )
      {
       Printf(out,"ThumbEE(#;)",get_ThumbEE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ThumbEE(#;)",get_ThumbEE());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_ProcessorFeature1 */ 

struct Type_ProcessorFeature1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_ProcessorFeature1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_ProcessorFeature1 & setTo(Bar &bar) { bar.set_ProcessorFeature1(*this); return *this; }
 

  template <class Bar>
  Type_ProcessorFeature1 & setTo(Bar &bar,uint32 ind) { bar.set_ProcessorFeature1(ind,*this); return *this; }
 

  template <class T>
  Type_ProcessorFeature1 & set(T to) { to(*this); return *this; }
 

  Type get_ProgModel() const
   {
    return (value>>0)&0xF;
   }
 
  Type_ProcessorFeature1 & set_ProgModel(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_SecurityExt() const
   {
    return (value>>4)&0xF;
   }
 
  Type_ProcessorFeature1 & set_SecurityExt(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_MCTLProgModel() const
   {
    return (value>>8)&0xF;
   }
 
  Type_ProcessorFeature1 & set_MCTLProgModel(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"ProgModel(#;)",get_ProgModel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ProgModel(#;)",get_ProgModel());
      }

    if( first )
      {
       Printf(out,"SecurityExt(#;)",get_SecurityExt());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SecurityExt(#;)",get_SecurityExt());
      }

    if( first )
      {
       Printf(out,"MCTLProgModel(#;)",get_MCTLProgModel());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MCTLProgModel(#;)",get_MCTLProgModel());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DebugFeature */ 

struct Type_DebugFeature
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DebugFeature(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DebugFeature & setTo(Bar &bar) { bar.set_DebugFeature(*this); return *this; }
 

  template <class Bar>
  Type_DebugFeature & setTo(Bar &bar,uint32 ind) { bar.set_DebugFeature(ind,*this); return *this; }
 

  template <class T>
  Type_DebugFeature & set(T to) { to(*this); return *this; }
 

  Type get_CoreCopr() const
   {
    return (value>>0)&0xF;
   }
 
  Type_DebugFeature & set_CoreCopr(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_SecureCopr() const
   {
    return (value>>4)&0xF;
   }
 
  Type_DebugFeature & set_SecureCopr(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_CoreMemMap() const
   {
    return (value>>8)&0xF;
   }
 
  Type_DebugFeature & set_CoreMemMap(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_TraceCopr() const
   {
    return (value>>12)&0xF;
   }
 
  Type_DebugFeature & set_TraceCopr(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Type get_TraceMemMap() const
   {
    return (value>>16)&0xF;
   }
 
  Type_DebugFeature & set_TraceMemMap(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_MCTLMemMap() const
   {
    return (value>>20)&0xF;
   }
 
  Type_DebugFeature & set_MCTLMemMap(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"CoreCopr(#;)",get_CoreCopr());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CoreCopr(#;)",get_CoreCopr());
      }

    if( first )
      {
       Printf(out,"SecureCopr(#;)",get_SecureCopr());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SecureCopr(#;)",get_SecureCopr());
      }

    if( first )
      {
       Printf(out,"CoreMemMap(#;)",get_CoreMemMap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CoreMemMap(#;)",get_CoreMemMap());
      }

    if( first )
      {
       Printf(out,"TraceCopr(#;)",get_TraceCopr());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TraceCopr(#;)",get_TraceCopr());
      }

    if( first )
      {
       Printf(out,"TraceMemMap(#;)",get_TraceMemMap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TraceMemMap(#;)",get_TraceMemMap());
      }

    if( first )
      {
       Printf(out,"MCTLMemMap(#;)",get_MCTLMemMap());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MCTLMemMap(#;)",get_MCTLMemMap());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_AuxFeature */ 

typedef uint32 Type_AuxFeature;

/* struct Type_MemoryFeature0 */ 

struct Type_MemoryFeature0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MemoryFeature0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MemoryFeature0 & setTo(Bar &bar) { bar.set_MemoryFeature0(*this); return *this; }
 

  template <class Bar>
  Type_MemoryFeature0 & setTo(Bar &bar,uint32 ind) { bar.set_MemoryFeature0(ind,*this); return *this; }
 

  template <class T>
  Type_MemoryFeature0 & set(T to) { to(*this); return *this; }
 

  Type get_VMSA() const
   {
    return (value>>0)&0xF;
   }
 
  Type_MemoryFeature0 & set_VMSA(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_PMSA() const
   {
    return (value>>4)&0xF;
   }
 
  Type_MemoryFeature0 & set_PMSA(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_CacheCoherence() const
   {
    return (value>>8)&0xF;
   }
 
  Type_MemoryFeature0 & set_CacheCoherence(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_OuterShareable() const
   {
    return (value>>12)&0xF;
   }
 
  Type_MemoryFeature0 & set_OuterShareable(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Type get_TCM() const
   {
    return (value>>16)&0xF;
   }
 
  Type_MemoryFeature0 & set_TCM(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_AuxControl() const
   {
    return (value>>20)&0xF;
   }
 
  Type_MemoryFeature0 & set_AuxControl(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  Type get_FCSE() const
   {
    return (value>>24)&0xF;
   }
 
  Type_MemoryFeature0 & set_FCSE(Type field)
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
       Printf(out,"VMSA(#;)",get_VMSA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"VMSA(#;)",get_VMSA());
      }

    if( first )
      {
       Printf(out,"PMSA(#;)",get_PMSA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"PMSA(#;)",get_PMSA());
      }

    if( first )
      {
       Printf(out,"CacheCoherence(#;)",get_CacheCoherence());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CacheCoherence(#;)",get_CacheCoherence());
      }

    if( first )
      {
       Printf(out,"OuterShareable(#;)",get_OuterShareable());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"OuterShareable(#;)",get_OuterShareable());
      }

    if( first )
      {
       Printf(out,"TCM(#;)",get_TCM());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TCM(#;)",get_TCM());
      }

    if( first )
      {
       Printf(out,"AuxControl(#;)",get_AuxControl());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"AuxControl(#;)",get_AuxControl());
      }

    if( first )
      {
       Printf(out,"FCSE(#;)",get_FCSE());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"FCSE(#;)",get_FCSE());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SecureConfig */ 

enum Bits_SecureConfig : uint32
 {
  SecureConfig_NS  = 0x00000001,
  SecureConfig_IRQ = 0x00000002,
  SecureConfig_FIQ = 0x00000004,
  SecureConfig_EA  = 0x00000008,
  SecureConfig_FW  = 0x00000010,
  SecureConfig_AW  = 0x00000020
 };
 
inline Bits_SecureConfig operator | (Bits_SecureConfig a,Bits_SecureConfig b)
 { return Bits_SecureConfig(uint32(a)|uint32(b)); }
 
struct Type_SecureConfig
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SecureConfig(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SecureConfig & setTo(Bar &bar) { bar.set_SecureConfig(*this); return *this; }
 

  template <class Bar>
  Type_SecureConfig & setTo(Bar &bar,uint32 ind) { bar.set_SecureConfig(ind,*this); return *this; }
 

  template <class T>
  Type_SecureConfig & set(T to) { to(*this); return *this; }
 

  Type_SecureConfig & setbit(Bits_SecureConfig bits) { value|=Type(bits); return *this; }
 
  Type_SecureConfig & setbitIf(bool cond,Bits_SecureConfig bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SecureConfig & clearbit(Bits_SecureConfig bits) { value&=~Type(bits); return *this; }
 
  Type_SecureConfig & clearbitIf(bool cond,Bits_SecureConfig bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SecureConfig bits) const { return value&bits; }
 
  bool testbit(Bits_SecureConfig bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SecureConfig_NS )
      {
       if( first )
         {
          Putobj(out,"NS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NS");
         }
      }

    if( value&SecureConfig_IRQ )
      {
       if( first )
         {
          Putobj(out,"IRQ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IRQ");
         }
      }

    if( value&SecureConfig_FIQ )
      {
       if( first )
         {
          Putobj(out,"FIQ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FIQ");
         }
      }

    if( value&SecureConfig_EA )
      {
       if( first )
         {
          Putobj(out,"EA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EA");
         }
      }

    if( value&SecureConfig_FW )
      {
       if( first )
         {
          Putobj(out,"FW");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FW");
         }
      }

    if( value&SecureConfig_AW )
      {
       if( first )
         {
          Putobj(out,"AW");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AW");
         }
      }

    if( first ) out.put('0');
   }
 };
 
