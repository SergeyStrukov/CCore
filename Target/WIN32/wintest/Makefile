# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.09
#
#  Tag: Target/WIN32
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

CCORE_TARGET = WIN32

SRC_PATH_LIST = .

OBJ_PATH = ../wintest-obj

TARGET = main.exe

LDOPT_EXTRA = -lgdi32 $(OBJ_PATH)/main.res -Wl,--subsystem,windows

main.exe : $(OBJ_PATH)/main.res

include $(CCORE_ROOT)/Target/Makefile.app

$(OBJ_PATH)/main.res : main.rc main.rh
	windres $(CCINC) $< -O coff -o $@

run: $(TARGET)
	./$(TARGET)






