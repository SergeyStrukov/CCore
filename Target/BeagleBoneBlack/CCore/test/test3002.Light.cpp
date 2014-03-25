/* test3002.Light.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Timer.h>

#include <CCore/inc/dev/DevRW.h>

namespace App {

namespace Private_3002 {

const uint32 BaseAddress = 0x4804C000 ;

const uint32 OUT    = 0x13C ;
const uint32 CLROUT = 0x190 ;
const uint32 SETOUT = 0x194 ;

uint32 Mask(uint32 bits)
 {
  return (bits&15)<<21;
 }

void SetLight(uint32 bits)
 {
  Dev::RegRW rw(BaseAddress);

  rw.set<uint32>(OUT,Mask(bits));
 }

void OnLight(uint32 bits)
 {
  Dev::RegRW rw(BaseAddress);

  rw.set<uint32>(SETOUT,Mask(bits));
 }

void OffLight(uint32 bits)
 {
  Dev::RegRW rw(BaseAddress);

  rw.set<uint32>(CLROUT,Mask(bits));
 }

void Delay(unsigned tsec)
 {
  for(SecTimer timer; timer.less(tsec) ;);
 }

} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 Light";

template<>
bool Testit<3002>::Main() 
 {
  SetLight(15);
  
  Delay(5);
  
  for(unsigned cnt=100; cnt ;cnt--)
    {
     Printf(Con,"cnt = #;\n",cnt);
    
     OffLight(5);
    
     Delay(5);
    
     OnLight(5);
    
     Delay(5);
    }
  
  return true;
 }
 
} // namespace App
 
