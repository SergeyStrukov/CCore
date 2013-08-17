/* test3002.WIN64.cpp */ 
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

#include <CCore/inc/win64/Win64.h>

#include <CCore/inc/sys/SysProp.h>

#include <windows.h>
#include <winsock2.h>

namespace App {

namespace Private_3002 {


} // namespace Private_3002
 
using namespace Private_3002; 
 
/* Testit<3002> */ 

template<>
const char *const Testit<3002>::Name="Test3002 WIN64";

template<>
bool Testit<3002>::Main() 
 {
#if 1

  Printf(Con,"#;\n",sizeof (Win64::Coord));
  Printf(Con,"#; #;\n",sizeof (COORD),
                       offsetof(COORD,X));

#endif

#if 1

  Printf(Con,"#;\n",sizeof (Win64::Overlapped));
  Printf(Con,"#; #; #; #;\n",sizeof (OVERLAPPED),
                             offsetof(OVERLAPPED,InternalHigh),
                             offsetof(OVERLAPPED,Pointer),
                             offsetof(OVERLAPPED,hEvent));

#endif

#if 1

  Printf(Con,"#;\n",MAXIMUM_WAIT_OBJECTS);
  Printf(Con,"#.h;\n",INFINITE);

#endif

#if 1

  Printf(Con,"#;\n",sizeof (Win64::ProcessInfo));
  Printf(Con,"#; #; #; #;\n",sizeof (PROCESS_INFORMATION),
                             offsetof(PROCESS_INFORMATION,hThread),
                             offsetof(PROCESS_INFORMATION,dwProcessId),
                             offsetof(PROCESS_INFORMATION,dwThreadId));                   

#endif

#if 1

  Printf(Con,"#;\n",sizeof (Win64::StartupInfo));
  Printf(Con,"#;\n",sizeof (STARTUPINFO));

#endif

#if 1

  Printf(Con,"#.h;\n",TLS_OUT_OF_INDEXES);

#endif

#if 1

  Printf(Con,"sizeof (LONG) = #;\n",sizeof (LONG));

#endif

#if 1

  Printf(Con,"ACP = #;\n",Win64::GetACP());

#endif

#if 1

  Printf(Con,"sizeof (SYSTEM_INFO) = #;\n",sizeof (SYSTEM_INFO));
  Printf(Con,"sizeof (Win64::SystemInfo) = #;\n",sizeof (Win64::SystemInfo));

  Printf(Con,"#; #;\n",Sys::GetCpuCount(),Sys::GetSpinCount());

#endif

#if 1

  {
   Win64::SystemInfo info;

   Win64::GetSystemInfo(&info);

   Printf(Con,"#.h;\n",info.page_len);

   Printf(Con,"#.h;\n",info.alloc_granularity);

   Printf(Con,"#.h;\n",(uptr)info.min_address);
   Printf(Con,"#.h;\n",(uptr)info.max_address);
  }

#endif

#if 1

  Printf(Con,"#.h;\n",(uptr)INVALID_HANDLE_VALUE);

#endif

#if 1

  Printf(Con,"#;\n",Win64::GetConsoleOutputCP());

  for(unsigned code=128; code<256 ;code++) Printf(Con,"#3r; #.c;\n",code,code);

#endif

#if 1

  {
   Printf(Con,"sizeof (INPUT_RECORD) = #;\n",sizeof (INPUT_RECORD));

   Printf(Con,"sizeof (Win64::ConInputRecord) = #;\n",sizeof (Win64::ConInputRecord));

   INPUT_RECORD rec;

   Printf(Con,"sizeof (rec.EventType) = #;\n",sizeof (rec.EventType));

   Printf(Con,"#;\n",offsetof(INPUT_RECORD,Event));
   Printf(Con,"#;\n",offsetof(Win64::ConInputRecord,event));
  } 

#endif

#if 1

  Printf(Con,"#;\n",sizeof (uint8));
  Printf(Con,"#;\n",sizeof (uint16));
  Printf(Con,"#;\n",sizeof (uint32));
  Printf(Con,"#;\n",sizeof (uint64));

#endif

#if 1

  Printf(Con,"sizeof (WSAEVENT) = #;\n",sizeof (WSAEVENT));

  Printf(Con,"WSA_MAXIMUM_WAIT_EVENTS = #;\n",WSA_MAXIMUM_WAIT_EVENTS);
  Printf(Con,"WSA_WAIT_FAILED = #.h;\n",WSA_WAIT_FAILED);
  Printf(Con,"WSA_WAIT_EVENT_0 = #;\n",WSA_WAIT_EVENT_0);
  Printf(Con,"WSA_WAIT_TIMEOUT = #;\n",WSA_WAIT_TIMEOUT);
  Printf(Con,"WSA_INFINITE = #.h;\n",WSA_INFINITE);

#endif

#if 1

  Printf(Con,"INVALID_FILE_ATTRIBUTES = #.h;\n",INVALID_FILE_ATTRIBUTES);
  Printf(Con,"GENERIC_READ = #.h;\n",GENERIC_READ);
  Printf(Con,"GENERIC_WRITE = #.h;\n",GENERIC_WRITE);
  Printf(Con,"DELETE = #.h;\n",DELETE);

#endif

#if 1

  Printf(Con,"sizeof (WIN32_FIND_DATA) = #;\n",sizeof (WIN32_FIND_DATA));
  Printf(Con,"sizeof (Win64::FindFileData) = #;\n",sizeof (Win64::FindFileData));

  Printf(Con,"#; #; #; #; #; #; #; #;\n",offsetof(WIN32_FIND_DATA,dwFileAttributes)
                                        ,offsetof(WIN32_FIND_DATA,ftCreationTime)
                                        ,offsetof(WIN32_FIND_DATA,ftLastAccessTime)
                                        ,offsetof(WIN32_FIND_DATA,ftLastWriteTime)
                                        ,offsetof(WIN32_FIND_DATA,nFileSizeHigh)
                                        ,offsetof(WIN32_FIND_DATA,nFileSizeLow)
                                        ,offsetof(WIN32_FIND_DATA,cFileName)
                                        ,offsetof(WIN32_FIND_DATA,cAlternateFileName));

#endif

#if 1

  Printf(Con,"SOCKET_ERROR = #;\n",SOCKET_ERROR);
  Printf(Con,"sizeof (GROUP) = #;\n",sizeof (GROUP));
  Printf(Con,"sizeof (SOCKET) = #;\n",sizeof (SOCKET));
  Printf(Con,"INVALID_SOCKET = #.h;\n",INVALID_SOCKET);
  Printf(Con,"FD_SETSIZE = #;\n",FD_SETSIZE);
  Printf(Con,"sizeof (WSABUF) = #;\n",sizeof (WSABUF));
  Printf(Con,"#;\n",offsetof(WSABUF,buf));
  Printf(Con,"sizeof (u_long) = #;\n",sizeof (u_long));
  Printf(Con,"sizeof (u_int) = #;\n",sizeof (u_int));
  Printf(Con,"sizeof (fd_set) = #;\n",sizeof (fd_set));

#endif
 
#if 1

  {
   Printf(Con,"sizeof (WSADATA) = #;\n",sizeof (WSADATA));
   Printf(Con,"sizeof (Win64::WSAInfo) = #;\n",sizeof (Win64::WSAInfo));

   Win64::WSAInfo info;

   if( Win64::WSAStartup(Win64::WSAVersion_2_00,&info) )
     {
      Printf(Con,"error\n");
     }
   else
     {
      Printf(Con,"version = #.h;\n",info.version);
      Printf(Con,"hi_version = #.h;\n",info.hi_version);
      Printf(Con,"desc = #;\n",info.desc);
      Printf(Con,"status = #;\n",info.status);
     }
  }

#endif

#if 1

  Printf(Con,"sizeof (sockaddr_in) = #;\n",sizeof (sockaddr_in));
  Printf(Con,"sizeof (u_long) = #;\n",sizeof (u_long));
  Printf(Con,"sizeof (__ms_u_long) = #;\n",sizeof (__ms_u_long));

#endif

  return true;
 }
 
} // namespace App
 
