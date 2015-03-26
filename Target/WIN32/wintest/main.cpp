/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.09
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003 
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Abort.h>

#include <CCore/inc/win32/Win32gui.h>

#include "main.rh"

/* using */

using namespace CCore::Video;

/* main functions */

namespace App1 { int testmain(CmdDisplay cmd_display); }
 
namespace App2 { int testmain(CmdDisplay cmd_display); }

namespace App3 { int testmain(CmdDisplay cmd_display); }

namespace App4 { int testmain(CmdDisplay cmd_display); }

namespace App5 { int testmain(CmdDisplay cmd_display); }

/* WinMain() */ 

DesktopConfig AppDesktopConfig={IDI_APP,IDI_SMALL_APP};

const CCore::AbortMsgFuncType CCore::AbortMsgFunc = AbortMsgBox ;

extern "C" int WIN32_CALLTYPE WinMain(Win32::HModule,Win32::HModule,char *,unsigned cmd_show)
 {
  return App5::testmain(MapCmdShow(cmd_show)); 
 }
 
 


