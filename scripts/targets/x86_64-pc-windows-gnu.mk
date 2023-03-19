$(info Compiling x86_64-pc-windows-gnu target)

O = o
A = a
DYLIB = so
EXE = .exe

BENCHMARK_RUNNER_ASSET_NAME = rust-parser-x86_64-pc-windows-gnu.exe
CODEGEN_ASSET_NAME = codegen-x86_64-pc-windows-msvc.exe

LIB_RUBY_PARSER_DYLIB = lib/lib-ruby-parser/native/x86_64-pc-windows-gnu/$(RUBY_VERSION)/lib_ruby_parser.so
