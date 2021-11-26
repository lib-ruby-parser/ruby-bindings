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

# manual codegen task
do-codegen:
	$(DO_CODEGEN)
