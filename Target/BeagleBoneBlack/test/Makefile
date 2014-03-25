# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.08
#
#  Tag: Target/BeagleBoneBlack
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2014 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

CCORE_ROOT = ../../..

CCORE_TARGET = BeagleBoneBlack

SRC_PATH_LIST = . \
                $(CCORE_ROOT)/CCore/test \
                $(CCORE_ROOT)/XCore/CCore/test \
                $(CCORE_ROOT)/Target/$(CCORE_TARGET)/CCore/testip \
                $(CCORE_ROOT)/Target/$(CCORE_TARGET)/CCore/test

OBJ_PATH = ../test-obj

TARGET = main.exe

include $(CCORE_ROOT)/Target/Makefile.app

#run: $(TARGET)
#	BeagleBoot.exe r 192.168.1.10 $(TARGET) && cd root && PTPServer.exe c
	
run: $(TARGET)
	ELFtoUboot.exe $(TARGET) D:/Tools/TFTPD64/bootfile

OBJDUMP = /opt/BeagleBoneBlack/bin/arm-objdump.exe

txt: $(TARGET)
	$(OBJDUMP) -xD $(TARGET) > main.exe.txt

