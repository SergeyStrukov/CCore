/* test0020.Crc.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/Crc.h>

namespace App {

/* Testit<20> */ 

template<>
const char *const Testit<20>::Name="Test20 Crc";

template<>
bool Testit<20>::Main() 
 { 
  {
   CrcTable<uint16,0xFFFF,0x1021> table;
   
   if( table.check(AlgoCrc16::Table) )
     {
      Printf(Con,"\n#;\n\n",table);
      
      Printf(Con,"Crc16 Ok\n");
     } 
   else
     {
      Printf(Con,"Crc16 Failed\n");
      
      return false;
     }  
  } 
  
  {
   CrcTable<uint32,0xFFFFFF,0x864CFB> table;
   
   if( table.check(AlgoCrc24::Table) )
     {
      Printf(Con,"\n#;\n\n",table);
      
      Printf(Con,"Crc24 Ok\n");
     } 
   else
     {
      Printf(Con,"Crc24 Failed\n");
      
      return false;
     }  
  }
 
  {
   CrcTable<uint32,0xFFFFFFFF,0x00A00805> table;
   
   if( table.check(AlgoCrc32::Table) )
     {
      Printf(Con,"\n#;\n\n",table);
      
      Printf(Con,"Crc32 Ok\n");
     } 
   else
     {
      Printf(Con,"Crc32 Failed\n");
      
      return false;
     }  
  } 
  
  return true;
 }
 
} // namespace App
 
