C_BINDINGS_DIR = c-bindings

ifeq ($(DETECTED_OS), windows)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-pc-windows-gnu.a
else ifeq ($(DETECTED_OS), linux)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-unknown-linux-gnu.a
else ifeq ($(DETECTED_OS), darwin)
	LIB_RUBY_PARSER_NAME = lib-ruby-parser-x86_64-apple-darwin.a
endif

VERSION = v1.0.0

C_BINDINGS_BASE_URL = https://github.com/lib-ruby-parser/c-bindings/releases/download/$(VERSION)
HEADER_URL = $(C_BINDINGS_BASE_URL)/lib-ruby-parser.h

c-bindings/libruby_parser_c-$(TARGET).$(A):
	$(call download_file, $(C_BINDINGS_BASE_URL)/libruby_parser_c-$(TARGET).$(A), $@)

c-bindings/lib-ruby-parser.h:
	$(call download_file, $(C_BINDINGS_BASE_URL)/lib-ruby-parser.h, $@)

c-bindings/clean:
	rm -f libruby_parser_c-$(TARGET).$(A)
	rm -f c-bindings/lib-ruby-parser.h
