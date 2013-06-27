/* test3004.IntelAES.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/IntelAES.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_3004 {

/* functions */

template <class T>
void ApplyBlockCipher(T &cipher,const uint8 *src,uint8 *dst,ulen blocks)
 {
  const ulen BlockLen = T::BlockLen ;
  
  for(; blocks ;blocks--,src+=BlockLen,dst+=BlockLen) cipher.apply(src,dst);
 }

/* classes */

template <class C1,class C2> class Engine;

/* class Engine<C1,C2> */

template <class C1,class C2> 
class Engine : NoCopy
 {
   Random random;
   
   const ulen KeyLen = C1::KeyLen ;
   const ulen BlockLen = C1::BlockLen ;
   
   static_assert( C1::KeyLen==C2::KeyLen ,"C1::KeyLen != C2::KeyLen");
   static_assert( C1::BlockLen==C2::BlockLen ,"C1::BlockLen != C2::BlockLen");
   
   C1 cipher1;
   C2 cipher2;
  
   ulen blocks;
   DynArray<uint8> key;
   DynArray<uint8> src;
   DynArray<uint8> dst1;
   DynArray<uint8> dst2;
   
  public:
   
   explicit Engine(ulen blocks_)
    : blocks(blocks_),
      key(KeyLen),
      src(BlockLen*blocks),
      dst1(BlockLen*blocks),
      dst2(BlockLen*blocks)
    {
     Printf(Con,"Compare #; and #;\n",C1::GetName(),C2::GetName());
    }
   
   ~Engine() 
    {
    }
   
   bool step()
    {
     random.fill(Range(key));
     random.fill(Range(src));
     
     cipher1.key(key.getPtr());
     cipher2.key(key.getPtr());

     ApplyBlockCipher(cipher1,src.getPtr(),dst1.getPtr(),blocks);
     ApplyBlockCipher(cipher2,src.getPtr(),dst2.getPtr(),blocks);
     
#if 0
     
     Printf(Con,"\n#;\n\n#;\n",PrintDump(Range(dst1)),PrintDump(Range(dst2)));
     
#endif     
     
     return Range(dst1).equal(Range(dst2));
    }
   
   void run(ulen count)
    {
     for(; count ;count--)
       if( !step() )
         {
          Printf(Exception,"test failed");
         }
     
     Printf(Con,"Success\n\n");
    }
 };

} // namespace Private_3004
 
using namespace Private_3004; 
 
/* Testit<3004> */ 

template<>
const char *const Testit<3004>::Name="Test3004 IntelAES";

template<>
bool Testit<3004>::Main() 
 {
  Printf(Con,"Detect = #;\n\n",Crypton::DetectIntelAES());

  {
   Engine<Crypton::AES128,Crypton::IntelAES128> engine(1000);
  
   engine.run(1000);
  } 
  
  {
   Engine<Crypton::AES192,Crypton::IntelAES192> engine(1000);
  
   engine.run(1000);
  } 
  
  {
   Engine<Crypton::AES256,Crypton::IntelAES256> engine(1000);
  
   engine.run(1000);
  } 
  
  {
   Engine<Crypton::AESInverse128,Crypton::IntelAESInverse128> engine(1000);
  
   engine.run(1000);
  } 
  
  {
   Engine<Crypton::AESInverse192,Crypton::IntelAESInverse192> engine(1000);
  
   engine.run(1000);
  } 
  
  {
   Engine<Crypton::AESInverse256,Crypton::IntelAESInverse256> engine(1000);
  
   engine.run(1000);
  } 
  
  return true;
 }
 
} // namespace App
 
