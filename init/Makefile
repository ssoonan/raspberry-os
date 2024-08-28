# Define the cross-compiler prefix
CROSS_COMPILE = aarch64-linux-gnu-

# Define compiler and linker
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

# Define C flags
CFLAGS = -std=c99 -ffreestanding -mgeneral-regs-only

# Source files
ASM_SOURCES = start.s
C_SOURCES = main.c

# Define object files
ASM_OBJECTS = start.o
C_OBJECTS = main.o

# Final output
INIT_BIN = init.bin
DISK_IMAGE = ../image/os.img

# Linker script
LDSCRIPT = link.lds

# Targets
.PHONY: all clean build-image

# Default target
all: build-image $(INIT_BIN)

# Rule to create init.bin
$(INIT_BIN): start.o main.o
	$(LD) -nostdlib -T $(LDSCRIPT) -o init start.o main.o
	$(OBJCOPY) -O binary init $(INIT_BIN)

# Rule to build the disk image with init.bin
build-image: $(INIT_BIN)
	# Set up loop device and mount in one line to keep variables
	sudo losetup --find --show $(DISK_IMAGE) | \
	while read LOOP_DEV; do \
		MOUNT_POINT=`mktemp -d`; \
		OFFSET=$$((63 * 512)); \
		sudo mount -o loop,offset=$$OFFSET $$LOOP_DEV $$MOUNT_POINT; \
		sudo cp $(INIT_BIN) $$MOUNT_POINT; \
		sudo umount $$MOUNT_POINT; \
		sudo losetup -d $$LOOP_DEV; \
		rmdir $$MOUNT_POINT; \
	done

# Rules to compile assembly files
start.o: start.s
	$(CC) -c start.s -o start.o

# Rules to compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(ASM_OBJECTS) $(C_OBJECTS) init $(INIT_BIN)
