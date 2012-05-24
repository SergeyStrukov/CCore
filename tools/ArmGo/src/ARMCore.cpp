/* ARMCore.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: ARMGo 0.50
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2012 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/ARMCore.h>

#include <CCore/inc/Elf.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace ARMCore {

namespace Private_ARMCore {

/* struct PrintFlags */ 
 
struct PrintFlags
 {
  uint32 flags;
  
  explicit PrintFlags(uint32 flags_) : flags(flags_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( flags&Elf::SectFlag_code )
      Putobj(out,"C  ");
    else
      Putobj(out,"D  ");
    
    if( flags&Elf::SectFlag_write )
      Putobj(out,"RW");
    else
      Putobj(out,"RO");
   }
 };
 
/* class Load */ 

class Load : NoCopy
 {
   static const uint32 MinAddress   =  2_MByte ;
   static const uint32 LimAddress   = 32_MByte ;
   static const uint32 AlignAddress =        4 ;
 
   struct Rec
    {
     StrLen name;
     Elf::SectHeader sect;
     PtrLen<const uint8> data;
     
     Rec(StrLen name_,const Elf::SectHeader &sect_,PtrLen<const uint8> data_) : name(name_),sect(sect_),data(data_) {}
     
     bool operator < (const Rec &b) const { return sect.address<b.sect.address ; }
   
     // no-throw flags
   
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
    
   DynArray<Rec> table;
   
   uint32 entry_point;
   
  private:
  
   uint32 guard(uint32 address,uint32 size);
   
   static void CopyData(Word &mem,Word b1,Word b2,Word b3,Word b4);
   
   static void CopyData(PtrLen<Word> mem,PtrLen<const uint8> data);
   
   static void CopyData(PtrLen<Word> mem,uint32 address,PtrLen<const uint8> data);
   
  public:
  
   Load() {}
   
   ~Load() {}
  
   void operator () (const Elf::Header &header)
    {
     if( !header.check_id(Elf::BitType_32,Elf::EndianType_BE) )
       {
        Printf(Exception,"Bad ELF file");
       }
       
     if( !header.check_cpu(Elf::CPUType_ARM) )
       {
        Printf(Exception,"Bad ELF file");
       }
       
     entry_point=header.entry_point;
    }
    
   void operator () (ulen,StrLen,const Elf::SectHeader &)
    {
    }
    
   void operator () (ulen,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data)
    {
     table.append_fill(name,sect,data);
    }
    
   void operator () (); 
    
   void boot(PtrLen<Word> mem); 
 };
 
uint32 Load::guard(uint32 address,uint32 size)
 {
  uint32 lim=address+size;
        
  if( address<MinAddress )
    {
     Printf(Exception,"Section is below limit");
    }
        
  if( size>LimAddress || address>LimAddress-size )
    {
     Printf(Exception,"Section is above limit");
    }
    
  if( address%AlignAddress )  
    {
     Printf(Exception,"Section is not aligned");
    }

  return lim;     
 }
 
void Load::operator () ()
 {
  Sort(table.getPtr(),table.getLen());
     
  ulen max_name_len=8;
     
  for(auto r=Range(table); +r ;++r) Replace_max(max_name_len,r->name.len);
     
  StrPrintOpt name_opt;
     
  name_opt.width=max_name_len;
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
   
  Printf(Con,"#;   address      size  flags\n",BindOpt(name_opt,"name"));
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
     
  for(auto r=Range(table); +r ;++r)
    {
     Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",BindOpt(name_opt,r->name),r->sect.address,r->sect.size,PrintFlags(r->sect.flags));
     
     uint32 lim=guard(r->sect.address,r->sect.size);
     
     if( r.len>=2 )
       {
        auto r1=&(r[1]);
        
        if( r1->sect.address<lim )
          {
           Printf(Exception,"Section overlapp");
          }
             
        if( r1->sect.address>lim )  
          {
           Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",RepeatChar(max_name_len,' '),lim,(r1->sect.address-lim),"hole");
          }
       }
     else
       {
        Printf(Con,"#;  #8.16i;\n",RepeatChar(max_name_len,' '),lim);
       }
    } 
       
  Printf(Con,"#;  --------  --------  -----\n\n",RepeatChar(max_name_len,'-'));  
     
  Printf(Con,"entry_point = #8.16i;\n\n",entry_point);
 } 
    
void Load::CopyData(Word &mem,Word b1,Word b2,Word b3,Word b4)
 {
  mem=(b1<<24)|(b2<<16)|(b3<<8)|b4;
 }

void Load::CopyData(PtrLen<Word> mem,PtrLen<const uint8> data)
 {
  if( (data.len+3)/4>mem.len )
    {
     Printf(Exception,"Section does not fit memory");
    }
  
  for(; data.len>=4 ;data+=4,++mem)
    {
     CopyData(*mem,data[0],data[1],data[2],data[3]);
    }
  
  switch( data.len )
    {
     case 1 : CopyData(*mem,data[0],0,0,0); break;
     case 2 : CopyData(*mem,data[0],data[1],0,0); break;
     case 3 : CopyData(*mem,data[0],data[1],data[2],0); break;
    }
 }

void Load::CopyData(PtrLen<Word> mem,uint32 address,PtrLen<const uint8> data)
 {
  ulen off=address/4;
  
  if( off>mem.len )
    {
     Printf(Exception,"Section does not fit memory");
    }
  
  CopyData(mem.part(off),data);
 }

void Load::boot(PtrLen<Word> mem)
 {
  for(auto r=Range(table); +r ;++r) CopyData(mem,r->sect.address,r->data);

  if( mem.len<20 )
    {
     Printf(Exception,"Too short memory");
    }
  
  mem.prefix(8).set(0xE59FF018);
  
  mem[8]=64;
  
  mem.part(9,7).set(StopAddress);
  
  mem[16]=0xE59FD000;
  mem[17]=0xE59FF000;
  mem[18]=0x10000;
  mem[19]=entry_point;
 }

} // namespace Private_ARMCore

using namespace Private_ARMCore;
 
/* LoadImage() */

void LoadImage(PtrLen<Word> mem,StrLen file_name)
 {
  FileToMem file(file_name);
  
  Load load;
  
  Elf::Parse<BeOrder>(load,Range(file));
  
  load.boot(mem);
 }

} // namespace ARMCore

