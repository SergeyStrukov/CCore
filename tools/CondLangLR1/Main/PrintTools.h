/* PrintTools.h */
//----------------------------------------------------------------------------------------
//
//  Project: CondLangLR1 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CondLangLR1_PrintTools_h
#define CondLangLR1_PrintTools_h

#include "Tools.h"

namespace App {

/* classes */

struct OutPos;

template <class Out> class PosPrint;

struct Indent;

struct AutoIndent;

struct EndItem;

struct EndList;

/* struct OutPos */

struct OutPos
 {
  ulen line = 0 ;
  ulen col = 0 ;

  OutPos() {}
  
  void update(char ch,ulen len=1)
   {
    if( ch=='\n' )
      {
       if( len )
         {
          col=0;
          line+=len;
         }
      }
    else
      {
       col+=len;
      }
   }
  
  void update(const char *str,ulen len)
   {
    for(char ch : Range(str,len) ) update(ch);
   }
 };

/* class PosPrint<Out> */

template <class Out> 
class PosPrint : NoCopy
 {
   Out out;
   OutPos pos;
   
  public:
   
   // constructors
   
   template <class ... SS>
   explicit PosPrint(SS && ... ss) : out( std::forward<SS>(ss)... ) {}
   
   ~PosPrint() {}

   // print device methods
   
   using PrintOutType = PosPrint<Out> & ;
   
   PrintOutType printRef() { return *this; }

   void put(char ch)
    {
     pos.update(ch);
     out.put(ch);
    }
    
   void put(char ch,ulen len)
    {
     pos.update(ch,len);
     out.put(ch,len);
    }
    
   void put(const char *str,ulen len)
    {
     pos.update(str,len);
     out.put(str,len);
    }

   void flush()
    {
     out.flush();
    }
 
   // extra methods
   
   ulen getCol() const { return pos.col; }
 };

/* struct Indent */

struct Indent
 {
  ulen len;
  
  Indent(ulen len_=0) : len(len_) {}
  
  void back(ulen delta=1) 
   {
    len=PosSub(len,delta);
   }
  
  template <class P>
  void print(P &out) const
   {
    out.put('\n');
    out.put(' ',len);
   }
 };

/* struct AutoIndent */

struct AutoIndent
 {
  AutoIndent() {}
  
  template <class P>
  void print(P &out) const
   {
    ulen len=out.getCol();
    
    out.put('\n');
    out.put(' ',len);
   }
 };

/* class ListPrint<Out> */

template <class Out>
class ListPrint : NoCopy
 {
   Out &out;
   Indent indent;
   
   bool end_item = false ;
   
  private:
   
   void putChar(char ch)
    {
     if( ch=='\n' )
       Putobj(out,indent); 
     else
       out.put(ch);
    }
   
   void printEnd()
    {
     if( end_item )
       {
        end_item=false;
        
        out.put(',');
        
        Putobj(out,indent);
       } 
    }
   
  public: 
   
   // constructors
   
   explicit ListPrint(Out &out_) 
    : out(out_) 
    {
     out.put(' ');
     out.put('{');
     
     indent=out.getCol();
     
     Putobj(out,indent);
    }
   
   // print device methods
   
   using PrintOutType = ListPrint<Out> & ;
   
   PrintOutType printRef() { return *this; }

   void put(char ch)
    {
     printEnd();
     
     putChar(ch);
    }
    
   void put(char ch,ulen len)
    {
     printEnd();
     
     if( ch=='\n' )
       {
        while( len-- ) Putobj(out,indent);
       }
     else
       {
        out.put(ch,len);
       }
    }
    
   void put(const char *str,ulen len)
    {
     printEnd();
     
     for(char ch : Range(str,len) ) putChar(ch);
    }

   void flush()
    {
     out.flush();
    }
   
   // extra methods
   
   ulen getCol() const { return out.getCol()-indent.len; }
   
   void endItem() 
    { 
     printEnd();
     
     end_item=true; 
    }
   
   void endList()
    {
     indent.back();
     
     Putobj(out,indent);
     
     out.put('}');
    }
 };

/* struct EndItem */

struct EndItem
 {
  EndItem() {}
  
  template <class P>
  void print(P &out) const
   {
    out.endItem();
   }
 };

/* struct EndList */

struct EndList
 {
  EndList() {}
  
  template <class P>
  void print(P &out) const
   {
    out.endList();
   }
 };

} // namespace App

#endif

