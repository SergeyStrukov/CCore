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
 
/* struct Type_MemoryFeature1 */ 

struct Type_MemoryFeature1
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MemoryFeature1(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MemoryFeature1 & setTo(Bar &bar) { bar.set_MemoryFeature1(*this); return *this; }
 

  template <class Bar>
  Type_MemoryFeature1 & setTo(Bar &bar,uint32 ind) { bar.set_MemoryFeature1(ind,*this); return *this; }
 

  template <class T>
  Type_MemoryFeature1 & set(T to) { to(*this); return *this; }
 

  Type get_L1HMVA() const
   {
    return (value>>0)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1HMVA(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_L1UMVA() const
   {
    return (value>>4)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1UMVA(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_L1HSW() const
   {
    return (value>>8)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1HSW(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_L1USW() const
   {
    return (value>>12)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1USW(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Type get_L1H() const
   {
    return (value>>16)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1H(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_L1U() const
   {
    return (value>>20)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1U(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  Type get_L1Test() const
   {
    return (value>>24)&0xF;
   }
 
  Type_MemoryFeature1 & set_L1Test(Type field)
   {
    value=((field&0xF)<<24)|(value&0xF0FFFFFF);

    return *this;
   }
 

  Type get_BTB() const
   {
    return (value>>28)&0xF;
   }
 
  Type_MemoryFeature1 & set_BTB(Type field)
   {
    value=((field&0xF)<<28)|(value&0xFFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"L1HMVA(#;)",get_L1HMVA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1HMVA(#;)",get_L1HMVA());
      }

    if( first )
      {
       Printf(out,"L1UMVA(#;)",get_L1UMVA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1UMVA(#;)",get_L1UMVA());
      }

    if( first )
      {
       Printf(out,"L1HSW(#;)",get_L1HSW());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1HSW(#;)",get_L1HSW());
      }

    if( first )
      {
       Printf(out,"L1USW(#;)",get_L1USW());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1USW(#;)",get_L1USW());
      }

    if( first )
      {
       Printf(out,"L1H(#;)",get_L1H());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1H(#;)",get_L1H());
      }

    if( first )
      {
       Printf(out,"L1U(#;)",get_L1U());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1U(#;)",get_L1U());
      }

    if( first )
      {
       Printf(out,"L1Test(#;)",get_L1Test());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1Test(#;)",get_L1Test());
      }

    if( first )
      {
       Printf(out,"BTB(#;)",get_BTB());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BTB(#;)",get_BTB());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MemoryFeature2 */ 

struct Type_MemoryFeature2
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MemoryFeature2(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MemoryFeature2 & setTo(Bar &bar) { bar.set_MemoryFeature2(*this); return *this; }
 

  template <class Bar>
  Type_MemoryFeature2 & setTo(Bar &bar,uint32 ind) { bar.set_MemoryFeature2(ind,*this); return *this; }
 

  template <class T>
  Type_MemoryFeature2 & set(T to) { to(*this); return *this; }
 

  Type get_L1HFP() const
   {
    return (value>>0)&0xF;
   }
 
  Type_MemoryFeature2 & set_L1HFP(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_L1HBP() const
   {
    return (value>>4)&0xF;
   }
 
  Type_MemoryFeature2 & set_L1HBP(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_L1H() const
   {
    return (value>>8)&0xF;
   }
 
  Type_MemoryFeature2 & set_L1H(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_TLBH() const
   {
    return (value>>12)&0xF;
   }
 
  Type_MemoryFeature2 & set_TLBH(Type field)
   {
    value=((field&0xF)<<12)|(value&0xFFFF0FFF);

    return *this;
   }
 

  Type get_TLBU() const
   {
    return (value>>16)&0xF;
   }
 
  Type_MemoryFeature2 & set_TLBU(Type field)
   {
    value=((field&0xF)<<16)|(value&0xFFF0FFFF);

    return *this;
   }
 

  Type get_MB() const
   {
    return (value>>20)&0xF;
   }
 
  Type_MemoryFeature2 & set_MB(Type field)
   {
    value=((field&0xF)<<20)|(value&0xFF0FFFFF);

    return *this;
   }
 

  Type get_WFI() const
   {
    return (value>>24)&0xF;
   }
 
  Type_MemoryFeature2 & set_WFI(Type field)
   {
    value=((field&0xF)<<24)|(value&0xF0FFFFFF);

    return *this;
   }
 

  Type get_HAF() const
   {
    return (value>>28)&0xF;
   }
 
  Type_MemoryFeature2 & set_HAF(Type field)
   {
    value=((field&0xF)<<28)|(value&0xFFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"L1HFP(#;)",get_L1HFP());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1HFP(#;)",get_L1HFP());
      }

    if( first )
      {
       Printf(out,"L1HBP(#;)",get_L1HBP());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1HBP(#;)",get_L1HBP());
      }

    if( first )
      {
       Printf(out,"L1H(#;)",get_L1H());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"L1H(#;)",get_L1H());
      }

    if( first )
      {
       Printf(out,"TLBH(#;)",get_TLBH());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TLBH(#;)",get_TLBH());
      }

    if( first )
      {
       Printf(out,"TLBU(#;)",get_TLBU());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"TLBU(#;)",get_TLBU());
      }

    if( first )
      {
       Printf(out,"MB(#;)",get_MB());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MB(#;)",get_MB());
      }

    if( first )
      {
       Printf(out,"WFI(#;)",get_WFI());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"WFI(#;)",get_WFI());
      }

    if( first )
      {
       Printf(out,"HAF(#;)",get_HAF());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HAF(#;)",get_HAF());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_MemoryFeature3 */ 

struct Type_MemoryFeature3
 {
  typedef uint32 Type;

  Type value;


  explicit Type_MemoryFeature3(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_MemoryFeature3 & setTo(Bar &bar) { bar.set_MemoryFeature3(*this); return *this; }
 

  template <class Bar>
  Type_MemoryFeature3 & setTo(Bar &bar,uint32 ind) { bar.set_MemoryFeature3(ind,*this); return *this; }
 

  template <class T>
  Type_MemoryFeature3 & set(T to) { to(*this); return *this; }
 

  Type get_HCMVA() const
   {
    return (value>>0)&0xF;
   }
 
  Type_MemoryFeature3 & set_HCMVA(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_HCSW() const
   {
    return (value>>4)&0xF;
   }
 
  Type_MemoryFeature3 & set_HCSW(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  Type get_BP() const
   {
    return (value>>8)&0xF;
   }
 
  Type_MemoryFeature3 & set_BP(Type field)
   {
    value=((field&0xF)<<8)|(value&0xFFFFF0FF);

    return *this;
   }
 

  Type get_SS() const
   {
    return (value>>28)&0xF;
   }
 
  Type_MemoryFeature3 & set_SS(Type field)
   {
    value=((field&0xF)<<28)|(value&0xFFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"HCMVA(#;)",get_HCMVA());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HCMVA(#;)",get_HCMVA());
      }

    if( first )
      {
       Printf(out,"HCSW(#;)",get_HCSW());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"HCSW(#;)",get_HCSW());
      }

    if( first )
      {
       Printf(out,"BP(#;)",get_BP());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"BP(#;)",get_BP());
      }

    if( first )
      {
       Printf(out,"SS(#;)",get_SS());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SS(#;)",get_SS());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CacheLevelID */ 

struct Type_CacheLevelID
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CacheLevelID(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CacheLevelID & setTo(Bar &bar) { bar.set_CacheLevelID(*this); return *this; }
 

  template <class Bar>
  Type_CacheLevelID & setTo(Bar &bar,uint32 ind) { bar.set_CacheLevelID(ind,*this); return *this; }
 

  template <class T>
  Type_CacheLevelID & set(T to) { to(*this); return *this; }
 

  Type get_CL1() const
   {
    return (value>>0)&0x7;
   }
 
  Type_CacheLevelID & set_CL1(Type field)
   {
    value=((field&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Type get_CL2() const
   {
    return (value>>3)&0x7;
   }
 
  Type_CacheLevelID & set_CL2(Type field)
   {
    value=((field&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Type get_CL3() const
   {
    return (value>>6)&0x7;
   }
 
  Type_CacheLevelID & set_CL3(Type field)
   {
    value=((field&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  Type get_CL4() const
   {
    return (value>>9)&0x7;
   }
 
  Type_CacheLevelID & set_CL4(Type field)
   {
    value=((field&0x7)<<9)|(value&0xFFFFF1FF);

    return *this;
   }
 

  Type get_CL5() const
   {
    return (value>>12)&0x7;
   }
 
  Type_CacheLevelID & set_CL5(Type field)
   {
    value=((field&0x7)<<12)|(value&0xFFFF8FFF);

    return *this;
   }
 

  Type get_CL6() const
   {
    return (value>>15)&0x7;
   }
 
  Type_CacheLevelID & set_CL6(Type field)
   {
    value=((field&0x7)<<15)|(value&0xFFFC7FFF);

    return *this;
   }
 

  Type get_CL7() const
   {
    return (value>>18)&0x7;
   }
 
  Type_CacheLevelID & set_CL7(Type field)
   {
    value=((field&0x7)<<18)|(value&0xFFE3FFFF);

    return *this;
   }
 

  Type get_CL8() const
   {
    return (value>>21)&0x7;
   }
 
  Type_CacheLevelID & set_CL8(Type field)
   {
    value=((field&0x7)<<21)|(value&0xFF1FFFFF);

    return *this;
   }
 

  Type get_LOC() const
   {
    return (value>>24)&0x7;
   }
 
  Type_CacheLevelID & set_LOC(Type field)
   {
    value=((field&0x7)<<24)|(value&0xF8FFFFFF);

    return *this;
   }
 

  Type get_LOU() const
   {
    return (value>>27)&0x7;
   }
 
  Type_CacheLevelID & set_LOU(Type field)
   {
    value=((field&0x7)<<27)|(value&0xC7FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"CL1(#;)",get_CL1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL1(#;)",get_CL1());
      }

    if( first )
      {
       Printf(out,"CL2(#;)",get_CL2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL2(#;)",get_CL2());
      }

    if( first )
      {
       Printf(out,"CL3(#;)",get_CL3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL3(#;)",get_CL3());
      }

    if( first )
      {
       Printf(out,"CL4(#;)",get_CL4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL4(#;)",get_CL4());
      }

    if( first )
      {
       Printf(out,"CL5(#;)",get_CL5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL5(#;)",get_CL5());
      }

    if( first )
      {
       Printf(out,"CL6(#;)",get_CL6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL6(#;)",get_CL6());
      }

    if( first )
      {
       Printf(out,"CL7(#;)",get_CL7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL7(#;)",get_CL7());
      }

    if( first )
      {
       Printf(out,"CL8(#;)",get_CL8());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CL8(#;)",get_CL8());
      }

    if( first )
      {
       Printf(out,"LOC(#;)",get_LOC());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LOC(#;)",get_LOC());
      }

    if( first )
      {
       Printf(out,"LOU(#;)",get_LOU());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LOU(#;)",get_LOU());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CacheSizeID */ 

enum Bits_CacheSizeID : uint32
 {
  CacheSizeID_WA = 0x10000000,
  CacheSizeID_RA = 0x20000000,
  CacheSizeID_WB = 0x40000000,
  CacheSizeID_WT = 0x80000000
 };
 
inline Bits_CacheSizeID operator | (Bits_CacheSizeID a,Bits_CacheSizeID b)
 { return Bits_CacheSizeID(uint32(a)|uint32(b)); }
 
struct Type_CacheSizeID
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CacheSizeID(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CacheSizeID & setTo(Bar &bar) { bar.set_CacheSizeID(*this); return *this; }
 

  template <class Bar>
  Type_CacheSizeID & setTo(Bar &bar,uint32 ind) { bar.set_CacheSizeID(ind,*this); return *this; }
 

  template <class T>
  Type_CacheSizeID & set(T to) { to(*this); return *this; }
 

  Type_CacheSizeID & setbit(Bits_CacheSizeID bits) { value|=Type(bits); return *this; }
 
  Type_CacheSizeID & setbitIf(bool cond,Bits_CacheSizeID bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CacheSizeID & clearbit(Bits_CacheSizeID bits) { value&=~Type(bits); return *this; }
 
  Type_CacheSizeID & clearbitIf(bool cond,Bits_CacheSizeID bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CacheSizeID bits) const { return value&bits; }
 
  bool testbit(Bits_CacheSizeID bits) const { return (value&bits)==Type(bits); }
 

  Type get_LineSize() const
   {
    return (value>>0)&0x7;
   }
 
  Type_CacheSizeID & set_LineSize(Type field)
   {
    value=((field&0x7)<<0)|(value&0xFFFFFFF8);

    return *this;
   }
 

  Type get_Ass() const
   {
    return (value>>3)&0x3FF;
   }
 
  Type_CacheSizeID & set_Ass(Type field)
   {
    value=((field&0x3FF)<<3)|(value&0xFFFFE007);

    return *this;
   }
 

  Type get_Sets() const
   {
    return (value>>13)&0x7FFF;
   }
 
  Type_CacheSizeID & set_Sets(Type field)
   {
    value=((field&0x7FFF)<<13)|(value&0xF0001FFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CacheSizeID_WA )
      {
       if( first )
         {
          Putobj(out,"WA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WA");
         }
      }

    if( value&CacheSizeID_RA )
      {
       if( first )
         {
          Putobj(out,"RA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"RA");
         }
      }

    if( value&CacheSizeID_WB )
      {
       if( first )
         {
          Putobj(out,"WB");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WB");
         }
      }

    if( value&CacheSizeID_WT )
      {
       if( first )
         {
          Putobj(out,"WT");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WT");
         }
      }

    if( first )
      {
       Printf(out,"LineSize(#;)",get_LineSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"LineSize(#;)",get_LineSize());
      }

    if( first )
      {
       Printf(out,"Ass(#;)",get_Ass());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Ass(#;)",get_Ass());
      }

    if( first )
      {
       Printf(out,"Sets(#;)",get_Sets());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Sets(#;)",get_Sets());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CacheSizeSel */ 

enum Bits_CacheSizeSel : uint32
 {
  CacheSizeSel_InD = 0x00000001
 };
 
inline Bits_CacheSizeSel operator | (Bits_CacheSizeSel a,Bits_CacheSizeSel b)
 { return Bits_CacheSizeSel(uint32(a)|uint32(b)); }
 
struct Type_CacheSizeSel
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CacheSizeSel(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CacheSizeSel & setTo(Bar &bar) { bar.set_CacheSizeSel(*this); return *this; }
 

  template <class Bar>
  Type_CacheSizeSel & setTo(Bar &bar,uint32 ind) { bar.set_CacheSizeSel(ind,*this); return *this; }
 

  template <class T>
  Type_CacheSizeSel & set(T to) { to(*this); return *this; }
 

  Type_CacheSizeSel & setbit(Bits_CacheSizeSel bits) { value|=Type(bits); return *this; }
 
  Type_CacheSizeSel & setbitIf(bool cond,Bits_CacheSizeSel bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CacheSizeSel & clearbit(Bits_CacheSizeSel bits) { value&=~Type(bits); return *this; }
 
  Type_CacheSizeSel & clearbitIf(bool cond,Bits_CacheSizeSel bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CacheSizeSel bits) const { return value&bits; }
 
  bool testbit(Bits_CacheSizeSel bits) const { return (value&bits)==Type(bits); }
 

  Type get_Level() const
   {
    return (value>>1)&0x7;
   }
 
  Type_CacheSizeSel & set_Level(Type field)
   {
    value=((field&0x7)<<1)|(value&0xFFFFFFF1);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CacheSizeSel_InD )
      {
       if( first )
         {
          Putobj(out,"InD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"InD");
         }
      }

    if( first )
      {
       Printf(out,"Level(#;)",get_Level());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Level(#;)",get_Level());
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
 
/* struct Type_DataFaultStatus */ 

enum Bits_DataFaultStatus : uint32
 {
  DataFaultStatus_S  = 0x00000400,
  DataFaultStatus_W  = 0x00000800,
  DataFaultStatus_SD = 0x00001000
 };
 
inline Bits_DataFaultStatus operator | (Bits_DataFaultStatus a,Bits_DataFaultStatus b)
 { return Bits_DataFaultStatus(uint32(a)|uint32(b)); }
 
struct Type_DataFaultStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DataFaultStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DataFaultStatus & setTo(Bar &bar) { bar.set_DataFaultStatus(*this); return *this; }
 

  template <class Bar>
  Type_DataFaultStatus & setTo(Bar &bar,uint32 ind) { bar.set_DataFaultStatus(ind,*this); return *this; }
 

  template <class T>
  Type_DataFaultStatus & set(T to) { to(*this); return *this; }
 

  Type_DataFaultStatus & setbit(Bits_DataFaultStatus bits) { value|=Type(bits); return *this; }
 
  Type_DataFaultStatus & setbitIf(bool cond,Bits_DataFaultStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_DataFaultStatus & clearbit(Bits_DataFaultStatus bits) { value&=~Type(bits); return *this; }
 
  Type_DataFaultStatus & clearbitIf(bool cond,Bits_DataFaultStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_DataFaultStatus bits) const { return value&bits; }
 
  bool testbit(Bits_DataFaultStatus bits) const { return (value&bits)==Type(bits); }
 

  Type get_Status() const
   {
    return (value>>0)&0xF;
   }
 
  Type_DataFaultStatus & set_Status(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Type get_Domain() const
   {
    return (value>>4)&0xF;
   }
 
  Type_DataFaultStatus & set_Domain(Type field)
   {
    value=((field&0xF)<<4)|(value&0xFFFFFF0F);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&DataFaultStatus_S )
      {
       if( first )
         {
          Putobj(out,"S");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"S");
         }
      }

    if( value&DataFaultStatus_W )
      {
       if( first )
         {
          Putobj(out,"W");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"W");
         }
      }

    if( value&DataFaultStatus_SD )
      {
       if( first )
         {
          Putobj(out,"SD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SD");
         }
      }

    if( first )
      {
       Printf(out,"Status(#;)",get_Status());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Status(#;)",get_Status());
      }

    if( first )
      {
       Printf(out,"Domain(#;)",get_Domain());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Domain(#;)",get_Domain());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_InstructionFaultStatus */ 

enum Bits_InstructionFaultStatus : uint32
 {
  InstructionFaultStatus_S  = 0x00000400,
  InstructionFaultStatus_SD = 0x00001000
 };
 
inline Bits_InstructionFaultStatus operator | (Bits_InstructionFaultStatus a,Bits_InstructionFaultStatus b)
 { return Bits_InstructionFaultStatus(uint32(a)|uint32(b)); }
 
struct Type_InstructionFaultStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_InstructionFaultStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_InstructionFaultStatus & setTo(Bar &bar) { bar.set_InstructionFaultStatus(*this); return *this; }
 

  template <class Bar>
  Type_InstructionFaultStatus & setTo(Bar &bar,uint32 ind) { bar.set_InstructionFaultStatus(ind,*this); return *this; }
 

  template <class T>
  Type_InstructionFaultStatus & set(T to) { to(*this); return *this; }
 

  Type_InstructionFaultStatus & setbit(Bits_InstructionFaultStatus bits) { value|=Type(bits); return *this; }
 
  Type_InstructionFaultStatus & setbitIf(bool cond,Bits_InstructionFaultStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_InstructionFaultStatus & clearbit(Bits_InstructionFaultStatus bits) { value&=~Type(bits); return *this; }
 
  Type_InstructionFaultStatus & clearbitIf(bool cond,Bits_InstructionFaultStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_InstructionFaultStatus bits) const { return value&bits; }
 
  bool testbit(Bits_InstructionFaultStatus bits) const { return (value&bits)==Type(bits); }
 

  Type get_Status() const
   {
    return (value>>0)&0xF;
   }
 
  Type_InstructionFaultStatus & set_Status(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&InstructionFaultStatus_S )
      {
       if( first )
         {
          Putobj(out,"S");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"S");
         }
      }

    if( value&InstructionFaultStatus_SD )
      {
       if( first )
         {
          Putobj(out,"SD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SD");
         }
      }

    if( first )
      {
       Printf(out,"Status(#;)",get_Status());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Status(#;)",get_Status());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_DataFaultAddress */ 

typedef uint32 Type_DataFaultAddress;

/* type Type_InstructionFaultAddress */ 

typedef uint32 Type_InstructionFaultAddress;

/* struct Type_Control */ 

enum Bits_Control : uint32
 {
  Control_M    = 0x00000001,
  Control_A    = 0x00000002,
  Control_C    = 0x00000004,
  Control_Z    = 0x00000800,
  Control_I    = 0x00001000,
  Control_V    = 0x00002000,
  Control_EE   = 0x02000000,
  Control_NMFI = 0x08000000,
  Control_TRE  = 0x10000000,
  Control_AFE  = 0x20000000,
  Control_TE   = 0x40000000
 };
 
inline Bits_Control operator | (Bits_Control a,Bits_Control b)
 { return Bits_Control(uint32(a)|uint32(b)); }
 
enum Field_Control_SBO : uint32
 {
  Control_SBO_Ones = 0x0F
 };
 
struct PrintField_Control_SBO
 {
  Field_Control_SBO field;

  explicit PrintField_Control_SBO(Field_Control_SBO field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x0F : Putobj(out,"Ones"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_Control_SBO GetTextDesc(Field_Control_SBO field)
 {
  return PrintField_Control_SBO(field);
 }
 
struct Type_Control
 {
  typedef uint32 Type;

  Type value;


  explicit Type_Control(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_Control & setTo(Bar &bar) { bar.set_Control(*this); return *this; }
 

  template <class Bar>
  Type_Control & setTo(Bar &bar,uint32 ind) { bar.set_Control(ind,*this); return *this; }
 

  template <class T>
  Type_Control & set(T to) { to(*this); return *this; }
 

  Type_Control & setbit(Bits_Control bits) { value|=Type(bits); return *this; }
 
  Type_Control & setbitIf(bool cond,Bits_Control bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_Control & clearbit(Bits_Control bits) { value&=~Type(bits); return *this; }
 
  Type_Control & clearbitIf(bool cond,Bits_Control bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_Control bits) const { return value&bits; }
 
  bool testbit(Bits_Control bits) const { return (value&bits)==Type(bits); }
 

  Field_Control_SBO get_SBO() const
   {
    return Field_Control_SBO((value>>3)&0xF);
   }
 
  Type_Control & set_SBO(Field_Control_SBO field)
   {
    value=((Type(field)&0xF)<<3)|(value&0xFFFFFF87);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&Control_M )
      {
       if( first )
         {
          Putobj(out,"M");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"M");
         }
      }

    if( value&Control_A )
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

    if( value&Control_C )
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

    if( value&Control_Z )
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

    if( value&Control_I )
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

    if( value&Control_V )
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

    if( value&Control_EE )
      {
       if( first )
         {
          Putobj(out,"EE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"EE");
         }
      }

    if( value&Control_NMFI )
      {
       if( first )
         {
          Putobj(out,"NMFI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"NMFI");
         }
      }

    if( value&Control_TRE )
      {
       if( first )
         {
          Putobj(out,"TRE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TRE");
         }
      }

    if( value&Control_AFE )
      {
       if( first )
         {
          Putobj(out,"AFE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AFE");
         }
      }

    if( value&Control_TE )
      {
       if( first )
         {
          Putobj(out,"TE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TE");
         }
      }

    if( first )
      {
       Printf(out,"SBO(#;)",get_SBO());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"SBO(#;)",get_SBO());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_AuxControl */ 

enum Bits_AuxControl : uint32
 {
  AuxControl_L1Alias  = 0x00000001,
  AuxControl_L2EN     = 0x00000002,
  AuxControl_L1PE     = 0x00000008,
  AuxControl_ASA      = 0x00000010,
  AuxControl_L1NEON   = 0x00000020,
  AuxControl_IBE      = 0x00000040,
  AuxControl_DBSM     = 0x00000080,
  AuxControl_WFINOP   = 0x00000100,
  AuxControl_PLDNOP   = 0x00000200,
  AuxControl_FSI      = 0x00000400,
  AuxControl_FLSSI    = 0x00000800,
  AuxControl_FNEONSI  = 0x00001000,
  AuxControl_FMCLK    = 0x00002000,
  AuxControl_FNEONCLK = 0x00004000,
  AuxControl_FETMCLK  = 0x00008000,
  AuxControl_CPPF     = 0x00010000,
  AuxControl_CPWI     = 0x00020000,
  AuxControl_CPIS     = 0x00040000,
  AuxControl_CSRD     = 0x00080000,
  AuxControl_CMP      = 0x00100000,
  AuxControl_L1HRD    = 0x40000000,
  AuxControl_L2HRD    = 0x80000000
 };
 
inline Bits_AuxControl operator | (Bits_AuxControl a,Bits_AuxControl b)
 { return Bits_AuxControl(uint32(a)|uint32(b)); }
 
struct Type_AuxControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_AuxControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_AuxControl & setTo(Bar &bar) { bar.set_AuxControl(*this); return *this; }
 

  template <class Bar>
  Type_AuxControl & setTo(Bar &bar,uint32 ind) { bar.set_AuxControl(ind,*this); return *this; }
 

  template <class T>
  Type_AuxControl & set(T to) { to(*this); return *this; }
 

  Type_AuxControl & setbit(Bits_AuxControl bits) { value|=Type(bits); return *this; }
 
  Type_AuxControl & setbitIf(bool cond,Bits_AuxControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_AuxControl & clearbit(Bits_AuxControl bits) { value&=~Type(bits); return *this; }
 
  Type_AuxControl & clearbitIf(bool cond,Bits_AuxControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_AuxControl bits) const { return value&bits; }
 
  bool testbit(Bits_AuxControl bits) const { return (value&bits)==Type(bits); }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&AuxControl_L1Alias )
      {
       if( first )
         {
          Putobj(out,"L1Alias");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L1Alias");
         }
      }

    if( value&AuxControl_L2EN )
      {
       if( first )
         {
          Putobj(out,"L2EN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L2EN");
         }
      }

    if( value&AuxControl_L1PE )
      {
       if( first )
         {
          Putobj(out,"L1PE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L1PE");
         }
      }

    if( value&AuxControl_ASA )
      {
       if( first )
         {
          Putobj(out,"ASA");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"ASA");
         }
      }

    if( value&AuxControl_L1NEON )
      {
       if( first )
         {
          Putobj(out,"L1NEON");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L1NEON");
         }
      }

    if( value&AuxControl_IBE )
      {
       if( first )
         {
          Putobj(out,"IBE");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"IBE");
         }
      }

    if( value&AuxControl_DBSM )
      {
       if( first )
         {
          Putobj(out,"DBSM");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"DBSM");
         }
      }

    if( value&AuxControl_WFINOP )
      {
       if( first )
         {
          Putobj(out,"WFINOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"WFINOP");
         }
      }

    if( value&AuxControl_PLDNOP )
      {
       if( first )
         {
          Putobj(out,"PLDNOP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PLDNOP");
         }
      }

    if( value&AuxControl_FSI )
      {
       if( first )
         {
          Putobj(out,"FSI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FSI");
         }
      }

    if( value&AuxControl_FLSSI )
      {
       if( first )
         {
          Putobj(out,"FLSSI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FLSSI");
         }
      }

    if( value&AuxControl_FNEONSI )
      {
       if( first )
         {
          Putobj(out,"FNEONSI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FNEONSI");
         }
      }

    if( value&AuxControl_FMCLK )
      {
       if( first )
         {
          Putobj(out,"FMCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FMCLK");
         }
      }

    if( value&AuxControl_FNEONCLK )
      {
       if( first )
         {
          Putobj(out,"FNEONCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FNEONCLK");
         }
      }

    if( value&AuxControl_FETMCLK )
      {
       if( first )
         {
          Putobj(out,"FETMCLK");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"FETMCLK");
         }
      }

    if( value&AuxControl_CPPF )
      {
       if( first )
         {
          Putobj(out,"CPPF");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CPPF");
         }
      }

    if( value&AuxControl_CPWI )
      {
       if( first )
         {
          Putobj(out,"CPWI");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CPWI");
         }
      }

    if( value&AuxControl_CPIS )
      {
       if( first )
         {
          Putobj(out,"CPIS");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CPIS");
         }
      }

    if( value&AuxControl_CSRD )
      {
       if( first )
         {
          Putobj(out,"CSRD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CSRD");
         }
      }

    if( value&AuxControl_CMP )
      {
       if( first )
         {
          Putobj(out,"CMP");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"CMP");
         }
      }

    if( value&AuxControl_L1HRD )
      {
       if( first )
         {
          Putobj(out,"L1HRD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L1HRD");
         }
      }

    if( value&AuxControl_L2HRD )
      {
       if( first )
         {
          Putobj(out,"L2HRD");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"L2HRD");
         }
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_DomainAccessControl */ 

enum Field_DomainAccessControl_D0 : uint32
 {
  DomainAccessControl_D0_NoAccess = 0x00,
  DomainAccessControl_D0_Client   = 0x01,
  DomainAccessControl_D0_Manager  = 0x03
 };
 
struct PrintField_DomainAccessControl_D0
 {
  Field_DomainAccessControl_D0 field;

  explicit PrintField_DomainAccessControl_D0(Field_DomainAccessControl_D0 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"Client"); break;
       case 0x03 : Putobj(out,"Manager"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAccessControl_D0 GetTextDesc(Field_DomainAccessControl_D0 field)
 {
  return PrintField_DomainAccessControl_D0(field);
 }
 
struct Type_DomainAccessControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DomainAccessControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DomainAccessControl & setTo(Bar &bar) { bar.set_DomainAccessControl(*this); return *this; }
 

  template <class Bar>
  Type_DomainAccessControl & setTo(Bar &bar,uint32 ind) { bar.set_DomainAccessControl(ind,*this); return *this; }
 

  template <class T>
  Type_DomainAccessControl & set(T to) { to(*this); return *this; }
 

  Field_DomainAccessControl_D0 get_D0() const
   {
    return Field_DomainAccessControl_D0((value>>0)&0x3);
   }
 
  Type_DomainAccessControl & set_D0(Field_DomainAccessControl_D0 field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Type get_D1() const
   {
    return (value>>2)&0x3;
   }
 
  Type_DomainAccessControl & set_D1(Type field)
   {
    value=((field&0x3)<<2)|(value&0xFFFFFFF3);

    return *this;
   }
 

  Type get_D2() const
   {
    return (value>>4)&0x3;
   }
 
  Type_DomainAccessControl & set_D2(Type field)
   {
    value=((field&0x3)<<4)|(value&0xFFFFFFCF);

    return *this;
   }
 

  Type get_D3() const
   {
    return (value>>6)&0x3;
   }
 
  Type_DomainAccessControl & set_D3(Type field)
   {
    value=((field&0x3)<<6)|(value&0xFFFFFF3F);

    return *this;
   }
 

  Type get_D4() const
   {
    return (value>>8)&0x3;
   }
 
  Type_DomainAccessControl & set_D4(Type field)
   {
    value=((field&0x3)<<8)|(value&0xFFFFFCFF);

    return *this;
   }
 

  Type get_D5() const
   {
    return (value>>10)&0x3;
   }
 
  Type_DomainAccessControl & set_D5(Type field)
   {
    value=((field&0x3)<<10)|(value&0xFFFFF3FF);

    return *this;
   }
 

  Type get_D6() const
   {
    return (value>>12)&0x3;
   }
 
  Type_DomainAccessControl & set_D6(Type field)
   {
    value=((field&0x3)<<12)|(value&0xFFFFCFFF);

    return *this;
   }
 

  Type get_D7() const
   {
    return (value>>14)&0x3;
   }
 
  Type_DomainAccessControl & set_D7(Type field)
   {
    value=((field&0x3)<<14)|(value&0xFFFF3FFF);

    return *this;
   }
 

  Type get_D8() const
   {
    return (value>>16)&0x3;
   }
 
  Type_DomainAccessControl & set_D8(Type field)
   {
    value=((field&0x3)<<16)|(value&0xFFFCFFFF);

    return *this;
   }
 

  Type get_D9() const
   {
    return (value>>18)&0x3;
   }
 
  Type_DomainAccessControl & set_D9(Type field)
   {
    value=((field&0x3)<<18)|(value&0xFFF3FFFF);

    return *this;
   }
 

  Type get_D10() const
   {
    return (value>>20)&0x3;
   }
 
  Type_DomainAccessControl & set_D10(Type field)
   {
    value=((field&0x3)<<20)|(value&0xFFCFFFFF);

    return *this;
   }
 

  Type get_D11() const
   {
    return (value>>22)&0x3;
   }
 
  Type_DomainAccessControl & set_D11(Type field)
   {
    value=((field&0x3)<<22)|(value&0xFF3FFFFF);

    return *this;
   }
 

  Type get_D12() const
   {
    return (value>>24)&0x3;
   }
 
  Type_DomainAccessControl & set_D12(Type field)
   {
    value=((field&0x3)<<24)|(value&0xFCFFFFFF);

    return *this;
   }
 

  Type get_D13() const
   {
    return (value>>26)&0x3;
   }
 
  Type_DomainAccessControl & set_D13(Type field)
   {
    value=((field&0x3)<<26)|(value&0xF3FFFFFF);

    return *this;
   }
 

  Type get_D14() const
   {
    return (value>>28)&0x3;
   }
 
  Type_DomainAccessControl & set_D14(Type field)
   {
    value=((field&0x3)<<28)|(value&0xCFFFFFFF);

    return *this;
   }
 

  Type get_D15() const
   {
    return (value>>30)&0x3;
   }
 
  Type_DomainAccessControl & set_D15(Type field)
   {
    value=((field&0x3)<<30)|(value&0x3FFFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( first )
      {
       Printf(out,"D0(#;)",get_D0());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D0(#;)",get_D0());
      }

    if( first )
      {
       Printf(out,"D1(#;)",get_D1());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D1(#;)",get_D1());
      }

    if( first )
      {
       Printf(out,"D2(#;)",get_D2());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D2(#;)",get_D2());
      }

    if( first )
      {
       Printf(out,"D3(#;)",get_D3());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D3(#;)",get_D3());
      }

    if( first )
      {
       Printf(out,"D4(#;)",get_D4());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D4(#;)",get_D4());
      }

    if( first )
      {
       Printf(out,"D5(#;)",get_D5());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D5(#;)",get_D5());
      }

    if( first )
      {
       Printf(out,"D6(#;)",get_D6());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D6(#;)",get_D6());
      }

    if( first )
      {
       Printf(out,"D7(#;)",get_D7());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D7(#;)",get_D7());
      }

    if( first )
      {
       Printf(out,"D8(#;)",get_D8());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D8(#;)",get_D8());
      }

    if( first )
      {
       Printf(out,"D9(#;)",get_D9());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D9(#;)",get_D9());
      }

    if( first )
      {
       Printf(out,"D10(#;)",get_D10());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D10(#;)",get_D10());
      }

    if( first )
      {
       Printf(out,"D11(#;)",get_D11());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D11(#;)",get_D11());
      }

    if( first )
      {
       Printf(out,"D12(#;)",get_D12());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D12(#;)",get_D12());
      }

    if( first )
      {
       Printf(out,"D13(#;)",get_D13());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D13(#;)",get_D13());
      }

    if( first )
      {
       Printf(out,"D14(#;)",get_D14());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D14(#;)",get_D14());
      }

    if( first )
      {
       Printf(out,"D15(#;)",get_D15());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"D15(#;)",get_D15());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TTControl */ 

enum Bits_TTControl : uint32
 {
  TTControl_PD0 = 0x00000010,
  TTControl_PD1 = 0x00000020
 };
 
inline Bits_TTControl operator | (Bits_TTControl a,Bits_TTControl b)
 { return Bits_TTControl(uint32(a)|uint32(b)); }
 
struct Type_TTControl
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TTControl(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TTControl & setTo(Bar &bar) { bar.set_TTControl(*this); return *this; }
 

  template <class Bar>
  Type_TTControl & setTo(Bar &bar,uint32 ind) { bar.set_TTControl(ind,*this); return *this; }
 

  template <class T>
  Type_TTControl & set(T to) { to(*this); return *this; }
 

  Type_TTControl & setbit(Bits_TTControl bits) { value|=Type(bits); return *this; }
 
  Type_TTControl & setbitIf(bool cond,Bits_TTControl bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TTControl & clearbit(Bits_TTControl bits) { value&=~Type(bits); return *this; }
 
  Type_TTControl & clearbitIf(bool cond,Bits_TTControl bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TTControl bits) const { return value&bits; }
 
  bool testbit(Bits_TTControl bits) const { return (value&bits)==Type(bits); }
 

  Type get_N() const
   {
    return (value>>0)&0xF;
   }
 
  Type_TTControl & set_N(Type field)
   {
    value=((field&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TTControl_PD0 )
      {
       if( first )
         {
          Putobj(out,"PD0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PD0");
         }
      }

    if( value&TTControl_PD1 )
      {
       if( first )
         {
          Putobj(out,"PD1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PD1");
         }
      }

    if( first )
      {
       Printf(out,"N(#;)",get_N());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"N(#;)",get_N());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_TTBase0 */ 

enum Bits_TTBase0 : uint32
 {
  TTBase0_C = 0x00000001,
  TTBase0_S = 0x00000002,
  TTBase0_P = 0x00000004
 };
 
inline Bits_TTBase0 operator | (Bits_TTBase0 a,Bits_TTBase0 b)
 { return Bits_TTBase0(uint32(a)|uint32(b)); }
 
struct Type_TTBase0
 {
  typedef uint32 Type;

  Type value;


  explicit Type_TTBase0(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_TTBase0 & setTo(Bar &bar) { bar.set_TTBase0(*this); return *this; }
 

  template <class Bar>
  Type_TTBase0 & setTo(Bar &bar,uint32 ind) { bar.set_TTBase0(ind,*this); return *this; }
 

  template <class T>
  Type_TTBase0 & set(T to) { to(*this); return *this; }
 

  Type_TTBase0 & setbit(Bits_TTBase0 bits) { value|=Type(bits); return *this; }
 
  Type_TTBase0 & setbitIf(bool cond,Bits_TTBase0 bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_TTBase0 & clearbit(Bits_TTBase0 bits) { value&=~Type(bits); return *this; }
 
  Type_TTBase0 & clearbitIf(bool cond,Bits_TTBase0 bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_TTBase0 bits) const { return value&bits; }
 
  bool testbit(Bits_TTBase0 bits) const { return (value&bits)==Type(bits); }
 

  Type get_RGN() const
   {
    return (value>>3)&0x3;
   }
 
  Type_TTBase0 & set_RGN(Type field)
   {
    value=((field&0x3)<<3)|(value&0xFFFFFFE7);

    return *this;
   }
 

  Type get_Base() const
   {
    return (value>>14)&0x3FFFF;
   }
 
  Type_TTBase0 & set_Base(Type field)
   {
    value=((field&0x3FFFF)<<14)|(value&0x3FFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&TTBase0_C )
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

    if( value&TTBase0_S )
      {
       if( first )
         {
          Putobj(out,"S");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"S");
         }
      }

    if( value&TTBase0_P )
      {
       if( first )
         {
          Putobj(out,"P");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"P");
         }
      }

    if( first )
      {
       Printf(out,"RGN(#;)",get_RGN());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"RGN(#;)",get_RGN());
      }

    if( first )
      {
       Printf(out,"Base(#;)",get_Base());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base(#;)",get_Base());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_SectionDesc */ 

enum Bits_SectionDesc : uint32
 {
  SectionDesc_PXN  = 0x00000001,
  SectionDesc_SBO  = 0x00000002,
  SectionDesc_B    = 0x00000004,
  SectionDesc_C    = 0x00000008,
  SectionDesc_XN   = 0x00000010,
  SectionDesc_Imp  = 0x00000200,
  SectionDesc_AP0  = 0x00000400,
  SectionDesc_AP1  = 0x00000800,
  SectionDesc_TEX0 = 0x00001000,
  SectionDesc_TEX1 = 0x00002000,
  SectionDesc_TEX2 = 0x00004000,
  SectionDesc_AP2  = 0x00008000,
  SectionDesc_S    = 0x00010000,
  SectionDesc_nG   = 0x00020000,
  SectionDesc_SBZ  = 0x00040000,
  SectionDesc_NS   = 0x00080000
 };
 
inline Bits_SectionDesc operator | (Bits_SectionDesc a,Bits_SectionDesc b)
 { return Bits_SectionDesc(uint32(a)|uint32(b)); }
 
struct Type_SectionDesc
 {
  typedef uint32 Type;

  Type value;


  explicit Type_SectionDesc(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_SectionDesc & setTo(Bar &bar) { bar.set_SectionDesc(*this); return *this; }
 

  template <class Bar>
  Type_SectionDesc & setTo(Bar &bar,uint32 ind) { bar.set_SectionDesc(ind,*this); return *this; }
 

  template <class T>
  Type_SectionDesc & set(T to) { to(*this); return *this; }
 

  Type_SectionDesc & setbit(Bits_SectionDesc bits) { value|=Type(bits); return *this; }
 
  Type_SectionDesc & setbitIf(bool cond,Bits_SectionDesc bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_SectionDesc & clearbit(Bits_SectionDesc bits) { value&=~Type(bits); return *this; }
 
  Type_SectionDesc & clearbitIf(bool cond,Bits_SectionDesc bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_SectionDesc bits) const { return value&bits; }
 
  bool testbit(Bits_SectionDesc bits) const { return (value&bits)==Type(bits); }
 

  Type get_Domain() const
   {
    return (value>>5)&0xF;
   }
 
  Type_SectionDesc & set_Domain(Type field)
   {
    value=((field&0xF)<<5)|(value&0xFFFFFE1F);

    return *this;
   }
 

  Type get_Base() const
   {
    return (value>>20)&0xFFF;
   }
 
  Type_SectionDesc & set_Base(Type field)
   {
    value=((field&0xFFF)<<20)|(value&0xFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&SectionDesc_PXN )
      {
       if( first )
         {
          Putobj(out,"PXN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"PXN");
         }
      }

    if( value&SectionDesc_SBO )
      {
       if( first )
         {
          Putobj(out,"SBO");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SBO");
         }
      }

    if( value&SectionDesc_B )
      {
       if( first )
         {
          Putobj(out,"B");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"B");
         }
      }

    if( value&SectionDesc_C )
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

    if( value&SectionDesc_XN )
      {
       if( first )
         {
          Putobj(out,"XN");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"XN");
         }
      }

    if( value&SectionDesc_Imp )
      {
       if( first )
         {
          Putobj(out,"Imp");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Imp");
         }
      }

    if( value&SectionDesc_AP0 )
      {
       if( first )
         {
          Putobj(out,"AP0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AP0");
         }
      }

    if( value&SectionDesc_AP1 )
      {
       if( first )
         {
          Putobj(out,"AP1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AP1");
         }
      }

    if( value&SectionDesc_TEX0 )
      {
       if( first )
         {
          Putobj(out,"TEX0");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TEX0");
         }
      }

    if( value&SectionDesc_TEX1 )
      {
       if( first )
         {
          Putobj(out,"TEX1");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TEX1");
         }
      }

    if( value&SectionDesc_TEX2 )
      {
       if( first )
         {
          Putobj(out,"TEX2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"TEX2");
         }
      }

    if( value&SectionDesc_AP2 )
      {
       if( first )
         {
          Putobj(out,"AP2");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"AP2");
         }
      }

    if( value&SectionDesc_S )
      {
       if( first )
         {
          Putobj(out,"S");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"S");
         }
      }

    if( value&SectionDesc_nG )
      {
       if( first )
         {
          Putobj(out,"nG");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"nG");
         }
      }

    if( value&SectionDesc_SBZ )
      {
       if( first )
         {
          Putobj(out,"SBZ");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"SBZ");
         }
      }

    if( value&SectionDesc_NS )
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

    if( first )
      {
       Printf(out,"Domain(#;)",get_Domain());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Domain(#;)",get_Domain());
      }

    if( first )
      {
       Printf(out,"Base(#;)",get_Base());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Base(#;)",get_Base());
      }

    if( first ) out.put('0');
   }
 };
 
