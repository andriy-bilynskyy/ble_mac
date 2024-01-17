#*******************************************************************************
#*
#*  (C) 2024 Andrii Bilynskyi <andriy.bilynskyy@gmail.com>
#*
#*  This code is licensed under the GPLv3.
#*
#*******************************************************************************

CC      := gcc
CXX     := g++
AS      := gcc

STYLE   := astyle
CHECK   := cppcheck

#*******************************************************************************
# Project name
#*******************************************************************************
PROJECT ?= ble_mac

#*******************************************************************************
# Project sources
#*******************************************************************************
PROJECT_SRC := \
  ./main.c \
  ./ble_mac_src/ble_mac.c \
  ./ble_mac_src/ble_mac_ext.c \
  ./tiny_aes_c/aes.c \

#*******************************************************************************
# Project include paths
#*******************************************************************************
PROJECT_INC := \
  ./ \
  ./ble_mac_src \
  ./tiny_aes_c \

#*******************************************************************************
# Project libraries
#*******************************************************************************
PROJECT_LIB := \

PROJECT_LIB_PATH := \

#*******************************************************************************
# Project files for static analyse and formatting
#*******************************************************************************
PROJECT_STYLE := \
  ./main.c \
  ./ble_mac_src/ble_mac.c ./ble_mac_src/ble_mac.h \
  ./ble_mac_src/ble_mac_ext.c ./ble_mac_src/ble_mac_ext.h \


#*******************************************************************************
# Do not modify
#*******************************************************************************
CFLAGS   := -Wall -std=c99 -fdata-sections -ffunction-sections
ASFLAGS  := -Wall -std=c99 -fdata-sections -ffunction-sections
CXXFLAGS := -Wall -fno-exceptions -fdata-sections -ffunction-sections

LDFLAGS := -fdata-sections -ffunction-sections
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Xlinker -Map=${PROJECT}.map
LDFLAGS += ${addprefix -l, ${PROJECT_LIB}}
LDFLAGS += ${addprefix -L, ${PROJECT_LIB_PATH}}


OBJECTS := ${addsuffix .o, ${PROJECT_SRC}}

ifndef BUILD
  BUILD := RELEASE
endif

ifeq (${BUILD},DEBUG)
  CFLAGS  += -g3 -O1 -DDEBUG
  ASFLAGS += -g3 -O1 -DDEBUG
  CXXFLAGS += -g3 -O1 -DDEBUG
else ifeq (${BUILD},RELEASE)
  CFLAGS  += -g0 -O3
  ASFLAGS += -g0 -O3
  CXXFLAGS += -g0 -O3
else
  ${error Wrong BUILD '${BUILD}'! Should be: DEBUG or RELEASE}
endif

CFLAGS  += ${addprefix -I, ${PROJECT_INC}}
ASFLAGS  += ${addprefix -I, ${PROJECT_INC}}
CXXFLAGS  += ${addprefix -I, ${PROJECT_INC}}

.PHONY: all build clean run style check help

all: ${PROJECT}

build: ${PROJECT}

${PROJECT}: ${OBJECTS} ${LD_SCRIPT}
	${info ${BUILD} BUILD}
	${CXX} ${OBJECTS} -o $@ ${LDFLAGS}

%.c.o: %.c
	${CC} ${CFLAGS} -MD -c $< -o $@

%.S.o: %.S
	${AS} ${ASFLAGS} -MD -c $< -o $@

%.cpp.o: %.cpp
	${CXX} ${CXXFLAGS} -MD -c $< -o $@

clean:
	rm -f ${OBJECTS} ${OBJECTS:.o=.d} ${PROJECT}

run:
	@if [ -f "${PROJECT}" ];                                                        \
    then                                                                            \
        "./${PROJECT}"                                                              \
    else                                                                            \
        echo "Output executable file doesn't exist. Run 'make all' before!";        \
    fi                                                                              \

style:
	${STYLE} --style=linux --lineend=linux --suffix=none                            \
           --indent=force-tab=4 --indent-after-parens --indent-continuation=1       \
           --pad-header --pad-comma --unpad-paren --max-code-length=100             \
           ${PROJECT_STYLE}                                                         \

check:
	${CHECK} -q --enable=style,performance,portability,information                  \
                --force --inconclusive --inline-suppr ${PROJECT_STYLE}              \
                --suppress=missingInclude                                           \

help:
	@:
	${info Help}
	${info ---------------------------------------------------------------------}
	${info make help                     - this help text}
	${info make BUILD=<build_type> build - create binary files (.elf, .hex)}
	${info make BUILD=<build_type> all   - create binary files (.elf, .hex). same as build}
	${info make clean                    - remove generated files}
	${info make run                      - run binary}
	${info make style                    - perform user sources formatting}
	${info make check                    - perform user sources static analysis}
	${info ---------------------------------------------------------------------}
	${info Available build_type [DEBUG RELEASE], eg: make BUILD=RELEASE ...}
	${info Default build_type RELEASE}

-include ${OBJECTS:.o=.d}
