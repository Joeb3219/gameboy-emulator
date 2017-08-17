#ifndef CPU_H_

#define CPU_H_

struct cpu_instruction{
	char *opcode;
	int numArgs;
	void (*function);
};

static const struct cpu_instruction instructions[0xFF] = {
	{"nop", 0, NULL}
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

int cpu_execute();
int cpu_decode();
int cpu_fetch();
void cpu_run(struct cpu_cpu *cpu);

void printRegisters(struct cpu_registers* registers);

void pushStack(struct cpu_cpu *cpu, unsigned char value);
unsigned char popStack(struct cpu_cpu *cpu);

#endif
