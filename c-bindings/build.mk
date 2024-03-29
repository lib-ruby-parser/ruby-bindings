C_BINDINGS_DIR = c-bindings

ifeq ($(DETECTED_OS), windows)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-pc-windows-gnu.a
else ifeq ($(DETECTED_OS), linux)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-unknown-linux-gnu.a
else ifeq ($(DETECTED_OS), darwin)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-apple-darwin.a
endif

VERSION = v3.0.4.2

ASSET_PREFIX = https://github.com/lib-ruby-parser/c-bindings/releases/download/$(VERSION)
HEADER_URL = $(ASSET_PREFIX)/lib-ruby-parser.h
LIB_URL = $(ASSET_PREFIX)/$(LIB_RUBY_PARSER_NAME)

LIB_RUBY_PARSER_STATIC = $(C_BINDINGS_DIR)/$(LIB_RUBY_PARSER_NAME)

download-c-bindings:
	wget -q $(HEADER_URL) -O $(C_BINDINGS_DIR)/lib-ruby-parser.h
	wget -q $(LIB_URL) -O $(LIB_RUBY_PARSER_STATIC)
