# Script for getting relevant 64bit windows headers
# Run from the parent awbw-gui directory in Bash-CLI
# Note: wget isn't on Bash-CLI by default; download 64bit exe from https://eternallybored.org/misc/wget/
#	and run mv C:\[USERNAME]\Downloads\wget.exe C:\Program Files\Git\mingw64\bin
#	from an ELEVATED PowerShell prompt

mkdir ext
cd ext

# giflib
git clone https://github.com/tofy-dev/giflib-cmake
mv giflib-cmake GIFLib
cd GIFLib

cmake -G "MinGW Makefiles" .
cmake --build .

cp *.dll ../../bin/

cd ..


# sdl2
mkdir SDL2

## sdl-base
SDL_VERSION="2.26.4"
wget https://github.com/libsdl-org/SDL/releases/download/release-$SDL_VERSION/SDL2-devel-$SDL_VERSION-mingw.zip
unzip SDL2-devel-$SDL_VERSION-mingw.zip

cp SDL2-$SDL_VERSION/x86_64-w64-mingw32/lib/*.a SDL2
cp SDL2-$SDL_VERSION/x86_64-w64-mingw32/include/SDL2/*.[hc] SDL2
cp SDL2-$SDL_VERSION/x86_64-w64-mingw32/bin/*.dll ../bin/


## sdl-image
IMG_VERSION="2.6.3"
wget https://github.com/libsdl-org/SDL_image/releases/download/release-$IMG_VERSION/SDL2_image-devel-$IMG_VERSION-mingw.zip
unzip SDL2_image-devel-$IMG_VERSION-mingw.zip

cp SDL2_image-$IMG_VERSION/x86_64-w64-mingw32/lib/*.a SDL2
cp SDL2_image-$IMG_VERSION/x86_64-w64-mingw32/include/SDL2/*.[hc] SDL2
cp SDL2_image-$IMG_VERSION/x86_64-w64-mingw32/bin/*.dll ../bin/


# clean up
rm *.zip
rm -rf SDL2-$SDL_VERSION
rm -rf SDL2_image-$IMG_VERSION
