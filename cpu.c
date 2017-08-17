#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

// No operation
Status fn_nop(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	return OK;
}

// Absolute jump
Status fn_jp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short address = (arg1 << 8) | arg2;
	address --; // Avoid increment that occurs after instruction execute
	cpu->registers->pc = address;
	return OK;
}

// Copy B => C
Status fn_ld_c_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->b;
	return OK;
}

// Copy C => C
Status fn_ld_c_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->c;
	return OK;
}

// Copy D => C
Status fn_ld_c_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->d;
	return OK;
}

// Copy E => C
Status fn_ld_c_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->e;
	return OK;
}

// Copy H => C
Status fn_ld_c_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->h;
	return OK;
}

// Copy L => C
Status fn_ld_c_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->l;
	return OK;
}

// Bitwise invert all bits in A register.
Status fn_cpl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = ~cpu->registers->a;
	cpu->registers->flag_sub = cpu->registers->flag_halfcarry = 1;
	return OK;
}

// Decrement BC
Status fn_dec_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->bc = cpu->registers->bc - 1;
	return OK;
}

// Decrement DE
Status fn_dec_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->de = cpu->registers->de - 1;
	return OK;
}

// Decrement HL
Status fn_dec_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->hl = cpu->registers->hl - 1;
	return OK;
}

// Decrement SP
Status fn_dec_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->sp = cpu->registers->sp - 1;
	return OK;
}

struct cpu_cpu* createCPU(){
	struct cpu_cpu *cpu = malloc(sizeof(struct cpu_cpu));
	cpu->registers = malloc(sizeof(struct cpu_registers));
	cpu->memory = calloc(sizeof(unsigned char), 0xFFFF);
	return cpu;
}

void destroyCPU(struct cpu_cpu* cpu){
	free(cpu->registers);
	free(cpu);
}

void cpu_decode(struct cpu_cpu *cpu, struct cpu_instruction *instruction, unsigned char *arg1, unsigned char *arg2){
	unsigned char instrOpcode = cpu->memory[cpu->registers->pc];
	*instruction = instructions[instrOpcode];
	if(instruction->numArgs > 0) (*arg1) = cpu->memory[cpu->registers->pc + 1];
	if(instruction->numArgs > 1) (*arg2) = cpu->memory[cpu->registers->pc + 2];
	if(instruction->numArgs > 2) printf("Err: Expected a maximum of 2 args, however %s carries %d args.\n", instruction->opcode, instruction->numArgs);
        return;
}

void cpu_run(struct cpu_cpu *cpu){
	Status status = OK;
	unsigned char arg1, arg2;
	struct cpu_instruction instruction;

        while(status == OK){
                cpu_decode(cpu, &instruction, &arg1, &arg2);
		printf("Executing instruction: %s [%0x: %0x] (%0X, %0X)\n", instruction.opcode, cpu->registers->pc, cpu->memory[cpu->registers->pc], cpu->memory[cpu->registers->pc + 1], cpu->memory[cpu->registers->pc + 2]);

		if(instruction.function == NULL){
			printf("[ERR]: Unimplemented instruction.\n");
			status = ERR;
		}else{
			status = instruction.function(cpu, arg1, arg2);
		}
		cpu->registers->pc ++;
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
	printf("SP: %0x\n", registers->sp);
	printf("PC: %0x\n", registers->pc);
	printf("FLAG: Z: %x, S: %x, HC: %x, C: %x\n", registers->flag_zero, registers->flag_sub, registers->flag_halfcarry, registers->flag_carry);
	printf("== End Registers ==\n");
}

void pushStack(struct cpu_cpu *cpu, unsigned char value){
	cpu->registers->sp --;
	cpu->memory[cpu->registers->sp] = value;
}

unsigned char popStack(struct cpu_cpu *cpu){
	unsigned char value = cpu->memory[cpu->registers->sp];
	cpu->registers->sp ++;
	return value;
}
