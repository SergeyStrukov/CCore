# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: LR1Track 1.00
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../..

CCORE_TARGET = WIN32

OBJ_PATH = obj

TARGET = $(HOME)/bin/LR1Track.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	cd DDL && $(TARGET)
	cd AMP && $(TARGET)
