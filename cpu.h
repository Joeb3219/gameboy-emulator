#ifndef CPU_H_

#define CPU_H_

typedef enum status{
	OK, HLT, ERR
} Status;

struct cpu_instruction{
	char *opcode;
	int numArgs;
	void (*function);
};

static const struct cpu_instruction instructions[256] = {
	{"NOP", 0, NULL},
	{"LD BC,nn", 2, NULL},
	{"LD (BC),A", 0, NULL},
	{"INC BC", 0, NULL},
	{"INC B", 0, NULL},
	{"DEC B", 0, NULL},
	{"LD B,n", 1, NULL},
	{"RLC A", 0, NULL},
	{"LD (nn),SP", 22, NULL},
	{"ADD HL,BC", 0, NULL},
	{"LD A,(BC)", 0, NULL},
	{"DEC BC", 0, NULL},
	{"INC C", 0, NULL},
	{"DEC C", 0, NULL},
	{"LD C,n", 1, NULL},
	{"RRC A", 0, NULL},
	{"STOP", 0, NULL},
	{"LD DE,nn", 2, NULL},
	{"LD (DE),A", 0, NULL},
	{"INC DE", 0, NULL},
	{"INC D", 0, NULL},
	{"DEC D", 0, NULL},
	{"LD D,n", 1, NULL},
	{"RL A", 0, NULL},
	{"JR n", 1, NULL},
	{"ADD HL,DE", 0, NULL},
	{"LD A,(DE)", 0, NULL},
	{"DEC DE", 0, NULL},
	{"INC E", 0, NULL},
	{"DEC E", 0, NULL},
	{"LD E,n", 1, NULL},
	{"RR A", 0, NULL},
	{"JR NZ,n", 1, NULL},
	{"LD HL,nn", 2, NULL},
	{"LDI (HL),A", 0, NULL},
	{"INC HL", 0, NULL},
	{"INC H", 0, NULL},
	{"DEC H", 0, NULL},
	{"LD H,n", 1, NULL},
	{"DAA", 0, NULL},
	{"JR Z,n", 1, NULL},
	{"ADD HL,HL", 0, NULL},
	{"LDI A,(HL)", 0, NULL},
	{"DEC HL", 0, NULL},
	{"INC L", 0, NULL},
	{"DEC L", 0, NULL},
	{"LD L,n", 1, NULL},
	{"CPL", 0, NULL},
	{"JR NC,n", 1, NULL},
	{"LD SP,nn", 2, NULL},
	{"LDD (HL),A", 0, NULL},
	{"INC SP", 0, NULL},
	{"INC (HL)", 0, NULL},
	{"DEC (HL)", 0, NULL},
	{"LD (HL),n", 1, NULL},
	{"SCF", 0, NULL},
	{"JR C,n", 1, NULL},
	{"ADD HL,SP", 0, NULL},
	{"LDD A,(HL)", 0, NULL},
	{"DEC SP", 0, NULL},
	{"INC A", 0, NULL},
	{"DEC A", 0, NULL},
	{"LD A,n", 0, NULL},
	{"CCF", 0, NULL},
	{"LD B,C", 0, NULL},
	{"LD B,B", 0, NULL},
	{"LD B,D", 0, NULL},
	{"LD B,E", 0, NULL},
	{"LD B,H", 0, NULL},
	{"LD B,L", 0, NULL},
	{"LD B,(HL)", 0, NULL},
	{"LD B,A", 0, NULL},
	{"LD C,B", 0, NULL},
	{"LD C,C", 0, NULL},
	{"LD C,D", 0, NULL},
	{"LD C,E", 0, NULL},
	{"LD C,H", 0, NULL},
	{"LD C,L", 0, NULL},
	{"LD C,(HL)", 0, NULL},
	{"LD C,A", 0, NULL},
	{"LD D,B", 0, NULL},
	{"LD D,C", 0, NULL},
	{"LD D,D", 0, NULL},
	{"LD D,E", 0, NULL},
	{"LD D,H", 0, NULL},
	{"LD D,L", 0, NULL},
	{"LD D,(HL)", 0, NULL},
	{"LD D,A", 0, NULL},
	{"LD E,B", 0, NULL},
	{"LD E,C", 0, NULL},
	{"LD E,D", 0, NULL},
	{"LD E,E", 0, NULL},
	{"LD E,H", 0, NULL},
	{"LD E,L", 0, NULL},
	{"LD E,(HL)", 0, NULL},
	{"LD E,A", 0, NULL},
	{"LD H,B", 0, NULL},
	{"LD H,C", 0, NULL},
	{"LD H,D", 0, NULL},
	{"LD H,E", 0, NULL},
	{"LD H,H", 0, NULL},
	{"LD H,L", 0, NULL},
	{"LD H,(HL)", 0, NULL},
	{"LD H,A", 0, NULL},
	{"LD L,B", 0, NULL},
	{"LD L,C", 0, NULL},
	{"LD L,D", 0, NULL},
	{"LD L,E", 0, NULL},
	{"LD L,H", 0, NULL},
	{"LD L,L", 0, NULL},
	{"LD L,(HL)", 0, NULL},
	{"LD L,A", 0, NULL},
	{"LD (HL),B", 0, NULL},
	{"LD (HL),C", 0, NULL},
	{"LD (HL),D", 0, NULL},
	{"LD (HL),E", 0, NULL},
	{"LD (HL),H", 0, NULL},
	{"LD (HL),L", 0, NULL},
	{"HALT", 0, NULL},
	{"LD (HL),A", 0, NULL},
	{"LD A,B", 0, NULL},
	{"LD A,C", 0, NULL},
	{"LD A,D", 0, NULL},
	{"LD A,E", 0, NULL},
	{"LD A,H", 0, NULL},
	{"LD A,L", 0, NULL},
	{"LD A,(HL)", 0, NULL},
	{"LD A,A", 0, NULL},
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
	{"JP nn", 2, NULL},
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
	unsigned short flag_zero;
	unsigned short flag_sub;
	unsigned short flag_halfcarry;
	unsigned short flag_carry;
};

struct cpu_cpu{
	struct cpu_registers* registers;
	unsigned char *memory;
};

struct cpu_cpu* createCPU();
void destroyCPU(struct cpu_cpu* cpu);

Status cpu_execute();
int cpu_decode();
int cpu_fetch();
void cpu_run(struct cpu_cpu *cpu);

void printRegisters(struct cpu_registers* registers);

void pushStack(struct cpu_cpu *cpu, unsigned char value);
unsigned char popStack(struct cpu_cpu *cpu);

#endif
