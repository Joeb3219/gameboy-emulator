#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

unsigned short mergeBytesToShort(unsigned char a, unsigned char b){
	return (((unsigned short) b) << 8) | a;
}

// No operation
Status fn_nop(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	return OK;
}

// Absolute jump
Status fn_jp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short address = mergeBytesToShort(arg1, arg2);
	address -= 3; // Avoid increment that occurs after instruction execute
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
	cpu->registers->b = cpu->registers->b - 1;

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
	unsigned short val = mergeBytesToShort(arg2, arg1);
	cpu->registers->bc = val;
	return OK;
}

// Loads nn -> DE
Status fn_ld_de_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = mergeBytesToShort(arg1, arg2);
	cpu->registers->de = val;
	return OK;
}

// Loads nn -> HL
Status fn_ld_hl_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = mergeBytesToShort(arg1, arg2);
	cpu->registers->hl = val;
	return OK;
}

// Loads nn -> SP
Status fn_ld_sp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short val = mergeBytesToShort(arg1, arg2);
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

// Loads (HL) -> A
Status fn_ld_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> B
Status fn_ld_b_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->b = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> C
Status fn_ld_c_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->c = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> D
Status fn_ld_d_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->d = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> E
Status fn_ld_e_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->e = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> H
Status fn_ld_h_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->h = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads (HL) -> L
Status fn_ld_l_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->l = cpu->memory[cpu->registers->hl];
	return OK;
}

// Loads A -> (HL)
Status fn_ld_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->a;
	return OK;
}

// Loads B -> (HL)
Status fn_ld_hl_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->b;
	return OK;
}

// Loads C -> (HL)
Status fn_ld_hl_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->c;
	return OK;
}

// Loads D -> (HL)
Status fn_ld_hl_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->d;
	return OK;
}

// Loads E -> (HL)
Status fn_ld_hl_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->e;
	return OK;
}

// Loads H -> (HL)
Status fn_ld_hl_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->h;
	return OK;
}

// Loads L -> (HL)
Status fn_ld_hl_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->l;
	return OK;
}

// STOP! Wait for an input of some sort.
Status fn_stop(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	return STOP;
}

// Generic subtract method for bytes
void subtract(struct cpu_cpu *cpu, unsigned char *destination, unsigned char b){
	unsigned char a = *destination;
	cpu->registers->flag_zero = (a - b) == 0;
	cpu->registers->flag_sub = 1;
	cpu->registers->flag_halfcarry = getCarry(a, -1 * b, 4);
	cpu->registers->flag_carry = (b > a);
	(*destination) = a - b;
}

// Subtract A - A -> A
Status fn_sub_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->a);
	return OK;
}

// Subtract A - B -> A
Status fn_sub_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->b);
	return OK;
}

// Subtract A - C -> A
Status fn_sub_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->c);
	return OK;
}

// Subtract A - D -> A
Status fn_sub_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->d);
	return OK;
}

// Subtract A - E -> A
Status fn_sub_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->e);
	return OK;
}

// Subtract A - H -> A
Status fn_sub_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->h);
	return OK;
}

// Subtract A - L -> A
Status fn_sub_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->l);
	return OK;
}

// Subtract A - (HL) -> A
Status fn_sub_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->memory[cpu->registers->hl]);
	return OK;
}

// Subtract (+ 1 if carry from previous), A - A -> A
Status fn_sbc_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->a + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - B -> A
Status fn_sbc_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->b + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - C -> A
Status fn_sbc_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->c + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - D -> A
Status fn_sbc_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->d + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - H -> A
Status fn_sbc_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->h + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - E -> A
Status fn_sbc_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->e + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - L -> A
Status fn_sbc_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->registers->l + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Subtract (+ 1 if carry from previous), A - (HL) -> A
Status fn_sbc_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	subtract(cpu, &cpu->registers->a, cpu->memory[cpu->registers->hl] + (cpu->registers->flag_carry ? 1 : 0));
	return OK;
}

// Add n to current address pointer and jump to it (jump relative)
Status fn_jr_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->pc += (signed char) arg1 - 2; // Subtract two so that we will be at the correct address
	return OK;
}

// Increments BC by one
Status fn_inc_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->bc += 1;
	return OK;
}

// Increments DE by one
Status fn_inc_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->de += 1;
	return OK;
}

// Increments HL by one
Status fn_inc_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->hl += 1;
	return OK;
}

// Increments SP by one
Status fn_inc_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->sp += 1;
	return OK;
}

// Calls a function by pushing the next addy to the stack and jumping to nn
Status fn_call_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	unsigned short address = mergeBytesToShort(arg1, arg2);
	pushStack(cpu, cpu->registers->pc + 1);
	cpu->registers->pc = address - 3; // Subtract 3 so we don't move an extra instruction ahead.
	return OK;
}

// A generic XOR method for two bytes
void xor(struct cpu_cpu *cpu, unsigned char *destination, unsigned char b){
	(*destination) = (*destination) ^ b;
	cpu->registers->flag_zero = (*destination) == 0;
	cpu->registers->flag_carry = cpu->registers->flag_sub = cpu->registers->flag_halfcarry = 0;
}

// A XOR A -> A
Status fn_xor_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->a);
	return OK;
}

// A XOR B -> A
Status fn_xor_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->b);
	return OK;
}

// A XOR C -> A
Status fn_xor_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->c);
	return OK;
}

// A XOR D -> A
Status fn_xor_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->d);
	return OK;
}

// A XOR E -> A
Status fn_xor_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->e);
	return OK;
}

// A XOR H -> A
Status fn_xor_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->h);
	return OK;
}

// A XOR L -> A
Status fn_xor_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->registers->l);
	return OK;
}

// A XOR (HL) -> A
Status fn_xor_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	xor(cpu, &cpu->registers->a, cpu->memory[cpu->registers->hl]);
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_00h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x00 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_08h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x08 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_10h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x10 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_18h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x18 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_20h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x20 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_28h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x28 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_30h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x30 - 1;
	return OK;
}

// Pushes current addy to stack and does a reset jump
Status fn_rst_38h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	pushStack(cpu, cpu->registers->pc);
	cpu->registers->pc = 0x0000 + 0x38 - 1;
	return OK;
}

// A -> (HL), HL --.
Status fn_ldd_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->memory[cpu->registers->hl] = cpu->registers->a;
	cpu->registers->hl -= 1;
	return OK;
}

// (HL) -> A, HL --.
Status fn_ldd_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->memory[cpu->registers->hl];
	cpu->registers->hl -= 1;
	return OK;
}

// (HL) -> A, HL --.
Status fn_ld_a_hlminus(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->memory[cpu->registers->hl];
	cpu->registers->hl -= 1;
	return OK;
}

// (HL) -> A, HL --.
Status fn_ld_a_hld(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	cpu->registers->a = cpu->memory[cpu->registers->hl];
	cpu->registers->hl -= 1;
	return OK;
}

// IF zero flag isn't set, jump relative
Status fn_jr_nz_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	if(!cpu->registers->flag_zero) cpu->registers->pc += ((signed char) arg1);
	return OK;
}

// IF zero flag is set, jump relative
Status fn_jr_z_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	if(cpu->registers->flag_zero) cpu->registers->pc += ((signed char) arg1);
	return OK;
}

// IF carry flag isn't set, jump relative
Status fn_jr_nc_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	if(!cpu->registers->flag_carry) cpu->registers->pc += ((signed char) arg1);
	return OK;
}

// IF carry flag is set, jump relative
Status fn_jr_c_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2){
	if(!cpu->registers->flag_carry) cpu->registers->pc += ((signed char) arg1);
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

void printMemory(struct cpu_cpu *cpu, unsigned short start, unsigned short end){
	printf("MEMORY DUMP:\n");
	for(start; start <= end; start ++){
		printf("[%0X]: %0X\n", start, cpu->memory[start]);
	}
	printf("END MEM DUMP\n");
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

        while(status == OK || status == STOP){
		if(status == STOP){
			printf("Waiting for input\n");
			status = OK; // TODO: actually implement a button must be pressed.
			continue;
		}
                cpu_decode(cpu, &instruction, &arg1, &arg2);
		printf("Executing instruction: %s [%0x: %0x] (%0X, %0X)\n", instruction.opcode, cpu->registers->pc, cpu->memory[cpu->registers->pc], cpu->memory[cpu->registers->pc + 1], cpu->memory[cpu->registers->pc + 2]);
		if(cpu->registers->pc == 0x38) break;

		if(instruction.function == NULL){
			printf("[ERR]: Unimplemented instruction.\n");
			status = ERR;
		}else{
			status = instruction.function(cpu, arg1, arg2);
		}
		cpu->registers->pc += 1 + instruction.numArgs;
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
	if(bit == 3 || 4) return (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10;	// 0xf = 0x1 << 3 (filling 1s); 0x10 = 0x1 << 4.
	if(bit == 11) return (((a & 0xf) + (b & 0xf)) & 0x10) > 0xf;
	return (a + b) > 0xFFFF;
}
