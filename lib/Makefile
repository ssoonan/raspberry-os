# Define the cross-compiler prefix
CROSS_COMPILE = aarch64-linux-gnu-

# Define compiler, assembler, and archiver
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

# Define C flags
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only

# Source files
ASM_SOURCES = syscall.s
C_SOURCES = print.c

# Object files
ASM_OBJECTS = $(ASM_SOURCES:.s=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)

# Output library
LIBRARY = lib.a

# Default target
.PHONY: all clean

all: $(LIBRARY)

# Rule to create the static library lib.a
$(LIBRARY): $(ASM_OBJECTS) $(C_OBJECTS)
	$(AR) rcs $(LIBRARY) $(ASM_OBJECTS) $(C_OBJECTS)

# Rule to compile assembly files
%.o: %.s
	$(CC) -c $< -o $@

# Rule to compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) $(LIBRARY)
