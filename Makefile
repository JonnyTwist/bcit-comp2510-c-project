# Compiler
CC = gcc

# Compiler Flags (added -fsanitize=address)
CFLAGS = -Wall -Wextra -std=c11 -fsanitize=address -g

# Sources and Objects
SRC = main.c patient.c dsm.c list.c test.c file_m.c report.c
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

# Run Target (Optional)
run: $(TARGET)
	./$(TARGET)

# Clean Rule
clean:
	rm -f $(OBJ) $(TARGET)

# Phony Targets
.PHONY: all clean run
