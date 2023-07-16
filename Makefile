.SILENT:

GXX=g++
GXX_FLAGS=-std=c++17

BUILD=build

SRC=$(wildcard src/*.cpp)

FILE=

all: mkbuild clean compile run
build: mkbuild clean compile

compile:
	$(GXX) $(GXX_FLAGS) $(SRC) -o $(BUILD)/main

run:
	./$(BUILD)/main $(FILE)

mkbuild:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*