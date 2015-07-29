# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: ShapeLab 1.00
#
#  Tag: VideoLabs
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2015 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

CCORE_TARGET = WIN32

OBJ_PATH = obj

SRC_PATH_LIST = .

TARGET = ShapeLab.exe

CCOPT_EXTRA = -I.

LDOPT_EXTRA = -lgdi32 $(OBJ_PATH)/Application.res -Wl,--subsystem,windows

$(TARGET) : $(OBJ_PATH)/Application.res

include $(CCORE_ROOT)/Target/Makefile.app

$(OBJ_PATH)/Application.res : res/Application.rc inc/Application.rh
	windres $(CCINC) -I. $< -O coff -o $@

run: $(TARGET)
	./$(TARGET)






