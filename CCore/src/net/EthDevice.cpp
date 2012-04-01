/* EthDevice.cpp */ 
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
 
#include <CCore/inc/net/EthDevice.h>
 
namespace CCore {
namespace Net {

/* enum EthEvent */ 

const char * GetTextDesc(EthEvent ev)
 {
  static const char *const Table[]=
   {
    "Link up",       //  EthLink_Up
    "Link down",     //  EthLink_Down
 
    "Tx",            //  EthTx_Done
    "Rx",            //  EthRx_Done
    
    "Tx bad length", //  EthTx_BadPacketLen
    "Tx error",      //  EthTx_Error
  
    "Rx bad length", //  EthRx_BadPacketLen
    "Rx drop",       //  EthRx_Drop
    "Rx broadcast",  //  EthRx_Broadcast
    "Rx error"       //  EthRx_Error
    
    ""
   };
 
  return Table[ev];
 }
 
} // namespace Net
} // namespace CCore
 

