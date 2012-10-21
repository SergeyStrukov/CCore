/* VIA_Rhine_III.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/driver/VIA_Rhine_III.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/SpecialMemBase.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PacketPool.h>

namespace Driver {
namespace VIA_Rhine_III {

/* enum IntEvent */ 

const char * GetTextDesc(IntEvent ev)
 {
  static const char *const Table[]=
   {
    "SRC",    //  IntSRC
    "RX+GEN", //  IntRX
    "TX+GEN", //  IntTX
    "GEN",    //  IntGEN
    "Other",  //  IntOther
    
    ""
   };
 
  return Table[ev];
 }
 
/* class DeviceControl */ 

DeviceControl::DeviceControl(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map_)
 : connector(info.id),
 
   address_map(address_map_),
   
   cfg(info.id),
   
   cfg_reg(cfg),
   pci_reg(cfg),
   dev_reg(info.bars[1].host_base)
 {
 }
  
DeviceControl::~DeviceControl()
 {
 }
 
void DeviceControl::enable_pci()
 {
  cfg_reg.null_StatusCommand()
         .setbit(PCIBus::StatusCommand_IOEnable
                |PCIBus::StatusCommand_MemEnable)
         .setTo(cfg_reg);
 }
 
void DeviceControl::mode_pci()
 {
  pci_reg.get_PCIMode2()
         .setbit(PCIMode2_T10|PCIMode2_PCEROPT)
         .setTo(pci_reg);
         
  pci_reg.get_PCIMode3()
         .setbit(PCIMode3_MIION)       
         .setTo(pci_reg);
 }
 
void DeviceControl::enable_pci_busmaster()
 {
  cfg_reg.null_StatusCommand()
         .setbit(PCIBus::StatusCommand_IOEnable
                |PCIBus::StatusCommand_MemEnable
                |PCIBus::StatusCommand_BusMasterEnable)
         .setTo(cfg_reg);
 }
 
void DeviceControl::stop_pci()
 {
  cfg_reg.null_StatusCommand()
         .setTo(cfg_reg);
 }
 
void DeviceControl::init_int()
 {
  dev_reg.ones_ISR()
         .setTo(dev_reg);
  
  dev_reg.ones_MISR()
         .clearbit(MISR_UDPSET)
         .setTo(dev_reg);
 }
 
void DeviceControl::enable_int()
 {
  dev_reg.ones_ISR()
         .set(dev_reg.to_IMR());
  
  dev_reg.null_MIMR()
         .setbit(MIMR_TM0|MIMR_TM1)
         .setTo(dev_reg);
 }
 
void DeviceControl::enable_rtx_int()
 {
  dev_reg.get_IMR()
         .setbit(ISR_PRX|ISR_PTX)
         .set(dev_reg.to_IMR());
 }
 
void DeviceControl::disable_int()
 {
  dev_reg.null_ISR()
         .set(dev_reg.to_IMR());
  
  dev_reg.null_MIMR()
         .setTo(dev_reg);
 }
 
auto DeviceControl::get_int() -> IntStatus 
 {
  Type_ISR isr=dev_reg.get_ISR();

  Type_MISR misr=dev_reg.get_MISR();        
  
  return IntStatus(isr,misr);
 }
 
auto DeviceControl::clear_int() -> IntStatus
 {
  Type_ISR isr=dev_reg.get_ISR().setTo(dev_reg);

  Type_MISR misr=dev_reg.get_MISR().setTo(dev_reg);        
  
  connector.clear();
  
  return IntStatus(isr,misr);
 }
 
void DeviceControl::delay_int(Type_ISR isr)
 {
  if( isr.maskbit(ISR_PRX|ISR_PTX) )
    {
     dev_reg.get_IMR()
            .clearbit(ISR_PRX|ISR_PTX)
            .set(dev_reg.to_IMR());
  
     dev_reg.get_MiscCR()
            .setbit(MiscCR_T0US)
            .setTo(dev_reg);
    
     dev_reg.set_SoftT0(1000); // 1 ms, 1 kHz
     
     dev_reg.get_MiscCR()
            .setbit(MiscCR_T0EN)
            .clearbit(MiscCR_T0SUSPEND)
            .setTo(dev_reg);
    }
 }
 
void DeviceControl::setup_int_handler(Function<void (void)> handle_int)
 {
  connector.setup(handle_int);
 }
 
void DeviceControl::cleanup_int_handler()
 {
  connector.cleanup();
 }
 
void DeviceControl::enable_txpoll()
 {
  dev_reg.get_CR()
         .setbit(CR_TDMD1|CR_TXON)
         .setTo(dev_reg);
 }
 
void DeviceControl::enable_mmio()
 {
  dev_reg.get_CFG()
         .setbit(CFG_GPIOEN)
         .setTo(dev_reg);
 }
 
void DeviceControl::reload_eeprom()
 {
  dev_reg.get_EECSR()
         .setbit(EECSR_AUTOLD)
         .setTo(dev_reg);

  for(MSecTimer timer; dev_reg.get_EECSR().maskbit(EECSR_AUTOLD) ;) 
    if( timer.exceed(ResetWait) )
      {
       Abort("Driver::VIA_Rhine_III::DeviceControl::reload_eeprom() timeout");
      }
 }
 
void DeviceControl::set_tx_threshold(Field_TCR_RTFT value)
 {
  dev_reg.get_BCR()
         .set_CTFT(value) 
         .setTo(dev_reg);
         
  dev_reg.get_TCR()
         .set_RTFT(value)
         .setTo(dev_reg);
 }
 
void DeviceControl::set_rx_threshold(Field_RCR_RRFT value)
 {
  dev_reg.get_BCR()
         .set_CRFT(value)
         .setTo(dev_reg);
  
  dev_reg.get_RCR()
         .set_RRFT(value)
         .setTo(dev_reg);
 }
 
void DeviceControl::set_dma_length(Field_BCR_DMAL value)
 {
  dev_reg.get_BCR()
         .set_DMAL(value)
         .setTo(dev_reg);
 }

void DeviceControl::soft_reset()
 {
  dev_reg.get_CR()
         .setbit(CR_RESET)
         .setTo(dev_reg);
         
  for(MSecTimer timer; dev_reg.get_CR().maskbit(CR_RESET) ;)
    if( timer.exceed(ResetWait) )
      {
       Abort("Driver::VIA_Rhine_III::DeviceControl::soft_reset() timeout");
      }
 }
 
void DeviceControl::wol_reset()
 {
  dev_reg.get_StickHW()
         .clearbit(StickHW_DS0_SHADOW|StickHW_DS1_SHADOW)
         .setTo(dev_reg);

  dev_reg.null_WOLCFG()
         .setbit(WOLCFG_PME_OVR)
         .set(dev_reg.to_WOLCFG_CLR());

  dev_reg.ones_WOLCR()
         .set(dev_reg.to_WOLCR_CLR());
  
  dev_reg.null_TEST()
         .setbit(TEST_SNORMAL|TEST_SMACTEST)
         .set(dev_reg.to_TEST_CLR());
  
  dev_reg.set_PWRCSR_CLR(0x03FF); // no description
 }
 
void DeviceControl::enable_duplex()
 {
  dev_reg.get_CR()
         .setbit(CR_FDX)
         .setTo(dev_reg);
         
  dev_reg.null_WOLCFG()
         .setbit(WOLCFG_SFDX)
         .set(dev_reg.to_WOLCFG_SET());
 }
 
void DeviceControl::disable_duplex()
 {
  dev_reg.get_CR()
         .clearbit(CR_FDX)
         .setTo(dev_reg);
         
  dev_reg.null_WOLCFG()
         .setbit(WOLCFG_SFDX)
         .set(dev_reg.to_WOLCFG_CLR());
 }
 
LinkStatus DeviceControl::check_link()
 {
  auto status=dev_reg.get_MIISR();
  
  if( status.maskbit(MIISR_NOLINK) )
    {
     disable_duplex();
     
     return LinkStatus_NoLink;
    }
  else
    {
     LinkStatus ret;
    
     if( status.maskbit(MIISR_SPEED10) )
       ret=LinkStatus_Speed10;
     else 
       ret=0;  
    
     if( status.maskbit(MIISR_FDX) )
       {
        ret|=LinkStatus_Duplex;
        
        enable_duplex();
       }
     else
       {
        disable_duplex();
       }  
       
     return ret;  
    }
 }
 
void DeviceControl::set_promiscuous()
 {
  dev_reg.set_MAR(0,0xFFFFFFFF);
  dev_reg.set_MAR(1,0xFFFFFFFF);
  
  dev_reg.get_RCR()
         .setbit(RCR_AM|RCR_AB|RCR_PROM)
         .setTo(dev_reg);
 }
 
void DeviceControl::set_all_multicast()
 {
  dev_reg.set_MAR(0,0xFFFFFFFF);
  dev_reg.set_MAR(1,0xFFFFFFFF);
  
  dev_reg.get_RCR()
         .setbit(RCR_AM|RCR_AB)
         .setTo(dev_reg);
 }
 
void DeviceControl::enable_promiscuous()
 {
  dev_reg.get_RCR()
         .setbit(RCR_PROM)
         .setTo(dev_reg);
 }
 
void DeviceControl::disable_promiscuous()
 {
  dev_reg.get_RCR()
         .clearbit(RCR_PROM)
         .setTo(dev_reg);
 }
 
MACAddress DeviceControl::get_MAC()
 {
  return MACAddress(dev_reg.get_MAC(0),
                    dev_reg.get_MAC(1),
                    dev_reg.get_MAC(2),
                    dev_reg.get_MAC(3),
                    dev_reg.get_MAC(4),
                    dev_reg.get_MAC(5));
 }
 
void DeviceControl::cfg_device()
 {
  dev_reg.get_CFG()
         .clearbit(CFG_LED0S0|CFG_QPKTDIS|CFG_MBA|CFG_CAP|CFG_CRADOM|CFG_BAKOPT)
         .setTo(dev_reg);

  dev_reg.null_WOLCFG()
         .setbit(WOLCFG_SAM|WOLCFG_SAB)
         .set(dev_reg.to_WOLCFG_SET());

  dev_reg.get_TCR()
         .setbit(TCR_OFSET)
         .setTo(dev_reg);
 }
 
void DeviceControl::start_device(LinkStatus link_status)
 {
  dev_reg.null_CR()
         .setbit(CR_START|CR_RXON|CR_TXON|CR_DPOLL|CR_TDMD1)
         .setbitIf( (link_status&LinkStatus_Duplex) ,CR_FDX)
         .setTo(dev_reg);
 }
 
void DeviceControl::stop_device()
 {
  dev_reg.null_CR()
         .setbit(CR_STOP)
         .setTo(dev_reg);
 }
 
void DeviceControl::init_flow_control()
 {
  dev_reg.null_FLOWCR1()
         .setbit(FLOWCR1_XONEN|FLOWCR1_XHITH1|FLOWCR1_XLTH1|FLOWCR1_XLTH0)
         .setTo(dev_reg);
  
  dev_reg.set_PauseTimer(0xFFFF);
 }
 
void DeviceControl::flow_control(unsigned rx_done)
 {
  dev_reg.set_FLOWCR0(rx_done);
 }

void DeviceControl::mii_disable_auto_poll()
 {
  dev_reg.null_MIICR()
         .setTo(dev_reg);
         
  for(ClockTimer timer; dev_reg.get_MIIAD().maskbit(MIIAD_MIDLE)==0 ;)
    if( timer.exceed(Sys::USecToClock(MIIWait)) )
      Abort("Driver::VIA_Rhine_III::DeviceControl::mii_disable_auto_poll() timeout");
 }
 
void DeviceControl::mii_enable_auto_poll()
 {
  dev_reg.null_MIICR()
         .setTo(dev_reg);
         
  dev_reg.null_MIIAD()
         .setbit(MIIAD_MSRCEN|MIIAD_MAD0)
         .setTo(dev_reg);
         
  dev_reg.null_MIICR()
         .setbit(MIICR_MAUTO)
         .setTo(dev_reg);
         
#if 0
  
  for(ClockTimer timer; dev_reg.get_MIIAD().maskbit(MIIAD_MDONE)==0 ;)
     if( timer.exceed(Sys::USecToClock(MIIWait)) )
       Abort("Driver::VIA_Rhine_III::DeviceControl::mii_enable_auto_poll() timeout");
    
#endif    
  
  dev_reg.get_MIIAD()
         .setbit(MIIAD_MSRCEN)
         .setTo(dev_reg);
 } 
 
uint16 DeviceControl::mii_read(uint8 address)
 {
  Type_MIIAD(address).setTo(dev_reg);

  dev_reg.get_MIICR()
         .setbit(MIICR_RCMD)
         .setTo(dev_reg);
  
  for(ClockTimer timer; dev_reg.get_MIICR().maskbit(MIICR_RCMD) ;)
    if( timer.exceed(Sys::USecToClock(MIIWait)) )
      Abort("Driver::VIA_Rhine_III::DeviceControl::mii_read() timeout");
  
  return dev_reg.get_MIIDATA();
 }
 
void DeviceControl::mii_write(uint8 address,uint16 value) 
 {
  Type_MIIAD(address).setTo(dev_reg);

  dev_reg.set_MIIDATA(value);
  
  dev_reg.get_MIICR()
         .setbit(MIICR_WCMD)
         .setTo(dev_reg);
  
  for(ClockTimer timer; dev_reg.get_MIICR().maskbit(MIICR_WCMD) ;)
    if( timer.exceed(Sys::USecToClock(MIIWait)) )
      Abort("Driver::VIA_Rhine_III::DeviceControl::mii_write() timeout");
 }
 
class DeviceControl::MIIRW
 {
   DeviceControl &dc;
   
  public:
  
   explicit MIIRW(DeviceControl &dc_) : dc(dc_) { dc.mii_disable_auto_poll(); }
   
   ~MIIRW() { dc.mii_enable_auto_poll(); }
   
   typedef uint8 AddressType;
   
   template <class UInt>
   UInt get(AddressType address);
   
   template <class UInt>
   void set(AddressType address,UInt data);
 };                        
 
template <>
inline uint16 DeviceControl::MIIRW::get<uint16>(AddressType address) { return dc.mii_read(address); }
 
template <>
inline void DeviceControl::MIIRW::set<uint16>(AddressType address,uint16 data) { return dc.mii_write(address,data); }
 
class DeviceControl::MII : NoCopy
 {
   MIIRegBar<MIIRW> reg;
 
  public:
  
   explicit MII(DeviceControl &dc) : reg(dc) {}
   
   ~MII() {}
   
   Type_MIIANAR get_MIIANAR() { return reg.get_MIIANAR(); }
   
   Type_MIIANLPAR get_MIIANLPAR() { return reg.get_MIIANLPAR(); }
   
   void set_auto_on()
    {
     reg.get_MIIModCfg()
        .clearbit(MIIModCfg_Bit0)
        .setTo(reg);
      
     reg.get_MIIBMCR()
        .setbit(MIIBMCR_AUTO|MIIBMCR_REAUTO)
        .setTo(reg);    
    }
    
   void set_auto_off()
    {
     reg.get_MIIModCfg()
        .setbit(MIIModCfg_Bit0)
        .setTo(reg);

     reg.get_MIIBMCR()
        .clearbit(MIIBMCR_AUTO)
        .setTo(reg);    
    }
    
   void set_mode()
    {
     reg.get_MIIANAR()
        .setbit(MIIANAR_T10|MIIANAR_T10FD|MIIANAR_TX|MIIANAR_TXFD)
        .setTo(reg);
     
     set_auto_on();
    }
 };
 
void DeviceControl::mii_set_auto_on()
 {
  MII mii(*this);

  mii.set_auto_on();
 }
 
void DeviceControl::mii_set_auto_off()
 {
  MII mii(*this);

  mii.set_auto_off();
 } 
 
void DeviceControl::mii_set_mode()
 {
  MII mii(*this);
  
  dev_reg.get_FLOWCR1()
         .clearbit(FLOWCR1_HDXFCEN)
         .setTo(dev_reg);

  mii.set_mode();
 }
 
LinkStatus DeviceControl::check_flow_control()
 {
  LinkStatus ret=check_link();
  
  if( ret&LinkStatus_Duplex )
    {
     MII mii(*this);
     
     auto anar=mii.get_MIIANAR();
     auto anlpar=mii.get_MIIANLPAR();
     
     if( anar.maskbit(MIIANAR_PAUSE) && anlpar.maskbit(MIIANLPAR_PAUSE) )
       {
        dev_reg.get_FLOWCR1()
               .setbit(FLOWCR1_FDXTFCEN|FLOWCR1_FDXRFCEN)
               .clearbit(FLOWCR1_HDXFCEN)
               .setTo(dev_reg);
       }
     else if( anar.testbit(MIIANAR_PAUSE|MIIANAR_ASMDIR) && anlpar.maskbit(MIIANLPAR_ASMDIR) )
       {
        dev_reg.get_FLOWCR1()
               .setbit(FLOWCR1_FDXRFCEN)
               .clearbit(FLOWCR1_HDXFCEN|FLOWCR1_FDXTFCEN)
               .setTo(dev_reg);
       }
     else if( anar.maskbit(MIIANAR_ASMDIR) && anlpar.testbit(MIIANLPAR_PAUSE|MIIANLPAR_ASMDIR) )  
       {
        dev_reg.get_FLOWCR1()
               .setbit(FLOWCR1_FDXTFCEN)
               .clearbit(FLOWCR1_HDXFCEN|FLOWCR1_FDXRFCEN)
               .setTo(dev_reg);
       }
     else
       {
        dev_reg.get_FLOWCR1()
               .clearbit(FLOWCR1_HDXFCEN|FLOWCR1_FDXRFCEN|FLOWCR1_FDXTFCEN)
               .setTo(dev_reg);
       }  
    }
  else
    {
     dev_reg.get_FLOWCR1()
            .clearbit(FLOWCR1_HDXFCEN|FLOWCR1_FDXTFCEN)
            .setTo(dev_reg);
    }  
    
  return ret;  
 }

void DeviceControl::setRD(AddressType ptr)
 {
  dev_reg.set_CurRD(address_map.host_to_pci(ptr));
 }
 
void DeviceControl::setTD(AddressType ptr)
 {
  dev_reg.set_CurTD(0,address_map.host_to_pci(ptr));  
 }
 
/* class DeviceEngine */ 

void DeviceEngine::InitRxDesc(AddressType desc,PCIBus::AddressMap address_map,AddressType buf,ulen buf_len,AddressType next)
 {
  RxDescBar<PCIBus::MemRW> bar(desc);
  
  bar.null_RxDescStatus()
     .setbit(RxDescStatus_Own)
     .setTo(bar);
  
  bar.null_RxDescControl()
     .set_Len(buf_len)
     .setTo(bar);
  
  bar.set_RxDescBuf(address_map.host_to_pci(buf));
  bar.set_RxDescNext(address_map.host_to_pci(next));
  
  bar.set_RxDescRes1(0);
  bar.set_RxDescRes2(0);
  bar.set_RxDescRes3(0);
  bar.set_RxDescRes4(0);
 }
 
void DeviceEngine::InitTxDesc(AddressType desc,PCIBus::AddressMap address_map,AddressType buf,AddressType next)
 {
  TxDescBar<PCIBus::MemRW> bar(desc);
  
  bar.null_TxDescStatus()
     .setTo(bar);
  
  bar.null_TxDescControl()
     .setbit(TxDescControl_CHAIN)
     .setTo(bar);
     
  bar.set_TxDescBuf(address_map.host_to_pci(buf));
  bar.set_TxDescNext(address_map.host_to_pci(next));
  
  bar.set_TxDescRes1(0);
  bar.set_TxDescRes2(0);
  bar.set_TxDescRes3(0);
  bar.set_TxDescRes4(0);
 }
 
void DeviceEngine::init_ring()
 {
  ulen mem_len = RxCount*(PacketLen+RxDescLen)
               + TxCount*(PacketLen+TxDescLen) ;
               
  ring_mem=TryMemAlloc_shared(mem_len);             
  
  if( !ring_mem )
    {
     dc.stop_device();

     dc.stop_pci();
     
     Printf(Exception,"Driver::VIA_Rhine_III::DeviceEngine::init_ring(...) : no shared memory");
    } 
    
  AddressType place=(AddressType)ring_mem;
  
  rx_ring=place; place+=RxCount*RxDescLen;
  
  tx_ring=place; place+=TxCount*TxDescLen;

  {
   AddressType desc=rx_ring;
   
   rx_buf_ring=(uint8 *)place;
  
   for(ulen cnt=RxCount; cnt ;cnt--,place+=PacketLen,desc+=RxDescLen)
     {
      AddressType next;
      
      if( cnt>1 )
        next=desc+RxDescLen;
      else  
        next=rx_ring;
     
      InitRxDesc(desc,dc.getAddressMap(),place,PacketLen,next);
     }
  }
  
  {
   AddressType desc=tx_ring;
   
   tx_buf_ring=(uint8 *)place;
  
   for(ulen cnt=TxCount; cnt ;cnt--,place+=PacketLen,desc+=TxDescLen)
     {
      AddressType next;
      
      if( cnt>1 )
        next=desc+TxDescLen;
      else  
        next=tx_ring;
     
      InitTxDesc(desc,dc.getAddressMap(),place,next);
     }
  }
  
  dc.setRD(rx_ring);
  dc.setTD(tx_ring);
    
  rx_ind=0;
  tx_ind=0;
  txdone_ind=0;
  tx_active=0;
 }
 
void DeviceEngine::handle_int()
 {
  DeviceControl::IntStatus status=dc.clear_int();
  
  dc.delay_int(status.isr);
  
  if( status.isr.maskbit(ISR_SRC) || (link_status&LinkStatus_NoLink) )
    {
     mevent.trigger_int(Event_Link);
     
     int_count.count(IntSRC);
    }

  if( status.isr.maskbit(ISR_PRX|ISR_GEN) || status.misr.maskbit(MISR_TM0) )
    {
     mevent.trigger_int(Event_Rx);
     
     int_count.count(IntRX);
    }

  if( status.isr.maskbit(ISR_PTX|ISR_GEN) || status.misr.maskbit(MISR_TM0) )
    {
     mevent.trigger_int(Event_Tx);
     
     int_count.count(IntTX);
    }
    
  if( status.isr.maskbit(ISR_GEN) || status.misr.maskbit(MISR_TM0) )      
    {
     dc.enable_rtx_int();
    
     int_count.count(IntGEN);
    } 
    
  status.isr.clearbit(ISR_SRC|ISR_PRX|ISR_PTX|ISR_GEN);  
  status.misr.clearbit(MISR_TM0);
    
  if( status.isr || status.misr )  
    {
     mevent.trigger_int(Event_Link);
     mevent.trigger_int(Event_Rx);
     mevent.trigger_int(Event_Tx);
     
     int_count.count(IntOther);
    }
 }
 
void DeviceEngine::handle_rx()
 {
  for(ulen cnt=RxCount; cnt ;cnt--)
    {
     RxDescBar<PCIBus::MemRW> bar(rx_desc(rx_ind));
     
     auto status=bar.get_RxDescStatus();
     
     if( status.maskbit(RxDescStatus_Own) ) break;
     
     if( status.testbit(RxDescStatus_OK|RxDescStatus_SOP|RxDescStatus_EOP) )
       {
        inbound_packet(rx_buf(rx_ind),status);
       }
     else if( status.maskbit(RxDescStatus_EOP) )  
       {
        inbound_error(status);
       }
     
     bar.null_RxDescStatus()
        .setbit(RxDescStatus_Own)
        .setTo(bar);
     
     dc.flow_control(1);
       
     rx_ind=NextRxInd(rx_ind);
    }

  dc.start_device(link_status);
 }
 
void DeviceEngine::handle_tx()
 {
  while( tx_active>0 )
    {
     TxDescBar<PCIBus::MemRW> bar(tx_desc(txdone_ind));
     
     auto status=bar.get_TxDescStatus();
     
     if( status.maskbit(TxDescStatus_Own) ) break;
     
     auto control=bar.get_TxDescControl();

     outbound_done(status,control.get_Len());
     
     tx_active--;
     
     txdone_ind=NextTxInd(txdone_ind);
    }
 }
 
void DeviceEngine::pump_tx()
 {
  while( tx_active<TxCount )
    {
     TxDescBar<PCIBus::MemRW> bar(tx_desc(tx_ind));
     
     auto status=bar.get_TxDescStatus();
     
     if( status.maskbit(TxDescStatus_Own) ) break;
     
     uint8 *buf=tx_buf(tx_ind);
     
     if( ulen len=get_outbound_packet(buf,PacketLen) )
       {
        if( len<MinPacketLen )
          {
           Range(buf+len,MinPacketLen-len).set_null();
           
           len=MinPacketLen;
          }
       
        bar.null_TxDescControl()
           .setbit(TxDescControl_SOP|TxDescControl_EOP|TxDescControl_IC|TxDescControl_CHAIN)
           .set_Len(len)
           .setTo(bar);
     
        bar.null_TxDescStatus()
           .setbit(TxDescStatus_Own)
           .setTo(bar);
  
        tx_active++;
        
        tx_ind=NextTxInd(tx_ind);
       }
     else
       {
        break;
       }
    }
    
  if( tx_active ) 
    {
     dc.start_device(link_status);
    } 
 }
 
auto DeviceEngine::getLinkStatus() -> LinkStatusUpdate
 {
  LinkStatus prev_link_status=Replace(link_status,dc.check_flow_control());
  
  LinkStatusUpdate ret;
  
  ret.status=link_status;
  ret.change=prev_link_status^link_status;
  
  return ret;
 }
 
void DeviceEngine::handle_link()
 {
  if( LinkStatusUpdate update=getLinkStatus() )
    {
     if( update.status&LinkStatus_NoLink )
       {
        linkDown();
       } 
     else
       {
        linkUp();
        
        pump_tx();
       } 
    }
 }
 
void DeviceEngine::inbound_packet(uint8 *,InboundStatus)
 {
  // do nothing
 }
 
void DeviceEngine::inbound_error(InboundStatus)
 {
  // do nothing
 }
 
void DeviceEngine::prepareOutbound()
 {
  // do nothing
 }
 
ulen DeviceEngine::get_outbound_packet(uint8 *,ulen)
 {
  // nothing to send
  
  return 0;
 }
 
void DeviceEngine::outbound_done(OutboundStatus,ulen)
 {
  // do nothing
 }
 
void DeviceEngine::linkUp()
 {
  // do nothing
 }
   
void DeviceEngine::linkDown()
 {
  // do nothing
 }
 
void DeviceEngine::tick()
 {
  // do nothing
 }
 
void DeviceEngine::start()
 {
  // do nothing
 }
   
void DeviceEngine::stop()
 {
  // do nothing
 }
 
void DeviceEngine::entry()
 {
  start();
  
  for(;;)
    {
     switch( mevent.wait() )
       {
        case Event_Stop     : stop();        return;
        
        case Event_Rx       : handle_rx();   break;
        
        case Event_Tick     : tick();        break;
        
        case Event_Link     : handle_link(); break;
        
        case Event_Tx       : handle_tx();       pump_tx(); break;
        
        case Event_Outbound : prepareOutbound(); pump_tx(); break;
       }
    }
 }
 
DeviceEngine::DeviceEngine(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map)
 : dc(info,address_map),
   mevent("Eth"),
   ticker(mevent.function_trigger_int<Event_Tick>()),
   outbound_trigger(mevent.function_trigger_int<Event_Outbound>(),1_msec),
   stop_sem("Eth")
 {
  // PCI
  
  dc.enable_pci();
                                           
  // stage 1                                        
  
  dc.enable_mmio();   
  
  dc.wol_reset();
  
  dc.soft_reset();
  
  //dc.reload_eeprom();
  
  address=dc.get_MAC();
  
  // PCI  
  
  dc.mode_pci();
         
  dc.enable_pci_busmaster();       
  
  // stage 2
  
  dc.set_tx_threshold(TxThreshold);
  
  dc.set_rx_threshold(RxThreshold);
  
  dc.set_dma_length(DMALength);
  
  dc.init_int();
  
  dc.cfg_device();
  
  dc.set_all_multicast();
    
  init_ring();

  dc.init_flow_control();
  
  dc.flow_control(RxCount);

  dc.start_device(LinkStatus_NoLink);  
  
  dc.mii_set_mode(); 
  
  link_status=dc.check_flow_control();
  
  dc.start_device(link_status);  
  
  mevent.trigger(Event_Link);
  
  // stage 3
  
  dc.setup_int_handler(function_handle_int());
  
  dc.enable_int();
 }
   
DeviceEngine::~DeviceEngine()
 {
  dc.disable_int();
 
  dc.stop_device();
  
  dc.soft_reset();
  
  dc.stop_pci(); 

  dc.cleanup_int_handler();                                         
  
  MemFree_shared(ring_mem);
 }
 
void DeviceEngine::test() 
 {
  Printf(Con,"link = #;\n",dc.check_link());
  
  auto int_status=dc.get_int();
  
  Printf(Con,"ISR = #;\nMISR = #;\n",int_status.isr,int_status.misr);
 }
 
void DeviceEngine::do_startTask(TaskPriority priority,ulen stack_len)
 {
  RunFuncTask(function_entry(),stop_sem.function_give(),"EthTask",priority,stack_len);
  
  ticker.start(100_msec,100_msec);
 }
 
void DeviceEngine::do_stopTask()
 {
  ticker.stop();
  outbound_trigger.stop();
 
  mevent.trigger(Event_Stop);
  
  stop_sem.take();
 }
 
void DeviceEngine::getIntCount(Counters<IntEvent,IntEventLim> &ret)
 {
  IntLock lock;
  
  ret=int_count;
 }
 
void DeviceEngine::enable_promiscuous()
 {
  IntLock lock;
  
  dc.enable_promiscuous();
 }
 
void DeviceEngine::disable_promiscuous()
 {
  IntLock lock;
  
  dc.disable_promiscuous();
 }
 
/* struct PacketEvent */

void PacketEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto enum_id=info.addEnum_uint8("VIA_Rhine_III_PreparePacket")
                   .addValueName(RxBegin,"Rx begin",EventMarker_Up)
                   .addValueName(RxEnd,"Rx end",EventMarker_Down)
                   .addValueName(TxBegin,"Tx begin",EventMarker_Up)
                   .addValueName(TxEnd,"Tx end",EventMarker_Down)
                   .getId();
  
  auto id=info.addStruct("VIA_Rhine_III_Event")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(enum_id,"type",Offset_type)
              .getId();
  
  desc.setStructId(info,id);
 }

/* class DeviceImp */  

void DeviceImp::inbound_packet(uint8 *buf,InboundStatus status)
 {
  if( status.isBroadcast() ) stat.count(EthRx_Broadcast);
  
  ulen len=status.getPacketLen();
  
  if( len<EthHeaderLen )
    {
     stat.count(EthRx_BadPacketLen);
    
     return;
    }
    
  ulen data_len=len-EthHeaderLen;  
    
  Replace_min(data_len,MaxEthDataLen); // packet with CRC  
    
  Packet<uint8> packet=pset.try_get();
  
  if( !packet )
    {
     stat.count(EthRx_Drop);
    
     return;
    }
    
  if( data_len>packet.getMaxDataLen() ) // not happens
    {
     stat.count(EthRx_BadPacketLen);
     
     packet.complete();
     
     return;
    }
    
  // prepare and send  
    
  TaskEventHost.addDev<PacketEvent>(PacketEvent::RxBegin);
  
  EthHeader header;
  
  BufGetDev dev(buf);
  
  dev(header);
  
  Packet<uint8,EthRxExt> packet2=packet.pushExt<EthRxExt>(header.src,header.dst,header.type); 
    
  packet2.setDataLen(data_len).copy(buf+EthHeaderLen);
  
  packet2.pushCompleteFunction(DropPacketExt<uint8,EthRxExt>);
  
  packet2.stamp();

  TaskEventHost.addDev<PacketEvent>(PacketEvent::RxEnd);
  
  proc->inbound(packet2);
  
  stat.count(EthRx_Done);
 }
   
void DeviceImp::inbound_error(InboundStatus)
 {
  stat.count(EthRx_Error);
 }
   
void DeviceImp::prepareOutbound()
 {
  proc->prepareOutbound();
 }
  
ulen DeviceImp::get_outbound_packet(uint8 *buf,ulen buf_len)
 {
  for(;;)
    {
     Packet<uint8,EthTxExt> packet=proc->outbound();
     
     if( !packet ) return 0;
     
     ulen len=packet.getDataLen();
  
     if( len<EthHeaderLen || len>EthHeaderLen+MaxEthDataLen || len>buf_len )
       {
        packet.complete();
        
        stat.count(EthTx_BadPacketLen);
       }
     else
       {
        TaskEventHost.addDev<PacketEvent>(PacketEvent::TxBegin);
        
        EthTxExt *ext=packet.getExt();
       
        EthHeader header(getAddress(),ext->dst,ext->type);
        
        BufPutDev dev(packet.getData());
        
        dev(header);
        
        packet.getRange().copyTo(buf);
       
        TaskEventHost.addDev<PacketEvent>(PacketEvent::TxEnd);
        
        packet.complete();
       
        return len;
       }
    }
 }
   
void DeviceImp::outbound_done(OutboundStatus status,ulen)
 {
  if( status.isError() )
    stat.count(EthTx_Error);
  else
    stat.count(EthTx_Done);
 }
   
void DeviceImp::linkUp()
 {
  stat.count(EthLink_Up);
  
  has_link=true;
  
  proc->linkUp();
 }
   
void DeviceImp::linkDown()
 {
  stat.count(EthLink_Down);
  
  has_link=false;
 
  proc->linkDown();
 }
   
void DeviceImp::tick()
 {
  {
   Mutex::Lock lock(mutex);
   
   stat_toget=stat;
  }
 
  proc->tick();
 }
   
void DeviceImp::start()
 {
  stat.reset();
  has_link=false;
  
  {
   Mutex::Lock lock(mutex);
   
   stat_toget.reset();
  }
 
  proc->start();
 }
   
void DeviceImp::stop()
 {
  proc->stop();
  
  pset.cancel_and_wait();
 }
   
DeviceImp::DeviceImp(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map)
 : DeviceEngine(info,address_map),
   has_link(false),
   pset("VIA_Rhine_III.pset",MaxRxPackets),
   mutex("VIA_Rhine_III"),
   proc(0),
   run_flag(Stopped),
   promisc(false)
 {
 }
   
DeviceImp::~DeviceImp()
 {
  Mutex::Lock lock(mutex);
  
  if( run_flag!=Stopped ) Abort("Fatal error : Driver::VIA_Rhine_III::DeviceImp is running on exit");
  
  if( proc ) Abort("Fatal error : Driver::VIA_Rhine_III::DeviceImp is attached on exit");
 }
   
PacketFormat DeviceImp::getTxFormat()
 {
  PacketFormat ret;
  
  ret.prefix=EthHeaderLen;
  ret.max_data=MaxEthDataLen;
  ret.suffix=0;
  
  return ret;
 }
  
PacketFormat DeviceImp::getRxFormat()
 {
  PacketFormat ret;
 
  ret.prefix=0;
  ret.max_data=MaxEthDataLen;
  ret.suffix=0;
  
  return ret;
 }
  
void DeviceImp::attach(EthProc *proc_)
 {
  bool running;
  bool has_proc;
  
  {
   Mutex::Lock lock(mutex);
   
   running=(run_flag!=Stopped);
   has_proc=(proc!=0);
   
   if( !running && !has_proc ) proc=proc_;
  }
  
  if( running )
    {
     Printf(Exception,"Driver::VIA_Rhine_III::DeviceImp::attach(...) : device is running");
    }
    
  if( has_proc )  
    {
     Printf(Exception,"Driver::VIA_Rhine_III::DeviceImp::attach(...) : already attached");
    }
 }
  
void DeviceImp::detach()
 {
  bool running;
  
  {
   Mutex::Lock lock(mutex);
   
   running=(run_flag!=Stopped);
   
   if( !running ) proc=0;
  }
  
  if( running )
    {
     Printf(NoException,"Driver::VIA_Rhine_III::DeviceImp::detach() : device is running");
     
     Abort("Fatal error : Driver::VIA_Rhine_III::DeviceImp is running on detach");
    }
 }
  
void DeviceImp::getStat(EthStatInfo &ret)
 {
  Mutex::Lock lock(mutex);
  
  ret=stat_toget;
 }
  
bool DeviceImp::getPromiscMode()
 {
  Mutex::Lock lock(mutex);
  
  return promisc;
 }
  
void DeviceImp::setPromiscMode(bool enable)
 {
  Mutex::Lock lock(mutex);

  if( promisc!=enable )
    {
     if( enable )
       enable_promiscuous();
     else
       disable_promiscuous();
     
     promisc=enable;
    }
 }
  
void DeviceImp::startTask(TaskPriority priority,ulen stack_len)
 {
  bool running;
  bool has_proc;
  
  {
   Mutex::Lock lock(mutex);
   
   running=(run_flag!=Stopped);
   has_proc=(proc!=0);
   
   if( !running && has_proc )
     {
      do_startTask(priority,stack_len);
      
      run_flag=Running;
     }
  }
  
  if( running )
    {
     Printf(Exception,"Driver::VIA_Rhine_III::DeviceImp::startTask() : already running");
    }
     
  if( !has_proc )  
    {
     Printf(Exception,"Driver::VIA_Rhine_III::DeviceImp::startTask() : not attached");
    }
 }
  
void DeviceImp::stopTask()
 {
  bool running;
  
  {
   Mutex::Lock lock(mutex);
   
   running=(run_flag==Running);

   if( running ) run_flag=Stopping;
  }
  
  if( !running )
    {
     Printf(NoException,"Driver::VIA_Rhine_III::DeviceImp::stopTask() : not running");
     
     return;
    }
  
  do_stopTask();
  
  {
   Mutex::Lock lock(mutex);

   run_flag=Stopped;
  } 
 }
   
/* class Device */ 

Device::Device(const PCIBus::DeviceInfo &info,PCIBus::AddressMap address_map) : dev(info,address_map) {}
   
Device::~Device() {}
   
void Device::getIntCount(Counters<IntEvent,IntEventLim> &ret) { dev.getIntCount(ret); }
   
MACAddress Device::getAddress() { return dev.getAddress(); }
  
PacketFormat Device::getTxFormat() { return dev.getTxFormat(); }
  
PacketFormat Device::getRxFormat() { return dev.getRxFormat(); }
  
void Device::attach(EthProc *proc) { dev.attach(proc); }
  
void Device::detach() { dev.detach(); }
  
void Device::getStat(EthStatInfo &ret) { dev.getStat(ret); }
  
bool Device::getPromiscMode() { return dev.getPromiscMode(); }
  
void Device::setPromiscMode(bool enable) { dev.setPromiscMode(enable); }
  
void Device::signalOutbound() { dev.signalOutbound(); }
  
void Device::startTask(TaskPriority priority,ulen stack_len) { dev.startTask(priority,stack_len); }
  
void Device::stopTask() { dev.stopTask(); }
 
} // namespace VIA_Rhine_III
} // namespace Driver
 

