#include <ruby.h>
#include "c-bindings/lib-ruby-parser.h"
#include "nodes.h"
#include "messages.h"

#define DBG(v)                        \
    rb_p(                             \
        rb_ary_new_from_args(         \
            4,                        \
            rb_str_new_cstr("line "), \
            INT2FIX(__LINE__),        \
            rb_str_new_cstr(#v),      \
            v))

// Ruby -> C
static LIB_RUBY_PARSER_ParserOptions LIB_RUBY_PARSER_ParserOptions__from_ruby(VALUE rb_options);
static LIB_RUBY_PARSER_ByteList LIB_RUBY_PARSER_ByteList__from_ruby(VALUE rb_byte_list);
static LIB_RUBY_PARSER_String LIB_RUBY_PARSER_String__from_ruby(VALUE rb_s);
static LIB_RUBY_PARSER_MaybeDecoder LIB_RUBY_PARSER_MaybeDecoder__from_ruby(VALUE rb_maybe_decoder);

// C -> Ruby
static VALUE LIB_RUBY_PARSER_Loc__to_ruby(LIB_RUBY_PARSER_Loc *loc);
static VALUE LIB_RUBY_PARSER_MaybeLoc__to_ruby(LIB_RUBY_PARSER_MaybeLoc *maybe_loc);
static VALUE LIB_RUBY_PARSER_NodeList__to_ruby(LIB_RUBY_PARSER_NodeList *list);
static VALUE LIB_RUBY_PARSER_String__to_ruby(LIB_RUBY_PARSER_String *string);
static VALUE LIB_RUBY_PARSER_MaybeString__to_ruby(LIB_RUBY_PARSER_MaybeString *maybe_string);
static VALUE LIB_RUBY_PARSER_MaybeNode__to_ruby(LIB_RUBY_PARSER_Node *node);
static VALUE LIB_RUBY_PARSER_NodePtr__to_ruby(LIB_RUBY_PARSER_Node **node);
static VALUE LIB_RUBY_PARSER_MaybeNodePtr__to_ruby(LIB_RUBY_PARSER_Node **maybe_node);
static VALUE LIB_RUBY_PARSER_ByteList__to_ruby(LIB_RUBY_PARSER_ByteList *byte_list);
static VALUE LIB_RUBY_PARSER_Bytes__to_ruby(LIB_RUBY_PARSER_Bytes *bytes);
static VALUE uint8_t__to_ruby(uint8_t *n);
static VALUE LIB_RUBY_PARSER_ParserResult__to_ruby(LIB_RUBY_PARSER_ParserResult result);
static VALUE LIB_RUBY_PARSER_Token__to_ruby(LIB_RUBY_PARSER_Token *token);
static VALUE LIB_RUBY_PARSER_TokenList__to_ruby(LIB_RUBY_PARSER_TokenList *token_list);
static VALUE LIB_RUBY_PARSER_ErrorLevel__to_ruby(LIB_RUBY_PARSER_ErrorLevel *level);
static VALUE LIB_RUBY_PARSER_Diagnostic__to_ruby(LIB_RUBY_PARSER_Diagnostic *diagnostic);
static VALUE LIB_RUBY_PARSER_DiagnosticList__to_ruby(LIB_RUBY_PARSER_DiagnosticList *diagnostic_list);
static VALUE LIB_RUBY_PARSER_CommentType__to_ruby(LIB_RUBY_PARSER_CommentType *comment_type);
static VALUE LIB_RUBY_PARSER_Comment__to_ruby(LIB_RUBY_PARSER_Comment *comment);
static VALUE LIB_RUBY_PARSER_CommentList__to_ruby(LIB_RUBY_PARSER_CommentList *comment_list);
static VALUE LIB_RUBY_PARSER_MagicCommentKind__to_ruby(LIB_RUBY_PARSER_MagicCommentKind *magic_comment_kind);
static VALUE LIB_RUBY_PARSER_MagicComment__to_ruby(LIB_RUBY_PARSER_MagicComment *magic_comment);
static VALUE LIB_RUBY_PARSER_MagicCommentList__to_ruby(LIB_RUBY_PARSER_MagicCommentList *magic_comment_list);
static VALUE LIB_RUBY_PARSER_SourceLine__to_ruby(LIB_RUBY_PARSER_SourceLine *source_line);
static VALUE LIB_RUBY_PARSER_SourceLineList__to_ruby(LIB_RUBY_PARSER_SourceLineList *source_line_list);
static VALUE LIB_RUBY_PARSER_DecodedInput__to_ruby(LIB_RUBY_PARSER_DecodedInput *decoded_input);

static VALUE rb_parse(VALUE self, VALUE rb_input, VALUE rb_options)
{
    (void)self;
    LIB_RUBY_PARSER_ParserOptions options = LIB_RUBY_PARSER_ParserOptions__from_ruby(rb_options);
    LIB_RUBY_PARSER_ByteList input = LIB_RUBY_PARSER_ByteList__from_ruby(rb_input);
    LIB_RUBY_PARSER_ParserResult result = LIB_RUBY_PARSER_parse(input, options);
    return LIB_RUBY_PARSER_ParserResult__to_ruby(result);
}

void Init_lib_ruby_parser()
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    rb_define_singleton_method(rb_mLibRubyParser, "parse", rb_parse, 2);
}

// __from_ruby
static LIB_RUBY_PARSER_ParserOptions LIB_RUBY_PARSER_ParserOptions__from_ruby(VALUE rb_options)
{
    if (NIL_P(rb_options))
    {
        rb_options = rb_hash_new();
    }
    Check_Type(rb_options, T_HASH);

    VALUE rb_buffer_name = rb_hash_aref(rb_options, CSTR_TO_SYM("buffer_name"));
    if (NIL_P(rb_buffer_name))
    {
        rb_buffer_name = rb_str_new_cstr("(eval)");
    }
    LIB_RUBY_PARSER_String buffer_name = LIB_RUBY_PARSER_String__from_ruby(rb_buffer_name);

    VALUE rb_maybe_decoder = rb_hash_aref(rb_options, CSTR_TO_SYM("decoder"));
    if (NIL_P(rb_maybe_decoder))
    {
        VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
        rb_maybe_decoder = rb_const_get(rb_mLibRubyParser, rb_intern("DEFAULT_DECODER"));
    }
    LIB_RUBY_PARSER_MaybeDecoder maybe_decoder = LIB_RUBY_PARSER_MaybeDecoder__from_ruby(rb_maybe_decoder);

    VALUE rb_record_tokens = rb_hash_aref(rb_options, CSTR_TO_SYM("record_tokens"));
    bool record_tokens = RTEST(rb_record_tokens);

    return (LIB_RUBY_PARSER_ParserOptions){
        .buffer_name = buffer_name,
        .decoder = maybe_decoder,
        .token_rewriter = {
            .token_rewriter = {.f = NULL, .state = NULL}},
        .record_tokens = record_tokens,
    };
}
static LIB_RUBY_PARSER_ByteList LIB_RUBY_PARSER_ByteList__from_ruby(VALUE rb_byte_list)
{
    Check_Type(rb_byte_list, T_STRING);
    size_t len = FIX2LONG(rb_funcall(rb_byte_list, rb_intern("bytesize"), 0));
    char *rb_ptr = StringValuePtr(rb_byte_list);
    char *ptr = malloc(len);
    memcpy(ptr, rb_ptr, len);
    return (LIB_RUBY_PARSER_ByteList){
        .ptr = ptr,
        .len = len,
        .capacity = len};
}
static LIB_RUBY_PARSER_String LIB_RUBY_PARSER_String__from_ruby(VALUE rb_s)
{
    Check_Type(rb_s, T_STRING);
    size_t len = FIX2LONG(rb_funcall(rb_s, rb_intern("bytesize"), 0));
    char *rb_ptr = StringValueCStr(rb_s);
    char *ptr = (char *)malloc(len);
    memcpy(ptr, rb_ptr, len);
    return (LIB_RUBY_PARSER_String){
        .ptr = ptr,
        .len = len,
        .capacity = len};
}
static VALUE rb_call_decoder(VALUE rb_decoder_call_args)
{
    VALUE rb_decoder = rb_ary_entry(rb_decoder_call_args, 0);
    VALUE rb_encoding = rb_ary_entry(rb_decoder_call_args, 1);
    VALUE rb_input = rb_ary_entry(rb_decoder_call_args, 2);

    VALUE rb_output = rb_funcall(rb_decoder, rb_intern("call"), 2, rb_encoding, rb_input);
    Check_Type(rb_output, T_STRING);

    return rb_output;
}
static VALUE rb_handle_decode_error(VALUE rb_success_ptr, VALUE rb_error)
{
    VALUE *rb_success = (VALUE *)rb_success_ptr;
    *rb_success = Qfalse;
    return rb_error;
}
static LIB_RUBY_PARSER_DecoderResult rb_decode(void *state, LIB_RUBY_PARSER_String encoding, LIB_RUBY_PARSER_ByteList input)
{
    VALUE rb_decoder = (VALUE)state;

    VALUE rb_encoding = rb_utf8_str_new(encoding.ptr, encoding.len);
    LIB_RUBY_PARSER_drop_string(&encoding);

    VALUE rb_input = rb_str_new(input.ptr, input.len);
    LIB_RUBY_PARSER_drop_byte_list(&input);

    VALUE rb_success = Qtrue;
    VALUE rb_decoder_call_args = rb_ary_new_from_args(3, rb_decoder, rb_encoding, rb_input);
    VALUE rb_output = rb_rescue2(
        rb_call_decoder,
        rb_decoder_call_args,
        rb_handle_decode_error,
        (VALUE)(&rb_success),
        rb_eException,
        0);

    if (RTEST(rb_success))
    {
        // rb_output is a String returned from decoder object
        LIB_RUBY_PARSER_ByteList decoded = LIB_RUBY_PARSER_ByteList__from_ruby(rb_output);
        return (LIB_RUBY_PARSER_DecoderResult){
            .tag = LIB_RUBY_PARSER_DECODER_RESULT_OK,
            .as = {.ok = decoded}};
    }
    else
    {
        // rb_output is an error
        VALUE rb_error_message = rb_funcall(rb_output, rb_intern("message"), 0);
        LIB_RUBY_PARSER_InputError error = {
            .tag = LIB_RUBY_PARSER_INPUT_ERROR_DECODING_ERROR,
            .as = {
                .decoding_error =
                    LIB_RUBY_PARSER_new_string_from_cstr(
                        StringValueCStr(rb_error_message))}};
        return (LIB_RUBY_PARSER_DecoderResult){
            .tag = LIB_RUBY_PARSER_DECODER_RESULT_ERR,
            .as = {.err = error}};
    }
}
static LIB_RUBY_PARSER_MaybeDecoder LIB_RUBY_PARSER_MaybeDecoder__from_ruby(VALUE rb_maybe_decoder)
{
    if (NIL_P(rb_maybe_decoder))
    {
        return (LIB_RUBY_PARSER_MaybeDecoder){
            .decoder = {
                .f = NULL,
                .state = NULL}};
    }
    else
    {
        return (LIB_RUBY_PARSER_MaybeDecoder){
            .decoder = {
                .f = rb_decode,
                .state = (void *)rb_maybe_decoder}};
    }
}

// __to_ruby
static VALUE LIB_RUBY_PARSER_ParserResult__to_ruby(LIB_RUBY_PARSER_ParserResult result)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cParserResult = rb_const_get(rb_mLibRubyParser, rb_intern("ParserResult"));
    VALUE rb_parser_result = rb_obj_alloc(rb_cParserResult);

    rb_ivar_set(rb_parser_result, rb_intern("@ast"), LIB_RUBY_PARSER_MaybeNode__to_ruby(result.ast));
    rb_ivar_set(rb_parser_result, rb_intern("@tokens"), LIB_RUBY_PARSER_TokenList__to_ruby(&(result.tokens)));
    rb_ivar_set(rb_parser_result, rb_intern("@diagnostics"), LIB_RUBY_PARSER_DiagnosticList__to_ruby(&(result.diagnostics)));
    rb_ivar_set(rb_parser_result, rb_intern("@comments"), LIB_RUBY_PARSER_CommentList__to_ruby(&(result.comments)));
    rb_ivar_set(rb_parser_result, rb_intern("@magic_comments"), LIB_RUBY_PARSER_MagicCommentList__to_ruby(&(result.magic_comments)));
    rb_ivar_set(rb_parser_result, rb_intern("@input"), LIB_RUBY_PARSER_DecodedInput__to_ruby(&(result.input)));

    LIB_RUBY_PARSER_drop_parser_result(&result);

    return rb_parser_result;
}

static VALUE LIB_RUBY_PARSER_Loc__to_ruby(LIB_RUBY_PARSER_Loc *loc)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cLoc = rb_const_get(rb_mLibRubyParser, rb_intern("Loc"));
    VALUE rb_loc = rb_obj_alloc(rb_cLoc);
    rb_ivar_set(rb_loc, rb_intern("@begin"), LONG2FIX(loc->begin));
    rb_ivar_set(rb_loc, rb_intern("@end"), LONG2FIX(loc->end));
    return rb_loc;
}
static VALUE LIB_RUBY_PARSER_MaybeLoc__to_ruby(LIB_RUBY_PARSER_MaybeLoc *maybe_loc)
{
    if (maybe_loc->tag == LIB_RUBY_PARSER_NONE_LOC)
    {
        return Qnil;
    }
    return LIB_RUBY_PARSER_Loc__to_ruby(&(maybe_loc->as.loc));
}

static VALUE LIB_RUBY_PARSER_String__to_ruby(LIB_RUBY_PARSER_String *string)
{
    return rb_utf8_str_new(string->ptr, string->len);
}
static VALUE LIB_RUBY_PARSER_MaybeString__to_ruby(LIB_RUBY_PARSER_MaybeString *maybe_string)
{
    if (maybe_string->string.ptr == NULL)
    {
        return Qnil;
    }
    return LIB_RUBY_PARSER_String__to_ruby(&(maybe_string->string));
}

static VALUE LIB_RUBY_PARSER_MaybeNode__to_ruby(LIB_RUBY_PARSER_Node *node)
{
    if (node == NULL)
    {
        return Qnil;
    }
    else
    {
        return LIB_RUBY_PARSER_Node__to_ruby(node);
    }
}
static VALUE LIB_RUBY_PARSER_NodePtr__to_ruby(LIB_RUBY_PARSER_Node **node)
{
    return LIB_RUBY_PARSER_Node__to_ruby(*node);
}
static VALUE LIB_RUBY_PARSER_MaybeNodePtr__to_ruby(LIB_RUBY_PARSER_Node **maybe_node)
{
    return LIB_RUBY_PARSER_MaybeNode__to_ruby(*maybe_node);
}
static VALUE LIB_RUBY_PARSER_NodeList__to_ruby(LIB_RUBY_PARSER_NodeList *node_list)
{
    VALUE rb_node_list = rb_ary_new_capa(node_list->len);
    for (size_t i = 0; i < node_list->len; i++)
    {
        rb_ary_push(rb_node_list, LIB_RUBY_PARSER_Node__to_ruby(&(node_list->ptr[i])));
    }
    return rb_node_list;
}

static VALUE uint8_t__to_ruby(uint8_t *n)
{
    return INT2FIX(*n);
}

static VALUE LIB_RUBY_PARSER_Bytes__to_ruby(LIB_RUBY_PARSER_Bytes *bytes)
{
    return LIB_RUBY_PARSER_ByteList__to_ruby(&(bytes->raw));
}
static VALUE LIB_RUBY_PARSER_ByteList__to_ruby(LIB_RUBY_PARSER_ByteList *byte_list)
{
    return rb_utf8_str_new(byte_list->ptr, byte_list->len);
}

static VALUE LIB_RUBY_PARSER_Token__to_ruby(LIB_RUBY_PARSER_Token *token)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cToken = rb_const_get(rb_mLibRubyParser, rb_intern("Token"));
    VALUE rb_token = rb_obj_alloc(rb_cToken);
    rb_ivar_set(rb_token, rb_intern("@token_type"), INT2FIX(token->token_type));
    rb_ivar_set(rb_token, rb_intern("@token_value"), LIB_RUBY_PARSER_Bytes__to_ruby(&(token->token_value)));
    char *token_name = LIB_RUBY_PARSER_token_name(token);
    rb_ivar_set(rb_token, rb_intern("@token_name"), rb_str_new(token_name, strlen(token_name)));
    free(token_name);
    rb_ivar_set(rb_token, rb_intern("@loc"), LIB_RUBY_PARSER_Loc__to_ruby(&(token->loc)));
    rb_ivar_set(rb_token, rb_intern("@lex_state_before"), INT2FIX(token->lex_state_before));
    rb_ivar_set(rb_token, rb_intern("@lex_state_after"), INT2FIX(token->lex_state_after));
    return rb_token;
}
static VALUE LIB_RUBY_PARSER_TokenList__to_ruby(LIB_RUBY_PARSER_TokenList *token_list)
{
    VALUE rb_token_list = rb_ary_new_capa(token_list->len);
    for (size_t i = 0; i < token_list->len; i++)
    {
        rb_ary_push(rb_token_list, LIB_RUBY_PARSER_Token__to_ruby(&(token_list->ptr[i])));
    }
    return rb_token_list;
}

static VALUE LIB_RUBY_PARSER_ErrorLevel__to_ruby(LIB_RUBY_PARSER_ErrorLevel *level)
{
    switch (*level)
    {
    case LIB_RUBY_PARSER_ERROR_LEVEL_ERROR:
        return CSTR_TO_SYM("error");
    case LIB_RUBY_PARSER_ERROR_LEVEL_WARNING:
        return CSTR_TO_SYM("warning");
    }
}
static VALUE LIB_RUBY_PARSER_Diagnostic__to_ruby(LIB_RUBY_PARSER_Diagnostic *diagnostic)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cDiagnostic = rb_const_get(rb_mLibRubyParser, rb_intern("Diagnostic"));
    VALUE rb_diagnostic = rb_obj_alloc(rb_cDiagnostic);
    rb_ivar_set(rb_diagnostic, rb_intern("@level"), LIB_RUBY_PARSER_ErrorLevel__to_ruby(&(diagnostic->level)));
    rb_ivar_set(rb_diagnostic, rb_intern("@message"), LIB_RUBY_PARSER_DiagnosticMessage__to_ruby(&(diagnostic->message)));
    rb_ivar_set(rb_diagnostic, rb_intern("@loc"), LIB_RUBY_PARSER_Loc__to_ruby(&(diagnostic->loc)));
    return rb_diagnostic;
}
static VALUE LIB_RUBY_PARSER_DiagnosticList__to_ruby(LIB_RUBY_PARSER_DiagnosticList *diagnostic_list)
{
    VALUE rb_diagnostic_list = rb_ary_new_capa(diagnostic_list->len);
    for (size_t i = 0; i < diagnostic_list->len; i++)
    {
        rb_ary_push(rb_diagnostic_list, LIB_RUBY_PARSER_Diagnostic__to_ruby(&(diagnostic_list->ptr[i])));
    }
    return rb_diagnostic_list;
}

static VALUE LIB_RUBY_PARSER_CommentType__to_ruby(LIB_RUBY_PARSER_CommentType *comment_type)
{
    switch (*comment_type)
    {
    case LIB_RUBY_PARSER_COMMENT_TYPE_INLINE:
        return CSTR_TO_SYM("inline");
    case LIB_RUBY_PARSER_COMMENT_TYPE_DOCUMENT:
        return CSTR_TO_SYM("document");
    case LIB_RUBY_PARSER_COMMENT_TYPE_UNKNOWN:
        return CSTR_TO_SYM("unknown");
    }
}
static VALUE LIB_RUBY_PARSER_Comment__to_ruby(LIB_RUBY_PARSER_Comment *comment)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cComment = rb_const_get(rb_mLibRubyParser, rb_intern("Comment"));
    VALUE rb_comment = rb_obj_alloc(rb_cComment);
    rb_ivar_set(rb_comment, rb_intern("@location"), LIB_RUBY_PARSER_Loc__to_ruby(&(comment->location)));
    rb_ivar_set(rb_comment, rb_intern("@kind"), LIB_RUBY_PARSER_CommentType__to_ruby(&(comment->kind)));
    return rb_comment;
}
static VALUE LIB_RUBY_PARSER_CommentList__to_ruby(LIB_RUBY_PARSER_CommentList *comment_list)
{
    VALUE rb_comment_list = rb_ary_new_capa(comment_list->len);
    for (size_t i = 0; i < comment_list->len; i++)
    {
        rb_ary_push(rb_comment_list, LIB_RUBY_PARSER_Comment__to_ruby(&(comment_list->ptr[i])));
    }
    return rb_comment_list;
}

static VALUE LIB_RUBY_PARSER_MagicCommentKind__to_ruby(LIB_RUBY_PARSER_MagicCommentKind *magic_comment_kind)
{
    switch (*magic_comment_kind)
    {
    case LIB_RUBY_PARSER_MAGIC_COMMENT_KIND_ENCODING:
        return CSTR_TO_SYM("encoding");
    case LIB_RUBY_PARSER_MAGIC_COMMENT_KIND_FROZEN_STRING_LITERAL:
        return CSTR_TO_SYM("frozen_string_literal");
    case LIB_RUBY_PARSER_MAGIC_COMMENT_KIND_WARN_INDENT:
        return CSTR_TO_SYM("warn_indent");
    case LIB_RUBY_PARSER_MAGIC_COMMENT_KIND_SHAREABLE_CONSTANT_VALUE:
        return CSTR_TO_SYM("shareable_constant_value");
    }
}
static VALUE LIB_RUBY_PARSER_MagicComment__to_ruby(LIB_RUBY_PARSER_MagicComment *magic_comment)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cMagicComment = rb_const_get(rb_mLibRubyParser, rb_intern("MagicComment"));
    VALUE rb_magic_comment = rb_obj_alloc(rb_cMagicComment);
    rb_ivar_set(rb_magic_comment, rb_intern("@kind"), LIB_RUBY_PARSER_MagicCommentKind__to_ruby(&(magic_comment->kind)));
    rb_ivar_set(rb_magic_comment, rb_intern("@key_l"), LIB_RUBY_PARSER_Loc__to_ruby(&(magic_comment->key_l)));
    rb_ivar_set(rb_magic_comment, rb_intern("@value_l"), LIB_RUBY_PARSER_Loc__to_ruby(&(magic_comment->value_l)));
    return rb_magic_comment;
}
static VALUE LIB_RUBY_PARSER_MagicCommentList__to_ruby(LIB_RUBY_PARSER_MagicCommentList *magic_comment_list)
{
    VALUE rb_magic_comment_list = rb_ary_new_capa(magic_comment_list->len);
    for (size_t i = 0; i < magic_comment_list->len; i++)
    {
        rb_ary_push(rb_magic_comment_list, LIB_RUBY_PARSER_MagicComment__to_ruby(&(magic_comment_list->ptr[i])));
    }
    return rb_magic_comment_list;
}

static VALUE LIB_RUBY_PARSER_SourceLine__to_ruby(LIB_RUBY_PARSER_SourceLine *source_line)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cSourceLine = rb_const_get(rb_mLibRubyParser, rb_intern("SourceLine"));
    VALUE rb_source_line = rb_obj_alloc(rb_cSourceLine);
    rb_ivar_set(rb_source_line, rb_intern("@start"), LONG2FIX(source_line->start));
    rb_ivar_set(rb_source_line, rb_intern("@end"), LONG2FIX(source_line->end));
    rb_ivar_set(rb_source_line, rb_intern("@ends_with_eof"), source_line->ends_with_eof ? Qtrue : Qfalse);
    return rb_source_line;
}
static VALUE LIB_RUBY_PARSER_SourceLineList__to_ruby(LIB_RUBY_PARSER_SourceLineList *source_line_list)
{
    VALUE rb_source_line_list = rb_ary_new_capa(source_line_list->len);
    for (size_t i = 0; i < source_line_list->len; i++)
    {
        rb_ary_push(rb_source_line_list, LIB_RUBY_PARSER_SourceLine__to_ruby(&(source_line_list->ptr[i])));
    }
    return rb_source_line_list;
}

static VALUE LIB_RUBY_PARSER_DecodedInput__to_ruby(LIB_RUBY_PARSER_DecodedInput *decoded_input)
{
    VALUE rb_mLibRubyParser = rb_const_get(rb_cObject, rb_intern("LibRubyParser"));
    VALUE rb_cDecodedInput = rb_const_get(rb_mLibRubyParser, rb_intern("DecodedInput"));
    VALUE rb_decoded_input = rb_obj_alloc(rb_cDecodedInput);
    rb_ivar_set(rb_decoded_input, rb_intern("@name"), LIB_RUBY_PARSER_String__to_ruby(&(decoded_input->name)));
    rb_ivar_set(rb_decoded_input, rb_intern("@lines"), LIB_RUBY_PARSER_SourceLineList__to_ruby(&(decoded_input->lines)));
    rb_ivar_set(rb_decoded_input, rb_intern("@bytes"), LIB_RUBY_PARSER_ByteList__to_ruby(&(decoded_input->bytes)));
    return rb_decoded_input;
}
