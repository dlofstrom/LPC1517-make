# Main makefile for application

BINARY = test
CC = arm-none-eabi-gcc
COPY = arm-none-eabi-objcopy
BUILD_PATH = build

all: $(BINARY)

CORE ?= lpc1517
CORE_PATH = core/$(CORE)
include $(CORE_PATH)/Makefile.core

# Main source file
MAIN = main.c
MAIN_OBJ = $(BUILD_PATH)/$(MAIN:.c=.o)
OBJ += $(MAIN_OBJ)

# J-Link support
JLINK = JLinkExe -device $(CORE) -if swd -speed 4000
JLINK_FILE = $(BUILD_PATH)/flash.jlink

.PHONY: flash
flash: all $(JLINK_FILE)
	$(JLINK) $(JLINK_FILE)

$(JLINK_FILE):
	echo "loadfile $(BUILD_PATH)/$(BINARY).hex\nr\nexit\n" > $(JLINK_FILE)

$(MAIN_OBJ): $(MAIN)
	$(CC) -I$(INC) $(CFLAGS) -o $@ -c $<

$(BINARY): $(BUILD_PATH)/$(BINARY).hex $(BUILD_PATH)/$(BINARY).bin $(BUILD_PATH)/$(BINARY).elf

$(BUILD_PATH)/%.hex: $(BUILD_PATH)/%.elf
	$(COPY) -O ihex $< $@

$(BUILD_PATH)/%.bin: $(BUILD_PATH)/%.elf
	$(COPY) -v -O binary $< $@

$(BUILD_PATH)/%.elf: $(OBJ)
	$(CC) -I$(INC) $(CFLAGS) $(OBJ) -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_PATH)
