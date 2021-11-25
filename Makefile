CLEAN =

include scripts/setup.mk
include c-bindings/build.mk
include codegen/build.mk

main.$(O): main.c nodes.h messages.h c-bindings/lib-ruby-parser.h
	$(call compile_o)
CLEAN += main.$(O)

lib/lib-ruby-parser/lib_ruby_parser_native.$(DYLIB): main.$(O) c-bindings/libruby_parser_c-$(TARGET).$(A)
	$(call link_dylib)
CLEAN += lib/lib-ruby-parser/lib_ruby_parser_native.$(DYLIB)

test: lib/lib-ruby-parser/lib_ruby_parser_native.$(DYLIB)
	bundle exec rake spec

clean:
	rm -rf $(CLEAN)
