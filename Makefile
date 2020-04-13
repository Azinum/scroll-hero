# Makefile

include config.mk

all: prepare build_debug run

prepare:
	mkdir -p $(BUILD_DIR)

build_debug:
	$(CC) $(FLAGS) $(LIBS)

run:
	./$(BUILD_DIR)/$(PROG_NAME)
