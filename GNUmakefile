CC = clang
include $(GNUSTEP_MAKEFILES)/common.make

PACKAGE_NAME = Higgs
VERSION = 0.1
TOOL_NAME = Main Blocktest DictionaryTest PthreadTest GfxTest TacoIsland

Main_OBJC_FILES = main.m
Main_OBJCFLAGS = -Icarulator/
Main_SUBPROJECTS = carulator

#TOOL_NAME = Blocktest
Blocktest_OBJC_FILES = blocktest.m
Blocktest_OBJCFLAGS = -fblocks

DictionaryTest_OBJC_FILES = Plist.m dicttest.m
DictionaryTest_OBJCFLAGS =

PthreadTest_C_FILES = PthreadTest/main.c
PthreadTest_CFLAGS = -pthread

#GfxTest_C_FILES = GfxTest/main.c
#GfxTest_CFLAGS = -pthread -I/usr/local/include -g
#GfxTest_LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image
GfxTest_CC_FILES = GfxTest/LUtil.cpp GfxTest/main.cpp
GfxTest_CCFLAGS = -pthread -I/usr/local/include -g
GfxTest_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut

TacoIsland_C_FILES = TacoIsland/main.c
TacoIsland_CFLAGS = -pthread -I/usr/local/include -g
TacoIsland_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut

include $(GNUSTEP_MAKEFILES)/tool.make
