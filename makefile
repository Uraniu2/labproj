# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Output executable
EXEC = jogo

# Source files
SRCS = main.c menu.c logic.c

# Object files (created by compiling source files)
OBJS = $(SRCS:.c=.o)

# Default target to build the executable
all: $(EXEC)

# Rule to link the object files into the final executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Rule to compile each .c file into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)

# Make sure 'clean' and 'run' are not treated as filenames
.PHONY: all clean run

