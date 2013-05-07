# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: DDLTypeSet 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

include $(CCORE_ROOT)/Makefile.host

OBJ_PATH = obj

TARGET = $(HOME)/bin/DDLTypeSet.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET) 
	$(TARGET) ../LangLR1-tools/StateTypes.ddl ../LangLR1-tools/StateTypes.TypeDef.gen.h ../LangLR1-tools/StateTypes.TypeSet.gen.h
	$(TARGET) ../LangLR1-tools/ShiftStateTypes.ddl ../LangLR1-tools/ShiftStateTypes.TypeDef.gen.h ../LangLR1-tools/ShiftStateTypes.TypeSet.gen.h






