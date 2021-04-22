#include <ruby.h>
#include <stdio.h>
#include "convert.h"
#include "convert_known.h"
#include <ruby/encoding.h>
#include "../c-bindings/lib-ruby-parser.h"
// #include "helpers.h"
#include "parser_options.h"

VALUE rb_parse(VALUE self, VALUE rb_code, VALUE rb_options)
{
    UNUSED(self);
    if (NIL_P(rb_options))
    {
        rb_options = rb_hash_new();
    }

    LIB_RUBY_PARSER_ParserOptions options = c_parser_options_from_ruby_hash(rb_options);
    LIB_RUBY_PARSER_ByteList input = byte_list_from_rstring(rb_code);

    LIB_RUBY_PARSER_ParserResult result = lib_ruby_parser_parse(input, options);

    return convert_ParserResult(result);
}

void Init_lib_ruby_parser_native()
{
    VALUE lib_ruby_parser_mod = rb_define_module("LibRubyParser");
    rb_define_singleton_method(lib_ruby_parser_mod, "parse", rb_parse, 2);
}

// Platform-specific entry points
void Init_lib_ruby_parser_native_darwin()
{
    Init_lib_ruby_parser_native();
}

void Init_lib_ruby_parser_native_linux()
{
    Init_lib_ruby_parser_native();
}

void Init_lib_ruby_parser_native_windows()
{
    Init_lib_ruby_parser_native();
}
