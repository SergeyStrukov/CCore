/* CScanf.h */ 
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

#ifndef CCore_inc_libc_CScanf_h
#define CCore_inc_libc_CScanf_h

#include <CCore/inc/libc/CDef.h>

namespace LibC_Internal {

/* enum ScanfPrefix */ 

enum ScanfPrefix
 {
  Scanf_none,
  Scanf_hh,
  Scanf_h,
  Scanf_l,
  Scanf_ll,
  Scanf_j,
  Scanf_z,
  Scanf_t,
  Scanf_L
 };
 
/* classes */

struct Peek;

struct ParseScanfPrefix;

template <class In,class Arg> class ScanfContext;

/* struct Peek */

struct Peek
 {
  char ch;
  bool ok;
  
  Peek() : ch(0),ok(false) {}
  
  Peek(char ch_) : ch(ch_),ok(true) {}
  
  bool operator + () const { return ok; }
  
  bool operator ! () const { return !ok; }
 };

/* struct ParseScanfPrefix */ 

struct ParseScanfPrefix
 {
  ScanfPrefix value;
  const char *str;
  
  explicit ParseScanfPrefix(const char *str);
 };
 
/* class ScanfContext<In,Arg> */

template <class In,class Arg> 
class ScanfContext 
 {
   In in;
   Arg arg;
   
   Size item_count;
   Size in_count;
   
   bool suppress;
   Size width;
   
  private:
   
   template <class SInt,class UInt>
   Size set_signed(bool neg,UInt value);
   
   template <class UInt1,class UInt>
   Size set_unsigned(bool neg,UInt value);
   
  private: 
   
   void scan_space();
   
   bool scan_char(char ch);
   
   bool scan_percent(ScanfPrefix prefix);
   
   bool scan_neg();
   
   template <class SInt,class UInt>
   bool scan_dec();
   
   bool scan_dec(ScanfPrefix prefix);
   
   template <class SInt,class UInt>
   bool scan_mix();
   
   bool scan_mix(ScanfPrefix prefix);
   
   template <class UInt1,class UInt>
   bool scan_oct();
   
   bool scan_oct(ScanfPrefix prefix);
   
   template <class UInt1,class UInt>
   bool scan_uns();
   
   bool scan_uns(ScanfPrefix prefix);
   
   template <class UInt1,class UInt>
   bool scan_hex();
   
   bool scan_hex(ScanfPrefix prefix);
   
   bool scan_ch(ScanfPrefix prefix);
   bool scan_str(ScanfPrefix prefix);
   bool scan_count(ScanfPrefix prefix);
   
   bool scan_spec(ScanfPrefix prefix,char spec);
   
  private: 
  
   Peek peek() { return in.peek(); }
   
   void next() { in_count++; in.next(); }
   
   Peek peek_width() 
    { 
     if( !width ) return Peek();
     
     return in.peek(); 
    }
   
   void next_width() 
    { 
     in_count++;
     width--;
     
     in.next();  
    }
   
  public:
   
   ScanfContext(typename In::InitType in_init,typename Arg::InitType arg_init) 
    : in(in_init),arg(arg_init) {}
   
   int scan(const char *str);
 };
 
template <class In,class Arg> 
template <class SInt,class UInt>
Size ScanfContext<In,Arg>::set_signed(bool neg,UInt value)
 {
  if( suppress ) return 0;
  
  SInt *out=arg.template get<SInt>();
  
  if( neg )
    SetNegInt(out,value);
  else
    SetPosInt(out,value);
  
  return 1;
 }

template <class In,class Arg> 
template <class UInt1,class UInt>
Size ScanfContext<In,Arg>::set_unsigned(bool neg,UInt value)
 {
  if( suppress ) return 0;
  
  UInt1 *out=arg.template get<UInt1>();
  
  if( neg )
    *out=(UInt1)(UInt)-value;
  else
    *out=(UInt1)value;
  
  return 1;
 }

template <class In,class Arg> 
void ScanfContext<In,Arg>::scan_space()
 {
  for(;;)
    {
     Peek p=peek();
  
     if( !p || !IsSpace(p.ch) ) break;
     
     next();
    }
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_char(char ch)
 {
  Peek p=peek();
  
  if( !p || p.ch!=ch ) return false;
  
  next();
  
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_percent(ScanfPrefix prefix)
 {
  if( prefix!=Scanf_none || suppress || width ) return false;
  
  return scan_char('%');
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_neg()
 {
  Peek p=peek_width();
 
  if( !p ) return false;
 
  if( p.ch=='+' )
    {
     next_width();
     
     return false;
    }
  
  if( p.ch=='-' )
    {
     next_width();
     
     return true;
    }
  
  return false;
 }

template <class In,class Arg> 
template <class SInt,class UInt>
bool ScanfContext<In,Arg>::scan_dec()
 {
  bool neg=scan_neg();
  
  UInt value;

  {
   Peek p=peek_width();
     
   if( !p ) return false;
      
   int dig=DecValue(p.ch);
      
   if( dig<0 ) return false;
      
   value=dig;
      
   next_width();
  }
     
  for(;;)
    {
     Peek p=peek_width();
       
     if( !p ) break;
        
     int dig=DecValue(p.ch);
        
     if( dig<0 ) break;
        
     value=10*value+dig;
        
     next_width();
    }
  
  item_count+=set_signed<SInt>(neg,value);
     
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_dec(ScanfPrefix prefix)
 {
  scan_space();
  
  if( !width ) width=Size(-1);

  switch( prefix )
    {
     case Scanf_none : return scan_dec<int,unsigned>();
     case Scanf_hh   : return scan_dec<signed char,unsigned>();
     case Scanf_h    : return scan_dec<short,unsigned>();
     case Scanf_l    : return scan_dec<long,unsigned long>();
     case Scanf_ll   : return scan_dec<long long,unsigned long long>();
     case Scanf_j    : return scan_dec<Format_sj_t,Format_uj_t>();
     case Scanf_z    : return scan_dec<Format_sz_t,Format_uz_t>();
     case Scanf_t    : return scan_dec<Format_st_t,Format_ut_t>();
     
     default: return false;
    }
 }

template <class In,class Arg> 
template <class SInt,class UInt>
bool ScanfContext<In,Arg>::scan_mix()
 {
  bool neg=scan_neg();
  
  UInt value;

  {
   Peek p=peek_width();
     
   if( !p ) return false;
      
   int dig=DecValue(p.ch);
      
   if( dig<0 ) return false;
      
   value=dig;
      
   next_width();
  }

  if( value==0 )
    {
     bool hex=false;
     
     {
      Peek p=peek_width();
      
      if( +p && ( p.ch=='x' || p.ch=='X' ) )
        {
         hex=true;
         
         next_width();
         
         {
          Peek p=peek_width();
            
          if( !p ) return false;
             
          int dig=HexValue(p.ch);
             
          if( dig<0 ) return false;
             
          value=dig;
             
          next_width();
         }
        }
     } 
     
     if( hex )
       {
        for(;;)
          {
           Peek p=peek_width();
             
           if( !p ) break;
              
           int dig=HexValue(p.ch);
              
           if( dig<0 ) break;
              
           value=16*value+dig;
              
           next_width();
          }
       }
     else
       {
        for(;;)
          {
           Peek p=peek_width();
             
           if( !p ) break;
              
           int dig=OctValue(p.ch);
              
           if( dig<0 ) break;
              
           value=8*value+dig;
              
           next_width();
          }
       }
    }
  else
    {
     for(;;)
       {
        Peek p=peek_width();
          
        if( !p ) break;
           
        int dig=DecValue(p.ch);
           
        if( dig<0 ) break;
           
        value=10*value+dig;
           
        next_width();
       }
    }
  
  item_count+=set_signed<SInt>(neg,value);
     
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_mix(ScanfPrefix prefix)
 {
  scan_space();
  
  if( !width ) width=Size(-1);

  switch( prefix )
    {
     case Scanf_none : return scan_mix<int,unsigned>();
     case Scanf_hh   : return scan_mix<signed char,unsigned>();
     case Scanf_h    : return scan_mix<short,unsigned>();
     case Scanf_l    : return scan_mix<long,unsigned long>();
     case Scanf_ll   : return scan_mix<long long,unsigned long long>();
     case Scanf_j    : return scan_mix<Format_sj_t,Format_uj_t>();
     case Scanf_z    : return scan_mix<Format_sz_t,Format_uz_t>();
     case Scanf_t    : return scan_mix<Format_st_t,Format_ut_t>();
     
     default: return false;
    }
 }

template <class In,class Arg> 
template <class UInt1,class UInt>
bool ScanfContext<In,Arg>::scan_oct()
 {
  bool neg=scan_neg();
  
  UInt value;

  {
   Peek p=peek_width();
     
   if( !p ) return false;
      
   int dig=OctValue(p.ch);
      
   if( dig<0 ) return false;
      
   value=dig;
      
   next_width();
  }
     
  for(;;)
    {
     Peek p=peek_width();
       
     if( !p ) break;
        
     int dig=OctValue(p.ch);
        
     if( dig<0 ) break;
        
     value=8*value+dig;
        
     next_width();
    }
  
  item_count+=set_unsigned<UInt1>(neg,value);
     
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_oct(ScanfPrefix prefix)
 {
  scan_space();
  
  if( !width ) width=Size(-1);

  switch( prefix )
    {
     case Scanf_none : return scan_oct<unsigned,unsigned>();
     case Scanf_hh   : return scan_oct<unsigned char,unsigned>();
     case Scanf_h    : return scan_oct<unsigned short,unsigned>();
     case Scanf_l    : return scan_oct<unsigned long,unsigned long>();
     case Scanf_ll   : return scan_oct<unsigned long long,unsigned long long>();
     case Scanf_j    : return scan_oct<Format_uj_t,Format_uj_t>();
     case Scanf_z    : return scan_oct<Format_uz_t,Format_uz_t>();
     case Scanf_t    : return scan_oct<Format_ut_t,Format_ut_t>();
     
     default: return false;
    }
 }

template <class In,class Arg> 
template <class UInt1,class UInt>
bool ScanfContext<In,Arg>::scan_uns()
 {
  bool neg=scan_neg();
  
  UInt value;

  {
   Peek p=peek_width();
     
   if( !p ) return false;
      
   int dig=DecValue(p.ch);
      
   if( dig<0 ) return false;
      
   value=dig;
      
   next_width();
  }
  
  for(;;)
    {
     Peek p=peek_width();
       
     if( !p ) break;
        
     int dig=DecValue(p.ch);
        
     if( dig<0 ) break;
        
     value=10*value+dig;
        
     next_width();
    }
  
  item_count+=set_unsigned<UInt1>(neg,value);
     
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_uns(ScanfPrefix prefix)
 {
  scan_space();
  
  if( !width ) width=Size(-1);

  switch( prefix )
    {
     case Scanf_none : return scan_uns<unsigned,unsigned>();
     case Scanf_hh   : return scan_uns<unsigned char,unsigned>();
     case Scanf_h    : return scan_uns<unsigned short,unsigned>();
     case Scanf_l    : return scan_uns<unsigned long,unsigned long>();
     case Scanf_ll   : return scan_uns<unsigned long long,unsigned long long>();
     case Scanf_j    : return scan_uns<Format_uj_t,Format_uj_t>();
     case Scanf_z    : return scan_uns<Format_uz_t,Format_uz_t>();
     case Scanf_t    : return scan_uns<Format_ut_t,Format_ut_t>();
     
     default: return false;
    }
 }

template <class In,class Arg> 
template <class UInt1,class UInt>
bool ScanfContext<In,Arg>::scan_hex()
 {
  bool neg=scan_neg();
  
  UInt value;

  {
   Peek p=peek_width();
     
   if( !p ) return false;
      
   int dig=HexValue(p.ch);
      
   if( dig<0 ) return false;
      
   value=dig;
      
   next_width();
  }
  
  if( value==0 )
    {
     Peek p=peek_width();

     if( +p && ( p.ch=='x' || p.ch=='X' ) )
       {
        next_width();
        
        p=peek_width();
        
        if( !p ) return false;
           
        int dig=HexValue(p.ch);
           
        if( dig<0 ) return false;
           
        value=dig;
           
        next_width();
       }
    }
     
  for(;;)
    {
     Peek p=peek_width();
       
     if( !p ) break;
        
     int dig=HexValue(p.ch);
        
     if( dig<0 ) break;
        
     value=16*value+dig;
        
     next_width();
    }
  
  item_count+=set_unsigned<UInt1>(neg,value);
     
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_hex(ScanfPrefix prefix)
 {
  scan_space();
  
  if( !width ) width=Size(-1);

  switch( prefix )
    {
     case Scanf_none : return scan_hex<unsigned,unsigned>();
     case Scanf_hh   : return scan_hex<unsigned char,unsigned>();
     case Scanf_h    : return scan_hex<unsigned short,unsigned>();
     case Scanf_l    : return scan_hex<unsigned long,unsigned long>();
     case Scanf_ll   : return scan_hex<unsigned long long,unsigned long long>();
     case Scanf_j    : return scan_hex<Format_uj_t,Format_uj_t>();
     case Scanf_z    : return scan_hex<Format_uz_t,Format_uz_t>();
     case Scanf_t    : return scan_hex<Format_ut_t,Format_ut_t>();
     
     default: return false;
    }
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_ch(ScanfPrefix prefix)
 {
  if( prefix!=Scanf_none ) return false;
   
  if( !width ) width=1;
  
  if( suppress )
    {
     for(auto n=width; n ;n--)
       {
        Peek p=peek();
     
        if( !p ) return false;
     
        next();
       }
    }
  else
    {
     char *dst=arg.template get<char>();
  
     for(Size n=width; n ;n--)
       {
        Peek p=peek();
     
        if( !p ) return false;
     
        next();
     
        *(dst++)=p.ch;
       }
     
     item_count++;
    }
  
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_str(ScanfPrefix prefix)
 {
  if( prefix!=Scanf_none ) return false;
  
  scan_space();
  
  if( !width ) width=Size(-1);
  
  if( suppress )
    {
     for(;;)
       {
        Peek p=peek_width();
     
        if( !p || IsSpace(p.ch) ) break;
     
        next_width();
       }
    }
  else
    {
     char *dst=arg.template get<char>();
     
     for(;;)
       {
        Peek p=peek_width();
        
        if( !p || IsSpace(p.ch) ) break;
     
        next_width();
        
        *(dst++)=p.ch;
       }
     
     *dst=0;
     
     item_count++;
    }
  
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_count(ScanfPrefix prefix)
 {
  if( suppress || width ) return false;
  
  switch( prefix )
    {
     case Scanf_hh   : set_signed<signed char>(false,in_count); break; 
     case Scanf_h    : set_signed<short>(false,in_count); break;
     case Scanf_none : set_signed<int>(false,in_count); break;
     case Scanf_l    : set_signed<long>(false,in_count); break;
     case Scanf_ll   : set_signed<long long>(false,in_count); break;
     
     case Scanf_j    : set_signed<Format_sj_t>(false,in_count); break;
     case Scanf_z    : set_signed<Format_sz_t>(false,in_count); break;
     case Scanf_t    : set_signed<Format_st_t>(false,in_count); break;
     
     default: return false;
    }
  
  return true;
 }

template <class In,class Arg> 
bool ScanfContext<In,Arg>::scan_spec(ScanfPrefix prefix,char spec)
 {
  switch( spec )
    {
     case '%' :            return scan_percent(prefix);
      
     case 'd' :            return scan_dec(prefix);
     case 'i' :            return scan_mix(prefix);
     case 'o' :            return scan_oct(prefix);
     case 'u' :            return scan_uns(prefix);
     case 'x' : case 'X' : return scan_hex(prefix);
      
     case 'c' :            return scan_ch(prefix);
     case 's' :            return scan_str(prefix);
     case 'n' :            return scan_count(prefix);
      
     case '[' : // TODO
     case 'p' : // TODO
      
     case 'a' : case 'A' : // TODO
     case 'e' : case 'E' : // TODO
     case 'f' : case 'F' : // TODO
     case 'g' : case 'G' : // TODO
      
     default: return false;
    }
 }

template <class In,class Arg> 
int ScanfContext<In,Arg>::scan(const char *str)
 {
  item_count=0;
  in_count=0;
  
  while( char ch=*str )
    {
     str++;
     
     if( ch=='%' )
       {
        if( *str=='*' )
          {
           suppress=true;
           
           str++;
          }
        else
          {
           suppress=false;
          }

        ParseSize parse_width(str);
        
        width=parse_width.value;
        str=parse_width.str;
        
        ParseScanfPrefix parse_prefix(str);
        
        str=parse_prefix.str;
        
        if( !scan_spec(parse_prefix.value,*str) ) break;
        
        str++;
       }
     else if( IsSpace(ch) )
       {
        while( IsSpace(*str) ) str++;
        
        scan_space();
       }
     else
       {
        if( !scan_char(ch) ) break;
       }
    }
  
  in.complete();
  
  if( !in ) return -1;
  
  return item_count;
 }

} // namespace LibC_Internal
 
#endif



