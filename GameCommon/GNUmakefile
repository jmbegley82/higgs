-include GNUmakefile.preamble
include $(GNUSTEP_MAKEFILES)/common.make

CC = clang

SUBPROJECT_NAME = GameCommon

GameCommon_C_FILES = Debug.c Cel.c CelSet.c AnimationSet.c Sprite.c FieldMgr.c
GameCommon_CFLAGS = -I/usr/local/include ${JMCFLAGS}
GameCommon_CPPFLAGS = ${JMCPPFLAGS}
GameCommon_LDFLAGS = ${JMLDFLAGS}

include $(GNUSTEP_MAKEFILES)/subproject.make
