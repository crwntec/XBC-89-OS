# Directory setup
SRC_DIR = src
BOOT_SRC = $(SRC_DIR)/boot
KERNEL_SRC = $(SRC_DIR)/kernel
INCLUDE_DIR = $(BOOT_SRC)/include
BUILD_DIR = build
OUTPUT_DIR = output

# Sources and headers
C_SOURCES = $(wildcard $(SRC_DIR)/kernel/*.c $(SRC_DIR)/drivers/*.c)
OBJ = $(C_SOURCES:.c=.o)
HEADERS = $(wildcard $(SRC_DIR)/kernel/*.h $(SRC_DIR)/drivers/*.h)

# Final image
all: $(OUTPUT_DIR)/image.bin

# Running in QEMU
run: all
	qemu-system-x86_64.exe -drive format=raw,file=$(OUTPUT_DIR)/image.bin

# Ensure directories exist
$(OUTPUT_DIR) $(BUILD_DIR):
	mkdir -p $@

# Create image by concatenating bootloader and kernel binary
$(OUTPUT_DIR)/image.bin: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin | $(OUTPUT_DIR)
	cat $^ > $@

# Assemble bootloader
$(BUILD_DIR)/%.bin : $(BOOT_SRC)/%.asm | $(BUILD_DIR)
	nasm -f bin $< -o $@ -I $(INCLUDE_DIR)

# Link kernel binary
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel_entry.o ${OBJ} | $(BUILD_DIR)
	$(warning OBJ is ${OBJ})
	$(warning SRCS is ${C_SOURCES})
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Assemble kernel entry code
$(BUILD_DIR)/%.o: $(KERNEL_SRC)/%.asm | $(BUILD_DIR)
	nasm $< -f elf -o $@

# Compile kernel C code
%.o: %.c ${HEADERS} | $(BUILD_DIR)
	$(warning HEADERS is ${HEADERS})
	i386-elf-gcc -ffreestanding -m32 -g -c $< -o $@ -I $(SRC_DIR)

# Clean up build and output files
clean:
	rm -fr $(BUILD_DIR) $(OUTPUT_DIR)
	rm -f src/drivers/*.bin src/drivers/*.dis src/drivers/*.o
	rm -f src/kernel/*.bin src/kernel/*.dis src/kernel/*.o
	rm -f $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin $(OUTPUT_DIR)/image.bin

.PHONY: all run clean
