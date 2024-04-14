# Compiler and flags
CC=gcc
CFLAGS=-Iinclude -Wall

# Define the target executable
TARGET_DIR=output
TARGET=$(TARGET_DIR)/compress

# Define source and object files
SRCS=$(wildcard src/*.c)

compile:
	@[ -d "$(TARGET_DIR)" ] || mkdir -p "$(TARGET_DIR)"
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)
