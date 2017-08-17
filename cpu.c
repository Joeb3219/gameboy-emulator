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

// Decrement H
Status fn_dec_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->h;
	cpu->registers->h -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement A
Status fn_dec_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->a;
	cpu->registers->a -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement B
Status fn_dec_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->b;
	cpu->registers->b -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement C
Status fn_dec_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->c;
	cpu->registers->c -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement D
Status fn_dec_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->d;
	cpu->registers->d -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement E
Status fn_dec_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->e;
	cpu->registers->e -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// Decrement L
Status fn_dec_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned char val = cpu->registers->l;
	cpu->registers->l -= 1;

	cpu->registers->flag_zero = (val - 1 == 0);
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(val, -1, 3);
	return OK;
}

// A -> (HL), then icrement HL
Status fn_ldi_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->a;
	cpu->registers->hl += 1;
	return OK;
}

// A -> (HL), then icrement HL
Status fn_ld_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	fn_ldi_hl_a(cpu, arg1, arg2);
	return OK;
}

// A -> (HL), then icrement HL
Status fn_ld_hli_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	fn_ldi_hl_a(cpu, arg1, arg2);
	return OK;
}

// HL + BC -> HL.
Status fn_add_hl_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->flag_sub = 0;
	cpu->registers->flag_halfcarry = getCarry(cpu->registers->hl, cpu->registers->bc, 11);
	cpu->registers->flag_carry = (cpu->registers->hl + cpu->registers->bc) > 0xFFFF;
	cpu->registers->hl += cpu->registers->bc;
	return OK;
}

// HL + DE -> HL.
Status fn_add_hl_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->flag_sub = 0;
	cpu->registers->flag_halfcarry = getCarry(cpu->registers->hl, cpu->registers->de, 11);
	cpu->registers->flag_carry = (cpu->registers->hl + cpu->registers->de) > 0xFFFF;
	cpu->registers->hl += cpu->registers->de;
	return OK;
}

// HL + HL -> HL.
Status fn_add_hl_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->flag_sub = 0;
	cpu->registers->flag_halfcarry = getCarry(cpu->registers->hl, cpu->registers->hl, 11);
	cpu->registers->flag_carry = (cpu->registers->hl + cpu->registers->hl) > 0xFFFF;
	cpu->registers->hl += cpu->registers->hl;
	return OK;
}

// HL + SP -> HL.
Status fn_add_hl_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->flag_sub = 0;
	cpu->registers->flag_halfcarry = getCarry(cpu->registers->hl, cpu->registers->sp, 11);
	cpu->registers->flag_carry = (cpu->registers->hl + cpu->registers->sp) > 0xFFFF;
	cpu->registers->hl += cpu->registers->sp;
	return OK;
}

// n -> A
Status fn_ld_a_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = arg1;
	return OK;
}

// n -> B
Status fn_ld_b_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = arg1;
	return OK;
}

// n -> C
Status fn_ld_c_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = arg1;
	return OK;
}

// n -> D
Status fn_ld_d_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = arg1;
	return OK;
}

// n -> E
Status fn_ld_e_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = arg1;
	return OK;
}

// n -> H
Status fn_ld_h_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = arg1;
	return OK;
}

// n -> l
Status fn_ld_l_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = arg1;
	return OK;
}

// Increment A
Status fn_inc_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->a += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment B
Status fn_inc_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->b += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment C
Status fn_inc_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->c += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment D
Status fn_inc_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->d += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment E
Status fn_inc_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->e += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment H
Status fn_inc_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->h += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Increment L
Status fn_inc_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (cpu->registers->l += 1);
	cpu->registers->flag_zero = (val == 0);
	cpu->registers->flag_halfcarry = getCarry(val - 1, 1, 3);
	cpu->registers->flag_zero = 0;
	return OK;
}

// Rotate A right through carry
Status fn_rra(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	int newCarryFlag = (cpu->registers->a & 0x1) != 0;
	cpu->registers->a = (cpu->registers->a >> 1) | (cpu->registers->flag_carry << 7);
	cpu->registers->flag_carry = newCarryFlag;
	cpu->registers->flag_zero = cpu->registers->flag_halfcarry = cpu->registers->flag_sub = 0;
	return OK;
}

// Loads nn -> BC
Status fn_ld_bc_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (arg1 << 8) | arg2;
	cpu->registers->bc = val;
	return OK;
}

// Loads nn -> DE
Status fn_ld_de_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (arg1 << 8) | arg2;
	cpu->registers->de = val;
	return OK;
}

// Loads nn -> HL
Status fn_ld_hl_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (arg1 << 8) | arg2;
	cpu->registers->hl = val;
	return OK;
}

// Loads nn -> SP
Status fn_ld_sp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = (arg1 << 8) | arg2;
	cpu->registers->sp = val;
	return OK;
}

// Loads A -> (DE)
Status fn_ld_de_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->de] = cpu->registers->a;
	return OK;
}

// Loads A -> (BC)
Status fn_ld_bc_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->bc] = cpu->registers->a;
	return OK;
}

Status fn_ld_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->a;
	return OK;
}
	
Status fn_ld_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->b;
	return OK;
}
	
Status fn_ld_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->c;
	return OK;
}
	
Status fn_ld_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->d;
	return OK;
}
	
Status fn_ld_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->e;
	return OK;
}
	
Status fn_ld_a_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->f;
	return OK;
}
	
Status fn_ld_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->h;
	return OK;
}
	
Status fn_ld_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->registers->l;
	return OK;
}
	
Status fn_ld_b_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->a;
	return OK;
}
	
Status fn_ld_b_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->b;
	return OK;
}
	
Status fn_ld_b_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->c;
	return OK;
}
	
Status fn_ld_b_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->d;
	return OK;
}
	
Status fn_ld_b_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->e;
	return OK;
}
	
Status fn_ld_b_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->h;
	return OK;
}
	
Status fn_ld_b_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->f;
	return OK;
}
	
Status fn_ld_b_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->registers->l;
	return OK;
}
	
Status fn_ld_c_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->a;
	return OK;
}
	
Status fn_ld_c_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->b;
	return OK;
}
	
Status fn_ld_c_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->c;
	return OK;
}
	
Status fn_ld_c_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->d;
	return OK;
}
	
Status fn_ld_c_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->e;
	return OK;
}
	
Status fn_ld_c_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->h;
	return OK;
}
	
Status fn_ld_c_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->f;
	return OK;
}
	
Status fn_ld_c_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->registers->l;
	return OK;
}
	
Status fn_ld_d_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->a;
	return OK;
}
	
Status fn_ld_d_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->b;
	return OK;
}
	
Status fn_ld_d_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->c;
	return OK;
}
	
Status fn_ld_d_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->d;
	return OK;
}
	
Status fn_ld_d_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->e;
	return OK;
}
	
Status fn_ld_d_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->f;
	return OK;
}
	
Status fn_ld_d_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->h;
	return OK;
}
	
Status fn_ld_d_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->registers->l;
	return OK;
}
	
Status fn_ld_e_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->a;
	return OK;
}
	
Status fn_ld_e_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->b;
	return OK;
}
	
Status fn_ld_e_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->c;
	return OK;
}
	
Status fn_ld_e_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->d;
	return OK;
}
	
Status fn_ld_e_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->e;
	return OK;
}
	
Status fn_ld_e_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->f;
	return OK;
}
	
Status fn_ld_e_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->h;
	return OK;
}
	
Status fn_ld_e_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->registers->l;
	return OK;
}
	
Status fn_ld_f_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->a;
	return OK;
}
	
Status fn_ld_f_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->b;
	return OK;
}
	
Status fn_ld_f_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->c;
	return OK;
}
	
Status fn_ld_f_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->d;
	return OK;
}
	
Status fn_ld_f_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->e;
	return OK;
}
	
Status fn_ld_f_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->f;
	return OK;
}
	
Status fn_ld_f_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->h;
	return OK;
}
	
Status fn_ld_f_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->f = cpu->registers->l;
	return OK;
}
	
Status fn_ld_h_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->a;
	return OK;
}
	
Status fn_ld_h_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->b;
	return OK;
}
	
Status fn_ld_h_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->c;
	return OK;
}
	
Status fn_ld_h_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->d;
	return OK;
}
	
Status fn_ld_h_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->e;
	return OK;
}
	
Status fn_ld_h_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->f;
	return OK;
}
	
Status fn_ld_h_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->h;
	return OK;
}
	
Status fn_ld_h_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->registers->l;
	return OK;
}
	
Status fn_ld_l_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->a;
	return OK;
}
	
Status fn_ld_l_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->b;
	return OK;
}
	
Status fn_ld_l_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->c;
	return OK;
}
	
Status fn_ld_l_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->d;
	return OK;
}
	
Status fn_ld_l_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->e;
	return OK;
}
	
Status fn_ld_l_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->f;
	return OK;
}
	
Status fn_ld_l_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->h;
	return OK;
}
	
Status fn_ld_l_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->registers->l;
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

// Borrowed from: http://robdor.com/2016/08/10/gameboy-emulator-half-carry-flag/
int getCarry(unsigned short a, unsigned short b, int bit){
	if(bit == 3) return (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10;	// 0xf = 0x1 << 3 (filling 1s); 0x10 = 0x1 << 4.
	if(bit == 11) return (((a & 0xf) + (b & 0xf)) & 0x10) > 0xf;
	return (a + b) > 0xFFFF;
}
