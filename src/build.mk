ALL_SRCS = $(wildcard src/*.c)
ALL_HEADERS = $(wildcard src/*.h)
OBJECTS = $(foreach src,$(ALL_SRCS), $(patsubst src/%.c,$(TARGET_DIR)/%.$(OBJ_FILE_EXT),$(src)))

MAIN_C = src/main.c
OBJECT_FILE = $(TARGET_DIR)/lib_ruby_parser_native.o
ifeq ($(DETECTED_OS), windows)
	DLEXT = so
else ifeq ($(DETECTED_OS), linux)
	DLEXT = so
else ifeq ($(DETECTED_OS), darwin)
	DLEXT = bundle
endif
DYLIB = lib/lib-ruby-parser/lib_ruby_parser_native_$(DETECTED_OS).$(DLEXT)

COMPILE_COMMAND = $$(ruby scripts/compile.rb $(MAIN_C) $(OBJECT_FILE))
LINK_COMMAND = $$(ruby scripts/link.rb $(OBJECT_FILE) $(LIB_RUBY_PARSER_STATIC) $(DYLIB))

$(OBJECT_FILE): $(ALL_SRCS) $(ALL_HEADERS)
	@echo "$(COMPILE_COMMAND)"
	$(COMPILE_COMMAND)

$(DYLIB): $(OBJECT_FILE)
	@echo "$(LINK_COMMAND)"
	$(LINK_COMMAND)
