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
	unsigned short interrupts;
	unsigned short interrupts_enabled;
	unsigned short interruptDelayTicks;
};

struct cpu_cpu{
	struct cpu_registers* registers;
	unsigned char *memory;
};

typedef enum status{
	OK, HLT, ERR, STOP
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
Status fn_inc_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rra(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_bc_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_de_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_sp_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_bc_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_de_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_stop(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_b_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_c_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_d_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_e_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_h_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_l_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sub_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_sbc_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jr_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_bc(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_de(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_inc_sp(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_call_nn(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_xor_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_00h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_08h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_10h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_18h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_20h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_28h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_30h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_rst_38h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldd_hl_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldd_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_hlminus(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_a_hld(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jr_nz_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jr_z_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jr_nc_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_jr_c_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_di(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldh_n_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldh_a_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_cp_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_hl_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ld_nn_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldi_a_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ldh_c_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_or_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ret(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ei(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_and_n(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_a(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_b(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_c(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_d(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_e(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_h(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_l(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_swap_hl(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);
Status fn_ext(struct cpu_cpu *cpu, unsigned char arg1, unsigned char arg2);

static const struct cpu_instruction instructions[256] = {
	{"NOP", 0, fn_nop},
	{"LD BC,nn", 2, fn_ld_bc_nn},
	{"LD (BC),A", 0, fn_ld_bc_a},
	{"INC BC", 0, fn_inc_bc},
	{"INC B", 0, fn_inc_b},
	{"DEC B", 0, fn_dec_b},
	{"LD B,n", 1, fn_ld_b_n},
	{"RLC A", 0, NULL},
	{"LD (nn),SP", 2, NULL},
	{"ADD HL,BC", 0, fn_add_hl_bc},
	{"LD A,(BC)", 0, NULL},
	{"DEC BC", 0, fn_dec_bc},
	{"INC C", 0, fn_inc_c},
	{"DEC C", 0, fn_dec_c},
	{"LD C,n", 1, fn_ld_c_n},
	{"RRC A", 0, NULL},
	{"STOP", 0, fn_stop},
	{"LD DE,nn", 2, fn_ld_de_nn},
	{"LD (DE),A", 0, fn_ld_de_a},
	{"INC DE", 0, fn_inc_de},
	{"INC D", 0, fn_inc_d},
	{"DEC D", 0, fn_dec_d},
	{"LD D,n", 1, fn_ld_d_n},
	{"RL A", 0, NULL},
	{"JR n", 1, fn_jr_n},
	{"ADD HL,DE", 0, fn_add_hl_de},
	{"LD A,(DE)", 0, NULL},
	{"DEC DE", 0, fn_dec_bc},
	{"INC E", 0, fn_inc_e},
	{"DEC E", 0, fn_dec_e},
	{"LD E,n", 1, fn_ld_e_n},
	{"RRA", 0, fn_rra},
	{"JR NZ,n", 1, fn_jr_nz_n},
	{"LD HL,nn", 2, fn_ld_hl_nn},
	{"LDI (HL),A", 0, fn_ldi_hl_a},
	{"INC HL", 0, fn_inc_hl},
	{"INC H", 0, fn_inc_h},
	{"DEC H", 0, fn_dec_h},
	{"LD H,n", 1, fn_ld_h_n},
	{"DAA", 0, NULL},
	{"JR Z,n", 1, fn_jr_z_n},
	{"ADD HL,HL", 0, fn_add_hl_hl},
	{"LDI A,(HL)", 0, fn_ldi_a_hl},
	{"DEC HL", 0, fn_dec_hl},
	{"INC L", 0, fn_inc_l},
	{"DEC L", 0, fn_dec_l},
	{"LD L,n", 1, fn_ld_l_n},
	{"CPL", 0, fn_cpl},
	{"JR NC,n", 1, fn_jr_nc_n},
	{"LD SP,nn", 2, fn_ld_sp_nn},
	{"LDD (HL),A", 0, fn_ldd_hl_a},
	{"INC SP", 0, fn_inc_sp},
	{"INC (HL)", 0, NULL},
	{"DEC (HL)", 0, NULL},
	{"LD (HL),n", 1, fn_ld_hl_n},
	{"SCF", 0, NULL},
	{"JR C,n", 1, fn_jr_c_n},
	{"ADD HL,SP", 0, fn_add_hl_sp},
	{"LDD A,(HL)", 0, fn_ldd_a_hl},
	{"DEC SP", 0, fn_dec_sp},
	{"INC A", 0, fn_inc_a},
	{"DEC A", 0, fn_dec_a},
	{"LD A,n", 1, fn_ld_a_n},
	{"CCF", 0, NULL},
	{"LD B,C", 0, fn_ld_b_c},
	{"LD B,B", 0, fn_ld_b_b},
	{"LD B,D", 0, fn_ld_b_d},
	{"LD B,E", 0, fn_ld_b_e},
	{"LD B,H", 0, fn_ld_b_h},
	{"LD B,L", 0, fn_ld_b_l},
	{"LD B,(HL)", 0, fn_ld_b_hl},
	{"LD B,A", 0, fn_ld_b_a},
	{"LD C,B", 0, fn_ld_c_b},
	{"LD C,C", 0, fn_ld_c_c},
	{"LD C,D", 0, fn_ld_c_d},
	{"LD C,E", 0, fn_ld_c_e},
	{"LD C,H", 0, fn_ld_c_h},
	{"LD C,L", 0, fn_ld_c_l},
	{"LD C,(HL)", 0, fn_ld_c_hl},
	{"LD C,A", 0, fn_ld_c_a},
	{"LD D,B", 0, fn_ld_d_b},
	{"LD D,C", 0, fn_ld_d_c},
	{"LD D,D", 0, fn_ld_d_d},
	{"LD D,E", 0, fn_ld_d_e},
	{"LD D,H", 0, fn_ld_d_h},
	{"LD D,L", 0, fn_ld_d_l},
	{"LD D,(HL)", 0, fn_ld_d_hl},
	{"LD D,A", 0, fn_ld_d_a},
	{"LD E,B", 0, fn_ld_e_b},
	{"LD E,C", 0, fn_ld_e_c},
	{"LD E,D", 0, fn_ld_e_d},
	{"LD E,E", 0, fn_ld_e_e},
	{"LD E,H", 0, fn_ld_e_h},
	{"LD E,L", 0, fn_ld_e_l},
	{"LD E,(HL)", 0, fn_ld_e_hl},
	{"LD E,A", 0, fn_ld_e_a},
	{"LD H,B", 0, fn_ld_h_b},
	{"LD H,C", 0, fn_ld_h_c},
	{"LD H,D", 0, fn_ld_h_d},
	{"LD H,E", 0, fn_ld_h_e},
	{"LD H,H", 0, fn_ld_h_h},
	{"LD H,L", 0, fn_ld_h_l},
	{"LD H,(HL)", 0, fn_ld_h_hl},
	{"LD H,A", 0, fn_ld_h_a},
	{"LD L,B", 0, fn_ld_l_b},
	{"LD L,C", 0, fn_ld_l_c},
	{"LD L,D", 0, fn_ld_l_d},
	{"LD L,E", 0, fn_ld_l_e},
	{"LD L,H", 0, fn_ld_l_h},
	{"LD L,L", 0, fn_ld_l_l},
	{"LD L,(HL)", 0, fn_ld_l_hl},
	{"LD L,A", 0, fn_ld_l_a},
	{"LD (HL),B", 0, fn_ld_hl_b},
	{"LD (HL),C", 0, fn_ld_hl_c},
	{"LD (HL),D", 0, fn_ld_hl_d},
	{"LD (HL),E", 0, fn_ld_hl_e},
	{"LD (HL),H", 0, fn_ld_hl_h},
	{"LD (HL),L", 0, fn_ld_hl_l},
	{"HALT", 0, NULL},
	{"LD (HL),A", 0, fn_ld_hl_a},
	{"LD A,B", 0, fn_ld_a_b},
	{"LD A,C", 0, fn_ld_a_c},
	{"LD A,D", 0, fn_ld_a_d},
	{"LD A,E", 0, fn_ld_a_e},
	{"LD A,H", 0, fn_ld_a_h},
	{"LD A,L", 0, fn_ld_a_l},
	{"LD A,(HL)", 0, fn_ld_a_hl},
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
	{"SUB A,B", 0, fn_sub_a_b},
	{"SUB A,C", 0, fn_sub_a_c},
	{"SUB A,D", 0, fn_sub_a_d},
	{"SUB A,E", 0, fn_sub_a_e},
	{"SUB A,H", 0, fn_sub_a_h},
	{"SUB A,L", 0, fn_sub_a_l},
	{"SUB A,(HL)", 0, fn_sub_a_hl},
	{"SUB A,A", 0, fn_sub_a_a},
	{"SBC A,B", 0, fn_sbc_a_b},
	{"SBC A,C", 0, fn_sbc_a_c},
	{"SBC A,D", 0, fn_sbc_a_d},
	{"SBC A,E", 0, fn_sbc_a_e},
	{"SBC A,H", 0, fn_sbc_a_h},
	{"SBC A,L", 0, fn_sbc_a_l},
	{"SBC A,(HL)", 0, fn_sbc_a_hl},
	{"SBC A,A", 0, fn_sbc_a_a},
	{"AND B", 0, fn_and_b},
	{"AND C", 0, fn_and_c},
	{"AND D", 0, fn_and_d},
	{"AND E", 0, fn_and_e},
	{"AND H", 0, fn_and_h},
	{"AND L", 0, fn_and_l},
	{"AND (HL)", 0, NULL},
	{"AND A", 0, fn_and_a},
	{"XOR B", 0, fn_xor_b},
	{"XOR C", 0, fn_xor_c},
	{"XOR D", 0, fn_xor_d},
	{"XOR E", 0, fn_xor_e},
	{"XOR H", 0, fn_xor_h},
	{"XOR L", 0, fn_xor_l},
	{"XOR (HL)", 0, fn_xor_hl},
	{"XOR A", 0, fn_xor_a},
	{"OR B", 0, fn_or_b},
	{"OR C", 0, fn_or_c},
	{"OR D", 0, fn_or_d},
	{"OR E", 0, fn_or_e},
	{"OR H", 0, fn_or_h},
	{"OR L", 0, fn_or_l},
	{"OR (HL)", 0, NULL},
	{"OR A", 0, fn_or_a},
	{"CP B", 0, fn_cp_b},
	{"CP C", 0, fn_cp_c},
	{"CP D", 0, fn_cp_d},
	{"CP E", 0, fn_cp_e},
	{"CP H", 0, fn_cp_h},
	{"CP L", 0, fn_cp_l},
	{"CP (HL)", 0, fn_cp_hl},
	{"CP A", 0, fn_cp_a},
	{"RET NZ", 0, NULL},
	{"POP BC", 0, NULL},
	{"JP NZ,nn", 2, NULL},
	{"JP nn", 2, fn_jp_nn},
	{"CALL NZ,nn", 2, NULL},
	{"PUSH BC", 0, NULL},
	{"ADD A,n", 1, NULL},
	{"RST 0", 0, fn_rst_00h},
	{"RET Z", 0, NULL},
	{"RET", 0, fn_ret},
	{"JP Z,nn", 2, NULL},
	{"Ext ops", 1, fn_ext},
	{"CALL Z,nn", 2, NULL},
	{"CALL nn", 2, fn_call_nn},
	{"ADC A,n", 1, NULL},
	{"RST 8", 0, fn_rst_08h},
	{"RET NC", 0, NULL},
	{"POP DE", 0, NULL},
	{"JP NC,nn", 2, NULL},
	{"XX", 0, NULL},
	{"CALL NC,nn", 2, NULL},
	{"PUSH DE", 0, NULL},
	{"SUB A,n", 1, NULL},
	{"RST 10", 0, fn_rst_10h},
	{"RET C", 0, NULL},
	{"RETI", 0, NULL},
	{"JP C,nn", 2, NULL},
	{"XX", 0, NULL},
	{"CALL C,nn", 2, NULL},
	{"XX", 0, NULL},
	{"SBC A,n", 1, NULL},
	{"RST 18", 0, fn_rst_18h},
	{"LDH (n),A", 1, fn_ldh_n_a},
	{"POP HL", 0, NULL},
	{"LDH (C),A", 0, fn_ldh_c_a},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"PUSH HL", 0, NULL},
	{"AND n", 1, fn_and_n},
	{"RST 20", 0, fn_rst_20h},
	{"ADD SP,d", 0, NULL},
	{"JP (HL)", 0, NULL},
	{"LD (nn),A", 2, fn_ld_nn_a},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"XOR n", 1, NULL},
	{"RST 28", 0, fn_rst_28h},
	{"LDH A,(n)", 1, fn_ldh_a_n},
	{"POP AF", 0, NULL},
	{"XX", 0, NULL},
	{"DI", 0, fn_di},
	{"XX", 0, NULL},
	{"PUSH AF", 0, NULL},
	{"OR n", 1, fn_or_n},
	{"RST 30", 0, fn_rst_30h},
	{"LDHL SP,d", 0, NULL},
	{"LD SP,HL", 0, NULL},
	{"LD A,(nn)", 2, NULL},
	{"EI", 0, fn_ei},
	{"XX", 0, NULL},
	{"XX", 0, NULL},
	{"CP n", 1, fn_cp_n},
	{"RST 38", 0, fn_rst_38h}
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
