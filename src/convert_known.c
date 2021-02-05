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

VALUE InitKnownClasses(VALUE lib_ruby_parser_mod)
{
    rb_define_class_under(lib_ruby_parser_mod, "Range", rb_cObject);
}
