/* AES.h */ 
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

#ifndef CCore_inc_crypton_AES_h
#define CCore_inc_crypton_AES_h

#include <CCore/inc/crypton/BlockCipher.h>

namespace CCore {
namespace Crypton {

/* classes */ 

struct AESBase;

struct AES128Param;

struct AES192Param;

struct AES256Param;

template <class Param> struct AES;

template <class Param> struct AESInverse;

/* struct AESBase */ 

struct AESBase
 {
  // consts
  
  static const ulen BlockWordLen = 4 ;
  static const ulen BlockLen = 4*BlockWordLen ;
  
  static const uint8 PolynomMask = 0x1b ; // x^8 + ( x^4 + x^3 + x + 1 )
  
  static const uint8 SBox[256];
  
  static const uint8 SBoxInverse[256];
  
  static const uint8 Mul02Table[256];
  
  static const uint8 Mul03Table[256];
  
  static const uint8 Mul0eTable[256];
  
  static const uint8 Mul0bTable[256];
  
  static const uint8 Mul0dTable[256];
  
  static const uint8 Mul09Table[256];
  
  // GF(2^8)
  
  static uint8 MulX(uint8 a)
   {
    if( a&0x80 )
      return uint8( (a<<1)^PolynomMask );
    else
      return uint8( a<<1 );
   }
  
  static uint8 MulX2(uint8 a) { return MulX(MulX(a)); }
  
  static uint8 MulX3(uint8 a) { return MulX(MulX(MulX(a))); }
  
#if 0 
  
  static uint8 Mul02(uint8 a) { return MulX(a); } // x*
  
  static uint8 Mul03(uint8 a) { return uint8( MulX(a)^a ); } // (x+1)*
  
  static uint8 Mul0e(uint8 a) { return uint8( MulX3(a)^MulX2(a)^MulX(a) ); } // (x^3+x^2+x)*
  
  static uint8 Mul0b(uint8 a) { return uint8( MulX3(a)^MulX(a)^a ); } // (x^3+x+1)*
  
  static uint8 Mul0d(uint8 a) { return uint8( MulX3(a)^MulX2(a)^a ); } // (x^3+x^2+1)* 
  
  static uint8 Mul09(uint8 a) { return uint8( MulX3(a)^a ); } // (x^3+1)*
  
#else
  
  static uint8 Mul02(uint8 a) { return Mul02Table[a]; }
  
  static uint8 Mul03(uint8 a) { return Mul03Table[a]; }
  
  static uint8 Mul0e(uint8 a) { return Mul0eTable[a]; }
  
  static uint8 Mul0b(uint8 a) { return Mul0bTable[a]; }
  
  static uint8 Mul0d(uint8 a) { return Mul0dTable[a]; } 
  
  static uint8 Mul09(uint8 a) { return Mul09Table[a]; }
  
#endif
  
  static uint8 Mul(uint8 a,uint8 b);
 
  static uint8 Inverse(uint8 a);
 
  static uint8 Transform(uint8 a);
 
  // key expansion
  
  static void XorWord(const uint8 a[4],const uint8 b[4],uint8 *restrict c/* [4] */) 
   {
    c[0] = uint8( a[0]^b[0] ) ; 
    c[1] = uint8( a[1]^b[1] ) ; 
    c[2] = uint8( a[2]^b[2] ) ; 
    c[3] = uint8( a[3]^b[3] ) ; 
   }
   
  static void SubstWord(const uint8 a[4],uint8 *restrict b/* [4] */)
   {
    b[0] = SBox[a[0]] ;
    b[1] = SBox[a[1]] ;
    b[2] = SBox[a[2]] ;
    b[3] = SBox[a[3]] ;
   }
 
  static void RotWord(const uint8 a[4],uint8 *restrict b/* [4] */)
   {
    b[0] = a[1] ;
    b[1] = a[2] ;
    b[2] = a[3] ;
    b[3] = a[0] ;
   }
   
  static void FirstRcon(uint8 a[4]) 
   {
    a[0] = 1 ;
    a[1] = 0 ;
    a[2] = 0 ;
    a[3] = 0 ;
   }
   
  static void NextRcon(uint8 a[4]) 
   {
    a[0] = MulX(a[0]) ;
   }
 
  template <ulen KeyWordLen,ulen RoundKeyWordLen>
  static void KeyExpansion(uint8 round_key[4*RoundKeyWordLen])
   {
    uint8 Rcon[4];
    
    FirstRcon(Rcon);
   
    for(ulen ind=KeyWordLen; ind<RoundKeyWordLen ;ind++)
      {
       uint8 *c=round_key+4*ind;
       const uint8 *a=round_key+4*(ind-KeyWordLen);
       const uint8 *b=round_key+4*(ind-1);
       
       if( ind%KeyWordLen == 0 )
         {
          uint8 temp1[4];
          uint8 temp2[4];
          uint8 temp3[4];
          
          RotWord(b,temp1);
          SubstWord(temp1,temp2);
          XorWord(temp2,Rcon,temp3); NextRcon(Rcon);
          
          XorWord(a,temp3,c);
         }
       else if( KeyWordLen>6 && ind%KeyWordLen == 4 )
         {
          uint8 temp[4];
          
          SubstWord(b,temp);
          XorWord(a,temp,c);
         }
       else
         {
          XorWord(a,b,c);
         }
      }
   }
 
  // cipher
  
  static void AddRoundKey(const uint8 round_key[BlockLen],uint8 *restrict state/* [BlockLen] */)
   {
#if 0    
    
    for(ulen len=BlockLen; len ;len--,state++,round_key++) (*state) ^= (*round_key) ;
    
#else /* BlockLen == 16 */
    
    state[0] ^= round_key[0] ;
    state[1] ^= round_key[1] ;
    state[2] ^= round_key[2] ;
    state[3] ^= round_key[3] ;
    
    state[4] ^= round_key[4] ;
    state[5] ^= round_key[5] ;
    state[6] ^= round_key[6] ;
    state[7] ^= round_key[7] ;

    state[8] ^= round_key[8] ;
    state[9] ^= round_key[9] ;
    state[10] ^= round_key[10] ;
    state[11] ^= round_key[11] ;

    state[12] ^= round_key[12] ;
    state[13] ^= round_key[13] ;
    state[14] ^= round_key[14] ;
    state[15] ^= round_key[15] ;
    
#endif    
   }
   
  static void SubstBytes(uint8 state[BlockLen])
   {
#if 0
    
    for(ulen len=BlockLen; len ;len--,state++) (*state) = SBox[*state] ;
    
#else /* BlockLen == 16 */
    
    state[0]=SBox[state[0]];
    state[1]=SBox[state[1]];
    state[2]=SBox[state[2]];
    state[3]=SBox[state[3]];
    
    state[4]=SBox[state[4]];
    state[5]=SBox[state[5]];
    state[6]=SBox[state[6]];
    state[7]=SBox[state[7]];
    
    state[8]=SBox[state[8]];
    state[9]=SBox[state[9]];
    state[10]=SBox[state[10]];
    state[11]=SBox[state[11]];

    state[12]=SBox[state[12]];
    state[13]=SBox[state[13]];
    state[14]=SBox[state[14]];
    state[15]=SBox[state[15]];
    
#endif
   }
   
  static void ShiftRows(uint8 state[BlockLen])
   {
#if 0   
   
    // shift row 1
    {
     uint8 temp = state[1] ;
     
     for(ulen i=0; i<BlockWordLen-1 ;i++) state[1+4*i] = state[5+4*i] ;
     
     state[1+4*(BlockWordLen-1)] = temp ;
    }
    
    // shift row 2
    {
     uint8 temp1 = state[2] ;
     uint8 temp2 = state[2+4] ;
     
     for(ulen i=0; i<BlockWordLen-2 ;i++) state[2+4*i] = state[10+4*i] ;
     
     state[2+4*(BlockWordLen-2)] = temp1 ;
     state[2+4*(BlockWordLen-1)] = temp2 ;
    }
    
    // shift row 3
    {
     uint8 temp1 = state[3] ;
     uint8 temp2 = state[3+4] ;
     uint8 temp3 = state[3+2*4] ;
     
     for(ulen i=0; i<BlockWordLen-3 ;i++) state[3+4*i] = state[15+4*i] ;
     
     state[3+4*(BlockWordLen-3)] = temp1 ;
     state[3+4*(BlockWordLen-2)] = temp2 ;
     state[3+4*(BlockWordLen-1)] = temp3 ;
    }
    
#else /* BlockWordLen == 4 */ 

    // shift row 1
    {
     uint8 temp = state[1+0*4] ;
     
     state[1+0*4] = state[1+1*4] ;
     state[1+1*4] = state[1+2*4] ;
     state[1+2*4] = state[1+3*4] ;
     
     state[1+3*4] = temp ;
    }
    
    // shift row 2
    {
     uint8 temp1 = state[2+0*4] ;
     uint8 temp2 = state[2+1*4] ;
     
     state[2+0*4] = state[2+2*4] ;
     state[2+1*4] = state[2+3*4] ;
     
     state[2+2*4] = temp1 ;
     state[2+3*4] = temp2 ;
    }
    
    // shift row 3
    {
     uint8 temp = state[3+3*4] ; 
     
     state[3+3*4] = state[3+2*4] ;
     state[3+2*4] = state[3+1*4] ;
     state[3+1*4] = state[3+0*4] ;
     
     state[3+0*4] = temp ;
    }
 
#endif    
   }
   
  static void MulColumn(uint8 a[4])
   {
    uint8 a0=a[0];
    uint8 a1=a[1];
    uint8 a2=a[2];
    uint8 a3=a[3];
   
    a[0] = uint8( Mul02(a0)^Mul03(a1)^a2^a3 ) ;
    a[1] = uint8( Mul02(a1)^Mul03(a2)^a3^a0 ) ;
    a[2] = uint8( Mul02(a2)^Mul03(a3)^a0^a1 ) ;
    a[3] = uint8( Mul02(a3)^Mul03(a0)^a1^a2 ) ;
   }
 
  static void MixColumns(uint8 state[BlockLen])
   {
#if 0
    
    for(ulen i=0; i<BlockWordLen ;i++) MulColumn(state+4*i);
    
#else /* BlockWordLen == 4 */
    
    MulColumn(state);
    MulColumn(state+4);
    MulColumn(state+8);
    MulColumn(state+12);
    
#endif
   }
   
  template <ulen Rounds> 
  static void Apply(const uint8 *round_key/* [(Rounds+1)*BlockLen] */,uint8 *restrict state/* [BlockLen] */)
   {
#if 0    
    
    AddRoundKey(round_key,state); round_key+=BlockLen;
    
    for(ulen round=Rounds-1; round ;round--)
      {
       SubstBytes(state);
       ShiftRows(state);
       MixColumns(state);
       AddRoundKey(round_key,state); round_key+=BlockLen;
      }
      
    SubstBytes(state);
    ShiftRows(state);
    AddRoundKey(round_key,state);
    
#else
    
    for(ulen round=Rounds-1; round ;round--)
      {
       AddRoundKey(round_key,state); round_key+=BlockLen;
       SubstBytes(state);
       ShiftRows(state);
       MixColumns(state);
      }
      
    AddRoundKey(round_key,state); round_key+=BlockLen;
    SubstBytes(state);
    ShiftRows(state);
    AddRoundKey(round_key,state);
    
#endif    
   }
  
  static void SubstBytesInverse(uint8 state[BlockLen])
   {
#if 0
    
    for(ulen len=BlockLen; len ;len--,state++) (*state) = SBoxInverse[*state] ;
    
#else /* BlockLen == 16 */
    
    state[0]=SBoxInverse[state[0]];
    state[1]=SBoxInverse[state[1]];
    state[2]=SBoxInverse[state[2]];
    state[3]=SBoxInverse[state[3]];
    
    state[4]=SBoxInverse[state[4]];
    state[5]=SBoxInverse[state[5]];
    state[6]=SBoxInverse[state[6]];
    state[7]=SBoxInverse[state[7]];
    
    state[8]=SBoxInverse[state[8]];
    state[9]=SBoxInverse[state[9]];
    state[10]=SBoxInverse[state[10]];
    state[11]=SBoxInverse[state[11]];

    state[12]=SBoxInverse[state[12]];
    state[13]=SBoxInverse[state[13]];
    state[14]=SBoxInverse[state[14]];
    state[15]=SBoxInverse[state[15]];
    
#endif
   }
   
  static void ShiftRowsInverse(uint8 state[BlockLen])
   {
#if 0   
   
    // shift row 1
    {
     uint8 temp = state[1+4*(BlockWordLen-1)] ;
     
     for(ulen i=BlockWordLen-1; i ;i--) state[1+4*i] = state[4*i-3] ;
     
     state[1] = temp ;
    }
    
    // shift row 2
    {
     uint8 temp1 = state[2+4*(BlockWordLen-2)] ;
     uint8 temp2 = state[2+4*(BlockWordLen-1)] ;
     
     for(ulen i=BlockWordLen-2; i ;i--) state[6+4*i] = state[4*i-2] ;
     
     state[2] = temp1 ;
     state[2+4] = temp2 ;
    }
    
    // shift row 3
    {
     uint8 temp1 = state[3+4*(BlockWordLen-3)] ;
     uint8 temp2 = state[3+4*(BlockWordLen-2)] ;
     uint8 temp3 = state[3+4*(BlockWordLen-1)] ;
     
     for(ulen i=BlockWordLen-3; i ;i--) state[11+4*i] = state[4*i-1] ;
     
     state[3] = temp1 ; 
     state[3+4] = temp2 ; 
     state[3+2*4] = temp3 ; 
    }
    
#else /* BlockWordLen == 4 */ 

    // shift row 1
    {
     uint8 temp = state[1+3*4] ; 
     
     state[1+3*4] = state[1+2*4] ;
     state[1+2*4] = state[1+1*4] ;
     state[1+1*4] = state[1+0*4] ;
     
     state[1+0*4] = temp ;
    }
    
    // shift row 2
    {
     uint8 temp1 = state[2+0*4] ;
     uint8 temp2 = state[2+1*4] ;
     
     state[2+0*4] = state[2+2*4] ;
     state[2+1*4] = state[2+3*4] ;
     
     state[2+2*4] = temp1 ;
     state[2+3*4] = temp2 ;
    }
    
    // shift row 3
    {
     uint8 temp = state[3+0*4] ;
     
     state[3+0*4] = state[3+1*4] ;
     state[3+1*4] = state[3+2*4] ;
     state[3+2*4] = state[3+3*4] ;
     
     state[3+3*4] = temp ;
    }
 
#endif    
   }
   
  static void MulColumnInverse(uint8 a[4])
   {
    uint8 a0=a[0];
    uint8 a1=a[1];
    uint8 a2=a[2];
    uint8 a3=a[3];
   
    a[0] = uint8( Mul0e(a0)^Mul0b(a1)^Mul0d(a2)^Mul09(a3) ) ;
    a[1] = uint8( Mul0e(a1)^Mul0b(a2)^Mul0d(a3)^Mul09(a0) ) ;
    a[2] = uint8( Mul0e(a2)^Mul0b(a3)^Mul0d(a0)^Mul09(a1) ) ;
    a[3] = uint8( Mul0e(a3)^Mul0b(a0)^Mul0d(a1)^Mul09(a2) ) ;
   }
 
  static void MixColumnsInverse(uint8 state[BlockLen])
   {
#if 0
    
    for(ulen i=0; i<BlockWordLen ;i++) MulColumnInverse(state+4*i);
    
#else /* BlockWordLen == 4 */
    
    MulColumnInverse(state);
    MulColumnInverse(state+4);
    MulColumnInverse(state+8);
    MulColumnInverse(state+12);
    
#endif
   }
   
  template <ulen Rounds> 
  static void ApplyInverse(const uint8 *round_key/* [(Rounds+1)*BlockLen] */,uint8 *restrict state/* [BlockLen] */)
   {
    round_key+=Rounds*BlockLen;
    
    AddRoundKey(round_key,state);
    ShiftRowsInverse(state);
    SubstBytesInverse(state);
    round_key-=BlockLen; AddRoundKey(round_key,state);
    
    for(ulen round=Rounds-1; round ;round--)
      {
       MixColumnsInverse(state);
       ShiftRowsInverse(state);
       SubstBytesInverse(state);
       round_key-=BlockLen; AddRoundKey(round_key,state); 
      }
   }
 };
 
/* struct AES128Param */ 

struct AES128Param
 {
  static const ulen KeyWordLen = 4 ;
  static const ulen Rounds = 10 ;
  
  static const char *const Name;
  static const char *const InverseName;
 };
 
/* struct AES192Param */ 

struct AES192Param
 {
  static const ulen KeyWordLen = 6 ;
  static const ulen Rounds = 12 ;
  
  static const char *const Name;
  static const char *const InverseName;
 };
 
/* struct AES256Param */ 

struct AES256Param
 {
  static const ulen KeyWordLen = 8 ;
  static const ulen Rounds = 14 ;
  
  static const char *const Name;
  static const char *const InverseName;
 };
 
/* struct AES<Param> */ 

template <class Param>
struct AES : AESBase
 {
  // consts
  
  static const ulen KeyWordLen = Param::KeyWordLen ;
  static const ulen KeyLen = 4*KeyWordLen ;
  
  static const ulen Rounds = Param::Rounds ;

  static const ulen RoundKeyWordLen = (Rounds+1)*BlockWordLen ;
  static const ulen RoundKeyLen = (Rounds+1)*BlockLen ;
  
  static const char * GetName() { return Param::Name; }
  
  // data
  
  uint8 round_key[RoundKeyLen];
  
  // methods
  
  void key(const uint8 src[KeyLen])
   {
    Range(round_key,KeyLen).copy(src);

    KeyExpansion<KeyWordLen,RoundKeyWordLen>(round_key);
   }
   
  void unkey()
   {
    Range(round_key).set_null();
   } 
  
  void apply(const uint8 src[BlockLen],uint8 *restrict dst/* [BlockLen] */) const
   {
    Range(dst,BlockLen).copy(src);
    
    apply(dst);
   }
   
  void apply(uint8 src_dst[BlockLen]) const
   {
    Apply<Rounds>(round_key,src_dst);
   }
 };

/* struct AESInverse<Param> */ 

template <class Param> 
struct AESInverse : AESBase
 {
  // consts
  
  static const ulen KeyWordLen = Param::KeyWordLen ;
  static const ulen KeyLen = 4*KeyWordLen ;
  
  static const ulen Rounds = Param::Rounds ;

  static const ulen RoundKeyWordLen = (Rounds+1)*BlockWordLen ;
  static const ulen RoundKeyLen = (Rounds+1)*BlockLen ;
  
  static const char * GetName() { return Param::InverseName; }
  
  // data
  
  uint8 round_key[RoundKeyLen];
  
  // methods
  
  void key(const uint8 src[KeyLen])
   {
    Range(round_key,KeyLen).copy(src);

    KeyExpansion<KeyWordLen,RoundKeyWordLen>(round_key);
   }
   
  void unkey()
   {
    Range(round_key).set_null();
   } 
  
  void apply(const uint8 src[BlockLen],uint8 *restrict dst/* [BlockLen] */) const
   {
    Range(dst,BlockLen).copy(src);
    
    apply(dst);
   }
   
  void apply(uint8 src_dst[BlockLen]) const
   {
    ApplyInverse<Rounds>(round_key,src_dst);
   }
 };

/* types */  

typedef BlockCipher<AES<AES128Param> > AES128;

typedef BlockCipher<AES<AES192Param> > AES192;

typedef BlockCipher<AES<AES256Param> > AES256;

typedef BlockCipher<AESInverse<AES128Param> > AESInverse128;

typedef BlockCipher<AESInverse<AES192Param> > AESInverse192;

typedef BlockCipher<AESInverse<AES256Param> > AESInverse256;

} // namespace Crypton
} // namespace CCore
 
#endif
 

