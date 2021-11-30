# LibRubyParser

Ruby bindings for [`lib-ruby-parser`](https://github.com/lib-ruby-parser/lib-ruby-parser)

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'lib-ruby-parser'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install lib-ruby-parser

## Usage

Basic usage:

```ruby
require 'lib-ruby-parser'

input = <<~RUBY
def foo(a, b, c)
  a + b + c
end
RUBY

result = LibRubyParser.parse(input, {})
pp result
```

Full documentation can be found [here](https://lib-ruby-parser.github.io/ruby-bindings/)

## Development

This repo is **mostly** based on [`c-bindings`](https://github.com/lib-ruby-parser/c-bindings) and [`lib-ruby-parser-nodes Rust crate`](https://github.com/lib-ruby-parser/nodes)

1. `c-bindings` directory contains static library and header file from the latest [c-bindings release](https://github.com/lib-ruby-parser/c-bindings/releases). Both header and static lib are under gitignore.
2. `codegen` directory is a Rust micro-library that generates:
    + `nodes.h` - header file with C -> Ruby conversion functions for all `Node` types
    + `messages.h` - header file with C -> Ruby conversion functions for all `DiagnosticMessage` types
    + `lib/lib-ruby-parser/nodes.rb` - classes and documentation for all `Node` types
    + `lib/lib-ruby-parser/messages.rb` - classes and documentation for all `DiagnosticMessage` types
3. `lib` directory contains classes and documentation for all classes except dynamic nodes and diagnostic messages
4. `main.c` is the main entrypoint to C world. It defines a single `LibRubyParser.parse` function that converts given Ruby objects, converts them to C equivalent, calls `LIB_RUBY_PARSER_parse` from `c-bindings` and converts returned C objects back to Ruby objects. 90% function names in `main.c` end with either `__from_ruby` (to convert object from Ruby to C) or `__to_ruby` (to convert C -> Ruby).
5. `scripts` directory:
    1. `scripts/targets` - directory with target- (and in our case OS-) specific configurations
    2. `scripts/compile.rb` - prints code to compile `main.c` to `main.o`
    3. `scripts/link.rb` - prints code to link `main.o` to `lib/lib-ruby-parser/lib_ruby_parser_native.$(DYLIB_EXT)`
    4. `scripts/setup.mk` - basic setup, prints debug information, auto-included by root Makefile
6. `test` directory contains a single minitest test that performs a smoke test

To run it locally:

1. make sure to have Ruby and Rust
2. `git clone` the repo
3. run `bundle install`
4. run `make test`

## Safety

`c-bindings` is tested with Address Sanitizer (ASAN) on every commit, so it's clean from memory leaks.

We do run ASAN on CI on every commit for this repo too, but enabling it is a bit tricky. Ruby executable is not linked with `libasan.so`, and so if `main.c` is compiled with `-fsanitize=address` loading `lib_ruby_parser.dylib` gives an error at runtime, `malloc` is supposed to "track itself" using `libasan.so` functionality, but it's not available. `LD_PRELOAD` (on Linux) and `DYLD_INSERT_LIBRARIES` (on MacOS) can do the trick.

1. On Linux:
    + Pass `CFLAGS="-fsanitize=address"` to `make test` to get `lib/lib-ruby-parser/lib_ruby_parser_native.so` compiled with ASAN
    + Get path to `libasan.so` by running `gcc -print-file-name=libasan.so`
    + Pass it to `make test` with `LD_PRELOAD=$(gcc -print-file-name=libasan.so) make test`
2. On MacOS:
    + Make sure to have `clang` installed with Homebrew, default `clang` that ships with MacOS doesn't have it.
    + Pass `CC=clang CFLAGS="-fsanitize=address"` to `make test` to get `lib/lib-ruby-parser/lib_ruby_parser_native.so` compiled with ASAN
    + Get path to `libclang_rt.asan_osx_dynamic.dylib` by running `clang --print-file-name=libclang_rt.asan_osx_dynamic.dylib`
    + Pass it to `make test` with `DYLD_INSERT_LIBRARIES=$(clang --print-file-name=libclang_rt.asan_osx_dynamic.dylib) make test`

CI does the same thing on every commit.

Additionally, we run Leak Sanitizer (LSAN) that is a part of ASAN, it can be enabled by setting `ASAN_OPTIONS=detect_leaks=1` env var.

Unfortunately, Ruby does something that makes LSAN complain no matter what:

```
ASAN_OPTIONS=detect_leaks=1 \
    DYLD_INSERT_LIBRARIES=$(clang --print-file-name=libclang_rt.asan_osx_dynamic.dylib) \
    ruby -e 'p 1'

# prints a TON of leaks leaks
Direct leak of 48 byte(s) in 1 object(s) allocated from:
    #0 0x108e0fb25 in wrap_calloc+0xa5 (libclang_rt.asan_osx_dynamic.dylib:x86_64+0x44b25)
    #1 0x1098cfab4 in ruby_xcalloc_body+0x214 (libruby.3.0.dylib:x86_64+0xd0ab4)
    #2 0x109a6dfb2 in rb_method_entry_make+0x3a2 (libruby.3.0.dylib:x86_64+0x26efb2)
    #3 0x109a6cfd8 in rb_add_method+0x38 (libruby.3.0.dylib:x86_64+0x26dfd8)
    #4 0x109a6cf3e in rb_add_method_cfunc+0x3e (libruby.3.0.dylib:x86_64+0x26df3e)
    #5 0x1098f2efc in Init_IO+0x134c (libruby.3.0.dylib:x86_64+0xf3efc)
    #6 0x1098ea7c4 in rb_call_inits+0x94 (libruby.3.0.dylib:x86_64+0xeb7c4)
    #7 0x1098b61e7 in ruby_setup+0x137 (libruby.3.0.dylib:x86_64+0xb71e7)
    #8 0x1098b6268 in ruby_init+0x8 (libruby.3.0.dylib:x86_64+0xb7268)
    #9 0x108db7ef8 in main+0x48 (ruby:x86_64+0x100003ef8)
    #10 0x7fff203baf3c in start+0x0 (libdyld.dylib:x86_64+0x15f3c)
```

It is possible to suppress specified leaks, we have `LSan.supp` file for that:

```
LSAN_OPTIONS=suppressions=LSan.supp \
    ASAN_OPTIONS=detect_leaks=1 \
    DYLD_INSERT_LIBRARIES=$(clang --print-file-name=libclang_rt.asan_osx_dynamic.dylib) \
    ruby -e 'p 1'
# prints nothing
```

We use the same file on CI, no functions from `lib-ruby-parser` are allowed to produce leaks.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/lib-ruby-parser/ruby-bindings.
