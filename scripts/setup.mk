ifndef TARGET
$(error TARGET variable is required)
endif

include scripts/targets/$(TARGET).mk

define download_file
URL="$(1)" SAVE_AS="$(2)" ruby scripts/download_file.rb
endef

$(info Build configuration:)

$(info O = $(O))
$(info A = $(A))
$(info download_file = $(call download_file,https://example.com,path/to/file))
