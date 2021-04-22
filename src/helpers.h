#ifndef LIB_RUBY_PARSER_HELPERS_H
#define LIB_RUBY_PARSER_HELPERS_H

#include <ruby.h>
#include "../c-bindings/lib-ruby-parser.h"

#define UNUSED(x) (void)(x)

VALUE rb_sym_from_cstr(char *cstr)
{
    return ID2SYM(rb_intern(cstr));
}

char *copy_string(const char *source, uint32_t length)
{
    char *out = (char *)malloc(length + 1);
    memcpy(out, source, length);
    out[length] = '\0';
    return out;
}

LIB_RUBY_PARSER_ByteList byte_list_from_rstring(VALUE string)
{
    char *ptr = StringValueCStr(string);
    uint32_t length = strlen(ptr);
    ptr = copy_string(ptr, length);

    LIB_RUBY_PARSER_ByteList result = {
        .ptr = (uint8_t *)ptr,
        .len = length,
        .capacity = length};

    return result;
}

#endif // LIB_RUBY_PARSER_HELPERS_H
