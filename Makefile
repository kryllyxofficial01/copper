GXX=g++

GXX_FLAGS=-g -std=c++17

BUILD=build

all: compile

compile: mkbuild clean
	$(GXX) $(GXX_FLAGS) src/main.cpp -o $(BUILD)/main

mkbuild:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*