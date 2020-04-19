# config.mk

CC=gcc

PROG_NAME=game

INCLUDE_DIR=include

SRC_DIR=src

SRC_FILES=$(SRC_DIR)/*.c

SRC_FILES+=$(SRC_DIR)/entity_types/*.c

BUILD_DIR=build

RESOURCES_DIR=resources

LIBS=-lSDL2 -lSDL2_ttf -lpng -lm

FLAGS=$(SRC_FILES) -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$(PROG_NAME) -O2 -Wall

FLAGS_DEBUG=-g
