# Makefile for building the project

# Compiler and tools
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

# Flags and options
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only
LDFLAGS = -nostdlib
OBJCOPYFLAGS = -O binary

# Source files and targets
ASM_SRC = start.s
ASM_OBJ = start.o
C_SRC = main.c
C_OBJ = main.o
LIB = ../lib/lib.a
LDSCRIPT = link.lds
TARGET = test
BIN = test.bin

# Default rule
all: $(BIN)

# Rule to build the final binary
$(BIN): $(ASM_OBJ) $(C_OBJ) $(LIB)
	$(LD) $(LDFLAGS) -T $(LDSCRIPT) -o $@ $(ASM_OBJ) $(C_OBJ) $(LIB)
	$(OBJCOPY) $(OBJCOPYFLAGS) $@ $@

# Rule to compile assembly source
$(ASM_OBJ): $(ASM_SRC)
	$(CC) -c $(ASM_SRC) -o $(ASM_OBJ)

# Rule to compile C source
$(C_OBJ): $(C_SRC)
	$(CC) $(CFLAGS) -c $(C_SRC) -o $(C_OBJ)

# Clean rule
clean:
	rm -f $(ASM_OBJ) $(C_OBJ) $(TARGET) $(BIN)

.PHONY: all clean
