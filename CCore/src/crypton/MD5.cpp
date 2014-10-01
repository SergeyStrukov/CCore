/* MD5.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: General
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------
 
#include <CCore/inc/crypton/MD5.h>
#include <CCore/inc/crypton/Rot.h>
#include <CCore/inc/SaveLoad.h>
 
namespace CCore {
namespace Crypton {

/* struct MD5Core::State */

uint32 MD5Core::State::Func1(uint32 x,uint32 y,uint32 z) { return (x&y)|(~x&z); }

uint32 MD5Core::State::Func2(uint32 x,uint32 y,uint32 z) { return (x&z)|(y&~z); }

uint32 MD5Core::State::Func3(uint32 x,uint32 y,uint32 z) { return x^y^z; }

uint32 MD5Core::State::Func4(uint32 x,uint32 y,uint32 z) { return y^(x|~z); }

void MD5Core::State::Round1(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift) 
 {
  a = b + Rol32(a+Func1(b,c,d)+xt,shift) ;
 }

void MD5Core::State::Round2(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift) 
 {
  a = b + Rol32(a+Func2(b,c,d)+xt,shift) ;
 }

void MD5Core::State::Round3(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift) 
 {
  a = b + Rol32(a+Func3(b,c,d)+xt,shift) ;
 }

void MD5Core::State::Round4(uint32 &a,uint32 b,uint32 c,uint32 d,uint32 xt,unsigned shift) 
 {
  a = b + Rol32(a+Func4(b,c,d)+xt,shift) ;
 }

void MD5Core::State::Round1(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen])
 {
  const uint32 T0  = 0xd76aa478 ;
  const uint32 T1  = 0xe8c7b756 ;
  const uint32 T2  = 0x242070db ;
  const uint32 T3  = 0xc1bdceee ;

  const uint32 T4  = 0xf57c0faf ;
  const uint32 T5  = 0x4787c62a ;
  const uint32 T6  = 0xa8304613 ;
  const uint32 T7  = 0xfd469501 ;

  const uint32 T8  = 0x698098d8 ;
  const uint32 T9  = 0x8b44f7af ;
  const uint32 T10 = 0xffff5bb1 ;
  const uint32 T11 = 0x895cd7be ;

  const uint32 T12 = 0x6b901122 ;
  const uint32 T13 = 0xfd987193 ;
  const uint32 T14 = 0xa679438e ;
  const uint32 T15 = 0x49b40821 ;
  
  Round1(a,b,c,d,X[0]+T0,7);
  Round1(d,a,b,c,X[1]+T1,12);
  Round1(c,d,a,b,X[2]+T2,17);
  Round1(b,c,d,a,X[3]+T3,22);
  
  Round1(a,b,c,d,X[4]+T4,7);
  Round1(d,a,b,c,X[5]+T5,12);
  Round1(c,d,a,b,X[6]+T6,17);
  Round1(b,c,d,a,X[7]+T7,22);
  
  Round1(a,b,c,d,X[8]+T8,7);
  Round1(d,a,b,c,X[9]+T9,12);
  Round1(c,d,a,b,X[10]+T10,17);
  Round1(b,c,d,a,X[11]+T11,22);
  
  Round1(a,b,c,d,X[12]+T12,7);
  Round1(d,a,b,c,X[13]+T13,12);
  Round1(c,d,a,b,X[14]+T14,17);
  Round1(b,c,d,a,X[15]+T15,22);
 }

void MD5Core::State::Round2(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen])
 {
  const uint32 T0  = 0xf61e2562 ;
  const uint32 T1  = 0xc040b340 ;
  const uint32 T2  = 0x265e5a51 ;
  const uint32 T3  = 0xe9b6c7aa ;

  const uint32 T4  = 0xd62f105d ;
  const uint32 T5  = 0x02441453 ;
  const uint32 T6  = 0xd8a1e681 ;
  const uint32 T7  = 0xe7d3fbc8 ;

  const uint32 T8  = 0x21e1cde6 ;
  const uint32 T9  = 0xc33707d6 ;
  const uint32 T10 = 0xf4d50d87 ;
  const uint32 T11 = 0x455a14ed ;

  const uint32 T12 = 0xa9e3e905 ;
  const uint32 T13 = 0xfcefa3f8 ;
  const uint32 T14 = 0x676f02d9 ;
  const uint32 T15 = 0x8d2a4c8a ;
  
  Round2(a,b,c,d,X[1]+T0,5);
  Round2(d,a,b,c,X[6]+T1,9);
  Round2(c,d,a,b,X[11]+T2,14);
  Round2(b,c,d,a,X[0]+T3,20);
  
  Round2(a,b,c,d,X[5]+T4,5);
  Round2(d,a,b,c,X[10]+T5,9);
  Round2(c,d,a,b,X[15]+T6,14);
  Round2(b,c,d,a,X[4]+T7,20);
  
  Round2(a,b,c,d,X[9]+T8,5);
  Round2(d,a,b,c,X[14]+T9,9);
  Round2(c,d,a,b,X[3]+T10,14);
  Round2(b,c,d,a,X[8]+T11,20);
  
  Round2(a,b,c,d,X[13]+T12,5);
  Round2(d,a,b,c,X[2]+T13,9);
  Round2(c,d,a,b,X[7]+T14,14);
  Round2(b,c,d,a,X[12]+T15,20);
 }

void MD5Core::State::Round3(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen])
 {
  const uint32 T0  = 0xfffa3942 ;
  const uint32 T1  = 0x8771f681 ;
  const uint32 T2  = 0x6d9d6122 ;
  const uint32 T3  = 0xfde5380c ;

  const uint32 T4  = 0xa4beea44 ;
  const uint32 T5  = 0x4bdecfa9 ;
  const uint32 T6  = 0xf6bb4b60 ;
  const uint32 T7  = 0xbebfbc70 ;

  const uint32 T8  = 0x289b7ec6 ;
  const uint32 T9  = 0xeaa127fa ;
  const uint32 T10 = 0xd4ef3085 ;
  const uint32 T11 = 0x04881d05 ;

  const uint32 T12 = 0xd9d4d039 ;
  const uint32 T13 = 0xe6db99e5 ;
  const uint32 T14 = 0x1fa27cf8 ;
  const uint32 T15 = 0xc4ac5665 ;
  
  Round3(a,b,c,d,X[5]+T0,4);
  Round3(d,a,b,c,X[8]+T1,11);
  Round3(c,d,a,b,X[11]+T2,16);
  Round3(b,c,d,a,X[14]+T3,23);
  
  Round3(a,b,c,d,X[1]+T4,4);
  Round3(d,a,b,c,X[4]+T5,11);
  Round3(c,d,a,b,X[7]+T6,16);
  Round3(b,c,d,a,X[10]+T7,23);
  
  Round3(a,b,c,d,X[13]+T8,4);
  Round3(d,a,b,c,X[0]+T9,11);
  Round3(c,d,a,b,X[3]+T10,16);
  Round3(b,c,d,a,X[6]+T11,23);
  
  Round3(a,b,c,d,X[9]+T12,4);
  Round3(d,a,b,c,X[12]+T13,11);
  Round3(c,d,a,b,X[15]+T14,16);
  Round3(b,c,d,a,X[2]+T15,23);
 }

void MD5Core::State::Round4(uint32 &a,uint32 &b,uint32 &c,uint32 &d,const uint32 X[BlockWordLen])
 {
  const uint32 T0  = 0xf4292244 ;
  const uint32 T1  = 0x432aff97 ;
  const uint32 T2  = 0xab9423a7 ;
  const uint32 T3  = 0xfc93a039 ;

  const uint32 T4  = 0x655b59c3 ;
  const uint32 T5  = 0x8f0ccc92 ;
  const uint32 T6  = 0xffeff47d ;
  const uint32 T7  = 0x85845dd1 ;

  const uint32 T8  = 0x6fa87e4f ;
  const uint32 T9  = 0xfe2ce6e0 ;
  const uint32 T10 = 0xa3014314 ;
  const uint32 T11 = 0x4e0811a1 ;

  const uint32 T12 = 0xf7537e82 ;
  const uint32 T13 = 0xbd3af235 ;
  const uint32 T14 = 0x2ad7d2bb ;
  const uint32 T15 = 0xeb86d391 ;
  
  Round4(a,b,c,d,X[0]+T0,6);
  Round4(d,a,b,c,X[7]+T1,10);
  Round4(c,d,a,b,X[14]+T2,15);
  Round4(b,c,d,a,X[5]+T3,21);
  
  Round4(a,b,c,d,X[12]+T4,6);
  Round4(d,a,b,c,X[3]+T5,10);
  Round4(c,d,a,b,X[10]+T6,15);
  Round4(b,c,d,a,X[1]+T7,21);
  
  Round4(a,b,c,d,X[8]+T8,6);
  Round4(d,a,b,c,X[15]+T9,10);
  Round4(c,d,a,b,X[6]+T10,15);
  Round4(b,c,d,a,X[13]+T11,21);
  
  Round4(a,b,c,d,X[4]+T12,6);
  Round4(d,a,b,c,X[11]+T13,10);
  Round4(c,d,a,b,X[2]+T14,15);
  Round4(b,c,d,a,X[9]+T15,21);
 }

void MD5Core::State::reset()
 {
  A=0x67452301;
  B=0xEFCDAB89;
  C=0x98BADCFE;
  D=0x10325476;
 }

void MD5Core::State::step(const uint32 X[BlockWordLen])
 {
  uint32 a=A;
  uint32 b=B;
  uint32 c=C;
  uint32 d=D;
  
  Round1(a,b,c,d,X);
  Round2(a,b,c,d,X);
  Round3(a,b,c,d,X);
  Round4(a,b,c,d,X);
  
  A+=a;
  B+=b;
  C+=c;
  D+=d;
 }

void MD5Core::State::step(const uint8 buf[BlockLen])
 {
  uint32 X[BlockWordLen];
  
  BufGetDev dev(buf);
  
  LoadRange_use<LeOrder>(X,BlockWordLen,dev);
  
  step(X);
 }

void MD5Core::State::finish(uint8 digest[DigestLen])
 {
  BufPutDev dev(digest);
  
  dev.use<LeOrder>(A,B,C,D);
 }

/* struct MD5Core::Buf */

void MD5Core::Buf::reset()
 {
  len=0;
  bitlen=0;
 }

template <class Func>
void MD5Core::Buf::add(PtrLen<const uint8> data,Func func)
 {
  bitlen += (uint64(data.len)<<3) ;
  
  if( len )
    {
     unsigned rest=BlockLen-len;
     
     if( data.len<rest )
       {
        data.copyTo(buf+len);
        
        len+=(unsigned)data.len;
        
        return;
       }
     
     (data+=rest).copyTo(buf+len);
     
     func(buf);
     
     len=0;
    }
  
  while( data.len>=BlockLen )
    {
     func(data.ptr);
     
     data+=BlockLen;
    }
  
  data.copyTo(buf);
  
  len=(unsigned)data.len;
 }

template <class Func>
void MD5Core::Buf::finish(Func func)
 {
  if( len<BlockLen-TailLen )
    {
     buf[len]=0x80;
     
     Range(buf+len+1,BlockLen-TailLen-len-1).set_null();
    }
  else
    {
     buf[len]=0x80;
     
     Range(buf+len+1,BlockLen-len-1).set_null();
     
     func(buf);
     
     Range(buf,BlockLen-TailLen).set_null();    
    }
  
  BufPutDev dev(buf+(BlockLen-TailLen));
  
  dev.use<LeOrder>(bitlen);
  
  func(buf);
 }

/* class MD5Core */

void MD5Core::reset()
 {
  state.reset();
  buf.reset();
 }

void MD5Core::add(const uint8 *data,ulen len)
 {
  buf.add(Range(data,len), [this] (const uint8 buf[BlockLen]) { state.step(buf); } );
 }

void MD5Core::finish(uint8 digest[DigestLen])
 {
  buf.finish( [this] (const uint8 buf[BlockLen]) { state.step(buf); } );
  
  state.finish(digest);
  
  reset();
 }

} // namespace Crypton
} // namespace CCore
 

