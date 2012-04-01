/* CheckedData.cpp */ 
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
 
#include <CCore/inc/net/CheckedData.h>
 
namespace CCore {
namespace Net {

/* class CheckedData */ 

CheckedData::CheckedData()
 {
  start_sum=random.next8();
 }
    
ulen CheckedData::getLen(ulen max_len)
 {
  if( max_len<=2 ) return max_len;
    
  return random.select(2,max_len);
 }
    
bool CheckedData::fill(PtrLen<uint8> data) 
 {
  if( data.len<2 ) return false;
     
  uint8 sum=uint8(data.len);
     
  data[0]=sum;
     
  sum+=start_sum;
    
  PtrLen<uint8> r=data;
     
  for(r+=2; +r ;++r) 
    {
     uint8 b=random.next8();
       
     *r=b;
     sum+=b;
    }
       
  data[1]=sum;  
     
  return true; 
 }
    
bool CheckedData::check(PtrLen<const uint8> data) const
 {
  if( data.len<2 ) return false;
     
  uint8 sum=data[0];
     
  if( sum!=(uint8)data.len ) return false;
     
  sum+=start_sum;
    
  PtrLen<const uint8> r=data;
     
  for(r+=2; +r ;++r) 
    {
     sum+=*r;
    }
       
  return data[1]==sum ;  
 }
 
} // namespace Net
} // namespace CCore
 

