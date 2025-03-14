#
# Copyright (c) 2014-2025, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

MAKE_HELPERS_DIRECTORY := ../../make_helpers/
include ${MAKE_HELPERS_DIRECTORY}build_macros.mk
include ${MAKE_HELPERS_DIRECTORY}common.mk
include ${MAKE_HELPERS_DIRECTORY}defaults.mk
include ${MAKE_HELPERS_DIRECTORY}toolchain.mk

FIPTOOL ?= fiptool$(.exe)
PROJECT := $(notdir ${FIPTOOL})
OBJECTS := fiptool.o tbbr_config.o
STATIC ?= 0

override CPPFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=700
HOSTCCFLAGS := -Wall -Werror -pedantic -std=c99
ifeq (${DEBUG},1)
  HOSTCCFLAGS += -g -O0 -DDEBUG
else
  HOSTCCFLAGS += -O2
endif

INCLUDE_PATHS := -I../../include/tools_share

DEFINES += -DSTATIC=$(STATIC)

ifeq (${STATIC},1)
LDOPTS := -static
else
OPENSSL_DIR := /usr

# Select OpenSSL version flag according to the OpenSSL build selected
# from setting the OPENSSL_DIR path.
$(eval $(call SELECT_OPENSSL_API_VERSION))

# USING_OPENSSL3 flag will be added to the HOSTCCFLAGS variable with the proper
# computed value.
DEFINES += -DUSING_OPENSSL3=$(USING_OPENSSL3)

# Include library directories where OpenSSL library files are located.
# For a normal installation (i.e.: when ${OPENSSL_DIR} = /usr or
# /usr/local), binaries are located under the ${OPENSSL_DIR}/lib/
# directory. However, for a local build of OpenSSL, the built binaries are
# located under the main project directory (i.e.: ${OPENSSL_DIR}, not
# ${OPENSSL_DIR}/lib/).
LDOPTS := -L${OPENSSL_DIR}/lib -L${OPENSSL_DIR} -lcrypto
INCLUDE_PATHS += -I${OPENSSL_DIR}/include
endif # STATIC

HOSTCCFLAGS += ${DEFINES}

ifneq (${PLAT},)
TF_PLATFORM_ROOT	:=	../../plat/
include ${MAKE_HELPERS_DIRECTORY}plat_helpers.mk
COMBINED_PATH_FRAG := plat_fiptool/
PLAT_FIPTOOL_HELPER_MK := $(foreach path_frag,$(subst /, ,$(patsubst ../../plat/%/,%,${PLAT_DIR})),\
			  $(eval COMBINED_PATH_FRAG := ${COMBINED_PATH_FRAG}/${path_frag})\
			  $(wildcard ${COMBINED_PATH_FRAG}/plat_fiptool.mk))
endif

ifneq (,$(wildcard $(lastword ${PLAT_FIPTOOL_HELPER_MK})))
include ${PLAT_FIPTOOL_HELPER_MK}
endif

DEPS := $(patsubst %.o,%.d,$(OBJECTS))

.PHONY: all clean distclean --openssl

all: --openssl ${PROJECT}

${PROJECT}: ${OBJECTS} Makefile
	$(s)echo "  HOSTLD  $@"
	$(q)$(host-cc) ${OBJECTS} -o $@ $(LDOPTS)
	$(s)echo
	$(s)echo "Built $@ successfully"
	$(s)echo

%.o: %.c Makefile
	$(s)echo "  HOSTCC  $<"
	$(q)$(host-cc) -c ${CPPFLAGS} ${HOSTCCFLAGS} ${INCLUDE_PATHS} -MD -MP $< -o $@

-include $(DEPS)

--openssl:
ifeq ($(STATIC),0)
ifeq ($(DEBUG),1)
	$(s)echo "Selected OpenSSL version: ${OPENSSL_CURRENT_VER}"
endif
endif # STATIC

clean:
	$(q)rm -rf $(PROJECT) $(OBJECTS) $(DEPS)
