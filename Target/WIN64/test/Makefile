# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.06
#
#  Tag: Target/WIN64
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2013 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

CCORE_TARGET = WIN64

SRC_PATH_LIST = . \
                $(CCORE_ROOT)/CCore/test \
                $(CCORE_ROOT)/HCore/CCore/test \
                $(CCORE_ROOT)/Target/$(CCORE_TARGET)/CCore/test

OBJ_PATH = ../test-obj

TARGET = main.exe

include $(CCORE_ROOT)/Target/Makefile.app

run: main.exe
	./main.exe
