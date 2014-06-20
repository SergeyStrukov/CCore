/* UIntSplit.h */ 
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

#ifndef CCore_inc_UIntSplit_h
#define CCore_inc_UIntSplit_h

#include <CCore/inc/Gadget.h>
 
namespace CCore {

/* classes */ 

template <class UIntBig,class UIntSmall> class UIntSplit;

/* class UIntSplit<UIntBig,UIntSmall> */ 

template <class UIntBig,class UIntSmall>
class UIntSplit
 {
   static const unsigned BitLen    = Meta::UIntBits<UIntSmall>::Ret ;
   static const unsigned BigBitLen = Meta::UIntBits<UIntBig>::Ret ;
   
  public:
   
   static const unsigned Len       = BigBitLen/BitLen ;
   
  private: 
  
   static_assert( BigBitLen%BitLen==0 ,"CCore::UIntSplit<UIntBig,UIntSmall> : bad bit lengths");
   static_assert( Len>=2 ,"CCore::UIntSplit<UIntBig,UIntSmall> : bad bit lengths"); 
  
  private:
 
   UIntSmall buf[Len]; // big-endian order
  
  public:
   
   // access
  
   UIntSmall operator [] (unsigned index) const { return buf[index]; }
 
   UIntSmall & operator [] (unsigned index) { return buf[index]; }
   
   PtrLen<UIntSmall> take() { return Range(buf); }
   
   // get
  
   template <unsigned Ind,unsigned Off> struct Get_loop;
   
   template <unsigned Ind,unsigned Off> struct Get_last;
  
   template <unsigned Ind,unsigned Off>
   using Get = Meta::Select<( Ind>0 ), Get_loop<Ind,Off> , Get_last<Ind,Off> > ;
  
   UIntBig get() const
    {
     UIntBig ret=buf[Len-1];
    
     Get<Len-2,BitLen>::Do(ret,buf);
    
     return ret;
    }
   
   // set
   
   template <unsigned Ind,unsigned Off> struct Set_loop;
   
   template <unsigned Ind,unsigned Off> struct Set_last;
  
   template <unsigned Ind,unsigned Off>
   using Set = Meta::Select<( Ind>0 ), Set_loop<Ind,Off> , Set_last<Ind,Off> > ;
  
   void set(UIntBig value)
    {
     buf[Len-1]=UIntSmall( value );
    
     Set<Len-2,BitLen>::Do(value,buf);
    }
 };
 
template <class UIntBig,class UIntSmall>
template <unsigned Ind,unsigned Off> 
struct UIntSplit<UIntBig,UIntSmall>::Get_loop
 {
  static void Do(UIntBig &ret,const UIntSmall buf[])
   {
    ret|=( UIntBig(buf[Ind])<<Off );
    
    Get<Ind-1,Off+BitLen>::Do(ret,buf);
   }
 };
 
template <class UIntBig,class UIntSmall>
template <unsigned Ind,unsigned Off> 
struct UIntSplit<UIntBig,UIntSmall>::Get_last
 {
  static void Do(UIntBig &ret,const UIntSmall buf[])
   {
    ret|=( UIntBig(buf[Ind])<<Off );
   }
 };
 
template <class UIntBig,class UIntSmall>
template <unsigned Ind,unsigned Off> 
struct UIntSplit<UIntBig,UIntSmall>::Set_loop
 {
  static void Do(UIntBig value,UIntSmall buf[])
   {
    buf[Ind]=UIntSmall( value>>Off );
    
    Set<Ind-1,Off+BitLen>::Do(value,buf);
   }
 };
 
template <class UIntBig,class UIntSmall>
template <unsigned Ind,unsigned Off> 
struct UIntSplit<UIntBig,UIntSmall>::Set_last
 {
  static void Do(UIntBig value,UIntSmall buf[])
   {
    buf[Ind]=UIntSmall( value>>Off ); 
   }
 };
 
} // namespace CCore
 
#endif
 

