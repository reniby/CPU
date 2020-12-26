#include "cpu.h"
#include <stdio.h>

#define OPCODE(x) ((x)>>26)
#define ADD(x) ((x)&0x3FFFFFF)

void j(unsigned int instruction){
	npc = ((pc + 4) & 0xF0000000) | (ADD(instruction) << 2);
}	
void jal(unsigned int instruction) {
	registers[31] = pc + 4;
	npc = ((pc + 4) & 0xF0000000) | (ADD(instruction) << 2);
}