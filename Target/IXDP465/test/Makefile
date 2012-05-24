# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/IXDP465
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2010 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

CCORE_TARGET = IXDP465

SRC_PATH_LIST = . \
                $(CCORE_ROOT)/CCore/test \
                $(CCORE_ROOT)/XCore/CCore/test \
                $(CCORE_ROOT)/Target/$(CCORE_TARGET)/CCore/testip \
                $(CCORE_ROOT)/Target/$(CCORE_TARGET)/CCore/test

OBJ_PATH = ../test-obj

TARGET = main.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	IXDP465Boot.exe r 192.168.1.10 $(TARGET) && cd root && PTPServer.exe c
	
sim: $(TARGET)
	ARMGo.exe $(TARGET)
	
simlog: $(TARGET)
	ARMGo.exe $(TARGET) ARMLog.txt
	
