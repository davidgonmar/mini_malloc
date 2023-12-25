CC=gcc
CFLAGS=-Wall
SRCFILES = $(wildcard *.c)
BIN_DIR=bin
HEADERS = $(wildcard *.h)

.PHONY: all format

test:
ifeq ($(OS),Windows_NT)
	$(CC) $(SRCFILES) -o $(BIN_DIR)\test && $(BIN_DIR)\test
else
	$(CC) $(SRCFILES) -o $(BIN_DIR)/test && $(BIN_DIR)/test
endif

format:
	clang-format -i $(SRCFILES) $(HEADERS)