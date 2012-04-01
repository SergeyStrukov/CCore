/* CPrintf.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_libc_CPrintf_h
#define CCore_inc_libc_CPrintf_h

#include <CCore/inc/libc/CDef.h>

namespace LibC_Internal {

/* functions */ 

template <class T> 
inline char DecDigit(T t) { return char( '0'+t ); }
 
template <class T> 
inline T PosSub(T a,T b) 
 {
  if( b<a ) return a-b;
  
  return 0;
 }
  
Size StrLen(const char *str);  
  
Size StrLen(const char *str,Size len);  
  
/* classes */ 

//enum PrintfPrefix;

//enum AlignFlags; 

//enum PrintfRegister;

struct PrintfFlags;

template <class SInt> struct ToUns;

class RevBuf;

template <class UInt> class DecFormat;

template <class UInt> class OctFormat;

template <class UInt> class HexFormat;

class NoSign;

class SignChar;

class SignChar2;

struct ParsePrintfPrefix;

template <class Out,class Arg> class PrintfContext;

/* enum PrintfPrefix */ 

enum PrintfPrefix
 {
  Printf_none,
  Printf_hh,
  Printf_h,
  Printf_l,
  Printf_ll,
  Printf_j,
  Printf_z,
  Printf_t,
  Printf_L
 };
 
/* enum AlignFlags */ 

enum AlignFlags
 {
  AlignRight,
  AlignLeft,
  AlignInternal
 }; 
 
/* enum PrintfRegister */ 

enum PrintfRegister
 {
  PrintfUpper,
  PrintfLower
 };
 
const char * GetHexDigits(PrintfRegister reg); 

char GetHexSign(PrintfRegister reg);
 
/* struct PrintfFlags */ 

struct PrintfFlags
 {
  bool minus;
  bool plus;
  bool space;
  bool pound;
  bool zero;
  
  const char * parse(const char *str);
 };
  
/* struct ToUns<SInt> */ 

template <> 
struct ToUns<int>
 {
  typedef unsigned Ret;
 };
 
template <> 
struct ToUns<long>
 {
  typedef unsigned long Ret;
 };
 
template <> 
struct ToUns<long long>
 {
  typedef unsigned long long Ret;
 };
 
/* class RevBuf */ 

class RevBuf
 {
   char buf[NumberBufSize];
   char *ptr;
   
  protected: 
  
   void put(char ch) { *(--ptr)=ch; }
   
  private:
   
   RevBuf(const RevBuf &) = delete ;
   
   void operator = (const RevBuf &) = delete ;
 
  public:
  
   RevBuf() { ptr=buf+NumberBufSize; }
   
   const char * getPtr() const { return ptr; }
   
   const char * getLim() const { return buf+NumberBufSize; }
   
   Size getSize() const { return Size( getLim()-getPtr() ); }
   
   template <class P,class Sign>
   void print(P &out,Sign sign,Size precision,AlignFlags align,Size width) const;
 };
  
template <class P,class Sign>
void RevBuf::print(P &out,Sign sign,Size precision,AlignFlags align,Size width) const
 {
  Size dsize=getSize();
  Size zpad=PosSub(precision,dsize);

  width=PosSub(width,dsize);
  width=PosSub(width,zpad);
  width=PosSub(width,sign.getSize());
  
  if( align==AlignRight ) out.pad(width,' '); 
    
  sign.print(out);
  
  if( align==AlignInternal )
    out.pad(zpad+width,'0');
  else
    out.pad(zpad,'0');
  
  out.put(getPtr(),dsize);
  
  if( align==AlignLeft ) out.pad(width,' '); 
 }
 
/* class DecFormat<UInt> */ 
 
template <class UInt> 
class DecFormat : public RevBuf
 {
  public:
  
   explicit DecFormat(UInt value)
    {
     for(; value ;value/=10) put( DecDigit(value%10) );
    }
 };
 
/* class OctFormat<UInt> */ 
 
template <class UInt> 
class OctFormat : public RevBuf
 {
  public:
   
   explicit OctFormat(UInt value)
    {
     for(; value ;value/=8) put( DecDigit(value%8) );
    }
 };
 
/* class HexFormat<UInt> */ 
 
template <class UInt> 
class HexFormat : public RevBuf
 {
  public:
  
   HexFormat(UInt value,PrintfRegister reg)
    {
     const char *dig=GetHexDigits(reg); 
    
     for(; value ;value/=16) put( dig[value%16] );
    }
 };
 
/* class NoSign */ 

class NoSign
 {
  public:
  
   NoSign() {}
   
   Size getSize() const { return 0; }
   
   template <class P>
   void print(P &) const {}
 };
 
/* class SignChar */ 

class SignChar
 {
   char ch;
   
  public:
  
   explicit SignChar(char ch_) : ch(ch_) {}
   
   Size getSize() const { return 1; }
   
   template <class P>
   void print(P &out) const { out.put(ch); }
 };
 
/* class SignChar2 */ 

class SignChar2
 {
   char ch1;
   char ch2;
   
  public:
  
   SignChar2(char ch1_,char ch2_) : ch1(ch1_),ch2(ch2_) {}
   
   Size getSize() const { return 2; }
   
   template <class P>
   void print(P &out) const 
    { 
     out.put(ch1); 
     out.put(ch2); 
    }
 };
 
/* struct ParsePrintfPrefix */ 

struct ParsePrintfPrefix
 {
  PrintfPrefix value;
  const char *str;
  
  explicit ParsePrintfPrefix(const char *str);
 };
 
/* class PrintfContext<Out,Arg> */ 

template <class Out,class Arg>
class PrintfContext
 {
   Out out;
   Arg arg;
   
   Size count;
   
   PrintfFlags flags;
   
   Size width;
   bool no_precision;
   Size precision;
   
  private: 
  
   const char * parse_width(const char *str); 
   
   const char * parse_precision(const char *str); 
   
   template <class SInt>
   bool format_sint();
 
   bool format_sint(PrintfPrefix prefix);
 
   template <class UInt>
   bool format_uint(UInt value);
   
   template <class UInt>
   bool format_uint();
 
   bool format_uint_short(int unused);
   bool format_uint_short(unsigned unused);
   
   bool format_uint(PrintfPrefix prefix);
   
   template <class UInt>
   bool format_oct(UInt value);
 
   template <class UInt>
   bool format_oct();
   
   bool format_oct_short(int unused);
   bool format_oct_short(unsigned unused);
   
   bool format_oct(PrintfPrefix prefix);
   
   template <class UInt>
   bool format_hex(PrintfRegister reg,UInt value);
   
   template <class UInt>
   bool format_hex(PrintfRegister reg);
 
   bool format_hex_short(PrintfRegister reg,int unused);
   bool format_hex_short(PrintfRegister reg,unsigned unused);
   
   bool format_hex(PrintfRegister reg,PrintfPrefix prefix);
   
   bool format_char(char ch);
   
   bool format_char(PrintfPrefix prefix);
   
   bool format_str(const char *str);
   
   bool format_str(PrintfPrefix prefix);
   
   bool format_ptr(PrintfPrefix prefix);
   
   template <class SInt>
   bool format_cnt();
   
   bool format_cnt(PrintfPrefix prefix);
   
   bool format_percent(PrintfPrefix prefix);
   
   
   bool format_spec(PrintfPrefix prefix,char spec);
   
  public:
  
   PrintfContext(typename Out::InitType out_init,typename Arg::InitType arg_init)
    : out(out_init),arg(arg_init) {}
    
   void put(char ch)
    {
     out.put(ch);
     count++;
    }
    
   void put(const char *str,Size cnt) 
    {
     out.put(str,cnt);
     count+=cnt;
    }
    
   void pad(Size cnt,char ch) 
    {
     out.pad(cnt,ch);
     count+=cnt;
    }
    
   int format(const char *str); 
 };
 
template <class Out,class Arg>
const char * PrintfContext<Out,Arg>::parse_width(const char *str)
 {
  if( (*str)=='*' )
    {
     str++;
     
     int w=arg.template get<int>();
     
     if( w<0 )
       {
        flags.minus=true;
        width=-(Size)w;
       }
     else
       {
        width=(Size)w;
       }  
    }
  else
    {  
     ParseSize parse(str);
     
     width=parse.value;
     str=parse.str;
    }
  
  return str;
 }
 
template <class Out,class Arg>
const char * PrintfContext<Out,Arg>::parse_precision(const char *str)
 {
  if( (*str)=='.' )
    {
     str++;
     
     if( (*str)=='*' )
       {
        str++;
        
        precision=(Size)arg.template get<int>();
       }
     else
       {
        ParseSize parse(str);
        
        precision=parse.value;
        str=parse.str;
       } 
       
     no_precision=false;  
    }
  else
    {
     no_precision=true;  
    }
    
  return str;  
 }
 
template <class Out,class Arg>
template <class SInt>
bool PrintfContext<Out,Arg>::format_sint()
 {
  typedef typename ToUns<SInt>::Ret UInt;
 
  SInt value=arg.template get<SInt>();
  AlignFlags align=AlignRight;
  
  if( no_precision )
    {
     precision=1;
     
     if( flags.zero ) align=AlignInternal;
    }
    
  if( flags.minus ) align=AlignLeft; 
  
  if( value<0 )
    {
     DecFormat<UInt> dig(-(UInt)value);
     
     dig.print(*this,SignChar('-'),precision,align,width);
    }
  else
    {
     DecFormat<UInt> dig((UInt)value);
     
     if( flags.plus )
       dig.print(*this,SignChar('+'),precision,align,width);
     else if( flags.space ) 
       dig.print(*this,SignChar(' '),precision,align,width);
     else  
       dig.print(*this,NoSign(),precision,align,width);
    }
  
  return true;
 }
  
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_sint(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_hh : 
     case Printf_h : 
     case Printf_none : return format_sint<int>();
               
     case Printf_l :    return format_sint<long>();
     
     case Printf_ll :   return format_sint<long long>();
     
     case Printf_j :    return format_sint<Format_sj_t>();
               
     case Printf_z :    return format_sint<Format_sz_t>();
               
     case Printf_t :    return format_sint<Format_st_t>();
               
     default:           return false;
    }
 }
  
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_uint(UInt value)
 {
  AlignFlags align=AlignRight;
  
  if( no_precision )
    {
     precision=1;
     
     if( flags.zero ) align=AlignInternal;
    }
    
  if( flags.minus ) align=AlignLeft; 
  
  DecFormat<UInt> dig(value);
     
  dig.print(*this,NoSign(),precision,align,width);
    
  return true;
 }
  
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_uint()
 {
  UInt value=arg.template get<UInt>();
  
  return format_uint(value);
 }
  
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_uint_short(int)
 {
  int value=arg.template get<int>();
  
  return format_uint((unsigned)value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_uint_short(unsigned)
 {
  unsigned value=arg.template get<unsigned>();
  
  return format_uint(value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_uint(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_hh :   return format_uint_short((unsigned char)0);
      
     case Printf_h :    return format_uint_short((unsigned short)0);
     
     case Printf_none : return format_uint<unsigned>();
               
     case Printf_l :    return format_uint<unsigned long>();
               
     case Printf_ll :   return format_uint<unsigned long long>();
               
     case Printf_j :    return format_uint<Format_uj_t>();
               
     case Printf_z :    return format_uint<Format_uz_t>();
               
     case Printf_t :    return format_uint<Format_ut_t>();
               
     default:           return false;
    }
 }
    
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_oct(UInt value)
 {
  AlignFlags align=AlignRight;
  
  if( no_precision )
    {
     precision=1;
     
     if( flags.zero ) align=AlignInternal;
    }
    
  if( flags.minus ) align=AlignLeft; 
  
  OctFormat<UInt> dig(value);
     
  if( flags.pound )   
    {
     Size s=dig.getSize();
     
     if( precision<=s ) precision=s+1;
    }
    
  dig.print(*this,NoSign(),precision,align,width);
  
  return true;
 }
  
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_oct()
 {
  UInt value=arg.template get<UInt>();
  
  return format_oct(value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_oct_short(int)
 {
  int value=arg.template get<int>();
  
  return format_oct((unsigned)value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_oct_short(unsigned)
 {
  unsigned value=arg.template get<unsigned>();
  
  return format_oct(value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_oct(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_hh :   return format_oct_short((unsigned char)0);
   
     case Printf_h :    return format_oct_short((unsigned short)0);    

     case Printf_none : return format_oct<unsigned>();
               
     case Printf_l :    return format_oct<unsigned long>();
               
     case Printf_ll :   return format_oct<unsigned long long>();
               
     case Printf_j :    return format_oct<Format_uj_t>();
               
     case Printf_z :    return format_oct<Format_uz_t>();
               
     case Printf_t :    return format_oct<Format_ut_t>();
               
     default:           return false;
    }
 }
    
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_hex(PrintfRegister reg,UInt value)
 {
  AlignFlags align=AlignRight;
  
  if( no_precision )
    {
     precision=1;
     
     if( flags.zero ) align=AlignInternal;
    }
    
  if( flags.minus ) align=AlignLeft; 
  
  HexFormat<UInt> dig(value,reg);
     
  if( value && flags.pound )   
    dig.print(*this,SignChar2('0',GetHexSign(reg)),precision,align,width);
  else
    dig.print(*this,NoSign(),precision,align,width);
  
  return true;
 }
  
template <class Out,class Arg>
template <class UInt>
bool PrintfContext<Out,Arg>::format_hex(PrintfRegister reg)
 {
  UInt value=arg.template get<UInt>();
  
  return format_hex(reg,value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_hex_short(PrintfRegister reg,int)
 {
  int value=arg.template get<int>();
  
  return format_hex(reg,(unsigned)value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_hex_short(PrintfRegister reg,unsigned)
 {
  unsigned value=arg.template get<unsigned>();
  
  return format_hex(reg,value);
 }

template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_hex(PrintfRegister reg,PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_hh :   return format_hex_short(reg,(unsigned char)0);
      
     case Printf_h :    return format_hex_short(reg,(unsigned short)0);
     
     case Printf_none : return format_hex<unsigned>(reg);
               
     case Printf_l :    return format_hex<unsigned long>(reg);
               
     case Printf_ll :   return format_hex<unsigned long long>(reg);
               
     case Printf_j :    return format_hex<Format_uj_t>(reg);
               
     case Printf_z :    return format_hex<Format_uz_t>(reg);
               
     case Printf_t :    return format_hex<Format_ut_t>(reg);
               
     default:           return false;
    }
 }
    
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_char(char ch)
 {
  if( width>1 )
    {
     if( flags.minus )
       {
        put(ch);
        pad(width-1,' ');
       }
     else
       {
        pad(width-1,' ');
        put(ch);
       }
    }
  else
    {
     put(ch);
    }
  
  return true;
 }
  
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_char(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_none : return format_char((char)arg.template get<int>());
     
     // case Printf_l : // TODO
     
     default:           return false;
    }
 }
    
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_str(const char *str)
 {
  Size len=no_precision?StrLen(str):StrLen(str,precision);
  Size spad=PosSub(width,len);
  
  if( flags.minus ) 
    {
     put(str,len);
     pad(spad,' ');
    }
  else
    {
     pad(spad,' ');
     put(str,len);
    }  
 
  return true;
 }
 
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_str(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_none : return format_str(arg.template get<const char *>());
     
     // case Printf_l : // TODO
     
     default : return false;
    }
 
  return true;
 }
    
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_ptr(PrintfPrefix prefix)
 {
  if( prefix!=Printf_none ) return false;
 
  const void *value=arg.template get<const void *>(); 
  
  HexFormat<PtrValue> dig((PtrValue)value,PrintfUpper);

  put('[');
  
  dig.print(*this,NoSign(),PtrValueHexSize,AlignLeft,0);
  
  put(']');
 
  return true;
 }
    
template <class Out,class Arg>
template <class SInt>
bool PrintfContext<Out,Arg>::format_cnt()
 {
  SInt *ret=arg.template get<SInt *>();
  
  (*ret)=(SInt)count;
  
  return true;
 }
    
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_cnt(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_hh :   return format_cnt<signed char>();
     
     case Printf_h :    return format_cnt<short>();
     
     case Printf_none : return format_cnt<int>();
     
     case Printf_l :    return format_cnt<long>();
               
     case Printf_ll :   return format_cnt<long long>();
               
     case Printf_j :    return format_cnt<Format_sj_t>();
               
     case Printf_z :    return format_cnt<Format_sz_t>();
               
     case Printf_t :    return format_cnt<Format_st_t>();
               
     default: return false;
    }
 }
  
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_percent(PrintfPrefix prefix)
 {
  switch( prefix )
    {
     case Printf_none : return format_char('%');
     
     default:           return false;
    }
 }
  
template <class Out,class Arg>
bool PrintfContext<Out,Arg>::format_spec(PrintfPrefix prefix,char spec)
 {
  switch( spec )
    {
     case 'd' : case 'i' :
     return format_sint(prefix);
          
     case 'u' :
     return format_uint(prefix);
          
     case 'o' :
     return format_oct(prefix);
          
     case 'x' :
     return format_hex(PrintfLower,prefix);
          
     case 'X' :
     return format_hex(PrintfUpper,prefix);
          
     //case 'a' : TODO 
          
     //case 'A' : TODO
          
     //case 'f' : TODO
          
     //case 'F' : TODO
          
     //case 'e' : TODO
          
     //case 'E' : TODO
          
     //case 'g' : TODO
          
     //case 'G' : TODO
          
     case 'c' :
     return format_char(prefix);
          
     case 's' :
     return format_str(prefix);
          
     case 'p' :
     return format_ptr(prefix);
          
     case 'n' :
     return format_cnt(prefix);
          
     case '%' :
     return format_percent(prefix);
          
     default: return false;
    }
 }
    
template <class Out,class Arg>
int PrintfContext<Out,Arg>::format(const char *str)
 {
  count=0;
  
  for(; char ch=*str ;str++)
    if( ch=='%' )
      {
       str=flags.parse(str+1);
       str=parse_width(str);
       str=parse_precision(str);
       
       ParsePrintfPrefix prefix(str);
       
       str=prefix.str;
       
       if( !format_spec(prefix.value,*str) )
         {
          out.complete();  
          
          return -1;
         }
      }
    else
      {
       put(ch);
      }
      
  out.complete();    
      
  if( !out ) return -1;   
      
  return (int)count;    
 }
 
} // namespace LibC_Internal
 
#endif


