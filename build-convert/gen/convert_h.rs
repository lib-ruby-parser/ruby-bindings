pub(crate) struct ConvertH<'a> {
    nodes: &'a [lib_ruby_parser_nodes::Node],
}

impl<'a> ConvertH<'a> {
    pub(crate) fn new(nodes: &'a [lib_ruby_parser_nodes::Node]) -> Self {
        Self { nodes }
    }

    pub(crate) fn write(&self) {
        std::fs::write("../src/convert.h", self.contents()).unwrap()
    }

    fn contents(&self) -> String {
        format!(
            "#ifndef LIB_RUBY_PARSER_CONVERT_H
#define LIB_RUBY_PARSER_CONVERT_H

#include <ruby.h>
#include \"../c-bindings/lib-ruby-parser.h\"

VALUE convert_NodePtr(LIB_RUBY_PARSER_NodePtr);
VALUE convert_MaybeNodePtr(LIB_RUBY_PARSER_MaybeNodePtr);
VALUE convert_Loc(LIB_RUBY_PARSER_Loc);
VALUE convert_MaybeLoc(LIB_RUBY_PARSER_MaybeLoc);
VALUE convert_NodeList(LIB_RUBY_PARSER_NodeList);
VALUE convert_StringPtr(LIB_RUBY_PARSER_StringPtr);
VALUE convert_MaybeStringPtr(LIB_RUBY_PARSER_MaybeStringPtr);
VALUE convert_StringValue(LIB_RUBY_PARSER_StringValue);
VALUE convert_uint32_t(uint32_t);

{implementations}

VALUE convert_NodePtr(LIB_RUBY_PARSER_NodePtr node)
{{
    if (node == NULL)
    {{
        return Qnil;
    }}
    switch(node->tag)
    {{
        {switch_branches}
    }}
}}

#endif // LIB_RUBY_PARSER_CONVERT_H
",
            implementations = self.implementations().join("\n"),
            switch_branches = self.switch_branches().join("\n        "),
        )
    }

    fn implementations(&self) -> Vec<String> {
        self.nodes
            .iter()
            .map(|node| Node::new(node).convert_fn_implementation())
            .collect()
    }

    fn switch_branches(&self) -> Vec<String> {
        self.nodes
            .iter()
            .map(|node| Node::new(node).c_switch_branch())
            .collect()
    }
}

struct Node<'a> {
    node: &'a lib_ruby_parser_nodes::Node,
}

impl<'a> Node<'a> {
    fn new(node: &'a lib_ruby_parser_nodes::Node) -> Self {
        Self { node }
    }

    fn convert_fn_implementation(&self) -> String {
        format!(
            "VALUE convert_{node_name}(LIB_RUBY_PARSER_{node_name} node) {{
    VALUE lib_ruby_parser_mod = rb_const_get(rb_cObject, rb_intern(\"LibRubyParser\"));
    VALUE node_klass = rb_const_get(lib_ruby_parser_mod, rb_intern(\"{node_name}\"));
    VALUE result = rb_obj_alloc(node_klass);
    {convert_fields}
    return result;
}}",
            node_name = self.node.struct_name,
            convert_fields = self.convert_fields().join("\n    ")
        )
    }

    fn convert_fields(&self) -> Vec<String> {
        self.node
            .fields
            .iter()
            .map(|f| Field::new(f).code())
            .collect()
    }

    fn c_switch_branch(&self) -> String {
        format!(
            "case {enum_field_name}:
            return convert_{node_name}(node->{union_field_name});",
            enum_field_name = self.enum_field_name(),
            node_name = self.node.struct_name,
            union_field_name = self.union_field_name()
        )
    }

    const RESERVED_WORDS: &'static [&'static str] = &[
        "break", "case", "class", "const", "false", "float", "for", "if", "int", "return", "true",
        "while",
    ];

    fn union_field_name(&self) -> String {
        let result = camel_case_to_underscored(&self.node.struct_name).to_lowercase();
        if result == "self_" {
            return String::from("self");
        }
        for reserved_word in Self::RESERVED_WORDS {
            if &result == reserved_word {
                return format!("{}_", result);
            }
        }
        result
    }

    fn enum_field_name(&self) -> String {
        let mut suffix = camel_case_to_underscored(&self.node.struct_name).to_uppercase();
        if suffix == "SELF_" {
            suffix = String::from("SELF");
        }
        format!("NODE_{}", suffix)
    }
}

struct Field<'a> {
    field: &'a lib_ruby_parser_nodes::Field,
}

impl<'a> Field<'a> {
    pub fn new(field: &'a lib_ruby_parser_nodes::Field) -> Self {
        Self { field }
    }

    pub fn code(&self) -> String {
        format!(
            "rb_ivar_set(result, rb_intern(\"@{field_name}\"), {convert_fn}(node.{field_name}));",
            convert_fn = self.convert_fn(),
            field_name = self.field_name()
        )
    }

    fn convert_fn(&self) -> &str {
        use lib_ruby_parser_nodes::FieldType;

        match self.field.field_type {
            FieldType::Node => "convert_NodePtr",
            FieldType::MaybeNode | FieldType::RegexOptions => "convert_MaybeNodePtr",

            FieldType::Nodes => "convert_NodeList",

            FieldType::Loc => "convert_Loc",
            FieldType::MaybeLoc => "convert_MaybeLoc",

            FieldType::Str | FieldType::RawString => "convert_StringPtr",

            FieldType::MaybeStr | FieldType::Chars => "convert_MaybeStringPtr",

            FieldType::StringValue => "convert_StringValue",

            FieldType::U8 | FieldType::Usize => "convert_uint32_t",
        }
    }

    fn field_name(&self) -> String {
        match &self.field.field_name[..] {
            "default" => "default_",
            "operator" => "operator_",
            other => other,
        }
        .to_string()
    }
}

pub(crate) fn camel_case_to_underscored(s: &str) -> String {
    let mut words = vec![];
    let mut word = String::from("");

    for c in s.chars() {
        if c.is_uppercase() {
            // flush
            words.push(word);
            word = String::from("");
        }
        word.push(c);
    }

    words.push(word);

    words
        .into_iter()
        .filter(|w| !w.is_empty())
        .collect::<Vec<_>>()
        .join("_")
}
