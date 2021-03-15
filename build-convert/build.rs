extern crate lib_ruby_parser_nodes;
mod gen;

fn main() {
    let nodes = lib_ruby_parser_nodes::nodes();

    gen::ConvertH::new(&nodes).write();
    gen::ConvertC::new(&nodes).write();

    gen::NodesRb::new(&nodes).write();
}
