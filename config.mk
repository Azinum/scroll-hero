# config.mk

CC=gcc

PROG_NAME=game

INCLUDE_DIR=include

SRC_DIR=src

SRC_FILES=$(SRC_DIR)/*.c

BUILD_DIR=build

LIBS=-lSDL2

FLAGS=$(SRC_FILES) -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$(PROG_NAME) -O2 -Wall

FLAGS_DEBUG=-g
