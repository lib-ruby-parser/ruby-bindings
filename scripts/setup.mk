ifndef TARGET
$(error TARGET variable is required)
endif

RUBY_VERSION = $(shell ruby scripts/print-ruby-version.rb)

include scripts/targets/$(TARGET).mk

define download_file
URL="$(1)" SAVE_AS="$(2)" ruby scripts/download_file.rb
endef

define compile_o
EXTRA_CFLAGS="$(CFLAGS)" ruby scripts/compile.rb main.c main.o
endef

define link_dylib
EXTRA_CFLAGS="$(CFLAGS)" ruby \
	scripts/link.rb \
	main.o \
	c-bindings/libruby_parser_c-$(TARGET).$(A) \
	$(LIB_RUBY_PARSER_DYLIB)
endef

build-info:
	DRY_RUN=1 $(call compile_o)
	echo
	DRY_RUN=1 $(call link_dylib)

$(info Build configuration:)

$(info O = $(O))
$(info A = $(A))
$(info DYLIB = $(DYLIB))
$(info RUBY_VERSION = $(RUBY_VERSION))
$(info LIB_RUBY_PARSER_DYLIB = $(LIB_RUBY_PARSER_DYLIB))

$(info )
