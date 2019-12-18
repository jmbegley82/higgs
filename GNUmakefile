-include GNUmakefile.preamble

#JMCFLAGS =
#-fprofile-instr-generate -fcoverage-mapping -fsanitize=address -fno-omit-frame-pointer
#JMLDFLAGS =
#-fprofile-instr-generate -fsanitize=address -fno-omit-frame-pointer -lcxxrt

include $(GNUSTEP_MAKEFILES)/common.make

PACKAGE_NAME = Higgs
VERSION = 0.1
TOOL_NAME = Main Blocktest DictionaryTest PthreadTest GfxTest TacoIsland \
	    AsyncDemo VBODemo FieldTest

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
#GfxTest_CFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
#GfxTest_LDFLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image
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

FieldTest_C_FILES = FieldTest/Cel.c FieldTest/CelSet.c FieldTest/AnimationSet.c \
		    FieldTest/Sprite.c FieldTest/FieldMgr.c FieldTest/main.c
FieldTest_CFLAGS = -pthread -I/usr/local/include ${JMCFLAGS}
FieldTest_LDFLAGS = -L/usr/local/lib -lGL -lGLU -lglut -lGLEW -lIL -lILU ${JMLDFLAGS}

include $(GNUSTEP_MAKEFILES)/tool.make
