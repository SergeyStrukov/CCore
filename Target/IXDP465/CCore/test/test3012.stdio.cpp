/* test3012.stdio.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/testip/testip.h>

#include <stdio.h>

namespace App {

namespace Private_3012 {


} // namespace Private_3012
 
using namespace Private_3012; 
 
/* Testit<3012> */ 

template<>
const char *const Testit<3012>::Name="Test3012 stdio";

template<>
bool Testit<3012>::Main() 
 { 
  IPEngine ip_engine;
  
  HostEngine host_engine(Net::UDPoint(192,168,1,1,Net::PTPServerUDPort));
  
  for(int i=0; i<10 ;i++) printf("--- %d ---\n",i);
  
  FILE *f=fopen("host:test.txt","w");
  
  if( !f ) return false;
  
  for(int i=0; i<10000 ;i++) fprintf(f,"--- %d -----------------------------------\n",i);
  
  fclose(f);
  
  rename("host:test.txt","host:test1.txt");
  
  remove("host:test1.txt");
  
  f=fopen("host:testa.txt","a");
  
  if( !f ) return false;
  
  for(int i=0; i<10000 ;i++) fprintf(f,"--- %d -----------------------------------\n",i);
  
  fclose(f);
  
  return true;
 }
 
} // namespace App
 
