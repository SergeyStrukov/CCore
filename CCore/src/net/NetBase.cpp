/* NetBase.cpp */ 
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
 
#include <CCore/inc/net/NetBase.h>

#include <CCore/inc/sys/SysAtomic.h>

namespace CCore {
namespace Net {

/* struct EthHeader */ 

EthHeader::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);
  
  ParseInbound(dev,inbound);
  
  if( !dev.finish() ) setDefault(); 
 }
 
/* struct CheckSum */  

void CheckSum::add(PtrLen<const uint8> data)
 {
  for(; data.len>=2 ;data+=2) add(data[0],data[1]);
  
  if( data.len==1 ) add(data[0],0);
 }
 
/* struct IPHeader */  

static Sys::Atomic NextId={0};
 
uint16 IPHeader::GetId()
 {
  return NextId++;
 }
   
void IPHeader::setCheckSum()
 {
  CheckSum sum;
  
  sum(vhl,tos,len,id,flags_offset,ttl,proto.get(),src.get(),dst.get());
  
  check_sum=sum.complete();
 }
  
bool IPHeader::testCheckSum() const
 {
  CheckSum sum;
  
  sum(vhl,tos,len,id,flags_offset,ttl,proto.get(),check_sum,src.get(),dst.get());
  
  return sum.test();
 }
 
IPHeader::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);
  
  ParseInbound(dev,inbound);
  ParseExtra(dev,extra);
  
  if( !dev.finish() ) setDefault(); 
 }
 
/* struct ICMPEcho */ 

void ICMPEcho::setCheckSum(PtrLen<const uint8> data)
 {
  CheckSum sum;
  
  sum(type.get(),code,id,num);
  
  sum.add(data);
  
  check_sum=sum.complete();
 }
  
bool ICMPEcho::testCheckSum(PtrLen<const uint8> data) const
 {
  CheckSum sum;
  
  sum(type.get(),code,check_sum,id,num);
  
  sum.add(data);
  
  return sum.test();
 }
 
/* struct UDPHeader */ 

void UDPHeader::setCheckSum(IPAddress src,IPAddress dst,IPLen len,PtrLen<const uint8> data)
 {
  CheckSum sum;
  
  uint16 proto=IP_UDP;
  
  sum(src.get(),dst.get(),proto,len,src_port,dst_port,len);
  
  sum.add(data);
  
  check_sum=sum.complete();
 }
  
bool UDPHeader::testCheckSum(IPAddress src,IPAddress dst,IPLen len,PtrLen<const uint8> data) const
 {
  if( !check_sum ) return true;
 
  CheckSum sum;
  
  uint16 proto=IP_UDP;
  
  sum(src.get(),dst.get(),proto,len,src_port,dst_port,len,check_sum);
  
  sum.add(data);
  
  return sum.test();
 }
 
} // namespace Net
} // namespace CCore
 

