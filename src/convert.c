#include "convert.h"
#include "convert_known.h"

VALUE convert_Alias(struct Alias *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Alias"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@to"), convert_Node(node->to));
    rb_ivar_set(result, rb_intern("@from"), convert_Node(node->from));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_AndAsgn(struct AndAsgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("AndAsgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_And(struct And *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("And"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@lhs"), convert_Node(node->lhs));
    rb_ivar_set(result, rb_intern("@rhs"), convert_Node(node->rhs));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Arg(struct Arg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Arg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Args(struct Args *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Args"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    return result;
}
VALUE convert_Array(struct Array *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Array"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@elements"), convert_NodeList(node->elements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ArrayPattern(struct ArrayPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ArrayPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@elements"), convert_NodeList(node->elements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ArrayPatternWithTail(struct ArrayPatternWithTail *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ArrayPatternWithTail"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@elements"), convert_NodeList(node->elements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_BackRef(struct BackRef *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("BackRef"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Begin(struct Begin *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Begin"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@statements"), convert_NodeList(node->statements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Block(struct Block *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Block"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@call"), convert_Node(node->call));
    rb_ivar_set(result, rb_intern("@args"), convert_Node(node->args));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_BlockPass(struct BlockPass *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("BlockPass"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Blockarg(struct Blockarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Blockarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Break(struct Break *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Break"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Case(struct Case *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Case"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expr"), convert_Node(node->expr));
    rb_ivar_set(result, rb_intern("@when_bodies"), convert_NodeList(node->when_bodies));
    rb_ivar_set(result, rb_intern("@else_body"), convert_Node(node->else_body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@else_l"), convert_Range(node->else_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_CaseMatch(struct CaseMatch *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("CaseMatch"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expr"), convert_Node(node->expr));
    rb_ivar_set(result, rb_intern("@in_bodies"), convert_NodeList(node->in_bodies));
    rb_ivar_set(result, rb_intern("@else_body"), convert_Node(node->else_body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@else_l"), convert_Range(node->else_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Casgn(struct Casgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Casgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@scope"), convert_Node(node->scope));
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@double_colon_l"), convert_Range(node->double_colon_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Cbase(struct Cbase *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Cbase"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Class(struct Class *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Class"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_Node(node->name));
    rb_ivar_set(result, rb_intern("@superclass"), convert_Node(node->superclass));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Complex(struct Complex *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Complex"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_String(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Const(struct Const *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Const"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@scope"), convert_Node(node->scope));
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@double_colon_l"), convert_Range(node->double_colon_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ConstPattern(struct ConstPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ConstPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@const_"), convert_Node(node->const_));
    rb_ivar_set(result, rb_intern("@pattern"), convert_Node(node->pattern));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_CSend(struct CSend *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("CSend"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@method_name"), convert_String(node->method_name));
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@dot_l"), convert_Range(node->dot_l));
    rb_ivar_set(result, rb_intern("@selector_l"), convert_Range(node->selector_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Cvar(struct Cvar *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Cvar"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Cvasgn(struct Cvasgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Cvasgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Def(struct Def *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Def"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@args"), convert_Node(node->args));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@assignment_l"), convert_Range(node->assignment_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Defined(struct Defined *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Defined"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Defs(struct Defs *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Defs"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@definee"), convert_Node(node->definee));
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@args"), convert_Node(node->args));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@assignment_l"), convert_Range(node->assignment_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Dstr(struct Dstr *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Dstr"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Dsym(struct Dsym *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Dsym"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_EFlipFlop(struct EFlipFlop *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("EFlipFlop"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@left"), convert_Node(node->left));
    rb_ivar_set(result, rb_intern("@right"), convert_Node(node->right));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_EmptyElse(struct EmptyElse *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("EmptyElse"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Encoding(struct Encoding *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Encoding"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Ensure(struct Ensure *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Ensure"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@ensure"), convert_Node(node->ensure));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Erange(struct Erange *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Erange"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@left"), convert_Node(node->left));
    rb_ivar_set(result, rb_intern("@right"), convert_Node(node->right));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_False(struct False *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("False"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_File(struct File *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("File"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_FindPattern(struct FindPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("FindPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@elements"), convert_NodeList(node->elements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Float(struct Float *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Float"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_String(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_For(struct For *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("For"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@iterator"), convert_Node(node->iterator));
    rb_ivar_set(result, rb_intern("@iteratee"), convert_Node(node->iteratee));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ForwardArg(struct ForwardArg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ForwardArg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ForwardedArgs(struct ForwardedArgs *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ForwardedArgs"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Gvar(struct Gvar *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Gvar"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Gvasgn(struct Gvasgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Gvasgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Hash(struct Hash *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Hash"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@pairs"), convert_NodeList(node->pairs));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwargs(struct Kwargs *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwargs"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@pairs"), convert_NodeList(node->pairs));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_HashPattern(struct HashPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("HashPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@elements"), convert_NodeList(node->elements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Heredoc(struct Heredoc *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Heredoc"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@heredoc_body_l"), convert_Range(node->heredoc_body_l));
    rb_ivar_set(result, rb_intern("@heredoc_end_l"), convert_Range(node->heredoc_end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_If(struct If *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("If"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@if_true"), convert_Node(node->if_true));
    rb_ivar_set(result, rb_intern("@if_false"), convert_Node(node->if_false));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@else_l"), convert_Range(node->else_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_IfGuard(struct IfGuard *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("IfGuard"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_IfMod(struct IfMod *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("IfMod"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@if_true"), convert_Node(node->if_true));
    rb_ivar_set(result, rb_intern("@if_false"), convert_Node(node->if_false));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_IfTernary(struct IfTernary *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("IfTernary"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@if_true"), convert_Node(node->if_true));
    rb_ivar_set(result, rb_intern("@if_false"), convert_Node(node->if_false));
    rb_ivar_set(result, rb_intern("@question_l"), convert_Range(node->question_l));
    rb_ivar_set(result, rb_intern("@colon_l"), convert_Range(node->colon_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_IFlipFlop(struct IFlipFlop *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("IFlipFlop"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@left"), convert_Node(node->left));
    rb_ivar_set(result, rb_intern("@right"), convert_Node(node->right));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchPattern(struct MatchPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@pattern"), convert_Node(node->pattern));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchPatternP(struct MatchPatternP *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchPatternP"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@pattern"), convert_Node(node->pattern));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_InPattern(struct InPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("InPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@pattern"), convert_Node(node->pattern));
    rb_ivar_set(result, rb_intern("@guard"), convert_Node(node->guard));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Index(struct Index *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Index"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@indexes"), convert_NodeList(node->indexes));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_IndexAsgn(struct IndexAsgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("IndexAsgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@indexes"), convert_NodeList(node->indexes));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Int(struct Int *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Int"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_String(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Irange(struct Irange *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Irange"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@left"), convert_Node(node->left));
    rb_ivar_set(result, rb_intern("@right"), convert_Node(node->right));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Ivar(struct Ivar *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Ivar"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Ivasgn(struct Ivasgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Ivasgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwarg(struct Kwarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_KwBegin(struct KwBegin *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("KwBegin"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@statements"), convert_NodeList(node->statements));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwnilarg(struct Kwnilarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwnilarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwoptarg(struct Kwoptarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwoptarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@default_"), convert_Node(node->default_));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwrestarg(struct Kwrestarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwrestarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Kwsplat(struct Kwsplat *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Kwsplat"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Lambda(struct Lambda *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Lambda"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Line(struct Line *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Line"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Lvar(struct Lvar *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Lvar"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Lvasgn(struct Lvasgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Lvasgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Masgn(struct Masgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Masgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@lhs"), convert_Node(node->lhs));
    rb_ivar_set(result, rb_intern("@rhs"), convert_Node(node->rhs));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchAlt(struct MatchAlt *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchAlt"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@lhs"), convert_Node(node->lhs));
    rb_ivar_set(result, rb_intern("@rhs"), convert_Node(node->rhs));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchAs(struct MatchAs *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchAs"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@as_"), convert_Node(node->as_));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchCurrentLine(struct MatchCurrentLine *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchCurrentLine"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@re"), convert_Node(node->re));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchNilPattern(struct MatchNilPattern *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchNilPattern"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchRest(struct MatchRest *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchRest"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_Node(node->name));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchVar(struct MatchVar *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchVar"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_MatchWithLvasgn(struct MatchWithLvasgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("MatchWithLvasgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@re"), convert_Node(node->re));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Mlhs(struct Mlhs *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Mlhs"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@items"), convert_NodeList(node->items));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Module(struct Module *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Module"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_Node(node->name));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Next(struct Next *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Next"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Nil(struct Nil *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Nil"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_NthRef(struct NthRef *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("NthRef"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Numblock(struct Numblock *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Numblock"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@call"), convert_Node(node->call));
    rb_ivar_set(result, rb_intern("@numargs"), convert_uint32_t(node->numargs));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_OpAsgn(struct OpAsgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("OpAsgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@operator"), convert_String(node->operator));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Optarg(struct Optarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Optarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@default_"), convert_Node(node->default_));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Or(struct Or *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Or"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@lhs"), convert_Node(node->lhs));
    rb_ivar_set(result, rb_intern("@rhs"), convert_Node(node->rhs));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_OrAsgn(struct OrAsgn *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("OrAsgn"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Pair(struct Pair *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Pair"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@key"), convert_Node(node->key));
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Pin(struct Pin *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Pin"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@var"), convert_Node(node->var));
    rb_ivar_set(result, rb_intern("@selector_l"), convert_Range(node->selector_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Postexe(struct Postexe *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Postexe"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Preexe(struct Preexe *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Preexe"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Procarg0(struct Procarg0 *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Procarg0"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Rational(struct Rational *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Rational"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_String(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Redo(struct Redo *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Redo"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_RegOpt(struct RegOpt *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("RegOpt"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@options"), convert_String(node->options));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Regexp(struct Regexp *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Regexp"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@options"), convert_Node(node->options));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Rescue(struct Rescue *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Rescue"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@rescue_bodies"), convert_NodeList(node->rescue_bodies));
    rb_ivar_set(result, rb_intern("@else_"), convert_Node(node->else_));
    rb_ivar_set(result, rb_intern("@else_l"), convert_Range(node->else_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_RescueBody(struct RescueBody *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("RescueBody"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@exc_list"), convert_Node(node->exc_list));
    rb_ivar_set(result, rb_intern("@exc_var"), convert_Node(node->exc_var));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@assoc_l"), convert_Range(node->assoc_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Restarg(struct Restarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Restarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@name_l"), convert_Range(node->name_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Retry(struct Retry *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Retry"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Return(struct Return *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Return"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_SClass(struct SClass *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("SClass"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expr"), convert_Node(node->expr));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Self_(struct Self_ *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Self_"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Send(struct Send *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Send"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@recv"), convert_Node(node->recv));
    rb_ivar_set(result, rb_intern("@method_name"), convert_String(node->method_name));
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@dot_l"), convert_Range(node->dot_l));
    rb_ivar_set(result, rb_intern("@selector_l"), convert_Range(node->selector_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Shadowarg(struct Shadowarg *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Shadowarg"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Splat(struct Splat *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Splat"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_Node(node->value));
    rb_ivar_set(result, rb_intern("@operator_l"), convert_Range(node->operator_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Str(struct Str *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Str"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@value"), convert_String(node->value));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Super(struct Super *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Super"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Sym(struct Sym *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Sym"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@name"), convert_String(node->name));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_True(struct True *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("True"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Undef(struct Undef *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Undef"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@names"), convert_NodeList(node->names));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_UnlessGuard(struct UnlessGuard *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("UnlessGuard"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Until(struct Until *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Until"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_UntilPost(struct UntilPost *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("UntilPost"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_When(struct When *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("When"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@patterns"), convert_NodeList(node->patterns));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_While(struct While *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("While"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_WhilePost(struct WhilePost *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("WhilePost"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@cond"), convert_Node(node->cond));
    rb_ivar_set(result, rb_intern("@body"), convert_Node(node->body));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_XHeredoc(struct XHeredoc *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("XHeredoc"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@heredoc_body_l"), convert_Range(node->heredoc_body_l));
    rb_ivar_set(result, rb_intern("@heredoc_end_l"), convert_Range(node->heredoc_end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Xstr(struct Xstr *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Xstr"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@parts"), convert_NodeList(node->parts));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_Yield(struct Yield *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("Yield"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@args"), convert_NodeList(node->args));
    rb_ivar_set(result, rb_intern("@keyword_l"), convert_Range(node->keyword_l));
    rb_ivar_set(result, rb_intern("@begin_l"), convert_Range(node->begin_l));
    rb_ivar_set(result, rb_intern("@end_l"), convert_Range(node->end_l));
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}
VALUE convert_ZSuper(struct ZSuper *node) {
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern("ZSuper"));
    VALUE result = rb_obj_alloc(node_klass);
    rb_ivar_set(result, rb_intern("@expression_l"), convert_Range(node->expression_l));
    return result;
}

VALUE convert_Node(struct Node* node)
{
    if (node == NULL)
    {
        return Qnil;
    }
    switch(node->node_type)
    {
        case NODE_ALIAS:
            return convert_Alias(node->inner->_alias);
        case NODE_AND_ASGN:
            return convert_AndAsgn(node->inner->_and_asgn);
        case NODE_AND:
            return convert_And(node->inner->_and);
        case NODE_ARG:
            return convert_Arg(node->inner->_arg);
        case NODE_ARGS:
            return convert_Args(node->inner->_args);
        case NODE_ARRAY:
            return convert_Array(node->inner->_array);
        case NODE_ARRAY_PATTERN:
            return convert_ArrayPattern(node->inner->_array_pattern);
        case NODE_ARRAY_PATTERN_WITH_TAIL:
            return convert_ArrayPatternWithTail(node->inner->_array_pattern_with_tail);
        case NODE_BACK_REF:
            return convert_BackRef(node->inner->_back_ref);
        case NODE_BEGIN:
            return convert_Begin(node->inner->_begin);
        case NODE_BLOCK:
            return convert_Block(node->inner->_block);
        case NODE_BLOCK_PASS:
            return convert_BlockPass(node->inner->_block_pass);
        case NODE_BLOCKARG:
            return convert_Blockarg(node->inner->_blockarg);
        case NODE_BREAK_:
            return convert_Break(node->inner->_break_);
        case NODE_CASE:
            return convert_Case(node->inner->_case);
        case NODE_CASE_MATCH:
            return convert_CaseMatch(node->inner->_case_match);
        case NODE_CASGN:
            return convert_Casgn(node->inner->_casgn);
        case NODE_CBASE:
            return convert_Cbase(node->inner->_cbase);
        case NODE_CLASS:
            return convert_Class(node->inner->_class);
        case NODE_COMPLEX:
            return convert_Complex(node->inner->_complex);
        case NODE_CONST_:
            return convert_Const(node->inner->_const_);
        case NODE_CONST_PATTERN:
            return convert_ConstPattern(node->inner->_const_pattern);
        case NODE_CSEND:
            return convert_CSend(node->inner->_csend);
        case NODE_CVAR:
            return convert_Cvar(node->inner->_cvar);
        case NODE_CVASGN:
            return convert_Cvasgn(node->inner->_cvasgn);
        case NODE_DEF:
            return convert_Def(node->inner->_def);
        case NODE_DEFINED:
            return convert_Defined(node->inner->_defined);
        case NODE_DEFS:
            return convert_Defs(node->inner->_defs);
        case NODE_DSTR:
            return convert_Dstr(node->inner->_dstr);
        case NODE_DSYM:
            return convert_Dsym(node->inner->_dsym);
        case NODE_EFLIPFLOP:
            return convert_EFlipFlop(node->inner->_eflipflop);
        case NODE_EMPTY_ELSE:
            return convert_EmptyElse(node->inner->_empty_else);
        case NODE_ENCODING_:
            return convert_Encoding(node->inner->_encoding_);
        case NODE_ENSURE:
            return convert_Ensure(node->inner->_ensure);
        case NODE_ERANGE:
            return convert_Erange(node->inner->_erange);
        case NODE_FALSE_:
            return convert_False(node->inner->_false_);
        case NODE_FILE:
            return convert_File(node->inner->_file);
        case NODE_FIND_PATTERN:
            return convert_FindPattern(node->inner->_find_pattern);
        case NODE_FLOAT:
            return convert_Float(node->inner->_float);
        case NODE_FOR_:
            return convert_For(node->inner->_for_);
        case NODE_FORWARD_ARG:
            return convert_ForwardArg(node->inner->_forward_arg);
        case NODE_FORWARDED_ARGS:
            return convert_ForwardedArgs(node->inner->_forwarded_args);
        case NODE_GVAR:
            return convert_Gvar(node->inner->_gvar);
        case NODE_GVASGN:
            return convert_Gvasgn(node->inner->_gvasgn);
        case NODE_HASH:
            return convert_Hash(node->inner->_hash);
        case NODE_KWARGS:
            return convert_Kwargs(node->inner->_kwargs);
        case NODE_HASH_PATTERN:
            return convert_HashPattern(node->inner->_hash_pattern);
        case NODE_HEREDOC:
            return convert_Heredoc(node->inner->_heredoc);
        case NODE_IF_:
            return convert_If(node->inner->_if_);
        case NODE_IF_GUARD:
            return convert_IfGuard(node->inner->_if_guard);
        case NODE_IF_MOD:
            return convert_IfMod(node->inner->_if_mod);
        case NODE_IF_TERNARY:
            return convert_IfTernary(node->inner->_if_ternary);
        case NODE_IFLIPFLOP:
            return convert_IFlipFlop(node->inner->_iflipflop);
        case NODE_MATCH_PATTERN:
            return convert_MatchPattern(node->inner->_match_pattern);
        case NODE_MATCH_PATTERN_P:
            return convert_MatchPatternP(node->inner->_match_pattern_p);
        case NODE_IN_PATTERN:
            return convert_InPattern(node->inner->_in_pattern);
        case NODE_INDEX:
            return convert_Index(node->inner->_index);
        case NODE_INDEX_ASGN:
            return convert_IndexAsgn(node->inner->_index_asgn);
        case NODE_INT:
            return convert_Int(node->inner->_int);
        case NODE_IRANGE:
            return convert_Irange(node->inner->_irange);
        case NODE_IVAR:
            return convert_Ivar(node->inner->_ivar);
        case NODE_IVASGN:
            return convert_Ivasgn(node->inner->_ivasgn);
        case NODE_KWARG:
            return convert_Kwarg(node->inner->_kwarg);
        case NODE_KWBEGIN:
            return convert_KwBegin(node->inner->_kwbegin);
        case NODE_KWNILARG:
            return convert_Kwnilarg(node->inner->_kwnilarg);
        case NODE_KWOPTARG:
            return convert_Kwoptarg(node->inner->_kwoptarg);
        case NODE_KWRESTARG:
            return convert_Kwrestarg(node->inner->_kwrestarg);
        case NODE_KWSPLAT:
            return convert_Kwsplat(node->inner->_kwsplat);
        case NODE_LAMBDA:
            return convert_Lambda(node->inner->_lambda);
        case NODE_LINE:
            return convert_Line(node->inner->_line);
        case NODE_LVAR:
            return convert_Lvar(node->inner->_lvar);
        case NODE_LVASGN:
            return convert_Lvasgn(node->inner->_lvasgn);
        case NODE_MASGN:
            return convert_Masgn(node->inner->_masgn);
        case NODE_MATCH_ALT:
            return convert_MatchAlt(node->inner->_match_alt);
        case NODE_MATCH_AS:
            return convert_MatchAs(node->inner->_match_as);
        case NODE_MATCH_CURRENT_LINE:
            return convert_MatchCurrentLine(node->inner->_match_current_line);
        case NODE_MATCH_NIL_PATTERN:
            return convert_MatchNilPattern(node->inner->_match_nil_pattern);
        case NODE_MATCH_REST:
            return convert_MatchRest(node->inner->_match_rest);
        case NODE_MATCH_VAR:
            return convert_MatchVar(node->inner->_match_var);
        case NODE_MATCH_WITH_LVASGN:
            return convert_MatchWithLvasgn(node->inner->_match_with_lvasgn);
        case NODE_MLHS:
            return convert_Mlhs(node->inner->_mlhs);
        case NODE_MODULE:
            return convert_Module(node->inner->_module);
        case NODE_NEXT:
            return convert_Next(node->inner->_next);
        case NODE_NIL:
            return convert_Nil(node->inner->_nil);
        case NODE_NTH_REF:
            return convert_NthRef(node->inner->_nth_ref);
        case NODE_NUMBLOCK:
            return convert_Numblock(node->inner->_numblock);
        case NODE_OP_ASGN:
            return convert_OpAsgn(node->inner->_op_asgn);
        case NODE_OPTARG:
            return convert_Optarg(node->inner->_optarg);
        case NODE_OR:
            return convert_Or(node->inner->_or);
        case NODE_OR_ASGN:
            return convert_OrAsgn(node->inner->_or_asgn);
        case NODE_PAIR:
            return convert_Pair(node->inner->_pair);
        case NODE_PIN:
            return convert_Pin(node->inner->_pin);
        case NODE_POSTEXE:
            return convert_Postexe(node->inner->_postexe);
        case NODE_PREEXE:
            return convert_Preexe(node->inner->_preexe);
        case NODE_PROCARG0:
            return convert_Procarg0(node->inner->_procarg0);
        case NODE_RATIONAL:
            return convert_Rational(node->inner->_rational);
        case NODE_REDO:
            return convert_Redo(node->inner->_redo);
        case NODE_REG_OPT:
            return convert_RegOpt(node->inner->_reg_opt);
        case NODE_REGEXP:
            return convert_Regexp(node->inner->_regexp);
        case NODE_RESCUE:
            return convert_Rescue(node->inner->_rescue);
        case NODE_RESCUE_BODY:
            return convert_RescueBody(node->inner->_rescue_body);
        case NODE_RESTARG:
            return convert_Restarg(node->inner->_restarg);
        case NODE_RETRY:
            return convert_Retry(node->inner->_retry);
        case NODE_RETURN_:
            return convert_Return(node->inner->_return_);
        case NODE_SCLASS:
            return convert_SClass(node->inner->_sclass);
        case NODE_SELF_:
            return convert_Self_(node->inner->_self_);
        case NODE_SEND:
            return convert_Send(node->inner->_send);
        case NODE_SHADOWARG:
            return convert_Shadowarg(node->inner->_shadowarg);
        case NODE_SPLAT:
            return convert_Splat(node->inner->_splat);
        case NODE_STR_:
            return convert_Str(node->inner->_str_);
        case NODE_SUPER_:
            return convert_Super(node->inner->_super_);
        case NODE_SYM:
            return convert_Sym(node->inner->_sym);
        case NODE_TRUE_:
            return convert_True(node->inner->_true_);
        case NODE_UNDEF:
            return convert_Undef(node->inner->_undef);
        case NODE_UNLESS_GUARD:
            return convert_UnlessGuard(node->inner->_unless_guard);
        case NODE_UNTIL:
            return convert_Until(node->inner->_until);
        case NODE_UNTIL_POST:
            return convert_UntilPost(node->inner->_until_post);
        case NODE_WHEN:
            return convert_When(node->inner->_when);
        case NODE_WHILE_:
            return convert_While(node->inner->_while_);
        case NODE_WHILE_POST:
            return convert_WhilePost(node->inner->_while_post);
        case NODE_X_HEREDOC:
            return convert_XHeredoc(node->inner->_x_heredoc);
        case NODE_XSTR:
            return convert_Xstr(node->inner->_xstr);
        case NODE_YIELD_:
            return convert_Yield(node->inner->_yield_);
        case NODE_ZSUPER:
            return convert_ZSuper(node->inner->_zsuper);
    }
}

void InitNodeClasses(VALUE lib_ruby_parser_mod)
{
    VALUE rb_Node = rb_define_class_under(lib_ruby_parser_mod, "Node", rb_cObject);
    rb_define_class_under(lib_ruby_parser_mod, "Alias", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "AndAsgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "And", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Arg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Args", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Array", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ArrayPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ArrayPatternWithTail", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "BackRef", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Begin", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Block", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "BlockPass", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Blockarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Break", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Case", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "CaseMatch", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Casgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Cbase", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Class", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Complex", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Const", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ConstPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "CSend", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Cvar", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Cvasgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Def", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Defined", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Defs", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Dstr", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Dsym", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "EFlipFlop", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "EmptyElse", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Encoding", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Ensure", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Erange", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "False", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "File", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "FindPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Float", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "For", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ForwardArg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ForwardedArgs", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Gvar", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Gvasgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Hash", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwargs", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "HashPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Heredoc", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "If", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "IfGuard", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "IfMod", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "IfTernary", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "IFlipFlop", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchPatternP", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "InPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Index", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "IndexAsgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Int", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Irange", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Ivar", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Ivasgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "KwBegin", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwnilarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwoptarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwrestarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Kwsplat", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Lambda", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Line", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Lvar", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Lvasgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Masgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchAlt", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchAs", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchCurrentLine", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchNilPattern", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchRest", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchVar", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "MatchWithLvasgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Mlhs", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Module", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Next", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Nil", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "NthRef", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Numblock", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "OpAsgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Optarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Or", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "OrAsgn", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Pair", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Pin", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Postexe", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Preexe", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Procarg0", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Rational", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Redo", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "RegOpt", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Regexp", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Rescue", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "RescueBody", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Restarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Retry", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Return", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "SClass", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Self_", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Send", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Shadowarg", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Splat", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Str", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Super", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Sym", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "True", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Undef", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "UnlessGuard", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Until", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "UntilPost", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "When", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "While", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "WhilePost", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "XHeredoc", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Xstr", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "Yield", rb_Node);
    rb_define_class_under(lib_ruby_parser_mod, "ZSuper", rb_Node);
}
