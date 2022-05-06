CODEGEN_EXE = codegen/codegen$(EXE)
$(CODEGEN_EXE):
	$(call download_file, https://github.com/lib-ruby-parser/lib-ruby-parser/releases/download/v4.0.2+ruby-3.1.1/codegen-$(TARGET)$(EXE), $@)
	chmod +x $(CODEGEN_EXE)
# CLEAN += $(CODEGEN_EXE)

# Codegen deps
messages.h: codegen/messages.h.liquid $(CODEGEN_EXE)
	$(CODEGEN_EXE) --template $< --write-to $@
CLEAN += messages.h
CODEGEN_FILES += messages.h

nodes.h: codegen/nodes.h.liquid $(CODEGEN_EXE)
	$(CODEGEN_EXE) --template $< --write-to $@
CLEAN += nodes.h
CODEGEN_FILES += nodes.h

lib/lib-ruby-parser/messages.rb: codegen/messages.rb.liquid $(CODEGEN_EXE)
	$(CODEGEN_EXE) --template $< --write-to $@
CLEAN += lib/lib-ruby-parser/messages.rb
CODEGEN_FILES += lib/lib-ruby-parser/messages.rb

lib/lib-ruby-parser/nodes.rb: codegen/nodes.rb.liquid $(CODEGEN_EXE)
	$(CODEGEN_EXE) --template $< --write-to $@
CLEAN += lib/lib-ruby-parser/nodes.rb
CODEGEN_FILES += lib/lib-ruby-parser/nodes.rb

# manual codegen task
do-codegen: $(CODEGEN_FILES)
.PHONY: do-codegen
