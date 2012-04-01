/* Elf.h */ 
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

#ifndef CCore_inc_Elf_h
#define CCore_inc_Elf_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/SaveLoad.h>
 
namespace CCore {
namespace Elf {

/* consts */ 

enum BitType
 {
  BitType_32 = 1,
  BitType_64 = 2
 };
 
enum EndianType
 {
  EndianType_LE = 1,
  EndianType_BE = 2
 };
 
enum CPUType
 {
  CPUType_ARM = 40
 };
 
enum SectType
 {
  SectType_null                 =  0,
  SectType_program_defined      =  1,
  SectType_symbol_table         =  2,
  SectType_string_table         =  3,
  SectType_relocation_A         =  4,
  SectType_symbol_hash_table    =  5,
  SectType_dynamic_link_info    =  6,
  SectType_note                 =  7,
  SectType_no_data              =  8,
  SectType_reloaction           =  9,
  SectType_shlib                = 10,
  SectType_dynamic_symbol_table = 11 
 };
 
enum SectFlags
 {
  SectFlag_write = 1,
  SectFlag_alloc = 2,
  SectFlag_code  = 4
 };
 
/* functions */   

void GuardTakeFailed(uint32 off,ulen len,ulen lim);

inline void GuardTake(uint32 off,ulen len,ulen lim)
 {
  if( len>lim || off>lim-len ) GuardTakeFailed(off,len,lim);
 }
 
ulen ScanNull(const uint8 *base,uint32 off,ulen lim); 

void GuardLimFailed(const char *name,uint32 val);
 
/* classes */  

struct Header;

struct PrintSectType;

struct PrintSectFlags;

struct SectHeader;

template <class Custom> struct LoadHeader;

template <class Custom> struct LoadSectHeader;

class Take;

/* struct Header */ 

struct Header
 {
  // +0
  
  uint8 elf0;
  uint8 elf1;
  uint8 elf2;
  uint8 elf3;
  uint8 bit_type;
  uint8 endian_type;
  
  // +16
  
  uint16 file_type;
  uint16 cpu_type;
  uint32 elf_version;
  uint32 entry_point;
  uint32 program_header_off;
  uint32 section_header_off;
  uint32 cpu_flags;
  uint16 header_size;
  uint16 program_header_size;
  uint16 program_header_count;
  uint16 section_header_size;
  uint16 section_header_count;
  uint16 section_name_section_index;
  
  bool check_id(uint8 bit_type_,uint8 endian_type_) const
   {
    return elf0==0x7f && 
           elf1=='E' && 
           elf2=='L' && 
           elf3=='F' && 
           bit_type==bit_type_ && 
           endian_type==endian_type_ ;
   }
   
  bool check_cpu(uint16 cpu_type_) const
   {
    return cpu_type==cpu_type_;
   }
   
  template <class P>
  void print(P &out) const
   {
    Printf(out,"file type   = #;\n"
               "elf version = #;\n"
               "cpu flags   = #.h;\n"
               
               "program header offset = #9.hi;\n"
               "program header count  = #;\n"
               "program header size   = #5.hi;\n"
               
               "entry point           = #9.hi;\n"
               "section header offset = #9.hi;\n"
               "section header count  = #;\n"
               "section header size   = #5.hi;\n"
               "section name index    = #;\n"
           
              ,file_type
              ,elf_version
              ,cpu_flags
              
              ,program_header_off
              ,program_header_count
              ,program_header_size
              
              ,entry_point
              ,section_header_off
              ,section_header_count
              ,section_header_size
              ,section_name_section_index);
   }  
 };
 
/* struct PrintSectType */ 
 
struct PrintSectType
 {
  uint32 type;
  
  explicit PrintSectType(uint32 type_) : type(type_) {}
  
  const char * getStr() const
   {
    switch( type )
      {
       case SectType_null                 : return "null";
       case SectType_program_defined      : return "program defined";
       case SectType_symbol_table         : return "symbol table";
       case SectType_string_table         : return "string table";
       case SectType_relocation_A         : return "relocation A";
       case SectType_symbol_hash_table    : return "symbol hash table";
       case SectType_dynamic_link_info    : return "dynamic link info";
       case SectType_note                 : return "note";
       case SectType_no_data              : return "no data";
       case SectType_reloaction           : return "reloaction";
       case SectType_shlib                : return "shlib";
       case SectType_dynamic_symbol_table : return "dynamic symbol table";
           
       default: return 0;
      }
   }
  
  template <class P>
  void print(P &out) const
   {
    if( const char *zstr=getStr() )
      {
       Putobj(out,zstr);
      }
    else
      {
       Printf(out,"#;",type);
      }
   }
 };
 
/* struct PrintSectFlags */ 

struct PrintSectFlags
 {
  uint32 flags;
  
  explicit PrintSectFlags(uint32 flags_) : flags(flags_) {}
  
  template <class P>
  void print(P &out) const
   {
    if( flags&SectFlag_code ) 
      Putobj(out,"CODE");
    else
      Putobj(out,"DATA");
        
    if( flags&SectFlag_write ) 
      Putobj(out," READ-WRITE");
    else  
      Putobj(out," READ-ONLY");
        
    if( flags&SectFlag_alloc ) 
      Putobj(out," ALLOC");
   }
 };
 
/* struct SectHeader */ 

struct SectHeader
 {
  uint32 name_off;
  uint32 type;
  uint32 flags;
  uint32 address;
  uint32 data_off;
  uint32 size;
  uint32 link;
  uint32 info;
  uint32 address_align;
  uint32 entry_size;
  
  bool isLoadable() const
   {
    return (flags&SectFlag_alloc) && (type!=SectType_no_data) && size!=0 ;
   }
  
  template <class P>
  void print(P &out) const
   {
    Printf(out,"address     = #9.hi;\n"
               "data offset = #9.hi;\n"  
               "size        = #9.hi;\n"
               "type        = #;\n"
               "flags       = #;\n"
               
              ,address
              ,data_off
              ,size
              ,PrintSectType(type)
              ,PrintSectFlags(flags));
   }  
 };
 
/* struct LoadHeader<Custom> */ 
 
template <class Custom> 
struct LoadHeader : Header
 {
  // load object
  
  enum { SaveLoadLen = 52 };
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<Custom>(elf0,
                             elf1,
                             elf2,
                             elf3,
                             bit_type,
                             endian_type);
                             
    dev.getRange(10);        
    
    dev.template use<Custom>(file_type,
                             cpu_type,
                             elf_version,
                             entry_point,
                             program_header_off,
                             section_header_off,
                             cpu_flags,
                             header_size,
                             program_header_size,
                             program_header_count,
                             section_header_size,
                             section_header_count,
                             section_name_section_index);                 
   } 
 };
 
/* struct LoadSectHeader<Custom> */ 

template <class Custom> 
struct LoadSectHeader : SectHeader
 {
  // load object
  
  enum { SaveLoadLen = 40 };
  
  template <class Dev>
  void load(Dev &dev)
   {
    dev.template use<Custom>(name_off,
                             type,
                             flags,
                             address,
                             data_off,
                             size,
                             link,
                             info,
                             address_align,
                             entry_size);
   }
 };
 
/* class Take */ 

class Take : NoCopy
 {
   const uint8 *base;
   ulen len;

  public:
  
   explicit Take(PtrLen<const uint8> map) : base(map.ptr),len(map.len) {}
   
   template <class T>
   void operator () (uint32 off,T &t) const
    {
     GuardTake(off,T::SaveLoadLen,len);
     
     BufGetDev dev(base+off);
     
     dev(t);
    }
   
   void operator () (uint32 off,StrLen &ret) const
    {
     ret.len=ScanNull(base,off,len);
     ret.ptr=MutatePtr<const char>(base+off);
    }
    
   void operator () (uint32 off,ulen size,PtrLen<const uint8> &ret) const
    {
     GuardTake(off,size,len);
     
     ret=Range(base+off,size);
    }
 };
 
/* functions */  

//
// class Dev
//  {
//   public:
//
//    void operator () (const Elf::Header &header);
//
//    void operator () (ulen index,StrLen name,const Elf::SectHeader &sect);
//
//    void operator () (ulen index,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data);
//
//    void operator () ();
//  };
//

template <class Custom,class Dev>
void Parse(Dev &dev,PtrLen<const uint8> map)
 {
  Take take(map);
 
  StrLen no_name("<no name>");
  uint32 name_list_off;
     
  // Header
     
  LoadHeader<Custom> header;
  
  take(0,header);
     
  if( header.section_header_size<LoadSectHeader<Custom>::SaveLoadLen ) 
    {
     GuardLimFailed("header.section_header_size",header.section_header_size);
    }
     
  if( header.section_name_section_index )
    {
     uint32 off=header.section_header_off+(uint32)header.section_name_section_index*header.section_header_size;
     
     LoadSectHeader<Custom> sect;
     
     take(off,sect);
     
     name_list_off=sect.data_off;
    } 
  else
    {
     name_list_off=0;
    }  
       
  dev((const Header &)header);  

  // *SectHeader
     
  uint32 off=header.section_header_off;
     
  for(uint16 i=0; i<header.section_header_count ;i++,off+=header.section_header_size)
    {
     LoadSectHeader<Custom> sect;
     
     take(off,sect);
        
     StrLen name=no_name;
        
     if( header.section_name_section_index )
       {
        take(name_list_off+sect.name_off,name);
       }
          
     if( sect.isLoadable() )  
       {
        if( sect.size>MaxULen ) GuardLimFailed("sect.size",sect.size);
       
        PtrLen<const uint8> data;
           
        take(sect.data_off,(ulen)sect.size,data);
          
        dev(i,name,(const SectHeader &)sect,data);
       }
     else
       {
        dev(i,name,(const SectHeader &)sect);  
       } 
    } 
       
  // complete
     
  dev();  
 }
 
} // namespace Elf
} // namespace CCore
 
#endif
 

