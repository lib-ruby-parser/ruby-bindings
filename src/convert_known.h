#ifndef LIB_RUBY_PARSER_CONVERT_KNOWN_H
#define LIB_RUBY_PARSER_CONVERT_KNOWN_H

#include <ruby.h>
#include "../lib-ruby-parser.h"

VALUE convert_NodeList(struct NodeList *list);
VALUE convert_Range(struct Range *range);
VALUE convert_Loc(struct Loc *loc);
VALUE convert_Token(struct Token *token);
VALUE convert_String(char *string);
VALUE convert_uint32_t(uint32_t value);

VALUE InitKnownClasses(VALUE lib_ruby_parser_mod);

#endif // LIB_RUBY_PARSER_CONVERT_KNOWN_H
