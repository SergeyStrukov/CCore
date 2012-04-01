/* SHA.cpp */ 
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
 
#include <CCore/inc/crypton/SHA.h>
 
#include <CCore/inc/SaveLoad.h>

namespace CCore {
namespace Crypton {

/* struct SHA32Word */

void SHA32Word::Load(Word &x,const uint8 data[4])
 {
  SaveLoadBe32 temp(data[0],data[1],data[2],data[3]);
  
  x=temp.get();
 }

void SHA32Word::Save(Word x,uint8 data[4])
 {
  SaveLoadBe32 temp(x);
  
  Range(temp.buf).copyTo(data);
 }

void SHA32Word::Load(Word W[WLoadLen],const uint8 block[BlockLen])
 {
  Load(W[0],block);
  Load(W[1],block+4);
  Load(W[2],block+8);
  Load(W[3],block+12);
  
  Load(W[4],block+16);
  Load(W[5],block+20);
  Load(W[6],block+24);
  Load(W[7],block+28);
  
  Load(W[8],block+32);
  Load(W[9],block+36);
  Load(W[10],block+40);
  Load(W[11],block+44);
  
  Load(W[12],block+48);
  Load(W[13],block+52);
  Load(W[14],block+56);
  Load(W[15],block+60);
 }

void SHA32Word::Load(Word W[WLoadLen],const uint8 block[BlockLen-TailLen],TotalType total)
 {
  Load(W[0],block);
  Load(W[1],block+4);
  Load(W[2],block+8);
  Load(W[3],block+12);
  
  Load(W[4],block+16);
  Load(W[5],block+20);
  Load(W[6],block+24);
  Load(W[7],block+28);
  
  Load(W[8],block+32);
  Load(W[9],block+36);
  Load(W[10],block+40);
  Load(W[11],block+44);
  
  Load(W[12],block+48);
  Load(W[13],block+52);
  
  W[14]=Word(total>>32);
  W[15]=Word(total    );
 }

/* struct SHA64Word */

void SHA64Word::Load(Word &x,const uint8 data[8])
 {
  SaveLoadBe64 temp(data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
  
  x=temp.get();
 }

void SHA64Word::Save(Word x,uint8 data[8])
 {
  SaveLoadBe64 temp(x);
  
  Range(temp.buf).copyTo(data);
 }

void SHA64Word::Load(Word W[WLoadLen],const uint8 block[BlockLen])
 {
  Load(W[0],block);
  Load(W[1],block+8);
  Load(W[2],block+16);
  Load(W[3],block+24);
  
  Load(W[4],block+32);
  Load(W[5],block+40);
  Load(W[6],block+48);
  Load(W[7],block+56);
  
  Load(W[8],block+64);
  Load(W[9],block+72);
  Load(W[10],block+80);
  Load(W[11],block+88);
  
  Load(W[12],block+96);
  Load(W[13],block+104);
  Load(W[14],block+112);
  Load(W[15],block+120);
 }

void SHA64Word::Load(Word W[WLoadLen],const uint8 block[BlockLen-TailLen],TotalType total)
 {
  Load(W[0],block);
  Load(W[1],block+8);
  Load(W[2],block+16);
  Load(W[3],block+24);
  
  Load(W[4],block+32);
  Load(W[5],block+40);
  Load(W[6],block+48);
  Load(W[7],block+56);
  
  Load(W[8],block+64);
  Load(W[9],block+72);
  Load(W[10],block+80);
  Load(W[11],block+88);
  
  Load(W[12],block+96);
  Load(W[13],block+104);
  
  W[14]=total.hi;
  W[15]=total.lo;
 }

/* struct SHA1Param */

const char *const SHA1Param::Name="SHA1";

void SHA1Param::State::Extend(Word W[WLen])
 {
  for(ulen i=WLoadLen; i<WLen ;i++) W[i]=Rol32(Word( W[i-3]^W[i-8]^W[i-14]^W[i-16] ),1);
 }

void SHA1Param::State::add(Word W[WLen])
 {
  Extend(W);

  State temp(*this);
  
  temp.run<Func1>(W);
  temp.run<Func2>(W+RunLen);
  temp.run<Func3>(W+2*RunLen);
  temp.run<Func4>(W+3*RunLen);
  
  a+=temp.a;
  b+=temp.b;
  c+=temp.c;
  d+=temp.d;
  e+=temp.e;
 }

void SHA1Param::State::add(const uint8 block[BlockLen])
 {
  Word W[WLen];
  
  Load(W,block);
  
  add(W);
 }

void SHA1Param::State::add(const uint8 block[BlockLen-TailLen],TotalType total)
 {
  Word W[WLen];
  
  Load(W,block,total);
  
  add(W);
 }

void SHA1Param::State::finish(uint8 digest[DigestLen])
 {
  Save(a,digest);
  Save(b,digest+4);
  Save(c,digest+8);
  Save(d,digest+12);
  Save(e,digest+16);
 }

/* struct SHA256Param */

const char *const SHA256Param::Name="SHA256";
  
const SHA256Param::Word SHA256Param::State::K[WLen]=
 {
  0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
  0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
  0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
  0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
  0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
  0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
  0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
  0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
 };

void SHA256Param::State::Extend(Word W[WLen])
 {
  for(ulen i=WLoadLen; i<WLen ;i++) W[i]=Word( Sigma1(W[i-2])+W[i-7]+Sigma0(W[i-15])+W[i-16] );
 }

void SHA256Param::State::Run(Word &a,Word &b,Word &c,Word &d,Word &e,Word &f,Word &g,Word &h,Word w)
 {
  Word t1=Word( USigma1(e)+((e&f)^(~e&g))+h+w );
  Word t2=Word( USigma0(a)+((a&b)^(a&c)^(b&c)) );
  
  h=t1+t2;
  d+=t1;
 }

void SHA256Param::State::run8(const Word W[8],const Word K[8])
 {
  Run(a,b,c,d,e,f,g,h,K[0]+W[0]);
  Run(h,a,b,c,d,e,f,g,K[1]+W[1]);
  Run(g,h,a,b,c,d,e,f,K[2]+W[2]);
  Run(f,g,h,a,b,c,d,e,K[3]+W[3]);
  Run(e,f,g,h,a,b,c,d,K[4]+W[4]);
  Run(d,e,f,g,h,a,b,c,K[5]+W[5]);
  Run(c,d,e,f,g,h,a,b,K[6]+W[6]);
  Run(b,c,d,e,f,g,h,a,K[7]+W[7]);
 }

void SHA256Param::State::run(const Word W[WLen])
 {
#if 0  
  
  for(ulen i=0; i<WLen ;i++)
    {
     Word t1=Word( USigma1(e)+((e&f)^(~e&g))+h+K[i]+W[i] );
     Word t2=Word( USigma0(a)+((a&b)^(a&c)^(b&c)) );
     
     h=g;
     g=f;
     f=e;
     e=d+t1;
     d=c;
     c=b;
     b=a;
     a=t1+t2;
    }
  
#else
  
  run8(W,K);
  run8(W+8,K+8);
  run8(W+16,K+16);
  run8(W+24,K+24);
  run8(W+32,K+32);
  run8(W+40,K+40);
  run8(W+48,K+48);
  run8(W+56,K+56);
  
#endif  
 }

void SHA256Param::State::add(Word W[WLen])
 {
  Extend(W);
  
  State temp(*this);
  
  temp.run(W);
  
  a+=temp.a;
  b+=temp.b;
  c+=temp.c;
  d+=temp.d;
  e+=temp.e;
  f+=temp.f;
  g+=temp.g;
  h+=temp.h;
 }

void SHA256Param::State::add(const uint8 block[BlockLen])
 {
  Word W[WLen];
  
  Load(W,block);
  
  add(W);
 }

void SHA256Param::State::add(const uint8 block[BlockLen-TailLen],TotalType total)
 {
  Word W[WLen];
  
  Load(W,block,total);
  
  add(W);
 }

void SHA256Param::State::finish(uint8 digest[DigestLen])
 {
  Save(a,digest);
  Save(b,digest+4);
  Save(c,digest+8);
  Save(d,digest+12);
  Save(e,digest+16);
  Save(f,digest+20);
  Save(g,digest+24);
  Save(h,digest+28);
 }

/* struct SHA224Param */

const char *const SHA224Param::Name="SHA224";

void SHA224Param::State::finish(uint8 digest[DigestLen])
 {
  Save(a,digest);
  Save(b,digest+4);
  Save(c,digest+8);
  Save(d,digest+12);
  Save(e,digest+16);
  Save(f,digest+20);
  Save(g,digest+24);
 }
  
/* struct SHA512Param */

const char *const SHA512Param::Name="SHA512";

const SHA512Param::Word SHA512Param::State::K[WLen]=
 {
  0x428a2f98d728ae22ull, 0x7137449123ef65cdull, 0xb5c0fbcfec4d3b2full, 0xe9b5dba58189dbbcull,
  0x3956c25bf348b538ull, 0x59f111f1b605d019ull, 0x923f82a4af194f9bull, 0xab1c5ed5da6d8118ull,
  0xd807aa98a3030242ull, 0x12835b0145706fbeull, 0x243185be4ee4b28cull, 0x550c7dc3d5ffb4e2ull,
  0x72be5d74f27b896full, 0x80deb1fe3b1696b1ull, 0x9bdc06a725c71235ull, 0xc19bf174cf692694ull,
  0xe49b69c19ef14ad2ull, 0xefbe4786384f25e3ull, 0x0fc19dc68b8cd5b5ull, 0x240ca1cc77ac9c65ull,
  0x2de92c6f592b0275ull, 0x4a7484aa6ea6e483ull, 0x5cb0a9dcbd41fbd4ull, 0x76f988da831153b5ull,
  0x983e5152ee66dfabull, 0xa831c66d2db43210ull, 0xb00327c898fb213full, 0xbf597fc7beef0ee4ull,
  0xc6e00bf33da88fc2ull, 0xd5a79147930aa725ull, 0x06ca6351e003826full, 0x142929670a0e6e70ull,
  0x27b70a8546d22ffcull, 0x2e1b21385c26c926ull, 0x4d2c6dfc5ac42aedull, 0x53380d139d95b3dfull,
  0x650a73548baf63deull, 0x766a0abb3c77b2a8ull, 0x81c2c92e47edaee6ull, 0x92722c851482353bull,
  0xa2bfe8a14cf10364ull, 0xa81a664bbc423001ull, 0xc24b8b70d0f89791ull, 0xc76c51a30654be30ull,
  0xd192e819d6ef5218ull, 0xd69906245565a910ull, 0xf40e35855771202aull, 0x106aa07032bbd1b8ull,
  0x19a4c116b8d2d0c8ull, 0x1e376c085141ab53ull, 0x2748774cdf8eeb99ull, 0x34b0bcb5e19b48a8ull,
  0x391c0cb3c5c95a63ull, 0x4ed8aa4ae3418acbull, 0x5b9cca4f7763e373ull, 0x682e6ff3d6b2b8a3ull,
  0x748f82ee5defb2fcull, 0x78a5636f43172f60ull, 0x84c87814a1f0ab72ull, 0x8cc702081a6439ecull,
  0x90befffa23631e28ull, 0xa4506cebde82bde9ull, 0xbef9a3f7b2c67915ull, 0xc67178f2e372532bull,
  0xca273eceea26619cull, 0xd186b8c721c0c207ull, 0xeada7dd6cde0eb1eull, 0xf57d4f7fee6ed178ull,
  0x06f067aa72176fbaull, 0x0a637dc5a2c898a6ull, 0x113f9804bef90daeull, 0x1b710b35131c471bull,
  0x28db77f523047d84ull, 0x32caab7b40c72493ull, 0x3c9ebe0a15c9bebcull, 0x431d67c49c100d4cull,
  0x4cc5d4becb3e42b6ull, 0x597f299cfc657e2aull, 0x5fcb6fab3ad6faecull, 0x6c44198c4a475817ull
 };

void SHA512Param::State::Extend(Word W[WLen])
 {
  for(ulen i=WLoadLen; i<WLen ;i++) W[i]=Word( Sigma1(W[i-2])+W[i-7]+Sigma0(W[i-15])+W[i-16] );
 }

void SHA512Param::State::Run(Word &a,Word &b,Word &c,Word &d,Word &e,Word &f,Word &g,Word &h,Word w)
 {
  Word t1=Word( USigma1(e)+((e&f)^(~e&g))+h+w );
  Word t2=Word( USigma0(a)+((a&b)^(a&c)^(b&c)) );
  
  h=t1+t2;
  d+=t1;
 }

void SHA512Param::State::run8(const Word W[8],const Word K[8])
 {
  Run(a,b,c,d,e,f,g,h,K[0]+W[0]);
  Run(h,a,b,c,d,e,f,g,K[1]+W[1]);
  Run(g,h,a,b,c,d,e,f,K[2]+W[2]);
  Run(f,g,h,a,b,c,d,e,K[3]+W[3]);
  Run(e,f,g,h,a,b,c,d,K[4]+W[4]);
  Run(d,e,f,g,h,a,b,c,K[5]+W[5]);
  Run(c,d,e,f,g,h,a,b,K[6]+W[6]);
  Run(b,c,d,e,f,g,h,a,K[7]+W[7]);
 }

void SHA512Param::State::run(const Word W[WLen])
 {
  run8(W,K);
  run8(W+8,K+8);
  run8(W+16,K+16);
  run8(W+24,K+24);
  run8(W+32,K+32);
  run8(W+40,K+40);
  run8(W+48,K+48);
  run8(W+56,K+56);
  run8(W+64,K+64);
  run8(W+72,K+72);
 }

void SHA512Param::State::add(Word W[WLen])
 {
  Extend(W);
  
  State temp(*this);
  
  temp.run(W);
  
  a+=temp.a;
  b+=temp.b;
  c+=temp.c;
  d+=temp.d;
  e+=temp.e;
  f+=temp.f;
  g+=temp.g;
  h+=temp.h;
 }

void SHA512Param::State::add(const uint8 block[BlockLen])
 {
  Word W[WLen];
  
  Load(W,block);
  
  add(W);
 }

void SHA512Param::State::add(const uint8 block[BlockLen-TailLen],TotalType total)
 {
  Word W[WLen];
  
  Load(W,block,total);
  
  add(W);
 }

void SHA512Param::State::finish(uint8 digest[DigestLen])
 {
  Save(a,digest);
  Save(b,digest+8);
  Save(c,digest+16);
  Save(d,digest+24);
  Save(e,digest+32);
  Save(f,digest+40);
  Save(g,digest+48);
  Save(h,digest+56);
 }

/* struct SHA384Param */

const char *const SHA384Param::Name="SHA384";

void SHA384Param::State::finish(uint8 digest[DigestLen])
 {
  Save(a,digest);
  Save(b,digest+8);
  Save(c,digest+16);
  Save(d,digest+24);
  Save(e,digest+32);
  Save(f,digest+40);
 }

} // namespace Crypton
} // namespace CCore
 

