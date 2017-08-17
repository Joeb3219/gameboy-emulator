#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "cpu.h"

#define MEMORY_ROM_0_START 0x0000
#define MEMORY_ROM_B_START 0x4000
#define MEMORY_VRAM_START 0x8000
#define MEMORY_VRAM_SWITCH_START 0xA000
#define MEMORY_INTERNAL_RAM_START 0xC000
#define MEMORY_INTERNAL_RAM_ECHO_START  0xE000
#define MEMORY_SPRITE_ATTR_START  0xFE00
#define MEMORY_EMPTY_BEFORE_IO_START 0xFEA0
#define MEMORY_IO_PORTS_START 0xFF00
#define MEMORY_EMPTY_AFTER_IO_START 0xFF40
#define MEMORY_INTERNAL_RAM_END_START 0xFFC0
#define MEMORY_INTERRUPT_ENABLE_START 0xFFFF

void loadROM(unsigned char *memory, char *fileName){
	FILE * rom = fopen(fileName, "r");
	size_t fileSize = 0;

	fseek(rom, 0, SEEK_END);
	fileSize = ftell(rom);
	rewind(rom);

	fread(memory + MEMORY_ROM_0_START, fileSize, 1, rom);

	fclose(rom);
}

int main(int argc, char** argv){

	if(argc != 2){
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	struct cpu_cpu *cpu = createCPU();

	printf("Hello world!\n");

	cpu->registers->hl = 0xf84A;

	printRegisters(cpu->registers);
	printf("Register HL: %d\n", cpu->registers->hl);

	printf("%d\n", instructions[0].numArgs);

	unsigned char *memory = calloc(sizeof(unsigned char), 0xFFFF); // Request 0xFFFF bytes of memory
	loadROM(memory, argv[1]);

	printf("Memory @ 0x000: %0x\n", memory[0x0000]);

	destroyCPU(cpu);

	return 0;

}
