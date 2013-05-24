/* CharProp.h */ 
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

#ifndef CCore_inc_CharProp_h
#define CCore_inc_CharProp_h

#include <CCore/inc/Printf.h>
 
namespace CCore {

/* classes */ 

class ASCIICode;

class PrintCString;

/* class ASCIICode */ 

class ASCIICode
 {
  public:
  
   typedef uint8 CodeType;
   
   template <class Char> struct Map;
   
   static char InverseMap(CodeType code) { return char(code-256); }
   
   //
   // Char ch -> code
   //
   // (int)ch == (int)code (mod 256) 
   //
   
  private:
 
   CodeType code; 
   
    //
    // ASCII code table
    // 
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |     I  00 |  01 |  02 |  03 |  04 |  05 |  06 |  07 |  08 |  09 |  0A |  0B |  0C |  0D |  0E |  0F |
    // +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    // |  00 I     |     |     |     |     |     |     |     | \b  | \t  | \n  | \v  | \f  | \r  |     |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  10 I     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  20 I     |  !  |  "  |  #  |  $  |  %  |  &  |  '  |  (  |  )  |  *  |  +  |  ,  |  -  |  .  |  /  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  30 I  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  :  |  ;  |  <  |  =  |  >  |  ?  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  40 I  @  |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |  K  |  L  |  M  |  N  |  O  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  50 I  P  |  Q  |  R  |  S  |  T  |  U  |  V  |  W  |  X  |  Y  |  Z  |  [  |  \  |  ]  |  ^  |  _  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  60 I  `  |  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  |  i  |  j  |  k  |  l  |  m  |  n  |  o  |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // |  70 I  p  |  q  |  r  |  s  |  t  |  u  |  v  |  w  |  x  |  y  |  z  |  {  |  |  |  }  |  ~  |     |
    // +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    // 
    
   static const bool IsSpaceTable[256];
   
   static const bool IsPunctTable[256];
   
   static const bool IsSpaceOrPunctTable[256];
    
   static const signed char DecValueTable[256];

   static const signed char HexValueTable[256];
    
  public:
  
   // constructors
  
   ASCIICode() : code(0) {}
   
   template <class Char>
   explicit ASCIICode(Char ch) : code( Map<Char>(ch) ) {}
   
   // properties
   
   bool isSpecial() const { return code<32 || code==127 ; }
   
        // special -- represents no character
 
   bool isVisible() const { return code>32 && code!=127 ; }
   
        // visible -- represents non-space character
   
   bool isPrintable() const { return code>=32 && code!=127 ; }
   
        // printable -- not a special char
 
   bool isSpace() const { return IsSpaceTable[code]; }
   
        // space-like -- " \t\n\v\f\r"
   
   bool isPunct() const { return IsPunctTable[code]; }
   
        // punctuation characters
   
   bool isSpaceOrPunct() const { return IsSpaceOrPunctTable[code]; }
   
        // space or punct
  
   int decValue() const { return DecValueTable[code]; }
   
       // decimal digit value or -1
   
   int hexValue() const { return HexValueTable[code]; }
   
       // hexadecimal digit value or -1

   char getChar() const { return InverseMap(code); }
   
   // print object
   
   template <class P>
   void print(P &out) const
    {
     if( code>=32 && code!=127 )
       {
        switch( char ch=getChar() )
          {
           case '\\' : case '"' : out.put('\\'); // falldown;
            
           default: out.put(ch);
          }
       }
     else if( code>=8 && code<=13 )
       {
        out.put('\\');
        out.put("btnvfr"[code-8]);
       }
     else
       {
        Printf(out,"\\x#2.16i;",code);
       }
    }
 };
 
template <> 
struct ASCIICode::Map<char>
 {
  CodeType code;
  
  Map(char ch) : code(ch) {}
  
  operator CodeType() const { return code; }
 };                           
 
template <> 
struct ASCIICode::Map<signed char>
 {
  CodeType code;
  
  Map(signed char ch) : code(ch) {}
  
  operator CodeType() const { return code; }
 };                           
 
template <> 
struct ASCIICode::Map<unsigned char>
 {
  CodeType code;
  
  Map(unsigned char ch) : code(ch) {}
  
  operator CodeType() const { return code; }
 };          

/* type CharCode */

typedef ASCIICode CharCode;
 
/* class PrintCString */ 

class PrintCString
 {
   StrLen str;

  public:

   explicit PrintCString(StrLen str_) : str(str_) {}
 
   typedef StrPrintOpt PrintOptType;
   
   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     if( opt.quoted ) out.put('"');
     
     for(auto r=str; +r ;++r) Putobj(out,CharCode(*r));
     
     if( opt.quoted ) out.put('"');
    }
 };

/* functions */ 

template <class Char>
bool CharIsSpecial(Char ch) { return CharCode(ch).isSpecial(); }
 
template <class Char>
bool CharIsVisible(Char ch) { return CharCode(ch).isVisible(); }
 
template <class Char>
bool CharIsPrintable(Char ch) { return CharCode(ch).isPrintable(); } 
 
template <class Char>
bool CharIsSpace(Char ch) { return CharCode(ch).isSpace(); }
  
template <class Char>
bool CharIsPunct(Char ch) { return CharCode(ch).isPunct(); }

template <class Char>
bool CharIsSpaceOrPunct(Char ch) { return CharCode(ch).isSpaceOrPunct(); }

template <class Char>
int CharDecValue(Char ch) { return CharCode(ch).decValue(); }
 
template <class Char>
int CharHexValue(Char ch) { return CharCode(ch).hexValue(); }

/* char sets */

inline const char * GetSpaceChars() { return " \t\f\v\r\n"; }

inline const char * GetPunctChars() { return "!\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~"; }

inline const char * GetDigitChars() { return "0123456789"; }

inline const char * GetHexDigitChars() { return "0123456789abcdefABCDEF"; }

inline const char * GetCLetterChars() { return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; }
 
} // namespace CCore
 
#endif
 

