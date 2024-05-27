GXX = g++

GXX_FLAGS = -g -Wno-return-type

BUILD = build
EXEC = main

SRC = $(wildcard src/*.cpp)

FILE=

all: compile

compile: clean
	$(GXX) $(GXX_FLAGS) $(SRC) -o $(BUILD)/$(EXEC)

clean: common
	rm -rf $(BUILD)/*

common:
	mkdir -p $(BUILD)

debug: compile
	valgrind -s --track-origins=yes --leak-check=full $(BUILD)/$(EXEC) $(FILE)