use super::{fns_c, fns_shared};
use lib_ruby_parser_nodes::{
    template::{TemplateFns, F},
    Message, MessageField, Node, NodeField,
};

fn convert_non_code_line_to_yard(line: &str) -> String {
    let mut output = String::new();
    let mut in_code_block = false;
    let mut idx: usize = 0;
    let chars = line.chars().collect::<Vec<char>>();

    let char_at = |idx: usize| chars.get(idx).map(|c| *c);

    while idx < chars.len() {
        let c = chars[idx];

        if c == ' ' && char_at(idx + 1) == Some('$') && char_at(idx + 2) == Some('`') {
            // a very special $` variable
            idx += 3;
            output.push_str("&`");
            continue;
        }

        if c == '`' {
            if char_at(idx + 1) == Some('`') {
                // double back-tick, used to escape inner backtick
                in_code_block = !in_code_block;
                idx += 2;
                output.push('+');
                continue;
            }
            // regular single backtick
            in_code_block = !in_code_block;
            idx += 1;
            output.push('+');
            continue;
        } else {
            // regular char
            idx += 1;
            output.push(c);
            continue;
        }
    }
    assert!(!in_code_block, "not balanced - {:?}", line);
    output
}

fn convert_comment_to_yard(comment: &[&str], offset: usize) -> String {
    let prefix = " ".repeat(offset);
    let empty_line = format!("{prefix}#\n", prefix = prefix);
    let mut output = String::new();
    let mut in_code_block = false;
    for line in comment {
        if *line == "```text" {
            in_code_block = true;
            if !output.ends_with(&empty_line) {
                output.push_str(&empty_line);
            }
            output.push_str(&format!("{prefix}# @example\n", prefix = prefix));
            continue;
        }
        if *line == "```" {
            assert!(in_code_block);
            output.push_str(&empty_line);
            in_code_block = false;
            continue;
        }
        if in_code_block {
            output.push_str(&format!(
                "{prefix}#  {line}\n",
                prefix = prefix,
                line = line
            ));
            continue;
        }
        let line = convert_non_code_line_to_yard(*line);
        output.push_str(&format!("{prefix}# {line}\n", prefix = prefix, line = line))
    }
    assert!(!in_code_block);

    let output = output
        .lines()
        .map(|line| {
            let line = if line.ends_with(" ") {
                line.strip_suffix(" ").unwrap().to_string()
            } else {
                line.to_string()
            };
            format!("{}\n", line)
        })
        .collect::<Vec<_>>();

    let mut stripped = vec![];
    let mut prev_line_was_empty = false;
    for line in output.into_iter() {
        if line == empty_line {
            if prev_line_was_empty {
                continue;
            } else {
                stripped.push(line)
            }
            prev_line_was_empty = true;
        } else {
            stripped.push(line);
            prev_line_was_empty = false;
        }
    }

    stripped.join("")
}

mod nodes {
    use super::{convert_comment_to_yard, Node};

    pub(crate) fn comment(node: &Node) -> String {
        convert_comment_to_yard(node.comment, 4)
    }
}

mod node_fields {
    use super::{convert_comment_to_yard, NodeField};

    pub(crate) fn comment(node_field: &NodeField) -> String {
        let comment = convert_comment_to_yard(node_field.comment, 6);

        use lib_ruby_parser_nodes::NodeFieldType::*;
        let rb_return_type = match node_field.field_type {
            Node => "Node",
            Nodes => "::Array<Node>",
            MaybeNode { .. } => "Node, nil",
            Loc => "Loc",
            MaybeLoc => "Loc, nil",
            Str { .. } => "String",
            MaybeStr { .. } => "String, nil",
            StringValue => "String",
            U8 => "Integer",
        };

        let return_comment = format!(
            "      #
      # @return [{rb_return_type}]
",
            rb_return_type = rb_return_type
        );

        format!("{}{}", comment, return_comment)
    }
}

mod messages {
    use super::{convert_comment_to_yard, Message};

    pub(crate) fn comment(message: &Message) -> String {
        convert_comment_to_yard(message.comment, 4)
    }
}

mod message_fields {
    use super::{convert_comment_to_yard, MessageField};

    pub(crate) fn comment(message_field: &MessageField) -> String {
        let comment = convert_comment_to_yard(message_field.comment, 6);

        use lib_ruby_parser_nodes::MessageFieldType::*;
        let rb_return_type = match message_field.field_type {
            Str => "String",
            Byte => "Integer",
        };

        let return_comment = format!(
            "      #
      # @return [{rb_return_type}]
",
            rb_return_type = rb_return_type
        );

        format!("{}{}", comment, return_comment)
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
