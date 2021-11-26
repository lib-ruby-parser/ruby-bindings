extern crate cbindgen;

#[derive(Debug, Default)]
struct TokenId {
    comment: String,
    name: String,
    value: String,
}

impl TokenId {
    fn declaration(&self) -> String {
        format!(
            "{comment}
#define LIB_RUBY_PARSER_TOKEN_{name} {value}",
            comment = self.comment,
            name = self.name,
            value = self.value
        )
    }
}

fn bindgen() -> String {
    const TMP_BINDINGS: &str = "codegen/examples/target/tmp_bindings.h";

    cbindgen::Builder::new()
        .with_crate("ruby-parser-c")
        .with_parse_deps(true)
        .with_parse_extra_bindings(&["lib-ruby-parser"])
        .with_no_includes()
        .include_item("Lexer")
        .generate()
        .expect("Unable to generate bindings")
        .write_to_file(TMP_BINDINGS);

    let contents = std::fs::read_to_string(TMP_BINDINGS).unwrap();

    std::fs::remove_file(TMP_BINDINGS).unwrap();

    contents
}

fn collect_token_ids() -> Vec<TokenId> {
    let bindings = bindgen();

    let mut token_ids = vec![];
    let mut token_id = TokenId::default();

    for line in bindings.lines() {
        if line.starts_with("/// Token") {
            // token comment line
            token_id.comment = line.to_string();
        } else if line.starts_with("static const int32_t Lexer_") {
            let line = line
                .replace("static const int32_t Lexer_", "")
                .replace(";", "");

            let parts = line.split(" = ").collect::<Vec<_>>();
            assert_eq!(parts.len(), 2);
            token_id.name = parts[0].to_string();
            token_id.value = parts[1].to_string();

            token_ids.push(std::mem::take(&mut token_id));
        }
    }

    token_ids
}

pub fn main() {
    let token_ids = collect_token_ids();

    let token_ids_h = format!(
        "#ifndef LIB_RUBY_PARSER_TOKEN_IDS_H
#define LIB_RUBY_PARSER_TOKEN_IDS_H

{declarations}

#endif // LIB_RUBY_PARSER_TOKEN_IDS_H
",
        declarations = token_ids
            .iter()
            .map(TokenId::declaration)
            .collect::<Vec<_>>()
            .join("\n\n")
    );

    std::fs::write("token_ids.h", token_ids_h).unwrap();
}
