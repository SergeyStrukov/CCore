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

all:
	make -C EchoServer
	make -C MakeList
	make -C PTPEchoTest
	make -C Regen
	make -C PTPServer
	make -C exectest
	make -C FileMap
	make -C LangLR1
	make -C EllipticPi
	make -C ParserGen

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

