#ifndef LIB_RUBY_PARSER_DECODER_H
#define LIB_RUBY_PARSER_DECODER_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"
#include "helpers.h"

LIB_RUBY_PARSER_CustomDecoderResult rb_decoder_wrapper(LIB_RUBY_PARSER_StringPtr encoding, LIB_RUBY_PARSER_ByteList input, void *state)
{
    VALUE rb_decoder = (VALUE)state;

    VALUE rb_encoding = rb_external_str_new((char *)(encoding.ptr), encoding.len);
    VALUE rb_input = rb_external_str_new((char *)(input.ptr), input.len);
    rb_input = rb_enc_associate(rb_input, rb_ascii8bit_encoding());

    VALUE rb_decoded = rb_proc_call(rb_decoder, rb_ary_new_from_args(2, rb_encoding, rb_input));

    if (!RB_TYPE_P(rb_decoded, T_STRING))
    {
        rb_raise(rb_eTypeError, ":decoder must return a String");
    }

    LIB_RUBY_PARSER_ByteList decoded = byte_list_from_rstring(rb_decoded);

    LIB_RUBY_PARSER_CustomDecoderResult result = {
        .tag = CUSTOM_DECODER_RESULT_OK,
        .ok = decoded};
    return result;
}

#endif // LIB_RUBY_PARSER_DECODER_H
