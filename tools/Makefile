# Makefile
#----------------------------------------------------------------------------------------
#
#  License: Boost Software License - Version 1.0 - August 17th, 2003 
#
#            see http://www.boost.org/LICENSE_1_0.txt or the local copy
#
#  Copyright (c) 2010 Sergey Strukov. All rights reserved.
#
#----------------------------------------------------------------------------------------

OPT = -j 8

all:
	make $(OPT) -C EchoServer
	make $(OPT) -C MakeList
	make $(OPT) -C PTPEchoTest
	make $(OPT) -C Regen
	make $(OPT) -C PTPServer
	make $(OPT) -C exectest
	make $(OPT) -C FileMap
	make $(OPT) -C LangLR1
	make $(OPT) -C EllipticPi
	make $(OPT) -C ParserGen
	make $(OPT) -C ArmGo
	make $(OPT) -C DDLShow
	make $(OPT) -C DDLTypeSet

clean:
	make -C EchoServer   clean
#	make -C MakeList     clean
	make -C PTPEchoTest  clean
	make -C Regen        clean
	make -C PTPServer    clean
	make -C exectest     clean
	make -C FileMap      clean
	make -C LangLR1      clean
	make -C EllipticPi   clean
	make -C ParserGen    clean
	make -C ArmGo        clean
	make -C DDLShow      clean
	make -C DDLTypeSet   clean

list:
	make -C EchoServer   list
	make -C MakeList     list
	make -C PTPEchoTest  list
	make -C Regen        list
	make -C PTPServer    list
	make -C exectest     list
	make -C FileMap      list
	make -C LangLR1      list
	make -C EllipticPi   list
	make -C ParserGen    list
	make -C ArmGo        list
	make -C DDLShow      list
	make -C DDLTypeSet   list

