/* DevPCIHost.h */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: Target/IXDP465
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevPCIHost_h
#define CCore_inc_dev_DevPCIHost_h

#include <CCore/inc/pci/PCIBusRW.h>

namespace CCore {
namespace Dev {
namespace PCIBus {

/* classes */ 

struct DeviceInfoExt;

class BusEnum;

class HostInitExit;

/* struct DeviceInfoExt */ 

struct DeviceInfoExt : DeviceInfo
 {
  // info
  
  uint32 vendor_id;
  uint32 device_id;
  uint32 revision_id;
     
  uint32 base_class;
  uint32 sub_class;
  uint32 if_class;
  
  uint32 subsystem_vendor_id;
  uint32 subsystem_id;
  
  uint32 int_pin; // 0 -- none, 1:4 -- IntA:IntD 
  uint32 msi_address;
  uint32 msi_bits;
  
  bool is_type0;
  bool is_supported;
  
  // enum bus
  
  static bool IsSupported(BarType type);
  
  void init(DeviceId id);
     
  void setBars();
     
  void setHostBase(AddressMap address_map);
  
  void disable();
      
  template <class P>
  void print(P &out) const
   {
    Printf(out,"PCISlot #;:#; vendor_id=#4.16i; device_id=#4.16i; revision_id=#2.16i;\n",id.slot,id.function,vendor_id,device_id,revision_id);
       
    Printf(out,"class=#2.16i;.#2.16i;.#2.16i;\n",base_class,sub_class,if_class);
       
    if( is_supported )
      {
       Printf(out,"subsystem vendor_id=#4.16i; id=#4.16i;\n",subsystem_vendor_id,subsystem_id);
          
       if( int_pin )
         {
          if( int_pin<=4 )
            Printf(out,"int_pin=Int#.c;\n",int_pin[" ABCD"]);
          else
            Printf(out,"int_pin=#;\n",int_pin);
         }
          
       if( msi_address )
         {
          Printf(out,"msi address=#2.16i msi_bits=#;\n",msi_address,msi_bits);
         } 
          
       for(ulen i=0; i<MaxDeviceBars ;i++) 
         {
          Printf(out,"bar[#;] #;\n",i,bars[i]);
         }
      }
    else
      {
       Printf(out,"unsupported type\n");
      } 
   }
 };
 
/* class BusEnum */ 

class BusEnum : NoCopy
 {
   DeviceInfoExt table[DeviceId::SlotLim*DeviceId::FunctionLim];
   ulen len;
   
  public: 
  
   BusEnum() : len(0) {}
   
   const DeviceInfoExt * getPtr() const { return table; }
   
   ulen getLen() const { return len; } 
   
   void scan(); 

   void assignMem(BusAddressType pci_base,BusAddressType pci_len);
   
   void setBars();
   
   void setHostBase(BusAddressType pci_base,AddressType host_base);
   
   void disable();
   
   template <class P>
   void print(P &out) const
    {
     Printf(out,"\n#;\n\n",Title("PCI bus"));
     
     for(ulen i=0; i<len ;i++)
       {
        Printf(out,"#;\n#;\n\n",table[i],TextDivider());
       } 
    };
 };
 
/* class HostInitExit : NOT LOCKED */ 

class HostInitExit : NoCopy
 {
   BusEnum bus_enum;
   
  public:
  
   HostInitExit();
   
   ~HostInitExit();
   
   const DeviceInfo * find(uint32 vendor_id,uint32 device_id) const;
   
   ulen find(uint32 vendor_id,uint32 device_id,PtrLen<const DeviceInfo *> buf) const;
   
   AddressMap getAddressMap() const;
   
   template <class P>
   void print(P &out) const
    {
     Putobj(out,bus_enum);
    }
 };
 
} // namespace PCIBus
} // namespace Dev
} // namespace CCore

#endif 
 
 

