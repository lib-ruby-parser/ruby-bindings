use super::{fns_c, fns_shared};
use lib_ruby_parser_nodes::{
    template::{TemplateFns, F},
    Message, MessageField, Node, NodeField,
};

mod nodes {
    use super::Node;

    pub(crate) fn comment(node: &Node) -> String {
        node.render_comment("//", 0)
    }
}

mod node_fields {
    use super::NodeField;

    pub(crate) fn comment(node_field: &NodeField) -> String {
        node_field.render_comment("//", 4)
    }
}

mod messages {
    use super::Message;

    pub(crate) fn comment(message: &Message) -> String {
        message.render_comment("//", 0)
    }
}

mod message_fields {
    use super::MessageField;

    pub(crate) fn comment(message_field: &MessageField) -> String {
        message_field.render_comment("//", 4)
    }
}

pub(crate) fn build() -> TemplateFns {
    let mut fns = fns_shared::build() + fns_c::build();

    fns.register::<Node, F::Helper>("node-comment", nodes::comment);
    fns.register::<NodeField, F::Helper>("node-field-comment", node_fields::comment);
    fns.register::<Message, F::Helper>("message-comment", messages::comment);
    fns.register::<MessageField, F::Helper>("message-field-comment", message_fields::comment);

    fns
}

macro_rules! default_fns {
    () => {{
        fn generated_by(_: &lib_ruby_parser_nodes::template::GlobalContext) -> String {
            file!().to_string()
        }
        fn generated_by_for_node(_: &lib_ruby_parser_nodes::Node) -> String {
            file!().to_string()
        }
        let mut fns = $crate::codegen::fns::build();
        fns.register::<GlobalContext, F::Helper>("generated-by", generated_by);
        fns.register::<lib_ruby_parser_nodes::Node, F::Helper>(
            "generated-by",
            generated_by_for_node,
        );
        fns
    }};
}
pub(crate) use default_fns;
