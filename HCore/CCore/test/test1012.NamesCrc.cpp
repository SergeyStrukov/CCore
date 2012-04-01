/* test1012.NamesCrc.cpp */ 
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

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Crc.h>

namespace App {

namespace Private_1012 {

/* struct Rec<Crc> */  
 
template <class Crc>
struct Rec
 {
  StrLen name;
  typename Crc::ResultType crc;
  
  Rec(StrLen name_) 
   : name(name_)
   {
    Crc dev;
    
    dev.addRange(name);
    
    crc=dev;
   }
   
  bool operator < (const Rec<Crc> &obj) const 
   { 
    return crc<obj.crc || ( crc==obj.crc && StrLess(name,obj.name) ) ; 
   }
   
  template <class P> 
  void print(P &out) const
   {
    Printf(out,"#8.16i; #;",crc,name);
   }
  
  // no-throw flags
  
  enum NoThrowFlagType
   {
    Default_no_throw = true,
    Copy_no_throw = true
   };
 };
 
/* class Engine<Crc> */ 
 
template <class Crc>
class Engine : NoCopy
 {
   FileToMem txt_file;
   PrintFile out_file;
   
   DynArray<Rec<Crc> > rec_list;
   
  private:
  
   struct Split
    {
     StrLen name;
     StrLen rest;
     bool ok;
     
     explicit Split(StrLen txt)
      {
       for(StrLen r=txt; r.len>=2 ;++r)
         if( r[0]=='\r' && r[1]=='\n' )
           {
            name=txt.prefix(r);
            
            r+=2;
            
            rest=r;
            
            ok=true;
            
            return;
           }
           
       ok=false;    
      }
    };
  
   void fillList()
    {
     Printf(Con,"fill...");
     
     for(StrLen txt=Mutate<const char>(Range(txt_file)); +txt ;)
       {
        Split split(txt);
        
        if( split.ok )
          {
           rec_list.append_fill(split.name);
           
           txt=split.rest;
          }
        else
          {
           Printf(Con,"Warning : input file is not as expected\n");
           
           break;
          }  
       }
       
     Printf(Con," done\n");  
    }
    
   void sortList()
    {
     Printf(Con,"sort...");
     
     Sort(Range(rec_list));
       
     Printf(Con," done\n");  
    }
    
   template <class R> 
   ulen process(R list) 
    {
     ulen count=0;
     auto first_rec=*list;
    
     for(auto cur=list; +cur ;)
       {
        auto rec=*cur;
        
        count++;
        
        if( count>1 )
          {
           if( count==2 ) Printf(out_file,"#;\n",first_rec);
          
           Printf(out_file,"#;\n",rec);
          }
        
        for(++cur; +cur && !(rec<*cur) ;++cur);
       }
       
     if( count>1 )  
       {
        Printf(out_file,"\ncount = #;\n\n#;\n\n",count,TextDivider());
       }
       
     return count;  
    }
    
   void cutList()
    {
     Printf(Con,"cut...");
     
     Printf(out_file,"#;\n\n",TextDivider());
     
     ulen max_count=0;
     
     for(auto list=Range_const(rec_list); +list ;)
       {
        auto crc=list[0].crc;
        
        auto rest=list;
        
        for(++rest; +rest && rest->crc==crc ;++rest);
        
        ulen count=process(list.prefix(rest));
        
        Replace_max(max_count,count);
        
        list=rest;
       }
     
     Printf(Con," done\n\nmax_count = #;\n\n",max_count);  
     
     Printf(out_file,"max_count = #;\n",max_count);
    }
    
   void printList()
    {
     Printf(out_file,"name list #;\n\n",rec_list.getLen());
     
     for(auto r=Range_const(rec_list); +r ;++r)
       {
        Printf(out_file,"#;\n",*r);
       } 
    }
 
  public:
  
   Engine(const char *txt_file_name,const char *out_file_name)
    : txt_file(txt_file_name),
      out_file(out_file_name)
    {
    }
   
   ~Engine()
    {
    }
   
   void run()
    {
     fillList();
     
     sortList();
     
     cutList();
     
     //printList();
    }
 };
 
} // namespace Private_1012
 
using namespace Private_1012; 
 
/* Testit<1012> */ 

template<>
const char *const Testit<1012>::Name="Test1012 NamesCrc";

template<>
bool Testit<1012>::Main() 
 { 
  {
   Printf(Con,"Crc16 test\n\n");
 
   Engine<Crc16>("../../../HCore/files/NameList.txt","Crc16Test.txt").run();
  } 
 
  {
   Printf(Con,"Crc24 test\n\n");
 
   Engine<Crc24>("../../../HCore/files/NameList.txt","Crc24Test.txt").run();
  } 
 
  {
   Printf(Con,"Crc32 test\n\n");
 
   Engine<Crc32>("../../../HCore/files/NameList.txt","Crc32Test.txt").run();
  } 
 
  return true;
 }
 
} // namespace App
 
