/* TextTools.h */ 
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
//  Copyright (c) 2011 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TextTools_h
#define CCore_inc_TextTools_h

#include <CCore/inc/CharProp.h>
 
namespace CCore {

/* functions */

inline bool CharIsEOL(char ch) { return ch=='\r' || ch=='\n' ; }

inline bool CharIsBin(char ch) { return ch=='0' || ch=='1' ; }
 
inline bool CharIsDec(char ch) { return ch>='0' && ch<='9' ; }

inline bool CharIsHex(char ch) { return CharHexValue(ch)>=0; }

inline int CharBinValue(char ch) { if( ch>='0' && ch<='1' ) return ch-'0'; return -1; }

/* classes */

struct TextPos;

template <class CharClass,CharClass DefaultClass> class CharPropTable;

/* struct TextPos */ 

struct TextPos
 {
  ulen line;
  ulen col;

  TextPos() : line(1),col(1) {}
  
  void nextPos() { col++; }
 
  void nextLine() { col=1; line++; }
  
  void update(ulen len) { col+=len; }
  
  void update(StrLen text); // must not break "\r\n"
 
  template <class P>
  void print(P &out) const
   {
    Printf(out,"(line=#;,col=#;)",line,col);
   }
 };

/* class CharPropTable<CharClass,CharClass DefaultClass> */

template <class CharClass,CharClass DefaultClass> 
class CharPropTable : NoCopy
 {
   CharClass table[256];
   
  private: 

   static uint8 Index(char ch) { return uint8(ch); }
   
  protected:
  
   void set(char ch,CharClass cc)
    {
     table[Index(ch)]=cc;
    }

   void setSet(const char *zstr,CharClass cc)
    {
     for(; char ch=*zstr ;zstr++) set(ch,cc);
    }
   
   template <class Func>
   void setIf(Func cond,CharClass cc)
    {
     for(int i=-128; i<128 ;i++) 
       {
        char ch=char(i);
        
        if( cond(ch) ) set(ch,cc);
       }
    }

  public:

   CharPropTable() { Range(table).set(DefaultClass); }

   CharClass operator [] (char ch) const { return table[Index(ch)]; }
 };

} // namespace CCore
 
#endif
 

