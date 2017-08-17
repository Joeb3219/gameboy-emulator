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

#define MEMORY_STACK_START 0xFFFE

void loadROM(unsigned char *memory, char *fileName){
	FILE * rom = fopen(fileName, "r");
	size_t fileSize = 0;

	fseek(rom, 0, SEEK_END);
	fileSize = ftell(rom);
	rewind(rom);

	fread(memory + MEMORY_ROM_0_START, fileSize, 1, rom);

	fclose(rom);
}

void resetStackAndRegisters(struct cpu_cpu *cpu, unsigned char *memory){
	cpu->registers->a = 0x0001;
	cpu->registers->f = 0x00B0;
	cpu->registers->bc = 0x0013;
	cpu->registers->de = 0x00D8;
	cpu->registers->hl = 0x014D;
	cpu->registers->sp = 0xFFFE;
	memory[0xFF05] = memory[0xFF06] = memory[0xFF07] = 0x0000;
	memory[0xFF10] = 0x0080;
	memory[0xFF11] = 0xBF;
	memory[0xFF12] = 0xF3;
	memory[0xFF14] = 0xBF;
	memory[0xFF16] = 0x3F;
	memory[0xFF17] = 0x00;
	memory[0xFF19] = 0xBF;
	memory[0xFF1A] = 0x7F;
	memory[0xFF1B] = 0xFF;
	memory[0xFF1C] = 0x9F;
	memory[0xFF1E] = 0xBF;
	memory[0xFF20] = 0xFF;

	memory[0xFF21] = 0x00;
	memory[0xFF22] = 0x00;
	memory[0xFF23] = 0xBF;
	memory[0xFF24] = 0x77;
	memory[0xFF25] = 0xF3;
	memory[0xFF26] = 0xF1;
	memory[0xFF40] = 0x91;
	memory[0xFF42] = 0x00;
	memory[0xFF43] = 0x00;
	memory[0xFF45] = 0x00;
	memory[0xFF47] = 0xFC;
	memory[0xFF48] = 0xFF;
	memory[0xFF49] = 0xFF;
	memory[0xFF4A] = 0x00;
	memory[0xFF4B] = 0x00;
	memory[0xFFFF] = 0x00;

	cpu->registers->pc = 0x100;
}

int main(int argc, char** argv){
	int i, tmp;

	if(argc != 2){
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	struct cpu_cpu *cpu = createCPU();

	loadROM(cpu->memory, argv[1]);

	// POWER UP SEQUENCE

	// Verify that rom has valid signature.
	tmp = 0;
	for(i = 0x134; i < 0x14d; i ++) tmp += cpu->memory[i];
	if( ( (tmp + 25) & 0x80) != 0x80){
		printf("Invalid signature.\n");
		return 1;
	}

	// Verification complete, we can now load in values to registers for program execution.


	resetStackAndRegisters(cpu, cpu->memory);

	printRegisters(cpu->registers);

	printf("Loading successful: Now executing the game.\n");

	cpu_run(cpu);

	destroyCPU(cpu);

	return 0;

}
