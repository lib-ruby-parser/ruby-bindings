include scripts/setup.mk

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

VERSION = 3.0.0-3.6

ASSET_PREFIX = https://github.com/lib-ruby-parser/c-bindings/releases/download/v$(VERSION)
HEADER_URL = $(ASSET_PREFIX)/lib-ruby-parser.h
LIB_URL = $(ASSET_PREFIX)/$(LIB_ASSET_NAME)

ifeq ($(DETECTED_OS), Darwin)
	CCFLAGS += -Wall -Wextra
	CCOBJFLAGS += -fPIC -c
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

	CCFLAGS += -fdeclspec
	CCSHAREDFLAGS += -shared -undefined dynamic_lookup

	ifeq ($(BUILD_ENV), debug)
		CCFLAGS += -g -O0
	else
		CCFLAGS += -O2
	endif
	OBJ_FILE_EXT = .o
	RUBY_LIB_EXT = .bundle

	CC_SET_OUT_FILE = -o #
	LIST_DEPS = otool -L
endif

ifeq ($(DETECTED_OS), Linux)
	CCFLAGS += -Wall -Wextra
	CCOBJFLAGS += -fPIC -c
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

	CCFLAGS += -fdeclspec
	CCSHAREDFLAGS += -shared -fPIC

	ifeq ($(BUILD_ENV), debug)
		CCFLAGS += -g -O0
	else
		CCFLAGS += -O2
	endif
	OBJ_FILE_EXT = .o
	RUBY_LIB_EXT = .so

	CC_SET_OUT_FILE = -o #
	LIST_DEPS = ldd
endif

ifeq ($(DETECTED_OS), Windows)
	CCFLAGS += -Wall -Wextra
	CCOBJFLAGS += -c
	# -fPIC
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

	# CCFLAGS += -fdeclspec
	CCSHAREDFLAGS += -pie -static -shared -Wl,--allow-shlib-undefined,--enable-runtime-pseudo-reloc
	#  -fPIC

	ifeq ($(BUILD_ENV), debug)
		CCFLAGS += -g -O0
	else
		CCFLAGS += -O2
	endif
	OBJ_FILE_EXT = .o
	RUBY_LIB_EXT = .so

	CC_SET_OUT_FILE = -o #
	LIST_DEPS = dumpbin /dependents
endif

generate-ruby-bindings:
	cd build-convert && cargo build

# objects

OBJECTS =

$(TARGET_DIR)/convert$(OBJ_FILE_EXT): src/convert.h src/convert.c
	$(CC) src/convert.c $(CCFLAGS) $(CCOBJFLAGS)
	mv convert$(OBJ_FILE_EXT) $(TARGET_DIR)/convert$(OBJ_FILE_EXT)
OBJECTS += $(TARGET_DIR)/convert$(OBJ_FILE_EXT)

$(TARGET_DIR)/convert_known$(OBJ_FILE_EXT): src/convert_known.h src/convert_known.c
	$(CC) src/convert_known.c $(CCFLAGS) $(CCOBJFLAGS)
	mv convert_known$(OBJ_FILE_EXT) $(TARGET_DIR)/convert_known$(OBJ_FILE_EXT)
OBJECTS += $(TARGET_DIR)/convert_known$(OBJ_FILE_EXT)

BUNDLE = $(TARGET_DIR)/lib_ruby_parser_native$(RUBY_LIB_EXT)
$(BUNDLE): $(OBJECTS) src/main.c
	$(CC) src/main.c $(LOCAL_LIB_NAME) $(OBJECTS) $(CCFLAGS) $(CCSHAREDFLAGS) $(CC_SET_OUT_FILE)$(BUNDLE)
	ls -l
	ls -l $(TARGET_DIR)
native-bundle: $(BUNDLE)

ATTACHED_BUNDLE = lib/lib-ruby-parser/lib_ruby_parser_native$(RUBY_LIB_EXT)
$(ATTACHED_BUNDLE): $(BUNDLE)
	cp $(BUNDLE) $(ATTACHED_BUNDLE)
attached-bundle: $(ATTACHED_BUNDLE)

# utils

download-c-bindings:
	wget -q $(HEADER_URL) -O lib-ruby-parser.h
	wget -q $(LIB_URL) -O $(LOCAL_LIB_NAME)

setup:
	mkdir -p $(TARGET_DIR)

print-env:
	ruby -rrbconfig -e 'pp RbConfig::CONFIG'
	@echo $(CCFLAGS)

clean:
	rm -rf $(TARGET_DIR)
	mkdir -p $(TARGET_DIR)
	rm -f $(ATTACHED_BUNDLE)
