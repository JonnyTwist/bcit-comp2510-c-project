# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Wextra -std=c11

# Sources and Objects
SRC = main.c patient.c dsm.c
OBJ = $(SRC:.c=.o)

# Output Binary
TARGET = manage_hosp

# Default Rule
all: $(TARGET)

# Linking Rule
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation Rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean Rule
clean:
	rm -f $(OBJ) $(TARGET)

# Phony Targets
.PHONY: all clean
