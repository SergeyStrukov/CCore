/* main.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: ELFtoUboot 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Elf.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/SaveLoad.h>

namespace App {

/* using */

using namespace CCore;

/* ZeroTo() */

const ulen ZeroToLen = 4_KByte ;

static const uint8 ZeroToBuf[ZeroToLen]={};

template <class Dev>
void ZeroTo(Dev &dst,uint32 len)
 {
  while( len>ZeroToLen )
    {
     dst.write(ZeroToBuf,ZeroToLen);
     
     len-=ZeroToLen;
    }
  
  dst.write(ZeroToBuf,len);
 }

/* SaveTo() */

template <class Dev,class T>
void SaveTo(Dev &dst,const T &obj)
 {
  uint8 temp[T::SaveLoadLen];
  
  BufPutDev dev(temp);
  
  dev(obj);
  
  dst.write(Range_const(temp));
 }

/* class BinaryFile */

class BinaryFile : NoCopy
 {
   RawFileToPrint file;
   
  public: 
   
   explicit BinaryFile(StrLen file_name)
    {
     if( FileError fe=file.open(file_name,Open_ToWrite) )
       {
        Printf(Exception,"Cannot open file #.q; : #;",file_name,fe);
       }
    }
   
   ~BinaryFile()
    {
     FileMultiError errout;
     
     file.close(errout);
     
     if( +errout ) 
       {
        Printf(NoException,"File close error : #;",errout);
       }
    }
   
   void write(const uint8 *buf,ulen len)
    {
     if( FileError fe=file.write(buf,len) )
       {
        Printf(Exception,"Write file failure : #;",fe);
       }
    }
   
   void write(PtrLen<const uint8> data)
    {
     write(data.ptr,data.len);
    }
 };

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
 
/* class BuildImage */

class BuildImage : NoCopy
 {
   struct Rec : NoThrowFlagsBase
    {
     StrLen name;
     Elf::SectHeader sect;
     PtrLen<const uint8> data;
    
     Rec(StrLen name_,const Elf::SectHeader &sect_,PtrLen<const uint8> data_) : name(name_),sect(sect_),data(data_) {}
    
     bool operator < (const Rec &b) const { return sect.address<b.sect.address ; }
   };
   
   DynArray<Rec> table;
  
   uint32 entry_point;
   uint32 load_base;
   uint32 load_lim;
   
  private:
 
   static const uint32 MinAddress   = 0x81000000 ;
   static const uint32 LimAddress   = 0x82000000 ;
   static const uint32 AlignAddress =          4 ;
  
   static uint32 Guard(uint32 address,uint32 size);
  
  public:
  
   BuildImage() {}
   
   ~BuildImage() {}
   
   void operator () (const Elf::Header &header);
    
   void operator () (ulen,StrLen,const Elf::SectHeader &);
    
   void operator () (ulen,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data);
    
   void operator () ();
   
   void save(StrLen img_file_name);
 };

uint32 BuildImage::Guard(uint32 address,uint32 size)
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

void BuildImage::operator () (const Elf::Header &header)
 {
  if( !header.check_id(Elf::BitType_32,Elf::EndianType_LE) )
    {
     Printf(Exception,"Bad file");
    }
    
  if( !header.check_cpu(Elf::CPUType_ARM) )
    {
     Printf(Exception,"Bad file");
    }
    
  entry_point=header.entry_point;
 }
 
void BuildImage::operator () (ulen,StrLen,const Elf::SectHeader &)
 {
 }
 
void BuildImage::operator () (ulen,StrLen name,const Elf::SectHeader &sect,PtrLen<const uint8> data)
 {
  table.append_fill(name,sect,data);
 }

void BuildImage::operator () ()
 {
  Sort(Range(table));
     
  ulen max_name_len=8;
     
  for(auto &obj : table ) Replace_max(max_name_len,obj.name.len);
     
  StrPrintOpt name_opt;
     
  name_opt.width=max_name_len;
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
   
  Printf(Con,"#;   address      size  flags\n",BindOpt(name_opt,"name"));
     
  Printf(Con,"#;  --------  --------  -----\n",RepeatChar(max_name_len,'-'));
  
  if( !table.getLen() )
    {
     Printf(Exception,"No sections");
    }
  
  load_base=table[0].sect.address;
     
  for(auto r=Range(table); +r ;++r)
    {
     Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",BindOpt(name_opt,r->name),r->sect.address,r->sect.size,PrintFlags(r->sect.flags));
     
     uint32 lim=Guard(r->sect.address,r->sect.size);
     
     if( r.len>=2 )
       {
        auto &r1=r[1];
        
        if( r1.sect.address<lim )
          {
           Printf(Exception,"Section overlapp");
          }
             
        if( r1.sect.address>lim )  
          {
           Printf(Con,"#;  #8.16i;  #8.16i;  #;\n",RepeatChar(max_name_len,' '),lim,(r1.sect.address-lim),"hole");
          }
       }
     else
       {
        Printf(Con,"#;  #8.16i;\n",RepeatChar(max_name_len,' '),lim);
        
        load_lim=lim;
       }
    } 
       
  Printf(Con,"#;  --------  --------  -----\n\n",RepeatChar(max_name_len,'-'));  
     
  Printf(Con,"load_base = #8.16i;\n\n",load_base);
  Printf(Con,"load_lim = #8.16i;\n\n",load_lim);
  Printf(Con,"entry_point = #8.16i;\n\n",entry_point);
  
  if( entry_point<load_base || entry_point>=load_lim )
    {
     Printf(Exception,"Bad entry point");
    }
  
#if 1  
  
  if( load_base!=0x81000000 )
    {
     Printf(Exception,"Bad load base");
    }
  
  if( entry_point!=load_base )
    {
     Printf(Exception,"Bad entry point");
    }
  
#endif  
 }

void BuildImage::save(StrLen img_file_name)
 {
  BinaryFile out(img_file_name);
  
  uint32 lim=load_base;
   
  for(auto &obj : table )
    {
     uint32 address=obj.sect.address;
      
     if( address>lim ) ZeroTo(out,address-lim);

     out.write(obj.data);
      
     lim=address+obj.sect.size;
    }
 }

/* Process() */

void Process(StrLen elf_file_name,StrLen img_file_name)
 {
  Printf(Con,"#; -> #;\n\n",elf_file_name,img_file_name);
  
  FileToMem file(elf_file_name);
  
  BuildImage build;
  
  Elf::Parse<LeOrder>(build,Range(file));
  
  build.save(img_file_name);
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  ReportException report;
  
  try
    {
     {
      Putobj(Con,"--- ELFtoUboot 1.00 ---\n--- Copyright (c) 2014 Sergey Strukov. All rights reserved. ---\n\n");
      
      if( argc!=3 )
        {
         Putobj(Con,"Usage: ELFtoUboot.exe <elf-file> <img-file>\n");

         return 1;
        }
      else
        {
         Process(argv[1],argv[2]);
        }
     }
     
     report.guard();
     
     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
 
