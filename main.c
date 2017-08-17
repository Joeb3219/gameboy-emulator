#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "cpu.h"

int main(int argc, char** argv){

	struct cpu_cpu *cpu = createCPU();

	printf("Hello world!\n");

	cpu->registers->hl = 0xf84A;

	printRegisters(cpu->registers);
	printf("Register HL: %d\n", cpu->registers->hl);

	destroyCPU(cpu);

	return 0;

}
