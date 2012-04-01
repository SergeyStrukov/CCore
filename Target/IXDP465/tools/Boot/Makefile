# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: IXDP465Boot 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2010 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../../..

CCORE_TARGET = WIN32

OBJ_PATH = obj

TARGET = $(HOME)/bin/IXDP465Boot.exe

include $(CCORE_ROOT)/Target/Makefile.app

boots: $(TARGET)
	$(TARGET) b 192.168.1.10 ../BootServer/main.exe





