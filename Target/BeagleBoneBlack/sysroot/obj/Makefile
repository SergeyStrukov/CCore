OBJDUMP = /opt/BeagleBoneBlack/bin/arm-objdump.exe

all: string.txt string_c.txt

%.txt : %.o
	$(OBJDUMP) -xD $< > $@
