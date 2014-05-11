/* BlockCipher.h */ 
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

#ifndef CCore_inc_crypton_BlockCipher_h
#define CCore_inc_crypton_BlockCipher_h
 
#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Crypton {

/* functions */

void GuardNoCipherKey();

/* classes */ 

template <class T> class BlockCipher;

/* class BlockCipher<T> */ 

template <class T> 
class BlockCipher : NoCopy
 {
  public:
  
   // length in octets
  
   static const ulen BlockLen = T::BlockLen ;
   static const ulen KeyLen = T::KeyLen ;
   
   static const char * GetName() { return T::GetName(); }
   
  private:
  
   T func;
   bool ok;
   
  private:
   
   void guardKey() const
    {
     if( !ok ) GuardNoCipherKey();
    }
  
  public:
   
   // constructors
  
   BlockCipher() { unkey(); }
   
   ~BlockCipher() { unkey(); }
   
   explicit BlockCipher(const uint8 src[KeyLen]) : ok(false) { key(src); }
   
   // methods
   
   void key(const uint8 src[KeyLen]) { func.key(src); ok=true; }
   
   void unkey() { func.unkey(); ok=false; }
   
   void apply(const uint8 src[BlockLen],uint8 *restrict dst/* [BlockLen] */) const
    {
     guardKey();
    
     func.apply(src,dst);
    }
   
   void apply(uint8 src_dst[BlockLen]) const
    {
     guardKey();
    
     func.apply(src_dst);
    }
 };
 
} // namespace Crypton
} // namespace CCore
 
#endif
 

