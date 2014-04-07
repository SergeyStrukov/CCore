# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  Tag: Target/Vanilla-X
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2011 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

XCORE_ROOT = ../../..

XCORE_TARGET = Vanilla-X

# CC tool

CC = /opt/gcc-4.7.1-cross/armeb/bin/arm-gcc-4.7.1

NOWARN = -Wno-non-virtual-dtor -Wno-switch

CCINC = -I$(XCORE_ROOT)/Target/$(XCORE_TARGET)

CCOPT = -c -O3 -std=c++0x -mbig-endian -Wall -Wextra $(NOWARN) $(CCINC) -D__STDBUILD

CCOPT_C = -c -O3 -mbig-endian -Wall -Wextra $(CCINC) -D__STDBUILD

# AS tool

AS = /opt/gcc-4.7.1-cross/armeb/bin/arm-as

ASOPT = -mcpu=xscale -EB

# AR tool

AR = /opt/gcc-4.7.1-cross/armeb/bin/arm-ar

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
           obj/setjmp.o      \

# deps

all: lib/libc.a

clean:
	$(RM) $(OBJ_LIST) lib/libc.a

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





