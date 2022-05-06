build-package:
	rm -rf build
	mkdir -p build

	cp package/$(TARGET)-gemspec.rb build/lib-ruby-parser.gemspec
	cp -r lib build/lib
	cp README.md build/README.md

	cd build && gem build --output lib-ruby-parser.gem

.PHONY: build-package
