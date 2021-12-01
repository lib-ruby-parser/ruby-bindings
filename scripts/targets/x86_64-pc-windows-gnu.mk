$(info Compiling x86_64-pc-windows-gnu target)

O = o
A = a
DYLIB = so

BENCHMARK_RUNNER_ASSET_NAME = rust-parser-x86_64-pc-windows-gnu.exe

STATIC_LIBRUBY = libruby-static.a

ifeq ($(RUBY_VERSION),3.0)
STATIC_LIBRUBY_URL = https://github.com/lib-ruby-parser/ruby-static-lib-mingw32/releases/download/v3_0_3/libx64-msvcrt-ruby300-static.a
endif

# TODO: add 2.7 and 2.6 support

ifndef RUBY_VERSION
$(error Only 3.0 branch is currently supported)
endif

$(STATIC_LIBRUBY):
	$(call download_file, $(STATIC_LIBRUBY_URL), $@)
