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

XCORE_ROOT = ../../..

XCORE_TARGET = BeagleBoneBlack

# CC tool

CC = /opt/BeagleBoneBlack/bin/arm-gcc.exe

NOWARN = -Wno-non-virtual-dtor -Wno-switch

CCINC = -I$(XCORE_ROOT)/Target/$(XCORE_TARGET)

CCOPT = -c -std=c++11 -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard -mno-unaligned-access -O3 -Wall -Wextra $(NOWARN) $(CCINC) -D__STDBUILD

CCOPT_C = -c -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard -mno-unaligned-access -O3 -Wall -Wextra $(CCINC) -D__STDBUILD

# AS tool

AS = /opt/BeagleBoneBlack/bin/arm-as.exe

ASOPT = -march=armv7-a -mfpu=vfpv3 -mfloat-abi=hard

# AR tool

AR = /opt/BeagleBoneBlack/bin/arm-ar.exe

# RM tool

RM = rm -f

# obj list

OBJ_LIST = obj/ctype.o       \
           obj/string_c.o    \
           obj/errno.o       \
           obj/locale.o      \
           obj/stdlib.o      \
           obj/string.o      \
           obj/time.o        \
           obj/consts.o      \
           obj/string_s.o    \

# deps

all: lib/libc.a lib/libm.a lib/crt0.o

clean:
	$(RM) $(OBJ_LIST) lib/libc.a lib/libm.a lib/crt0.o

install: all
	cp -r -v ./lib /opt/BeagleBoneBlack/sysroot
	cp -r -v ./usr /opt/BeagleBoneBlack/sysroot

lib/libc.a : $(OBJ_LIST)
	$(RM) $@
	$(AR) -r $@ $(OBJ_LIST)

lib/libm.a :
	$(RM) $@
	$(AR) -r $@ 

obj/%.o : src/%.cpp
	$(CC) $(CCOPT) $< -o $@

obj/%.o : src/%.c
	$(CC) $(CCOPT_C) $< -o $@

obj/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@

lib/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@





