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

ifeq ($(DETECTED_OS), Darwin)
	CCFLAGS += -Wall -Wextra
	CCOBJFLAGS += -fPIC -c
	CCEXECFLAGS = -lpthread -ldl
	LDFLAGS = -r
	# rubyhdrdir"=>"/Users/ilyabylich/.rvm/rubies/ruby-3.0.0/include/ruby-3.0.0
	CCFLAGS += -I /Users/ilyabylich/.rvm/rubies/ruby-3.0.0/include/ruby-3.0.0/
	# rubyarchhdrdir"=>"/Users/ilyabylich/.rvm/rubies/ruby-3.0.0/include/ruby-3.0.0/x86_64-darwin19
	CCFLAGS += -I /Users/ilyabylich/.rvm/rubies/ruby-3.0.0/include/ruby-3.0.0/x86_64-darwin19/

	CCFLAGS += -fdeclspec
	CCFLAGS += -undefined dynamic_lookup

	ifeq ($(BUILD_ENV), debug)
		CCFLAGS += -g -O0
	else
		CCFLAGS += -O2
	endif
	OBJ_FILE_EXT = .o
	STATIC_LIB_EXT = .a
	EXEC_EXT =
	RUBY_LIB_EXT = .bundle

	CC_SET_OUT_FILE = -o #
	LD_SET_OUT_FILE = -o #
	LIST_DEPS = otool -L
endif

# objects

OBJECTS =

target/convert.o: src/convert.h src/convert.c
	@echo $(A)
	$(CC) src/convert.c $(CCFLAGS) $(CCOBJFLAGS) -o target/convert.o
OBJECTS += target/convert.o

target/convert_known.o: src/convert_known.h src/convert_known.c
	@echo $(A)
	$(CC) src/convert_known.c $(CCFLAGS) $(CCOBJFLAGS) -o target/convert_known.o
OBJECTS += target/convert_known.o

BUNDLE = target/lib_ruby_parser_native$(RUBY_LIB_EXT)
$(BUNDLE): $(OBJECTS) src/main.c
	$(CC) src/main.c $(LOCAL_LIB_NAME) $(OBJECTS) $(CCFLAGS)  -shared -o $(BUNDLE)
native-bundle: $(BUNDLE)

ATTACHED_BUNDLE = lib/lib_ruby_parser_native$(RUBY_LIB_EXT)
$(ATTACHED_BUNDLE): $(BUNDLE)
	cp $(BUNDLE) $(ATTACHED_BUNDLE)
attached-bundle: $(ATTACHED_BUNDLE)

# utils

download-c-bindings:
	wget -q $(HEADER_URL) -O lib-ruby-parser.h
	wget -q $(LIB_URL) -O $(LOCAL_LIB_NAME)

setup:
	mkdir -p target

print-env:
	@echo $(CCFLAGS)

clean:
	rm -rf target
	mkdir -p target
	rm -f $(ATTACHED_BUNDLE)
