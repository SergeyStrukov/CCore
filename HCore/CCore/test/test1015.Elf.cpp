/* test1015.Elf.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2010 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Elf.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>

namespace App {

namespace Private_1015 {

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
 
/* class Show */

class Show : NoCopy
 {
   struct Rec
    {
     StrLen name;
     Elf::SectHeader sect;
     
     Rec(StrLen name_,const Elf::SectHeader &sect_) : name(name_),sect(sect_) {}
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
    
   DynArray<Rec> table;
 
   struct DataRec
    {
     StrLen name;
     Elf::SectHeader sect;
     PtrLen<const uint8> data;
     
     DataRec(StrLen name_,const Elf::SectHeader &sect_,PtrLen<const uint8> data_) : name(name_),sect(sect_),data(data_) {}
     
     bool operator < (const DataRec &obj) const { return sect.address<obj.sect.address ; }
     
     // no-throw flags
     
     enum NoThrowFlagType
      {
       Default_no_throw = true,
       Copy_no_throw = true
      };
    };
    
   DynArray<DataRec> data_table;
   
  public:
   
   Show() {}
  
   ~Show() {}
   
   void operator () (const Elf::Header &header)
    {
     Printf(Con,"#;\n",header);
     
     if( !header.check_id(Elf::BitType_32,Elf::EndianType_BE) )
       {
        Printf(Exception,"Bad file");
       }
       
     if( !header.check_cpu(Elf::CPUType_ARM) )
       {
        Printf(Exception,"Bad file");
       }
    }
    
   void operator () (ulen index,StrLen name,const Elf::SectHeader &sect)
    {
     Printf(Con,"sect[#;] #;\n\n#;\n",index,name,sect);
     
     table.append_fill(name,sect);
    }
    
   void operator () (ulen index,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data)
    {
     Printf(Con,"load sect[#;] #;\n\n#;\n",index,name,sect);
     
     data_table.append_fill(name,sect,data);
    }
    
   void operator () ()
    {
     Sort(Range(data_table));
     
     ulen max_name_len=8;
     
     for(auto r=Range(data_table); +r ;++r) Replace_max(max_name_len,r->name.len);
     
     StrPrintOpt name_opt;
     
     name_opt.width=max_name_len;
     
     Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
     
     Printf(Con,"#;   address      size  flags\n",BindOpt(name_opt,"name"));
     
     Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
     
     for(auto r=Range(data_table); +r ;++r)
       {
        Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",BindOpt(name_opt,r->name),r->sect.address,r->sect.size,PrintFlags(r->sect.flags));
        
        auto r1=r;
        
        ++r1;
        
        uint32 lim=r->sect.address+r->sect.size;
        
        if( +r1 )
          {
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
       
     Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));  
    } 
 };
 
} // namespace Private_1015
 
using namespace Private_1015; 
 
/* Testit<1015> */ 

template<>
const char *const Testit<1015>::Name="Test1015 Elf";

template<>
bool Testit<1015>::Main() 
 { 
  FileToMem file("../../../HCore/files/elf.exe");
  
  Show show;
  
  Elf::Parse<BeOrder>(show,Range(file));
 
  return true;
 }
 
} // namespace App
 
