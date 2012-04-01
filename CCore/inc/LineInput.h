/* LineInput.h */ 
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

#ifndef CCore_inc_LineInput_h
#define CCore_inc_LineInput_h

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/CharProp.h>
 
namespace CCore {

/* classes */ 

template <class ReadCon,ulen MaxLen=80> class LineInput;

/* class LineInput<ReadCon,ulen MaxLen> */ 

template <class ReadCon,ulen MaxLen>
class LineInput : NoCopy
 {
   ReadCon con;
   
   char buf[MaxLen];
   ulen ind;
   
  private: 
   
   bool process(char ch,PtrLen<const char> &ret);
 
  public:
  
   template <class ... SS>
   explicit LineInput(SS && ... ss) : con( std::forward<SS>(ss)... ),ind(0) {}
   
   ~LineInput() {}
   
   PtrLen<const char> get();
   
   bool get(TimeScope time_scope,PtrLen<const char> &ret);
 };
 
template <class ReadCon,ulen MaxLen>
bool LineInput<ReadCon,MaxLen>::process(char ch,PtrLen<const char> &ret) 
 {
  switch( ch )
    {
     case '\r' : 
     case '\n' :
      {
       con.put("\r\n",2);
       
       ret=Range_const(buf,Replace_null(ind));
      }
     return true;
           
     case '\b' :
      {
       if( ind>0 )
         {
          ind--;
             
          con.put("\b \b",3);
         }
      }
     break;
           
     default:
      {
       if( ind<MaxLen && CharIsPrintable(ch) )
         {
          buf[ind++]=ch;
             
          con.put(ch);
         }
      }
    }
    
  return false;  
 }
 
template <class ReadCon,ulen MaxLen>
PtrLen<const char> LineInput<ReadCon,MaxLen>::get()
 {
  PtrLen<const char> ret;
  
  while( !process(con.get(),ret) );
  
  return ret;
 }
    
template <class ReadCon,ulen MaxLen>
bool LineInput<ReadCon,MaxLen>::get(TimeScope time_scope,PtrLen<const char> &ret)
 {
  for(;;)
    {
     char ch;
     
     if( !con.get(time_scope,ch) ) return false;
     
     if( process(ch,ret) ) return true;
    }
 }
    
} // namespace CCore
 
#endif
 

