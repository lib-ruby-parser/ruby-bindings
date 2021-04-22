#ifndef LIB_RUBY_PARSER_CONVERT_KNOWN_H
#define LIB_RUBY_PARSER_CONVERT_KNOWN_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"
#include "helpers.h"

VALUE convert_Bytes(LIB_RUBY_PARSER_Bytes bytes);
VALUE convert_StringValue(LIB_RUBY_PARSER_StringValue string_value);
VALUE convert_LexState(LIB_RUBY_PARSER_LexState lex_state);
VALUE convert_uint32_t(uint32_t value);

VALUE convert_NodeList(LIB_RUBY_PARSER_NodeList node_list)
{
    VALUE result = rb_ary_new_capa(node_list.len);
    for (uint32_t i = 0; i < node_list.len; i++)
    {
        LIB_RUBY_PARSER_NodePtr node_ptr = &(node_list.ptr[i]);
        rb_ary_push(result, convert_NodePtr(node_ptr));
    }
    return result;
}

VALUE convert_MaybeNodePtr(LIB_RUBY_PARSER_MaybeNodePtr maybe_node_ptr)
{
    if (maybe_node_ptr == NULL)
    {
        return Qnil;
    }
    return convert_NodePtr(maybe_node_ptr);
}

VALUE convert_MaybeLoc(LIB_RUBY_PARSER_MaybeLoc maybe_loc)
{
    if (maybe_loc.tag == MAYBE_LOC_NONE)
    {
        return Qnil;
    }
    return convert_Loc(maybe_loc.some);
}

VALUE convert_Loc(LIB_RUBY_PARSER_Loc loc)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Loc = rb_const_get(lib_ruby_parser_mod, rb_intern("Loc"));
    VALUE result = rb_obj_alloc(rb_Loc);
    rb_ivar_set(result, rb_intern("@begin"), convert_uint32_t(loc.begin));
    rb_ivar_set(result, rb_intern("@end"), convert_uint32_t(loc.end));
    return result;
}

VALUE convert_Token(LIB_RUBY_PARSER_Token token)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Token = rb_const_get(lib_ruby_parser_mod, rb_intern("Token"));
    VALUE result = rb_obj_alloc(rb_Token);
    rb_ivar_set(result, rb_intern("@token_type"), INT2FIX(token.token_type));
    rb_ivar_set(result, rb_intern("@token_name"), rb_str_new_cstr(lib_ruby_parser_token_name(token.token_type)));
    rb_ivar_set(result, rb_intern("@token_value"), convert_Bytes(token.token_value));
    rb_ivar_set(result, rb_intern("@lex_state_before"), convert_LexState(token.lex_state_before));
    rb_ivar_set(result, rb_intern("@lex_state_after"), convert_LexState(token.lex_state_after));
    rb_ivar_set(result, rb_intern("@loc"), convert_Loc(token.loc));
    return result;
}

VALUE convert_TokenList(LIB_RUBY_PARSER_TokenList token_list)
{
    VALUE result = rb_ary_new_capa(token_list.len);
    for (uint32_t i = 0; i < token_list.len; i++)
    {
        LIB_RUBY_PARSER_Token token = token_list.ptr[i];
        rb_ary_push(result, convert_Token(token));
    }
    return result;
}

VALUE convert_ErrorLevel(LIB_RUBY_PARSER_ErrorLevel level)
{
    switch (level)
    {
    case ERROR_LEVEL_WARNING:
        return ID2SYM(rb_intern("warning"));
    case ERROR_LEVEL_ERROR:
        return ID2SYM(rb_intern("error"));
    }
}

VALUE convert_Diagnostic(LIB_RUBY_PARSER_Diagnostic diagnostic)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Diagnostic = rb_const_get(lib_ruby_parser_mod, rb_intern("Diagnostic"));
    VALUE result = rb_obj_alloc(rb_Diagnostic);
    rb_ivar_set(result, rb_intern("@level"), convert_ErrorLevel(diagnostic.level));
    rb_ivar_set(result, rb_intern("@message"), rb_str_new_cstr(lib_ruby_parser_diagnostic_render_message(diagnostic)));
    rb_ivar_set(result, rb_intern("@loc"), convert_Loc(diagnostic.loc));
    return result;
}

VALUE convert_DiagnosticList(LIB_RUBY_PARSER_DiagnosticList diagnostic_list)
{
    VALUE result = rb_ary_new_capa(diagnostic_list.len);
    for (uint32_t i = 0; i < diagnostic_list.len; i++)
    {
        LIB_RUBY_PARSER_Diagnostic diagnostic = diagnostic_list.ptr[i];
        rb_ary_push(result, convert_Diagnostic(diagnostic));
    }
    return result;
}

VALUE convert_Comment(LIB_RUBY_PARSER_Comment comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Comment = rb_const_get(lib_ruby_parser_mod, rb_intern("Comment"));
    VALUE result = rb_obj_alloc(rb_Comment);
    rb_ivar_set(result, rb_intern("@location"), convert_Loc(comment.location));
    return result;
}

VALUE convert_CommentList(LIB_RUBY_PARSER_CommentList comment_list)
{
    VALUE result = rb_ary_new_capa(comment_list.len);
    for (uint32_t i = 0; i < comment_list.len; i++)
    {
        LIB_RUBY_PARSER_Comment comment = comment_list.ptr[i];
        rb_ary_push(result, convert_Comment(comment));
    }
    return result;
}

VALUE convert_MagicCommentKind(LIB_RUBY_PARSER_MagicCommentKind kind)
{
    switch (kind)
    {
    case MAGIC_COMMENT_KIND_ENCODING:
        return ID2SYM(rb_intern("encoding"));
    case MAGIC_COMMENT_KIND_FROZEN_STRING_LITERAL:
        return ID2SYM(rb_intern("frozen_string_literal"));
    case MAGIC_COMMENT_KIND_WARN_INDENT:
        return ID2SYM(rb_intern("warn_indent"));
    case MAGIC_COMMENT_KIND_SHAREABLE_CONTSTANT_VALUE:
        return ID2SYM(rb_intern("shareable_constant_value"));
    }
}

VALUE convert_MagicComment(LIB_RUBY_PARSER_MagicComment magic_comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_MagicComment = rb_const_get(lib_ruby_parser_mod, rb_intern("MagicComment"));
    VALUE result = rb_obj_alloc(rb_MagicComment);
    rb_ivar_set(result, rb_intern("@kind"), convert_MagicCommentKind(magic_comment.kind));
    rb_ivar_set(result, rb_intern("@key_l"), convert_Loc(magic_comment.key_l));
    rb_ivar_set(result, rb_intern("@value_l"), convert_Loc(magic_comment.value_l));
    return result;
}

VALUE convert_MagicCommentList(LIB_RUBY_PARSER_MagicCommentList magic_comment_list)
{
    VALUE result = rb_ary_new_capa(magic_comment_list.len);
    for (uint32_t i = 0; i < magic_comment_list.len; i++)
    {
        LIB_RUBY_PARSER_MagicComment magic_comment = magic_comment_list.ptr[i];
        rb_ary_push(result, convert_MagicComment(magic_comment));
    }
    return result;
}

VALUE convert_StringPtr(LIB_RUBY_PARSER_StringPtr string_ptr)
{
    if (string_ptr.len == 0)
    {
        return Qnil;
    }
    char *ptr = (char *)(string_ptr.ptr);
    string_ptr.ptr = NULL;
    return rb_utf8_str_new(ptr, string_ptr.len);
}

VALUE convert_Bytes(LIB_RUBY_PARSER_Bytes bytes)
{
    if (bytes.raw.len == 0)
    {
        return Qnil;
    }
    char *ptr = (char *)(bytes.raw.ptr);
    bytes.raw.ptr = NULL;
    return rb_utf8_str_new(ptr, bytes.raw.len);
}

VALUE convert_StringValue(LIB_RUBY_PARSER_StringValue string_value)
{
    return convert_Bytes(string_value.bytes);
}

VALUE convert_LexState(LIB_RUBY_PARSER_LexState lex_state)
{
    return convert_uint32_t(lex_state.value);
}

VALUE convert_uint32_t(uint32_t value)
{
    return INT2FIX(value);
}

VALUE convert_Input(LIB_RUBY_PARSER_DecodedInput input)
{
    uint32_t length = input.bytes.len;
    char *ptr = (char *)(input.bytes.ptr);
    input.bytes.ptr = NULL;
    return rb_utf8_str_new(ptr, length);
}

VALUE convert_ParserResult(LIB_RUBY_PARSER_ParserResult parser_result)
{
    VALUE rb_result = rb_hash_new();

    rb_hash_aset(rb_result, rb_sym_from_cstr("ast"), convert_MaybeNodePtr(parser_result.ast));
    rb_hash_aset(rb_result, rb_sym_from_cstr("tokens"), convert_TokenList(parser_result.tokens));
    rb_hash_aset(rb_result, rb_sym_from_cstr("diagnostics"), convert_DiagnosticList(parser_result.diagnostics));
    rb_hash_aset(rb_result, rb_sym_from_cstr("comments"), convert_CommentList(parser_result.comments));
    rb_hash_aset(rb_result, rb_sym_from_cstr("magic_comments"), convert_MagicCommentList(parser_result.magic_comments));
    rb_hash_aset(rb_result, rb_sym_from_cstr("input"), convert_Input(parser_result.input));

    lib_ruby_parser_free_parser_result(parser_result);

    return rb_result;
}

#endif // LIB_RUBY_PARSER_CONVERT_KNOWN_H
