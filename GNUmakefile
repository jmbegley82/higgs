-include GNUmakefile.preamble

include $(GNUSTEP_MAKEFILES)/common.make

PACKAGE_NAME = Higgs
VERSION = 0.1
TOOL_NAME = Blocktest DictionaryTest PthreadTest GfxTest TacoIsland \
	    AsyncDemo VBODemo GTest1

#TOOL_NAME = Blocktest
Blocktest_OBJC_FILES = blocktest.m
Blocktest_OBJCFLAGS = -fblocks

DictionaryTest_OBJC_FILES = Plist.m dicttest.m
DictionaryTest_OBJCFLAGS =

PthreadTest_C_FILES = PthreadTest/main.c
PthreadTest_CFLAGS = -pthread

GfxTest_CC_FILES = GfxTest/LUtil.cpp GfxTest/main.cpp
GfxTest_CCFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
GfxTest_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut ${JMLDFLAGS}

TacoIsland_C_FILES = TacoIsland/main.c
TacoIsland_CFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
TacoIsland_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut ${JMLDFLAGS}

AsyncDemo_C_FILES = AsyncDemo/FieldMgr.c AsyncDemo/main.c
AsyncDemo_CFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
AsyncDemo_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut ${JMLDFLAGS}

VBODemo_C_FILES = VBODemo/FieldMgr.c VBODemo/main.c
VBODemo_CFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
VBODemo_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut -lGLEW -lIL -lILU ${JMLDFLAGS}

GTest1_C_FILES = GameCommon/main.c
GTest1_CFLAGS = -I/usr/local/include ${JMCFLAGS}
GTest1_CPPFLAGS =
GTest1_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut -lGLEW -lIL -lILU ${JMLDFLAGS}
GTest1_SUBPROJECTS = GameCommon

include $(GNUSTEP_MAKEFILES)/tool.make
