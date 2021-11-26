CODEGEN_DEPS = $(wildcard codegen/codegen/*.rs)
CODEGEN_DEPS += codegen/Cargo.toml
CODEGEN_DEPS += codegen/build.rs

DO_CODEGEN = cd codegen && cargo build

# Codegen deps
messages.h: $(CODEGEN_DEPS)
	$(DO_CODEGEN)
CLEAN += messages.h

nodes.h: $(CODEGEN_DEPS)
	$(DO_CODEGEN)
CLEAN += nodes.h

# token_id.{h,c} codegen
DO_CODEGEN_TOKEN_IDS = cargo run --example build_token_ids --manifest-path codegen/Cargo.toml

token_ids.h: codegen/examples/build_token_ids.rs
	$(DO_CODEGEN_TOKEN_IDS)
CLEAN += token_ids.h
update-depend: token_ids.h

# manual codegen task
do-codegen:
	$(DO_CODEGEN)
