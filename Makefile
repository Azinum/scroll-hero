# Makefile

include config.mk

all: prepare build_debug run

clean:
	rm -dr $(BUILD_DIR)/*

prepare:
	python3 gen_entity_types.py
	mkdir -p $(BUILD_DIR)
	cp -r $(RESOURCES_DIR)/ $(BUILD_DIR)/$(RESOURCES_DIR)/

build_debug:
	$(CC) $(FLAGS) $(LIBS)

run:
	./$(BUILD_DIR)/$(PROG_NAME)
