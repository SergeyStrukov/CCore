# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: ARMGo 0.50
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2012 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

OBJ_PATH = obj

TARGET = $(HOME)/bin/ARMGo.exe

CCOPT_EXTRA = -I.

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	$(TARGET) $(CCORE_ROOT)/Target/IXDP465/test/main.exe # ARMLog.txt


