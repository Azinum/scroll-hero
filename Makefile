# Makefile

include config.mk

all: prepare build_debug run

clean:
	rm -dr $(BUILD_DIR)/*

prepare:
	mkdir -p $(BUILD_DIR)
	cp -r $(RESOURCES_DIR)/ $(BUILD_DIR)/$(RESOURCES_DIR)/

build_debug:
	$(CC) $(FLAGS) $(LIBS)

run:
	./$(BUILD_DIR)/$(PROG_NAME)
