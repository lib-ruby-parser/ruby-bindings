ifeq ($(OS), Windows_NT)
	DETECTED_OS = Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		DETECTED_OS = Linux
	else
		ifeq ($(UNAME_S), Darwin)
			DETECTED_OS = Darwin
		else
			DETECTED_OS = Unknown
		endif
	endif
endif

ifeq ($(DETECTED_OS), Windows)
	LIB_ASSET_NAME = lib-ruby-parser-x86_64-pc-windows-msvc.lib
	LOCAL_LIB_NAME = lib-ruby-parser.lib
endif
ifeq ($(DETECTED_OS), Linux)
	LIB_ASSET_NAME = lib-ruby-parser-x86_64-unknown-linux-gnu.a
	LOCAL_LIB_NAME = lib-ruby-parser.a
endif
ifeq ($(UNAME_S), Darwin)
	LIB_ASSET_NAME = lib-ruby-parser-x86_64-apple-darwin.a
	LOCAL_LIB_NAME = lib-ruby-parser.a
endif

VERSION = 3.0.0-3.0

ifndef BUILD_ENV
	BUILD_ENV = debug
endif

ASSET_PREFIX = https://github.com/lib-ruby-parser/c-bindings/releases/download/v$(VERSION)
HEADER_URL = $(ASSET_PREFIX)/lib-ruby-parser.h
LIB_URL = $(ASSET_PREFIX)/$(LIB_ASSET_NAME)

setup:
	mkdir -p target

clean:
	rm -rf target
	mkdir -p target

# build

ifeq ($(DETECTED_OS), Darwin)
	CCFLAGS += -Wall -Wextra
	CCOBJFLAGS += -fPIC -c
	CCEXECFLAGS = -lpthread -ldl
	LDFLAGS = -r

	ifeq ($(BUILD_ENV), debug)
		CCFLAGS += -g -O0
	else
		CCFLAGS += -O2
	endif
	OBJ_FILE_EXT = .o
	STATIC_LIB_EXT = .a
	EXEC_EXT =

	CC_SET_OUT_FILE = -o #
	LD_SET_OUT_FILE = -o #
	LIST_DEPS = otool -L
endif


# download

download-c-bindings:
	wget -q $(HEADER_URL) -O lib-ruby-parser.h
	wget -q $(LIB_URL) -O $(LOCAL_LIB_NAME)
