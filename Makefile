CLEAN =

include scripts/setup.mk
include c-bindings/build.mk
include codegen/build.mk
include benchmark/build.mk

main.$(O): main.c nodes.h messages.h c-bindings/lib-ruby-parser.h
	$(call compile_o)
CLEAN += main.$(O)

$(LIB_RUBY_PARSER_DYLIB): main.$(O) c-bindings/libruby_parser_c-$(TARGET).$(A)
	$(call link_dylib)
CLEAN += $(LIB_RUBY_PARSER_DYLIB)

test: $(LIB_RUBY_PARSER_DYLIB)
	ruby test/test_parser.rb

clean:
	rm -rf $(CLEAN)

include package/build.mk
