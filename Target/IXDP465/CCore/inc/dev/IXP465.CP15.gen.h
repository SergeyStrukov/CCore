/* IXP465.CP15.gen.h */ 

/* struct Type_ID */ 

enum Field_ID_Revision : uint32
 {
  ID_Revision_IXP45x_46x = 0x00
 };
 
struct PrintField_ID_Revision
 {
  Field_ID_Revision field;

  explicit PrintField_ID_Revision(Field_ID_Revision field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"IXP45x_46x"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_Revision GetTextDesc(Field_ID_Revision field)
 {
  return PrintField_ID_Revision(field);
 }
 
enum Field_ID_Number : uint32
 {
  ID_Number_IXP45x_46x = 0x20
 };
 
struct PrintField_ID_Number
 {
  Field_ID_Number field;

  explicit PrintField_ID_Number(Field_ID_Number field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x20 : Putobj(out,"IXP45x_46x"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_Number GetTextDesc(Field_ID_Number field)
 {
  return PrintField_ID_Number(field);
 }
 
enum Field_ID_CoreRevision : uint32
 {
  ID_CoreRevision_CoreRev0 = 0x00
 };
 
struct PrintField_ID_CoreRevision
 {
  Field_ID_CoreRevision field;

  explicit PrintField_ID_CoreRevision(Field_ID_CoreRevision field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"CoreRev0"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_CoreRevision GetTextDesc(Field_ID_CoreRevision field)
 {
  return PrintField_ID_CoreRevision(field);
 }
 
enum Field_ID_CoreGen : uint32
 {
  ID_CoreGen_Intel_XScale = 0x02
 };
 
struct PrintField_ID_CoreGen
 {
  Field_ID_CoreGen field;

  explicit PrintField_ID_CoreGen(Field_ID_CoreGen field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x02 : Putobj(out,"Intel_XScale"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_CoreGen GetTextDesc(Field_ID_CoreGen field)
 {
  return PrintField_ID_CoreGen(field);
 }
 
enum Field_ID_Arch : uint32
 {
  ID_Arch_Intel_StrongARM_5TE = 0x05
 };
 
struct PrintField_ID_Arch
 {
  Field_ID_Arch field;

  explicit PrintField_ID_Arch(Field_ID_Arch field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x05 : Putobj(out,"Intel_StrongARM_5TE"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_Arch GetTextDesc(Field_ID_Arch field)
 {
  return PrintField_ID_Arch(field);
 }
 
enum Field_ID_Impl : uint32
 {
  ID_Impl_Intel = 0x69
 };
 
struct PrintField_ID_Impl
 {
  Field_ID_Impl field;

  explicit PrintField_ID_Impl(Field_ID_Impl field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x69 : Putobj(out,"Intel"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_ID_Impl GetTextDesc(Field_ID_Impl field)
 {
  return PrintField_ID_Impl(field);
 }
 
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
 

  Field_ID_Revision get_Revision() const
   {
    return Field_ID_Revision((value>>0)&0xF);
   }
 
  Type_ID & set_Revision(Field_ID_Revision field)
   {
    value=((Type(field)&0xF)<<0)|(value&0xFFFFFFF0);

    return *this;
   }
 

  Field_ID_Number get_Number() const
   {
    return Field_ID_Number((value>>4)&0x3F);
   }
 
  Type_ID & set_Number(Field_ID_Number field)
   {
    value=((Type(field)&0x3F)<<4)|(value&0xFFFFFC0F);

    return *this;
   }
 

  Field_ID_CoreRevision get_CoreRevision() const
   {
    return Field_ID_CoreRevision((value>>10)&0x7);
   }
 
  Type_ID & set_CoreRevision(Field_ID_CoreRevision field)
   {
    value=((Type(field)&0x7)<<10)|(value&0xFFFFE3FF);

    return *this;
   }
 

  Field_ID_CoreGen get_CoreGen() const
   {
    return Field_ID_CoreGen((value>>13)&0x7);
   }
 
  Type_ID & set_CoreGen(Field_ID_CoreGen field)
   {
    value=((Type(field)&0x7)<<13)|(value&0xFFFF1FFF);

    return *this;
   }
 

  Field_ID_Arch get_Arch() const
   {
    return Field_ID_Arch((value>>16)&0xFF);
   }
 
  Type_ID & set_Arch(Field_ID_Arch field)
   {
    value=((Type(field)&0xFF)<<16)|(value&0xFF00FFFF);

    return *this;
   }
 

  Field_ID_Impl get_Impl() const
   {
    return Field_ID_Impl((value>>24)&0xFF);
   }
 
  Type_ID & set_Impl(Field_ID_Impl field)
   {
    value=((Type(field)&0xFF)<<24)|(value&0xFFFFFF);

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
       Printf(out,"Number(#;)",get_Number());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Number(#;)",get_Number());
      }

    if( first )
      {
       Printf(out,"CoreRevision(#;)",get_CoreRevision());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CoreRevision(#;)",get_CoreRevision());
      }

    if( first )
      {
       Printf(out,"CoreGen(#;)",get_CoreGen());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"CoreGen(#;)",get_CoreGen());
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
       Printf(out,"Impl(#;)",get_Impl());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Impl(#;)",get_Impl());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_CacheType */ 

enum Bits_CacheType : uint32
 {
  CacheType_Harvard = 0x01000000
 };
 
inline Bits_CacheType operator | (Bits_CacheType a,Bits_CacheType b)
 { return Bits_CacheType(uint32(a)|uint32(b)); }
 
enum Field_CacheType_ILine : uint32
 {
  CacheType_ILine_L8word = 0x02
 };
 
struct PrintField_CacheType_ILine
 {
  Field_CacheType_ILine field;

  explicit PrintField_CacheType_ILine(Field_CacheType_ILine field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x02 : Putobj(out,"L8word"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_ILine GetTextDesc(Field_CacheType_ILine field)
 {
  return PrintField_CacheType_ILine(field);
 }
 
enum Field_CacheType_IAss : uint32
 {
  CacheType_IAss_A32way = 0x05
 };
 
struct PrintField_CacheType_IAss
 {
  Field_CacheType_IAss field;

  explicit PrintField_CacheType_IAss(Field_CacheType_IAss field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x05 : Putobj(out,"A32way"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_IAss GetTextDesc(Field_CacheType_IAss field)
 {
  return PrintField_CacheType_IAss(field);
 }
 
enum Field_CacheType_ISize : uint32
 {
  CacheType_ISize_S32k = 0x06
 };
 
struct PrintField_CacheType_ISize
 {
  Field_CacheType_ISize field;

  explicit PrintField_CacheType_ISize(Field_CacheType_ISize field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x06 : Putobj(out,"S32k"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_ISize GetTextDesc(Field_CacheType_ISize field)
 {
  return PrintField_CacheType_ISize(field);
 }
 
enum Field_CacheType_DLine : uint32
 {
  CacheType_DLine_L8word = 0x02
 };
 
struct PrintField_CacheType_DLine
 {
  Field_CacheType_DLine field;

  explicit PrintField_CacheType_DLine(Field_CacheType_DLine field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x02 : Putobj(out,"L8word"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_DLine GetTextDesc(Field_CacheType_DLine field)
 {
  return PrintField_CacheType_DLine(field);
 }
 
enum Field_CacheType_DAss : uint32
 {
  CacheType_DAss_A32way = 0x05
 };
 
struct PrintField_CacheType_DAss
 {
  Field_CacheType_DAss field;

  explicit PrintField_CacheType_DAss(Field_CacheType_DAss field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x05 : Putobj(out,"A32way"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_DAss GetTextDesc(Field_CacheType_DAss field)
 {
  return PrintField_CacheType_DAss(field);
 }
 
enum Field_CacheType_DSize : uint32
 {
  CacheType_DSize_S32k = 0x06
 };
 
struct PrintField_CacheType_DSize
 {
  Field_CacheType_DSize field;

  explicit PrintField_CacheType_DSize(Field_CacheType_DSize field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x06 : Putobj(out,"S32k"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_DSize GetTextDesc(Field_CacheType_DSize field)
 {
  return PrintField_CacheType_DSize(field);
 }
 
enum Field_CacheType_Class : uint32
 {
  CacheType_Class_L_WB_RR = 0x05
 };
 
struct PrintField_CacheType_Class
 {
  Field_CacheType_Class field;

  explicit PrintField_CacheType_Class(Field_CacheType_Class field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x05 : Putobj(out,"L_WB_RR"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CacheType_Class GetTextDesc(Field_CacheType_Class field)
 {
  return PrintField_CacheType_Class(field);
 }
 
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
 

  Type_CacheType & setbit(Bits_CacheType bits) { value|=Type(bits); return *this; }
 
  Type_CacheType & setbitIf(bool cond,Bits_CacheType bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CacheType & clearbit(Bits_CacheType bits) { value&=~Type(bits); return *this; }
 
  Type_CacheType & clearbitIf(bool cond,Bits_CacheType bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CacheType bits) const { return value&bits; }
 
  bool testbit(Bits_CacheType bits) const { return (value&bits)==Type(bits); }
 

  Field_CacheType_ILine get_ILine() const
   {
    return Field_CacheType_ILine((value>>0)&0x3);
   }
 
  Type_CacheType & set_ILine(Field_CacheType_ILine field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Field_CacheType_IAss get_IAss() const
   {
    return Field_CacheType_IAss((value>>3)&0x7);
   }
 
  Type_CacheType & set_IAss(Field_CacheType_IAss field)
   {
    value=((Type(field)&0x7)<<3)|(value&0xFFFFFFC7);

    return *this;
   }
 

  Field_CacheType_ISize get_ISize() const
   {
    return Field_CacheType_ISize((value>>6)&0x7);
   }
 
  Type_CacheType & set_ISize(Field_CacheType_ISize field)
   {
    value=((Type(field)&0x7)<<6)|(value&0xFFFFFE3F);

    return *this;
   }
 

  Field_CacheType_DLine get_DLine() const
   {
    return Field_CacheType_DLine((value>>12)&0x3);
   }
 
  Type_CacheType & set_DLine(Field_CacheType_DLine field)
   {
    value=((Type(field)&0x3)<<12)|(value&0xFFFFCFFF);

    return *this;
   }
 

  Field_CacheType_DAss get_DAss() const
   {
    return Field_CacheType_DAss((value>>15)&0x7);
   }
 
  Type_CacheType & set_DAss(Field_CacheType_DAss field)
   {
    value=((Type(field)&0x7)<<15)|(value&0xFFFC7FFF);

    return *this;
   }
 

  Field_CacheType_DSize get_DSize() const
   {
    return Field_CacheType_DSize((value>>18)&0x7);
   }
 
  Type_CacheType & set_DSize(Field_CacheType_DSize field)
   {
    value=((Type(field)&0x7)<<18)|(value&0xFFE3FFFF);

    return *this;
   }
 

  Field_CacheType_Class get_Class() const
   {
    return Field_CacheType_Class((value>>25)&0xF);
   }
 
  Type_CacheType & set_Class(Field_CacheType_Class field)
   {
    value=((Type(field)&0xF)<<25)|(value&0xE1FFFFFF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CacheType_Harvard )
      {
       if( first )
         {
          Putobj(out,"Harvard");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"Harvard");
         }
      }

    if( first )
      {
       Printf(out,"ILine(#;)",get_ILine());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ILine(#;)",get_ILine());
      }

    if( first )
      {
       Printf(out,"IAss(#;)",get_IAss());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"IAss(#;)",get_IAss());
      }

    if( first )
      {
       Printf(out,"ISize(#;)",get_ISize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"ISize(#;)",get_ISize());
      }

    if( first )
      {
       Printf(out,"DLine(#;)",get_DLine());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DLine(#;)",get_DLine());
      }

    if( first )
      {
       Printf(out,"DAss(#;)",get_DAss());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DAss(#;)",get_DAss());
      }

    if( first )
      {
       Printf(out,"DSize(#;)",get_DSize());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"DSize(#;)",get_DSize());
      }

    if( first )
      {
       Printf(out,"Class(#;)",get_Class());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Class(#;)",get_Class());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_Control */ 

enum Bits_Control : uint32
 {
  Control_M = 0x00000001,
  Control_A = 0x00000002,
  Control_C = 0x00000004,
  Control_B = 0x00000080,
  Control_S = 0x00000100,
  Control_R = 0x00000200,
  Control_Z = 0x00000800,
  Control_I = 0x00001000,
  Control_V = 0x00002000
 };
 
inline Bits_Control operator | (Bits_Control a,Bits_Control b)
 { return Bits_Control(uint32(a)|uint32(b)); }
 
enum Field_Control_Ones : uint32
 {
  Control_Ones_Fill = 0x0F
 };
 
struct PrintField_Control_Ones
 {
  Field_Control_Ones field;

  explicit PrintField_Control_Ones(Field_Control_Ones field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x0F : Putobj(out,"Fill"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_Control_Ones GetTextDesc(Field_Control_Ones field)
 {
  return PrintField_Control_Ones(field);
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
 

  Field_Control_Ones get_Ones() const
   {
    return Field_Control_Ones((value>>3)&0xF);
   }
 
  Type_Control & set_Ones(Field_Control_Ones field)
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

    if( value&Control_B )
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

    if( value&Control_S )
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

    if( value&Control_R )
      {
       if( first )
         {
          Putobj(out,"R");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"R");
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

    if( first )
      {
       Printf(out,"Ones(#;)",get_Ones());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"Ones(#;)",get_Ones());
      }

    if( first ) out.put('0');
   }
 };
 
/* struct Type_AuxControl */ 

enum Bits_AuxControl : uint32
 {
  AuxControl_K = 0x00000001,
  AuxControl_P = 0x00000002
 };
 
inline Bits_AuxControl operator | (Bits_AuxControl a,Bits_AuxControl b)
 { return Bits_AuxControl(uint32(a)|uint32(b)); }
 
enum Field_AuxControl_MD : uint32
 {
  AuxControl_MD_WB_RA  = 0x00,
  AuxControl_MD_WB_RWA = 0x01,
  AuxControl_MD_WT_RA  = 0x02
 };
 
struct PrintField_AuxControl_MD
 {
  Field_AuxControl_MD field;

  explicit PrintField_AuxControl_MD(Field_AuxControl_MD field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"WB_RA"); break;
       case 0x01 : Putobj(out,"WB_RWA"); break;
       case 0x02 : Putobj(out,"WT_RA"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_AuxControl_MD GetTextDesc(Field_AuxControl_MD field)
 {
  return PrintField_AuxControl_MD(field);
 }
 
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
 

  Field_AuxControl_MD get_MD() const
   {
    return Field_AuxControl_MD((value>>4)&0x3);
   }
 
  Type_AuxControl & set_MD(Field_AuxControl_MD field)
   {
    value=((Type(field)&0x3)<<4)|(value&0xFFFFFFCF);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&AuxControl_K )
      {
       if( first )
         {
          Putobj(out,"K");

          first=false;
         }
       else
         {
          out.put('|');

          Putobj(out,"K");
         }
      }

    if( value&AuxControl_P )
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
       Printf(out,"MD(#;)",get_MD());

       first=false;
      }
    else
      {
       out.put('|');

       Printf(out,"MD(#;)",get_MD());
      }

    if( first ) out.put('0');
   }
 };
 
/* type Type_TTBase */ 

typedef uint32 Type_TTBase;

/* struct Type_DomainAC */ 

enum Field_DomainAC_D0 : uint32
 {
  DomainAC_D0_NoAccess   = 0x00,
  DomainAC_D0_DescAccess = 0x01,
  DomainAC_D0_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D0
 {
  Field_DomainAC_D0 field;

  explicit PrintField_DomainAC_D0(Field_DomainAC_D0 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D0 GetTextDesc(Field_DomainAC_D0 field)
 {
  return PrintField_DomainAC_D0(field);
 }
 
enum Field_DomainAC_D1 : uint32
 {
  DomainAC_D1_NoAccess   = 0x00,
  DomainAC_D1_DescAccess = 0x01,
  DomainAC_D1_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D1
 {
  Field_DomainAC_D1 field;

  explicit PrintField_DomainAC_D1(Field_DomainAC_D1 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D1 GetTextDesc(Field_DomainAC_D1 field)
 {
  return PrintField_DomainAC_D1(field);
 }
 
enum Field_DomainAC_D2 : uint32
 {
  DomainAC_D2_NoAccess   = 0x00,
  DomainAC_D2_DescAccess = 0x01,
  DomainAC_D2_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D2
 {
  Field_DomainAC_D2 field;

  explicit PrintField_DomainAC_D2(Field_DomainAC_D2 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D2 GetTextDesc(Field_DomainAC_D2 field)
 {
  return PrintField_DomainAC_D2(field);
 }
 
enum Field_DomainAC_D3 : uint32
 {
  DomainAC_D3_NoAccess   = 0x00,
  DomainAC_D3_DescAccess = 0x01,
  DomainAC_D3_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D3
 {
  Field_DomainAC_D3 field;

  explicit PrintField_DomainAC_D3(Field_DomainAC_D3 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D3 GetTextDesc(Field_DomainAC_D3 field)
 {
  return PrintField_DomainAC_D3(field);
 }
 
enum Field_DomainAC_D4 : uint32
 {
  DomainAC_D4_NoAccess   = 0x00,
  DomainAC_D4_DescAccess = 0x01,
  DomainAC_D4_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D4
 {
  Field_DomainAC_D4 field;

  explicit PrintField_DomainAC_D4(Field_DomainAC_D4 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D4 GetTextDesc(Field_DomainAC_D4 field)
 {
  return PrintField_DomainAC_D4(field);
 }
 
enum Field_DomainAC_D5 : uint32
 {
  DomainAC_D5_NoAccess   = 0x00,
  DomainAC_D5_DescAccess = 0x01,
  DomainAC_D5_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D5
 {
  Field_DomainAC_D5 field;

  explicit PrintField_DomainAC_D5(Field_DomainAC_D5 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D5 GetTextDesc(Field_DomainAC_D5 field)
 {
  return PrintField_DomainAC_D5(field);
 }
 
enum Field_DomainAC_D6 : uint32
 {
  DomainAC_D6_NoAccess   = 0x00,
  DomainAC_D6_DescAccess = 0x01,
  DomainAC_D6_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D6
 {
  Field_DomainAC_D6 field;

  explicit PrintField_DomainAC_D6(Field_DomainAC_D6 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D6 GetTextDesc(Field_DomainAC_D6 field)
 {
  return PrintField_DomainAC_D6(field);
 }
 
enum Field_DomainAC_D7 : uint32
 {
  DomainAC_D7_NoAccess   = 0x00,
  DomainAC_D7_DescAccess = 0x01,
  DomainAC_D7_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D7
 {
  Field_DomainAC_D7 field;

  explicit PrintField_DomainAC_D7(Field_DomainAC_D7 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D7 GetTextDesc(Field_DomainAC_D7 field)
 {
  return PrintField_DomainAC_D7(field);
 }
 
enum Field_DomainAC_D8 : uint32
 {
  DomainAC_D8_NoAccess   = 0x00,
  DomainAC_D8_DescAccess = 0x01,
  DomainAC_D8_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D8
 {
  Field_DomainAC_D8 field;

  explicit PrintField_DomainAC_D8(Field_DomainAC_D8 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D8 GetTextDesc(Field_DomainAC_D8 field)
 {
  return PrintField_DomainAC_D8(field);
 }
 
enum Field_DomainAC_D9 : uint32
 {
  DomainAC_D9_NoAccess   = 0x00,
  DomainAC_D9_DescAccess = 0x01,
  DomainAC_D9_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D9
 {
  Field_DomainAC_D9 field;

  explicit PrintField_DomainAC_D9(Field_DomainAC_D9 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D9 GetTextDesc(Field_DomainAC_D9 field)
 {
  return PrintField_DomainAC_D9(field);
 }
 
enum Field_DomainAC_D10 : uint32
 {
  DomainAC_D10_NoAccess   = 0x00,
  DomainAC_D10_DescAccess = 0x01,
  DomainAC_D10_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D10
 {
  Field_DomainAC_D10 field;

  explicit PrintField_DomainAC_D10(Field_DomainAC_D10 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D10 GetTextDesc(Field_DomainAC_D10 field)
 {
  return PrintField_DomainAC_D10(field);
 }
 
enum Field_DomainAC_D11 : uint32
 {
  DomainAC_D11_NoAccess   = 0x00,
  DomainAC_D11_DescAccess = 0x01,
  DomainAC_D11_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D11
 {
  Field_DomainAC_D11 field;

  explicit PrintField_DomainAC_D11(Field_DomainAC_D11 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D11 GetTextDesc(Field_DomainAC_D11 field)
 {
  return PrintField_DomainAC_D11(field);
 }
 
enum Field_DomainAC_D12 : uint32
 {
  DomainAC_D12_NoAccess   = 0x00,
  DomainAC_D12_DescAccess = 0x01,
  DomainAC_D12_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D12
 {
  Field_DomainAC_D12 field;

  explicit PrintField_DomainAC_D12(Field_DomainAC_D12 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D12 GetTextDesc(Field_DomainAC_D12 field)
 {
  return PrintField_DomainAC_D12(field);
 }
 
enum Field_DomainAC_D13 : uint32
 {
  DomainAC_D13_NoAccess   = 0x00,
  DomainAC_D13_DescAccess = 0x01,
  DomainAC_D13_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D13
 {
  Field_DomainAC_D13 field;

  explicit PrintField_DomainAC_D13(Field_DomainAC_D13 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D13 GetTextDesc(Field_DomainAC_D13 field)
 {
  return PrintField_DomainAC_D13(field);
 }
 
enum Field_DomainAC_D14 : uint32
 {
  DomainAC_D14_NoAccess   = 0x00,
  DomainAC_D14_DescAccess = 0x01,
  DomainAC_D14_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D14
 {
  Field_DomainAC_D14 field;

  explicit PrintField_DomainAC_D14(Field_DomainAC_D14 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D14 GetTextDesc(Field_DomainAC_D14 field)
 {
  return PrintField_DomainAC_D14(field);
 }
 
enum Field_DomainAC_D15 : uint32
 {
  DomainAC_D15_NoAccess   = 0x00,
  DomainAC_D15_DescAccess = 0x01,
  DomainAC_D15_FullAccess = 0x03
 };
 
struct PrintField_DomainAC_D15
 {
  Field_DomainAC_D15 field;

  explicit PrintField_DomainAC_D15(Field_DomainAC_D15 field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x00 : Putobj(out,"NoAccess"); break;
       case 0x01 : Putobj(out,"DescAccess"); break;
       case 0x03 : Putobj(out,"FullAccess"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_DomainAC_D15 GetTextDesc(Field_DomainAC_D15 field)
 {
  return PrintField_DomainAC_D15(field);
 }
 
struct Type_DomainAC
 {
  typedef uint32 Type;

  Type value;


  explicit Type_DomainAC(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_DomainAC & setTo(Bar &bar) { bar.set_DomainAC(*this); return *this; }
 

  template <class Bar>
  Type_DomainAC & setTo(Bar &bar,uint32 ind) { bar.set_DomainAC(ind,*this); return *this; }
 

  template <class T>
  Type_DomainAC & set(T to) { to(*this); return *this; }
 

  Field_DomainAC_D0 get_D0() const
   {
    return Field_DomainAC_D0((value>>0)&0x3);
   }
 
  Type_DomainAC & set_D0(Field_DomainAC_D0 field)
   {
    value=((Type(field)&0x3)<<0)|(value&0xFFFFFFFC);

    return *this;
   }
 

  Field_DomainAC_D1 get_D1() const
   {
    return Field_DomainAC_D1((value>>2)&0x3);
   }
 
  Type_DomainAC & set_D1(Field_DomainAC_D1 field)
   {
    value=((Type(field)&0x3)<<2)|(value&0xFFFFFFF3);

    return *this;
   }
 

  Field_DomainAC_D2 get_D2() const
   {
    return Field_DomainAC_D2((value>>4)&0x3);
   }
 
  Type_DomainAC & set_D2(Field_DomainAC_D2 field)
   {
    value=((Type(field)&0x3)<<4)|(value&0xFFFFFFCF);

    return *this;
   }
 

  Field_DomainAC_D3 get_D3() const
   {
    return Field_DomainAC_D3((value>>6)&0x3);
   }
 
  Type_DomainAC & set_D3(Field_DomainAC_D3 field)
   {
    value=((Type(field)&0x3)<<6)|(value&0xFFFFFF3F);

    return *this;
   }
 

  Field_DomainAC_D4 get_D4() const
   {
    return Field_DomainAC_D4((value>>8)&0x3);
   }
 
  Type_DomainAC & set_D4(Field_DomainAC_D4 field)
   {
    value=((Type(field)&0x3)<<8)|(value&0xFFFFFCFF);

    return *this;
   }
 

  Field_DomainAC_D5 get_D5() const
   {
    return Field_DomainAC_D5((value>>10)&0x3);
   }
 
  Type_DomainAC & set_D5(Field_DomainAC_D5 field)
   {
    value=((Type(field)&0x3)<<10)|(value&0xFFFFF3FF);

    return *this;
   }
 

  Field_DomainAC_D6 get_D6() const
   {
    return Field_DomainAC_D6((value>>12)&0x3);
   }
 
  Type_DomainAC & set_D6(Field_DomainAC_D6 field)
   {
    value=((Type(field)&0x3)<<12)|(value&0xFFFFCFFF);

    return *this;
   }
 

  Field_DomainAC_D7 get_D7() const
   {
    return Field_DomainAC_D7((value>>14)&0x3);
   }
 
  Type_DomainAC & set_D7(Field_DomainAC_D7 field)
   {
    value=((Type(field)&0x3)<<14)|(value&0xFFFF3FFF);

    return *this;
   }
 

  Field_DomainAC_D8 get_D8() const
   {
    return Field_DomainAC_D8((value>>16)&0x3);
   }
 
  Type_DomainAC & set_D8(Field_DomainAC_D8 field)
   {
    value=((Type(field)&0x3)<<16)|(value&0xFFFCFFFF);

    return *this;
   }
 

  Field_DomainAC_D9 get_D9() const
   {
    return Field_DomainAC_D9((value>>18)&0x3);
   }
 
  Type_DomainAC & set_D9(Field_DomainAC_D9 field)
   {
    value=((Type(field)&0x3)<<18)|(value&0xFFF3FFFF);

    return *this;
   }
 

  Field_DomainAC_D10 get_D10() const
   {
    return Field_DomainAC_D10((value>>20)&0x3);
   }
 
  Type_DomainAC & set_D10(Field_DomainAC_D10 field)
   {
    value=((Type(field)&0x3)<<20)|(value&0xFFCFFFFF);

    return *this;
   }
 

  Field_DomainAC_D11 get_D11() const
   {
    return Field_DomainAC_D11((value>>22)&0x3);
   }
 
  Type_DomainAC & set_D11(Field_DomainAC_D11 field)
   {
    value=((Type(field)&0x3)<<22)|(value&0xFF3FFFFF);

    return *this;
   }
 

  Field_DomainAC_D12 get_D12() const
   {
    return Field_DomainAC_D12((value>>24)&0x3);
   }
 
  Type_DomainAC & set_D12(Field_DomainAC_D12 field)
   {
    value=((Type(field)&0x3)<<24)|(value&0xFCFFFFFF);

    return *this;
   }
 

  Field_DomainAC_D13 get_D13() const
   {
    return Field_DomainAC_D13((value>>26)&0x3);
   }
 
  Type_DomainAC & set_D13(Field_DomainAC_D13 field)
   {
    value=((Type(field)&0x3)<<26)|(value&0xF3FFFFFF);

    return *this;
   }
 

  Field_DomainAC_D14 get_D14() const
   {
    return Field_DomainAC_D14((value>>28)&0x3);
   }
 
  Type_DomainAC & set_D14(Field_DomainAC_D14 field)
   {
    value=((Type(field)&0x3)<<28)|(value&0xCFFFFFFF);

    return *this;
   }
 

  Field_DomainAC_D15 get_D15() const
   {
    return Field_DomainAC_D15((value>>30)&0x3);
   }
 
  Type_DomainAC & set_D15(Field_DomainAC_D15 field)
   {
    value=((Type(field)&0x3)<<30)|(value&0x3FFFFFFF);

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
 
/* type Type_PID */ 

typedef uint32 Type_PID;

