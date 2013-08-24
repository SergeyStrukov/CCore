# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CondLangLR1 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

include $(CCORE_ROOT)/Makefile.host

OBJ_PATH = obj

TARGET = ./BFTest.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	$(TARGET) ../AMP/AMP.ddl
	$(TARGET) ../DDL/DDL.ddl





