#include "convert_known.h"

VALUE convert_Node(struct Node *node);

VALUE convert_NodeList(struct NodeList *list)
{
    VALUE result = rb_ary_new_capa(list->len);
    for (uint32_t i = 0; i < list->len; i++)
    {
        rb_ary_push(result, convert_Node(&(list->list[i])));
    }
    return result;
}

VALUE convert_Range(struct Range *range)
{
    if (range == NULL)
    {
        return Qnil;
    }
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Range = rb_const_get(lib_ruby_parser_mod, rb_intern("Range"));
    VALUE result = rb_obj_alloc(rb_Range);
    rb_ivar_set(result, rb_intern("@begin_pos"), convert_uint32_t(range->begin_pos));
    rb_ivar_set(result, rb_intern("@end_pos"), convert_uint32_t(range->end_pos));
    return result;
}

VALUE convert_Loc(struct Loc *loc)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Loc = rb_const_get(lib_ruby_parser_mod, rb_intern("Loc"));
    VALUE result = rb_obj_alloc(rb_Loc);
    rb_ivar_set(result, rb_intern("@begin"), convert_uint32_t(loc->begin));
    rb_ivar_set(result, rb_intern("@end"), convert_uint32_t(loc->end));
    return result;
}

VALUE convert_Token(struct Token *token)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Token = rb_const_get(lib_ruby_parser_mod, rb_intern("Token"));
    VALUE result = rb_obj_alloc(rb_Token);
    rb_ivar_set(result, rb_intern("@token_type"), INT2FIX(token->token_type));
    rb_ivar_set(result, rb_intern("@token_name"), rb_str_new_cstr(token_name(token->token_type)));
    rb_ivar_set(result, rb_intern("@loc"), convert_Loc(token->loc));
    return result;
}

VALUE convert_ErrorLevel(enum ErrorLevel level)
{
    switch (level)
    {
    case ERROR_LEVEL_WARNING:
        return ID2SYM(rb_intern("warning"));
    case ERROR_LEVEL_ERROR:
        return ID2SYM(rb_intern("error"));
    }
}

VALUE convert_Diagnostic(struct Diagnostic *diagnostic)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Diagnostic = rb_const_get(lib_ruby_parser_mod, rb_intern("Diagnostic"));
    VALUE result = rb_obj_alloc(rb_Diagnostic);
    rb_ivar_set(result, rb_intern("@level"), convert_ErrorLevel(diagnostic->level));
    rb_ivar_set(result, rb_intern("@message"), convert_String(diagnostic->message));
    rb_ivar_set(result, rb_intern("@range"), convert_Range(diagnostic->range));
    return result;
}

VALUE convert_Comment(struct Comment *comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_Comment = rb_const_get(lib_ruby_parser_mod, rb_intern("Comment"));
    VALUE result = rb_obj_alloc(rb_Comment);
    rb_ivar_set(result, rb_intern("@location"), convert_Range(comment->location));
    return result;
}

VALUE convert_MagicCommentKind(enum MagicCommentKind kind)
{
    switch (kind)
    {
    case ENCODING:
        return ID2SYM(rb_intern("encoding"));
    case FROZEN_STRING_LITERAL:
        return ID2SYM(rb_intern("frozen_string_literal"));
    case WARN_INDENT:
        return ID2SYM(rb_intern("warn_indent"));
    case SHAREABLE_CONSTANT_VALUE:
        return ID2SYM(rb_intern("shareable_constant_value"));
    }
}

VALUE convert_MagicComment(struct MagicComment *magic_comment)
{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_MagicComment = rb_const_get(lib_ruby_parser_mod, rb_intern("MagicComment"));
    VALUE result = rb_obj_alloc(rb_MagicComment);
    rb_ivar_set(result, rb_intern("@kind"), convert_MagicCommentKind(magic_comment->kind));
    rb_ivar_set(result, rb_intern("@key_l"), convert_Range(magic_comment->key_l));
    rb_ivar_set(result, rb_intern("@value_l"), convert_Range(magic_comment->value_l));
    return result;
}

VALUE convert_String(char *string)
{
    if (string == NULL)
    {
        return Qnil;
    }
    return rb_str_new_cstr(string);
}

VALUE convert_uint32_t(uint32_t value)
{
    return INT2FIX(value);
}
