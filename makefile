# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable name
TARGET = program

# Source files
SRCS = main.c menu.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	del /f /q $(TARGET).exe *.o 2>nul || rm -f $(TARGET) *.o
