#include "cpu.h"
#include <stdio.h>

#define OPCODE(x) ((x)>>26)
#define RS(x) (((x)>>21)&0x1F)
#define RT(x) (((x)>>16)&0x1F)
#define IMM(x) ((x)&0xFFFF)

unsigned int sign_ext(unsigned int imm) {
	if ((imm & 0x8000) == 0)
		return (imm | 0x00000000);
	else {
		int mask = (1 << 16) - 1;
		mask = mask << 16;
		return (mask | (int)imm);
	}
}

void addi(unsigned int instruction) {
	int res = (int)registers[RS(instruction)] + (int)sign_ext(IMM(instruction));
	registers[RT(instruction)] = (unsigned int) res;
}

void addiu(unsigned int instruction) {
	registers[RT(instruction)] = registers[RS(instruction)] + sign_ext(IMM(instruction));
}

void andi(unsigned int instruction) {
	registers[RT(instruction)] = registers[RS(instruction)] & sign_ext(IMM(instruction));
}

void ori(unsigned int instruction) {
	registers[RT(instruction)] = registers[RS(instruction)] | sign_ext(IMM(instruction));
}

void xori(unsigned int instruction) {
	registers[RT(instruction)] = registers[RS(instruction)] ^ sign_ext(IMM(instruction));
}

void slti(unsigned int instruction) {
	if ((int)registers[RS(instruction)] < (int)sign_ext(IMM(instruction)))
		registers[RT(instruction)] = 1;
	else	
		registers[RT(instruction)] = 0;
}

void sltiu(unsigned int instruction) {
	if (registers[RS(instruction)] < sign_ext(IMM(instruction)))
		registers[RT(instruction)] = 1;
	else	
		registers[RT(instruction)] = 0;
}

void beq(unsigned int instruction) {
	if (registers[RS(instruction)] == registers[RT(instruction)]) 
		npc = pc + 4 + (sign_ext(IMM(instruction)) << 2);
}

void bne(unsigned int instruction) {
	if (registers[RS(instruction)] != registers[RT(instruction)])
		npc = pc + 4 + (sign_ext(IMM(instruction)) << 2);
}

void lb(unsigned int instruction) {
	char *p = (char *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	registers[RT(instruction)] = sign_ext(*p);
}

void lbu(unsigned int instruction) {
	registers[RT(instruction)] = memory[registers[RS(instruction)] + sign_ext(IMM(instruction))] | 0x00000000;
}

void lh(unsigned int instruction) {
	unsigned short *p = (unsigned short *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	registers[RT(instruction)] = sign_ext(*p);
}

void lhu(unsigned int instruction) {
	unsigned short *p = (unsigned short *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	registers[RT(instruction)] = (*p) | 0x00000000;
}

void lw(unsigned int instruction) {
	unsigned int *p = (unsigned int *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	registers[RT(instruction)] = *p;
}

void lui(unsigned int instruction) {
	registers[RT(instruction)] = (IMM(instruction) << 16);
}

void sb(unsigned int instruction) {
	memory[registers[RS(instruction)] + sign_ext(IMM(instruction))] = registers[RT(instruction)];
}

void sh(unsigned int instruction) {
	unsigned short *p = (unsigned short *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	(*p) = registers[RT(instruction)];
}

void sw(unsigned int instruction) {
	unsigned int *p = (unsigned int *)&memory[registers[RS(instruction)] + sign_ext(IMM(instruction))];
	(*p) = registers[RT(instruction)];
}