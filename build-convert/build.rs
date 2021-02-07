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

struct RubyNode {
    node: Node,
}

impl RubyNode {
    pub fn new(node: Node) -> Self {
        Self { node }
    }

    pub fn c_convert_declaration(&self) -> String {
        format!(
            "VALUE convert_{node_name}(struct {node_name} *node);",
            node_name = self.node.struct_name
        )
    }

    pub fn c_convert_implementation(&self) -> String {
        format!(
            "VALUE convert_{node_name}(struct {node_name} *node) {{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern(\"LibRubyParser\"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern(\"{node_name}\"));
    VALUE result = rb_obj_alloc(node_klass);
    {c_convert_fields}
    return result;
}}",
            node_name = self.node.struct_name,
            c_convert_fields = self.c_convert_fields()
        )
    }

    fn c_convert_fields(&self) -> String {
        self.node
            .fields
            .iter()
            .map(|f| FieldConverter::new(f.clone()).code())
            .collect::<Vec<_>>()
            .join("\n    ")
    }

    pub fn c_switch_branch(&self) -> String {
        format!(
            "case NODE_{upper}:
            return convert_{node_name}(node->inner->_{lower});",
            upper = self.node.filename.to_uppercase(),
            node_name = self.node.struct_name,
            lower = self.node.filename.to_lowercase()
        )
    }

    pub fn ruby_declaration(&self) -> String {
        format!(
            "  class {class_name} < Node
    attr_reader {attr_readers}
  end",
            class_name = self.node.struct_name,
            attr_readers = self.attr_readers().join(", ")
        )
    }

    pub fn attr_readers(&self) -> Vec<String> {
        self.node
            .fields
            .iter()
            .map(|f| format!(":{}", f.field_name))
            .collect()
    }
}

fn convert_h(ruby_nodes: &[RubyNode]) -> String {
    let declarations = ruby_nodes
        .iter()
        .map(RubyNode::c_convert_declaration)
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

fn convert_c(ruby_nodes: &[RubyNode]) -> String {
    let implementations = ruby_nodes
        .iter()
        .map(RubyNode::c_convert_implementation)
        .collect::<Vec<_>>()
        .join("\n");

    let switch_branches = ruby_nodes
        .iter()
        .map(RubyNode::c_switch_branch)
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
}}
",
        implementations = implementations,
        switch_branches = switch_branches,
    )
}

fn nodes_rb(ruby_nodes: &[RubyNode]) -> String {
    let node_classes = ruby_nodes
        .iter()
        .map(RubyNode::ruby_declaration)
        .collect::<Vec<_>>()
        .join("\n\n");

    format!(
        "module LibRubyParser
  class Node
  end

{node_classes}
end
",
        node_classes = node_classes
    )
}

fn write(path: &str, f: &dyn Fn(&[RubyNode]) -> String) {
    let nodes = lib_ruby_parser_nodes::nodes().unwrap();
    let convertes = nodes.into_iter().map(RubyNode::new).collect::<Vec<_>>();

    std::fs::write(&relative_path(path), &f(&convertes)).unwrap();
}

fn main() {
    write("../src/convert.h", &convert_h);
    write("../src/convert.c", &convert_c);
    write("../lib/lib-ruby-parser/nodes.rb", &nodes_rb);
}
