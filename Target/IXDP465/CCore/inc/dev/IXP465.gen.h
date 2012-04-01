/* IXP465.gen.h */ 

/* struct Type_CPUStatus */ 

enum Bits_CPUStatus : uint32
 {
  CPUStatus_T = 0x00000020,
  CPUStatus_F = 0x00000040,
  CPUStatus_I = 0x00000080,
  CPUStatus_Q = 0x08000000,
  CPUStatus_V = 0x10000000,
  CPUStatus_C = 0x20000000,
  CPUStatus_Z = 0x40000000,
  CPUStatus_N = 0x80000000
 };
 
inline Bits_CPUStatus operator | (Bits_CPUStatus a,Bits_CPUStatus b)
 { return Bits_CPUStatus(uint32(a)|uint32(b)); }
 
enum Field_CPUStatus_Mode : uint32
 {
  CPUStatus_Mode_User  = 0x10,
  CPUStatus_Mode_Svr   = 0x13,
  CPUStatus_Mode_FIQ   = 0x11,
  CPUStatus_Mode_IRQ   = 0x12,
  CPUStatus_Mode_Abort = 0x17,
  CPUStatus_Mode_Undef = 0x1B,
  CPUStatus_Mode_Sys   = 0x1F
 };
 
struct PrintField_CPUStatus_Mode
 {
  Field_CPUStatus_Mode field;

  explicit PrintField_CPUStatus_Mode(Field_CPUStatus_Mode field_) : field(field_) {}
 
  template <class P>
  void print(P &out) const
   {
    switch( field )
      {
       case 0x10 : Putobj(out,"User"); break;
       case 0x13 : Putobj(out,"Svr"); break;
       case 0x11 : Putobj(out,"FIQ"); break;
       case 0x12 : Putobj(out,"IRQ"); break;
       case 0x17 : Putobj(out,"Abort"); break;
       case 0x1B : Putobj(out,"Undef"); break;
       case 0x1F : Putobj(out,"Sys"); break;

       default: Putobj(out,uint32(field));
      }
   }
 };
 
inline PrintField_CPUStatus_Mode GetTextDesc(Field_CPUStatus_Mode field)
 {
  return PrintField_CPUStatus_Mode(field);
 }
 
struct Type_CPUStatus
 {
  typedef uint32 Type;

  Type value;


  explicit Type_CPUStatus(Type value_=0) : value(value_) {}
 

  operator Type() const { return value; }
 
  void operator = (Type value_) { value=value_; }
 
  template <class Bar>
  Type_CPUStatus & setTo(Bar &bar) { bar.set_CPUStatus(*this); return *this; }
 

  template <class Bar>
  Type_CPUStatus & setTo(Bar &bar,uint32 ind) { bar.set_CPUStatus(*this,ind); return *this; }
 

  template <class T>
  Type_CPUStatus & set(T to) { to(*this); return *this; }
 

  Type_CPUStatus & setbit(Bits_CPUStatus bits) { value|=Type(bits); return *this; }
 
  Type_CPUStatus & setbitIf(bool cond,Bits_CPUStatus bits) { if( cond ) value|=Type(bits); return *this; }
 
  Type_CPUStatus & clearbit(Bits_CPUStatus bits) { value&=~Type(bits); return *this; }
 
  Type_CPUStatus & clearbitIf(bool cond,Bits_CPUStatus bits) { if( cond ) value&=~Type(bits); return *this; }
 
  Type maskbit(Bits_CPUStatus bits) const { return value&bits; }
 
  bool testbit(Bits_CPUStatus bits) const { return (value&bits)==Type(bits); }
 

  Field_CPUStatus_Mode get_Mode() const
   {
    return Field_CPUStatus_Mode((value>>0)&0x1F);
   }
 
  Type_CPUStatus & set_Mode(Field_CPUStatus_Mode field)
   {
    value=((Type(field)&0x1F)<<0)|(value&0xFFFFFFE0);

    return *this;
   }
 

  template <class P>
  void print(P &out) const
   {
    bool first=true;

    if( value&CPUStatus_T )
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

    if( value&CPUStatus_F )
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

    if( value&CPUStatus_I )
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

    if( value&CPUStatus_Q )
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

    if( value&CPUStatus_V )
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

    if( value&CPUStatus_C )
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

    if( value&CPUStatus_Z )
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

    if( value&CPUStatus_N )
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

    if( first ) out.put('0');
   }
 };
 
