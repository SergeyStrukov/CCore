/* test0040.PtrLen.cpp */ 
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

#include <CCore/test/test.h>

namespace App {

namespace Private_0040 {

/* functions */

void copy0(const char *restrict src,char *restrict dst,ulen len)
 {
  for(; len ;len--) *(dst++)=*(src++);
 }
 
void copy1(const char *src,char *dst,ulen len)
 {
  Range(src,len).copyTo(dst);
 }
 
void copy2(const char *src,char *dst,ulen len)
 {
  Range(dst,len).copyFrom(src);
 }
 
void copy3(const char *src,char *dst,ulen len)
 {
  Range(dst,len).copy(src);
 }
 
void copy4(const short *src,int *dst,ulen len)
 {
  Range(src,len).copyTo(dst);
 }
 
void copy5(const short *src,int *dst,ulen len)
 {
  Range(dst,len).copyFrom(src);
 }

template <class R> 
void RevShow(R range)
 {
  for(auto fin=range.getFin(); fin.next() ;) Printf(Con,"#;\n",*fin);
 }
 
} // namespace Private_0040
 
using namespace Private_0040; 
 
/* Testit<40> */ 

template<>
const char *const Testit<40>::Name="Test40 PtrLen";

template<>
bool Testit<40>::Main() 
 { 
  PtrLen<int> r;
 
  Mutate<char>(r);
  Mutate<uint8>(r);
  Mutate<const char>(r);
  Mutate<const uint8>(r);
 
  PtrLen<int> s;
 
  Mutate<const char>(s);
  Mutate<const uint8>(s);
  
  int buf[10];
  
  int i=1; 
  
  for(auto r=Range(buf); +r ;++r) *r=i++;
  
  RevShow(Range(buf));
  
  return true;
 }
 
} // namespace App
 
