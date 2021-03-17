# ifeq ($(DETECTED_OS), Darwin)
# 	CCFLAGS += -Wall -Wextra
# 	CCOBJFLAGS += -fPIC -c
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

# 	CCFLAGS += -fdeclspec
# 	CCSHAREDFLAGS += -shared -undefined dynamic_lookup

# 	ifeq ($(BUILD_ENV), debug)
# 		CCFLAGS += -g -O0
# 	else
# 		CCFLAGS += -O2
# 	endif
# 	OBJ_FILE_EXT = .o
# 	RUBY_LIB_EXT = .bundle

# 	CC_SET_OUT_FILE = -o #
# 	LIST_DEPS = otool -L
# endif

# ifeq ($(DETECTED_OS), Linux)
# 	CCFLAGS += -Wall -Wextra
# 	CCOBJFLAGS += -fPIC -c
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

# 	CCFLAGS += -fdeclspec
# 	CCSHAREDFLAGS += -shared -fPIC

# 	ifeq ($(BUILD_ENV), debug)
# 		CCFLAGS += -g -O0
# 	else
# 		CCFLAGS += -O2
# 	endif
# 	OBJ_FILE_EXT = .o
# 	RUBY_LIB_EXT = .so

# 	CC_SET_OUT_FILE = -o #
# 	LIST_DEPS = ldd
# endif

# ifeq ($(DETECTED_OS), Windows)
# 	CCFLAGS += -Wall -Wextra
# 	CCOBJFLAGS += -c
# 	# -fPIC
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyhdrdir']")
# 	CCFLAGS += -I $$(ruby -rrbconfig -e "puts RbConfig::CONFIG['rubyarchhdrdir']")

# 	# CCFLAGS += -fdeclspec
# 	CCSHAREDFLAGS += -pie -static -shared -Wl,--allow-shlib-undefined,--enable-runtime-pseudo-reloc
# 	#  -fPIC

# 	ifeq ($(BUILD_ENV), debug)
# 		CCFLAGS += -g -O0
# 	else
# 		CCFLAGS += -O2
# 	endif
# 	OBJ_FILE_EXT = .o
# 	RUBY_LIB_EXT = .so

# 	CC_SET_OUT_FILE = -o #
# 	LIST_DEPS = dumpbin /dependents
# endif

ALL_SRCS = $(wildcard src/*.c)
ALL_HEADERS = $(wildcard src/*.h)
OBJECTS = $(foreach src,$(ALL_SRCS), $(patsubst src/%.c,$(TARGET_DIR)/%.$(OBJ_FILE_EXT),$(src)))

MAIN_C = src/main.c
OBJECT_FILE = $(TARGET_DIR)/lib_ruby_parser_native.o
ifeq ($(DETECTED_OS), Windows)
	DLEXT = so
else ifeq ($(DETECTED_OS), Linux)
	DLEXT = so
else ifeq ($(DETECTED_OS), Darwin)
	DLEXT = bundle
endif
DYLIB = lib/lib-ruby-parser/lib_ruby_parser_native.$(DLEXT)

COMPILE_COMMAND = $$(ruby scripts/compile.rb $(MAIN_C) $(OBJECT_FILE))
LINK_COMMAND = $$(ruby scripts/link.rb $(OBJECT_FILE) $(LIB_RUBY_PARSER_STATIC) $(DYLIB))

$(OBJECT_FILE): $(ALL_SRCS) $(ALL_HEADERS)
	@echo "$(COMPILE_COMMAND)"
	$(COMPILE_COMMAND)

$(DYLIB): $(OBJECT_FILE)
	@echo "$(LINK_COMMAND)"
	$(LINK_COMMAND)
