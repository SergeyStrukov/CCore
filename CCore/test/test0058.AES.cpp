/* test0058.AES.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/crypton/AES.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_0058 {

/* struct Data128 */

struct Data128
 {
  typedef Crypton::AES128 Cipher;
  
  typedef Crypton::AESInverse128 InverseCipher;
  
  static const uint8 Input[Cipher::BlockLen]; 
   
  static const uint8 Output[Cipher::BlockLen];
   
  static const uint8 Key[Cipher::KeyLen];
 };

const uint8 Data128::Input[Cipher::BlockLen]= 
 {
  0x00, 0x11, 0x22, 0x33,
  0x44, 0x55, 0x66, 0x77,
  0x88, 0x99, 0xaa, 0xbb,
  0xcc, 0xdd, 0xee, 0xff
 };
 
const uint8 Data128::Output[Cipher::BlockLen]=
 {
  0x69, 0xc4, 0xe0, 0xd8,
  0x6a, 0x7b, 0x04, 0x30, 
  0xd8, 0xcd, 0xb7, 0x80,
  0x70, 0xb4, 0xc5, 0x5a
 };
 
const uint8 Data128::Key[Cipher::KeyLen]=
 {
  0x00, 0x01, 0x02, 0x03,
  0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b,
  0x0c, 0x0d, 0x0e, 0x0f
 };

/* struct Data192 */

struct Data192
 {
  typedef Crypton::AES192 Cipher;
  
  typedef Crypton::AESInverse192 InverseCipher;
  
  static const uint8 Input[Cipher::BlockLen]; 
   
  static const uint8 Output[Cipher::BlockLen];
   
  static const uint8 Key[Cipher::KeyLen];
 };

const uint8 Data192::Input[Cipher::BlockLen]= 
 {
  0x00, 0x11, 0x22, 0x33,
  0x44, 0x55, 0x66, 0x77,
  0x88, 0x99, 0xaa, 0xbb,
  0xcc, 0xdd, 0xee, 0xff
 };
 
const uint8 Data192::Output[Cipher::BlockLen]=
 {
  0xdd, 0xa9, 0x7c, 0xa4,
  0x86, 0x4c, 0xdf, 0xe0,
  0x6e, 0xaf, 0x70, 0xa0,
  0xec, 0x0d, 0x71, 0x91
 };
 
const uint8 Data192::Key[Cipher::KeyLen]=
 {
  0x00, 0x01, 0x02, 0x03,
  0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b,
  0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13,
  0x14, 0x15, 0x16, 0x17
 };

/* struct Data256 */

struct Data256
 {
  typedef Crypton::AES256 Cipher;
  
  typedef Crypton::AESInverse256 InverseCipher;
  
  static const uint8 Input[Cipher::BlockLen]; 
   
  static const uint8 Output[Cipher::BlockLen];
   
  static const uint8 Key[Cipher::KeyLen];
 };

const uint8 Data256::Input[Cipher::BlockLen]= 
 {
  0x00, 0x11, 0x22, 0x33,
  0x44, 0x55, 0x66, 0x77,
  0x88, 0x99, 0xaa, 0xbb,
  0xcc, 0xdd, 0xee, 0xff
 };
 
const uint8 Data256::Output[Cipher::BlockLen]=
 {
  0x8e, 0xa2, 0xb7, 0xca,
  0x51, 0x67, 0x45, 0xbf,
  0xea, 0xfc, 0x49, 0x90,
  0x4b, 0x49, 0x60, 0x89
 };
 
const uint8 Data256::Key[Cipher::KeyLen]=
 {
  0x00, 0x01, 0x02, 0x03,
  0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b,
  0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13,
  0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b,
  0x1c, 0x1d, 0x1e, 0x1f
 };

/* testData<T>() */

template <class T>
void testData()
 {
  typename T::Cipher cipher(T::Key);
  uint8 result[T::Cipher::BlockLen];
  
  cipher.apply(T::Input,result);
  
  if( !Range(result).equal(T::Output) ) 
    {
     Printf(Exception,"#; failed",T::Cipher::GetName());
    }
  
  Printf(Con,"#; ok\n",T::Cipher::GetName());
 }

/* testDataInverse<T>() */

template <class T>
void testDataInverse()
 {
  typename T::InverseCipher cipher(T::Key);
  uint8 result[T::InverseCipher::BlockLen];
  
  cipher.apply(T::Output,result);
  
  if( !Range(result).equal(T::Input) ) 
    {
     Printf(Exception,"#; failed",T::InverseCipher::GetName());
    }
  
  Printf(Con,"#; ok\n",T::InverseCipher::GetName());
 }

/* SBox() */

uint8 SBox(uint8 a)
 {
  return Crypton::AESBase::Transform(Crypton::AESBase::Inverse(a));
 }

/* InvSBox() */

uint8 InvSBox(uint8 a)
 {
  for(uint8 b=255; b ;b--) if( SBox(b)==a ) return b;
  
  return 0;
 }

/* PrintLut() */

template <uint8 Func(uint8),class P>
void PrintLut(P &&out,const char *name)
 {
  Printf(out,"const uint8 #;[256]=\n {\n",name);
  
  uint8 a=0;
  
  for(ulen i=0; i<16 ;i++)
    {
     Printf(out,"  ");
     
     for(ulen j=0; j<15 ;j++)
       Printf(out,"#4.xi;, ",Func(a++));
     
     if( i<15 )
       Printf(out,"#4.xi;,\n",Func(a++));
     else
       Printf(out,"#4.xi;\n",Func(a++));
    }
  
  Printf(out," };\n\n");
 }

/* TestLut() */

template <uint8 Func(uint8)>
void TestLut(const uint8 (&Table)[256],const char *name)
 {
  uint8 a=0;
  
  do
    {
     if( Func(a)!=Table[a] )
       {
        Printf(Exception,"Lut #; incorrect",name);
       }
    }
  while( ++a );
 }

/* class Test */

class Test : NoCopy
 {
   Random random;
   
  public:
   
   Test() {}
   
   ~Test() {}
   
   template <class C,class IC>
   void test1(ulen count1,ulen count2)
    {
     static_assert( C::KeyLen==IC::KeyLen ,"C::KeyLen!=IC::KeyLen");
     static_assert( C::BlockLen==IC::BlockLen ,"C::BlockLen!=IC::BlockLen");
     
     for(ulen cnt=count1; cnt ;cnt--)
       {
        uint8 key[C::KeyLen];
        
        random.fill(Range(key));
        
        C cipher(key);
        IC decipher(key);
        
        uint8 block1[C::BlockLen];
        uint8 block2[C::BlockLen];
        uint8 block3[C::BlockLen];
        
        for(ulen cnt=count2; cnt ;cnt--)
          {
           random.fill(Range(block1));
           
           cipher.apply(block1,block2);
           decipher.apply(block2,block3);
           
           if( !Range(block1).equal(block3) )
             {
              Printf(Exception,"test1 failed");
             }
          }
       }
    }
 };

} // namespace Private_0058
 
using namespace Private_0058; 
 
/* Testit<58> */ 

template<>
const char *const Testit<58>::Name="Test58 AES";

template<>
bool Testit<58>::Main() 
 {
  testData<Data128>();
  testData<Data192>();
  testData<Data256>();
  
  testDataInverse<Data128>();
  testDataInverse<Data192>();
  testDataInverse<Data256>();
  
  TestLut<SBox>(Crypton::AESBase::SBox,"SBox");
  TestLut<InvSBox>(Crypton::AESBase::SBoxInverse,"SBoxInverse");
  
  TestLut<Crypton::AESBase::Mul02>(Crypton::AESBase::Mul02Table,"Mul02");
  TestLut<Crypton::AESBase::Mul03>(Crypton::AESBase::Mul03Table,"Mul03");
  TestLut<Crypton::AESBase::Mul0e>(Crypton::AESBase::Mul0eTable,"Mul0e");
  TestLut<Crypton::AESBase::Mul0b>(Crypton::AESBase::Mul0bTable,"Mul0b");
  TestLut<Crypton::AESBase::Mul0d>(Crypton::AESBase::Mul0dTable,"Mul0d");
  TestLut<Crypton::AESBase::Mul09>(Crypton::AESBase::Mul09Table,"Mul09");
  
  Test test;
  
  test.test1<Crypton::AES128,Crypton::AESInverse128>(100,1000);
  test.test1<Crypton::AES192,Crypton::AESInverse192>(100,1000);
  test.test1<Crypton::AES256,Crypton::AESInverse256>(100,1000);
  
  return true;
 }
 
} // namespace App
 
