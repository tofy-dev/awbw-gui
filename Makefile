OS = LINUX

ifeq ($(OS), WINDOWS))
	CXX = g++
	COMPILER_FLAGS = -w -Iext\ -Iext\GIFLib\ -Iinclude\ --std=c++17 -g3 -static-libstdc++
	LINKER_FLAGS = -Lext\SDL2 -Lext\GIFLib -lSDL2 -lSDL2main -lSDL2_image -lgiflib
	CPP_FILES = src\Main.cpp include\\*.cpp
	OUTPUT_NAME = bin\output.exe
else
	CXX = clang++
	COMPILER_FLAGS = -w -Iinclude/ --std=c++17 -g3
	LINKER_FLAGS = -lSDL2main -lSDL2 -lSDL2_image -lgif
	CPP_FILES = src/Main.cpp include/*.cpp
	OUTPUT_NAME = bin/output
endif

all:
	$(CXX) $(COMPILER_FLAGS) $(CPP_FILES) $(LINKER_FLAGS) -o $(OUTPUT_NAME)

clean:
	rm -rf bin/output*
	rm -rf ext/
