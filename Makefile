GXX = g++

GXX_FLAGS = -g -std=c++17 -Wno-return-type

BUILD = build
OBJ = $(BUILD)/obj
EXEC = copper

SRC = $(wildcard src/*.cpp)
OBJS = $(subst src/, $(OBJ)/, $(addsuffix .o, $(basename $(SRC))))

FILE =

all: clean compile

compile: $(BUILD)/$(EXEC)

$(BUILD)/$(EXEC): $(OBJS)
	$(GXX) $(OBJS) -o $@

$(OBJ)/%.o: src/%.cpp
	$(GXX) $(GXX_FLAGS) -c $< -o $@

ifeq ($(OS), Windows_NT)
.SILENT: clean
endif

.PHONY: clean
clean: mkbuild
ifeq ($(OS), Windows_NT)
	del /Q /S $(BUILD)\*
else ifeq ($(shell uname), Linux)
	find $(BUILD) -maxdepth 1 -type f -exec rm {} \;
	rm -rf $(OBJ)/*
endif

mkbuild:
ifeq ($(OS), Windows_NT)
	if not exist "$(BUILD)" mkdir "$(BUILD)"
	if not exist "$(OBJ)" mkdir "$(OBJ)"
else ifeq ($(shell uname), Linux)
	mkdir -p $(BUILD)
	mkdir -p $(OBJ)
endif

debug: compile
ifneq ($(OS), Windows_NT)
	ifeq ($(shell uname), Linux)
		valgrind -s --track-origins=yes $(BUILD)/$(EXEC) $(FILE)
	endif
endif