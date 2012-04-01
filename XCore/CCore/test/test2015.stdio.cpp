/* test2015.stdio.cpp */ 
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

#include <CCore/test/test.h>

#include <CCore/inc/StdioReadCon.h>

#include <stdio.h>

namespace App {

namespace Private_2015 {


} // namespace Private_2015
 
using namespace Private_2015; 
 
/* Testit<2015> */ 

template<>
const char *const Testit<2015>::Name="Test2015 stdio";

template<>
bool Testit<2015>::Main() 
 {
  for(unsigned i=1; i<=1000 ;i++) printf("--- %10u ------------------------\n",i);

  printf("ushort = %hu\nuchar = %hhu\n",(unsigned short)12345,(unsigned char)123);
  
  printf("long = %ld\nlong long = %lld\n",1234567890l,1234567890123456ll);
  
  StdioReadCon stdio_read_con;
  
  int count=0;
  
#if 1
  {
   char buf[3];
   char buf1[10];
  
   int nitem=scanf(" test%3c%9s%n",buf,buf1,&count);
  
   printf("buf = %.3s\n",buf);
   printf("buf1 = %s\n",buf1);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif  
  
#if 1
  {
   short dval=0;
  
   int nitem=scanf("%hd%n",&dval,&count);
  
   printf("dval = %hd\n",dval);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif  
  
#if 1
  {
   unsigned short dval=0;
  
   int nitem=scanf("%3hu%n",&dval,&count);
  
   printf("dval = %hu\n",dval);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif
  
#if 1
  {  
   unsigned short dval=0;
  
   int nitem=scanf("%3ho%n",&dval,&count);
  
   printf("dval = %ho\n",dval);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif
  
#if 1
  {
   unsigned short dval=0;
  
   int nitem=scanf("%3hx%n",&dval,&count);
  
   printf("dval = %hx\n",dval);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif

#if 1
  {
   unsigned short dval=0;
  
   int nitem=scanf("%3hi%n",&dval,&count);
  
   printf("dval = %hx\n",dval);
  
   printf("count = %d nitem = %d\n",count,nitem);
  }
#endif
  
#if 0
  
  for(;;)
    {
     char buf[100];
     
     char *str=fgets(buf,DimOf(buf),stdin);

     if( str )
       {
        printf("str = %s",str);
       }
     else
       {
        printf("str = nothing\n");
        
        clearerr(stdin);
       }
    }
  
#endif  
  
  return true;
 }
 
} // namespace App
 
