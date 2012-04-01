/* PTPBootBase.h */ 
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

#ifndef CCore_inc_net_PTPBootBase_h
#define CCore_inc_net_PTPBootBase_h
 
#include <CCore/inc/net/PTPExtra.h>

namespace CCore {
namespace Net {
namespace PTPBoot {

/* using */ 

using namespace PTP;

/* consts */ 

const ulen DeltaWriteLen   =   24 ;
const ulen MaxWriteDataLen = 1416 ; // MaxInfoLen-DeltaWriteLen

const ServiceIdType ServiceId = 4 ;
   
const FunctionIdType FunctionId_Alloc = 1 ;
const FunctionIdType FunctionId_Write = 2 ;
const FunctionIdType FunctionId_Boot  = 3 ;

/* types */ 
   
typedef uint64 AddressType;

typedef uint32 IndexType;

/* classes */ 

struct AllocInput;
struct AllocOutput;

struct WriteInput;
typedef Empty WriteOutput;   

struct BootInput;
typedef Empty BootOutput;   

/* struct AllocInput */ 

struct AllocInput
 {
  AddressType address;
  AddressType len;
  
  // constructors
  
  AllocInput() : address(),len() {}
  
  AllocInput(AddressType address_,AddressType len_) : address(address_),len(len_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<AddressType,AddressType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(address,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(address,len);
   }
 };
    
/* struct AllocOutput */ 
    
struct AllocOutput
 {
  IndexType index;
  
  // constructors
  
  AllocOutput() : index() {}
  
  explicit AllocOutput(IndexType index_) : index(index_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<IndexType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(index);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(index);
   }
 }; 
 
/* struct WriteInput */ 
 
struct WriteInput // + uint8 data[len];
 {
  static const ulen MaxLen = MaxWriteDataLen ;
 
  IndexType index;
  AddressType off;
  LenType len;
  
  // constructors
  
  WriteInput() : index(),off(),len() {}
  
  WriteInput(IndexType index_,AddressType off_,LenType len_) : index(index_),off(off_),len(len_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<IndexType,AddressType,LenType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(index,off,len);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(index,off,len);
   }
 };
 
/* struct BootInput */ 
 
struct BootInput
 {
  AddressType entry_point;
  FlagType flags;
  
  // constructors
  
  BootInput() : entry_point(),flags() {}
  
  BootInput(AddressType entry_point_,FlagType flags_) : entry_point(entry_point_),flags(flags_) {}
  
  // save/load object
  
  enum { SaveLoadLen = SaveLenCounter<AddressType,FlagType>::SaveLoadLen }; 
  
  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(entry_point,flags);
   }
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<BeOrder>(entry_point,flags);
   }
 };
    
} // namespace PTPBoot
} // namespace Net
} // namespace CCore
 
#endif
 

