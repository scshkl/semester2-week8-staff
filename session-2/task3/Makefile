# Variables
CC = gcc
CFLAGS = -Wall -Wextra
TARGET = student_program
OBJS = main.o student.o

# Phony targets (not actual files)
.PHONY: all clean

# Default target
all: $(TARGET)

# Default target
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Object files
main.o: main.c student.h structure.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c student.h structure.h
	$(CC) $(CFLAGS) -c student.c

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)