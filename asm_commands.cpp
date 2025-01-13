#include "asm_commands.h"
#include <stdio.h>


void ldi(int reg, char val) {
	printf("ldi %d %d\n", reg, val);
}

void mov(int reg1, int reg2) {
	printf("mov %d %d\n", reg1, reg2);
}

void add(int reg1, int reg2) {
	printf("add %d %d\n", reg1, reg2);
}

void sts(int memloc, int reg) {
	printf("sts %u %d\n", memloc, reg);
}

void push(int reg) {
	printf("push %d\n", reg);
}

void pop(int reg) {
	printf("pop %d\n", reg);
}

void jmp(const char* lbl) {
	printf("jmp %s\n", lbl);
}

void cp(int reg1, int reg2) {
	printf("cp %d %d\n", reg1, reg2);
}

void cpi(int reg1, int val) {
	printf("cpi %d %d\n", reg1, val);
}

void ld(int reg, int loc) {
	printf("ld %d %d\n", reg, loc);
}

void adiw(int reg, int val) {
	printf("adiw %d %d\n", reg, val);
}

void sbiw(int reg, int val) {
	printf("sbiw %d %d\n", reg, val);
}

void label(const char* label) {
	printf("%s\n", label);
}

void brge(const char* lbl) {
	printf("brge %s\n", lbl);
}

void brlt(const char* lbl) {
	printf("brlt %s\n", lbl);
}

void breq(const char* lbl) {
	printf("breq %s\n", lbl);
}

void brne(const char* lbl) {
	printf("brne %s\n", lbl);
}