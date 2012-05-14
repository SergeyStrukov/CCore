# Makefile
#----------------------------------------------------------------------------------------
#
#  Project: CCore 1.02
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2011 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

all:
	make $(OPT) -C Target/Win32
	make $(OPT) -C Target/Win32/test
	make $(OPT) -C tools
	make $(OPT) -C Target/IXDP465
	make $(OPT) -C Target/IXDP465/test
	make $(OPT) -C Target/IXDP465/test2
	make $(OPT) -C Target/IXDP465/tools
	make $(OPT) -C Target/Vanilla-H
	make $(OPT) -C Target/Vanilla-H/test
	make $(OPT) -C Target/Vanilla-X
	make $(OPT) -C Target/Vanilla-X/test

warn:
	make 2> warn.txt

notest:
	make -C Target/Win32
	make -C tools
	make -C Target/IXDP465
	make -C Target/IXDP465/tools

clean:
	make -C Target/Win32          clean
	make -C Target/Win32/test     clean
	make -C tools                 clean
	make -C Target/IXDP465        clean
	make -C Target/IXDP465/test   clean
	make -C Target/IXDP465/test2  clean
	make -C Target/IXDP465/tools  clean
	make -C Target/Vanilla-H      clean
	make -C Target/Vanilla-H/test clean
	make -C Target/Vanilla-X      clean
	make -C Target/Vanilla-X/test clean

list:
	make -C Target/Win32          list
	make -C Target/Win32/test     list
	make -C tools                 list
	make -C Target/IXDP465        list
	make -C Target/IXDP465/test   list
	make -C Target/IXDP465/test2  list
	make -C Target/IXDP465/tools  list
	make -C Target/Vanilla-H      list
	make -C Target/Vanilla-H/test list
	make -C Target/Vanilla-X      list
	make -C Target/Vanilla-X/test list

src:
	find . -name *.h > txt/h-list.txt
	find . -name *.cpp > txt/cpp-list.txt
	find . -name *.s > txt/s-list.txt

svnclean:
	find . -type d -name .svn -exec rm -r -f '{}' \;
