CC := gcc

all: clean emul

emul: main.c
	$(CC) -Wall -g -o emul main.c cpu.c

clean:
	rm -rf emul emul.o
