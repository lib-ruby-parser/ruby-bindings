#include <ruby.h>
#include <stdio.h>
#include "convert.h"
#include "convert_known.h"
#include "../lib-ruby-parser.h"

#define UNUSED(x) (void)(x)
#define rb_sym_from_cstr(x) ID2SYM(rb_intern(x))

#define get_parser_option_or(key, fallback)                            \
    VALUE rb_##key = rb_hash_aref(rb_options, rb_sym_from_cstr(#key)); \
    if (NIL_P(rb_##key))                                               \
    {                                                                  \
        rb_##key = (fallback);                                         \
    }

struct TokenRewriterOutput rewrite_token_wrapper(void *rewriter, struct Token token, const char *input)
{
    VALUE rb_rewriter = (VALUE)rewriter;
    if (NIL_P(rb_rewriter))
    {
        struct TokenRewriterOutput result = {
            .token = token,
            .token_rewriter_action = REWRITE_ACTION_KEEP,
            .lex_state_action = {.kind = LEX_STATE_ACTION_KEEP}};
        return result;
    }
    rb_proc_call(rb_rewriter, rb_ary_new());

    rb_raise(rb_eException, "Unimplemented");
}

struct ParserOptions parser_options(VALUE rb_options)
{
    get_parser_option_or(buffer_name, rb_str_new2("(eval)"));
    get_parser_option_or(debug, Qfalse);
    get_parser_option_or(decoder, Qnil);
    get_parser_option_or(record_tokens, Qfalse);
    get_parser_option_or(token_rewriter, Qnil);

    char *buffer_name = StringValueCStr(rb_buffer_name);
    bool debug = RTEST(rb_debug);
    CustomDecoder *decoder = NULL; // FIXME
    bool record_tokens = RTEST(rb_record_tokens);
    struct TokenRewriter *token_rewriter = malloc(sizeof(struct TokenRewriter));
    token_rewriter->state = (void *)rb_token_rewriter;
    token_rewriter->rewriter = rewrite_token_wrapper;

    struct ParserOptions options = {
        .buffer_name = buffer_name,
        .debug = debug,
        .decoder = decoder,
        .record_tokens = record_tokens,
        .token_rewriter = token_rewriter};

    return options;
}

VALUE ast_to_ruby(struct Node *node)
{
    return convert_Node(node);
}
VALUE tokens_to_ruby(struct TokenList *tokens)
{
    VALUE result = rb_ary_new_capa(tokens->len);
    for (uint32_t i = 0; i < tokens->len; i++)
    {
        rb_ary_push(result, convert_Token(&(tokens->list[i])));
    }
    return result;
}
VALUE diagnostics_to_ruby(struct Diagnostics *diagnostics)
{
    return Qnil;
}
VALUE comments_to_ruby(struct CommentList *comments)
{
    return Qnil;
}
VALUE magic_comments_to_ruby(struct MagicCommentList *magic_comments)
{
    return Qnil;
}
VALUE input_to_ruby(char *input)
{
    return Qnil;
}

VALUE parser_result_to_ruby(struct ParserResult *result)
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

    struct ParserOptions options = parser_options(rb_options);
    char *code = StringValueCStr(rb_code);
    long code_len = rb_str_strlen(rb_code);

    struct ParserResult *result = parse(&options, code, code_len);

    return parser_result_to_ruby(result);
}

void Init_lib_ruby_parser_native()
{
    VALUE lib_ruby_parser_mod = rb_define_module("LibRubyParser");
    rb_define_singleton_method(lib_ruby_parser_mod, "parse", rb_parse, 2);
}
