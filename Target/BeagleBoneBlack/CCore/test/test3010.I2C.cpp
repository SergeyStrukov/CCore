/* test3010.I2C.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.08
//
//  Tag: Target/BeagleBoneBlack 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2014 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/dev/DevI2C.h>
#include <CCore/inc/dev/AM3359.CONTROL.h>
#include <CCore/inc/UIntSplit.h>

namespace App {

namespace Private_3010 {

class Test : NoCopy
 {
   Dev::I2C dev;
   
  public:
 
   Test()
    : dev(Dev::I2C_0) 
    {
     dev.enable();
    
     dev.reset();
     
     using namespace AM3359::CONTROL;
      
     Bar bar;
      
     Printf(Con,"Conf_I2C0_SDA = #;\n\n",bar.get_Conf_I2C0_SDA());
     Printf(Con,"Conf_I2C0_SCL = #;\n\n",bar.get_Conf_I2C0_SCL());
     
     dev.init();
    }
   
   ~Test()
    {
    }
   
   void setSlave(uint8 address)
    { 
     dev.setSlave7(address); 
    }
   
   bool tryRead(uint8 address,PtrLen<uint8> buf)
    {
     return dev.tryExchange(Range_const(&address,1),buf);
    }
   
   void read(uint16 address,PtrLen<uint8> buf)
    {
     UIntSplit<uint16,uint8> split;
     
     split.set(address);
     
     uint8 temp[2]={split[0],split[1]};

     dev.exchange(Range_const(temp),buf);
    }
 };

} // namespace Private_3010
 
using namespace Private_3010; 
 
/* Testit<3010> */ 

template<>
const char *const Testit<3010>::Name="Test3010 I2C";

template<>
bool Testit<3010>::Main() 
 {
  Test test;
  
  uint8 buf[128]={};
  
  for(unsigned a=0; a<128 ;a++)
    {
     test.setSlave(uint8(a));
   
     if( test.tryRead(0,Range(buf,1)) )
       {
        Printf(Con,"address = #2.16i; byte = #2.16i;\n",a,buf[0]);
       }
    }
  
  test.setSlave(0x50);

  test.read(0,Range(buf,128));
 
  Printf(Con,"\n#;\n",PrintDump(Range(buf)));
  
  Printf(Con,"#;\n",StrLen(Mutate<char>(Range(buf+4,21))));
  
  Printf(Con,"#;\n",StrLen(Mutate<char>(Range(buf+48,16))));
  
  return true;
 }
 
} // namespace App
 
