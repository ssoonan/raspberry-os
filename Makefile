# Compiler and flags
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only
LDFLAGS = -nostdlib -T link.lds

# Source files
ASM_SOURCES = boot.s lib.s
C_SOURCES = main.c uart.c print.c debug.c

# Object files
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)

# Output files
KERNEL = kernel
IMG = kernel8.img

.PHONY: all clean

# Default target
all: $(IMG)

# Build kernel image
$(IMG): $(KERNEL)
	$(OBJCOPY) -O binary $(KERNEL) $(IMG)

# Link object files to create the kernel
$(KERNEL): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $(KERNEL) $(ASM_OBJECTS) $(C_OBJECTS)

# Compile assembly sources
%.o: %.s
	$(CC) -c $< -o $@

# Compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) $(KERNEL) $(IMG)

