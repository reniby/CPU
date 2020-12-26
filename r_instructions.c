#include "cpu.h"

#define OPCODE(x) ((x)>>26)
#define RS(x) (((x)>>21)&0x1F)
#define RT(x) (((x)>>16)&0x1F)
#define RD(x) (((x)>>11)&0x1F)
#define SHAMT(x) (((x)>>6)&0x1F)
#define FUNCT(x) ((x)&0x3F)


void add(unsigned int instruction) {
	int res = (int) registers[RS(instruction)] + (int) registers[RT(instruction)];
	registers[RD(instruction)] = (unsigned int) res;
}

void addu(unsigned int instruction) {
	unsigned int res = registers[RS(instruction)] + registers[RT(instruction)];
	registers[RD(instruction)] = res;
}

void sub(unsigned int instruction) {
	int res = (int) registers[RS(instruction)] - (int) registers[RT(instruction)];
	registers[RD(instruction)] = (unsigned int) res;
}

void subu(unsigned int instruction) {
	unsigned int res = registers[RS(instruction)] - registers[RT(instruction)];
	registers[RD(instruction)] = res;
}

void mult(unsigned int instruction) {
	long res = (long)registers[RS(instruction)] * (long)registers[RT(instruction)]; 
	HI = res>>32;
	LO = res&0xFFFFFFFF;
}

void multu(unsigned int instruction) {
	unsigned long res = (unsigned long)registers[RS(instruction)] * (unsigned long)registers[RT(instruction)]; 
	HI = res>>32;
	LO = res&0xFFFFFFFF;
}

void div(unsigned int instruction) {
	LO = (int)registers[RS(instruction)] / (int)registers[RT(instruction)]; 
	HI = (int)registers[RS(instruction)] % (int)registers[RT(instruction)];
}

void divu(unsigned int instruction) {
	LO = (unsigned long)registers[RS(instruction)] / (unsigned long)registers[RT(instruction)]; 
	HI = (unsigned long)registers[RS(instruction)] % (unsigned long)registers[RT(instruction)]; 
}	

void and(unsigned int instruction) {
	registers[RD(instruction)] = registers[RS(instruction)] & registers[RT(instruction)];
}	

void nor(unsigned int instruction) {
	registers[RD(instruction)] = ~(registers[RS(instruction)] | registers[RT(instruction)]);
}	

void or(unsigned int instruction) {
	registers[RD(instruction)] = registers[RS(instruction)] | registers[RT(instruction)];
}

void xor(unsigned int instruction) {
	registers[RD(instruction)] = registers[RS(instruction)] ^ registers[RT(instruction)];
}

void sll(unsigned int instruction) {
	registers[RD(instruction)] = registers[RT(instruction)] << SHAMT(instruction);
}

void sllv(unsigned int instruction) {
	registers[RD(instruction)] = registers[RS(instruction)] << registers[RT(instruction)];
}

void srl(unsigned int instruction) {
	registers[RD(instruction)] = registers[RT(instruction)] >> SHAMT(instruction);
} 

void srlv(unsigned int instruction) {
	registers[RD(instruction)] = registers[RS(instruction)] >> registers[RT(instruction)];
}

void sra(unsigned int instruction) {
	if ((registers[RT(instruction)]&0x80000000) == 0)
		registers[RD(instruction)] = registers[RT(instruction)] >> SHAMT(instruction);
	else {
		int mask = (1 << SHAMT(instruction)) - 1;
		mask = mask << (32 - SHAMT(instruction));
		registers[RD(instruction)] = (mask | ((int)registers[RT(instruction)] >> SHAMT(instruction)));
	}
}

void srav(unsigned int instruction) {
	if ((registers[RS(instruction)]&0x80000000) == 0)
		registers[RD(instruction)] = registers[RS(instruction)] >> registers[RT(instruction)];
	else {
		int mask = (1 << registers[RT(instruction)]) - 1;
		mask = mask << (32 - registers[RT(instruction)]);
		registers[RD(instruction)] = (mask | ((int)registers[RS(instruction)] >> registers[RT(instruction)]));
	}
}

void slt(unsigned int instruction) {
	if ((int)registers[RS(instruction)] < (int)registers[RT(instruction)])
		registers[RD(instruction)] = 1;
	else
		registers[RD(instruction)] = 0;
}

void sltu(unsigned int instruction) {
	if (registers[RS(instruction)] < registers[RT(instruction)])
		registers[RD(instruction)] = 1;
	else
		registers[RD(instruction)] = 0;
}

void jr(unsigned int instruction) {
	npc = registers[RS(instruction)];
}

void jalr(unsigned int instruction) {
	registers[31] = pc + 4;
	npc = registers[RS(instruction)];
}

void mfhi(unsigned int instruction) {
	registers[RD(instruction)] = HI;
}

void mflo(unsigned int instruction) {
	registers[RD(instruction)] = LO;
} 