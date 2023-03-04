CXX = clang++

COMPILER_FLAGS = -w -Iinclude/ --std=c++17 -g3
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lgif

CPP_FILES = src/Main.cpp include/*.cpp
OUTPUT_NAME = bin/output

all:
	$(CXX) $(CPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_NAME)

clean:
	rm -rf bin/*
