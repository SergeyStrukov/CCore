/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: DrawLab 1.00
//
//  Tag: private
//
//  License: proprietary software, don't distribute!
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>
#include <inc/Application.rh>

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Abort.h>

#include <CCore/inc/win32/Win32gui.h>

/* using */

using namespace CCore::Video;

/* WinMain() */ 

DesktopConfig AppDesktopConfig={IDI_APP,IDI_SMALL_APP};

const CCore::AbortMsgFuncType CCore::AbortMsgFunc = AbortMsgBox ;

extern "C" int WIN32_CALLTYPE WinMain(Win32::HModule,Win32::HModule,char *,unsigned cmd_show)
 {
  return App::Main(MapCmdShow(cmd_show)); 
 }
 
 


