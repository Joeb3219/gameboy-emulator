#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "cpu.h"

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

	

	destroyCPU(cpu);

	return 0;

}
