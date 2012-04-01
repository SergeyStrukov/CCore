# Makefile

CCORE_ROOT = ../../../..

CCORE_TARGET = WIN32

SRC_PATH_LIST = . $(CCORE_ROOT)/tools/LangLR1-tools/test

OBJ_PATH = obj

TARGET = main.exe

LANG = AMP

CCOPT_EXTRA = -D 'DEF_LANG=$(LANG)' -I .

include $(CCORE_ROOT)/Target/Makefile.app

run: $(TARGET)
	./$(TARGET)
