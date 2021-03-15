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
#include \"../lib-ruby-parser.h\"

{declarations}

VALUE convert_Node(struct Node* node);

void InitNodeClasses(VALUE lib_ruby_parser_mod);

#endif // LIB_RUBY_PARSER_CONVERT_H
",
            declarations = self.declarations().join("\n"),
        )
    }

    fn declarations(&self) -> Vec<String> {
        self.nodes
            .iter()
            .map(|node| {
                format!(
                    "VALUE convert_{node_name}(struct {node_name} *node);",
                    node_name = node.struct_name
                )
            })
            .collect()
    }
}
