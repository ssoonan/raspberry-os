# Compiler and flags
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only
LDFLAGS = -nostdlib -T link.lds

# Source files
ASM_SOURCES = boot.s lib.s handler.s
C_SOURCES = main.c uart.c print.c debug.c handler.c

# Object files
ASM_OBJECTS = boot.o liba.o handlera.o
C_OBJECTS = main.o uart.o print.o debug.o handler.o

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
boot.o: boot.s
	$(CC) -c boot.s -o boot.o

liba.o: lib.s
	$(CC) -c lib.s -o liba.o

handlera.o: handler.s
	$(CC) -c handler.s -o handlera.o

# Compile C sources
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) $(KERNEL) $(IMG)

