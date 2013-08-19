/* test3009.SysFile.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.06
//
//  Tag: Target/WIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/sys/SysFile.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_3009 {

/* class File */

class File : NoCopy
 {
   Sys::File file;
 
  public:
 
   explicit File(StrLen file_name,bool write=false) 
    { 
     auto fe=file.open(file_name,write?(Open_Write|Open_Create|Open_Erase):(Open_Read));
     
     if( fe ) Printf(Exception,"open() : #;",fe);
    }
   
   ~File() 
    { 
     FileMultiError errout;
     
     file.close(errout);
     
     if( +errout ) Printf(NoException,"close() : #;",errout);
    }
   
   void write(PtrLen<const uint8> data) 
    {  
     auto result=file.write(data.ptr,data.len);
     
     if( result.error ) Printf(Exception,"write() : #;",result.error);
     
     if( result.len!=data.len  ) Printf(Exception,"write() : len mismatch");
    }
   
   void read(PtrLen<uint8> data)
    {
     auto result=file.read(data.ptr,data.len);
     
     if( result.error ) Printf(Exception,"read() : #;",result.error);
     
     if( result.len!=data.len  ) Printf(Exception,"read() : len mismatch");
    }
 };

/* class AltFile */

class AltFile : NoCopy
 {
   Sys::AltFile file;
 
  public:
 
   explicit AltFile(StrLen file_name,bool write=false) 
    { 
     auto fe=file.open(file_name,write?(Open_Write|Open_Create|Open_Erase):(Open_Read)).error;
     
     if( fe ) Printf(Exception,"open() : #;",fe);
    }
   
   ~AltFile() 
    { 
     FileMultiError errout;
     
     file.close(errout);
     
     if( +errout ) Printf(NoException,"close() : #;",errout);
    }
   
   void write(PtrLen<const uint8> data) 
    {  
     auto result=file.write(0,data.ptr,data.len);
     
     if( result.error ) Printf(Exception,"write() : #;",result.error);
    }
   
   void read(PtrLen<uint8> data)
    {
     auto fe=file.read(0,data.ptr,data.len);
     
     if( fe ) Printf(Exception,"read() : #;",fe);
    }
 };

} // namespace Private_3009
 
using namespace Private_3009; 
 
/* Testit<3009> */ 

template<>
const char *const Testit<3009>::Name="Test3009 SysFile";

template<>
bool Testit<3009>::Main() 
 {
  Random random;
  
  // 1
  
  for(ulen rep=100; rep ;rep--)
    {
     ulen len=random.select(2000,10000)*1000;
     
     DynArray<uint8> wbuf(DoRaw{len});
     DynArray<uint8> rbuf(DoRaw{len});
     
     random.fill(Range(wbuf));

     {
      File file("test.tmp",true);
       
      file.write(Range_const(wbuf));
     }

     {
      File file("test.tmp");
      
      file.read(Range(rbuf));
     } 
     
     if( !Range_const(wbuf).equal(Range_const(rbuf)) )
       {
        Printf(Con,"Sys::File test failed\n");
       
        return false;
       }
    } 
  
  // 2
  
  for(ulen rep=100; rep ;rep--)
    {
     ulen len=random.select(2000,10000)*1000;
     
     DynArray<uint8> wbuf(DoRaw{len});
     DynArray<uint8> rbuf(DoRaw{len});
     
     random.fill(Range(wbuf));

     {
      AltFile file("test.tmp",true);
       
      file.write(Range_const(wbuf));
     }

     {
      AltFile file("test.tmp");
      
      file.read(Range(rbuf));
     } 
     
     if( !Range_const(wbuf).equal(Range_const(rbuf)) )
       {
        Printf(Con,"Sys::AltFile test failed\n");
       
        return false;
       }
    }
  
  return true;
 }
 
} // namespace App
 
