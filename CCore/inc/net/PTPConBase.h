/* PTPConBase.h */ 
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

#ifndef CCore_inc_net_PTPConBase_h
#define CCore_inc_net_PTPConBase_h

#include <CCore/inc/net/PTPExtra.h>
 
namespace CCore {
namespace Net {
namespace PTPCon {

/* using */ 

using namespace PTP;

/* consts */ 

const ulen MaxNameLen      =  128 ;
const ulen DeltaReadLen    =   20 ;
const ulen MaxReadDataLen  = 1420 ;
const ulen DeltaWriteLen   =   36 ;
const ulen MaxWriteDataLen = 1404 ;

const ServiceIdType ServiceId = 3 ;
   
const FunctionIdType FunctionId_Open  = 1 ;
const FunctionIdType FunctionId_Read  = 2 ;
const FunctionIdType FunctionId_Write = 3 ;
const FunctionIdType FunctionId_Close = 4 ;

enum Trigger
 {
  TriggerNone,
  TriggerDefault, // \r \n \t \b
  TriggerAll
 };

/* classes */ 

struct ConId;

struct TriggerMask;

struct OpenInput;
struct OpenOutput;

struct ReadInput;
struct ReadOutput;

struct WriteInput;
typedef Empty WriteOutput;

struct CloseInput;
typedef Empty CloseOutput;

/* struct ConId */ 

struct ConId
 {
  uint32 slot;
  uint64 number;
  uint64 clock;
  
  // constructors

  ConId() : slot(),number(),clock() {}
  
  // methods
  
  friend bool operator == (const ConId &a,const ConId &b)
   { 
    return a.slot==b.slot && a.number==b.number && a.clock==b.clock ;
   }
  
  friend bool operator != (const ConId &a,const ConId &b) { return !(a==b); }
  
  // save/load object
   
  enum { SaveLoadLen = SaveLenCounter<uint32,uint64,uint64>::SaveLoadLen };
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(slot,number,clock);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(slot,number,clock);
   }
 };
 
/* struct TriggerMask */ 

struct TriggerMask
 {
  uint32 mask[8];
  
  // constructors
  
  TriggerMask() : mask() {}
  
  explicit TriggerMask(const char *zstr) : mask() { set(zstr); }
  
  explicit TriggerMask(Trigger t)
   {
    switch( t )
      {
       default:
       case TriggerNone : setNone(); break;
        
       case TriggerDefault : setDefault(); break;
        
       case TriggerAll : setAll(); break;
      }
   }
  
  // methods
  
  void setNone() { Range(mask).set_null(); }
  
  void setDefault() { setNone(); set("\r\n\t\b"); }
  
  void setAll() { Range(mask).set(uint32(UIntMax())); }
  
  void set(uint8 ch) { mask[ch>>5] |= (uint32(1)<<(ch&31)) ; }
  
  void set(const char *zstr)
   {
    for(; char ch=*zstr ;zstr++) set((uint8)ch);
   }
  
  uint32 test(uint8 ch) const { return mask[ch>>5] & (uint32(1)<<(ch&31)) ; }
  
  // save/load object
  
  enum { SaveLoadLen = 8*SaveLenCounter<uint32>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    SaveRange_use<BeOrder>(Range(mask),dev);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    LoadRange_use<BeOrder>(Range(mask),dev);
   }
 };
 
/* struct OpenInput */  
 
struct OpenInput // + uint8 name[len];
 {
  static const ulen MaxLen = MaxNameLen ;
 
  uint32 write_timeout_msec;
  uint32 read_timeout_msec;
  TriggerMask trigger_mask;
  LenType len;
  
  // constructors

  OpenInput() : write_timeout_msec(),read_timeout_msec(),trigger_mask(),len() {}
  
  OpenInput(uint32 write_timeout_msec_,
            uint32 read_timeout_msec_,
            const TriggerMask &trigger_mask_,
            LenType len_)
   : write_timeout_msec(write_timeout_msec_),
     read_timeout_msec(read_timeout_msec_),
     trigger_mask(trigger_mask_),
     len(len_) 
   {
   }
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<uint32,uint32,TriggerMask,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(write_timeout_msec,read_timeout_msec,trigger_mask,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(write_timeout_msec,read_timeout_msec,trigger_mask,len);
   }
 };
 
/* struct OpenOutput */ 

struct OpenOutput
 {
  ConId con_id;
  
  // constructors

  OpenOutput() : con_id() {}
  
  explicit OpenOutput(const ConId &con_id_) : con_id(con_id_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<ConId>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(con_id);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(con_id);
   }
 };
 
/* struct ReadInput */ 

struct ReadInput
 {
  ConId con_id;
  uint32 number;
  LenType len;
  
  // constructors

  ReadInput() : con_id(),number(),len() {}
  
  ReadInput(const ConId &con_id_,uint32 number_,LenType len_) : con_id(con_id_),number(number_),len(len_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<ConId,uint32,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(con_id,number,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(con_id,number,len);
   }
 };
 
/* struct ReadOutput */ 

struct ReadOutput // + uint8 data[len];
 {
  static const ulen MaxLen = MaxReadDataLen ;

  uint32 number;
  LenType len;
  
  // constructors

  ReadOutput() : number(),len() {}
  
  ReadOutput(uint32 number_,LenType len_) : number(number_),len(len_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<uint32,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(number,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(number,len);
   }
 };
 
/* struct WriteInput */ 

struct WriteInput // + uint8 data[len];
 {
  static const ulen MaxLen = MaxWriteDataLen ;
  
  ConId con_id;
  uint32 number;
  LenType len;
  
  // constructors

  WriteInput() : con_id(),number(),len() {}
  
  WriteInput(const ConId &con_id_,uint32 number_,LenType len_) : con_id(con_id_),number(number_),len(len_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<ConId,uint32,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(con_id,number,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(con_id,number,len);
   }
 };
 
/* struct CloseInput */ 

struct CloseInput
 {
  ConId con_id;
  
  // constructors

  CloseInput() : con_id() {}
  
  explicit CloseInput(const ConId &con_id_) : con_id(con_id_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<ConId>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(con_id);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(con_id);
   }
 };
 
} // namespace PTPCon
} // namespace Net
} // namespace CCore
 
#endif
 

