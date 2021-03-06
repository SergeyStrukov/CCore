/* test3001.LIN64.cpp */ 
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.05
//
//  Tag: Target/LIN64 
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2013 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/sys/SysProp.h>

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <termios.h>
#include <semaphore.h>

namespace App {

namespace Private_3001 {

void PrintClockRes(clockid_t clock_id,const char *name)
 {
  timespec res;

  if( clock_getres(clock_id,&res)==-1 )
    {
     Printf(Con,"#; : resolution is not available\n",name);
    }
  else
    {
     Printf(Con,"#; : #; sec #; nsec\n",name,res.tv_sec,res.tv_nsec);
    }
 }

} // namespace Private_3001
 
using namespace Private_3001; 
 
/* Testit<3001> */ 

template<>
const char *const Testit<3001>::Name="Test3001 LIN64";

template<>
bool Testit<3001>::Main() 
 {
  Printf(Con,"off_t bits = #;\n",Meta::UIntBits<Meta::SIntToUInt<off_t>::UType>::Ret);
  
  Printf(Con,"pthread_t bits = #;\n",Meta::UIntBits<pthread_t>::Ret);
  
  Printf(Con,"alignof(long long) = #;\n",alignof(long long));
  
  Printf(Con,"alignof(long) = #;\n",alignof(long));
  
  Printf(Con,"alignof(int) = #;\n",alignof(int));
  
  Printf(Con,"alignof(double) = #;\n",alignof(double));
  
  Printf(Con,"alignof(int *) = #;\n",alignof(int *));
  
  Printf(Con,"alignof(long double) = #;\n",alignof(long double));
  
  Printf(Con,"max_align = #;\n",alignof(std::aligned_storage<1024>::type));
  
  uint64 value=0x1122334455667788ull;
  uint8 dst[8];
  
  memcpy(dst,&value,sizeof value);
  
  Printf(Con,"endian #;\n",PrintDump(Range(dst)));
  
  Printf(Con,"SEM_VALUE_MAX = #;\n",SEM_VALUE_MAX);
  
  Printf(Con,"CLOCKS_PER_SEC = #;\n",CLOCKS_PER_SEC);
  
  PrintClockRes(CLOCK_REALTIME,"CLOCK_REALTIME");
  PrintClockRes(CLOCK_PROCESS_CPUTIME_ID,"CLOCK_PROCESS_CPUTIME_ID");
  
  Printf(Con,"sizeof (struct termios) = #;\n",sizeof (struct termios));
  Printf(Con,"sizeof (sem_t) = #;\n",sizeof (sem_t));
  
  Printf(Con,"CPU Count = #;\n",sysconf(_SC_NPROCESSORS_ONLN));
  
  Printf(Con,"GetCpuCount = #;\n",Sys::GetCpuCount());
  Printf(Con,"GetSpinCount = #;\n",Sys::GetSpinCount());
  
  return true;
 }
 
} // namespace App
 
