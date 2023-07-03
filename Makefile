BUILD_DIR=build
include $(N64_INST)/include/n64.mk

src = $(wildcard src/*.c)
assets_png = $(wildcard assets/*.png)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite)))

MKSPRITE_FLAGS ?=

all: jamentry.z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) -f RGBA16 --compress -o "$(dir $@)" "$<"

#$(BUILD_DIR)/jamentry.dfs: $(assets_conv)
$(BUILD_DIR)/jamentry.elf: $(src:%.c=$(BUILD_DIR)/%.o)

jamentry.z64: N64_ROM_TITLE="2023 Jam Entry"
#jamentry.z64: $(BUILD_DIR)/jamentry.dfs

clean:
	rm -rf $(BUILD_DIR) filesystem/ jamentry.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
