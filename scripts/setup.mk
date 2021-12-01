RUBY_VERSION = $(shell ruby scripts/ruby-version.rb)

define download_file
URL="$(1)" SAVE_AS="$(2)" ruby scripts/download_file.rb
endef

ifndef TARGET
$(error TARGET variable is required)
endif

include scripts/targets/$(TARGET).mk

define compile_o
EXTRA_CFLAGS="$(CFLAGS)" ruby scripts/compile.rb main.c main.$(O)
endef

define link_dylib
EXTRA_CFLAGS="$(CFLAGS)" ruby \
	scripts/link.rb \
	main.$(O) \
	$(STATIC_LIBRUBY) \
	c-bindings/libruby_parser_c-$(TARGET).$(A) \
	lib/lib-ruby-parser/lib_ruby_parser_native.$(DYLIB)
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

$(info )
