#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

struct cpu_cpu* createCPU(){
	struct cpu_cpu *cpu = malloc(sizeof(struct cpu_cpu));
	cpu->registers = malloc(sizeof(struct cpu_registers));
	return cpu;
}

void destroyCPU(struct cpu_cpu* cpu){
	free(cpu->registers);
	free(cpu);
}

int cpu_fetch(){

        return 0;
}

int cpu_decode(){

        return 0;
}

int cpu_execute(){

        return 0;
}

void cpu_run(struct cpu_cpu cpu){

        while(1 == 1){
                cpu_fetch();
                cpu_decode();
                cpu_execute();
                break;
        }

}

void printRegisters(struct cpu_registers* registers){
	printf("==== Registers ====\n");

	printf("HL: %0x\n", registers->hl);
	printf(" H: %0x\n", registers->h);
	printf(" L: %0x\n", registers->l);
	printf("AF: %0x\n", registers->af);
	printf(" A: %0x\n", registers->a);
	printf(" F: %0x\n", registers->f);
	printf("DE: %0x\n", registers->de);
	printf(" D: %0x\n", registers->d);
	printf(" E: %0x\n", registers->e);
	printf("BC: %0x\n", registers->bc);
	printf(" B: %0x\n", registers->b);
	printf(" C: %0x\n", registers->c);

	printf("== End Registers ==\n");
}
