include scripts/setup.mk
include c-bindings/build.mk

main.$(O): main.c nodes.h messages.h
	$(call compile_o)

lib_ruby_parser_native.$(DYLIB): main.$(O) c-bindings/libruby_parser_c-$(TARGET).$(A)
	$(call link_dylib)

test: lib_ruby_parser_native.$(DYLIB)
	bundle exec rake spec
