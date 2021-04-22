#ifndef LIB_RUBY_PARSER_TOKEN_REWRITER_H
#define LIB_RUBY_PARSER_TOKEN_REWRITER_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"
#include "helpers.h"

LIB_RUBY_PARSER_Loc c_loc_from_ruby_loc(VALUE rb_loc)
{
    VALUE rb_begin = rb_ivar_get(rb_loc, rb_intern("@begin"));
    VALUE rb_end = rb_ivar_get(rb_loc, rb_intern("@end"));
    LIB_RUBY_PARSER_Loc result = {
        .begin = FIX2INT(rb_begin),
        .end = FIX2INT(rb_end)};
    return result;
}

LIB_RUBY_PARSER_TokenPtr c_token_from_ruby_token(VALUE rb_token)
{
    LIB_RUBY_PARSER_TokenPtr token_ptr = malloc(sizeof(LIB_RUBY_PARSER_Token));

    VALUE rb_lex_state_before = rb_ivar_get(rb_token, rb_intern("@lex_state_before"));
    VALUE rb_lex_state_after = rb_ivar_get(rb_token, rb_intern("@lex_state_after"));
    VALUE rb_loc = rb_ivar_get(rb_token, rb_intern("@loc"));
    VALUE rb_token_type = rb_ivar_get(rb_token, rb_intern("@token_type"));

    token_ptr->lex_state_before.value = FIX2INT(rb_lex_state_before);
    token_ptr->lex_state_after.value = FIX2INT(rb_lex_state_after);
    token_ptr->loc = c_loc_from_ruby_loc(rb_loc);
    token_ptr->token_type = FIX2INT(rb_token_type);
    VALUE rb_token_value = rb_ivar_get(rb_token, rb_intern("@token_value"));
    if (NIL_P(rb_token_value))
    {
        token_ptr->token_value.raw = lib_ruby_parser_make_byte_list("");
    }
    else
    {
        token_ptr->token_value.raw = lib_ruby_parser_make_byte_list(StringValueCStr(rb_token_value));
    }
    return token_ptr;
}

LIB_RUBY_PARSER_RewriteAction c_token_action_from_hash(VALUE hash)
{
    return REWRITE_ACTION_KEEP;
}

LIB_RUBY_PARSER_LexStateAction c_lex_state_action_from_hash(VALUE hash)
{
    LIB_RUBY_PARSER_LexStateAction result = {.tag = LEX_STATE_ACTION_KEEP};
    return result;
}

LIB_RUBY_PARSER_TokenRewriterResult c_token_rewriter_result_from_ruby_hash(VALUE hash)
{
    VALUE rb_rewritten_token = rb_hash_aref(hash, rb_sym_from_cstr("rewritten_token"));
    if (NIL_P(rb_rewritten_token))
    {
        rb_raise(rb_eTypeError, ":rewritten_token must be a Token");
    }
    LIB_RUBY_PARSER_TokenPtr rewritten_token_ptr = c_token_from_ruby_token(rb_rewritten_token);

    VALUE rb_token_action = rb_hash_aref(hash, rb_sym_from_cstr("token_action"));
    LIB_RUBY_PARSER_RewriteAction token_action;
    if (NIL_P(rb_token_action))
    {
        token_action = REWRITE_ACTION_KEEP;
    }
    else if (RB_TYPE_P(rb_token_action, T_HASH))
    {
        token_action = c_token_action_from_hash(rb_token_action);
    }
    else
    {
        rb_raise(rb_eTypeError, ":token_action must be a Hash or nil");
    }

    VALUE rb_lex_state_action = rb_hash_aref(hash, rb_sym_from_cstr("lex_state_action"));
    LIB_RUBY_PARSER_LexStateAction lex_state_action;
    if (NIL_P(rb_lex_state_action))
    {
        lex_state_action.tag = LEX_STATE_ACTION_KEEP;
    }
    else if (RB_TYPE_P(rb_lex_state_action, T_HASH))
    {
        lex_state_action = c_lex_state_action_from_hash(rb_lex_state_action);
    }
    else
    {
        rb_raise(rb_eTypeError, ":lex_state_action must be a Hash or nil");
    }

    LIB_RUBY_PARSER_TokenRewriterResult result = {
        .rewritten_token = rewritten_token_ptr,
        .token_action = token_action,
        .lex_state_action = lex_state_action};
    return result;
}

LIB_RUBY_PARSER_TokenRewriterResult rb_token_rewriter_wrapper(LIB_RUBY_PARSER_TokenPtr token, LIB_RUBY_PARSER_SharedByteList input, void *state)
{
    VALUE rb_token_rewriter = (VALUE)state;

    VALUE rb_token = convert_Token(*token);
    token->token_value.raw.ptr = NULL;

    VALUE rb_input = rb_external_str_new((char *)(input.ptr), input.len);

    VALUE rb_token_rewriter_result = rb_proc_call(rb_token_rewriter, rb_ary_new_from_args(2, rb_token, rb_input));
    if (!RB_TYPE_P(rb_token_rewriter_result, T_HASH))
    {
        rb_raise(rb_eTypeError, ":token_rewriter must return a Hash");
    }

    return c_token_rewriter_result_from_ruby_hash(rb_token_rewriter_result);
}

#endif // LIB_RUBY_PARSER_TOKEN_REWRITER_H
