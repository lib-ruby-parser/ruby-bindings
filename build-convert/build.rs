extern crate lib_ruby_parser_nodes;

use lib_ruby_parser_nodes::{Field, FieldType, Node};
use std::path::Path;

fn relative_path(path: &str) -> String {
    Path::new(file!())
        .parent()
        .unwrap()
        .join(path)
        .to_str()
        .unwrap()
        .to_owned()
}

struct Converter {
    node: Node,
}

impl Converter {
    pub fn new(node: Node) -> Self {
        Self { node }
    }

    pub fn declaration(&self) -> String {
        format!(
            "VALUE convert_{node_name}(struct {node_name} *node);",
            node_name = self.node.struct_name
        )
    }

    pub fn implementation(&self) -> String {
        format!(
            "VALUE convert_{node_name}(struct {node_name} *node) {{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern(\"LibRubyParser\"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern(\"{node_name}\"));
    VALUE result = rb_obj_alloc(node_klass);
    {convert_fields}
    return result;
}}",
            node_name = self.node.struct_name,
            convert_fields = self.convert_fields()
        )
    }

    fn convert_fields(&self) -> String {
        self.node
            .fields
            .iter()
            .map(|f| FieldConverter::new(f.clone()).code())
            .collect::<Vec<_>>()
            .join("\n    ")
    }

    pub fn ruby_class_declaration(&self) -> String {
        format!(
            "rb_define_class_under(lib_ruby_parser_mod, \"{class_name}\", rb_Node);",
            class_name = self.node.struct_name
        )
    }

    pub fn switch_branch(&self) -> String {
        format!(
            "case NODE_{upper}:
            return convert_{node_name}(node->inner->_{lower});",
            upper = self.node.filename.to_uppercase(),
            node_name = self.node.struct_name,
            lower = self.node.filename.to_lowercase()
        )
    }
}

fn convert_h(converters: &[Converter]) -> String {
    let declarations = converters
        .iter()
        .map(Converter::declaration)
        .collect::<Vec<_>>()
        .join("\n");

    format!(
        "#ifndef LIB_RUBY_PARSER_CONVERT_H
#define LIB_RUBY_PARSER_CONVERT_H

#include <ruby.h>
#include \"../lib-ruby-parser.h\"

{declarations}

VALUE convert_Node(struct Node* node);

void InitNodeClasses(VALUE lib_ruby_parser_mod);

#endif // LIB_RUBY_PARSER_CONVERT_H
",
        declarations = declarations,
    )
}

struct FieldConverter {
    field: Field,
}

impl FieldConverter {
    pub fn new(field: Field) -> Self {
        Self { field }
    }

    pub fn code(&self) -> String {
        format!(
            "rb_ivar_set(result, rb_intern(\"@{field_name}\"), {convert_fn}(node->{field_name}));",
            convert_fn = self.convert_fn(),
            field_name = self.field_name()
        )
    }

    fn convert_fn(&self) -> &str {
        match self.field.field_type {
            FieldType::Node | FieldType::MaybeNode | FieldType::RegexOptions => "convert_Node",

            FieldType::Nodes => "convert_NodeList",

            FieldType::Range | FieldType::MaybeRange => "convert_Range",

            FieldType::Str
            | FieldType::MaybeStr
            | FieldType::Chars
            | FieldType::StringValue
            | FieldType::RawString => "convert_String",

            FieldType::U8 | FieldType::Usize => "convert_uint32_t",
        }
    }

    fn field_name(&self) -> String {
        match &self.field.field_name[..] {
            "default" => "default_",
            other => other,
        }
        .to_string()
    }
}

fn convert_c(converters: &[Converter]) -> String {
    let implementations = converters
        .iter()
        .map(Converter::implementation)
        .collect::<Vec<_>>()
        .join("\n");

    let init_classes = converters
        .iter()
        .map(Converter::ruby_class_declaration)
        .collect::<Vec<_>>()
        .join("\n    ");

    let switch_branches = converters
        .iter()
        .map(Converter::switch_branch)
        .collect::<Vec<_>>()
        .join("\n        ");

    format!(
        "#include \"convert.h\"
#include \"convert_known.h\"

{implementations}

VALUE convert_Node(struct Node* node)
{{
    if (node == NULL)
    {{
        return Qnil;
    }}
    switch(node->node_type)
    {{
        {switch_branches}
    }}
}}

void InitNodeClasses(VALUE lib_ruby_parser_mod)
{{
    VALUE rb_Node = rb_define_class_under(lib_ruby_parser_mod, \"Node\", rb_cObject);
    {init_classes}
}}
",
        implementations = implementations,
        switch_branches = switch_branches,
        init_classes = init_classes,
    )
}

fn main() {
    let nodes = lib_ruby_parser_nodes::nodes().unwrap();
    let convertes = nodes.into_iter().map(Converter::new).collect::<Vec<_>>();

    std::fs::write(&relative_path("../src/convert.h"), &convert_h(&convertes)).unwrap();
    std::fs::write(&relative_path("../src/convert.c"), &convert_c(&convertes)).unwrap();
}
