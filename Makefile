all:
	g++ -Isrc/include/SDL2 -Iinclude/headers -Lsrc/lib -o main runFile/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -static-libstdc++ -static-libgcc -mwindows
