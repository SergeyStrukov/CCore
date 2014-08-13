/* test0107.PKE.cpp */ 
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

#include <CCore/inc/net/PKE.h>

namespace App {

namespace Private_0107 {


} // namespace Private_0107
 
using namespace Private_0107; 
 
/* Testit<107> */ 

template<>
const char *const Testit<107>::Name="Test107 PKE";

template<>
bool Testit<107>::Main() 
 {
  Net::PSec::ClientId client_id;
  Net::PSec::PrimeKey client_key;
  Net::PSec::PrimeKey server_key;
  
  Net::PSec::ClientNegotiant neg("",client_id,client_key,server_key);
  
  neg.start(Net::PSec::CryptAlgoSelect(Net::PSec::CryptID_AES128,Net::PSec::HashID_SHA1,Net::PSec::DHGroupID_I),
            Net::PSec::CryptAlgoSelect(Net::PSec::CryptID_AES256,Net::PSec::HashID_SHA256,Net::PSec::DHGroupID_II));
  
  return true;
 }
 
} // namespace App
 
