#include "variable_ops.h"
#include "asm_commands.h"
#include "microcontroller_consts.h"
#include "flash_alloc.h"
#include "expression_parser.h"

// decode an expression into a linear series of instructions

struct instruction {
	char op; // '+' or '-', etc.
	const char* varName; // name of variable being added
	int val; // val being added
	memory_allocation location; // being operated on

	instruction(memory_allocation m, const char* vn, char o) : varName(vn), op(o), val(0), location(m) {}
	instruction(memory_allocation m, int v, char o) : varName(nullptr), op(o), val(v), location(m) {}
};

struct instruction_alist {
	instruction* instructions = (instruction*)malloc(0);
	int sz = 0;
};

instruction_alist parse_expression(char* expression) {

}