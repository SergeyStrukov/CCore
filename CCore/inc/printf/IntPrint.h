/* IntPrint.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_printf_IntPrint_h
#define CCore_inc_printf_IntPrint_h
 
#include <CCore/inc/StrParse.h>
 
namespace CCore {

/* consts */ 

const unsigned MinIntBase =  2 ;
const unsigned MaxIntBase = 16 ;
 
/* classes */ 

//enum IntShowSign;

//enum IntAlign;

//enum IntShowBase;

struct IntPrintOpt;

class IntToStr;

template <class UInt> class UIntPrint;

template <class SInt> class SIntPrint;

struct PrintDumpOptType;

template <class UInt> class PrintDumpType;

/* enum IntShowSign */

enum IntShowSign
 {
  IntShowMinus,
  IntShowPlus,
  
  IntShowSignDefault = IntShowMinus
 };
 
template <class Dev>
void Parse_empty(Dev &dev,IntShowSign &ret)
 {
  if( ParseChar_try(dev,'+') )
    {
     ret=IntShowPlus;
    }
  else
    {
     ret=IntShowSignDefault;
    }
 }

/* enum IntAlign */
 
enum IntAlign
 {
  IntAlignLeft,
  IntAlignRight,
  IntAlignInternal,
  
  IntAlignDefault = IntAlignRight
 };
 
template <class Dev>
void Parse_empty(Dev &dev,IntAlign &ret)
 {
  typename Dev::Peek peek(dev);
  
  if( !peek )
    {
     ret=IntAlignDefault;
    }
  else
    {
     switch( *peek )
       {
        case 'l' : case 'L' : ret=IntAlignLeft;     ++dev; break;
        case 'r' : case 'R' : ret=IntAlignRight;    ++dev; break;
        case 'i' : case 'I' : ret=IntAlignInternal; ++dev; break;
        
        default: ret=IntAlignDefault;
       }
    }
 }
 
/* enum IntShowBase */

enum IntShowBase
 {
  IntShowNoBase,
  IntShowBaseSuffix,
  IntShowBasePrefix,
  
  IntShowBaseDefault = IntShowNoBase
 };
 
template <class Dev>
void Parse_IntBase(Dev &dev,unsigned &base,IntShowBase &show_base)
 {
  if( ParseChar_try(dev,'.') )  
    {
     typename Dev::Peek peek(dev);
  
     if( !peek )
       {
        dev.fail();
        
        return;
       }
       
     switch( *peek )
       {
        case 'b' : case 'B' : base=2 ; show_base=IntShowBaseSuffix; ++dev; break;
        case 'h' : case 'H' : base=16; show_base=IntShowBaseSuffix; ++dev; break;
        case 'x' : case 'X' : base=16; show_base=IntShowBasePrefix; ++dev; break;
        case 'c' : case 'C' : base=0 ; show_base=IntShowNoBase    ; ++dev; break;
        
        default:
         {
          ParseUInt(dev,base,MinIntBase,MaxIntBase);
          
          show_base=IntShowBaseDefault;
         }
       }
    }
  else
    {
     base=10;
     
     show_base=IntShowBaseDefault;
    }  
 }
 
/* struct IntPrintOpt */ 

struct IntPrintOpt
 {
  ulen width;
  unsigned base; // 2..16, 0 for c
  IntAlign align;
  IntShowSign show_sign;
  IntShowBase show_base;
  
  void setDefault()
   {
    width=0;
    base=10;
    align=IntAlignDefault;
    show_sign=IntShowSignDefault;
    show_base=IntShowBaseDefault;
   }
  
  IntPrintOpt() { setDefault(); }
  
  IntPrintOpt(const char *ptr,const char *lim);
  
  //
  // [+][width=0][.base|.b|.h|.x|.c=.10][l|L|r|R|i|I=R]
  //
 };
 
/* class IntToStr */ 
 
class IntToStr : NoCopy
 {
   static const ulen Len = MaxBitLen+16 ;
 
   unsigned base;
   IntShowSign show_sign;
   IntShowBase show_base;
   bool nok;
   
   char buf[Len];
   
   char *ptr;
   char *split;
   char *lim;
   
  private:
  
   bool reset() { ptr=split=lim=buf+Len; return nok; }
   
   void put(char ch) { *(--ptr)=ch; }
 
   template <class UInt>
   void do_uint_nosign(UInt value)
    {
     if( show_base==IntShowBaseSuffix )
       switch( base )
         {
          case 2  : put('b'); break;
          case 16 : put('h'); break;
         }
         
     if( value )    
       {
        for(; value ;value/=base) put("0123456789ABCDEF"[value%base]);
       }
     else
       {
        put('0');
       }

     split=ptr;
         
     if( show_base==IntShowBasePrefix )    
       {
        put('x');
        put('0');
       }
    }
   
  public:
  
   explicit IntToStr(unsigned base_=10,
                     IntShowSign show_sign_=IntShowSignDefault,
                     IntShowBase show_base_=IntShowBaseDefault)
    : base(base_),
      show_sign(show_sign_),
      show_base(show_base_)
    {
     if( base==0 )
       {
        nok = ( show_base!=IntShowNoBase || show_sign!=IntShowMinus ) ;
       }
     else
       {
        nok = ( base<MinIntBase || base>MaxIntBase || 
                ( show_base==IntShowBasePrefix && base!=16 ) || 
                ( show_base==IntShowBaseSuffix && base!=16 && base!=2 ) ) ;
       }      
             
     reset();        
    }     
    
   bool operator ! () const { return nok; }           
 
   template <class UInt>
   void do_uint(UInt value)
    {
     if( reset() ) return;
     
     if( base==0 )
       {
        put((char)value);
       }
     else
       {
        do_uint_nosign<UInt>(value);
        
        if( value!=0 && show_sign==IntShowPlus ) put('+');
       }
    }
   
   template <class SInt,class UInt>
   void do_sint(SInt value)
    {
     if( reset() ) return;
     
     if( base==0 )
       {
        put((char)value);
       }
     else
       {
        if( value<0 )
          {
           do_uint_nosign<UInt>(UIntFunc<UInt>::Neg((UInt)value));
           
           put('-');
          }
        else
          {
           do_uint_nosign<UInt>((UInt)value);
        
           if( value!=0 && show_sign==IntShowPlus ) put('+');
          }
       }
    }                          
   
   template <class UInt>
   void do_promote_uint(UInt value) 
    { 
     do_uint<typename Meta::PromoteUInt<UInt>::Type>(value); 
    }
   
   template <class SInt>
   void do_promote_sint(SInt value) 
    { 
     do_sint<typename Meta::PromoteSInt<SInt>::SType,typename Meta::PromoteSInt<SInt>::UType>(value); 
    }
   
   PtrLen<const char> getStr() const { return Range_const(ptr,lim); }
   
   PtrLen<const char> getPrefix() const { return Range_const(ptr,split); }
   PtrLen<const char> getSuffix() const { return Range_const(split,lim); }
   
   template <class P>
   void print(P &out,ulen width,IntAlign align) const
    {
     auto str=getStr();

     if( width>str.len )
       {
        ulen extra=width-str.len;
        
        if( base==0 && align==IntAlignInternal ) align=IntAlignRight;
        
        switch( align )
          {
           case IntAlignLeft : 
            {
             out.put(str.ptr,str.len);
             out.put(' ',extra);
            }
           break;
           
           case IntAlignRight :
            {
             out.put(' ',extra);
             out.put(str.ptr,str.len);
            }
           break;
           
           case IntAlignInternal :
            {
             auto pref=getPrefix();
             auto suff=getSuffix();
             
             out.put(pref.ptr,pref.len);
             out.put('0',extra);
             out.put(suff.ptr,suff.len);
            }
           break;
          }
       }
     else
       {
        out.put(str.ptr,str.len);
       }
    }
 };
 
/* class UIntPrint<UInt> */  

template <class UInt> 
class UIntPrint
 {
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::UIntPrint<UInt> : UInt must be an unsigned integral type");

  private:

   UInt value;
 
  public:
  
   explicit UIntPrint(UInt value_) : value(value_) {}
   
   typedef IntPrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     IntToStr dev(opt.base,opt.show_sign,opt.show_base);

     dev.do_promote_uint<UInt>(value);
     
     dev.print(out,opt.width,opt.align);
    }
 };
 
/* class SIntPrint<SInt> */ 

template <class SInt> 
class SIntPrint
 {
   static_assert( Meta::IsSInt<SInt>::Ret ,"CCore::SIntPrint<SInt> : SInt must be a signed integral type");

  private:

   SInt value;
 
  public:
  
   explicit SIntPrint(SInt value_) : value(value_) {}
   
   typedef IntPrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     IntToStr dev(opt.base,opt.show_sign,opt.show_base);

     dev.do_promote_sint<SInt>(value);
     
     dev.print(out,opt.width,opt.align);
    }
 };
 
/* struct PrintDumpOptType */  

struct PrintDumpOptType
 {
  static const ulen Default_line_len = 16 ;
 
  ulen width;
  ulen line_len;
    
  void setDefault()
   {
    width=0;
    line_len=Default_line_len;
   }
   
  PrintDumpOptType() { setDefault(); }
    
  PrintDumpOptType(const char *ptr,const char *lim);
  
  //
  // [width=0][.line_len=16]
  //
  
  template <class UInt>
  void correct()
   {
    if( line_len==0 ) line_len=1;
    
    if( width==0 ) width=Meta::HexWidth<UInt>::Ret;
   }
 };
 
/* class PrintDumpType<UInt> */ 

template <class UInt>
class PrintDumpType
 {
   static_assert( Meta::IsUInt<UInt>::Ret ,"CCore::PrintDumpType<UInt> : UInt must be an unsigned integral type");

  private:
   
   PtrLen<const UInt> data;
 
  public:
  
   explicit PrintDumpType(PtrLen<const UInt> data_) : data(data_) {}
  
   typedef PrintDumpOptType PrintOptType;
   
   class Engine : NoCopy
    {
      IntToStr dev;
      ulen width;
      
     public: 
      
      explicit Engine(ulen width_) : dev(16),width(width_) {}
      
      template <class P>
      void print(P &out,PtrLen<const UInt> data)
       {
        if( +data )
          {
           dev.do_promote_uint<UInt>(*data);
             
           dev.print(out,width,IntAlignInternal);
           
           for(++data; +data ;++data)
             {
              out.put(' ');
              
              dev.do_promote_uint<UInt>(*data);
             
              dev.print(out,width,IntAlignInternal);
             }
          }
       }
    };
   
   template <class P> 
   void print(P &out,PrintOptType opt) const
    {
     opt.correct<UInt>();
   
     PtrLen<const UInt> cur(data);
     
     Engine engine(opt.width);
    
     while( cur.len>opt.line_len )
       {
        engine.print(out,cur+=opt.line_len);
        
        out.put('\n');
       }
      
     engine.print(out,cur);
    }
 };
 
/* functions */  
 
template <class UInt> 
PrintDumpType<UInt> PrintDump(const UInt *ptr,ulen len) { return PrintDumpType<UInt>(Range(ptr,len)); }
 
template <class UInt> 
PrintDumpType<UInt> PrintDump(PtrLen<UInt> data) { return PrintDumpType<UInt>(Range_const(data)); }
 
template <class UInt> 
PrintDumpType<UInt> PrintDump(PtrLen<const UInt> data) { return PrintDumpType<UInt>(data); }
 
} // namespace CCore
 
#endif
 

