#ifndef LIB_RUBY_PARSER_PARSER_OPTIONS_H
#define LIB_RUBY_PARSER_PARSER_OPTIONS_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"
#include "helpers.h"
#include "decoder.h"
#include "token_rewriter.h"

LIB_RUBY_PARSER_StringPtr string_ptr_from_ruby_string(VALUE string);

LIB_RUBY_PARSER_StringPtr buffer_name_from_value(VALUE value)
{
    if (NIL_P(value))
    {
        value = rb_str_new2("(eval)");
    }
    return string_ptr_from_ruby_string(value);
}

bool debug_from_value(VALUE value)
{
    if (NIL_P(value))
    {
        return false;
    }
    return RTEST(value);
}

LIB_RUBY_PARSER_ForeignCustomDecoder decoder_from_value(VALUE value)
{
    LIB_RUBY_PARSER_ForeignCustomDecoder decoder;
    if (NIL_P(value))
    {
        decoder.dummy = true;
        decoder.f = NULL;
        decoder.state = NULL;
    }
    else if (RTEST(rb_obj_is_proc(value)))
    {
        decoder.dummy = false;
        decoder.f = rb_decoder_wrapper;
        decoder.state = (void *)value;
    }
    else
    {
        rb_raise(rb_eTypeError, ":decoder must be nil or Proc");
    }
    return decoder;
}

bool record_tokens_from_value(VALUE value)
{
    if (NIL_P(value))
    {
        return false;
    }
    return RTEST(value);
}

LIB_RUBY_PARSER_ForeignTokenRewriter token_rewriter_from_value(VALUE value)
{
    LIB_RUBY_PARSER_ForeignTokenRewriter token_rewriter;
    if (NIL_P(value))
    {
        token_rewriter.dummy = true;
        token_rewriter.f = NULL;
        token_rewriter.state = NULL;
    }
    else if (RTEST(rb_obj_is_proc(value)))
    {
        token_rewriter.dummy = false;
        token_rewriter.f = rb_token_rewriter_wrapper;
        token_rewriter.state = (void *)value;
    }
    else
    {
        rb_raise(rb_eTypeError, ":token_rewriter must be nil or Proc");
    }
    return token_rewriter;
}

LIB_RUBY_PARSER_ParserOptions c_parser_options_from_ruby_hash(VALUE rb_options)
{
    VALUE rb_buffer_name = rb_hash_aref(rb_options, rb_sym_from_cstr("buffer_name"));
    VALUE rb_debug = rb_hash_aref(rb_options, rb_sym_from_cstr("debug"));
    VALUE rb_decoder = rb_hash_aref(rb_options, rb_sym_from_cstr("decoder"));
    VALUE rb_record_tokens = rb_hash_aref(rb_options, rb_sym_from_cstr("record_tokens"));
    VALUE rb_token_rewriter = rb_hash_aref(rb_options, rb_sym_from_cstr("token_rewriter"));

    LIB_RUBY_PARSER_ParserOptions options = {
        .buffer_name = buffer_name_from_value(rb_buffer_name),
        .debug = debug_from_value(rb_debug),
        .decoder = decoder_from_value(rb_decoder),
        .record_tokens = record_tokens_from_value(rb_record_tokens),
        .token_rewriter = token_rewriter_from_value(rb_token_rewriter)};

    return options;
}

LIB_RUBY_PARSER_StringPtr string_ptr_from_ruby_string(VALUE string)
{
    char *ptr = StringValueCStr(string);
    uint32_t length = strlen(ptr);
    ptr = copy_string(ptr, length);

    LIB_RUBY_PARSER_StringPtr result = {
        .ptr = (uint8_t *)ptr,
        .len = length};

    return result;
}

#endif // LIB_RUBY_PARSER_PARSER_OPTIONS_H
