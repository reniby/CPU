
#include <stdio.h>
#include "cpu.h"
#include "r_instructions.h"
#include "i_instructions.h"
#include "j_instructions.h"

#define OPCODE(x) ((x)>>26)
#define FUNCT(x) ((x)&0x3F)

#define TRUE 1
#define FALSE 0

unsigned int registers[NUM_REGISTERS];

unsigned int pc;  
unsigned int npc;

unsigned int HI;
unsigned int LO;

unsigned char memory[MEMORY_SIZE_IN_BYTES];

void handle_r(unsigned int opcode);
int cpux = TRUE;

//This is the procedure for initializing (or reinitializing) the CPU.
void cpu_initialize() {
	pc = CODE_STARTING_ADDRESS;
	npc = CODE_STARTING_ADDRESS;
	registers[29] = STACK_STARTING_ADDRESS;
	registers[0] = 0;
}

//This is the procedure for causing the CPU to execute. It should
//start by executing the instruction at address CODE_STARTING_ADDRESS
void  cpu_execute() {
	cpux = TRUE;
	while (cpux == TRUE) {
		pc = npc;
		npc = npc + 4;
		unsigned int *p = (unsigned int *)&memory[pc];
		unsigned int pcinstr = *p;
		
		switch (OPCODE(pcinstr)){
			case 0: handle_r(pcinstr);
				break;
			case 0x08: addi(pcinstr);
				break;
			case 0x09: addiu(pcinstr);
				break;
			case 0x23: lw(pcinstr);
				break;
			case 0x21: lh(pcinstr);
				break;
			case 0x25: lhu(pcinstr);
				break;
			case 0x20: lb(pcinstr);
				break;
			case 0x24: lbu(pcinstr);
				break;
			case 0x2b: sw(pcinstr);
				break;
			case 0x29: sh(pcinstr);
				break;	
			case 0x28: sb(pcinstr);
				break;
			case 0x0f: lui(pcinstr);
				break;
			case 0x0d: ori(pcinstr);
				break;
			case 0x0c: andi(pcinstr);
				break;
			case 0x0e: xori(pcinstr);
				break;
			case 0x0a: slti(pcinstr);
				break;
			case 0x0b: sltiu(pcinstr);
				break;
			case 0x04: beq(pcinstr);
				break;
			case 0x05: bne(pcinstr);
				break;
			case 0x02: j(pcinstr);
				break;
			case 0x03: jal(pcinstr);					
				break;
		}
	}
}




void handle_r(unsigned int rinstr) {
	switch (FUNCT(rinstr)) {
		case 0x20: add(rinstr);
			break;
		case 0x21: addu(rinstr);
			break;
		case 0x22: sub(rinstr);
			break;
		case 0x23: subu(rinstr);
			break;
		case 0x18: mult(rinstr);
			break;
		case 0x19: multu(rinstr);
			break;
		case 0x1a: div(rinstr);
			break;
		case 0x1b: divu(rinstr);
			break;
		case 0x10: mfhi(rinstr);
			break;
		case 0x12: mflo(rinstr);
			break;
		case 0x24: and(rinstr);
			break;
		case 0x25: or(rinstr);
			break;
		case 0x26: xor(rinstr);
			break;
		case 0x27: nor(rinstr);
			break;
		case 0x2a: slt(rinstr);
			break;
		case 0x2b: sltu(rinstr);
			break;
		case 0x00: sll(rinstr);
			break;
		case 0x04: sllv(rinstr);
			break;
		case 0x02: srl(rinstr);
			break;
		case 0x06: srlv(rinstr);
			break;
		case 0x03: sra(rinstr);
			break;
		case 0x07: srav(rinstr);
			break;
		case 0x08: jr(rinstr);
			break;
		case 0x09: jalr(rinstr);
			break;
		case 0x0c: syscall(rinstr);
			break;
	}
}

//This procedure will cause the CPU to stop executing the current program. 
//If errorcode is 0, a message indicating normal termination will be printed. 
//Otherwise, a message indicating abnormal termination, along with the
//errorcode, will be printed.
void cpu_exit(int errorcode) {
	if (errorcode == 0)
		printf("\nProgram terminated normally\n");
	else 
		printf("Program terminated with an error. Error code: %d\n", errorcode);
	cpux = FALSE;
}








