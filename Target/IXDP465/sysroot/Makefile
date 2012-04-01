# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/IXDP465
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2009 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

XCORE_ROOT = ../../..

XCORE_TARGET = IXDP465

# CC tool

CC = /opt/crosstool/armeb/bin/arm-gcc-4.7.0

NOWARN = -Wno-non-virtual-dtor -Wno-switch

CCINC = -I$(XCORE_ROOT)/Target/$(XCORE_TARGET)

CCOPT = -c -O3 -std=c++11 -mbig-endian -Wall -Wextra $(NOWARN) $(CCINC) -D__STDBUILD

CCOPT_C = -c -O3 -mbig-endian -Wall -Wextra $(CCINC) -D__STDBUILD

# AS tool

AS = /opt/crosstool/armeb/bin/arm-as

ASOPT = -mcpu=xscale -EB

# AR tool

AR = /opt/crosstool/armeb/bin/arm-ar

# RM tool

RM = rm -f

# obj list

OBJ_LIST = obj/ctype.o       \
           obj/string_c.o    \
           obj/__std_init.o  \
           obj/errno.o       \
           obj/locale.o      \
           obj/stdlib.o      \
           obj/string.o      \
           obj/time.o        \
           obj/consts.o      \
           obj/setjmp.o      \
           obj/string_s.o    \

# deps

all: lib/libc.a lib/crt0.o

clean:
	$(RM) $(OBJ_LIST) lib/libc.a lib/crt0.o

install: all
	cp -r -v ./lib /opt/crosstool/armeb/sysroot
	cp -r -v ./usr /opt/crosstool/armeb/sysroot

lib/libc.a : $(OBJ_LIST)
	$(RM) $@
	$(AR) -r $@ $(OBJ_LIST)

obj/%.o : src/%.cpp
	$(CC) $(CCOPT) $< -o $@

obj/%.o : src/%.c
	$(CC) $(CCOPT_C) $< -o $@

obj/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@

lib/%.o : src/%.s
	$(AS) $(ASOPT) $< -o $@





