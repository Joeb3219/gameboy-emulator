CC := gcc
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include

all: clean emul

emul: main.c cpu.c gpu.c
	$(CC) -Wall -g -o emul `sdl2-config --cflags --libs` main.c cpu.c gpu.c -lSDL2

clean:
	rm -rf emul emul.o cpu.o
