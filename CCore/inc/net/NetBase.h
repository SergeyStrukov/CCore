/* NetBase.h */ 
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

#ifndef CCore_inc_net_NetBase_h
#define CCore_inc_net_NetBase_h

#include <CCore/inc/net/XPoint.h>

#include <CCore/inc/Printf.h>
#include <CCore/inc/SaveLoad.h>
 
namespace CCore {
namespace Net {

/* consts */ 

const ulen EthHeaderLen = 14 ;

const ulen IPHeaderLen  = 20 ;

const ulen ARPacketLen  = 28 ;

const ulen ICMPEchoLen  =  8 ;

const ulen UDPHeaderLen =  8 ;

/* consts */ 

const ulen MaxEthFrameLen = 1514 ;

const ulen MaxEthDataLen  = MaxEthFrameLen - EthHeaderLen ; // 1500

const ulen MaxIPDataLen   = MaxEthDataLen - IPHeaderLen ;   // 1480

const ulen MaxUDPDataLen  = MaxIPDataLen - UDPHeaderLen ;   // 1472

/* enum KnownEthType */ 

enum KnownEthType : uint16
 {
  Eth_IP  = 0x800,
  Eth_ARP = 0x806
 };
 
/* enum KnownIProto */  

enum KnownIProto : uint8
 {
  IP_ICMP =  1,
  IP_UDP  = 17
 };
 
/* enum KnownARPType */ 

enum KnownARPType : uint16
 {
  ARP_Request = 1,
  ARP_Reply   = 2
 };
 
/* enum KnownICMPEchoType */ 

enum KnownICMPEchoType : uint8
 {
  ICMPEcho_Request = 8,
  ICMPEcho_Reply   = 0
 };
 
/* type IPLen */

typedef uint16 IPLen;

/* type UDPort */ 

typedef uint16 UDPort;

/* classes */ 

struct EthType;

struct IProto;

struct ARPType;

struct ICMPEchoType;

struct MACAddress;

struct IPAddress;

struct EthHeader;

struct CheckSum;

struct IPHeader;

struct ARPacket;

struct ICMPEcho;

struct UDPHeader;

/* struct EthType */ 

struct EthType
 {
  uint16 type;
  
  // constructors
  
  EthType() : type() {}
  
  EthType(KnownEthType type_) : type(type_) {}
  
  // methods
  
  uint16 get() const { return type; }
  
  // save/load object
  
  enum { SaveLoadLen = 2 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(type);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(type);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    switch( type )
      {
       case Eth_IP  : Putobj(out,"IP" ); break;
       case Eth_ARP : Putobj(out,"ARP"); break;
       
       default: Printf(out,"EthType(#.h;)",type);
      }
   }
 };
 
/* struct IProto */ 

struct IProto 
 {
  uint8 proto;
  
  // constructors
  
  IProto() : proto() {}
  
  IProto(KnownIProto proto_) : proto(proto_) {}
  
  // methods
  
  uint8 get() const { return proto; }
  
  // save/load object
  
  enum { SaveLoadLen = 1 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev(proto);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev(proto);
   }
  
  // print object
   
  template <class P>
  void print(P &out) const
   {
    switch( proto )
      {
       case IP_ICMP : Putobj(out,"ICMP"); break;
       case IP_UDP  : Putobj(out,"UDP" ); break;
       
       default: Printf(out,"IProto(#;)",proto);
      }
   }
 };
 
/* struct ARPType */  
 
struct ARPType
 {
  uint16 type;
  
  // constructors
  
  ARPType() : type() {}
  
  ARPType(KnownARPType type_) : type(type_) {}
  
  // methods
  
  uint16 get() const { return type; }
  
  // save/load object
  
  enum { SaveLoadLen = 2 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(type);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(type);
   }
  
  // print object
   
  template <class P>
  void print(P &out) const
   {
    switch( type )
      {
       case ARP_Request : Putobj(out,"ARP Request"); break;
       case ARP_Reply   : Putobj(out,"ARP Reply"  ); break;
       
       default: Printf(out,"ARP(#;)",type);
      }
   }
 };
 
/* struct ICMPEchoType */ 

struct ICMPEchoType
 {
  uint8 type;
  
  // constructors
  
  ICMPEchoType() : type() {}
  
  ICMPEchoType(KnownICMPEchoType type_) : type(type_) {}
  
  // methods
  
  uint8 get() const { return type; }
  
  // save/load object
  
  enum { SaveLoadLen = 1 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev(type);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev(type);
   }
  
  // print object
   
  template <class P>
  void print(P &out) const
   {
    switch( type )
      {
       case ICMPEcho_Request : Putobj(out,"ICMP Echo Request"); break;
       case ICMPEcho_Reply   : Putobj(out,"ICMP Echo Reply"  ); break;
       
       default: Printf(out,"ICMP(#;)",type);
      }
   }
 };
 
/* struct MACAddress */ 

struct MACAddress
 {
  uint8 address[6];
  
  // constructors
  
  MACAddress() : address() {}
  
  MACAddress(uint8 b0,uint8 b1,uint8 b2,uint8 b3,uint8 b4,uint8 b5)
   {
    address[0]=b0;
    address[1]=b1;
    address[2]=b2;
    address[3]=b3;
    address[4]=b4;
    address[5]=b5;
   }
  
  explicit MACAddress(XPoint point)
   {
    SaveLoadBe64 temp(point);
    
    address[0]=temp.buf[2];
    address[1]=temp.buf[3];
    address[2]=temp.buf[4];
    address[3]=temp.buf[5];
    address[4]=temp.buf[6];
    address[5]=temp.buf[7];
   }
  
  // methods
   
  static MACAddress Broadcast() { return MACAddress(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF); }
  
  XPoint get() const 
   { 
    return SaveLoadBe64(0,0,address[0],address[1],address[2],address[3],address[4],address[5]).get(); 
   }
  
  // save/load object
  
  enum { SaveLoadLen = 6 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.put(address,6);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.get(address,6);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"#2.16i;:#2.16i;:#2.16i;:#2.16i;:#2.16i;:#2.16i;",
                address[0],address[1],address[2],address[3],address[4],address[5]);
   }
 };
 
/* struct IPAddress */ 
 
struct IPAddress
 {
  uint32 address;
  
  // constructors
  
  IPAddress() : address() {}
   
  explicit IPAddress(uint32 address_) { address=address_; }
  
  IPAddress(uint8 b0,uint8 b1,uint8 b2,uint8 b3)
   {
    address=SaveLoadBe32(b0,b1,b2,b3).get(); 
   }
  
  // methods
   
  uint32 get() const { return address; } 
  
  friend bool operator == (IPAddress a,IPAddress b) { return a.address==b.address; }
  
  friend bool operator != (IPAddress a,IPAddress b) { return a.address!=b.address; }
  
  IPAddress getNet(IPAddress net_mask) const { return IPAddress(address&net_mask.address); }
  
  bool sameNet(IPAddress obj,IPAddress net_mask) const { return getNet(net_mask)==obj.getNet(net_mask); }
  
  // save/load object
   
  enum { SaveLoadLen = 4 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(address);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(address);
   }
  
  // print object
  
  template <class P>
  void print(P &out) const
   {
    SaveLoadBe32 temp(address);
   
    Printf(out,"#;.#;.#;.#;",temp.buf[0],temp.buf[1],temp.buf[2],temp.buf[3]);
   }
 };
 
template <class Dev>
void ParseIPAddress(Dev &dev,IPAddress &ret)
 {
  uint8 b0,b1,b2,b3;
  
  ParseUInt(dev,b0);
  ParseChar(dev,'.');
  ParseUInt(dev,b1);
  ParseChar(dev,'.');
  ParseUInt(dev,b2);
  ParseChar(dev,'.');
  ParseUInt(dev,b3);
  
  if( !dev ) return;
  
  ret=IPAddress(b0,b1,b2,b3);
 }
 
/* struct EthHeader */ 

struct EthHeader
 {
  MACAddress dst;
  MACAddress src;
  EthType type;
  
  // constructors
  
  EthHeader() : dst(),src(),type() {}
  
  EthHeader(MACAddress src_,MACAddress dst_,EthType type_) : dst(dst_),src(src_),type(type_) {}
  
  // save/load object
  
  enum { SaveLoadLen = 14 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev(dst,src,type);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev(dst,src,type);
   }
  
  // print object
   
  struct PrintOptType
   {
    static const bool Default_inbound = false ;
    
    bool inbound;
   
    void setDefault() { inbound=Default_inbound; }
    
    PrintOptType() { setDefault(); }
    
    PrintOptType(const char *ptr,const char *lim);
    
    //
    // [i|o|I|O]
    //
    
    template <class Dev>
    static void ParseInbound(Dev &dev,bool &inbound)
     {
      typename Dev::Peek peek(dev);
  
      if( !peek )
        {
         inbound=Default_inbound;
        }
      else
        {
         switch( *peek )
           {
            case 'i' : case 'I' : inbound=true;  ++dev; break;
            case 'o' : case 'O' : inbound=false; ++dev; break;
            
            default: inbound=Default_inbound;
           }
        }
     }   
   }; 
   
  template <class P>
  void print(P &out,PrintOptType opt) const
   {
    if( opt.inbound )
      Printf(out,"#; <- #; #;",dst,src,type);
    else
      Printf(out,"#; -> #; #;",src,dst,type);
   }
 };
 
/* struct CheckSum */  
 
struct CheckSum 
 {
  uint32 word_sum;
  
  // constructors
  
  CheckSum() : word_sum(0) {}
  
  // add
  
  void add(uint8 hi_,uint8 lo)
   {
    uint16 hi=hi_;
    
    word_sum+=((hi<<8)|lo);
   }
   
  void add(uint16 word) 
   {
    word_sum+=word;
   }
   
  void add(uint32 dword) 
   {
    word_sum+=uint16(dword>>16)+uint16(dword);
   }
   
  void add(PtrLen<const uint8> data);
  
  // (TT)
   
  void operator () () {}
  
  template <class ... TT> 
  void operator () (uint8 b0,uint8 b1,TT... tt)
   {
    add(b0,b1);
    
    (*this)(tt...);
   }
   
  template <class ... TT> 
  void operator () (uint16 word,TT... tt)
   {
    add(word);
    
    (*this)(tt...);
   }
   
  template <class ... TT> 
  void operator () (uint32 dword,TT... tt)
   {
    add(dword);
    
    (*this)(tt...);
   }
  
  // complete 
   
  uint16 complete() const
   {
    uint32 sum=word_sum;
   
    sum=(sum>>16)+(sum&0xFFFF);
    sum=(sum>>16)+(sum&0xFFFF);

    sum=sum^0xFFFF;

    if( sum==0 ) sum=0xFFFF;

    return (uint16)sum;
   }
   
  bool test() const { return complete()==0xFFFF; }
 };
 
/* struct IPHeader */  

struct IPHeader
 {
  // consts
  
  static const uint8  DefaultVHL         = 0x45 ;
  static const uint8  DefaultTOS         = 0    ;
  static const uint16 DefaultFlagsOffset = 0    ;
  static const uint8  DefaultTTL         = 128  ;
  
  static const uint16 Flag_DF    = 1u<<14     ; // don't fragment
  static const uint16 Flag_MF    = 1u<<13     ; // more fragments
  static const uint16 OffsetMask = (1u<<13)-1 ;
  
  // data
 
  uint8 vhl; // default
  uint8 tos; // default
  IPLen len;
  uint16 id;
  
  uint16 flags_offset; // default
  uint8  ttl;          // default
  IProto proto;
  uint16 check_sum;
  
  IPAddress src;
  IPAddress dst;
  
  // constructors
  
  IPHeader()
   : len(),
     proto(),
     src(),
     dst()
   {
    setDefault();
    
    id=0;
    
    check_sum=0;
   }
    
  IPHeader(IPAddress src_,IPAddress dst_,IProto proto_,IPLen len_)
   : len(len_),
     proto(proto_),
     src(src_),
     dst(dst_)
   {
    setDefault();
    
    setId();
    
    setCheckSum();
   }
   
  // methods
  
  void setDefault()
   {
    vhl=DefaultVHL;
    tos=DefaultTOS;
    flags_offset=DefaultFlagsOffset;
    ttl=DefaultTTL;
   }
   
  static uint16 GetId(); 
   
  void setId() { id=GetId(); }
   
  void setCheckSum(); 
  
  bool testCheckSum() const;
  
  bool isFragment() const { return flags_offset&(Flag_MF|OffsetMask); }
  
  // save/load object
 
  enum { SaveLoadLen = 20 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(vhl,tos,len,id,flags_offset,ttl,proto,check_sum,src,dst);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(vhl,tos,len,id,flags_offset,ttl,proto,check_sum,src,dst);
   }
  
  // print object
   
  struct PrintOptType
   {
    static const bool Default_inbound = false ;
    static const bool Default_extra = false ;
    
    bool inbound;
    bool extra;
   
    void setDefault() { inbound=Default_inbound; extra=Default_extra; }
    
    PrintOptType() { setDefault(); }
    
    PrintOptType(const char *ptr,const char *lim);
    
    //
    // [i|o|I|O][x|X]
    //
    
    template <class Dev>
    static void ParseInbound(Dev &dev,bool &inbound)
     {
      typename Dev::Peek peek(dev);
  
      if( !peek )
        {
         inbound=Default_inbound;
        }
      else
        {
         switch( *peek )
           {
            case 'i' : case 'I' : inbound=true;  ++dev; break;
            case 'o' : case 'O' : inbound=false; ++dev; break;
            
            default: inbound=Default_inbound;
           }
        }
     }   
     
    template <class Dev>
    void ParseExtra(Dev &dev,bool &extra)
     {
      typename Dev::Peek peek(dev);
  
      if( !peek )
        {
         extra=Default_extra;
        }
      else
        {
         switch( *peek )
           {
            case 'x' : case 'X' : extra=true; ++dev; break;
            
            default: extra=Default_extra;
           }
        }
     }   
   }; 
   
  template <class P>
  void print(P &out,PrintOptType opt) const
   {
    if( opt.inbound )
      Printf(out,"#; <- #; #; len=#;",dst,src,proto,len);
    else
      Printf(out,"#; -> #; #; len=#;",src,dst,proto,len);
      
    if( opt.extra )  
      {
       if( vhl!=DefaultVHL ) Printf(out," vhl=#.h;",vhl);
      
       if( flags_offset&Flag_DF ) Putobj(out," DF");
            
       if( isFragment() )
         {
          uint16 offset=flags_offset&OffsetMask;  
            
          if( flags_offset&Flag_MF )
            Printf(out," cont(id=#.h;,off=#;)",id,offset);
          else
            Printf(out," last(id=#.h;,off=#;)",id,offset);
         }
         
       if( !testCheckSum() ) Putobj(out," bad checksum"); 
      }
   }
 };
 
/* struct ARPacket */  

struct ARPacket
 {
  // consts
  
  static const uint16 DefaultMACType = 1                       ;
  static const uint16 DefaultIPType  = Eth_IP                  ;
  static const uint8  DefaultMACLen  = MACAddress::SaveLoadLen ;
  static const uint8  DefaultIPLen   = IPAddress::SaveLoadLen  ;
  
  // data
 
  uint16 mac_type; // default
  uint16 ip_type;  // default
  uint8  mac_len;  // default
  uint8  ip_len;   // default
  
  ARPType type;

  MACAddress src_mac;
  IPAddress  src_ip;
  MACAddress dst_mac;
  IPAddress  dst_ip;
  
  // constructors
  
  ARPacket() 
   : type(),
     src_mac(),
     src_ip(),
     dst_mac(),
     dst_ip()
   { 
    setDefault(); 
   }
  
  ARPacket(ARPType type_,MACAddress src_mac_,IPAddress src_ip_,MACAddress dst_mac_,IPAddress dst_ip_)
   : type(type_),
     src_mac(src_mac_),
     src_ip(src_ip_),
     dst_mac(dst_mac_),
     dst_ip(dst_ip_)
   {
    setDefault();
   }
  
  // methods
  
  void setDefault()
   {
    mac_type=DefaultMACType;
    ip_type=DefaultIPType;
    mac_len=DefaultMACLen;
    ip_len=DefaultIPLen;
   }
  
  bool testDefault() const
   {
    return mac_type==DefaultMACType && 
           ip_type==DefaultIPType && 
           mac_len==DefaultMACLen && 
           ip_len==DefaultIPLen ;
   }
  
  // save/load object
  
  enum { SaveLoadLen = 28 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(mac_type,ip_type,mac_len,ip_len,type,src_mac,src_ip,dst_mac,dst_ip);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(mac_type,ip_type,mac_len,ip_len,type,src_mac,src_ip,dst_mac,dst_ip);
   }
 };
 
/* struct ICMPEcho */ 

struct ICMPEcho 
 {
  ICMPEchoType type;
  uint8 code;
  uint16 check_sum;
  uint16 id;
  uint16 num;
  
  // constructors
  
  ICMPEcho()
   : type(),
     code(),
     id(),
     num()
   {
    check_sum=0;
   }
  
  ICMPEcho(ICMPEchoType type_,uint16 id_,uint16 num_)
   : type(type_),
     code(),
     id(id_),
     num(num_)
   {
    check_sum=0;
   }
  
  // methods
  
  void setCheckSum(PtrLen<const uint8> data);
  
  bool testCheckSum(PtrLen<const uint8> data) const;
  
  // save/load object
  
  enum { SaveLoadLen = 8 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(type,code,check_sum,id,num);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(type,code,check_sum,id,num);
   }
   
  // print object
  
  template <class P> 
  void print(P &out) const
   {
    if( code )
      Printf(out,"#; code=#; id=#; num=#;",type,code,id,num);
    else  
      Printf(out,"#; id=#; num=#;",type,id,num);
   }
 };
 
/* struct UDPHeader */ 

struct UDPHeader 
 {
  UDPort src_port;
  UDPort dst_port;
  IPLen len;
  uint16 check_sum;
  
  // constructors
  
  UDPHeader()
   : src_port(),
     dst_port(),
     len()
   {
    check_sum=0;
   }
   
  UDPHeader(UDPort src_port_,UDPort dst_port_,IPLen len_)
   : src_port(src_port_),
     dst_port(dst_port_),
     len(len_)
   {
    check_sum=0;
   }
  
  // methods
  
  void setCheckSum(IPAddress src,IPAddress dst,IPLen len,PtrLen<const uint8> data);
  
  bool testCheckSum(IPAddress src,IPAddress dst,IPLen len,PtrLen<const uint8> data) const;
  
  // save/load object
  
  enum { SaveLoadLen = 8 };
 
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(src_port,dst_port,len,check_sum);
   }
   
  template <class Dev> 
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(src_port,dst_port,len,check_sum);
   }
 };
 
} // namespace Net
} // namespace CCore
 
#endif
 


