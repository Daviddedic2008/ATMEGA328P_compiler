#pragma once

// all commands that can be compiled

void ldi(int reg, char val);

void mov(int reg1, int reg2);

void add(int reg1, int reg2);

void sts(int memloc, int reg);

void push(int reg);

void pop(int reg);