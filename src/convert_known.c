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
