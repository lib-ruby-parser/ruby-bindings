include scripts/setup.mk
include c-bindings/build.mk

generate-ruby-bindings:
	cd build-convert && cargo build

# include src/build.mk

clean:
	rm -rf $(TARGET_DIR)
	mkdir -p $(TARGET_DIR)
	rm -f $(DYLIB)

test: $(DYLIB)
	bundle exec rake spec
