CC = gcc
CFLAGS = -Wall -Wextra -Werror -pg -O0

SRC_DIR = src
BIN_DIR = bin
RESULT_DIR = result

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
EXECUTABLES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRC_FILES))

all: $(EXECUTABLES)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: style clean run
style:
	find . -type f -name '*.[ch]' | xargs clang-format -style=file -i --verbose

run:
	mkdir -p $(RESULT_DIR)
	./run.sh

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(RESULT_DIR)
