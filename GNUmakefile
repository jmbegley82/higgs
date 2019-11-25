CC = clang
include $(GNUSTEP_MAKEFILES)/common.make

PACKAGE_NAME = Higgs
VERSION = 0.1
TOOL_NAME = Main Blocktest DictionaryTest PthreadTest

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

include $(GNUSTEP_MAKEFILES)/tool.make
