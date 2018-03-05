CXX=/usr/bin/clang++
SDLCFLAGS=-I/usr/local/include/SDL2 -D_THREAD_SAFE
SDLLIBS=-L/usr/local/lib -lSDL2

all:
	$(CXX) $(SDLCFLAGS) src/core/game.cc -o build/pacman $(SDLLIBS)
