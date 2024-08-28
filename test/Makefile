# Define variables
CC = aarch64-linux-gnu-gcc
OBJCOPY = aarch64-linux-gnu-objcopy
CFLAGS = -c
OBJ = test.o
BIN = TEST.BIN
SRC = test.s

# Default target
all: $(BIN)

# Rule to create the object file
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

# Rule to create the binary file
$(BIN): $(OBJ)
	$(OBJCOPY) -O binary $(OBJ) $(BIN)

# Clean up the generated files
clean:
	rm -f $(OBJ) $(BIN)
