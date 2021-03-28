#include <ruby.h>
#include <stdio.h>
#include "convert.h"
#include "convert_known.h"
#include <ruby/encoding.h>
#include "../c-bindings/lib-ruby-parser.h"

#define UNUSED(x) (void)(x)
#define rb_sym_from_cstr(x) ID2SYM(rb_intern(x))

#define get_parser_option_or(key, fallback)                            \
    VALUE rb_##key = rb_hash_aref(rb_options, rb_sym_from_cstr(#key)); \
    if (NIL_P(rb_##key))                                               \
    {                                                                  \
        rb_##key = (fallback);                                         \
    }

char *copy_string(const char *source, uint32_t length)
{
    char *out = (char *)malloc(length + 1);
    memcpy(out, source, length);
    out[length] = '\0';
    return out;
}

DecoderOutput rb_decoder_wrapper(void *state, const char *encoding, const char *input, uint32_t len)
{
    VALUE rb_decoder = (VALUE)state;

    VALUE rb_encoding = rb_external_str_new_cstr(encoding);
    VALUE rb_input = rb_external_str_new(input, len);
    rb_input = rb_enc_associate(rb_input, rb_ascii8bit_encoding());

    VALUE rb_decoded = rb_proc_call(rb_decoder, rb_ary_new_from_args(2, rb_encoding, rb_input));
    if (!RB_TYPE_P(rb_decoded, T_STRING))
    {
        rb_raise(rb_eTypeError, ":decoder must return a String");
    }
    uint32_t length = RSTRING_LEN(rb_decoded);
    char *ptr = copy_string(StringValueCStr(rb_decoded), length);

    return decode_ok(ptr, length);
}

ParserOptions parser_options(VALUE rb_options)
{
    get_parser_option_or(buffer_name, rb_str_new2("(eval)"));
    get_parser_option_or(debug, Qfalse);
    get_parser_option_or(decoder, Qnil);
    get_parser_option_or(record_tokens, Qfalse);
    get_parser_option_or(token_rewriter, Qnil);

    char *buffer_name = StringValueCStr(rb_buffer_name);
    bool debug = RTEST(rb_debug);

    CustomDecoder *decoder;
    if (NIL_P(rb_decoder))
    {
        decoder = NULL;
    }
    else if (RTEST(rb_obj_is_proc(rb_decoder)))
    {
        decoder = (CustomDecoder *)malloc(sizeof(CustomDecoder));
        decoder->state = (void *)rb_decoder;
        decoder->decoder = rb_decoder_wrapper;
    }
    else
    {
        rb_raise(rb_eTypeError, ":decoder must be nil or Proc");
    }

    bool record_tokens = RTEST(rb_record_tokens);
    if (!NIL_P(rb_token_rewriter))
    {
        rb_raise(rb_eNotImpError, ":token_rewriter is currently unsupported, please open an issue on https://github.com/lib-ruby-parser/ruby-bindings if you need this feature");
    }

    ParserOptions options = {
        .buffer_name = buffer_name,
        .debug = debug,
        .decoder = decoder,
        .record_tokens = record_tokens,
        .token_rewriter = NULL};

    return options;
}

VALUE ast_to_ruby(Node *node)
{
    return convert_Node(node);
}

VALUE tokens_to_ruby(TokenList *tokens)
{
    VALUE result = rb_ary_new_capa(tokens->len);
    for (uint32_t i = 0; i < tokens->len; i++)
    {
        rb_ary_push(result, convert_Token(&(tokens->list[i])));
    }
    return result;
}

VALUE diagnostics_to_ruby(DiagnosticList *diagnostics)
{
    VALUE result = rb_ary_new_capa(diagnostics->len);
    for (uint32_t i = 0; i < diagnostics->len; i++)
    {
        rb_ary_push(result, convert_Diagnostic(&(diagnostics->list[i])));
    }
    return result;
}

VALUE comments_to_ruby(CommentList *comments)
{
    VALUE result = rb_ary_new_capa(comments->len);
    for (uint32_t i = 0; i < comments->len; i++)
    {
        rb_ary_push(result, convert_Comment(&(comments->list[i])));
    }
    return result;
}

VALUE magic_comments_to_ruby(MagicCommentList *magic_comments)
{
    VALUE result = rb_ary_new_capa(magic_comments->len);
    for (uint32_t i = 0; i < magic_comments->len; i++)
    {
        rb_ary_push(result, convert_MagicComment(&(magic_comments->list[i])));
    }
    return result;
}

VALUE input_to_ruby(Input *input)
{
    uint32_t len = input_len(input);
    char *ptr = copy_string(input_ptr(input), len);
    return rb_utf8_str_new(ptr, len);
}

VALUE parser_result_to_ruby(ParserResult *result)
{
    VALUE rb_result = rb_hash_new();

    rb_hash_aset(rb_result, rb_sym_from_cstr("ast"), ast_to_ruby(result->ast));
    rb_hash_aset(rb_result, rb_sym_from_cstr("tokens"), tokens_to_ruby(result->tokens));
    rb_hash_aset(rb_result, rb_sym_from_cstr("diagnostics"), diagnostics_to_ruby(result->diagnostics));
    rb_hash_aset(rb_result, rb_sym_from_cstr("comments"), comments_to_ruby(result->comments));
    rb_hash_aset(rb_result, rb_sym_from_cstr("magic_comments"), magic_comments_to_ruby(result->magic_comments));
    rb_hash_aset(rb_result, rb_sym_from_cstr("input"), input_to_ruby(result->input));

    parser_result_free(result);

    return rb_result;
}

VALUE rb_parse(VALUE self, VALUE rb_code, VALUE rb_options)
{
    UNUSED(self);
    if (NIL_P(rb_options))
    {
        rb_options = rb_hash_new();
    }

    ParserOptions options = parser_options(rb_options);
    long code_len = rb_str_strlen(rb_code);
    char *code = StringValueCStr(rb_code);

    ParserResult *result = parse(&options, code);
    if (options.decoder != NULL)
    {
        free(options.decoder);
    }

    return parser_result_to_ruby(result);
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
