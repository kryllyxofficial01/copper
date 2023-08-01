GXX=g++

GXX_FLAGS=-g -std=c++17 -Wno-return-type

BUILD=build

SRC=$(wildcard src/*.cpp)

all: compile

compile: mkbuild clean
	$(GXX) $(GXX_FLAGS) $(SRC) -o $(BUILD)/main

mkbuild:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*