use lib_ruby_parser_nodes::template::*;

const TEMPLATE: &str = "# This file is autogenerated by {{ helper generated-by }}

# Root module
module LibRubyParser
  # Module with all known DiagnosticMessage sub-types
  module Messages
{{ each message }}<dnl>
{{ helper message-comment }}<dnl>
    class {{ helper message-camelcase-name }} < DiagnosticMessage
{{ each message-field }}<dnl>
{{ helper message-field-comment }}<dnl>
      attr_reader :{{ helper message-field-name }}

{{ end }}<dnl>
    end

{{ end }}<dnl>
  end
end
";

pub(crate) fn codegen() {
    let template = TemplateRoot::new(TEMPLATE).unwrap();
    let fns = crate::codegen::fns::default_fns!();

    let contents = template.render(ALL_DATA, &fns);
    std::fs::write("../lib/lib-ruby-parser/messages.rb", contents).unwrap();
}
