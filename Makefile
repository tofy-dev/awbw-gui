CXX = clang++

COMPILER_FLAGS = -w -Iinclude/ --std=c++17
LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image

CPP_FILES = src/Main.cpp include/*.cpp
OUTPUT_NAME = bin/output

all: $(OBJ_NAMES)
	$(CXX) $(CPP_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_NAME)

clean:
	rm -rf bin/*
