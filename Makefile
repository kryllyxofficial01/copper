GXX = g++

GXX_FLAGS = -g -Wno-return-type

BUILD = build

SRC = $(wildcard src/*.cpp)

all: compile

compile: clean
	$(GXX) $(GXX_FLAGS) $(SRC) -o $(BUILD)/main

clean: common
	rm -rf $(BUILD)/*

common:
	mkdir -p $(BUILD)