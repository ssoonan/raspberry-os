# Define the cross-compiler prefix
CROSS_COMPILE = aarch64-linux-gnu-

# Define compiler and linker
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

# Define C flags
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only

# Source files
ASM_SOURCES = boot.s lib.s handler.s mmu.s
C_SOURCES = main.c uart.c print.c debug.c handler.c memory.c file.c process.c syscall.c lib.c

# Define object files
ASM_OBJECTS = boot.o liba.o handlera.o mmu.o
C_OBJECTS = main.o uart.o print.o debug.o handler.o memory.o file.o process.o syscall.o lib.o

# Final output
KERNEL = kernel
KERNEL_IMG = kernel8.img

# Linker script
LDSCRIPT = link.lds

# Targets
.PHONY: all clean lib-build init-build

# Default target
all: lib-build init-build $(KERNEL_IMG)

# Rule to create kernel8.img
$(KERNEL_IMG): $(KERNEL)
	$(OBJCOPY) -O binary $(KERNEL) $(KERNEL_IMG)
	dd if=image/os.img >> $(KERNEL_IMG)

# Rule to link the kernel
$(KERNEL): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) -nostdlib -T $(LDSCRIPT) -o $(KERNEL) $(ASM_OBJECTS) $(C_OBJECTS)

# Rules to compile assembly files
boot.o: boot.s
	$(CC) -c boot.s -o boot.o

liba.o: lib.s
	$(CC) -c lib.s -o liba.o

handlera.o: handler.s
	$(CC) -c handler.s -o handlera.o

mmu.o: mmu.s
	$(CC) -c mmu.s -o mmu.o

# Rules to compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) $(KERNEL) $(KERNEL_IMG)
	$(MAKE) -C lib clean
	$(MAKE) -C init clean

# Target to ensure init directory Makefile runs
init-build:
	$(MAKE) -C init

lib-build:
	$(MAKE) -C lib
