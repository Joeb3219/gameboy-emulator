#ifndef CPU_H_

#define CPU_H_

struct cpu_registers{
	union{
		struct{
			unsigned char l;
			unsigned char h;
		};
		unsigned short hl;
	};
	union{
		struct{
			unsigned char c;
			unsigned char b;
		};
		unsigned short bc;
	};
	union{
		struct{
			unsigned char e;
			unsigned char d;
		};
		unsigned short de;
	};
	union{
		struct{
			unsigned char f;
			unsigned char a;
		};
		unsigned short af;
	};
	unsigned short pc;
	unsigned short sp;
	unsigned short flag_zero; // Z
	unsigned short flag_sub;  // N
	unsigned short flag_halfcarry; // H
	unsigned short flag_carry; // C
};

struct cpu_cpu{
	struct cpu_registers* registers;
	unsigned char *memory;
};

typedef enum status{
	OK, HLT, ERR
} Status;

struct cpu_instruction{
	char *opcode;
	int numArgs;
	Status (*function)(struct cpu_cpu *cpu, unsigned char, unsigned char);
};

Status fn_nop(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cpl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_dec_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldi_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hli_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_add_hl_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_add_hl_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_add_hl_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_add_hl_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_f_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_f(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);

static const struct cpu_instruction instructions[256] = {
	{"NOP", 0, fn_nop},
	{"LD BC,nn", 2, NULL},
	{"LD (BC),A", 0, NULL},
	{"INC BC", 0, NULL},
	{"INC B", 0, NULL},
	{"DEC B", 0, fn_dec_b},
	{"LD B,n", 1, fn_ld_b_n},
	{"RLC A", 0, NULL},
	{"LD (nn),SP", 2, NULL},
	{"ADD HL,BC", 0, fn_add_hl_bc},
	{"LD A,(BC)", 0, NULL},
	{"DEC BC", 0, fn_dec_bc},
	{"INC C", 0, NULL},
	{"DEC C", 0, fn_dec_c},
	{"LD C,n", 1, fn_ld_c_n},
	{"RRC A", 0, NULL},
	{"STOP", 0, NULL},
	{"LD DE,nn", 2, NULL},
	{"LD (DE),A", 0, NULL},
	{"INC DE", 0, NULL},
	{"INC D", 0, NULL},
	{"DEC D", 0, fn_dec_d},
	{"LD D,n", 1, fn_ld_d_n},
	{"RL A", 0, NULL},
	{"JR n", 1, NULL},
	{"ADD HL,DE", 0, fn_add_hl_de},
	{"LD A,(DE)", 0, NULL},
	{"DEC DE", 0, fn_dec_bc},
	{"INC E", 0, NULL},
	{"DEC E", 0, fn_dec_e},
	{"LD E,n", 1, fn_ld_e_n},
	{"RR A", 0, NULL},
	{"JR NZ,n", 1, NULL},
	{"LD HL,nn", 2, NULL},
	{"LDI (HL),A", 0, fn_ldi_hl_a},
	{"INC HL", 0, NULL},
	{"INC H", 0, NULL},
	{"DEC H", 0, fn_dec_h},
	{"LD H,n", 1, fn_ld_h_n},
	{"DAA", 0, NULL},
	{"JR Z,n", 1, NULL},
	{"ADD HL,HL", 0, fn_add_hl_hl},
	{"LDI A,(HL)", 0, NULL},
	{"DEC HL", 0, fn_dec_hl},
	{"INC L", 0, NULL},
	{"DEC L", 0, fn_dec_l},
	{"LD L,n", 1, fn_ld_l_n},
	{"CPL", 0, fn_cpl},
	{"JR NC,n", 1, NULL},
	{"LD SP,nn", 2, NULL},
	{"LDD (HL),A", 0, NULL},
	{"INC SP", 0, NULL},
	{"INC (HL)", 0, NULL},
	{"DEC (HL)", 0, NULL},
	{"LD (HL),n", 1, NULL},
	{"SCF", 0, NULL},
	{"JR C,n", 1, NULL},
	{"ADD HL,SP", 0, fn_add_hl_sp},
	{"LDD A,(HL)", 0, NULL},
	{"DEC SP", 0, fn_dec_sp},
	{"INC A", 0, NULL},
	{"DEC A", 0, fn_dec_a},
	{"LD A,n", 0, fn_ld_a_n},
	{"CCF", 0, NULL},
	{"LD B,C", 0, fn_ld_b_c},
	{"LD B,B", 0, fn_ld_b_b},
	{"LD B,D", 0, fn_ld_b_d},
	{"LD B,E", 0, fn_ld_b_e},
	{"LD B,H", 0, fn_ld_b_h},
	{"LD B,L", 0, fn_ld_b_l},
	{"LD B,(HL)", 0, NULL},
	{"LD B,A", 0, NULL},
	{"LD C,B", 0, fn_ld_c_b},
	{"LD C,C", 0, fn_ld_c_c},
	{"LD C,D", 0, fn_ld_c_d},
	{"LD C,E", 0, fn_ld_c_e},
	{"LD C,H", 0, fn_ld_c_h},
	{"LD C,L", 0, fn_ld_c_l},
	{"LD C,(HL)", 0, NULL},
	{"LD C,A", 0, NULL},
	{"LD D,B", 0, fn_ld_d_b},
	{"LD D,C", 0, fn_ld_d_c},
	{"LD D,D", 0, fn_ld_d_d},
	{"LD D,E", 0, fn_ld_d_e},
	{"LD D,H", 0, fn_ld_d_h},
	{"LD D,L", 0, fn_ld_d_l},
	{"LD D,(HL)", 0, NULL},
	{"LD D,A", 0, fn_ld_d_a},
	{"LD E,B", 0, fn_ld_e_b},
	{"LD E,C", 0, fn_ld_e_c},
	{"LD E,D", 0, fn_ld_e_d},
	{"LD E,E", 0, fn_ld_e_e},
	{"LD E,H", 0, fn_ld_e_h},
	{"LD E,L", 0, fn_ld_e_l},
	{"LD E,(HL)", 0, NULL},
	{"LD E,A", 0, fn_ld_e_a},
	{"LD H,B", 0, fn_ld_h_b},
	{"LD H,C", 0, fn_ld_h_c},
	{"LD H,D", 0, fn_ld_h_d},
	{"LD H,E", 0, fn_ld_h_e},
	{"LD H,H", 0, fn_ld_h_h},
	{"LD H,L", 0, fn_ld_h_l},
	{"LD H,(HL)", 0, NULL},
	{"LD H,A", 0, fn_ld_h_a},
	{"LD L,B", 0, fn_ld_l_b},
	{"LD L,C", 0, fn_ld_l_c},
	{"LD L,D", 0, fn_ld_l_d},
	{"LD L,E", 0, fn_ld_l_e},
	{"LD L,H", 0, fn_ld_l_h},
	{"LD L,L", 0, fn_ld_l_l},
	{"LD L,(HL)", 0, NULL},
	{"LD L,A", 0, fn_ld_l_a},
	{"LD (HL),B", 0, NULL},
	{"LD (HL),C", 0, NULL},
	{"LD (HL),D", 0, NULL},
	{"LD (HL),E", 0, NULL},
	{"LD (HL),H", 0, NULL},
	{"LD (HL),L", 0, NULL},
	{"HALT", 0, NULL},
	{"LD (HL),A", 0, fn_ld_hl_a},
	{"LD A,B", 0, fn_ld_a_b},
	{"LD A,C", 0, fn_ld_a_c},
	{"LD A,D", 0, fn_ld_a_d},
	{"LD A,E", 0, fn_ld_a_e},
	{"LD A,H", 0, fn_ld_a_h},
	{"LD A,L", 0, fn_ld_a_l},
	{"LD A,(HL)", 0, NULL},
	{"LD A,A", 0, fn_ld_a_a},
	{"ADD A,B", 0, NULL},
	{"ADD A,C", 0, NULL},
	{"ADD A,D", 0, NULL},
	{"ADD A,E", 0, NULL},
	{"ADD A,H", 0, NULL},
	{"ADD A,L", 0, NULL},
	{"ADD A,(HL)", 0, NULL},
	{"ADD A,A", 0, NULL},
	{"ADC A,B", 0, NULL},
	{"ADC A,C", 0, NULL},
	{"ADC A,D", 0, NULL},
	{"ADC A,E", 0, NULL},
	{"ADC A,H", 0, NULL},
	{"ADC A,L", 0, NULL},
	{"ADC A,(HL)", 0, NULL},
	{"ADC A,A", 0, NULL},
	{"SUB A,B", 0, NULL},
	{"SUB A,C", 0, NULL},
	{"SUB A,D", 0, NULL},
	{"SUB A,E", 0, NULL},
	{"SUB A,H", 0, NULL},
	{"SUB A,L", 0, NULL},
	{"SUB A,(HL)", 0, NULL},
	{"SUB A,A", 0, NULL},
	{"SBC A,B", 0, NULL},
	{"SBC A,C", 0, NULL},
	{"SBC A,D", 0, NULL},
	{"SBC A,E", 0, NULL},
	{"SBC A,H", 0, NULL},
	{"SBC A,L", 0, NULL},
	{"SBC A,(HL)", 0, NULL},
	{"SBC A,A", 0, NULL},
	{"AND B", 0, NULL},
	{"AND C", 0, NULL},
	{"AND D", 0, NULL},
	{"AND E", 0, NULL},
	{"AND H", 0, NULL},
	{"AND L", 0, NULL},
	{"AND (HL)", 0, NULL},
	{"AND A", 0, NULL},
	{"XOR B", 0, NULL},
	{"XOR C", 0, NULL},
	{"XOR D", 0, NULL},
	{"XOR E", 0, NULL},
	{"XOR H", 0, NULL},
	{"XOR L", 0, NULL},
	{"XOR (HL)", 0, NULL},
	{"XOR A", 0, NULL},
	{"OR B", 0, NULL},
	{"OR C", 0, NULL},
	{"OR D", 0, NULL},
	{"OR E", 0, NULL},
	{"OR H", 0, NULL},
	{"OR L", 0, NULL},
	{"OR (HL)", 0, NULL},
	{"OR A", 0, NULL},
	{"CP B", 0, NULL},
	{"CP C", 0, NULL},
	{"CP D", 0, NULL},
	{"CP E", 0, NULL},
	{"CP H", 0, NULL},
	{"CP L", 0, NULL},
	{"CP (HL)", 0, NULL},
	{"CP A", 0, NULL},
	{"RET NZ", 0, NULL},
	{"POP BC", 0, NULL},
	{"JP NZ,nn", 2, NULL},
	{"JP nn", 2, fn_jp_nn},
	{"CALL NZ,nn", 2, NULL},
	{"PUSH BC", 0, NULL},
	{"ADD A,n", 1, NULL},
	{"RST 0", 0, NULL},
	{"RET Z", 0, NULL},
	{"RET", 0, NULL},
	{"JP Z,nn", 2, NULL},
	{"Ext ops", 0, NULL},
	{"CALL Z,nn", 2, NULL},
	{"CALL nn", 2, NULL},
	{"ADC A,n", 1, NULL},
	{"RST 8", 0, NULL},
	{"RET NC", 0, NULL},
	{"POP DE", 0, NULL},
	{"JP NC,nn", 2, NULL},
	{"XX", 0, NULL},
	{"CALL NC,nn", 2, NULL},
	{"PUSH DE", 0, NULL},
	{"SUB A,n", 1, NULL},
	{"RST 10", 0, NULL},
	{"RET C", 0, NULL},
	{"RETI", 0, NULL},
	{"JP C,nn", 2, NULL},
	{"XX", 0, NULL},
	{"CALL C,nn", 2, NULL},
	{"XX", 0, NULL},
	{"SBC A,n", 1, NULL},
	{"RST 18", 0, NULL},
	{"LDH (n),A", 1, NULL},
	{"POP HL", 0, NULL},
	{"LDH (C),A", 0, NULL},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"PUSH HL", 0, NULL},
	{"AND n", 1, NULL},
	{"RST 20", 0, NULL},
	{"ADD SP,d", 0, NULL},
	{"JP (HL)", 0, NULL},
	{"LD (nn),A", 2, NULL},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"XOR n", 1, NULL},
	{"RST 28", 0, NULL},
	{"LDH A,(n)", 1, NULL},
	{"POP AF", 0, NULL},
	{"XX", 0, NULL},
	{"DI", 0, NULL},
	{"XX", 0, NULL},
	{"PUSH AF", 0, NULL},
	{"OR n", 1, NULL},
	{"RST 30", 0, NULL},
	{"LDHL SP,d", 0, NULL},
	{"LD SP,HL", 0, NULL},
	{"LD A,(nn)", 2, NULL},
	{"EI", 0, NULL},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"CP n", 1, NULL},
	{"RST 38", 0, NULL}
};

struct cpu_cpu* createCPU();
void destroyCPU(struct cpu_cpu* cpu);

Status cpu_execute();
void cpu_decode(struct cpu_cpu *cpu, struct cpu_instruction *instruction, unsigned char *arg1, unsigned char *arg2);
void cpu_run(struct cpu_cpu *cpu);

void printRegisters(struct cpu_registers* registers);

void pushStack(struct cpu_cpu *cpu, unsigned char value);
unsigned char popStack(struct cpu_cpu *cpu);

int getCarry(unsigned short a, unsigned short b, int bit);

#endif
