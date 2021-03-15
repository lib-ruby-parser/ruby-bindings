pub(crate) struct ConvertC<'a> {
    nodes: &'a [lib_ruby_parser_nodes::Node],
}

impl<'a> ConvertC<'a> {
    pub(crate) fn new(nodes: &'a [lib_ruby_parser_nodes::Node]) -> Self {
        Self { nodes }
    }

    pub(crate) fn write(&self) {
        std::fs::write("../src/convert.c", self.contents()).unwrap()
    }

    fn contents(&self) -> String {
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
            implementations = self.implementations().join("\n\n"),
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
            "VALUE convert_{node_name}(struct {node_name} *node) {{
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
            "case NODE_{upper}:
            return convert_{node_name}(node->node->_{lower});",
            upper = self.node.filename.to_uppercase(),
            node_name = self.node.struct_name,
            lower = self.node.filename.to_lowercase()
        )
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
            "rb_ivar_set(result, rb_intern(\"@{field_name}\"), {convert_fn}(node->{field_name}));",
            convert_fn = self.convert_fn(),
            field_name = self.field_name()
        )
    }

    fn convert_fn(&self) -> &str {
        use lib_ruby_parser_nodes::FieldType;

        match self.field.field_type {
            FieldType::Node | FieldType::MaybeNode | FieldType::RegexOptions => "convert_Node",

            FieldType::Nodes => "convert_NodeList",

            FieldType::Loc | FieldType::MaybeLoc => "convert_Loc",

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
