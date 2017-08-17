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
};

struct cpu_cpu{
	struct cpu_registers* registers;
};

struct cpu_cpu* createCPU();
void destroyCPU(struct cpu_cpu* cpu);

int cpu_execute();
int cpu_decode();
int cpu_fetch();
void cpu_run(struct cpu_cpu cpu);

void printRegisters(struct cpu_registers* registers);

#endif
