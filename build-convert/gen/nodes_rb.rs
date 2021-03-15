pub(crate) struct NodesRb<'a> {
    nodes: &'a [lib_ruby_parser_nodes::Node],
}

impl<'a> NodesRb<'a> {
    pub(crate) fn new(nodes: &'a [lib_ruby_parser_nodes::Node]) -> Self {
        Self { nodes }
    }

    pub(crate) fn write(&self) {
        std::fs::write("../lib/lib-ruby-parser/nodes.rb", self.contents()).unwrap()
    }

    fn contents(&self) -> String {
        format!(
            "module LibRubyParser
  class Node
  end

  {node_classes}
end
",
            node_classes = self.node_classes().join("\n\n  ")
        )
    }

    fn node_classes(&self) -> Vec<String> {
        self.nodes
            .iter()
            .map(|node| Node::new(node).declaration())
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

    fn declaration(&self) -> String {
        format!(
            "class {class_name} < Node
    attr_reader {attr_readers}
  end",
            class_name = self.node.struct_name,
            attr_readers = self.attr_readers().join(", ")
        )
    }

    fn attr_readers(&self) -> Vec<String> {
        self.node
            .fields
            .iter()
            .map(|f| format!(":{}", f.field_name))
            .collect()
    }
}
