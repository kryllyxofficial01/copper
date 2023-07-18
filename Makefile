.SILENT:

GXX=g++
GXX_FLAGS=-std=c++17

BUILD=build

SRC=$(wildcard src/*.cpp)

file=

all: mkbuild clean compile run
build: mkbuild clean compile

compile:
	$(GXX) $(GXX_FLAGS) $(SRC) -o $(BUILD)/main

run:
	./$(BUILD)/main $(file)

mkbuild:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*