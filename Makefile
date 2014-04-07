# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.08
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2014 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

all:
	make $(OPT) -C Target/Win32
	make $(OPT) -C Target/Win32/test
	make        -C tools

warn:
	make 2> warn.txt

clean:
	make -C Target/Win32          clean
	make -C Target/Win32/test     clean
	make -C tools                 clean

list:
	make -C Target/Win32                 list
	make -C Target/Win32/test            list
	make -C Target/WIN64                 list
	make -C Target/WIN64/test            list
	make -C Target/LIN64                 list
	make -C Target/LIN64/test            list
	make -C Target/Vanilla-H             list
	make -C Target/Vanilla-H/test        list
	make -C Target/Vanilla-X             list
	make -C Target/Vanilla-X/test        list
	make -C Target/IXDP465               list
	make -C Target/IXDP465/test          list
	make -C Target/IXDP465/test2         list
	make -C Target/IXDP465/tools         list
	make -C Target/BeagleBoneBlack       list
	make -C Target/BeagleBoneBlack/test  list
	make -C tools                        list


