#
# Copyright (c) 2017-2024, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

MAKE_HELPERS_DIRECTORY := ../../make_helpers/
include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}build_env.mk
include ${MAKE_HELPERS_DIRECTORY}common.mk
include ${MAKE_HELPERS_DIRECTORY}toolchain.mk

PROJECT := stm32image${BIN_EXT}
OBJECTS := stm32image.o

HOSTCCFLAGS := -Wall -Werror -pedantic -std=c99 -D_GNU_SOURCE

ifeq (${DEBUG},1)
  HOSTCCFLAGS += -g -O0 -DDEBUG
else
  HOSTCCFLAGS += -O2
endif

.PHONY: all clean distclean

all: ${PROJECT}

${PROJECT}: ${OBJECTS} Makefile
	$(s)echo "  HOSTLD  $@"
	$(q)$(host-cc) ${OBJECTS} -o $@
	$(s)echo
	$(s)echo "Built $@ successfully"
	$(s)echo

%.o: %.c Makefile
	$(s)echo "  HOSTCC  $<"
	$(q)$(host-cc) -c ${HOSTCCFLAGS} $< -o $@

clean:
	$(call SHELL_DELETE_ALL, ${PROJECT} ${OBJECTS})

distclean: clean
