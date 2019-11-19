CC = clang
include $(GNUSTEP_MAKEFILES)/common.make

TOOL_NAME = Main Blocktest

Main_OBJC_FILES = main.m
Main_OBJCFLAGS = -fblocks -Icarulator/
Main_SUBPROJECTS = carulator

#TOOL_NAME = Blocktest
Blocktest_OBJC_FILES = blocktest.m
Blocktest_OBJCFLAGS = -fblocks

include $(GNUSTEP_MAKEFILES)/tool.make
