CC = clang
include $(GNUSTEP_MAKEFILES)/common.make

PACKAGE_NAME = Higgs
VERSION = 0.1
TOOL_NAME = Main Blocktest DictionaryTest

Main_OBJC_FILES = main.m
Main_OBJCFLAGS = -fblocks -Icarulator/
Main_SUBPROJECTS = carulator

#TOOL_NAME = Blocktest
Blocktest_OBJC_FILES = blocktest.m
Blocktest_OBJCFLAGS = -fblocks

DictionaryTest_OBJC_FILES = dicttest.m
DictionaryTest_OBJCFLAGS = -fblocks

include $(GNUSTEP_MAKEFILES)/tool.make
