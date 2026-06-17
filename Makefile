CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -I./include \
		   -Wnull-dereference \
		  -fstack-protector-strong -fno-common -fPIC \
         -Wshadow -Wformat=2 -Wconversion -Wstrict-prototypes \
         #-Wdouble-promotion -Wundef -Wwrite-strings \
         #-Wfloat-equal -Wpointer-arith \

AR = ar
ARFLAGS = rcs

SRC_DIR = src/ds
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = tests
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(BIN_DIR)/%, $(TEST_SRCS))

LIB = $(LIB_DIR)/libarc.a

.PHONY: all clean test

all: $(LIB) $(TEST_BINS)

$(LIB): $(OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB) | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -larc -o $@

$(OBJ_DIR) $(LIB_DIR) $(BIN_DIR):
	mkdir -p $@

test: $(TEST_BINS)
	@for test_bin in $(TEST_BINS); do \
		echo "Running $$test_bin with valgrind..."; \
		valgrind --leak-check=full --error-exitcode=1 $$test_bin || exit 1; \
	done

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)
