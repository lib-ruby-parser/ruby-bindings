#ifndef LIB_RUBY_PARSER_CONVERT_KNOWN_H
#define LIB_RUBY_PARSER_CONVERT_KNOWN_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"

VALUE convert_NodeList(NodeList *list)
{
    VALUE result = rb_ary_new_capa(list->len);
    for (uint32_t i = 0; i < list->len; i++)
    {
        rb_ary_push(result, convert_Node(&(list->list[i])));
    }
    return result;
}

VALUE convert_Loc(Loc *loc)
{
    if (loc == NULL)
    {
        return Qnil;
    }
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Loc = rb_const_get(lib_ruby_parser_mod, rb_intern("Loc"));
    VALUE result = rb_obj_alloc(rb_Loc);
    rb_ivar_set(result, rb_intern("@begin"), convert_uint32_t(loc->begin));
    rb_ivar_set(result, rb_intern("@end"), convert_uint32_t(loc->end));
    return result;
}

VALUE convert_Token(Token *token)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Token = rb_const_get(lib_ruby_parser_mod, rb_intern("Token"));
    VALUE result = rb_obj_alloc(rb_Token);
    rb_ivar_set(result, rb_intern("@token_type"), INT2FIX(token->token_type));
    rb_ivar_set(result, rb_intern("@token_name"), rb_str_new_cstr(token_name(token->token_type)));
    rb_ivar_set(result, rb_intern("@loc"), convert_Loc(token->loc));
    return result;
}

VALUE convert_ErrorLevel(ErrorLevel level)
{
    switch (level)
    {
    case ERROR_LEVEL_WARNING:
        return ID2SYM(rb_intern("warning"));
    case ERROR_LEVEL_ERROR:
        return ID2SYM(rb_intern("error"));
    }
}

VALUE convert_Diagnostic(Diagnostic *diagnostic)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Diagnostic = rb_const_get(lib_ruby_parser_mod, rb_intern("Diagnostic"));
    VALUE result = rb_obj_alloc(rb_Diagnostic);
    rb_ivar_set(result, rb_intern("@level"), convert_ErrorLevel(diagnostic->level));
    rb_ivar_set(result, rb_intern("@message"), rb_str_new_cstr(diagnostic_render_message(*diagnostic)));
    rb_ivar_set(result, rb_intern("@loc"), convert_Loc(diagnostic->loc));
    return result;
}

VALUE convert_Comment(Comment *comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Comment = rb_const_get(lib_ruby_parser_mod, rb_intern("Comment"));
    VALUE result = rb_obj_alloc(rb_Comment);
    rb_ivar_set(result, rb_intern("@location"), convert_Loc(comment->location));
    return result;
}

VALUE convert_MagicCommentKind(MagicCommentKind kind)
{
    switch (kind)
    {
    case MAGIC_COMMENT_KIND_ENCODING:
        return ID2SYM(rb_intern("encoding"));
    case MAGIC_COMMENT_KIND_FROZEN_STRING_LITERAL:
        return ID2SYM(rb_intern("frozen_string_literal"));
    case MAGIC_COMMENT_KIND_WARN_INDENT:
        return ID2SYM(rb_intern("warn_indent"));
    case MAGIC_COMMENT_KIND_SHAREABLE_CONSTANT_VALUE:
        return ID2SYM(rb_intern("shareable_constant_value"));
    }
}

VALUE convert_MagicComment(MagicComment *magic_comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_MagicComment = rb_const_get(lib_ruby_parser_mod, rb_intern("MagicComment"));
    VALUE result = rb_obj_alloc(rb_MagicComment);
    rb_ivar_set(result, rb_intern("@kind"), convert_MagicCommentKind(magic_comment->kind));
    rb_ivar_set(result, rb_intern("@key_l"), convert_Loc(magic_comment->key_l));
    rb_ivar_set(result, rb_intern("@value_l"), convert_Loc(magic_comment->value_l));
    return result;
}

VALUE convert_String(char *string)
{
    if (string == NULL)
    {
        return Qnil;
    }
    return rb_utf8_str_new_cstr(string);
}

VALUE convert_uint32_t(uint32_t value)
{
    return INT2FIX(value);
}

#endif // LIB_RUBY_PARSER_CONVERT_KNOWN_H
