# Directory setup
SRC_DIR = src
BOOT_SRC = $(SRC_DIR)/boot
KERNEL_SRC = $(SRC_DIR)/kernel
DRIVERS_SRC = $(SRC_DIR)/drivers
INCLUDE_DIR = $(BOOT_SRC)/include
BUILD_DIR = build
OUTPUT_DIR = output
LD = i386-elf-ld
GCC = i386-elf-gcc

# Sources and headers
C_SOURCES = $(wildcard $(KERNEL_SRC)/*.c $(DRIVERS_SRC)/*.c $(SRC_DIR)/include/*.c)
HEADERS = $(wildcard $(KERNEL_SRC)/*.h $(DRIVERS_SRC)/*.h $(SRC_DIR)/include/*.h)
OBJ = $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(C_SOURCES:.c=.o))

# Final image
all: $(OUTPUT_DIR)/image.bin

# Running in QEMU
run: all
	qemu-system-x86_64 -drive format=raw,file=$(OUTPUT_DIR)/image.bin

# Ensure directories exist
$(OUTPUT_DIR) $(BUILD_DIR):
	mkdir -p $@

# Create image by concatenating bootloader and kernel binary
$(OUTPUT_DIR)/image.bin: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin | $(OUTPUT_DIR)
	cat $^ > $@

# Assemble bootloader
$(BUILD_DIR)/%.bin: $(BOOT_SRC)/%.asm | $(BUILD_DIR)
	nasm -f bin $< -o $@ -I $(INCLUDE_DIR)

# Link kernel binary
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel_entry.o $(OBJ) | $(BUILD_DIR)
	$(warning OBJ is $(OBJ))
	$(warning HEADERS is $(HEADERS))
	$(warning CSRCS is $(C_SOURCES))
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Assemble kernel entry code
$(BUILD_DIR)/%.o: $(KERNEL_SRC)/%.asm | $(BUILD_DIR)
	nasm $< -f elf -o $@

# Compile kernel and driver C code
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(GCC) -ffreestanding -m32 -g -c $< -o $@ -I $(SRC_DIR)/include -I $(SRC_DIR)

# Clean up build and output files
clean:
	rm -fr $(BUILD_DIR) $(OUTPUT_DIR) \
		$(DRIVERS_SRC)/*.bin $(DRIVERS_SRC)/*.dis $(DRIVERS_SRC)/*.o \
		$(KERNEL_SRC)/*.bin $(KERNEL_SRC)/*.dis $(KERNEL_SRC)/*.o

.PHONY: all run clean
