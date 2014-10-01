/* test0097.MD5.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/crypton/MD5.h>

namespace App {

namespace Private_0097 {

/* struct Data1 */

struct Data1
 {
  using Func = Crypton::MD5 ;
  
  static const uint8 Input[1];
  static const uint8 Digest[16];
 };

const uint8 Data1::Input[1]={'a'};

const uint8 Data1::Digest[16]=
 {
  0x0C, 0xC1, 0x75, 0xB9,
  0xC0, 0xF1, 0xB6, 0xA8,
  0x31, 0xC3, 0x99, 0xE2,
  0x69, 0x77, 0x26, 0x61
 };

/* struct Data2 */

struct Data2
 {
  using Func = Crypton::MD5 ;
  
  static const uint8 Input[3];
  static const uint8 Digest[16];
 };

const uint8 Data2::Input[3]={'a','b','c'};

const uint8 Data2::Digest[16]=
 {
  0x90, 0x01, 0x50, 0x98,
  0x3C, 0xD2, 0x4F, 0xB0,
  0xD6, 0x96, 0x3F, 0x7D,
  0x28, 0xE1, 0x7F, 0x72
 };

/* struct Data3 */

struct Data3
 {
  using Func = Crypton::MD5 ;
  
  static const uint8 Input[14];
  static const uint8 Digest[16];
 };

const uint8 Data3::Input[14]={'m','e','s','s','a','g','e',' ','d','i','g','e','s','t'};

const uint8 Data3::Digest[16]=
 {
  0xF9, 0x6B, 0x69, 0x7D,
  0x7C, 0xB7, 0x93, 0x8D,
  0x52, 0x5A, 0x2F, 0x31,
  0xAA, 0xF1, 0x61, 0xD0
 };

/* testData<T>() */

template <class T>
void testData()
 {
  typename T::Func hash;
  uint8 digest[T::Func::DigestLen];
  
  hash.add(Range(T::Input));
  
  hash.finish(digest);
  
  //Printf(Con,"\n#;\n",PrintDump(Range(digest)));
  
  if( !Range(digest).equal(T::Digest) )
    {
     Printf(Exception,"#; failed",T::Func::GetName());
    }
 }

} // namespace Private_0097
 
using namespace Private_0097; 
 
/* Testit<97> */ 

template<>
const char *const Testit<97>::Name="Test97 MD5";

template<>
bool Testit<97>::Main() 
 {
  testData<Data1>();
  testData<Data2>();
  testData<Data3>();
  
  return true;
 }
 
} // namespace App
 
