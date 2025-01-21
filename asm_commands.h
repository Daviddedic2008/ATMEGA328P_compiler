#pragma once

// all commands that can be compiled

void ldi(int reg, char val);

void mov(int reg1, int reg2);

void add(int reg1, int reg2);

void adc(int reg1, int reg2);

void mul(int reg1, int reg2);

void mulc(int reg1, int reg2);

void sts(int memloc, int reg);

void push(int reg);

void pop(int reg);

void jmp(const char* lbl);

void cp(int reg1, int reg2);

void cpi(int reg1, int val);

void ld(int reg, int loc);

void adiw(int reg, int val);

void sbiw(int reg, int val);

void label(const char* label);

void brge(const char* lbl);

void brlt(const char* lbl);

void breq(const char* lbl);

void brne(const char* lbl);